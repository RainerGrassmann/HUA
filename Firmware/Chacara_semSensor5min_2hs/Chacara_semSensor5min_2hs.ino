/* Controle de irrigaçãSo: monitor LCD + LED + Rele válvula Solenoide
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

//int umidade = 100; 

//const int tempo_rega = 4000; //define o tempo de rega

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
  lcd.print("sem sensor de");
  lcd.setCursor(0, 1);
  lcd.print("umidade do solo");
  delay(1500);

  //Limpa a tela do LCD
  lcd.clear();
  //Posiciona o cursor na coluna 2, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Iniciar rega");
  lcd.setCursor(0, 1);
  lcd.print(" em 5 ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(" em 4 ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(" em 3 ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(" em 2 ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(" em 1 ");
  delay(1000);
  lcd.clear();

  digitalWrite (LED_PIN, HIGH);
  digitalWrite(VALVE_PIN, LOW);
  lcd.setCursor(3, 0);
  lcd.print("REGANDO 2 min");
  delay(120000);
  //tempo equivalente a 2 minutos de rega em milisegundos
  digitalWrite (LED_PIN, LOW);
  digitalWrite(VALVE_PIN, HIGH);
  lcd.clear();
  lcd.print("REGA finalizada");
  delay(3000);
  lcd.clear();
  lcd.print("Prox. REGA 2h");
  delay(1800000);
  lcd.clear();
  lcd.print("Prox. REGA 1,5h");
  delay(1800000);
  lcd.clear() ;
   lcd.print("Prox. REGA 1h");
  delay(1800000);
  lcd.clear();
  lcd.print("Prox. REGA 30min");
  delay(600000);
  lcd.clear();
  lcd.print("Prox. REGA 20min");
  delay(600000);
  lcd.clear();
  lcd.print("Prox. REGA 10min");
  delay(300000);
 lcd.print("Prox. REGA 5min");
  delay(18000);
 lcd.print("Prox. REGA 2min");
  delay(12000);
}
