//motor A connected between A01 and A02
//motor B connected between B01 and B02

int const LEFT = 0;
int const CENTER = 1;
int const  RIGHT = 2;


int STBY = 10; //standby

int lastDirection = CENTER;

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 4; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

//Sensor
const int sensorPin = 7;
int sensorState = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Hello, World!"));
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(sensorPin, INPUT);


}

void loop() {
  /*
  ������:
  ������ 0, 1 � 2 ��� �������� �� ����� ����� �� ��������� ������ 
  �� �������� �� ����/�����. ��� ��������� �� left < 100(����) �� �� ������� ��. ������ �� �������� ������, � ��� �������� �� 
  right < 100 �� �� ������� ��. ������ �� �������� �������.
  */
  int left = analogRead(0);
  int center = analogRead(1);
  int right = analogRead(2);
  
  

  Serial.print(F("0=")); Serial.println(analogRead(0));
  Serial.print(F("1=")); Serial.println(analogRead(1));
  Serial.print(F("2=")); Serial.println(analogRead(2));
  sensorState = digitalRead(sensorPin);
  
  

  
  if(left < 100 && center < 100 && right < 100){
    switch(lastDirection){
      case LEFT:
      move(2, 255, 0);
      move(1, 128, 1); // ����� 70
      break;
      case CENTER:
      stop(); 
      // ����� ���������
      break;
      case RIGHT:
      move(2, 255, 1);
      move(1, 128, 1); // �����
      break;
      
    }
  } else if(left < 100 && center < 100 && right > 100) { // ��� ��� � ��������� ������� ��������
    lastDirection = LEFT;
    move(2, 255, 0); // ������ 45
     move(1, 128, 1); // �����
  } else if(right < 100 && center < 100 && left > 100) { // ��� ����� � ��������� ������ ��������
    lastDirection = RIGHT;
    move(2, 255, 1); // ������ 55
     move(1, 128, 1); // ����� 70
  } else if(left < 100) { // ��� ���� ��� � ��������
    lastDirection = LEFT;
    move(2, 255, 0); // ������ 25
    move(1, 128, 1); // �����
  } else if(right < 100 ){ // ��� ���� ����� � ��������
    lastDirection = RIGHT;
    move(2, 255, 1); // ������ 25
     move(1,128, 1); // �����
  } else{
    lastDirection = CENTER;
    stop();
     move(1, 128, 1); // �����
  }
  
  
  delay(20);
  /*if (left > 100 && right < 100 && center < 300) { //bqlo < 100
    while(center<300){
      center = analogRead(1);
    move(2, 128, 1); //motor 2,half speed, left 255
    }
  } else if (left < 100 && right > 100 && center < 300){
    while(center<300){
      center = analogRead(1);
     move(2, 128, 0); //motor 2,half speed, right 255
    }
} else {

stop();
}*/

// move(1, 70, 1); //motor 1, full speed, left 255
// move(2, 128, 1); //motor 2, full speed, left 255

// delay(1000); //go for 1 second
// stop(); //stop
// delay(250); //hold for 250ms until move again

// move(1, 70, 0); //motor 1, half speed, right 128
// move(2, 128, 0); //motor 2, half speed, right 128

// delay(1000);
//  stop();
// delay(250);

}


void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  } else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop() {
  //enable standby
  digitalWrite(STBY, LOW);
}