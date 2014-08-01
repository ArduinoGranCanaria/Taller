/*
 * Controlar el encendido y apagado de LEDs mediante ordenes leidas por el
 * monitor Serial.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
int pinLED1 = 13; // pin para el LED 1
int pinLED2 = 12; // pin para el LED 2
int pinLED3 = 11; // pin para el LED 3
String cadena; // Cadena de lectura de Serial

// Inicializacion del sistema
void setup() {
  // Activar los pines de los LEDs en modo escritura
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
  // Inicializar el Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Esperar a que haya datos de Serial
  if (Serial.available()) {
    // Cuando haya datos, leemos la cadena
    cadena = Serial.readString();
    Serial.println(cadena);
    // Si la cadena es "encender", encendemos el LED
    if (cadena == "on 1") {
      digitalWrite(pinLED1, HIGH);
    } // cerramos el if on
    if (cadena == "on 2") {
      digitalWrite(pinLED2, HIGH);
    } // cerramos el if on
    if (cadena == "on 3") {
      digitalWrite(pinLED3, HIGH);
    } // cerramos el if on
    // Si la cadena es "apagar", apagamos el LED
    if (cadena == "off 1") {
      digitalWrite(pinLED1, LOW);
    } // cerramos el if off
    // Si la cadena es "apagar", apagamos el LED
    if (cadena == "off 2") {
      digitalWrite(pinLED2, LOW);
    } // cerramos el if off
    // Si la cadena es "apagar", apagamos el LED
    if (cadena == "off 3") {
      digitalWrite(pinLED3, LOW);
    } // cerramos el if off
  } // cerramos el if serial.available
} // cerramos el void loop