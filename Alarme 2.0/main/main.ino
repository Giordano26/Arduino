//Alarme feito com buzzer e botão PULLUP
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = HIGH;
const byte buzzer = 9;



void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING); //rotina de interrupção quando sinal do botão for de low para high
  pinMode(buzzer, OUTPUT); 
}

void loop()
{
  
  while(state){ //se estado = true, botão foi pressionado e o led deverá ser acesso
  	digitalWrite(ledPin, HIGH);
    tone(buzzer,300,100);
  	delay(100);
  }
  //caso contrário deixa o led piscando e o buzzer silencioso
  noTone(buzzer);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin,LOW);
  delay(100);
  
}

void blink(){ //função de troca de estado do led
  
  state = !state;
  
}

