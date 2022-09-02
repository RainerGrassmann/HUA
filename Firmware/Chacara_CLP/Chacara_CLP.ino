/* Controle de irrigaçãSo: Sensor de umidade + monitor LCD + LED + Rele válvula Solenoide
  preparado para sistema de irrigação da chacara em Campo Limpo Paulista
  Autor: Rainer Grassmann
  This code oparates under CCAttributionNon-CommericalShare Alike
  Attribution-NonCommercial-ShareAlike 4.0 International
*/

//=texto informativo

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// define saida led
const int LED_PIN = 12;  //pino LED_PIN

// define saída da válvula Solenoide.
const int VALVE_PIN = 8 ;  //pino VALVE_PIN

// define porta Analógica do sensor de umidade do solo
const int val_umid = A0; // sensor de umidade do solo

int umidade = 100;

const int tempo_rega = 60000; //define o tempo de rega

void setup() {
  Serial.begin(9600);

  //Define o número de colunas e linhas do LCD
  lcd.begin(20, 3);

  // define como saida
  pinMode(LED_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);

  // para garantir valvula fechada o valor de VALVE_PIN é HIGH
  digitalWrite(VALVE_PIN, HIGH);

  // LED_PIN pisca 3 vezes no setup.
  digitalWrite(LED_PIN, HIGH);
  delay(75);
  digitalWrite(LED_PIN, LOW);
  delay(75);
  digitalWrite(LED_PIN, HIGH);
  delay(75);
  digitalWrite(LED_PIN, LOW);
  delay(75);
  digitalWrite(LED_PIN, HIGH);
  delay(75);
  digitalWrite(LED_PIN, LOW);
  delay(75);
}

