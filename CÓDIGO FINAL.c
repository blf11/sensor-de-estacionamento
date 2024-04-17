#include <Arduino.h>

// Definições de pinos
const int triggerPin = 13;
const int echoPin = 12;
const int buzzerPin = 14; 

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT); 
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Ler o tempo de eco
  long duration = pulseIn(echoPin, HIGH);

  // Converter o tempo em distância (em centímetros)
  float distance_cm = duration * 0.034 / 2;

  // Imprimir a distância no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Acionar o buzzer com base na distância
  if (distance_cm <= 10) /* se a distância for menor ou igual a 10 cm, será emitido um bip contínuo */
  {
    tone(buzzerPin, 1000); // 
  }
  
  else if (distance_cm <= 20) /* se a distância for menor ou igual a 20 cm, aumente a intensidade do alarme*/
  {
    tone(buzzerPin, 1000); 
    delay(25);
    noTone(buzzerPin); // 
    delay(25);
    tone(buzzerPin, 1000); 
    delay(25);
    noTone(buzzerPin); 
    delay(25);
    tone(buzzerPin, 1000); 
    delay(25);
    noTone(buzzerPin); 
  }

  else if (distance_cm <= 30) /* se a distância for menor ou igual a 30 cm, aumente a intensidade do alarme*/
  {
    tone(buzzerPin, 1000); 
    delay(50);
    noTone(buzzerPin); 
    delay(50);
    tone(buzzerPin, 1000); 
    delay(50);
    noTone(buzzerPin); 
    delay(50);
    tone(buzzerPin, 1000); 
    delay(50);
    noTone(buzzerPin); 
  }
  else if (distance_cm > 30 && distance_cm <= 40) /* se a distância for maior que 30 cm e menor ou igual a 40, diminui ligeiramente a intensidade do alarme*/
  {
    tone(buzzerPin, 1000); 
    delay(50);
    noTone(buzzerPin);
    delay(100); 
  }
  else if (distance_cm > 40 && distance_cm <= 60) /* se a distância for maior que 40 cm e menor ou igual a 60, diminui a intensidade do alarme*/
  {
    tone(buzzerPin, 1000); 
    delay(50);
    noTone(buzzerPin);
    delay(300); 
  }
  else /* se a distância for maior que 60 cm, parará os bips*/
  {
    noTone(buzzerPin); 
  }
}
