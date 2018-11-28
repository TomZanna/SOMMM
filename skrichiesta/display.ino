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

  /**
   *    !!!!PAURISSIMAAA!!!!! 
   *    Provo a gestire l'interpretazione del mio json
   */

  const size_t bufferSize = 7 * JSON_ARRAY_SIZE(10) + 10 * JSON_OBJECT_SIZE(5) + 2 * JSON_OBJECT_SIZE(6) + 1050;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject &root = jsonBuffer.parseObject(payload);

  // Dati header

  const char *stanza = root["stanza"];           // "L145"
  const char *giorno = root["giorno"];           // "Venerdi', 23 Novembre 2018"
  int giornoSettimana = root["giornoSettimana"]; // 5
  int oraAttuale = root["oraAttuale"];           // 3

  //CREAZIONE DELL'OGGETTO CONTENENTE I DATI RIGUARDANTI A "OGGI"

  JsonArray &oggi = root["oggi"]; //Oggetto "oggi" contenente tutte le informazioni

  /**
   * Struttura array per ogni ora del giorno  
   * 
   *  ora[5] = {"ora","prof1","prof2","materia","classe"}
   *  
   *  Example : prima_ora[5] = {"1","Tiziano Merzi","Antonino Bileddo","LTPI","5AI"}
   * 
   */

  //Prima ora ----------------------------------------------------------------------------------

  JsonObject &prima = oggi[0];
  const char *prima_ora[5] = {prima["ora"], prima["prof1"], prima["prof2"], prima["mat"], prima["res"]};

  //Seconda ora ----------------------------------------------------------------------------------

  JsonObject &seconda = oggi[1];
  const char *seconda_ora[5] = {seconda["ora"], seconda["prof1"], seconda["prof2"], seconda["mat"], seconda["res"]};

  //Terza ora ----------------------------------------------------------------------------------

  JsonObject &terza = oggi[2];
  const char *terza_ora[5] = {terza["ora"], terza["prof1"], terza["prof2"], terza["mat"], terza["res"]};

  //Quarta ora ----------------------------------------------------------------------------------

  JsonObject &quarta = oggi[3];
  const char *quarta_ora[5] = {quarta["ora"], quarta["prof1"], quarta["prof2"], quarta["mat"], quarta["res"]};

  //Quinta ora ----------------------------------------------------------------------------------

  JsonObject &quinta = oggi[4];
  const char *quinta_ora[5] = {quinta["ora"], quinta["prof1"], quinta["prof2"], quinta["mat"], quinta["res"]};

  //Sesta ora ----------------------------------------------------------------------------------

  JsonObject &sesta = oggi[5];
  const char *sesta_ora[5] = {sesta["ora"], sesta["prof1"], sesta["prof2"], sesta["mat"], sesta["res"]};

  //Settima ora ----------------------------------------------------------------------------------

  JsonObject &settima = oggi[6];
  const char *settima_ora[5] = {settima["ora"], settima["prof1"], settima["prof2"], settima["mat"], settima["res"]};

  //Ottava ora ----------------------------------------------------------------------------------

  JsonObject &ottava = oggi[7];
  const char *ottava_ora[5] = {ottava["ora"], ottava["prof1"], ottava["prof2"], ottava["mat"], ottava["res"]};

  //Nona ora ----------------------------------------------------------------------------------

  JsonObject &nona = oggi[8];
  const char *nona_ora[5] = {nona["ora"], nona["prof1"], nona["prof2"], nona["mat"], nona["res"]};

  //Decima ora ----------------------------------------------------------------------------------

  JsonObject &decima = oggi[9];
  const char *decima_ora[5] = {decima["ora"], decima["prof1"], decima["prof2"], decima["mat"], decima["res"]};

  //################################################################################################################

  //CREAZIONE DELL'OGGETTO CONTENENTE I DATI RIGUARDANTI A "SETTIMANA"

  JsonObject &settimana = root["settimana"]; //Oggetto "settima" contenente tutte le informazioni

  /**
   * Struttura array per ogni giorno della settimana
   * 
   *  giorno[6] = {"prima","seconda","terza","quarta","quinta","sesta"}
   *  
   *  Example : lunedi[5] = {"5AI","4AI","3BE","3AI","5AI","3CI"}
   * 
   */

  //Lunedì ----------------------------------------------------------------------------------

  JsonObject& settimana_1 = settimana["1"];
  const char *lun_aule[6] = {settimana_1["1"], settimana_1["2"], settimana_1["3"], settimana_1["4"], settimana_1["5"], settimana_1["6"]};
  

  //Martedì ----------------------------------------------------------------------------------

  JsonObject& settimana_2 = settimana["2"];
  const char *mar_aule[6] = {settimana_2["1"], settimana_2["2"], settimana_2["3"], settimana_2["4"], settimana_2["5"], settimana_2["6"]};

  //Mercoledì ----------------------------------------------------------------------------------

  JsonObject& settimana_3 = settimana["3"];
  const char *mer_aule[6] = {settimana_3["1"], settimana_3["2"], settimana_3["3"], settimana_3["4"], settimana_3["5"], settimana_3["6"]};
  Serial.println(mer_aule[3]);

  //Giovedì ----------------------------------------------------------------------------------

  JsonObject& settimana_4 = settimana["4"];
  const char *gio_aule[6] = {settimana_4["1"], settimana_4["2"], settimana_4["3"], settimana_4["4"], settimana_4["5"], settimana_4["6"]};

  //Venerdi ----------------------------------------------------------------------------------

  JsonObject& settimana_5 = settimana["5"];
  const char *ven_aule[6] = {settimana_5["1"], settimana_5["2"], settimana_5["3"], settimana_5["4"], settimana_5["5"], settimana_5["6"]};

  //Sabato ----------------------------------------------------------------------------------

  JsonObject& settimana_6 = settimana["6"];
  const char *sab_aule[6] = {settimana_6["1"], settimana_6["2"], settimana_6["3"], settimana_6["4"], settimana_6["5"], settimana_6["6"]};

  //###########################################################################

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
  ePaper.println(stanza);

  //Disegno i separatori

  ePaper.fillRect(355, 115, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 170, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 225, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 280, 280, 2, GxEPD_BLACK);
  ePaper.fillRect(355, 335, 280, 2, GxEPD_BLACK);

  // Disegno le informazioni ora per ora
  

  if (oraAttuale != 0 && oraAttuale < 7)
  { //mostro le prime 6 ore

    //#######################################################################
    // Primo Blocco

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 82);
    ePaper.println(prima_ora[1]); //primo professore

    ePaper.setCursor(363, 107);
    ePaper.println(prima_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 107);
    ePaper.println(prima_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 107);
    ePaper.println(prima_ora[4]); // Classe

    //#######################################################################
    // Secondo Blocco //seconda ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 135);
    ePaper.println(seconda_ora[1]); //primo professore

    ePaper.setCursor(363, 160);
    ePaper.println(seconda_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 160);
    ePaper.println(seconda_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 160);
    ePaper.println(seconda_ora[4]); // Classe

    //#######################################################################
    // Terzo Blocco //terza ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 190);
    ePaper.println(terza_ora[1]); //primo professore

    ePaper.setCursor(363, 215);
    ePaper.println(terza_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 215);
    ePaper.println(terza_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 215);
    ePaper.println(terza_ora[4]); // Classe

    //#######################################################################
    // Quarto Blocco //quarta ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 245);
    ePaper.println(quarta_ora[1]); //primo professore

    ePaper.setCursor(363, 270);
    ePaper.println(quarta_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 270);
    ePaper.println(quarta_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 270);
    ePaper.println(quarta_ora[4]); // Classe

    //#######################################################################
    // Quinto Blocco //quinta ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 300);
    ePaper.println(quinta_ora[1]); //primo professore

    ePaper.setCursor(363, 325);
    ePaper.println(quinta_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 325);
    ePaper.println(quinta_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 325);
    ePaper.println(quinta_ora[4]); // Classe

    //#######################################################################
    // Sesto Blocco //sesta Ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 355);
    ePaper.println(sesta_ora[1]); //primo professore

    ePaper.setCursor(363, 380);
    ePaper.println(sesta_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 380);
    ePaper.println(sesta_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 380);
    ePaper.println(sesta_ora[4]); // Classe
  }

  else if (oraAttuale != 0 && oraAttuale > 6)
  { //mostro le prime 6 ore

    //#######################################################################
    // Primo Blocco //Quinta ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 82);
    ePaper.println(quinta_ora[1]); //primo professore

    ePaper.setCursor(363, 107);
    ePaper.println(quinta_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 107);
    ePaper.println(quinta_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 107);
    ePaper.println(quinta_ora[4]); // Classe

    //#######################################################################
    // Secondo Blocco //Sesta ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 135);
    ePaper.println(sesta_ora[1]); //primo professore

    ePaper.setCursor(363, 160);
    ePaper.println(sesta_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 160);
    ePaper.println(sesta_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 160);
    ePaper.println(sesta_ora[4]); // Classe

    //#######################################################################
    // Terzo Blocco //Settima ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 190);
    ePaper.println(settima_ora[1]); //primo professore

    ePaper.setCursor(363, 215);
    ePaper.println(settima_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 215);
    ePaper.println(settima_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 215);
    ePaper.println(settima_ora[7]); // Classe

    //#######################################################################
    // Quarto Blocco //Ottava ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 245);
    ePaper.println(ottava_ora[1]); //primo professore

    ePaper.setCursor(363, 270);
    ePaper.println(ottava_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 270);
    ePaper.println(ottava_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 270);
    ePaper.println(ottava_ora[4]); // Classe

    //#######################################################################
    // Quinto Blocco //Nona ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 300);
    ePaper.println(nona_ora[1]); //primo professore

    ePaper.setCursor(363, 325);
    ePaper.println(nona_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 325);
    ePaper.println(nona_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 325);
    ePaper.println(nona_ora[4]); // Classe

    //#######################################################################
    // Sesto Blocco //Decima ora

    f = &Roboto_Regular10pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(363, 355);
    ePaper.println(decima_ora[1]); //primo professore

    ePaper.setCursor(363, 380);
    ePaper.println(decima_ora[2]); // secondoi professore

    f = &Roboto_Regular12pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(522, 380);
    ePaper.println(decima_ora[3]); // Materia

    f = &Roboto_Regular18pt7b;
    ePaper.setFont(f);
    ePaper.setTextColor(GxEPD_BLACK);

    ePaper.setCursor(575, 380);
    ePaper.println(decima_ora[4]); // Classe
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
  ePaper.println(lun_aule[0]); //prima ora
  ePaper.setCursor(35, 105);
  ePaper.println(lun_aule[1]); //seconda ora
  ePaper.setCursor(35, 155);
  ePaper.println(lun_aule[2]); //terza ora
  ePaper.setCursor(35, 205);
  ePaper.println(lun_aule[3]); //quarta ora
  ePaper.setCursor(35, 255);
  ePaper.println(lun_aule[4]); //quinta ora
  ePaper.setCursor(35, 305);
  ePaper.println(lun_aule[5]); //sesta ora

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
  ePaper.println(mar_aule[0]); //prima ora
  ePaper.setCursor(85, 105);
  ePaper.println(mar_aule[1]); //seconda ora
  ePaper.setCursor(85, 155);
  ePaper.println(mar_aule[2]); //terza ora
  ePaper.setCursor(85, 205);
  ePaper.println(mar_aule[3]); //quarta ora
  ePaper.setCursor(85, 255);
  ePaper.println(mar_aule[4]); //quinta ora
  ePaper.setCursor(85, 305);
  ePaper.println(mar_aule[5]); //sesta ora

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
  ePaper.println(mer_aule[0]); //prima ora
  ePaper.setCursor(135, 105);
  ePaper.println(mer_aule[1]); //seconda ora
  ePaper.setCursor(135, 155);
  ePaper.println(mer_aule[2]); //terza ora
  ePaper.setCursor(135, 205);
  ePaper.println(mer_aule[3]); //quarta ora
  ePaper.setCursor(135, 255);
  ePaper.println(mer_aule[4]); //quinta ora
  ePaper.setCursor(135, 305);
  ePaper.println(mer_aule[5]); //sesta ora

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
  ePaper.println(gio_aule[0]); //prima ora
  ePaper.setCursor(185, 105);
  ePaper.println(gio_aule[1]); //seconda ora
  ePaper.setCursor(185, 155);
  ePaper.println(gio_aule[2]); //terza ora
  ePaper.setCursor(185, 205);
  ePaper.println(gio_aule[3]); //quarta ora
  ePaper.setCursor(185, 255);
  ePaper.println(gio_aule[4]); //quinta ora
  ePaper.setCursor(185, 305);
  ePaper.println(gio_aule[5]); //sesta ora

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
  ePaper.println(ven_aule[0]); //prima ora
  ePaper.setCursor(235, 105);
  ePaper.println(ven_aule[1]); //seconda ora
  ePaper.setCursor(235, 155);
  ePaper.println(ven_aule[2]); //terza ora
  ePaper.setCursor(235, 205);
  ePaper.println(ven_aule[3]); //quarta ora
  ePaper.setCursor(235, 255);
  ePaper.println(ven_aule[4]); //quinta ora
  ePaper.setCursor(235, 305);
  ePaper.println(ven_aule[5]); //sesta ora

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
  ePaper.println(sab_aule[0]); //prima ora
  ePaper.setCursor(285, 105);
  ePaper.println(sab_aule[1]); //seconda ora
  ePaper.setCursor(285, 155);
  ePaper.println(sab_aule[2]); //terza ora
  ePaper.setCursor(285, 205);
  ePaper.println(sab_aule[3]); //quarta ora
  ePaper.setCursor(285, 255);
  ePaper.println(sab_aule[4]); //quinta ora
  ePaper.setCursor(285, 305);
  ePaper.println(sab_aule[5]); //sesta ora

  // Parte sotto del giorno

  ePaper.setCursor(8, 365);
  ePaper.println(giorno); //sesta ora
}