void loop() {
  //Limpa a tela do LCD
  lcd.clear();
  //Posiciona o cursor na coluna 2, linha 0;
  lcd.setCursor(2, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("sistema HUA");
  delay(1200);
  lcd.setCursor(0, 1);
  lcd.print("irrigação auto");

  //Limpa a tela do LCD
  lcd.clear();
  //Posiciona o cursor na coluna 2, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("iniciar leitura");
  delay(1500);

  umidade = analogRead(val_umid);
  umidade = constrain(umidade, 240, 1023); //intervalo dos resultados brutos entre úmido e seco
  umidade = map(umidade, 1023, 240, 0, 100); //convertendo os resultados em porcentagem de umidade (0 e 100%)

  Serial.println(umidade);
  //Limpa a tela do LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("lendo umidade"); //Envia o texto entre aspas para o LCD
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print(".");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print("..");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print("...");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1500);
  //Limpa a tela do LCD
  lcd.clear();

  if (umidade < 65) {      // CASO umidade esteja abaixo do parametro declarado,
    digitalWrite (LED_PIN, HIGH);
    digitalWrite(VALVE_PIN, LOW);
    //Limpa a tela do LCD, (em caso de LCD 16x2)
    // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
    //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
    lcd.setCursor(2, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("umidade baixa");
    delay(500);
    lcd.setCursor(6, 1);
    lcd.print("REGAR");
    delay(300);
    lcd.setCursor(11, 1);
    lcd.print("!");
    delay(tempo_rega * 3);
    digitalWrite (LED_PIN, LOW);
    digitalWrite(VALVE_PIN, HIGH);
    lcd.clear();
    lcd.print("REGA finalizada");
    delay(300);

  } else   {
    digitalWrite (LED_PIN, LOW);
    digitalWrite(VALVE_PIN, HIGH);
    //Limpa a tela do LCD
    // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
    //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
    lcd.setCursor(2, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("umidade boa");
    delay(500);
    lcd.setCursor(1, 1);
    lcd.print("PARAR DE REGAR");
    delay(300);
    lcd.setCursor(15, 1);
    lcd.print("!");
  }

  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 4h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 3h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 2h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 1h");
  delay(10000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1790000);
  lcd.clear();
  lcd.print("Prox. REGA 30m");
  //Posiciona o cursor na coluna 9, linha 1;
  delay(2000);
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1790000);
  lcd.clear();


  Serial.println(umidade);
  //Limpa a tela do LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("lendo umidade"); //Envia o texto entre aspas para o LCD
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print(".");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print("..");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print("...");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1500);
  //Limpa a tela do LCD
  lcd.clear();

  if (umidade < 65) {      // CASO umidade esteja abaixo do parametro declarado,
    digitalWrite (LED_PIN, HIGH);
    digitalWrite(VALVE_PIN, LOW);
    //Limpa a tela do LCD, (em caso de LCD 16x2)
    // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
    //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
    lcd.setCursor(2, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("umidade baixa");
    delay(500);
    lcd.setCursor(6, 1);
    lcd.print("REGAR");
    delay(300);
    lcd.setCursor(11, 1);
    lcd.print("!");
    delay(tempo_rega * 3);
    digitalWrite (LED_PIN, LOW);
    digitalWrite(VALVE_PIN, HIGH);
    lcd.clear();
    lcd.print("REGA finalizada");
    delay(300);

  } else   {
    digitalWrite (LED_PIN, LOW);
    digitalWrite(VALVE_PIN, HIGH);
    //Limpa a tela do LCD
    // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
    //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
    lcd.setCursor(2, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("umidade boa");
    delay(500);
    lcd.setCursor(1, 1);
    lcd.print("PARAR DE REGAR");
    delay(300);
    lcd.setCursor(15, 1);
    lcd.print("!");
  }

  delay(2600);
  lcd.clear();
  lcd.print("Prox. REGA 12h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 11h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 10h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 9h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 8h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 7h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 6h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 5h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 4h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 3h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 2h");
  delay(5000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1200000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.clear();
  lcd.print("Prox. REGA 1h");
  delay(10000);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1790000);
  lcd.clear();
  lcd.print("Prox. REGA 30m");
  //Posiciona o cursor na coluna 9, linha 1;
  delay(2000);
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1790000);
  lcd.clear();


  Serial.println(umidade);
  //Limpa a tela do LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("lendo umidade"); //Envia o texto entre aspas para o LCD
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print(".");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print("..");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  lcd.setCursor(13, 0);
  lcd.print("...");
  digitalWrite(LED_PIN, HIGH);
  delay(150);
  digitalWrite(LED_PIN, LOW);
  delay(150);
  //Posiciona o cursor na coluna 9, linha 1;
  lcd.setCursor(9, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print(umidade);
  lcd.setCursor(12, 1);
  lcd.print("%");
  delay(1500);
  //Limpa a tela do LCD
  lcd.clear();

  if (umidade < 65) {      // CASO umidade esteja abaixo do parametro declarado,
    digitalWrite (LED_PIN, HIGH);
    digitalWrite(VALVE_PIN, LOW);
    //Limpa a tela do LCD, (em caso de LCD 16x2)
    // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
    //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
    lcd.setCursor(2, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("umidade baixa");
    delay(500);
    lcd.setCursor(6, 1);
    lcd.print("REGAR");
    delay(300);
    lcd.setCursor(11, 1);
    lcd.print("!");
    delay(tempo_rega);
    digitalWrite (LED_PIN, LOW);
    digitalWrite(VALVE_PIN, HIGH);
    lcd.clear();
    lcd.print("REGA finalizada");
    delay(300);

  } else   {
    digitalWrite (LED_PIN, LOW);
    digitalWrite(VALVE_PIN, HIGH);
    //Limpa a tela do LCD
    // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
    //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
    lcd.setCursor(2, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("umidade boa");
    delay(500);
    lcd.setCursor(1, 1);
    lcd.print("PARAR DE REGAR");
    delay(300);
    lcd.setCursor(15, 1);
    lcd.print("!");
    lcd.clear();
    lcd.print("Prox. REGA 1h");
    delay(10000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1790000);
    lcd.clear();
    lcd.print("Prox. REGA 30m");
    //Posiciona o cursor na coluna 9, linha 1;
    delay(2000);
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1790000);
    lcd.clear();


    Serial.println(umidade);
    //Limpa a tela do LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("lendo umidade"); //Envia o texto entre aspas para o LCD
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
    lcd.setCursor(13, 0);
    lcd.print(".");
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
    lcd.setCursor(13, 0);
    lcd.print("..");
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
    lcd.setCursor(13, 0);
    lcd.print("...");
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1500);
    //Limpa a tela do LCD
    lcd.clear();

    if (umidade < 65) {      // CASO umidade esteja abaixo do parametro declarado,
      digitalWrite (LED_PIN, HIGH);
      digitalWrite(VALVE_PIN, LOW);
      //Limpa a tela do LCD, (em caso de LCD 16x2)
      // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
      //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
      lcd.setCursor(2, 0);
      //Envia o texto entre aspas para o LCD
      lcd.print("umidade baixa");
      delay(500);
      lcd.setCursor(6, 1);
      lcd.print("REGAR");
      delay(300);
      lcd.setCursor(11, 1);
      lcd.print("!");
      delay(tempo_rega);
      digitalWrite (LED_PIN, LOW);
      digitalWrite(VALVE_PIN, HIGH);
      lcd.clear();
      lcd.print("REGA finalizada");
      delay(300);

    } else   {
      digitalWrite (LED_PIN, LOW);
      digitalWrite(VALVE_PIN, HIGH);
      //Limpa a tela do LCD
      // lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
      //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
      lcd.setCursor(2, 0);
      //Envia o texto entre aspas para o LCD
      lcd.print("umidade boa");
      delay(500);
      lcd.setCursor(1, 1);
      lcd.print("PARAR DE REGAR");
      delay(300);
      lcd.setCursor(15, 1);
      lcd.print("!");
    }
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    lcd.clear();
    lcd.print("Prox. REGA 5h");
    delay(5000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    lcd.clear();
    lcd.print("Prox. REGA 4h");
    delay(5000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    lcd.clear();
    lcd.print("Prox. REGA 3h");
    delay(5000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    lcd.clear();
    lcd.print("Prox. REGA 2h");
    delay(5000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1200000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    lcd.clear();
    lcd.print("Prox. REGA 1h");
    delay(10000);
    //Posiciona o cursor na coluna 9, linha 1;
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1790000);
    lcd.clear();
    lcd.print("Prox. REGA 30m");
    //Posiciona o cursor na coluna 9, linha 1;
    delay(2000);
    lcd.setCursor(9, 1);
    //Envia o texto entre aspas para o LCD
    lcd.print(umidade);
    lcd.setCursor(12, 1);
    lcd.print("%");
    delay(1790000);
    lcd.clear();
 }
  }
