/*
 * Comunicacion con dos Arduinos. Biblioteca Wire.
 * ESCLAVO. Usar en conjuncion con el maestro.
 */

#include <Wire.h>
int dirEsclavo = 4;

// Inicializacion del sistema
void setup() {
  // Inicializa modo esclavo. Direccion = 4
  Wire.begin(dirEsclavo);
  // Registra funcion para recibir datos
  Wire.onReceive(receiveEvent);
  // Inicializa monitor serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Pausa
  delay(100);
}

// Evento de recepcion de datos
void receiveEvent(int numBytes) {
  while(Wire.available()) // Datos disponibles?
  {
    char c = Wire.read(); // Leer
    Serial.print(c); // Mostrar
  }
  Serial.println();
}

