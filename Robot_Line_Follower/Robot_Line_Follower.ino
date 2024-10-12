
//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define sensor_left A0
#define sensor_right A1

int speed = 230;
int curve_speed = 230;
bool on_cross_stop = false;

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {
  pinMode(sensor_left, INPUT);
  pinMode(sensor_right, INPUT);

  Serial.begin(9600);
}

/*
 * 1 e 1 = preto
 * 0 e 0 = branco
 */

void loop() {
  //printing values of the sensors to the serial monitor
  Serial.print("left sensor: ");
  Serial.print(digitalRead(sensor_left));

  Serial.print(" || right sensor: ");
  Serial.println(digitalRead(sensor_right));

  //line detected by both
  if (digitalRead(sensor_left) == 0 && digitalRead(sensor_right) == 0) {
    //Forward
    foward();
  }
  //line detected by left sensor
  else if (digitalRead(sensor_left) == 1 && digitalRead(sensor_right) == 0) {
    //turn left
    turn_left();
  }
  //line detected by right sensor
  else if (digitalRead(sensor_left) == 0 && digitalRead(sensor_right) == 1) {
    //turn right
    turn_right();
  }
  //line detected by none
  else if (digitalRead(sensor_left) == 1 && digitalRead(sensor_right) == 1) {
    if (on_cross_stop) {
      stop();
    } else {
      foward();
    }
  }
}

void foward() {
  motor1.run(FORWARD);
  motor1.setSpeed(speed);
  motor2.run(FORWARD);
  motor2.setSpeed(speed);
  motor3.run(FORWARD);
  motor3.setSpeed(speed);
  motor4.run(FORWARD);
  motor4.setSpeed(speed);
}

void turn_left() {
  motor1.run(FORWARD);
  motor1.setSpeed(curve_speed);
  motor2.run(FORWARD);
  motor2.setSpeed(curve_speed);
  motor3.run(BACKWARD);
  motor3.setSpeed(curve_speed);
  motor4.run(BACKWARD);
  motor4.setSpeed(curve_speed);
}

void turn_right() {
  motor1.run(BACKWARD);
  motor1.setSpeed(curve_speed);
  motor2.run(BACKWARD);
  motor2.setSpeed(curve_speed);
  motor3.run(FORWARD);
  motor3.setSpeed(curve_speed);
  motor4.run(FORWARD);
  motor4.setSpeed(curve_speed);
}

void stop() {
  motor1.run(RELEASE);
  motor1.setSpeed(0);
  motor2.run(RELEASE);
  motor2.setSpeed(0);
  motor3.run(RELEASE);
  motor3.setSpeed(0);
  motor4.run(RELEASE);
  motor4.setSpeed(0);
}
