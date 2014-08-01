/*
 * "Multitarea" con funcion millis.
 * 2013. Arduino Gran Canaria.
 */
 
unsigned long m = 0;
unsigned long dif_pio = 1000;
unsigned long dif_dellos = 2300;
unsigned long prev_pio = 0;
unsigned long prev_dellos = 0;

// Inicializacion del sistema
void setup(){
 // Inicializacion del monitor Serial
  Serial.begin(9600);
}

// Bucle principal
void loop() {
  m = millis();
  // Si han pasado dif_pio milisegundos, mostrar mensaje 1
  if (m - prev_pio > dif_pio) {
    Serial.println("Pio, pio");
    prev_pio = m;
  }
  // Si han pasado dif_dellos milisegundos, mostrar mensaje 2
  if (m - prev_dellos > dif_dellos) {
    Serial.println("Arriba d'ellos");
    prev_dellos = m;
  }
}

