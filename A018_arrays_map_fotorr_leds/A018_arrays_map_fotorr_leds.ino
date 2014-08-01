/*
 * Fotometro. Utilizacion de fotorresistencia para mostrar la cantidad de luz.
 * Si hay mucha luz, se encenderan todos los 5 LEDs (D2-D6).
 * 2013. Arduino Gran Canaria.
 */

// Inicializacion de variables
// Matriz de LEDs
int matriz[5] = {2,3,4,5,6};
// Contador
int c;
// Valor de la fotorresistencia
int fotor;
// Pin fotorresistencia
int pinFotor = 0;
// Nivel de brillo
int nivel;

// Inicializacion del sistema
void setup() {
  // Inicializacion de pines de los LEDs
  for (c = 0; c < 5; c++) {
    pinMode(matriz[c], OUTPUT);  
  }
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Lectura de la fotorresistencia
  fotor = analogRead(pinFotor);
  // Convertimos el rango [0,1023] a [-1,5]
  nivel = map(fotor, 0, 1023, -1, 5);
  // Recorremos los pines de los LEDs y activamos/desactivamos los adecuados
  for (c = 0; c < 5; c++) {
    // Comprobar si el LED debe encenderse
    if (c <= nivel) {
      // Encendemos el LED
      digitalWrite(matriz[c], HIGH);
    } else {
      // Apagamos el LED
      digitalWrite(matriz[c], LOW);
    } // Fin if-else
  } // Fin for
  delay(100);
} // Fin loop
