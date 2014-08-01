/* 
 * Control de LEDs con digitalWrite y delay.
 * 2013. Arduino Gran Canaria.
 */
// Declaracion de variables


// Inicializacion del sistema
void setup() {
  // Activar un pin para escritura
  pinMode(13, OUTPUT);
}

// Bucle principal
void loop() {
  // Encender el LED 
  digitalWrite(13, HIGH);
  // Pausa (5 segundos)
  delay(5000);
  // Apagar el LED
  digitalWrite(13, LOW);  
  // Pausa (5 segundos)
  delay(5000);
}
