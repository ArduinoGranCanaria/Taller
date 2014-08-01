/*
 * Controlar el apagado y encendido de 5 LEDs simultaneamente (D2-D6).
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
// Declarar una matriz de 5 elementos
int led[5] = {2,3,4,5,6};

int estado[4][5] =
  {
    {HIGH, LOW, LOW, LOW, HIGH},
    {HIGH, HIGH, LOW, HIGH, HIGH},
    {HIGH, HIGH, HIGH, HIGH, HIGH},
    {HIGH, HIGH, LOW, HIGH, HIGH},
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
  for (fila = 0; fila < 4; fila++)
  {
    for (columna = 0; columna < 5; columna++)
    {
      // Encender LED
      digitalWrite(led[columna], estado[fila][columna]);
    } // Final for columna
    // Pausa
    delay(250);
  } // Final for fila
} // Final de loop
