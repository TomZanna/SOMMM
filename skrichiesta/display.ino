void update_display(int page_mode, String string_1, String string_2)
{
  mex_1 = string_1;
  mex_2 = string_2;

  switch (page_mode)
  {
  case 0:
    ePaper.drawPaged(startup); // Modalità logo
    break;
  case 1:
    ePaper.drawPaged(communication); // Modalità comunicazione/errore
    break;
  case 2:
    int httpCode = http.GET();
    String response = http.getString();
    payload = response.c_str();

    Serial.println(httpCode);
    Serial.println(sizeof(payload));
    Serial.println(payload);

    http.end();

    ePaper.drawPaged(table); // Modalità comunicazione/errore
    break;
  }
}

/**
 * Modalità di startup dove viene visualizzato il logo som e iti g. marconi
 * @ page_mode 0 
 */

void startup()
{
  ePaper.eraseDisplay();
  ePaper.drawBitmap(gImage_marconi, 144, 50, 351, 82, GxEPD_BLACK);
  ePaper.drawBitmap(gImage_logo, 257, 180, 125, 55, GxEPD_BLACK);
}

/**
 * Modalità di comunicazione utilizando le due stringhe globali mex_1 e mex_2
 * @ page_mode 1
 * z
 */

void communication()
{
  ePaper.eraseDisplay();
  ePaper.drawBitmap(gImage_marconi, 144, 50, 351, 82, GxEPD_BLACK);
  ePaper.drawBitmap(gImage_logo, 257, 180, 125, 55, GxEPD_BLACK);

  const GFXfont *f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(100, 330);
  ePaper.println(mex_1);

  ePaper.setCursor(100, 360);
  ePaper.println(mex_2);
}


/**
 * Modalità di visualizzazione dell'orario preso da marconi tt
 * @ page_mode 2
 */

