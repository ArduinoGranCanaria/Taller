/*
 * Lectura del estado de un pulsador.
 * 2013. Arduino Gran Canaria.
 */

// Definicion de variables
int pinPulsador = 13; // Pin a utilizar
int estadoPulsador; // Estado del pulsador

// Inicializacion del sistema
void setup() {
  // Activar el pin para lectura
  pinMode(pinPulsador, INPUT);
  // Activaremos la comunicacion Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Lectura del estado del pin
  estadoPulsador = digitalRead(pinBoton);  
  // Imprimir el estado del pin en Serial
  Serial.println(estadoPulsador);
}
