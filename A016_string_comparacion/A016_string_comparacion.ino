/*
 * Comparacion de dos cadenas.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
String cadena = "Hola";

// Inicializacion del sistema
void setup() {
  // Inicializacion de la comunicacion Serial
  Serial.begin(9600);
  // Comparacion
  if (cadena == "Hola") {
    Serial.println("iguales");
  }
}

// Bucle principal
void loop() {
}
