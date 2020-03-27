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
#include <images.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define ENABLE_GxEPD2_GFX 1
#include <GxEPD2_3C.h>
#include <GxEPD2_BW.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <WiFiClient.h>

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "AsyncJson.h"

#include "FS.h"
#include "SPIFFS.h"

// Font di varia grandezza per il display
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT> display(GxEPD2_750(/*CS=*/15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25));

AsyncWebServer server(1518); // settaggio server sulla porta 1518

// FUNZIONI DEFINITE INIZIALMENTE PER POI ESSERE IMPLEMENTATE

void dithering(int sx, int sy, int w, int h, int percent, int size); // funzione per la gestione delle tonalià di grigio dei quadrati
void save_json(AsyncWebServerRequest *richiesta, JsonVariant &json);
void startup();                        // funzione di sturtup
void access_point();                   // funzione per la comunicazione di accesss point
void tabella();                        // funzione per il disegno della tabella principale
void reboot_page();                    // funzione per il disegno della pagina di salvataggio e reboot
void error_page(String codice_errore); // funzione per il disegno della pagina di errore con codice errore
void not_school(String frase);         // funzione per il disegno della pagina dove avvisiamoche non c'è scuola
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

const String version = "v2.2.0.1 x32";

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
const char *aula = "";
String aula_id = "";

const unsigned long delay_time = 300000; // Intervallo di aggiornamento richiesta e display -> 5 minuti

String getData, Link, file_config;

HTTPClient http;

void setup()
{

  // parte iniziale per il display e la seriale
  Serial.begin(115200);
  Serial.println();
  Serial.println("SOMMM STARTUP");
  delay(100);
  display.init(115200);

  SPI.end(); // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  //SPI: void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
  SPI.begin(13, 12, 14, 15); // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)

  startup();
  // Monto il mio SPIFFS File System

  if (!SPIFFS.begin())
  {
    Serial.println("File system non montato ");
    error_page("Errore caricamento File System");
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
    error_page("Errore lettura JSON configurazione");
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
  net_pswd = jsonRead["net_pswd"];
  api_url = jsonRead["api_url"];
  aula = jsonRead["aula"];
  aula_id = String(aula); // Per API raggiungibile a /info
  
  // salvo l'oggetto static_config in una variabile 
  JsonObject static_config = jsonRead["net_static"].as<JsonObject>();
  // solo se viene richiesto l'ip statico processo i dati
  if (!static_config.isNull()) {
    // matrice contenente nell'ordine indirizzo ip, subnet mask, default gateway e dns
    uint8_t settings[4][4];
    
    int row=0;
    // per ogni oggetto/array contenuto in net_static
    for(JsonPair array: static_config){
      if(row>=4) break;
      int column=0;
      // per ogni elemento dell'array
      for(JsonVariant settingN: array.value().as<JsonArray>()){
        if(column>=4) break;
        // salvo l'intero nella matrice
        settings[row][column] = settingN.as<int>();
        column++;
      }
      row++;
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

    AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/save", save_json);
    server.addHandler(handler);

    server.serveStatic("/img", SPIFFS, "/img");
    server.serveStatic("/css", SPIFFS, "/css");
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.serveStatic("/error_log", SPIFFS, "/log.txt");
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
    access_point();

    server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request) {
      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", aula_id);
      response->addHeader("Access-Control-Allow-Origin", "*");
      request->send(response);
    });

    AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/save", save_json);
    server.addHandler(handler);

    server.serveStatic("/img", SPIFFS, "/img");
    server.serveStatic("/css", SPIFFS, "/css");
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.serveStatic("/error_log", SPIFFS, "/log.txt");
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

void dithering(int sx, int sy, int w, int h, int percent, int size)
{
  switch (percent)
  {
  // 75% (DARK GREY)
  case (75):

    for (int y = sy; y < sy + h; y++)
    {
      for (int x = sx; x < sx + w; x++)
      {
        display.fillRect(x, y, size, size, (y % 2 == 0) ? ((x % 2 == 0) ? GxEPD_WHITE : GxEPD_BLACK) : GxEPD_BLACK);
      }
    }
    break;

  // 50% (MIDDLE GREY)
  case (50):

    for (int y = sy; y < sy + h; y++)
    {
      for (int x = sx; x < sx + w; x++)
      {
        display.fillRect(x, y, size, size, (y % 2 == 0) ? ((x % 2 == 0) ? GxEPD_WHITE : GxEPD_BLACK) : ((x % 2 == 0) ? GxEPD_BLACK : GxEPD_WHITE));
      }
    }
    break;

    // 25% (DARK GREY)
  case (25):

    for (int y = sy; y < sy + h; y++)
    {
      for (int x = sx; x < sx + w; x++)
      {
        display.fillRect(x, y, size, size, (y % 2 == 0) ? GxEPD_WHITE : ((x % 2 == 0) ? GxEPD_BLACK : GxEPD_WHITE));
      }
    }
    break;
  }
}

void not_school(String frase)
{
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeSans18pt7b);
    display.setTextColor(GxEPD_BLACK);

    // LOGO SMALLL IN 3D
    display.drawBitmap(468, 5, gImage_s_shadow, 163, 45, GxEPD_BLACK); // shadow
    display.drawBitmap(468, 5, gImage_s_text, 163, 45, GxEPD_WHITE);   // text

    display.setCursor(55, 135);
    display.println(frase);
    display.setFont(&FreeSans12pt7b);
    display.setCursor(55, 170);
    display.println("Il team SOMMM vi augura una buona giornata!");

    display.setFont(&FreeSans9pt7b);

    display.setCursor(55, 200);
    display.println("developed by V. Annunziata, R. Bussola, F. Cucino ");

    display.drawBitmap(211, 277, gImage_dev, 224, 107, GxEPD_BLACK);

  } while (display.nextPage());
}

