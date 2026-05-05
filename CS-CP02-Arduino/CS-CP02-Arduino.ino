#include <Servo.h>

Servo servo1;
Servo servo2;

int pinoServo1 = 9;
int pinoServo2 = 10;
int pinoLED = 11;

int btn1Up = 2;
int btn1Down = 3;
int btn2Right = 4;
int btn2Left = 5;
int btnLED = 6;

int angulo1 = 90;
int angulo2 = 90;

int passo = 30;

// Estado anterior dos botões
bool estadoAnt_btn1Up = HIGH;
bool estadoAnt_btn1Down = HIGH;
bool estadoAnt_btn2Right = HIGH;
bool estadoAnt_btn2Left = HIGH;
bool estadoAnt_btnLED = HIGH;

void setup() {
  Serial.begin(9600);
  servo1.attach(pinoServo1);
  servo2.attach(pinoServo2);

  pinMode(btn1Up, INPUT_PULLUP);
  pinMode(btn1Down, INPUT_PULLUP);
  pinMode(btn2Right, INPUT_PULLUP);
  pinMode(btn2Left, INPUT_PULLUP);
  pinMode(btnLED, INPUT_PULLUP);
  pinMode(pinoLED, OUTPUT);

  servo1.write(angulo1);
  servo2.write(angulo2);
}

void loop() {
  // Leitura atual
  bool leitura_btn1Up = digitalRead(btn1Up);
  bool leitura_btn1Down = digitalRead(btn1Down);
  bool leitura_btn2Right = digitalRead(btn2Right);
  bool leitura_btn2Left = digitalRead(btn2Left);
  bool leitura_btnLED = digitalRead(btnLED);

  // Servo 1 - aumentar
  if (estadoAnt_btn1Up == HIGH && leitura_btn1Up == LOW) {
    angulo1 += passo;
    if (angulo1 > 180) angulo1 = 180;
    servo1.write(angulo1);
  }

  // Servo 1 - diminuir
  if (estadoAnt_btn1Down == HIGH && leitura_btn1Down == LOW) {
    angulo1 -= passo;
    if (angulo1 < 0) angulo1 = 0;
    servo1.write(angulo1);
  }

  // Servo 2 - aumentar
  if (estadoAnt_btn2Right == HIGH && leitura_btn2Right == LOW) {
    angulo2 += passo;
    if (angulo2 > 180) angulo2 = 180;
    servo2.write(angulo2);
  }

  // Servo 2 - diminuir
  if (estadoAnt_btn2Left == HIGH && leitura_btn2Left == LOW) {
    angulo2 -= passo;
    if (angulo2 < 0) angulo2 = 0;
    servo2.write(angulo2);
  }

  if (estadoAnt_btnLED == HIGH && leitura_btnLED == LOW) {
  digitalWrite(pinoLED, HIGH);
  delay(1000);
  digitalWrite(pinoLED, LOW);
  }

  // Atualiza estados anteriores
  estadoAnt_btn1Up = leitura_btn1Up;
  estadoAnt_btn1Down = leitura_btn1Down;
  estadoAnt_btn2Right = leitura_btn2Right;
  estadoAnt_btn2Left = leitura_btn2Left;
  estadoAnt_btnLED = leitura_btnLED;

  delay(10); // pequeno debounce


}