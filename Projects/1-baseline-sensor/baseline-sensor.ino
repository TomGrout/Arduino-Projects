#include "DHTlib/dht.h"
dht DHT;
#define DHT11_PIN     13
/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
 */
 
// Pin 2-8 is connected  to the 7 segments of the display.

const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};
const int digitPins[] = {9, 10, 11, 12};

const byte digitPatterns[15][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}, // 9
  {0, 0, 1, 1, 1, 0, 0}, // 10: '°'
  {0, 1, 1, 0, 0, 0, 1}, // 11: 'C'
  {0, 0, 1, 1, 1, 0, 0}, // 12: '%' (Upper circle)
  {1, 1, 0, 0, 0, 1, 0}, // 13: '%' (Lower circle)
  {1, 1, 1, 1, 1, 1, 1}  // 14: Blank space
};


unsigned long lastDHTread = 0;
unsigned long lastButtonCheck= 0;
bool lastButtonState = HIGH;
int buttonPin = A0;
int displayValue = 0;
int tempValue = 0;
int humidValue = 0;
int displayMode = 0;    // 0 = Temp, 1 = Humidity


void displayDigit(int digitIndex, int value){
  // turn off all digits to prevent ghosting
  for (int i = 0; i < 4; i++){
    digitalWrite(digitPins[i], LOW);
  }

  // set segments
  if (value >= 0 && value <= 14) {
    for (int seg = 0; seg < 7; seg++){
      digitalWrite(segmentPins[seg], digitPatterns[value][seg]);
    }
  } else {
    for (int seg = 0; seg < 7; seg++) {
      digitalWrite(segmentPins[seg], HIGH); 
    }
  }

  // set actual digit (number)
  digitalWrite(digitPins[digitIndex], HIGH);
}

void updateDisplay(int value, bool isTemperature) {
  int displayBuffer[4];

  // Extract tens and ones for values (e.g., 27)
  int tens = (value / 10) % 10;
  int ones = value % 10;

  // Left-align value to Digits 0 and 1
  if (value >= 10) {
    displayBuffer[0] = tens;
    displayBuffer[1] = ones;
  } else {
    // Single digit left-alignment (e.g. 9 C)
    displayBuffer[0] = ones;
    displayBuffer[1] = 14; // Blank space on 2nd digit
  }

  // Assign symbols to Digits 2 and 3
  if (isTemperature) {
    displayBuffer[2] = 10; // '°'
    displayBuffer[3] = 11; // 'C'
  } else {
    displayBuffer[2] = 12; // '%' Part 1
    displayBuffer[3] = 13; // '%' Part 2
  }

  // Cycle through all 4 digits
  for (int i = 0; i < 4; i++) {
    displayDigit(i, displayBuffer[i]);
    delay(3);
  }
}

void setup() {                
  Serial.begin(9600);
  Serial.println();
  pinMode(buttonPin, INPUT_PULLUP);

  // initialise  the digital pins as outputs
  for (int i = 0; i < 7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++){
    pinMode(digitPins[i], OUTPUT);
  }

  delay(1000);
  if (DHT.read11(DHT11_PIN) == DHTLIB_OK) {
    tempValue  = (int)DHT.temperature;
    humidValue = (int)DHT.humidity;
  }
 
}


void loop() {
  unsigned long currentMillis = millis();

  // step 1 - read dht sensor value every 2 secs:
  
  // time since last check
  if (currentMillis - lastDHTread >= 2000){
    lastDHTread = currentMillis;

    int dht_check = DHT.read11(DHT11_PIN);
    if(dht_check == DHTLIB_OK){
      tempValue = (int)DHT.temperature;  // store temperature
      humidValue = (int)DHT.humidity;   // store humidity
    }
  }

  // step 2 - button input w/ debounce
  if (currentMillis - lastButtonCheck >= 50){
    lastButtonCheck = currentMillis;
    bool currentButtonState = digitalRead(buttonPin);
  
  //detect high->low and low->high press
    if (lastButtonState == HIGH &&currentButtonState == LOW){
      displayMode = !displayMode; // Switch state
      Serial.print("Humidity: ");
      Serial.print(DHT.humidity, 1);
      Serial.print("% | Temp: ");
      Serial.print(DHT.temperature, 1);
      Serial.println(" C"); 
    }
  lastButtonState = currentButtonState;

  }

  // step 3 - continually update

  if (displayMode == 0){
    updateDisplay(tempValue, true);
  }
  else{
    updateDisplay(humidValue, false);
  }

}