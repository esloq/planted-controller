

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <DateTime.h>
#include <DS323x.h>

DS323x rtc;

void clock_setup(){
    Wire.begin();
    delay(2000);
    rtc.attach(Wire);
    // Set onboard time if needed.
    // rtc.now(DateTime(2021, 04, 03, 11, 24, 00));
}


void clock_test() {
    DateTime now = rtc.now();
    Serial.println(now.timestamp());
    delay(1000);
}

String clock_timestamp() {
  DateTime now = rtc.now();
  return now.timestamp();
}
#endif
