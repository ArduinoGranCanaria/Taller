/*
 * Uso de la clase String.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
String cadena = "";
int numero;
char caracter;

// Inicializacion del sistema
void setup() {
  // Inicializacion de la comunicacion Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Leer datos de Serial cuando esten disponibles
  if (Serial.available()) {
    // Convertir cadena leida en un numero
    numero = Serial.parseInt();
    // Crear cadena con el numero
    cadena = "Has escrito el numero: " + String(numero);
    // Mostrar la cadena compuesta
    Serial.println(cadena);
  }
}
