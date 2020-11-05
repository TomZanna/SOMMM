/**
 * 
 * 
 *             Smart Orario Management Marconi Magalini
 *                         5AI anno 2k18/2k19
 *           -------------------------------------------
 *                              TEAM 1
 *           -------------------------------------------
 *           *- Riccardo Bussola
 *           *- Cucino Federico
 *           *- Victor Annunziata
 * 
 *            Project : SOMMM x ESP32
 *           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *                                                               
          _____                   _______                   _____                    _____                    _____          
         /\    \                 /::\    \                 /\    \                  /\    \                  /\    \         
        /::\    \               /::::\    \               /::\____\                /::\____\                /::\____\        
       /::::\    \             /::::::\    \             /::::|   |               /::::|   |               /::::|   |        
      /::::::\    \           /::::::::\    \           /:::::|   |              /:::::|   |              /:::::|   |        
     /:::/\:::\    \         /:::/~~\:::\    \         /::::::|   |             /::::::|   |             /::::::|   |        
    /:::/__\:::\    \       /:::/    \:::\    \       /:::/|::|   |            /:::/|::|   |            /:::/|::|   |        
    \:::\   \:::\    \     /:::/    / \:::\    \     /:::/ |::|   |           /:::/ |::|   |           /:::/ |::|   |        
  ___\:::\   \:::\    \   /:::/____/   \:::\____\   /:::/  |::|___|______    /:::/  |::|___|______    /:::/  |::|___|______  
 /\   \:::\   \:::\    \ |:::|    |     |:::|    | /:::/   |::::::::\    \  /:::/   |::::::::\    \  /:::/   |::::::::\    \ 
/::\   \:::\   \:::\____\|:::|____|     |:::|    |/:::/    |:::::::::\____\/:::/    |:::::::::\____\/:::/    |:::::::::\____\
\:::\   \:::\   \::/    / \:::\    \   /:::/    / \::/    / ~~~~~/:::/    /\::/    / ~~~~~/:::/    /\::/    / ~~~~~/:::/    /
 \:::\   \:::\   \/____/   \:::\    \ /:::/    /   \/____/      /:::/    /  \/____/      /:::/    /  \/____/      /:::/    / 
  \:::\   \:::\    \        \:::\    /:::/    /                /:::/    /               /:::/    /               /:::/    /  
   \:::\   \:::\____\        \:::\__/:::/    /                /:::/    /               /:::/    /               /:::/    /   
    \:::\  /:::/    /         \::::::::/    /                /:::/    /               /:::/    /               /:::/    /    
     \:::\/:::/    /           \::::::/    /                /:::/    /               /:::/    /               /:::/    /     
      \::::::/    /             \::::/    /                /:::/    /               /:::/    /               /:::/    /      
       \::::/    /               \::/____/                /:::/    /               /:::/    /               /:::/    /       
        \::/    /                 ~~                      \::/    /                \::/    /                \::/    /        
         \/____/                                           \/____/                  \/____/                  \/____/         V 2.0


                                  ./oo/-             `-+++/`                  /ydmdy:         
                                .so++omy           odhddmMN.                ymsohmNMy        
                                .`` .-/m-          N`   /mM+               .m:```:yNd        
                                `::`:-.+.          :.:`-+oy-               .:.:/:shm-        
                                  .`.-`-/` `         ```-`:s-`              `-`-:s+y-         
                              `.:::/--:::../+-    `  o-:/+o+-:/.          ``-///ohdy          
                            `+sdNm/-.:+ohdmNNds-+-  `y/-://-`:Nmo-   `..+syhmooydmmNy/-`      
                          .hdyhmNh:/hmNmddmddNmNds:..m::+y:ydNMMNo -syhNdhmdhhhoydNMMMmdo-`  
                          `yhhdhddhshhhyyymdhmNMMNNdh`dNMdoNMMMMMMNohhddmysyhhyNmmNNmNNmdmNh. 
                          sdhmmdddhyyhhdmNmydNNMMMMNh-yMMymMNmNMMMmNdmmNdsssydddhydddddddMNMm`
                        +hddNNmdmNmmmmm+shyNNMMMMMMh+yMMdMNMMNMMMNNmhdMmdhhhdNdhhshdmmMMMMMMo
                        -dhdNhssysyyhhhyoshdMmNMMMhdmmdMmNmsMs/MMMMMNdNMNNmdmdMdhhdNNNMMMMMMMo
                        +dhyyhmhhyyysysshshNMNNMMMomNNNNNmNmmdNMMMMMNNNMMNmmdmmhdmNMMMMMMNNMMo
                        -mmddhhmmmmmdddhddNMMNNMNNNMMMMMMMMMMMMMMMMMNMMMNmmdmmddmNNMNMMMNNmmNo
                        `:+dNNNmdmmmmNNMMMMMMMMMMNMMMMMMMMMMMMMMMMmddmNmyyyyhyyhyhmNMMMMNmmmo
                          `-yysssssosyhdmmNNmmNNhhNNNNNNNNNNNNNNNdmy/:/ymdhysssyyhhhdmNNmyyydo
 */

