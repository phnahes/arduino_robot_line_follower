
# Robô Seguidor de Linha com Sensores IR e Controle de Motores DC

Este projeto consiste em um robô seguidor de linha, controlado por dois sensores de infravermelho (**TCRT5000** ou similares) que detectam a cor do chão (preto ou branco) e quatro motores DC, controlados via **Adafruit Motor Shield V1**. O robô ajusta sua direção conforme a linha é detectada pelos sensores, movendo-se para frente, virando à esquerda ou à direita, ou parando em determinadas condições.

## Bibliotecas Utilizadas

- **AFMotor**: Biblioteca usada para controlar os motores conectados ao **Adafruit Motor Shield V1**. Esta biblioteca permite o controle de velocidade e direção dos motores.

```cpp
#include <AFMotor.h>
```

## Sensores de Linha

Os sensores de linha utilizam infravermelho (IR) para detectar a cor do chão:
- **Preto**: Representado por `1` na leitura digital.
- **Branco**: Representado por `0` na leitura digital.

No código, usamos dois sensores:
- **sensor_left (A0)**: Sensor localizado no lado esquerdo do robô.
- **sensor_right (A1)**: Sensor localizado no lado direito do robô.

Os sensores determinam o comportamento do robô:
- Ambos os sensores detectam **branco** (0 e 0): O robô segue em frente.
- O sensor esquerdo detecta **preto** (1 e 0): O robô vira à esquerda.
- O sensor direito detecta **preto** (0 e 1): O robô vira à direita.
- Ambos os sensores detectam **preto** (1 e 1): O robô pode parar ou continuar em frente, dependendo da variável `on_cross_stop`.

## Controle dos Motores

O robô possui quatro motores DC, conectados ao **Adafruit Motor Shield**:
- **motor1**: Traseiro direito.
- **motor2**: Dianteiro direito.
- **motor3**: Dianteiro esquerdo.
- **motor4**: Traseiro esquerdo.

Os motores são controlados em diferentes frequências de PWM para garantir suavidade e precisão na velocidade:
```cpp
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
```

### Funções de Movimento

#### `forward()`
Move todos os quatro motores para frente com a velocidade definida pela variável `speed`.

```cpp
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
```

#### `turn_left()`
Faz o robô virar à esquerda, invertendo o sentido de rotação dos motores no lado esquerdo (M3 e M4) e mantendo os motores do lado direito para frente. A velocidade é ajustada com `curve_speed`.

```cpp
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
```

#### `turn_right()`
Faz o robô virar à direita, invertendo o sentido de rotação dos motores do lado direito (M1 e M2) e mantendo os motores do lado esquerdo para frente.

```cpp
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
```

#### `stop()`
Para todos os motores.

```cpp
void stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
```

## Comportamento dos Sensores

O comportamento do robô é baseado nas leituras dos sensores de linha:
- **Ambos detectam branco**: O robô segue em frente.
- **Esquerdo detecta preto**: O robô vira à esquerda.
- **Direito detecta preto**: O robô vira à direita.
- **Ambos detectam preto**: O robô pode parar ou continuar dependendo do valor de `on_cross_stop`.

## Configurações e Ajustes

### Velocidade
- `speed`: Controla a velocidade em linha reta.
- `curve_speed`: Controla a velocidade nas curvas.

Ambas podem ser ajustadas para controlar a resposta do robô às leituras dos sensores.

### Variável `on_cross_stop`
A variável `on_cross_stop` controla se o robô deve parar quando os dois sensores detectarem preto (potencialmente em um cruzamento). Quando `true`, o robô para; quando `false`, ele continua avançando.

```cpp
bool on_cross_stop = false;
```

## Serial Monitor
O código utiliza o `Serial.begin(9600)` para exibir no monitor serial as leituras dos sensores. Isso facilita a depuração e o ajuste do comportamento do robô com base no ambiente.

---

