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
#include <ArduinoJson.h>

// Font di varia grandezza per il display
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

//#define RED //commentare o decommentare a seconda se il display supporta un terzo colore

#if defined(RED)

GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT / 4> display(GxEPD2_750c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); //display a colori
#else

GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT / 2> display(GxEPD2_750(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); //display in grayscale
#endif

// FUNZIONI DEFINITE INIZIALEMTE PER POI ESSERE IMPLEMENTATE

void update_display(int page_mode, String string_1, String string_2); // Funzione di gestione degli eventi

void dithering(); //funzione per la gestione delle tonalià di grigio dei quadrati

void startup();     //funzione di sturtup
void acces_point(); //funzione per la comunicazione di access point
void tabella();     //funzione per il disegno della tabella principale

// DEFINIZIONE DELLE VARIABILI GLOBALI NECESSARIE AL SISTEMA

String mex_1 = ""; // riga comunicazione 1
String mex_2 = ""; // riga comunicazione 2

void setup()
{
  // parte iniziale per il display e la seriale

  Serial.begin(115200);
  Serial.println();
  Serial.println("SOMMM STARTUP");
  delay(100);
  display.init(115200);
  update_display(0, "", "");
}

void loop()
{
}

/**
 * 
 *     FUNZIONI E GESTIONE DEL DISPLAY 
 **/

void update_display(int page_mode, String string_1, String string_2)
{
  //startup();
  acces_point();
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
 **/

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
 **/

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
    display.drawBitmap(468, 10, gImage_s_shadow, 163, 45, GxEPD_BLACK); //shadow
    display.drawBitmap(468, 10, gImage_s_text, 163, 45, GxEPD_WHITE);   //text

    //CHROME TAB (fatta di primitive; paurissima)

    dithering(175, 295, 145, 50, 50, 1);
    display.fillRect(0, 324, 640, 60, GxEPD_BLACK);         //base della scheda
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

    //Titolo

    display.setFont(&FreeSans18pt7b);
    display.setCursor(15, 110);
    display.setTextColor(GxEPD_BLACK);
    display.print("Configurazione SOMMM");

    display.setFont(&FreeSans12pt7b);
    display.setCursor(15, 150);

    display.epd2.hasColor ? display.setTextColor(GxEPD_WHITE) : display.setTextColor(GxEPD_BLACK);

    display.print("Connetteti alla rete \"SOMMM\" e apri il browser");
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
 * 
 **/

void tabella()
{

  display.setRotation(0);
  display.setFont(&FreeSans18pt7b);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);

    // ---------------------------------------------------------------------
    //                    LATO DESTRO DEL DISPLAY
    //----------------------------------------------------------------------

    display.fillRect(335, 0, 305, 60, GxEPD_BLACK);

    display.epd2.hasColor ? display.fillRect(335, 0, 305, 60, GxEPD_RED) : display.fillRect(335, 0, 305, 60, GxEPD_BLACK);

    //display.drawBitmap(500, 3, gImage_logo, 125, 55, GxEPD_WHITE);

    // Disegno i separatori

    display.fillRect(355, 115, 280, 2, GxEPD_BLACK);
    display.fillRect(355, 170, 280, 2, GxEPD_BLACK);
    display.fillRect(355, 225, 280, 2, GxEPD_BLACK);
    display.fillRect(355, 280, 280, 2, GxEPD_BLACK);
    display.fillRect(355, 335, 280, 2, GxEPD_BLACK);

    // ---------------------------------------------------------------------
    //                    LATO SINISTRO DEL DISPLAY
    //----------------------------------------------------------------------

    //display.setTextColor(display.epd2.hasColor ? GxEPD_WHITE : GxEPD_BLACK);

    dithering(0, 0, 335, 331, 50, 1); // SFONDO GRIGIO 50%
    display.drawFastVLine(335, 0, 331, GxEPD_BLACK);
    display.drawFastVLine(335, 331, 53, GxEPD_BLACK);

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
      display.setCursor(31 + ((48 * i) + i * 2), 18);
      display.println(gior_name[i]);
    }

    for (int j = 0; j < 6; j++)
    {
      for (int i = 0; i < 6; i++)
      {

        display.fillRoundRect(30 + (50 * j), 25 + (50 * i), 47, 47, 5, GxEPD_BLACK);
        display.fillRoundRect(29 + (50 * j), 24 + (50 * i), 46, 46, 5, GxEPD_WHITE);

        //display.fillRect(30 + (50 * j), 25 + (50 * i), 47, 47, GxEPD_BLACK);
        //display.fillRect(29 + (50 * j), 24 + (50 * i), 46, 46, GxEPD_WHITE);
      }
    }

  } while (display.nextPage());
}