#include <Arduino.h>
#include <SPIFFS.h>

#include <ArduinoOTA.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.h>
#include <AsyncJson.h>

#include "page/Page.hpp"

AsyncWebServer server(1518); // settaggio server sulla porta 1518

// FUNZIONI DEFINITE INIZIALMENTE PER POI ESSERE IMPLEMENTATE
void save_json(AsyncWebServerRequest *richiesta, JsonVariant &json);
void tabella();                        // funzione per il disegno della tabella principale
void log_error(String error_m);        // funzione per il salvataggio di messaggi di log viisibile attraverso il webserver /error_log

// DEFINIZIONE DELLE VARIABILI GLOBALI NECESSARIE AL SISTEMA

enum wifi_stat
{
  MY_WL_NO_SHIELD = 255,
  MY_WL_IDLE_STATUS = 0,
  MY_WL_NO_SSID_AVAIL = 1,
  MY_WL_SCAN_COMPLETED = 2,
  MY_WL_CONNECTED = 3,
  MY_WL_CONNECT_FAILED = 4,
  MY_WL_CONNECTION_LOST = 5,
  MY_WL_DISCONNECTED = 6,
};

const String version = "v2.2.1.0 x32";

//CREDENZIALI WEB

const char *www_username = "SOMMM";
const char *www_password = "laPasswordQui";
String random_id = "SOMMM_";

bool canRequest = false;
const char *payload = ""; // payload come variabile globale
int oraAttuale = 1;       // sisema di switch per le giornate con + di 6 ore
int httpCode = 0;

const char *net_ssid = "";
const char *net_pswd = "";
const char *api_url = "";
String aula_id = "";

const unsigned long delay_time = 300000; // Intervallo di aggiornamento richiesta e display -> 5 minuti

String getData, Link, file_config;

HTTPClient http;

GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT> display(GxEPD2_750(15, 27, 26, 25));
PageSystem page(display);

