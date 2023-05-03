#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <analogWrite.h>


//Definición de pines
#define AIN1 18
#define AIN2 4
#define BIN1 27
#define BIN2 14

int valorPWMLlantas = 255;
int tiempoPruebas = 100;

void setup() {
  Serial.begin(115200);      
  Dabble.begin("balam2023"); //Puede cambiar el nombre de su dispositivo aquí
  //Configuración de pines
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

}

void loop() {
  Dabble.processInput();   
  
  if (GamePad.isUpPressed()){
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
    
  } else if (GamePad.isLeftPressed()){
    //Girar hacia la izquierda
    digitalWrite(AIN1, LOW);
    analogWrite(AIN2, valorPWMLlantas);
    analogWrite(BIN1, valorPWMLlantas);
    digitalWrite(BIN2, LOW);
    delay(tiempoPruebas);
    
  } else if (GamePad.isRightPressed()){
    //Girar hacia la derecha
    analogWrite(AIN1, valorPWMLlantas);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    analogWrite(BIN2, valorPWMLlantas);
    delay(tiempoPruebas);
    
  } else if (GamePad.isTrianglePressed()){
    //Frena rápidamente
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255);
    analogWrite(BIN1, 255);
    analogWrite(BIN2, 255);
    
  } else if (GamePad.isSelectPressed()){
    //Cambia de velocidad
    if(valorPWMLlantas == 255){
      valorPWMLlantas = 200;  
    }else{
      valorPWMLlantas = 255;
    }
    
  } else {
    //Reinicia el valor de los motores cuando no se utilizan
    analogWrite(AIN1, 0);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, 0);
  }
}
