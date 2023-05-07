#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <analogWrite.h>


//Definición de pines
#define AIN1 18
#define AIN2 4
#define BIN1 27
#define BIN2 14
#define AIN1_1 32
#define AIN2_1 33
#define BIN1_1 25
#define BIN2_1 26

const int tiempoPruebas = 100;
//Valores máximos y mínimos de PWM
const int valorMaxPWM = 255;
const int valorMinPWM = 200;
//Se inicializa el pwm de las llantas con el valor máximo
int valorPWMLlantas = valorMaxPWM;

void setup() {
  Serial.begin(115200);
  Dabble.begin("balam2023"); //Puede cambiar el nombre de su dispositivo aquí
  //Configuración de pines
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(AIN1_1, OUTPUT);
  pinMode(AIN2_1, OUTPUT);
  pinMode(BIN1_1, OUTPUT);
  pinMode(BIN2_1, OUTPUT);

}

void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    //Mover hacia adelante
    analogWrite(AIN1, valorPWMLlantas);
    digitalWrite(AIN2, LOW);
    analogWrite(BIN1, valorPWMLlantas);
    digitalWrite(BIN2, LOW);
    delay(tiempoPruebas);

  } else if (GamePad.isDownPressed()) {
    //Mover hacia adelante
    digitalWrite(AIN1, LOW);
    analogWrite(AIN2, valorPWMLlantas);
    digitalWrite(BIN1, LOW);
    analogWrite(BIN2, valorPWMLlantas);
    delay(tiempoPruebas);

  } else if (GamePad.isLeftPressed()) {
    //Girar hacia la izquierda
    digitalWrite(AIN1, LOW);
    analogWrite(AIN2, valorPWMLlantas);
    analogWrite(BIN1, valorPWMLlantas);
    digitalWrite(BIN2, LOW);
    delay(tiempoPruebas);

  } else if (GamePad.isRightPressed()) {
    //Girar hacia la derecha
    analogWrite(AIN1, valorPWMLlantas);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    analogWrite(BIN2, valorPWMLlantas);
    delay(tiempoPruebas);

  } else if (GamePad.isTrianglePressed()) {
    //Frena rápidamente
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255);
    analogWrite(BIN1, 255);
    analogWrite(BIN2, 255);

  } else if (GamePad.isSelectPressed()) {
    //Cambia de velocidad
    if (valorPWMLlantas == valorMaxPWM) {
      valorPWMLlantas = valorMinPWM;
    } else {
      valorPWMLlantas = valorMaxPWM;
    }

  } else  if (GamePad.isSquarePressed()) {
    //Activa motores para soltar la pelota
    analogWrite(AIN1_1, valorMaxPWM);
    digitalWrite(AIN2_1, LOW);
    analogWrite(BIN1_1, valorMaxPWM);
    digitalWrite(BIN2_1, LOW);
    delay(tiempoPruebas);

  } else if (GamePad.isCirclePressed()) {
    //Activa motores para retener la pelota
    digitalWrite(AIN1_1, LOW);
    analogWrite(AIN2_1, valorMaxPWM);
    digitalWrite(BIN1_1, LOW);
    analogWrite(BIN2_1, valorMaxPWM);
    delay(tiempoPruebas);

  } else {
    //Reinicia el valor de los motores cuando no se utilizan
    analogWrite(AIN1, 0);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, 0);
    analogWrite(AIN1_1, 0);
    analogWrite(AIN2_1, 0);
    analogWrite(BIN1_1, 0);
    analogWrite(BIN2_1, 0);
  }
}