void setup()
{

  // parte iniziale per la seriale
  Serial.begin(115200);
  Serial.println();
  Serial.println("SOMMM STARTUP");
  delay(100);
  page.initDisplay();

  page.startup(version);

  // Monto il mio SPIFFS File System
  if (!SPIFFS.begin())
  {
    Serial.println("File system non montato ");
    page.error("Errore caricamento File System");
  }
  else
  {
    Serial.println("File system montato");
  }

  // Dichiaro che il file da aprire è il config.json

  File config_json_file = SPIFFS.open("/config.json", "r");

  file_config = config_json_file.readStringUntil('\n'); // questo è il nostro config.js salvato su stringa

  // Creo buffer JSON per la lettura del file config.json
  DynamicJsonDocument jsonRead(1024);

  DeserializationError errorRead = deserializeJson(jsonRead, file_config);
  if (errorRead)
  {
    Serial.print("deserializeJson() line168 failed: ");
    Serial.println(errorRead.c_str());
    Serial.println("Impossibile leggere la configurazione");
    page.error("Errore lettura JSON configurazione");
    return;
  }
  else
  {
    Serial.println("Configurazione correttamente caricata");
    serializeJson(jsonRead, Serial);
    Serial.println("");
  }

  // vado a settare le variabili coi valori caricati dalla memoria

  net_ssid = jsonRead["net_ssid"];
  File pswdFile = SPIFFS.open("/passwd.txt", "r");
  String tempStr = pswdFile.readStringUntil('\n');
  net_pswd = tempStr.c_str();
  pswdFile.close();
  api_url = jsonRead["api_url"];
  aula_id = jsonRead["aula"].as<String>(); // Per API raggiungibile a /info

  // Solo se viene richiesto l'ip statico processo i dati
  JsonObject static_config = jsonRead["net_static"].as<JsonObject>();
  if (!static_config.isNull()) {
    // Memorizzo le chiavi così la matrice sarà sempre nello stesso ordine
    const char *settingsKeys[] = {"net_ip", "net_sm", "net_dfgw", "net_dns"};

    // Copio le impostazioni in una matrice contenente nell'ordine 
    // indirizzo ip, subnet mask, default gateway e dns 
    uint8_t settings[4][4];
    for(int row = 0; row<4; row++){
      int column=0;
      for(JsonVariant settingN: static_config[settingsKeys[row]].as<JsonArray>()){
        if(column>=4) break;
        settings[row][column] = settingN.as<int>();
        column++;
      }
    }

    Serial.println("Configurazione statica...");
    IPAddress ip_addr(settings[0]);
    IPAddress sm_addr(settings[1]);
    IPAddress gw_addr(settings[2]);
    IPAddress dns_addr(settings[3]);

    Serial.println(ip_addr);
    Serial.println(sm_addr);
    Serial.println(gw_addr);
    Serial.println(dns_addr);

    if (!WiFi.config(ip_addr, gw_addr, sm_addr, dns_addr))
    { // Configurazione statica del web-server in caso di Client
      Serial.println("Errore configurazione statica");
    }
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(net_ssid, net_pswd); // Provo a eseguire una connessione con le credenziali che ho

  Serial.println("Connecting");

  const unsigned long start_c = millis();
  unsigned long counter = 0;
  const unsigned long soglia = 40000; // soglia di controllo per passare il AP (default 40s)

  while (WiFi.status() != WL_CONNECTED && counter < soglia) // Wait for connection
  {
    counter = millis() - start_c;
    Serial.println(counter);
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.getHostname());

  if (WiFi.status() == WL_CONNECTED)
  {
    // Connessione stabilita
    Serial.println(WiFi.localIP().toString().c_str());

    // Setto http sull'indirizzo del mio server
    String http_address = String(api_url) + "?stanza=" + aula_id; // Creo l'url per indirizzo API

    Serial.print("Richiesta settata su: "); // Stampo l'indirizzo
    Serial.println(http_address);

    canRequest = true; // Abilito l'invio del dato

    http.begin(http_address); // configuro e avvio http sul'url precedentemente dichiarato

    // Dichiaro la struttura del mio filesystem in modo da caricare i file archiviati con SPIFFS
    server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request) {
      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", aula_id);
      response->addHeader("Access-Control-Allow-Origin", "*");
      request->send(response);
    });

    server.addHandler(new AsyncCallbackJsonWebHandler("/save", save_json));
    server.serveStatic("/", SPIFFS, "/html/").setDefaultFile("index.html");
    server.serveStatic("/error_log", SPIFFS, "/log.txt");
    server.serveStatic("/config", SPIFFS, "/config.json");
    server.begin(); //Faccio partire il server

    // Port defaults to 3232
    ArduinoOTA.setPort(1815);

    // Hostname defaults to esp3232-[MAC]
    // ArduinoOTA.setHostname("myesp32");

    // No authentication by default
    ArduinoOTA.setPassword("laPasswordQui");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA
        .onStart([]() {
          String type;
          if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
          else // U_SPIFFS
            type = "filesystem";

          // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
          SPIFFS.end();
          Serial.println("Start updating " + type);
        })
        .onEnd([]() {
          Serial.println("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
          Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
          Serial.printf("Error[%u]: ", error);
          if (error == OTA_AUTH_ERROR)
            Serial.println("Auth Failed");
          else if (error == OTA_BEGIN_ERROR)
            Serial.println("Begin Failed");
          else if (error == OTA_CONNECT_ERROR)
            Serial.println("Connect Failed");
          else if (error == OTA_RECEIVE_ERROR)
            Serial.println("Receive Failed");
          else if (error == OTA_END_ERROR)
            Serial.println("End Failed");
        });

    ArduinoOTA.begin();

    tabella();
  }
  else
  {
    //Creo una stringa random e la aggiungo al device
    for (int i = 0; i < 3; i++)
    {
      random_id += char(random('a', 'z' + 1));
    }

    // Problemi di connessione (probabilmente rete non raggiungibile e/o settato), avvio accesss Point
    WiFi.disconnect(true); // Disconnetto la wifi
    WiFi.mode(WIFI_AP);    // Wifi Mode accesss-Point

    WiFi.softAP(random_id.c_str(), "laPasswordQui"); // dichiaro i parametri del mio accesss point

    Serial.println("Access Point Mode");
    Serial.println(WiFi.softAPIP());
    page.access_point(random_id);

    server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request) {
      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", aula_id);
      response->addHeader("Access-Control-Allow-Origin", "*");
      request->send(response);
    });

    server.addHandler(new AsyncCallbackJsonWebHandler("/save", save_json));
    server.serveStatic("/", SPIFFS, "/html/").setDefaultFile("index.html");
    server.serveStatic("/error_log", SPIFFS, "/log.txt");
    server.serveStatic("/config", SPIFFS, "/config.json");
    server.begin(); // Faccio partire il server
  }

  config_json_file.close();
}

