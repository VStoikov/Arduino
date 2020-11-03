/*
  Crusie control v0.1

  Cruise control for BMW e30 324d '86 year.

  created 2020
  by Victor Stoykov <https://github.com>

*/

// constants won't change. They're used here to set pin numbers:
const int BUTTON_KONST = 2; // Off
const int BUTTON_ABRUF = 3; //On
const int BUTTON_TEMPO = 4; //Up step for speed
const int RELAY_CLUTCH = 5; //Activate clutch solenoid
const int RELAY_MOTOR = 6; //Activate motor
const int BREAK_SIGNAL = 7; //Car break signal

int buttonKonstState = 0;
int buttonAbrufState = 0;
int buttonTempoState = 0;
int buttonBreakSignal = 0;

int cruise_state = 0;

void setup() {
  // Serial config
  Serial.begin(9600);

  // initialize the pushbutton pins as an input:
  pinMode(BUTTON_KONST, INPUT);
  pinMode(BUTTON_ABRUF, INPUT);
  pinMode(BUTTON_TEMPO, INPUT);
  pinMode(BREAK_SIGNAL, INPUT);

  // initialize digital pins as an output
  pinMode(RELAY_CLUTCH, OUTPUT);
  pinMode(RELAY_MOTOR, OUTPUT);
}

void loop() {
  // read the state of the buttons:
  buttonKonstState = digitalRead(BUTTON_KONST);
  buttonAbrufState = digitalRead(BUTTON_ABRUF);
  buttonTempoState = digitalRead(BUTTON_TEMPO);
  buttonBreakSignal = digitalRead(BREAK_SIGNAL);

  if (buttonBreakSignal == LOW && cruise_state == 1) {
    Serial.println("BR ON");
    digitalWrite(RELAY_CLUTCH, LOW);
    digitalWrite(RELAY_MOTOR, LOW);
    cruise_state = 0;
  }
  if (buttonKonstState == HIGH) {
    Serial.println("OFF");
    cruise_state = 0;
    digitalWrite(RELAY_CLUTCH, LOW);
    delay(1000);
  }
  if (buttonAbrufState == HIGH) {
    Serial.println("ON");
    cruise_state = 1;
    digitalWrite(RELAY_CLUTCH, HIGH);
    delay(1000);
  }
  if (cruise_state == 1 && buttonTempoState == LOW) {
    Serial.println("UP SPEED");
    digitalWrite(RELAY_MOTOR, HIGH);
    delay(200);
    digitalWrite(RELAY_MOTOR, LOW);
    delay(350);
  }
}

