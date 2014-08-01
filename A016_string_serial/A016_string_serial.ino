/*
 * Uso de la clase String para leer cadenas con comunicacion Serial.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
String cadena; // Variable de tipo String para leer de Serial
int pin = 13;

// Incializacion del sistema
void setup() {
  // Inicializar Serial
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
}

// Bucle principal
void loop() {
  // Leer cadena desde Serial
  if (Serial.available()) {
    // Imprimir cadena en Serial
    cadena = Serial.readString();
    if (cadena == "encendido") {
      digitalWrite(pin,HIGH);
    }
    else {
      digitalWrite(pin,LOW);
    }
  }
}
