#include "led.h"
#include "ph.h"
#include "sd.h"

#define PH_READING_INTERVAL_MS 300000  // 5 minutes
#define PH_LOW_VALUE 6.9
#define PH_HIGH_VALUE 8.1

void idle() {
  // TODO: implement circuit energy saving
  return;
}

void active() {
  // TODO: implement circuit energy saving, wake up
  return;
}

void setup() {
  Serial.begin(DATA_RATE);
  delay(300);
  ph_sensor_setup();
  led_display_setup();
  delay(300);
}

void loop() {
  active();

  float ph = ph_read();
  sd_ph_log(ph);
  if (ph == 0) {
    led_error();
  }
  else {
    led_display_ph(ph);
    if (ph <= PH_LOW_VALUE) {
      ph_handle_low();
    }
    if (ph >= PH_HIGH_VALUE) {
      ph_handle_high();
    }
  }

  idle();
  delay(PH_READING_INTERVAL_MS);
}
