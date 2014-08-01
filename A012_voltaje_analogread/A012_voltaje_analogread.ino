/*
 * Lectura de voltaje. Conversion de lectura digital a voltaje real.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
// Declarar variable del pin a leer
int pinVoltaje = 0;
int analogico;
float voltaje;

// Inicializacion del sistema
void setup() {
  // Inicializar la biblioteca Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Leer el "voltaje" del pin
  analogico = analogRead(pinVoltaje);
  // Convertir la cantidad a voltaje real
  voltaje = analogico / 1023.0 * 5.0 * 9.0 / 0.8;
  // Imprimir el "voltaje" del pin
  Serial.println(voltaje);
}
