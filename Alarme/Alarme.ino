const int trigPin = 12; 
const int echoPin = 11; 
const int buzzer = 3; 
const int disMin = 50; // em centimetros


void setup() {
  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);   
  pinMode(buzzer, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  float dur, dis;

  // Gera um pulso do sonar de 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //
  
  dur = pulseIn(echoPin, HIGH); // mede a distancia pelo pulso da entrada echo
  
  dis = 0.017 * dur; // calculo da distancia para centímetros

  if(dis < disMin)
   tone(buzzer, 500); //Liga o alarme caso chego abaixo dos 50 cms
  else
    noTone(buzzer);  


  Serial.print("Distancia: ");
  Serial.print(dis);
  Serial.println("cm");
  delay(200);
}

