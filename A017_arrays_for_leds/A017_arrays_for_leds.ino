/*
 * Uso de matrices (arrays) para controlar 5 LEDs (D2 a D6).
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
// Declarar una matriz de 5 elementos
int matriz[2][5] =
  {
    {2, 3, 4, 5, 6},
    {6, 5, 4, 3, 2},
  };

int elementos = 5;
int contador;
int fila, columna;
int anterior = -1;

// Inicializacion del sistema
void setup()
{
  // Inicializar la biblioteca Serial
  Serial.begin(9600);
  // Inicializar los pines de los LEDs en modo escritura
  for (contador = 2; contador < 6; contador++)
  {
    pinMode(contador, OUTPUT);
  }
}

// Bucle principal
void loop()
{
  // Bucle
  for (fila = 0; fila < 2; fila++)
  {
    for (columna = 0; columna < 5; columna++)
    {
      int led = matriz[fila][columna];
      // Encender LED
      digitalWrite(led, HIGH);
      // Pausa
      delay(250);
      // Apagar LED
      if (anterior >= 0) {
        digitalWrite(anterior, LOW);
      }
      // Indicamos que LED hay que apagar en el siguiente paso
      anterior = led;
    } // Final for columna
  } // Final for fila
  
} // Final de loop