/*
 * Lectura de temperatura y humedad con el sensor DHT-22.
 * 2014. Arduino Gran Canaria.
 */

// Declaracion de variables
#include "DHT.h"

DHT dht(2, DHT22); // pin, tipo

// Iniciacion del sistema
void setup() {
  // Inicializacion de la comunicacion Serial
  Serial.begin(9600);
  // Inicializacion del sensor de temperatura y humedad
  dht.begin();
}

// Bucle principal
void loop() {
  // Leer temperatura y humedad
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Mostrar datos en monitor Serial
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");

  // Pausa
  delay(500);
}
