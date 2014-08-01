/* Lectura de estado de un potenciometro */

// Declaracion de variables
int pinPotenciometro = 0; // Declarar el pin de lectura del potenciometro
int valor; // Declarar variable lectura del potenciometro 
float voltaje; // Declarar vaiable del voltaje

// Inicializacion del sistema
void setup() {
  // Inicializar la biblioteca Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Obtener el valor del potenciometro
  valor = analogRead(pinPotenciometro);
  // Conversion a voltaje
  voltaje = valor / 1023.0 * 5.0; 
  // Imprimir en Serial el valor del potenciometro
  Serial.println(voltaje, 3);
}
