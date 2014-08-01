/*
 * Controlar brillo del LED con analogWrite y bucles for.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
int pinLed = 9; // Pin PWM (~)
int pausa = 20;

byte brillo = 255;

// Inicializacion del sistema
void setup() {
  // Inicializar el pin del LED para escritura en modo digital
  pinMode(pinLed, OUTPUT);
}

// Bucle
void loop() {
  // Apagamos el LED
  for (byte brillo = 255; brillo > 0; brillo--) {
    // Indicar la intensidad del LED
    analogWrite(pinLed, brillo);
    // Pausa
    delay(pausa);
  } // Cierra for
  
  // Encendemos el LED
  for (byte brillo = 0; brillo < 255; brillo++) {
    // Indicar la intensidad del LED
    analogWrite(pinLed, brillo);
    // Pausa
    delay(pausa);
  } // Cierra for
} // Cierra loop()