/**
 * ---------------------------------------------------------------------------------------------
 *  Funzione che gestisce la schermata di accensione del SOMMM
 * 
 */
void startup()
{
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();
  do
  {
    if (display.epd2.hasColor)
    {
      display.fillScreen(GxEPD_RED);
    }
    else
    {
      display.fillScreen(GxEPD_WHITE);
      dithering(0, 0, 640, 384, 25, 1);
    }

    // LOGO IN 3D
    display.drawBitmap(145, 144, gImage_sommm_shadow, 350, 95, GxEPD_BLACK); //shadow
    display.drawBitmap(145, 144, gImage_sommm_text, 350, 95, GxEPD_WHITE);   //text

    display.setFont(&FreeSans12pt7b);
    display.setCursor(142, 297);
    display.setTextColor(GxEPD_BLACK);
    display.println("The new way to manage your time");

    display.setCursor(10, 25);
    display.println(version);

    //------shadow
    display.setCursor(140, 295);
    display.setTextColor(GxEPD_WHITE);
    display.println("The new way to manage your time");

  } while (display.nextPage());
}

/**
 * ---------------------------------------------------------------------------------------------
 *  Funzione per la comunicazione dell'access_point
 * 
 */
void access_point()
{
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();
  do
  {
    if (display.epd2.hasColor)
    {
      display.fillScreen(GxEPD_RED);
    }
    else
    {
      display.fillScreen(GxEPD_WHITE);
      dithering(0, 0, 640, 384, 25, 1);
    }

    // LOGO SMALLL IN 3D
    display.drawBitmap(468, 10, gImage_s_shadow, 163, 45, GxEPD_BLACK); // shadow
    display.drawBitmap(468, 10, gImage_s_text, 163, 45, GxEPD_WHITE);   // text

    // CHROME TAB (fatta di primitive; paurissima)

    dithering(175, 295, 145, 50, 50, 1);
    display.fillRect(0, 324, 640, 60, GxEPD_BLACK);         // base della scheda
    display.fillRoundRect(0, 285, 175, 60, 5, GxEPD_BLACK); // indicatore tab principlae
    display.fillRoundRect(25, 340, 450, 30, 100, GxEPD_WHITE);

    display.setFont(&FreeSans12pt7b);
    display.setCursor(35, 313);
    display.setTextColor(GxEPD_WHITE);
    display.print("SOMMM");

    display.setCursor(35, 363);
    display.setTextColor(GxEPD_BLACK);
    display.print("192.168.4.1");

    // Scritta Guida

    // Titolo

    display.setFont(&FreeSans18pt7b);
    display.setCursor(15, 110);
    display.setTextColor(GxEPD_BLACK);
    display.print("Configurazione");

    display.setFont(&FreeSans12pt7b);
    display.setCursor(15, 150);

    display.epd2.hasColor ? display.setTextColor(GxEPD_WHITE) : display.setTextColor(GxEPD_BLACK);

    display.print("Connettersi alla rete \"" + random_id + "\" e aprire il browser.");
    display.setCursor(15, 175);
    display.print("Digitare 192.168.4.1 e compilare i vari campi.");
    display.setCursor(15, 200);
    display.print("Premere Salva e aspettare la conferma dal device;");
    display.setCursor(15, 225);
    display.print("una volta ricevuta la conferma riavviare il sistema.");

  } while (display.nextPage());
}

