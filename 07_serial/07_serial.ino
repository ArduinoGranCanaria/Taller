/* Leer el voltaje y mostrarlo en el monitor serie.
 * 2013. Arduino Gran Canaria.
 */

// Inicializacion de variables
int valor;
float voltaje;

// Inicializacion del sistema
void setup() {
  // Inicializar la comunicacion serie
  Serial.begin(9600);
  Serial.println("Hola mundo");
}

// Bucle
void loop() { 
  // Leer el pin analogico 0
  valor = analogRead(0);
  
  // Calculo del voltaje
  voltaje = valor * 5 / 1023.0;
  
  // Mostrar el voltaje
  Serial.println(voltaje);
}
