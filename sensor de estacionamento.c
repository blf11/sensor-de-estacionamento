#include <LiquidCrystal.h> /* including the library of the LCD*/
#define trigger 10 /* assigning Arduino pin to trigger pin of HC-SR04*/
#define echo 9 /* assigning Arduino pin to echo pin of HC-SR04*/
#define buzzerPin 8 /* assigning Arduino pin to buzzer */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); /* assigning Arduino pins for LCD*/
float time; /* variable in which the time for the pulse will be saved */
float distance; /* variable in which distance covered by the pulse is saved */

void setup() {
  /* dealing working modes of buzzer and pin of HC-SR04*/
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  lcd.begin(16, 2); /* defining the size of LCD*/
  lcd.setCursor(5, 0);
  lcd.print("Arduino ");
  lcd.setCursor(0, 1);
  lcd.print(" Parking Sensor");
  delay(5000);
  lcd.clear();
  Serial.begin(9600); // initialize serial communication at 9600 baud rate
}

void loop() {
  /*generating the pulse by giving HIGH and LOW to HC-SR04*/
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  time = pulseIn(echo, HIGH); /* reading the time of the pulse received */
  distance = (time / 2) / 29.1; /* finding the distance from the obstacle in cm*/

  Serial.print("Distance: ");
  Serial.print(distance); /* printing the distance on the Serial Monitor*/
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.print(distance); /* printing the distance on LCD*/
  lcd.setCursor(13, 0);
  lcd.print("cm");
  if (distance <= 10) /* if distance is less than or equal to 5 cm then emit continuous beep */
  {
    lcd.setCursor(1, 1);
    lcd.print("   Danger! ");
    /* sounding the continuous beep using buzzer */
    tone(buzzerPin, 1000); // Emits a tone of 1000 Hz
  }
  else if (distance <= 30) /* if distance is less than or equal to 30 cm then increase the intensity of Alarm and show warning on LCD*/
  {
    lcd.setCursor(1, 1);
    lcd.print("   Stop! ");
    /* sounding the alarm using buzzer */
    tone(buzzerPin, 1000); // Emits a tone of 1000 Hz
    delay(50);
    noTone(buzzerPin); // Stops the tone
    delay(50);
    tone(buzzerPin, 1000); // Emits a tone of 1000 Hz
    delay(50);
    noTone(buzzerPin); // Stops the tone
    delay(50);
    tone(buzzerPin, 1000); // Emits a tone of 1000 Hz
    delay(50);
    noTone(buzzerPin); // Stops the tone
  }
  else if (distance > 30 && distance <= 40) /* if distance is greater than 30 cm  and less than 40 decrease the intensity of Alarm slightly*/
  {
    tone(buzzerPin, 1000); // Emits a tone of 1000 Hz
    delay(50);
    noTone(buzzerPin); // Stops the tone
  }
  else if (distance > 40 && distance <= 60) /* if distance is greater than 40 cm and less than 60 cm decrease the intensity of Alarm */
  {
    tone(buzzerPin, 1000); // Emits a tone of 1000 Hz
    delay(200);
    noTone(buzzerPin); // Stops the tone
  }
  else /* if distance is greater than 60 cm the intensity of Alarm will be too LOW*/
  {
    noTone(buzzerPin); // Stops the tone
  }
  delay(500);
  lcd.clear();
}