/**
 * -----------------------------------------------------------------------------------------
 *    Funzione che gestisce la tabella orario del SOMMM
 */
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
    error_page("Errore di connessione, verifica la rete");
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

  if (oggi.size() == 0) {
    not_school("Oggi non c'e` scuola, buon riposo ;P");
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

  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();

  do
  {
    display.fillScreen(GxEPD_WHITE);

    // ---------------------------------------------------------------------
    //                    LATO DESTRO DEL DISPLAY
    //----------------------------------------------------------------------

    display.epd2.hasColor ? display.fillRect(335, 0, 305, 60, GxEPD_RED) : dithering(335, 0, 305, 60, 50, 1);

    // LOGO SMALLL IN 3D
    display.drawBitmap(468, 5, gImage_s_shadow, 163, 45, GxEPD_BLACK); // shadow
    display.drawBitmap(468, 5, gImage_s_text, 163, 45, GxEPD_WHITE);   // text

    // Scrivo la stanza

    display.setFont(&FreeSans18pt7b);
    display.setTextColor(GxEPD_WHITE);

    display.setCursor(363, 42);
    display.println(stanza);

    // Disegno i separatori

    display.fillRoundRect(355, 115, 280, 2, 10, GxEPD_BLACK);
    display.fillRoundRect(355, 170, 280, 2, 10, GxEPD_BLACK);
    display.fillRoundRect(355, 225, 280, 2, 10, GxEPD_BLACK);
    display.fillRoundRect(355, 280, 280, 2, 10, GxEPD_BLACK);
    display.fillRoundRect(355, 335, 280, 2, 10, GxEPD_BLACK);

    int pos_y[6] = {100, 153, 205, 260, 315, 368};
    display.setTextColor(GxEPD_BLACK);

    if (oraAttuale != 0 && oraAttuale < 5)
    { // mostro le prime 6 ore

      for (int j = 0; j < 6; j++)
      {
        display.setFont(&FreeSans9pt7b);

        display.setCursor(342, 90 + (53 * j) + j);
        display.println(j + 1);

        if (j + 1 == oraAttuale)
        {
          display.epd2.hasColor ? display.fillRect(340, pos_y[j], 15, 5, GxEPD_RED) : display.fillRect(340, pos_y[j], 15, 5, GxEPD_BLACK);
        }
        else
        {
          display.drawRect(340, pos_y[j], 15, 5, GxEPD_BLACK);
        }

        display.setFont(&FreeSans9pt7b);

        display.setCursor(363, 110 + (53 * j) + j);
        display.println(today_matrix[j][1]); // primo professore

        display.setCursor(363, 85 + (53 * j) + j);
        display.println(today_matrix[j][2]); // secondo professore

        display.setFont(&FreeSans9pt7b);

        display.setCursor(510, 110 + (53 * j) + j);
        display.println(today_matrix[j][3]); // Materia

        display.setFont(&FreeSans18pt7b);

        display.setCursor(566, 110 + (53 * j) + j);
        display.println(today_matrix[j][4]); // Classe
      }
    }
    if (oraAttuale != 0 && oraAttuale >= 5)
    { // mostro le ultime 6 ore

      for (int j = 4; j < 10; j++)
      {

        display.setFont(&FreeSans9pt7b);

        display.setCursor(342, 90 + (53 * (j - 4)) + j);
        if (j + 1 == 10)
        {
          display.println('X');
        }
        else
        {
          display.println((j) + 1);
        }

        if (j + 1 == oraAttuale)
        {
          display.fillRect(340, pos_y[j - 4], 15, 5, GxEPD_BLACK);
        }
        else
        {
          display.drawRect(340, pos_y[j - 4], 15, 5, GxEPD_BLACK);
        }

        display.setFont(&FreeSans9pt7b);

        display.setCursor(363, 110 + (53 * (j - 4)) + j - 4);
        display.println(today_matrix[j][1]); // primo professore

        display.setCursor(363, 85 + (53 * (j - 4)) + j - 4);
        display.println(today_matrix[j][2]); // secondo professore

        display.setFont(&FreeSans9pt7b);

        display.setCursor(510, 110 + (53 * (j - 4)) + j - 4);
        display.println(today_matrix[j][3]); // Materia

        display.setFont(&FreeSans18pt7b);

        display.setCursor(566, 110 + (53 * (j - 4)) + j - 4);
        display.println(today_matrix[j][4]); // Classe
      }
    }
    else if (oraAttuale == 0 && httpCode != -1)
    { // Giornata terminata

      not_school("La giornata scolastica e` terminata.");
      return;
    }

    // ---------------------------------------------------------------------
    //                    LATO SINISTRO DEL DISPLAY
    // ----------------------------------------------------------------------

    //display.setTextColor(display.epd2.hasColor ? GxEPD_WHITE : GxEPD_BLACK);

    dithering(0, 0, 335, 331, 75, 1); // SFONDO GRIGIO 75%
    display.drawFastVLine(335, 0, 331, GxEPD_BLACK);
    display.drawFastVLine(335, 332, 53, GxEPD_BLACK);

    // GRIGLIA GIORNI

    display.setFont(&FreeSans12pt7b);
    display.setTextColor(GxEPD_WHITE);

    // Indicatore di ore dei vari giorni

    for (int i = 0; i < 6; i++)
    {
      display.setCursor(7, 52 + (50 * i));
      display.println(i + 1);
    }

    // Nome dei giorni
    display.setFont(&FreeSans9pt7b);
    String gior_name[6] = {"LUN", "MAR", "MER", "GIO", "VEN", "SAB"};

    for (int i = 0; i < 6; i++)
    {
      display.setCursor(33 + ((48 * i) + i * 2), 18);
      display.println(gior_name[i]);
    }

    for (int j = 0; j < 6; j++)
    {
      for (int i = 0; i < 6; i++)
      {
        display.fillRoundRect(30 + (50 * j), 25 + (50 * i), 47, 47, 5, GxEPD_BLACK);
        display.fillRoundRect(31 + (50 * j), 26 + (50 * i), 45, 45, 5, GxEPD_WHITE);
      }
    }

    if (giorno_settimana != -1)
    {
      for (int i = 0; i < 6; i++)
      {

        display.fillRoundRect(30 + (50 * giorno_settimana), 25 + (50 * i), 47, 47, 5, GxEPD_WHITE);
        display.fillRoundRect(31 + (50 * giorno_settimana), 26 + (50 * i), 45, 45, 5, GxEPD_BLACK);
      };
    }
    display.setFont(&FreeSans9pt7b);

    for (int i = 0; i < 6; i++)
    {
      for (int j = 0; j < 6; j++)
      {
        display.setCursor(35 + (50 * j), 55 + (50 * i));
        if (giorno_settimana == j && giorno_settimana != -1)
        {
          display.setTextColor(GxEPD_WHITE);
        }
        else
        {
          display.setTextColor(GxEPD_BLACK);
        }
        display.println(settimana_matrix[j][i]); // Settimana giorno per giorno
      }
    }

    display.setTextColor(GxEPD_BLACK);

    // Parte sotto del giorno
    display.setFont(&FreeSans12pt7b);

    display.setCursor(8, 365);
    display.println(giorno); // info giorno

  } while (display.nextPage());
}

