/*
 * Bucles con while.
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables
String cadena;

// Inicializacion del sistema
void setup() {
  // Inicializar el monitor Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Esperamos a que hayan datos disponibles en Serial
  while (!Serial.available()) {
    // Imprimimos en pantalla "no hay datos"
    Serial.println("Dame una galleta");
    // Pausa
    delay(1000);
  }
  // Leer Serial
  cadena = Serial.readString();
  // Imprimir en pantalla
  Serial.println(cadena);
  // Comprobar si me han dado una galleta
  if (cadena == "galleta") {
    Serial.println("GRRAAACCIIIAAASS :-D");
  } else {
    Serial.println("MUY MAL: ESO NO ES UNA GALLETA");
  }
  delay(1000);
}