unsigned long timeCounter = millis();

void loop()
{

  if (canRequest)
  {
    ArduinoOTA.handle();
    
    if ((millis() - timeCounter) >= delay_time)
    {
      // mando la richiesta
      Serial.println("--------------------");
      tabella();
      timeCounter = millis(); // azzerro il contatore
    }
  }
}

void tabella()
{
  // CREO LA RICHIESTA ALLE API

  httpCode = http.GET();
  String response = http.getString();
  payload = response.c_str();

  Serial.println(httpCode);
  Serial.println(payload);

  http.end();

  /**
    !!!!PAURISSIMAAA!!!!!
    Provo a gestire l'interpretazione del mio json
  */

  if (httpCode < 0)
  {
    page.error("Errore di connessione, verifica la rete");
    log_error("Codice http -> " + String(httpCode));
    delay(5000);
    ESP.restart();
  }

  // TODO: Valutare e implementare, se possibile, un do-while sulla richiesta fino a quando httpCode > 0

  const size_t bufferSize = 7 * JSON_ARRAY_SIZE(10) + 10 * JSON_OBJECT_SIZE(5) + 2 * JSON_OBJECT_SIZE(6) + 1050;
  DynamicJsonDocument doc(bufferSize);

  DeserializationError error = deserializeJson(doc, payload);
  if (error) // Se errore a elaborare json
  {
    Serial.print("deserializeJson() line552 failed: ");
    Serial.println(error.c_str());
    log_error("Deserializzazione API fallita");
    delay(5000);
    ESP.restart();
  }

  // Dati header

  const char *stanza = doc["stanza"];            // "L145"
  const char *giorno = doc["giorno"];            // "Venerdi', 23 Novembre 2018"
  int giorno_settimana = doc["giornoSettimana"]; // 5
  giorno_settimana -= 1;
  int oraAttuale = doc["oraAttuale"]; // 3

  // CREAZIONE DELL'OGGETTO CONTENENTE I DATI RIGUARDANTI A "OGGI"
  JsonArray oggi = doc["oggi"]; // Oggetto "oggi" contenente tutte le informazioni
  /* Matrice di strighe contenente le informazioni del girno in corso.
   * Ad ogni riga equivale un'ora e ad ogni colonna un'informazione. 
   */
  const char *today_matrix[10][5];

  if (doc["oggi"].size() == 0) {
    page.not_school("Oggi non c'e` scuola, buon riposo ;P");
    return;
  }
  else if (oraAttuale == 0) // Giornata terminata
  {
    page.not_school("La giornata scolastica e` terminata.");
    return;
  }

  {
    int row, column;
    row = 0;
    // per ogni oggetto oraN presente nell'array oggi
    for(JsonObject oraN: oggi) {
      column = 0;
      // per ogni coppia key-value nell'oggetto oraN
      for(JsonPair pair: oraN){
        // se supero le massime dimensioni dell'array mi fermo
        if(column>=5) break;
        // copio il riferimento alla stringa nella cella della matrice
        today_matrix[row][column] = pair.value();
        column++;
      }
      // se supero le massime dimensioni dell'array mi fermo
      if(row>=10) break;
      row++;
    }
  }

  // CREAZIONE DELL'OGGETTO CONTENENTE I DATI RIGUARDANTI A "SETTIMANA"
  JsonObject settimana = doc["settimana"]; // Oggetto "settima" contenente tutte le informazioni
  /* Matrice di strighe contenente le informazioni di tutta la settimana.
   * Ad ogni riga equivale un giorno della settimana e ad ogni colonna un'informazione. 
   */
  const char *settimana_matrix[6][6];
  
  {
    int row, column;
    row = 0;
    // per ogni oggetto giornoN presente nell'array settimana
    for(JsonPair giornoN: settimana) {
      column = 0;
      // per ogni coppia key-value nell'oggetto giornoN
      for(JsonPair oraN: giornoN.value().as<JsonObject>()){
        // se supero le massime dimensioni dell'array mi fermo
        if(column>=6) break;
        // copio il riferimento alla stringa nella cella della matrice
        settimana_matrix[row][column] = oraN.value();
        column++;
      }
      // se supero le massime dimensioni dell'array mi fermo
      if(row>=6) break;
      row++;
    }
  }

  page.tabella(giorno_settimana, oraAttuale, stanza, giorno, today_matrix, settimana_matrix);
}

