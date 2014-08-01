/*
 * Control de brillo de LED con potenciometro.
 * 2014. Arduino Gran Canaria.
 */

// Declaracion de variables
int pinPotenciometro = 0; // Declarar el pin de lectura del potenciometro
int pinLed = 3; // Pin del LED. PWM (~)
int valor; // Declarar variable lectura del potenciometro 
int brillo; // Declarar variable del brillo

// Inicializacion del sistema
void setup() {
  // Inicializar la biblioteca Serial
  Serial.begin(9600);
  // Inicializar pin del LED como escritura (necesita PWM)
  pinMode(pinLed, OUTPUT);
}

// Bucle principal
void loop() {
  // Obtener el valor del potenciometro
  valor = analogRead(pinPotenciometro);
  // Conversion a brillo
  brillo = valor / 1023.0 * 255.0;
  // Establecer brillo del LED
  analogWrite(pinLed, brillo);
  // Imprimir en Serial el valor del potenciometro
  Serial.println(brillo);
}
