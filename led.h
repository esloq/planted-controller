

#ifndef __LED_H__
#define __LED_H__

#include <ShiftRegister74HC595.h>

// Definitions for LED display (via shift register)
#define COUNTER_LEDS 5
#define SR_CLK_PIN 4
#define SR_DATA_PIN 5
#define SR_LATCH_PIN 6
#define SR_BLUE_LED_PIN 0
#define SR_GREEN_LED_PIN 1
#define SR_RED_LED_PIN 2
#define SR_FIRST_COUNTER_LED_PIN 3
#define SR_LAST_COUNTER_LED_PIN 7

ShiftRegister74HC595<1> led_shift_register(SR_DATA_PIN, SR_CLK_PIN, SR_LATCH_PIN);

void no_color_led() {
  led_shift_register.setNoUpdate(SR_RED_LED_PIN, LOW);
  led_shift_register.setNoUpdate(SR_GREEN_LED_PIN, LOW);
  led_shift_register.setNoUpdate(SR_BLUE_LED_PIN, LOW);
  led_shift_register.updateRegisters();
}

void white_led() {
  led_shift_register.setNoUpdate(SR_RED_LED_PIN, HIGH);
  led_shift_register.setNoUpdate(SR_GREEN_LED_PIN, HIGH);
  led_shift_register.setNoUpdate(SR_BLUE_LED_PIN, HIGH);
  led_shift_register.updateRegisters();
}

void red_led() {
  led_shift_register.setNoUpdate(SR_RED_LED_PIN, HIGH);
  led_shift_register.setNoUpdate(SR_GREEN_LED_PIN, LOW);
  led_shift_register.setNoUpdate(SR_BLUE_LED_PIN, LOW);
  led_shift_register.updateRegisters();
}

void green_led() {
  led_shift_register.setNoUpdate(SR_RED_LED_PIN, LOW);
  led_shift_register.setNoUpdate(SR_GREEN_LED_PIN, HIGH);
  led_shift_register.setNoUpdate(SR_BLUE_LED_PIN, LOW);
  led_shift_register.updateRegisters();
}

void blue_led() {
  led_shift_register.setNoUpdate(SR_RED_LED_PIN, LOW);
  led_shift_register.setNoUpdate(SR_GREEN_LED_PIN, LOW);
  led_shift_register.setNoUpdate(SR_BLUE_LED_PIN, HIGH);
  led_shift_register.updateRegisters();
}

void led_counter(float number) {
  int counters = round(number/2.0);
  if (counters > 5) {
    counters = 5;
  }
  for(int i=SR_FIRST_COUNTER_LED_PIN;i <= SR_LAST_COUNTER_LED_PIN;i++) {
    led_shift_register.set(i, LOW);
  }
  delay(50);
  for(int i=SR_FIRST_COUNTER_LED_PIN;i < counters+SR_FIRST_COUNTER_LED_PIN;i++) {
    led_shift_register.set(i, HIGH);
  }
}

void led_display_ph(float ph) {
  int ph_integer = ph;
  no_color_led();
  if (ph_integer == 5) {
    white_led();
  }
  if (ph_integer == 6) {
    red_led();
  }
  if (ph_integer == 7) {
    green_led();
  }
  if (ph_integer == 8) {
    blue_led();
  }
  led_counter((ph - (float) ph_integer) * 10.0);
}

void led_display_setup() {
  led_shift_register.setAllLow();
  delay(1000);
  for(int i=0;i <= 10;i++) {
    led_counter(i);
    delay(200);
  }
  led_shift_register.setAllLow();
  red_led();
  delay(300);
  green_led();
  delay(300);
  blue_led();
  delay(300);
  white_led();
  delay(300);
  led_shift_register.setAllLow();
}

void led_error() {
  // flash lights on error
  for(int i=0;i<5;i++) {
    led_shift_register.setAllHigh();
    delay(100);
    led_shift_register.setAllLow();
    delay(100);
  }
}

#endif
