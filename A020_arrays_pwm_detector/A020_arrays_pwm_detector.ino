/*
 * Detector de modulacion por ancho de pulso. Se utiliza un pin digital para
 * leer el valor de otro pin de tipo modulacion por ancho de pulso (PWM).
 * 2014. Arduino Gran Canaria.
 */

// Definicion de variables
#define elementos 10

int pin_in = 7; // Pin de lectura
int pin_out = 11; // Pin de escritura PWM (~)

int estado[elementos];
long tiempo[elementos];

// Inicializacion del sistema
void setup() {
  Serial.begin(9600); // Inicializacion de la biblioteca Serial
  
  pinMode(pin_in, INPUT); // Pin 7, lectura
  pinMode(pin_out, OUTPUT); // Pin 11 (PWM), escritura

  // Establece el estado del pin de escritura
  // Ojo: No puede ser 255 ni 0
  analogWrite(pin_out, 127);

  // Lectura del estado inicial  
  estado[0] = digitalRead(pin_in);
  tiempo[0] = micros();

  // Detectar n cambios de estado del pin (HIGH->LOW->HIGH...)  
  for (int n = 1; n < elementos; n++) {
    do {
      estado[n] = digitalRead(pin_in);
    } while (estado[n] == estado[n-1]);
    tiempo[n] = micros();
  }

  // Mostrar los n cambios de estado en el monitor Serial
  for (int i = 0; i < elementos; i++) {
    String valor = String(i) + " pin:" + String(estado[i]) + " t:" + String(tiempo[i]);
    if (i > 0) valor = valor + " dif_t:" + String(tiempo[i] - tiempo[i-1]);
    Serial.println(valor); 
  }  
}

void loop() {
  // put your main code here, to run repeatedly: 
}