void save_json(AsyncWebServerRequest *richiesta, JsonVariant &json) {
  if (!SPIFFS.begin()) { // controllo di aver accesso al filesystem
    // Se viene visualizzato c'è un problema al filesystem
    richiesta->send(500, "text/plain", "Impossibile leggere la configurazione attualmente memorizzata"); // messaggio di callback per client web

    Serial.println("SPIFFS2 Mount failed");
    page.error("Errore caricamento File System");
    return;
  } else Serial.println("SPIFFS2 Mount succesfull");

  canRequest = false;

  if (!richiesta->authenticate(www_username, www_password))
    return richiesta->requestAuthentication();

  if(json["net_pswd"]!="") {
    // salvo la password su un file non accessibile dalla rete
    File pswdFile = SPIFFS.open("/passwd.txt", "w");
    pswdFile.printf("%s\n",json["net_pswd"].as<char *>());
    pswdFile.close();
  }
  json["net_pswd"]="x"; // la password non deve essere esposta all'esterno

  File configFile = SPIFFS.open("/config.json", "w");
  serializeJson(json, configFile);   // salvo la nuova configurazione
  serializeJson(json, Serial); // stampo la nuova configurazione

  configFile.close();
  SPIFFS.end();

  // messaggio di callback per client web
  richiesta->send(200, "text/plain", "Salvataggio effettuato correttamente. Riavvia SOMMM.");
  ESP.restart();
}

void log_error(String error_m)
{
  File log_file;
  log_file = SPIFFS.open("/log.txt", "a");

  //Serial.print("Dimensione file di log: ");
  long f_size = log_file.size();
  //Serial.println(f_size);

  if (f_size > 1000 /* 1000 byte */)
  {
    log_file.close();

    log_file = SPIFFS.open("/log.txt", "w"); // reset del file
    log_file.println("");
    log_file.close();

    log_file = SPIFFS.open("/log.txt", "a");
  }

  log_file.println((String(millis()) + " -> error: " + error_m).c_str());

  log_file.close();
}