void table()
{

  ePaper.eraseDisplay();
  
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  //Parte di destra

  ePaper.fillRect(350, 0, 290, 60, GxEPD_BLACK);
  ePaper.drawBitmap(gImage_logo, 500, 3, 125, 55, GxEPD_WHITE);
  ePaper.drawFastVLine(350, 0, 330, GxEPD_WHITE);
  ePaper.drawFastVLine(349, 330, 84, GxEPD_BLACK);

  const GFXfont *f = &Roboto_Regular18pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_WHITE);

  ePaper.setCursor(363, 42);
  ePaper.println("L142");


  //Disegno i separatori

  ePaper.fillRect(355, 115, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 170, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 225, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 280, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 335, 280, 2, GxEPD_BLACK);

  // Disegno le informazioni ora per ora

  if(oraAttuale != 0 && oraAttuale < 7){

  //#######################################################################
  // Primo Blocco

  f = &Roboto_Regular10pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(363,82);
  ePaper.println("Merzi Tiziano"); //primo professore

  ePaper.setCursor(363,107);
  ePaper.println("Bileddo Antonino"); // secondoi professore

  f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(522,107);
  ePaper.println("LTPI"); // Materia 

  f = &Roboto_Regular18pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(575,107);
  ePaper.println("5AI"); // Classe


  //#######################################################################
  // Secondo Blocco

  f = &Roboto_Regular10pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(363,137);
  ePaper.println("Merzi Tiziano"); //primo professore

  ePaper.setCursor(363,162);
  ePaper.println("Bileddo Antonino"); // secondoi professore

  f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(522,162);
  ePaper.println("LTPI"); // Materia 

  f = &Roboto_Regular18pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(575,162);
  ePaper.println("5AI"); // Classe

  //#######################################################################
  // Terzo Blocco

  f = &Roboto_Regular10pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(363,192);
  ePaper.println("Merzi Tiziano"); //primo professore

  ePaper.setCursor(363,217);
  ePaper.println("Bileddo Antonino"); // secondoi professore

  f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(522,217);
  ePaper.println("LTPI"); // Materia 

  f = &Roboto_Regular18pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(575,217);
  ePaper.println("5AI"); // Classe
  
  //#######################################################################
  // Quarto Blocco

  f = &Roboto_Regular10pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(363,247);
  ePaper.println("Merzi Tiziano"); //primo professore

  ePaper.setCursor(363,272);
  ePaper.println("Bileddo Antonino"); // secondoi professore

  f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(522,272);
  ePaper.println("LTPI"); // Materia 

  f = &Roboto_Regular18pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(575,272);
  ePaper.println("5AI"); // Classe

  //#######################################################################
  // Quinto Blocco

  f = &Roboto_Regular10pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(363,302);
  ePaper.println("Merzi Tiziano"); //primo professore

  ePaper.setCursor(363,327);
  ePaper.println("Bileddo Antonino"); // secondoi professore

  f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(522,327);
  ePaper.println("LTPI"); // Materia 

  f = &Roboto_Regular18pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(575,327);
  ePaper.println("5AI"); // Classe

  //#######################################################################
  // Sesto Blocco

  f = &Roboto_Regular10pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(363,357);
  ePaper.println("Merzi Tiziano"); //primo professore

  ePaper.setCursor(363,382);
  ePaper.println("Bileddo Antonino"); // secondoi professore

  f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(522,382);
  ePaper.println("LTPI"); // Materia 

  f = &Roboto_Regular18pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_BLACK);

  ePaper.setCursor(575,382);
  ePaper.println("5AI"); // Classe




  }
  



  
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ò
  //Parte di sinistra

  ePaper.fillRect(0, 0, 350, 330, GxEPD_BLACK);

  //Scritte

  f = &Roboto_Regular10pt7b;
  ePaper.setFont(f);
  ePaper.setTextColor(GxEPD_WHITE);

  //Indicatore di ore dei vari giorni

  ePaper.setCursor(8, 52);
  ePaper.println("1");
  ePaper.setCursor(8, 102);
  ePaper.println("2");
  ePaper.setCursor(8, 152);
  ePaper.println("3");
  ePaper.setCursor(8, 202);
  ePaper.println("4");
  ePaper.setCursor(8, 252);
  ePaper.println("5");
  ePaper.setCursor(8, 302);
  ePaper.println("6");

  //Nome dei giorni

  ePaper.setCursor(33, 19);
  ePaper.println("LUN");
  ePaper.setCursor(81, 19);
  ePaper.println("MAR");
  ePaper.setCursor(133, 19);
  ePaper.println("MER");
  ePaper.setCursor(187, 19);
  ePaper.println("GIO");
  ePaper.setCursor(233, 19);
  ePaper.println("VEN");
  ePaper.setCursor(283, 19);
  ePaper.println("SAB");

  /*
    colonne = 30, 80, 130, 180 , 230,280
    righe = 25,75, 125, 175, 225,275

  */

  //configurazione del font
  f = &Roboto_Regular12pt7b;
  ePaper.setFont(f);

  ePaper.setTextColor(GxEPD_BLACK);


  //###################################################################
  //Lunedì

  if (giorno_settimana == 1)
  {
    ePaper.drawBitmap(gImage_round, 30, 25, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 30, 75, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 30, 125, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 30, 175, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 30, 225, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 30, 275, 45, 45, GxEPD_WHITE);
  }
  else
  {
    ePaper.fillRect(30, 25, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(30, 75, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(30, 125, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(30, 175, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(30, 225, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(30, 275, 45, 45, GxEPD_WHITE);
  }

  ePaper.setCursor(35, 55);
  ePaper.println("5AI"); //prima ora
  ePaper.setCursor(35, 105);
  ePaper.println("5AI"); //seconda ora
  ePaper.setCursor(35, 155);
  ePaper.println("5AI"); //terza ora
  ePaper.setCursor(35, 205);
  ePaper.println("5AI"); //quarta ora
  ePaper.setCursor(35, 255);
  ePaper.println("5AI"); //quinta ora
  ePaper.setCursor(35, 305);
  ePaper.println("5AI"); //sesta ora

  //####################################################################
  //Martedì

  if (giorno_settimana == 2)
  {
    ePaper.drawBitmap(gImage_round, 80, 25, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 80, 75, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 80, 125, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 80, 175, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 80, 225, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 80, 275, 45, 45, GxEPD_WHITE);
  }
  else
  {
    ePaper.fillRect(80, 25, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(80, 75, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(80, 125, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(80, 175, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(80, 225, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(80, 275, 45, 45, GxEPD_WHITE);
  }

  ePaper.setCursor(85, 55);
  ePaper.println("5AI"); //prima ora
  ePaper.setCursor(85, 105);
  ePaper.println("5AI"); //seconda ora
  ePaper.setCursor(85, 155);
  ePaper.println("5AI"); //terza ora
  ePaper.setCursor(85, 205);
  ePaper.println("5AI"); //quarta ora
  ePaper.setCursor(85, 255);
  ePaper.println("5AI"); //quinta ora
  ePaper.setCursor(85, 305);
  ePaper.println("5AI"); //sesta ora

  //####################################################################
  //Mercoledì
  
  if (giorno_settimana == 3)
  {
    ePaper.drawBitmap(gImage_round, 130, 25, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 130, 75, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 130, 125, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 130, 175, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 130, 225, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 130, 275, 45, 45, GxEPD_WHITE);
  }
  else
  {
    ePaper.fillRect(130, 25, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(130, 75, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(130, 125, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(130, 175, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(130, 225, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(130, 275, 45, 45, GxEPD_WHITE);
  }

  ePaper.setCursor(135, 55);
  ePaper.println("5AI"); //prima ora
  ePaper.setCursor(135, 105);
  ePaper.println("5AI"); //seconda ora
  ePaper.setCursor(135, 155);
  ePaper.println("5AI"); //terza ora
  ePaper.setCursor(135, 205);
  ePaper.println("5AI"); //quarta ora
  ePaper.setCursor(135, 255);
  ePaper.println("5AI"); //quinta ora
  ePaper.setCursor(135, 305);
  ePaper.println("5AI"); //sesta ora

  //####################################################################
  //Giovedì

  if (giorno_settimana == 4)
  {
    ePaper.drawBitmap(gImage_round, 180, 25, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 180, 75, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 180, 125, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 180, 175, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 180, 225, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 180, 275, 45, 45, GxEPD_WHITE);
  }
  else
  {
    ePaper.fillRect(180, 25, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(180, 75, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(180, 125, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(180, 175, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(180, 225, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(180, 275, 45, 45, GxEPD_WHITE);
  }

  ePaper.setCursor(185, 55);
  ePaper.println("5AI"); //prima ora
  ePaper.setCursor(185, 105);
  ePaper.println("5AI"); //seconda ora
  ePaper.setCursor(185, 155);
  ePaper.println("5AI"); //terza ora
  ePaper.setCursor(185, 205);
  ePaper.println("5AI"); //quarta ora
  ePaper.setCursor(185, 255);
  ePaper.println("5AI"); //quinta ora
  ePaper.setCursor(185, 305);
  ePaper.println("5AI"); //sesta ora

  //#####################################################################
  //Venerdì

  if (giorno_settimana == 5)
  {
    ePaper.drawBitmap(gImage_round, 230, 25, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 230, 75, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 230, 125, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 230, 175, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 230, 225, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 230, 275, 45, 45, GxEPD_WHITE);
  }
  else
  {
    ePaper.fillRect(230, 25, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(230, 75, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(230, 125, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(230, 175, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(230, 225, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(230, 275, 45, 45, GxEPD_WHITE);
  }

  ePaper.setCursor(235, 55);
  ePaper.println("5AI"); //prima ora
  ePaper.setCursor(235, 105);
  ePaper.println("5AI"); //seconda ora
  ePaper.setCursor(235, 155);
  ePaper.println("5AI"); //terza ora
  ePaper.setCursor(235, 205);
  ePaper.println("5AI"); //quarta ora
  ePaper.setCursor(235, 255);
  ePaper.println("5AI"); //quinta ora
  ePaper.setCursor(235, 305);
  ePaper.println("5AI"); //sesta ora


  //######################################################################
  //Sbato

  if (giorno_settimana == 6)
  {
    ePaper.drawBitmap(gImage_round, 280, 25, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 280, 75, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 280, 125, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 280, 175, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 280, 225, 45, 45, GxEPD_WHITE);
    ePaper.drawBitmap(gImage_round, 280, 275, 45, 45, GxEPD_WHITE);
  }
  else
  {
    ePaper.fillRect(280, 25, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(280, 75, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(280, 125, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(280, 175, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(280, 225, 45, 45, GxEPD_WHITE);
    ePaper.fillRect(280, 275, 45, 45, GxEPD_WHITE);
  }


  ePaper.setCursor(285, 55);
  ePaper.println("5AI"); //prima ora
  ePaper.setCursor(285, 105);
  ePaper.println("5AI"); //seconda ora
  ePaper.setCursor(285, 155);
  ePaper.println("5AI"); //terza ora
  ePaper.setCursor(285, 205);
  ePaper.println("5AI"); //quarta ora
  ePaper.setCursor(285, 255);
  ePaper.println("5AI"); //quinta ora
  ePaper.setCursor(285, 305);
  ePaper.println("5AI"); //sesta ora

  // Parte sotto del giorno
  
  ePaper.setCursor(8, 365);
  ePaper.println("Mercoledì 14 Novembre 2018"); //sesta ora

}
