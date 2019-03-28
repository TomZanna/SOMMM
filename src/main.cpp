#include <Arduino.h>
#include <images.h>

#define ENABLE_GxEPD2_GFX 1

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

// Font di varia grandezza per il display
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

#define RED //commentare o decommentare a seconda se il display supporta un terzo colore

#if defined(RED)
GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT / 4> display(GxEPD2_750c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); //display a colori
#else
GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT / 2> display(GxEPD2_750(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16));     //display in grayscale
#endif

// FUNZIONI DEFINITE INIZIALEMTE PER POI ESSERE IMPLEMENTATE

void update_display(int page_mode, String string_1, String string_2); // Funzione di gestione degli eventi

void dithering(); //funzione per la gestione delle tonalià di grigio dei quadrati
void tabella();   //funzione per il disegno della tabella principale

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

void update_display(int page_mode, String string_1, String string_2)
{
  tabella();
}

void dithering(int sx, int sy, int h, int w, int percent, int size)
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
  }
}

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

    //display.drawImage(gImage_logo, 500, 3, 125, 55, false, false, false);
    display.drawBitmap(500, 3, gImage_logo, 125, 55, GxEPD_WHITE);

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

    dithering(0, 0, 331, 335, 50, 2); // SFONDO GRIGIO 50%
    display.drawFastVLine(335,0,331,GxEPD_BLACK);

#if defined(RED)
    display.fillRect(0, 331, 336, 53, GxEPD_RED);
#else
    dithering(0, 331, 53, 335, 75, 2); // SFONDO GRIGIO 75%
    display.drawFastVLine(335,331,53,GxEPD_BLACK);
#endif
    

    // GRIGLIA GIORNI

    display.setFont(&FreeSans12pt7b);
    display.setTextColor(GxEPD_BLACK);

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
        /*
        display.fillRoundRect(30 + (50 * j), 25 + (50 * i), 47, 47, 5, GxEPD_BLACK);
        display.fillRoundRect(28 + (50 * j), 23 + (50 * i), 45, 45, 5, GxEPD_WHITE);*/

        display.fillRect(30 + (50 * j), 25 + (50 * i), 47, 47, GxEPD_BLACK);
        display.fillRect(28 + (50 * j), 23 + (50 * i), 45, 45, GxEPD_WHITE);
      }
    }

  } while (display.nextPage());
}