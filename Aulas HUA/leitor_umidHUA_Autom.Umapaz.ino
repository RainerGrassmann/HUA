/* Sensor de umidade LM393 + monitor LCD + LED
  preparado para HUA Automação de Irrigação Umapaz 2024
  Autor: Rainer Grassmann
  adaptado de Saulo Jacques - oficina HUA
*/

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// define saida led
const int LED_PIN = LED_BUILTIN;  //pino LED

// define saida da Bomba d'água.
const int PUMP_PIN = 8;  //pino PUMP


const int val_umid = A0; // sensor de umidade

int umidade = 0;

void setup() {
  Serial.begin(9600);

  //Define o número de colunas e linhas do LCD
  lcd.begin(20, 4);

  // define como saida
  pinMode(LED_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  // para garantir valvula fechada
  digitalWrite(PUMP_PIN, LOW);

  // LED_PIN pisca 3 vezes no setup.
  digitalWrite(LED_PIN, HIGH);
  delay(75);
  digitalWrite(LED_PIN, LOW);
  delay(75);
  digitalWrite(LED_PIN, HIGH);
  delay(75);
  digitalWrite(LED_PIN, LOW);
  delay(75); digitalWrite(LED_PIN, HIGH);
  delay(75);
  digitalWrite(LED_PIN, LOW);





  /*void led(int state) {
    digitalWrite(7, state);
  */
}

void loop() {
  //Limpa a tela do LCD
  lcd.clear();
  //Posiciona o cursor na coluna 2, linha 0;
  lcd.setCursor(2, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("oficina HUA");
  Serial.print("oficina HUA");
  delay(1200);
  lcd.setCursor(0, 1);
  lcd.print("leitor UMAPAZ");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("auto irrigacao");
  delay(2000);
  
  umidade = analogRead(val_umid);
  umidade = constrain(umidade, 240, 1023); //intervalo dos resultados brutos entre úmido e seco
  umidade = map(umidade, 1023, 240, 0, 100); //convertendo os resultados em porcentagem de umidade (0 e 100%)

  Serial.println(umidade);
  //Limpa a tela do LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("lendo umidade");
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

  if (umidade < 65) {      // CASO umidade esteja abaixo do parametro declarado,
    digitalWrite (LED_PIN, HIGH);
     digitalWrite (PUMP_PIN, HIGH);
    //Limpa a tela do LCD, (em caso de LCD 16x2)
    lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
    //Posiciona o cursor na coluna 2, linha 2; [tambem ajuste os setCusors abaixo para linhas = n-2 em caso de LCD 16x2]
    lcd.setCursor(2, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("umidade baixa");
    delay(500);
    lcd.setCursor(6, 1);
    lcd.print("REGAR");
    delay(5000);
    lcd.setCursor(11, 1);
    lcd.print("!");
    digitalWrite (PUMP_PIN, LOW);
  } else   {
    digitalWrite (LED_PIN, LOW);
    //Limpa a tela do LCD
   lcd.clear();//  <- [ative caso esteja usando um LCD 16x2]
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
}
