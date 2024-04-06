/*
  audible_uv_meter.ino

  An audible UV meter application for a Seeed Studio Wio Terminal
  and a GUVA-S12SD analog UV sensor ...

  Git repository: https://github.com/dxcfl/audible_uv_meter
*/

// #define DEBUG 1
#include "debug2serial.h"

/* Display
*/

// Comment the following line to disable the usage of the TFT display
#define USE_TFT_DISPLAY 1

#ifdef USE_TFT_DISPLAY
#include "aum_display.cpp"

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *dsc)
{
  DEBUG_SERIAL_PRINTF("%s@%d->%s\r\n", file, line, dsc);
  delay(100);
}
#endif
#endif

/* INCLUDES
*/

// - GUVA-S12SD UV Sensor Library: https://github.com/dxcfl/arduino-library-GUVA_S12SD
#include "GUVA_S12SD.h"

/* GLOBALS
*/

// Miscellaneous
#define BUZZER_PIN WIO_BUZZER
#define KEY_PIN WIO_KEY_A

// Sensors
#define GUVA_S12SD_PIN 0       // Analog pin connected to the UV sensor
#define GUVA_S12SD_VOLTAGE 3.3 // Reference voltage for the UV sensor (usually same as board supply voltage)
GUVA_S12SD guva_s12sd(GUVA_S12SD_PIN, GUVA_S12SD_VOLTAGE);

/* SETUP
*/

void setup()
{
  DEBUG_SERIAL_INIT(115200);
  DEBUG_SERIAL_PRINTLN("SETUP: Initialization ...");
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(KEY_PIN, INPUT_PULLUP);

#ifdef USE_TFT_DISPLAY
  DEBUG_SERIAL_PRINTLN("SETUP: Display ...");
  Display::setup();
#if USE_LV_LOG != 0
  lv_log_register_print(my_print); /* register print function for debugging */
#endif
  Display::screen();
  digitalWrite(LCD_BACKLIGHT, LOW);
  DEBUG_SERIAL_PRINTLN("SETUP: Display ready.");
#endif

  DEBUG_SERIAL_PRINTLN("SETUP: GUVA-S12SD UV Sensor ...");
  guva_s12sd.begin();
  DEBUG_SERIAL_PRINTLN("SETUP: GUVA-S12SD initialized.");

  DEBUG_SERIAL_PRINTLN("SETUP: initialized.");

  show(5000); // Show/play UV meter for 5 seconds on startuo ...
}

/* LOOP
*/

void loop()
{
  if (digitalRead(KEY_PIN) == LOW)
  { // Show/play UV meter for 10 seconds when button is pressed ...
    show(10000);
  }
}

/* MISC. ROUTINES
*/

/*
   Take a measurement and show the results for <duration> ms.
   Also play the corresponding tone sequence for the measured UV index.
*/
void show(uint32_t duration)
{
  uint32_t start = millis();

#ifdef USE_TFT_DISPLAY
  DEBUG_SERIAL_PRINTLN("SHOW: Backlight ON ...");
  digitalWrite(LCD_BACKLIGHT, HIGH);
#endif

  while (millis() - start <= duration)
  {
    float uv, uvi = 0;

    DEBUG_SERIAL_PRINTLN("SHOW: GUVA-S12SD: Reading values  ...");
    guva_s12sd.readSensor();
    uv = guva_s12sd.getUvLevel();
    uvi = guva_s12sd.getUvIndex();
    DEBUG_SERIAL_PRINTF("SHOW: GUVA-S12SD: UV reading = %.2f mW/m², UV index = %.1f\n", uv, uvi);

#ifdef USE_TFT_DISPLAY
    DEBUG_SERIAL_PRINTLN("SHOW: Updating display  ...");
    Display::update_labels(uv, uvi);
    Display::update_meter(uvi);
#ifdef DEBUG_VERBOSE
    DEBUG_SERIAL_PRINTLN("SHOW: Display update ...");
#endif
    Display::update();
#endif

    delay(500);

    DEBUG_SERIAL_PRINTLN("SHOW: Play buzzer tones ...");
    buzzerPlayUvIndexMelody((int) (uvi+0.5));
  }

#ifdef USE_TFT_DISPLAY
  DEBUG_SERIAL_PRINTLN("SHOW: Backlight OFF ...");
  digitalWrite(LCD_BACKLIGHT, LOW);
#endif
}

/*
   Play the corresponding tone sequence for the measured UV index on the buzzer:
   C5 (F5){UV index} for an UV index < 6,
   C5 (F5){5} (A5){UV index - 5} for an UV index 6 - 10 and
   C5 (F5){5} (A5){5} C6 for UV index 11 ...
*/
void buzzerPlayUvIndexMelody(int uvi)
{
  buzzerPlayTone(1915, 100); // C5
  delay(100);
  for (int i = 0; i < uvi; i++)
  {
    if ( i < 5 ) {
      buzzerPlayTone(1432, 100); // F5
    } else if ( i < 10 ) {
      buzzerPlayTone(1136, 100); // A5
    } else {
      buzzerPlayTone(1014, 100); // C6
    }
    delay(100);
  }
}

/*
   Play a tone on the buzzer.
*/
void buzzerPlayTone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(tone);
  }
}
