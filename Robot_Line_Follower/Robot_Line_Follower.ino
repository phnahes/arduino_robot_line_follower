//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define sensor_left A0
#define sensor_right A1
#define mode_switch A5  // Usando o pino A5 para a chave

int speed = 230;
int curve_speed = 230;
bool on_cross_stop = false;
bool follow_black_line = true; // Variável para decidir se deve seguir linhas pretas ou brancas

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {
  pinMode(sensor_left, INPUT);
  pinMode(sensor_right, INPUT);
  pinMode(mode_switch, INPUT_PULLUP); // Configurando o pino A5 como entrada com resistor pull-up
  
  Serial.begin(9600);
}

/*
 * 1 e 1 = preto (seguindo linha preta)
 * 0 e 0 = branco (seguindo linha preta)
 * A lógica será invertida para seguir linha branca.
 */

void loop() {
  // Atualiza o modo de operação com base no estado da chave
  follow_black_line = digitalRead(mode_switch);  // Chave ativada para seguir linha preta
  
  // Leitura e impressão dos valores dos sensores no monitor serial
  Serial.print("Leitura Esquerda: ");
  Serial.println(digitalRead(sensor_left));

  Serial.print("Leitura Direita: ");
  Serial.println(digitalRead(sensor_right));

  // Modifica a lógica de acordo com o modo selecionado
  if (follow_black_line) {
    // Seguir linhas pretas (como no código original)
    if (digitalRead(sensor_left) == 0 && digitalRead(sensor_right) == 0) {
      foward();
    } else if (digitalRead(sensor_left) == 1 && digitalRead(sensor_right) == 0) {
      turn_left();
    } else if (digitalRead(sensor_left) == 0 && digitalRead(sensor_right) == 1) {
      turn_right();
    } else if (digitalRead(sensor_left) == 1 && digitalRead(sensor_right) == 1) {
      if (on_cross_stop) {
        stop();
      } else {
        foward();
      }
    }
  } else {
    // Seguir linhas brancas (inverte a lógica)
    if (digitalRead(sensor_left) == 1 && digitalRead(sensor_right) == 1) {
      foward();
    } else if (digitalRead(sensor_left) == 0 && digitalRead(sensor_right) == 1) {
      turn_left();
    } else if (digitalRead(sensor_left) == 1 && digitalRead(sensor_right) == 0) {
      turn_right();
    } else if (digitalRead(sensor_left) == 0 && digitalRead(sensor_right) == 0) {
      if (on_cross_stop) {
        stop();
      } else {
        foward();
      }
    }
  }
}

// Função para mover para frente
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

// Função para virar à esquerda
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

// Função para virar à direita
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

// Função para parar os motores
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
