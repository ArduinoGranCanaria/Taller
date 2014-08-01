/*
 * Optoacoplador 4N35. Control de LED.
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables
#define pinLed 13

// Inicializacion del sistema
void setup() {
  // Inicializacion de pinLed
  pinMode(pinLed, OUTPUT);
}

void loop() {
  // Activar pinLed
  digitalWrite(pinLed, HIGH);
  // Pausa
  delay(1000);
  // Desactivar pinLed
  digitalWrite(pinLed, LOW);
  // Pausa
  delay(1000);
}
