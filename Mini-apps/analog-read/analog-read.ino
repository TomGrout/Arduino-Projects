int readPin=A3;
double A3v=0; 
int delayTime;
int readVal;

void setup() {
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  readVal = analogRead(readPin);
  A3v = (5./1023.)*readVal;
  Serial.println(A3v);
  delay(500);
  
}
