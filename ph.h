

#ifndef __PH_H__
#define __PH_H__

#include <math.h>
#include <SoftwareSerial.h>

// Definitions for pH sensor
#define DATA_RATE 9600
#define SAMPLES_TO_TAKE 10  // Averaging samples makes up one reading.
#define SAMPLING_INTERVAL_MS 1000  // 1 seconds
#define READINGS_TO_ALERT 4
#define PH_DATA_BUFFER_LEN 20
#define NL '\r'
#define PH_SENSOR_RX_PIN 2
#define PH_SENSOR_TX_PIN 3

float ph_samples[SAMPLES_TO_TAKE];

SoftwareSerial ph_sensor_connection(PH_SENSOR_RX_PIN, PH_SENSOR_TX_PIN);

void ph_sensor_command(String cmd) {
  ph_sensor_connection.print(cmd + NL);
}

void ph_sensor_quiescence() {
  ph_sensor_command("*OK,0");
  delay(1000);
  ph_sensor_command("c,0");
  delay(1000);
}

void ph_sensor_setup() {
  ph_sensor_connection.begin(DATA_RATE);
  delay(2000); // Wait for sensor to fully boot.
  ph_sensor_quiescence();
}

// ph_sample requests and reads a value from the sensor
float ph_sample() {
  bool ph_string_complete = false;
  String ph_sensor_string = "";
  ph_sensor_string.reserve(30);

  ph_sensor_command("r");
  delay(100);
  while (!ph_string_complete) {
    if (ph_sensor_connection.available() > 0) {
      char inchar = (char)ph_sensor_connection.read();
      ph_sensor_string += inchar;
      if (inchar == NL) {
        ph_string_complete = true;
      }
    }
  }
  Serial.println(ph_sensor_string);
  return ph_sensor_string.toFloat();
}

// ph_read requests and reads a value from the sensor
float ph_read() {
  bool read_error = false;
  for(int i=0; i < SAMPLES_TO_TAKE; i++) {
    float sample = ph_sample();
    if (sample > 0.0) {
      ph_samples[i] = sample;
      delay(SAMPLING_INTERVAL_MS);
    }
    else {  // Continue sampling despite error, this helps stabilize the probe.
      read_error = true;
    }
  }
  if(read_error) {
    return 0.0;
  }
  float sum = 0.0;
  for(int i=0; i < SAMPLES_TO_TAKE; i++) {
    sum += ph_samples[i];     
  }
  return sum / ((float) SAMPLES_TO_TAKE);
}


void ph_handle_low() {
  // TODO
  return;
}

void ph_handle_high() {
  // TODO
  return;
}

#endif
