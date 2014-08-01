/* Encender y apagar un LED mediante un pulsador */

// Definicion de variables
int pinPulsador = 13; // Pin a utilizar
int pinLed = 12; // Pin del LED
int estadoPulsador; // Estado del pulsador
int estadoAnterior = -1;
int estadoLed = 0; // Estado del LED (encendido o apagado)

// Inicializacion del sistema
void setup() {
  // Activar el pin para lectura
  pinMode(pinPulsador, INPUT);
  // Activar el pin del LED para escritura
  pinMode(pinLed, OUTPUT);
  // Activaremos la comunicacion Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  // Lectura del estado del pin
  estadoPulsador = digitalRead(pinBoton);
  if (estadoPulsador != estadoAnterior) {
    if (estadoPulsador == LOW) {
      // Cambiar el estado del Led
      if (estadoLed == HIGH) {
        estadoLed = LOW;
      } else {
        estadoLed = HIGH;
      }
      digitalWrite(pinLed, estadoLed);
    }
    // Logica de encendido y apagado
    estadoAnterior = estadoPulsador;
  }
}
