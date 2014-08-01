/*
 * Controlar LED con condicional (if).
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
int pinLed = 13;
int pausa = 5000;

char contador = 0;

// Inicializacion del sistema
void setup() {
  // Inicializar el pin del LED para escritura en modo digital
  pinMode(pinLed, OUTPUT);
}

// Bucle
void loop() {
  // Control de longitud de la pausa
  if (contador < 3) {
    pausa = 3000;
  } else {
    pausa = 1000;
  }
  // Encender el LED
  digitalWrite(pinLed, HIGH);
  // Pausa
  delay(pausa);
  // Apagamos el LED
  digitalWrite(pinLed, LOW);
  // Pausa
  delay(pausa);
  // Aumentar contador
  contador = contador + 1;
}
