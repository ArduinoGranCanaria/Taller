/*
 * Uso de la patilla AREF.
 * 2014. Arduino Gran Canaria.
 */

// Inicializacion de variables y constantes
#define pinLectura 2
long valor;
float voltaje;

// Inicializacion del sistema
void setup() {
  // Inicializacion de la biblioteca Serial
  Serial.begin(9600);
  // Utilizar el pin AREF como referencia
  analogReference(INTERNAL);
}

// Bucle principal
void loop() {
  // Leer valor del pin de lectura
  valor = analogRead(pinLectura);
  // Convertir a voltaje
  voltaje = valor * 1.1 / 1023;
  // Mostrar valor en monitor Serial
  Serial.print(valor);
  Serial.print(" ");
  Serial.println(voltaje);
  // Pausa
  delay(500);
}
