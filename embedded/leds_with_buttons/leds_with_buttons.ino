#define numberOfLeds 3

#define pinNumberButtonStart 2
#define pinNumberLedStart 5

#define delayTimeForSafety 250

int previous = 1;
boolean on[numberOfLeds];

long currentTime = 0;

void setup() {
  
  configureButtonPins();
  configureLedPins();

  Serial.begin(9600);
}

void configureButtonPins() {
  
  int currentPinNumber;
  
  for (int i = 0; i < numberOfLeds; i++) {
    currentPinNumber = pinNumberButtonStart + i;
    pinMode(currentPinNumber, INPUT);
    digitalWrite(currentPinNumber, HIGH);
  }
}

void configureLedPins() {
  for (int i = 0; i < numberOfLeds; i++) {
    pinMode(pinNumberLedStart + i, OUTPUT);   
  }
}

void loop() {
  currentTime++;
  updateState();
}

/**
 * Switches the light if necessary.
 */
void updateState() {
  int state;

  for (int i = 0; i < numberOfLeds; i++) {
    
    byte currentPinNumber = pinNumberButtonStart + i;

    state = digitalRead(currentPinNumber);

    // Button is down, was up
    if (state == 0 && state != previous) {
      on[i] = !on[i];
      switchLight(i);
      delay(delayTimeForSafety);
    }
    
    previous = state;
  }
}

void switchLight(byte index) {
  Serial.println(on[index] ? "on" : "off");
  digitalWrite(pinNumberLedStart + index, on[index] ? HIGH : LOW);
  Serial.println(currentTime);
}


