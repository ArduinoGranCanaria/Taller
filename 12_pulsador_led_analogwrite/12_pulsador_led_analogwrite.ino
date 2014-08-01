/* LED + pulsador, con contador de encendidos.
   En cada encendido se incrementa el brillo del LED.
 */

// Definicion de variables
int pinPulsador = 13; // Pin a utilizar
int pinLed = 11; // Pin del LED. PWM (~)
int estadoPulsador; // Estado del pulsador
int estadoAnterior = -1;
int estadoLed = 0; // Estado del LED (encendido o apagado)
int contadorPulsaciones = 0;
int brillo = 0; // Brillo del LED

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
        brillo = brillo + 10;
        analogWrite(pinLed, brillo);
      } else {
        estadoLed = HIGH;
        analogWrite(pinLed, 0);
      }
      // Aumentar el contador y mostrarlo por Serial
      contadorPulsaciones++;
      Serial.println(contadorPulsaciones);
    }
    // Logica de encendido y apagado
    estadoAnterior = estadoPulsador;
  }
}
