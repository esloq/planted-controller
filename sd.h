

#ifndef __SD_LOG_H__
#define __SD_LOG_H__

#include <SPI.h>
#include <SD.h>

// Definitions for SD card storage
#define SD_CARD_CS_PIN 10
#define SD_PH_LOG_FILENAME "PHLOG.TXT"
#define SD_PH_LOG_BUFFER_SIZE 25

String ph_log_lines[SD_PH_LOG_BUFFER_SIZE];
int ph_log_curr_line = 0;

void sd_ph_log_save() {
  if (SD.begin(SD_CARD_CS_PIN)) {
    File ph_log_file = SD.open(SD_PH_LOG_FILENAME, FILE_WRITE);
    if (ph_log_file) {
      for (int i=0;i<SD_PH_LOG_BUFFER_SIZE;i++) {
        ph_log_file.println(ph_log_lines[i]);
      }
      ph_log_file.close();
    }
    SD.end();
  }
}

void sd_ph_log(float ph) {
  ph_log_lines[ph_log_curr_line] = String(ph);
  ph_log_curr_line++;
  if(ph_log_curr_line >= SD_PH_LOG_BUFFER_SIZE) {
    sd_ph_log_save();
    ph_log_curr_line=0;
  }
}

#endif
