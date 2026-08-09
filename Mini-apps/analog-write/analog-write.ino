int pinGreenLED = 9;

void setup() {
  pinMode (pinGreenLED, OUTPUT);
  
}

void loop() {
  int brightness = 5;

  analogWrite(pinGreenLED, brightness);
  delay(1000);
  
  analogWrite(pinGreenLED, brightness + 30);
  delay(1000);

  analogWrite(pinGreenLED, brightness + 60);
  delay(1000);

  analogWrite(pinGreenLED, brightness + 90);
  delay(1000);

  analogWrite(pinGreenLED, brightness + 120);
  delay(1000);

  analogWrite(pinGreenLED, brightness + 150);
  delay(1000);

   analogWrite(pinGreenLED, brightness + 180);
  delay(1000);

}
