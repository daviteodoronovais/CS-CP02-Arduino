#include <Servo.h>

Servo servo1;
Servo servo2;

// Pinos
int pinoServo1 = 9;
int pinoServo2 = 10;
int pinoLED = 11;
int pinoLDR = A0;

// Botões
int btn1 = 2;
int btn2 = 3;
int btn3 = 4;
int btn4 = 5;
int btn5 = 6;

// Estados
int angulo1 = 90;
int angulo2 = 90;
int passo = 15;

// Controle LDR
bool modoLDR = false;
unsigned long tempoLDR = 0;
int limiarLDR = 600; // Regular conforme a luminosidade da sala e dos LEDs

void setup() {
  servo1.attach(pinoServo1);
  servo2.attach(pinoServo2);

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btn5, INPUT_PULLUP);

  pinMode(pinoLED, OUTPUT);

  servo1.write(angulo1);
  servo2.write(angulo2);

  Serial.begin(9600);
}

void loop() {

  int leituraLDR = analogRead(pinoLDR);
  Serial.println(analogRead(A0));

  // ===== PRIORIDADE DO LDR =====
  if (leituraLDR > limiarLDR && !modoLDR) {
    modoLDR = true;
    tempoLDR = millis();

    servo1.write(90);
    servo2.write(90);
  }

  if (modoLDR) {
    if (millis() - tempoLDR < 10000) {
      return; // trava sistema por 10s
    } else {
      modoLDR = false;
    }
  }

  // ===== BOTÕES =====

  if (digitalRead(btn1) == LOW) {
    angulo1 += passo;
    if (angulo1 > 180) angulo1 = 180;
    servo1.write(angulo1);
    delay(200);
  }

  if (digitalRead(btn2) == LOW) {
    angulo1 -= passo;
    if (angulo1 < 0) angulo1 = 0;
    servo1.write(angulo1);
    delay(200);
  }

  if (digitalRead(btn3) == LOW) {
    angulo2 += passo;
    if (angulo2 > 180) angulo2 = 180;
    servo2.write(angulo2);
    delay(200);
  }

  if (digitalRead(btn4) == LOW) {
    angulo2 -= passo;
    if (angulo2 < 0) angulo2 = 0;
    servo2.write(angulo2);
    delay(200);
  }

  if (digitalRead(btn5) == LOW) {
    digitalWrite(pinoLED, HIGH);
    delay(1000);
    digitalWrite(pinoLED, LOW);
  }
  
}
