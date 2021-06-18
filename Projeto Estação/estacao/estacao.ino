
//Projeto: Estação de temperatura feita com sensor DHT11
//Autor: Stefano Giordano

#include <LiquidCrystal.h> //lib LCD
#include <DHT.h> //lib sensor dht

//Definir a porta do sensor dht e o seu tipo
#define DHTPIN A1
#define DHTTYPE DHT11

//seta o pin do led
#define LEDPIN 8

//define o estado inicial da sentinela para a rotina de interrupção 
bool sentinel = false;

DHT dht(DHTPIN, DHTTYPE);



//definir os pinos do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Array simbolo grau
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};


void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  dht.begin();
  lcd.begin(16,2);
  lcd.clear();
  lcd.createChar(0, grau);

  //configuração do timer
  TCCR1A = 0;  //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0; //limpa registrador
  TCNT1 = 0; //zera temporizado

  OCR1A = 0xFFFF; //tempo máximo possível do prescaler --> 65535 em hex
  TCCR1B |= (1 << WGM12) | (1 << CS10) | (1 <<CS12); //prescaler de 1024: CS12 = 1 e CS10 = 1 
  TIMSK1 |= (1 << OCIE1A); // habilita interrupção por igualdade de comparação
} 

//
void lblink(int lpin){
    digitalWrite(lpin, HIGH);
    delay(500);
    digitalWrite(lpin, LOW);
    delay(500);
}

float temp(){
 return dht.readTemperature(); 
}
float umi(){
  return dht.readHumidity();
}

void printLCD(){
  lblink(LEDPIN); //indica que iniciou a leitura de temperatura e umidade
  
  float t = temp();
  float h = umi();
  
  lcd.setCursor(0,0);
  lcd.print("Temp : ");
  lcd.print(" ");
  lcd.setCursor(7,0);
  lcd.print(t,1);
  lcd.setCursor(12,0);
  
 
//Mostra o simbolo do grau formado pelo array
  lcd.write((byte)0);
 
//Mostra o simbolo do grau quadrado
//lcd.print((char)223);
  
  lcd.setCursor(0,1);
  lcd.print("Umid : ");
  lcd.print(" ");
  lcd.setCursor(7,1);
  lcd.print(h,1);
  lcd.setCursor(12,1);
  sentinel = !sentinel;
   

}

void loop() {
  
  if(sentinel)
    printLCD();
    
  }

  ISR(TIMER1_COMPA_vect){ //interrupção do TIMER1 
    
  sentinel =  !sentinel;
  
}
