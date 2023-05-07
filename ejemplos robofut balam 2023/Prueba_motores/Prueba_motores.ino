/* Definimos el pin del PWM*/
#include <analogWrite.h>

const int AIN1 = 18;
const int AIN2 = 4;
const int BIN1 = 27;
const int BIN2 = 14;



void setup() {
  // Configuramos el pin  del PWM como salida
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void loop() {
  //Hacia adelante
  analogWrite(AIN1, 200);
  analogWrite(AIN2, 0);
  analogWrite(BIN1, 200);
  analogWrite(BIN2, 0);
  //Hacia atrás
  analogWrite(AIN1, 0);
  analogWrite(AIN2, 255);
  analogWrite(BIN1, 0);
  analogWrite(BIN2, 255);
}
