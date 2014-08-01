/*
 * Botones LCD: Mostrar en pantalla el boton pulsado. Necesita la mochila
 * LCD 1602 con teclado (keypad).
 * 2014. Arduino Gran Canaria.
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int codigo;

// Ninguno: 1023
// SELECT: 720-640     < 800
// LEFT: 477-479-410   < 600
// DOWN: 304-305-258   < 400
// UP: 130-131-128-101 < 200
// RIGHT: 0            = 0

// Inicializacion del sistema
void setup() {
  // Inicializar la pantalla (LCD)
  lcd.begin(16, 2); // LCD 1602
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pres. un boton");
}

// Bucle principal
void loop() {
  // Lectura del pin analogico 0 (botonera)
  codigo = analogRead(0);
  if (codigo == 0) {
    mostrarTecla("RIGHT");
  } else if (codigo < 200) {
    mostrarTecla("UP");
  } else if (codigo < 400) {
    mostrarTecla("DOWN");
  } else if (codigo < 600) {
    mostrarTecla("LEFT");
  } else if (codigo < 800) {
    mostrarTecla("SELECT");
  }
}

void mostrarTecla(String tecla) {
  // Borrar el espacio de pantalla donde
  // aparece el boton pulsado
  lcd.setCursor(0, 1);
  lcd.print("      ");
  // Mostrar el boton pulsado
  lcd.setCursor(0, 1);
  lcd.print(tecla);
}
