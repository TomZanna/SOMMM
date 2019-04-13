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
 *            Project : SOMMM
 *           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                                                              
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
                                                                                                                             
 * 
 */

#include <Arduino.h>
#include <images.h>

#define ENABLE_GxEPD2_GFX 1
#include <GxEPD2_3C.h>
#include <GxEPD2_BW.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include "FS.h"

// Font di varia grandezza per il display
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

//#define RED // commentare o decommentare a seconda se il display supporta un terzo colore

#if defined(RED)
GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT / 4> display(GxEPD2_750c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); //display a colori
#else
GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT / 2> display(GxEPD2_750(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); //display in grayscale
#endif

ESP8266WebServer server(1518); //settaggio server sulla porta 1518

// FUNZIONI DEFINITE INIZIALMENTE PER POI ESSERE IMPLEMENTATE

void dithering(int sx, int sy, int w, int h, int percent, int size); // funzione per la gestione delle tonalià di grigio dei quadrati
void save_json();
void startup();     // funzione di sturtup
void acces_point(); // funzione per la comunicazione di access point
void tabella();     // funzione per il disegno della tabella principale

// DEFINIZIONE DELLE VARIABILI GLOBALI NECESSARIE AL SISTEMA

bool request = 0;
const char *payload = ""; // payload come variabile globale
int oraAttuale = 1;       // sisema di switch per le giornate con + di 6 ore
int httpCode = 0;

const char *net_ssid = "";
const char *net_pswd = "";
const char *api_url = "";
const char *aula = "";
String aula_id = "";

int delay_time = 600000; // Intervallo di aggiornamento richiesta e display
bool static_config = 0;  // static or DHCP

int ip[4], dns[4], default_gw[4], subnet_m[4];

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
  startup();

  // Monto il mio SPIFFS File System

  if (!SPIFFS.begin())
  {
    Serial.println("File system non montato ");
    //update_display(1, "Errore File System", ":X");
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
    Serial.print("deserializeJson() line142 failed: ");
    Serial.println(errorRead.c_str());
    Serial.println("Impossibile leggere la configurazione");
    //update_display(1, "Errore di lettura json", ":X");
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

  static_config = jsonRead["net_static"];

  ip[0] = jsonRead["net_ip_0"];
  ip[1] = jsonRead["net_ip_1"];
  ip[2] = jsonRead["net_ip_2"];
  ip[3] = jsonRead["net_ip_3"];

  default_gw[0] = jsonRead["net_dfgw_0"];
  default_gw[1] = jsonRead["net_dfgw_1"];
  default_gw[2] = jsonRead["net_dfgw_2"];
  default_gw[3] = jsonRead["net_dfgw_3"];

  subnet_m[0] = jsonRead["net_sm_0"];
  subnet_m[1] = jsonRead["net_sm_1"];
  subnet_m[2] = jsonRead["net_sm_2"];
  subnet_m[3] = jsonRead["net_sm_3"];

  dns[0] = jsonRead["net_dns_0"];
  dns[1] = jsonRead["net_dns_1"];
  dns[2] = jsonRead["net_dns_2"];
  dns[3] = jsonRead["net_dns_3"];

  if (static_config)
  {
    Serial.println("Configurazione statica....");
    IPAddress ip_addr(ip[0], ip[1], ip[2], ip[3]);
    IPAddress dns_addr(dns[0], dns[1], dns[2], dns[3]);
    IPAddress gw_addr(default_gw[0], default_gw[1], default_gw[2], default_gw[3]);
    IPAddress sm_addr(subnet_m[0], subnet_m[1], subnet_m[2], subnet_m[3]);

    Serial.println(ip_addr);
    Serial.println(gw_addr);
    Serial.println(sm_addr);
    Serial.println(dns_addr);

    if (!WiFi.config(ip_addr, gw_addr, sm_addr, dns_addr))
    { // Configurazione statica del web-server in caso di Client
      Serial.println("Errore configurazione statica");
    }
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(net_ssid, net_pswd); // Provo a eseguire una connessione con le credenziali che ho

  Serial.print("Connecting");

  long start_c = millis();
  long counter = 0;
  long soglia = 300000; // soglia di controllo per passare il AP (default 25s)

  while (WiFi.status() != WL_CONNECTED) // Wait for connection
  {
    counter += millis() - start_c;
    Serial.println(counter);
    if (counter < soglia)
    {
      delay(1000);
      Serial.print(".");
    }
    else
    {
      break;
    }
  }
  Serial.println("");
  Serial.println(WiFi.macAddress());

  if (WiFi.status() == WL_CONNECTED)
  {
    // Connessione stabilita
    Serial.println(WiFi.localIP().toString().c_str());

    // Setto http sull'indirizzo del mio server

    String http_address = String(api_url) + "?stanza=" + String(aula); // Creo l'url per indirizzo API

    Serial.print("Richiesta settata su: "); // Stampo l'indirizzo
    Serial.println(http_address);

    request = 1; // Abilito l'invio del dato

    http.begin(http_address); // configuro e avvio http sul'url precedentemente dichiarato

    // Dichiaro la struttura del mio filesystem in modo da caricare i file archiviati con SPIFFS
    server.on("/info", []() {
      return server.send(200, "text/plain", aula_id);
    });
    server.on("/save", save_json);
    server.serveStatic("/img", SPIFFS, "/img");
    server.serveStatic("/css", SPIFFS, "/css");
    server.serveStatic("/", SPIFFS, "/index.html");
    server.begin(); //Faccio partire il server
    delay(5000);
    tabella();
    //update_display(2, "", ""); // Mostro l'avvenuto successo della connesione su display e do informazioni utili all'utente
  }
  else
  {
    // Problemi di connessione (probabilmente rete non raggiungibile e/o settato), avvio Access Point
    WiFi.disconnect(true); // Disconnetto la wifi
    WiFi.mode(WIFI_AP);    // Wifi Mode Access-Point

    WiFi.softAP("SOMMM", "laPasswordQui"); // dichiaro i parametri del mio access point

    Serial.println("Access Point Mode");
    Serial.println(WiFi.softAPIP());
    //update_display(1, "AP SOMMM", "192.168.4.1"); // 192.168.4.1 + porta default
    acces_point();

    server.on("/info", []() {
      return server.send(200, "text/plain", aula_id);
    });
    server.on("/save", save_json);
    server.serveStatic("/img", SPIFFS, "/img");
    server.serveStatic("/css", SPIFFS, "/css");
    server.serveStatic("/", SPIFFS, "/index.html");
    server.begin(); // Faccio partire il server
  }
}

long time_start = millis();

void loop()
{
  server.handleClient();

  if (request)
  {
    if (delay_time >= 1000)
    { // verifica se l'update_s è almeno maggiore di 1s
      if ((millis() - time_start) >= delay_time)
      {
        // mando la richiesta
        Serial.println("--------------------");
        tabella();
        time_start = millis(); // azzerro il contatore
      }
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
    //------shadow
    display.setCursor(140, 295);
    display.setTextColor(GxEPD_WHITE);
    display.println("The new way to manage your time");

  } while (display.nextPage());
}

/**
 * ---------------------------------------------------------------------------------------------
 *  Funzione per la comunicazione dell'acces_point
 * 
 */
void acces_point()
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
    display.print("Configurazione SOMMM");

    display.setFont(&FreeSans12pt7b);
    display.setCursor(15, 150);

    display.epd2.hasColor ? display.setTextColor(GxEPD_WHITE) : display.setTextColor(GxEPD_BLACK);

    display.print("Connettersi alla rete \"SOMMM\" e aprire il browser");
    display.setCursor(15, 175);
    display.print("Digitare 192:168.4.1 e compilare i vari campi");
    display.setCursor(15, 200);
    display.print("Premere Salva e aspettare la conferma dal device");
    display.setCursor(15, 225);
    display.print("Una volta ricevuta la conferma riavviare il sistema");

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

  const size_t bufferSize = 7 * JSON_ARRAY_SIZE(10) + 10 * JSON_OBJECT_SIZE(5) + 2 * JSON_OBJECT_SIZE(6) + 1050;
  DynamicJsonDocument doc(bufferSize);

  DeserializationError error = deserializeJson(doc, payload);
  if (error) // Se errore a elaborare json
  {
    Serial.print("deserializeJson() line79 failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Dati header

  const char *stanza = doc["stanza"];            // "L145"
  const char *giorno = doc["giorno"];            // "Venerdi', 23 Novembre 2018"
  int giorno_settimana = doc["giornoSettimana"]; // 5
  giorno_settimana += -1;
  int oraAttuale = doc["oraAttuale"]; // 3

  if (httpCode == -1)
  {
    giorno = "Errore di connessione x(";
  }

  // ################################################################################################################
  // CREAZIONE DELL'OGGETTO CONTENENTE I DATI RIGUARDANTI A "OGGI"

  JsonArray oggi = doc["oggi"]; // Oggetto "oggi" contenente tutte le informazioni

  JsonObject prima = oggi[0];
  JsonObject seconda = oggi[1];
  JsonObject terza = oggi[2];
  JsonObject quarta = oggi[3];
  JsonObject quinta = oggi[4];
  JsonObject sesta = oggi[5];
  JsonObject settima = oggi[6];
  JsonObject ottava = oggi[7];
  JsonObject nona = oggi[8];
  JsonObject decima = oggi[9];

  const char *today_matrix[10][5] = {{prima["ora"], prima["prof1"], prima["prof2"], prima["mat"], prima["res"]},
                                     {seconda["ora"], seconda["prof1"], seconda["prof2"], seconda["mat"], seconda["res"]},
                                     {terza["ora"], terza["prof1"], terza["prof2"], terza["mat"], terza["res"]},
                                     {quarta["ora"], quarta["prof1"], quarta["prof2"], quarta["mat"], quarta["res"]},
                                     {quinta["ora"], quinta["prof1"], quinta["prof2"], quinta["mat"], quinta["res"]},
                                     {sesta["ora"], sesta["prof1"], sesta["prof2"], sesta["mat"], sesta["res"]},
                                     {settima["ora"], settima["prof1"], settima["prof2"], settima["mat"], settima["res"]},
                                     {ottava["ora"], ottava["prof1"], ottava["prof2"], ottava["mat"], ottava["res"]},
                                     {nona["ora"], nona["prof1"], nona["prof2"], nona["mat"], nona["res"]},
                                     {decima["ora"], decima["prof1"], decima["prof2"], decima["mat"], decima["res"]}};

  // ################################################################################################################
  // CREAZIONE DELL'OGGETTO CONTENENTE I DATI RIGUARDANTI A "SETTIMANA"

  JsonObject settimana = doc["settimana"]; // Oggetto "settima" contenente tutte le informazioni

  JsonObject settimana_1 = settimana["1"];
  JsonObject settimana_2 = settimana["2"];
  JsonObject settimana_3 = settimana["3"];
  JsonObject settimana_4 = settimana["4"];
  JsonObject settimana_5 = settimana["5"];
  JsonObject settimana_6 = settimana["6"];

  const char *settimana_matrix[6][6] = {{settimana_1["1"], settimana_1["2"], settimana_1["3"], settimana_1["4"], settimana_1["5"], settimana_1["6"]},
                                        {settimana_2["1"], settimana_2["2"], settimana_2["3"], settimana_2["4"], settimana_2["5"], settimana_2["6"]},
                                        {settimana_3["1"], settimana_3["2"], settimana_3["3"], settimana_3["4"], settimana_3["5"], settimana_3["6"]},
                                        {settimana_4["1"], settimana_4["2"], settimana_4["3"], settimana_4["4"], settimana_4["5"], settimana_4["6"]},
                                        {settimana_5["1"], settimana_5["2"], settimana_5["3"], settimana_5["4"], settimana_5["5"], settimana_5["6"]},
                                        {settimana_6["1"], settimana_6["2"], settimana_6["3"], settimana_6["4"], settimana_6["5"], settimana_6["6"]}};

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

    display.setFont(&FreeSans18pt7b);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(363, 42);
    display.println("L142");

    // LOGO SMALLL IN 3D
    display.drawBitmap(468, 5, gImage_s_shadow, 163, 45, GxEPD_BLACK); // shadow
    display.drawBitmap(468, 5, gImage_s_text, 163, 45, GxEPD_WHITE);   // text

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
          display.fillRect(340, pos_y[j], 15, 5, GxEPD_BLACK);
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

        display.setCursor(522, 110 + (53 * j) + j);
        display.println(today_matrix[j][3]); // Materia

        display.setFont(&FreeSans18pt7b);

        display.setCursor(573, 110 + (53 * j) + j);
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

        display.setCursor(522, 110 + (53 * (j - 4)) + j - 4);
        display.println(today_matrix[j][3]); // Materia

        display.setFont(&FreeSans18pt7b);

        display.setCursor(573, 110 + (53 * (j - 4)) + j - 4);
        display.println(today_matrix[j][4]); // Classe
      }
    }
    else if (oraAttuale == 0 && httpCode != -1)
    { // Giornata terminata

      display.setFont(&FreeSans9pt7b);

      display.setCursor(363, 82);
      display.println("Giornata scolastica");

      display.setCursor(363, 107);
      display.println("terminata");
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

    String num_ore[6] = {"1", "2", "3", "4", "5", "6"};

    for (int i = 0; i < 6; i++)
    {
      display.setCursor(7, 52 + (50 * i));
      display.println(num_ore[i]);
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

    for (int i = 0; i < 6; i++)
    {

      display.fillRoundRect(30 + (50 * giorno_settimana), 25 + (50 * i), 47, 47, 5, GxEPD_WHITE);
      display.fillRoundRect(31 + (50 * giorno_settimana), 26 + (50 * i), 45, 45, 5, GxEPD_BLACK);
    };

    display.setFont(&FreeSans9pt7b);

    for (int i = 0; i < 6; i++)
    {
      for (int j = 0; j < 6; j++)
      {
        display.setCursor(35 + (50 * j), 55 + (50 * i));
        if (giorno_settimana == j)
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

void save_json()
{
  if (!SPIFFS.begin()) // controllo di aver accesso al filesystem
  {
    // Se viene visualizzato c'è un problema al filesystem
    server.send(500, "text/plain", "Impossibile leggere la configurazione attualmente memorizzata"); // messaggio di callback per client web
    Serial.println("SPIFFS2 Mount failed");
    return;
  }
  else
  { // File system correttamente caricato
    Serial.println("SPIFFS2 Mount succesfull");
  }

  File file_conf_saved = SPIFFS.open("/config.json", "r"); // Apro il file in modalità lettura

  DynamicJsonDocument json(1024); // creo secondo buffer
  String conf_read_file = file_conf_saved.readStringUntil('\n');

  DeserializationError errorConf = deserializeJson(json, conf_read_file);
  if (errorConf)
  {
    server.send(500, "text/plain", "Impossibile leggere la configurazione attualmente memorizzata"); // messaggio di callback per client web
    Serial.print("deserializeJson() line327 failed: ");
    Serial.println(errorConf.c_str());
    Serial.println("Impossibile leggere la configurazione");
    return;
  }
  else
  {
    Serial.println("Configurazione attuale caricata correttamente");
    serializeJson(json, Serial);
    Serial.println("");
  }

  // #######################################################
  // controllo e salvataggio dei dati in caso di cambiamento
  // #######################################################

  if (server.arg("net_ssid") != "")
  { // ssid
    json["net_ssid"] = server.arg("net_ssid");
  }

  if (server.arg("net_pswd") != "")
  { // password
    json["net_pswd"] = server.arg("net_pswd");
  }

  if (server.arg("api_url") != "")
  { // codice dispositivo
    json["api_url"] = server.arg("api_url");
  }

  if (server.arg("aula") != "")
  { // url server con api
    json["aula"] = server.arg("aula");
  }

  if (server.arg("net_static") != "")
  { // 1-0 abilita configurazione statica
    json["net_static"] = server.arg("net_static");
  }

  if (server.arg("net_ip_0") != "")
  { // ip[0]
    json["net_ip_0"] = server.arg("net_ip_0");
  }

  if (server.arg("net_ip_1") != "")
  { // ip[1]
    json["net_ip_1"] = server.arg("net_ip_1");
  }

  if (server.arg("net_ip_2") != "")
  { // ip[2]
    json["net_ip_2"] = server.arg("net_ip_2");
  }

  if (server.arg("net_ip_3") != "")
  { // ip[3]
    json["net_ip_3"] = server.arg("net_ip_3");
  }

  if (server.arg("net_dns_0") != "")
  { // dns[0]
    json["net_dns_0"] = server.arg("net_dns_0");
  }

  if (server.arg("net_dns_1") != "")
  { // dns[1]
    json["net_dns_1"] = server.arg("net_dns_1");
  }

  if (server.arg("net_dns_2") != "")
  { // dns[2]
    json["net_dns_2"] = server.arg("net_dns_2");
  }

  if (server.arg("net_dns_3") != "")
  { // dns[3]
    json["net_dns_3"] = server.arg("net_dns_3");
  }

  request = 0;

  delay(100); // aspetto che tutto sia correttamente settato e poi scrivo

  /*if (!server.authenticate(www_username, www_password))
  {
    return server.requestAuthentication();
  }*/

  File save = SPIFFS.open("/config.json", "w"); // Apro il file in modalità scrittura

  delay(200);
  serializeJson(json, save);   // salvo la nuova configurazione
  serializeJson(json, Serial); // stampo la nuova configurazione

  server.send(200, "text/plain", "Salvataggio effettuato correttamente. Riavvia SOMMM appena led rosso spento"); // messaggio di callback per client web
  Serial.println("");
  Serial.println("Riavvia il dispositivo appena led rosso spento");
  //update_display(1, "Salvataggio effettuato", "Riavvia SOMM appena led rosso spento"); // Riavvio dispositivo

  // N.B. No reboot lato software per problemi successivi a stack di memoria, riavvio hardware
}