void reboot_page()
{

  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();
  do
  {
    if (display.epd2.hasColor)
    {
      display.fillScreen(GxEPD_RED);
    }
    else
    {
      display.fillScreen(GxEPD_WHITE);
      dithering(0, 0, 640, 384, 25, 1);
    }

    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeSans12pt7b);
    display.setCursor(50, 180);
    display.println("Attendere la conferma dalla pagina web;");
    display.setCursor(50, 210);
    display.println("successivamente riavviare il dispositivo per");
    display.setCursor(50, 240);
    display.println("caricare le nuove impostazioni.");

    // LOGO IN 3D
    display.drawBitmap(50, 50, gImage_sommm_shadow, 350, 95, GxEPD_BLACK); //shadow
    display.drawBitmap(50, 50, gImage_sommm_text, 350, 95, GxEPD_WHITE);   //text

    display.fillRoundRect(550, 62, 65, 260, 10, GxEPD_WHITE);
    display.drawBitmap(550, 62, gImage_reboot, 65, 260, GxEPD_BLACK);

  } while (display.nextPage());
}

void error_page(String codice_errore)
{
  display.setRotation(0);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);

    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeSans12pt7b);

    dithering(0, 0, 640, 384, 25, 1);
    display.drawChar(140, 150, 'X', GxEPD_BLACK, GxEPD_WHITE, 4);
    display.drawChar(440, 150, 'X', GxEPD_BLACK, GxEPD_WHITE, 4);

    display.setCursor(80, 250);
    display.println("Ops! Sembra che qualcosa sia andato storto!");
    display.setCursor(100, 285);
    display.println(codice_errore);
    log_error(codice_errore + String(", WiFi status: ") + String(wifi_stat(WiFi.status())));

  } while (display.nextPage());
}

void save_json(AsyncWebServerRequest *richiesta, JsonVariant &json) {
  if (!SPIFFS.begin()) { // controllo di aver accesso al filesystem
    // Se viene visualizzato c'è un problema al filesystem
    richiesta->send(500, "text/plain", "Impossibile leggere la configurazione attualmente memorizzata"); // messaggio di callback per client web

    Serial.println("SPIFFS2 Mount failed");
    error_page("Errore caricamento File System");
    return;
  } else Serial.println("SPIFFS2 Mount succesfull");

  canRequest = false;

  if (!richiesta->authenticate(www_username, www_password))
    return richiesta->requestAuthentication();

  File save = SPIFFS.open("/config.json", "w");

  delay(200);
  serializeJson(json, save);   // salvo la nuova configurazione
  serializeJson(json, Serial); // stampo la nuova configurazione

  save.close();
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
