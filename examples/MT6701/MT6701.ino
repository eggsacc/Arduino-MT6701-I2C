/*
 * Setup & usage of MT6701 library.
 * Reads encoder and prints the output in a variety of formats.
 */

#include <MT6701.h>

// create encoder object
MT6701 encoder;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  encoder.initEncoder(); // run init sequence
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // raw 14-bit sensor reading (0-16383), without startup zeroing
  int rawAngle = encoder.getRawAngle();

  // absolute angle in radians (0-2pi)
  float absoluteRadians = encoder.getAbsoluteAngleRadians();

  // absolute angle in degrees (0-360)
  float absoluteDegrees = encoder.getAbsoluteAngleDegrees();

  // total angle in radians
  float totalRadians = encoder.getTotalAngleRadians();

  // total angle in degrees
  float totalDegrees = encoder.getTotalAngleDegrees();
  
  Serial.print("Raw: ");
  Serial.print(rawAngle);
  Serial.print("   abs-rad: ");
  Serial.print(absoluteRadians);
  Serial.print("   abs-deg: ");
  Serial.print(absoluteDegrees);
  Serial.print("   total-rad: ");
  Serial.print(totalRadians);
  Serial.print("   total-deg: ");
  Serial.println(totalDegrees);

  // delay to prevent flooding serial port
  delay(50);

}