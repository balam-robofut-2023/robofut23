#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <analogWrite.h>


//Definición de pines
#define AIN1 18
#define AIN2 4
#define BIN1 27
#define BIN2 14

//Declaración de variables
const int valorMinPWM = 150;
const int valorMaxPWM = 255;
int tiempoPruebas = 100;
int newpwm = 0;

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
  //-------------- Variables para obtener los datos del joystick --------------
  //Obtiene el radio del joystick, 0 < r < 7
  int radio = GamePad.getRadius();

  //Obtiene el ángulo del joystick, 0 < a < 360
  int angle = GamePad.getAngle();

  //Calcula el pwm dependiendo del radio del joystick
  int pwm = map(radio, 0, 7, valorMinPWM, valorMaxPWM);

  //Obtiene la posición de y y de x del joystick
  int joystickX = GamePad.getXaxisData();
  int joystickY = GamePad.getYaxisData();
  int quadrant = getQuadrant(angle, radio, pwm);

                 //-------------- Condiciones para el funcionamiento de los motores --------------
  if (quadrant == 1) {
    //Giro en el primer cuadrante
    analogWrite(AIN1, pwm);
    digitalWrite(AIN2, LOW);
    analogWrite(BIN1, newpwm);
    digitalWrite(BIN2, LOW);

  } else if (quadrant == 2) {
    //Giro en el segundo cuadrante
    analogWrite(AIN1, newpwm);
    digitalWrite(AIN2, LOW);
    analogWrite(BIN1, pwm);
    digitalWrite(BIN2, LOW);

  } else if (quadrant == 3) {
    //Giro en el tercer cuadrante
    digitalWrite(AIN1, LOW);
    analogWrite(AIN2, newpwm);
    digitalWrite(BIN1, LOW);
    analogWrite(BIN2, pwm);

  } else if (quadrant == 4) {
    //Giro en el cuarto cuadrante
    digitalWrite(AIN1, LOW);
    analogWrite(AIN2, pwm);
    digitalWrite(BIN1, LOW);
    analogWrite(BIN2, newpwm);

  } else if (joystickY > 0 && joystickX == 0) {
    //Mover hacia adelante
    analogWrite(AIN1, pwm);
    digitalWrite(AIN2, LOW);
    analogWrite(BIN1, pwm);
    digitalWrite(BIN2, LOW);

  } else if (joystickY < 0 && joystickX == 0) {
    //Mover hacia atrás
    digitalWrite(AIN1, LOW);
    analogWrite(AIN2, pwm);
    digitalWrite(BIN1, LOW);
    analogWrite(BIN2, pwm);

  }  else if (joystickX > 0 && joystickY == 0) {
    //Giro completo hacia la derecha
    analogWrite(AIN1, pwm);
    digitalWrite(AIN2, LOW);
    analogWrite(BIN1, pwm * 0.7);
    digitalWrite(BIN2, LOW);

  } else if (joystickX < 0 && joystickY == 0) {
    //Giro completo hacia la izquierda
    analogWrite(AIN1, pwm * 0.7);
    digitalWrite(AIN2, LOW);
    analogWrite(BIN1, pwm);
    digitalWrite(BIN2, LOW);

  } else if (GamePad.isTrianglePressed()) {
    //Frena rápidamente
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255);
    analogWrite(BIN1, 255);
    analogWrite(BIN2, 255);

  } else {
    //Reinicia el valor de los motores cuando no se utilizan
    analogWrite(AIN1, 0);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, 0);
  }
}

//Función que devuelve según el ángulo en que cuadrante está y asigma un pwm para los giros
int getQuadrant(int angle, int radio, int pwm) {
  int maxAngle = 0;
  int minAngle = 0;
  int quadrant = 0;
  if (radio > 0) {
    if (angle < 80 &&  angle > 10) {
      maxAngle = 10;
      minAngle = 80;
      quadrant = 1;
    } else if (angle < 170 && angle > 100) {
      maxAngle = 100;
      minAngle = 170;
      quadrant = 2;
    } else if (angle < 260 && angle > 190) {
      maxAngle = 190;
      minAngle = 260;
      quadrant = 3;
    } else if (angle < 350 && angle > 280 ) {
      maxAngle = 280;
      minAngle = 350;
      quadrant = 4;
    }
  }
  newpwm = map(angle, maxAngle, minAngle, valorMinPWM, pwm);
  return quadrant;
}
