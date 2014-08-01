/*
 * Controlar tres LEDs para aumentar y disminuir el brillo.
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
int pinA = 11; // Pin PWM (~)
int pinB = 10; // Pin PWM (~)
int pinC = 9;  // Pin PWM (~)

int brillo = 0;
int paso = 1;

// Inicializacion del sistema
void setup() {
  // Inicializacion de pines digitales
  pinMode(pinA, OUTPUT);  
  pinMode(pinB, OUTPUT);  
  pinMode(pinC, OUTPUT);
}

// Inicializacion de variables
void loop() {
  // Establecer brillo de los LEDs
  analogWrite(pinA, brillo);
  analogWrite(pinB, brillo;
  analogWrite(pinC, brillo);
  // Pausa
  delay(10);
  // Aumentar o disminuir el brillo
  brillo += paso;
  // Controlar los limites
  if (brillo >= 255 || brillo <= 0) {
    paso = paso * -1;
  }
}

