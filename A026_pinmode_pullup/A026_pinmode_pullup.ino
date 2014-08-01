/*
 * Ejemplo de pull-up.
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables y constantes
#define pinInterruptor 13
#define pinLed 5
int estado;

// Inicializacion del sistema
void setup() {
  // Inicializar el pin del interruptor para entrada
  pinMode(pinInterruptor, INPUT);
  // Modo pull-up
  digitalWrite(pinInterruptor, HIGH);
  // Inicializar el pin del LED para salida
  pinMode(pinLed, OUTPUT);
}

// Bucle principal
void loop() {
  // Leer estado del interruptor
  estado = digitalRead(pinInterruptor);
  // Establecer estado del interruptor en el LED
  digitalWrite(pinLed, estado);
}


