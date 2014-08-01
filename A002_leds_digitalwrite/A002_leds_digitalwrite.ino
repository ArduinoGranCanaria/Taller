/*
 * Controlar tres LEDs (encender y apagar)
 * 2013. Arduino Gran Canaria.
 */

// Declaracion de variables
int pinA = 13;
int pinB = 12;
int pinC = 11;

int pause = 100;

// Inicializacion del sistema
void setup() {
  // Inicializacion de pines digitales
  pinMode(pinA, OUTPUT);  
  pinMode(pinB, OUTPUT);  
  pinMode(pinC, OUTPUT);  
}

// Bucle principal
void loop() {
  // Encender el primer led
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  // Pausa
  delay(pause);

  // Encender el segundo led
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  // Pausa
  delay(pause);

  // Encender el tercer led
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  // Pausa
  delay(pause);

  // Pausar
  pause -= 5;
  // Comprobar el limite de la pausa
  if (pause == 0) pause = 100;
}

