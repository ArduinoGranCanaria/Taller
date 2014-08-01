/*
 * Proyecto: Girasol. Seguidor de fuente de luz mediante una fotorresistencia.
 * 2014. Arduino Gran Canaria
 */

// Importacion de librerias
#include <Servo.h>

// Inicializacion de variables 
#define pinServo 8
#define pinFoto 0
#define paso 10

Servo servo; // Variable (objeto) para el servo
int posServo = 90; // Posicion del servo
int valorIzquierda; // Medida de la fotorresistencia izquierda
int valorDerecha;  // Medida de la fotorresistencia derecha

// Inicializacion del sistema
void setup() {
  // Inicializar Serial
  Serial.begin(9600);
  // Inicializar el servo
  servo.attach(pinServo);
}

// Bucle principal
void loop() {
  // Vamos a posServo - paso
  servo.write(posServo - paso);
  // Leemos valor de la fotorresistencia (valorIzquierda)
  valorIzquierda = analogRead(pinServo);
  // Pausa
  delay(1000);
  // Vamos a posServo + paso
  servo.write(posServo + paso);
  // Leemos valor de la fotorresistencia (valorDerecha)
  valorDerecha = analogRead(pinServo);
  // Pausa
  delay(1000);
  Serial.println("vI: " + String(valorIzquierda) + " vD:" + String(valorDerecha));
  // Si valorIzquierda > valorDerecha
  if (valorIzquierda > valorDerecha) {
    // Aumentamos posServo
    posServo += paso / 2;
    Serial.println("Ir a (i):" + String(posServo));
  } else if (valorDerecha > valorIzquierda) {
    // Si valorDerecha > valorIzquierda
    // Disminuimos posServo
    posServo -= paso / 2;
    Serial.println("Ir a (d):" + String(posServo));
  }
}

