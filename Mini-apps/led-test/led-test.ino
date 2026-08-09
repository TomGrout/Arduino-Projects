const int led = 13;
int longDelay = 1000;
int shortDelay = 100;
int waitTime = 500;

void setup() {
  pinMode(led, OUTPUT);

}

void loop() {
  for (int i=0; i<3; i++){
    digitalWrite(led, HIGH);
    delay(longDelay);
    digitalWrite(led, LOW);
    delay(waitTime);
  }
  
  for (int j=0; j<3; j++){
    digitalWrite(led, HIGH);
    delay(shortDelay);
    digitalWrite(led, LOW);
    delay(waitTime);
  }

  for (int i=0; i<3; i++){
    digitalWrite(led, HIGH);
    delay(longDelay);
    digitalWrite(led, LOW);
    delay(waitTime);
  }


  delay(3000);
}
