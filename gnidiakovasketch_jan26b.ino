#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HTU21DF.h>
#include <LiquidCrystal_I2C.h>

// Inicializácia HTU21D
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

// Inicializácia LCD (adresa I2C je zvyčajne 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Inicializácia senzora HTU21D
  if (!htu.begin()) {
    Serial.println("HTU21D senzor sa nepodarilo inicializovať!");
    while (1);
  }

  // Inicializácia LCD displeja (16 stĺpcov, 2 riadky, 5x8 bodová mriežka)
  lcd.begin(16, 2, LCD_5x8DOTS); // Explicitne zadávame tri parametre
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializacia...");
  delay(2000);
}

void loop() {
  // Čítanie teploty a vlhkosti
  float teplota = htu.readTemperature();
  float vlhkost = htu.readHumidity();

  // Výpis na sériový monitor
  Serial.print("Teplota: ");
  Serial.print(teplota);
  Serial.println(" °C");
  Serial.print("Vlhkosť: ");
  Serial.print(vlhkost);
  Serial.println(" %");

  // Zobrazenie údajov na LCD displeji
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(teplota);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(vlhkost);
  lcd.print(" %");

  delay(2000); // Aktualizácia každé 2 sekundy
}
