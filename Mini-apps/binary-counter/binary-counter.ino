
int counter = 0;
int pins[4];

void setup() {
  int firstPin = 2;
  Serial.begin(9600);
  Serial.write("test");
  pinMode (firstPin, OUTPUT);
  pinMode (firstPin+1, OUTPUT);
  pinMode (firstPin+2, OUTPUT);
  pinMode (firstPin+3, OUTPUT);


}

void loop() {
  counter++;
  if (counter > 15){
    counter = 0;
    digitalWrite(2, LOW );
    digitalWrite(3, LOW );
    digitalWrite(4, LOW );
    digitalWrite(5, LOW );
    //Serial.print(counter);
  }

  int decimalNum = counter;


  int rem = decimalNum % 8;
  if (rem < decimalNum){
    pins[0] = 1;
    decimalNum = rem;
  }
  else {
    pins[0] = 0;
  }


  rem = decimalNum % 4;
  if (rem < decimalNum){
    pins[1] = 1;
    decimalNum = rem;
  }
  else {
    pins[1] = 0;
  }

  rem = decimalNum % 2;
  if (rem < decimalNum){
    pins[2] = 1;
    decimalNum = rem;
  }
  else {
    pins[2] = 0;
  }

  rem = decimalNum % 1;
  if (rem < decimalNum){
    pins[3] = 1;
    decimalNum = rem;
  }
  else {
    pins[3] = 0;
  }

  Serial.println();
  Serial.write("NEXT");
  
  
  for (int i=0; i<4; i++){
    Serial.println();
    Serial.write("pin ");
    Serial.write(i);
    Serial.write(":");
    Serial.print(pins[i]);
    int currPin = i+2;
    digitalWrite(currPin, (pins[i] == 1 ? HIGH : LOW) );
  }

  delay(2000);

}
