/* Demo avanzada: Multitarea con funcion millis */
unsigned long m = 0;
unsigned long dif_pio = 1000;
unsigned long dif_dellos = 2300;
unsigned long prev_pio = 0;
unsigned long prev_dellos = 0;

void setup(){
  Serial.begin(9600);
}
void loop(){
  m = millis();
  if (m - prev_pio > dif_pio) {
    Serial.println("Pio, pio");
    prev_pio = m;
  }
  if (m - prev_dellos > dif_dellos) {
    Serial.println("Arriba d'ellos");
    prev_dellos = m;
  }
}

