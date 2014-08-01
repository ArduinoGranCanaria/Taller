/*
 * Lectura de fotorresistencia/sensor de temperatura. Si el voltaje leido es
 * menor de 0.5V, se enciende un LED de alarma. Si es mayor de 0.5V, el LED
 * permanece apagado.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
int pinResistencia = 0; // Fotorresistencia/sensor de temperatura
int pinLed = 11;
int medida;
int brillo;
float voltaje;

// Inicializacion del sistema
void setup() {
  // Inicializar el monitor
  Serial.begin(9600);
  // Inicializacion del pin del LED
  pinMode(pinLed, OUTPUT);
}

// Bucle principal
void loop() {
  // Lectura del pin 0
  medida = analogRead(pinResistencia);
  // Conversion a voltaje
  voltaje = medida / 1023.0 * 5.0;
  // Mostrar voltaje en el monitor
  Serial.print(voltaje);
  // Controlar LED
  Serial.println(brillo);
  if (voltaje < 0.5) {
    analogWrite(pinLed, 254);
  } else {
    analogWrite(pinLed, 0);
  }
}
