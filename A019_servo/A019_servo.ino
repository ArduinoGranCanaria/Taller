/*
 * Uso basico de la clase Servo.
 * 2014. Arduino Gran Canaria.
 */

// Importacion de librerias
#include <Servo.h>

// Inicializacion de variables 
int pinServo = 9; // Pin digital para el servo
Servo servo; // Variable (objeto) para el servo

// Inicializacion del sistema
void setup() {
  // Inicializar el servo
  servo.attach(pinServo);
  // Indicamos una posicion de inicio para el servo
  servo.write(90);
}

// Bucle principal
void loop() {
}

