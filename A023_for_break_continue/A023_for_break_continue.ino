/*
 * Controles para el bucle "for" (continue, break)
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables
#define maximo 10
int i;

// Inicializacion del sistema
void setup() {
  // Inicializar Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Recorrer desde 0 hasta "maximo"
  for (i = 0; i < maximo; i++) {
    // Imprimir el valor del contador
    Serial.println(i);
    // Salir del bucle "for" cuando el contador valga 5    
    if (i == 5) break;
    if (i >= 5) Serial.println("Has ganado la loteria");
  }
  Serial.println("Me he salido del bucle cuando i valia " + String(i));
  // Pausa
  delay(1000);
}
