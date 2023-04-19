/* State Machine
|             STATUS                 |         LED         |             ACTION             |
|:---------:| -------- | ----------- | -------- | -------- | -------------- | ------------- |
| HostPower | ATXPower | PowerButton | pinLED0  | pinLED1  | pinHostControl | pinATXControl |
| OPEN      | OPEN     | —           | POWERON  | POWERON  | PowerButton    | POWERON       |
| OPEN      | CLOSE    | —           | POWERON  | POWEROFF | PowerButton    | POWERON       |
|           |          |             |          |          |                |               |
|           |          |             |          |          |                |               |
| CLOSE     | OPEN     | —           | POWEROFF | POWERON  | PowerButton    | POWEROFF      |
| CLOSE     | CLOSE    | —           | POWEROFF | POWEROFF | PowerButton    | POWEROFF      |
*/

// constants won't change. They're used here to set pin numbers:
const int pinHostPower      = 2;
const int pinHostControl    = 3;
const int pinPowerButton    = 4;
const int pinLED0           = 5;
const int pinLED1           = 6;
const int pinATXPower       = 7;
const int pinATXControl     = 13;

// variables will change:
#define UP            1
#define DOWN          0
#define OPEN          1
#define CLOSE         0
#define POWERON       0
#define POWEROFF      1

int PowerButton       = UP;  // variable for reading the pinPowerButton status
int ATXPower          = CLOSE;  // variable for reading the pinATXPower status
int HostPower         = CLOSE;  // variable for reading the pinATXControl status

int PowerButtonCount  = 0;
int PBLastStatus      =UP;
int PowerButtonStatus =UP;

void PowerSwitch(int button) {
  if (button <= DOWN ) {
    digitalWrite(pinHostControl, DOWN);
    PowerButtonStatus = DOWN;
  } else {
    digitalWrite(pinHostControl, UP);
    PowerButtonStatus = UP;
  }
}

void setup() {
  // initialize the output pins:
  pinMode(pinHostControl, OUTPUT);
  pinMode(pinATXControl, OUTPUT);
  digitalWrite(pinATXControl, POWEROFF);
  PowerSwitch(UP);

  pinMode(pinLED0, OUTPUT);
  pinMode(pinLED1, OUTPUT);
  digitalWrite(pinLED0, POWEROFF);
  digitalWrite(pinLED1, POWEROFF);


  // initialize the input pins:
  pinMode(pinPowerButton, INPUT_PULLUP);
  pinMode(pinHostPower, INPUT_PULLUP);
  pinMode(pinATXPower, INPUT_PULLUP);
}

void loop() {
  HostPower = digitalRead(pinHostPower);
  ATXPower = digitalRead(pinATXPower);

  if (ATXPower == OPEN) {
    digitalWrite(pinLED1, POWERON);
  } else {
    digitalWrite(pinLED1, POWEROFF);
  } 

  if (HostPower == OPEN) {
    digitalWrite(pinLED0, POWERON);
    digitalWrite(pinATXControl,POWERON);
  } else {
    digitalWrite(pinLED0, POWEROFF);
    digitalWrite(pinATXControl,POWEROFF);
  }
  
  // pinHostControl link to the pinPowerButton:
  PBLastStatus = PowerButton;
  PowerButton = digitalRead(pinPowerButton);

  if (PowerButton == PBLastStatus) {
    PowerButtonCount ++;
    if (PowerButtonCount >= 3) {
      PowerButtonCount = 3;
      if (PowerButton != PowerButtonStatus) PowerSwitch(PowerButton);
    }
  } else {
    PowerButtonCount = 0;
  }
  delay(10);
}
