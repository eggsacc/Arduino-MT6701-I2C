/*
 * Setup & usage of MT6701 library.
 * Reads encoder and prints the output in a variety of formats.
 */

#include <MT6701.h>

#define DIRECTION 1
#define ZERO_ENCODER 0

// create encoder object
MT6701 encoder(DIRECTION, ZERO_ENCODER);

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
  float absoluteRadians = encoder.getAbsoluteAngle();

  // absolute angle in degrees (0-360)
  float absoluteDegrees = encoder.getAbsoluteAngleDegrees();

  // total angle in radians
  float totalRadians = encoder.getAngle();

  // total angle in degrees
  float totalDegrees = encoder.getAngleDegrees();
  
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