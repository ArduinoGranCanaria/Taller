/*
 * Controlar varios LEDs con bucles for.
 * 2013. Arduino Gran Canaria.
 */

// Inicializacion de variables
// Definir las variables de los 3 pines
int pinInicial = 10;
int pinFinal = 8;

// Inicializacion del sistema
void setup() {
  // Inicializar todos los pines para modo de escritura digital
  for (int pin = pinInicial; pin >= pinFinal; pin--) {
    pinMode(pin, OUTPUT);
  }
}

// Bucle
void loop() {
  for (int pin = pinInicial; pin >= pinFinal; pin--) {
    // Encendemos el pin
    digitalWrite(pin, HIGH);
    // Pausa
    delay(500);
    // Apagamos el pin
    digitalWrite(pin, LOW);
  }
}
