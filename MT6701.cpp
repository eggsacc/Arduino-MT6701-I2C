#include "MT6701.h"
#include <Wire.h>

/*
 * A simple library to obtain MT6701 sensor data through i2c.
 * Default i2c address for encoder is 0x06, SDA -> pin A4, SCL -> pin A5.
 * MT6701 datasheet: https://www.lcsc.com/datasheet/lcsc_datasheet_2109011830_Magn-Tek-MT6701CT-STD_C2856764.pdf
 * Reference tutorial for code: https://curiousscientist.tech/blog/as5600-magnetic-position-encoder (Thanks!)
 */

// I2C address
#define I2C_AD 0x06

// determines if angle increments when rotated clockwise or anti-clockwise. set to 1 or -1
#define dir -1

MT6701::MT6701() : lowbyte(0), highbyte(0), rawAngle(0), startAngle(0), correctedRawAngle(0), quadrant(0), prevQuadrant(0), numberOfTurns(0), totalAngle(0) {}

// init: begin I2C comminication, zero starting angle
void MT6701::initEncoder(){
  Wire.begin();
  Wire.setClock(400000L);
  Wire.beginTransmission(I2C_AD);
  while(Wire.endTransmission() != 0); // Blocks until encoder acknowledges i2c request  
  totalAngle = 0;
  numberOfTurns = 0;
  startAngle = getRawAngle(); // zero angle
  // delay(5);
  Serial.println("Encoder initialized!");

}

// get 14-bit raw sensor value
int MT6701::getRawAngle() {

  Wire.beginTransmission(I2C_AD);
  Wire.write(0x03);
  Wire.endTransmission();
  Wire.requestFrom(I2C_AD, 1);
  while(Wire.available() == 0 ); // wait until i2c bus available
  highbyte = Wire.read();

  Wire.beginTransmission(I2C_AD);
  Wire.write(0x04);
  Wire.endTransmission();
  Wire.requestFrom(I2C_AD, 1);
  while(Wire.available() == 0 );
  lowbyte = Wire.read();

  /*
    register 0x03 returns bits <13:6> (highbyte), 
    register 0x04 returns bits <5:0> (lowbyte).

    Bits:            |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  | 

    0x03 (highbyte): |  13 |  12 |  11 |  10 |  9  |  8  |  7  |  6  |
    0x04 (lowbyte):  |  5  |  4  |  3  |  2  |  1  |  0  | N/A | N/A | 

    To join highbyte & lowbyte into 14-bit value, shift highbyte left by 6 & lowbyte right by 2, 
    then join using OR (|) operator
  */

  highbyte <<= 6;
  rawAngle = highbyte | (lowbyte >> 2);

  return rawAngle; // int value 0-16383
}

// constrains raw angle in range 0-16383
int MT6701::correctAngle(){
  int offsetAngle = dir * (rawAngle - startAngle);
  correctedRawAngle = (offsetAngle < 0) ? offsetAngle + 16384 : offsetAngle;
  return correctedRawAngle; // int value 0-16383
}

float MT6701::getAbsoluteAngleRadians() {
  getRawAngle();
  return correctAngle() / 8192.0 * PI;
}

float MT6701::getAbsoluteAngleDegrees() {
  getRawAngle();
  return correctAngle() / 16384.0 * 360;
}

float MT6701::calculateTotalAngle() {
  /*
    Track number of turns by comparing quadrant occupied.

      2 | 1
    ---------
      3 | 4

    If angle was previously in quadrant 1 and is now in quadrant 4, means 1 clockwise cycle complete.
    If angle was previously in quadrant 4 and is now in quadrant 1, means 1 counter clockwise cycle complete.
  */

  // assign quadrant number base on angle
  quadrant = (correctedRawAngle >= 0 && correctedRawAngle <= 4096) ? 1 :
             (correctedRawAngle >= 12288 && correctedRawAngle <= 16384) ? 4 : 2;

  if(quadrant != prevQuadrant) {
    if(quadrant == 1 && prevQuadrant == 4) {
      numberOfTurns ++;
    }
    else if(quadrant == 4 && prevQuadrant == 1) {
      numberOfTurns --;
    }

    prevQuadrant = quadrant;
  }
  
  // converted to radians since it is more used in programs
  totalAngle = numberOfTurns * 2 * PI + correctedRawAngle / 8192.0 * PI; 

  return totalAngle; 
}

float MT6701::getTotalAngleRadians() {
  getRawAngle();
  correctAngle();
  return calculateTotalAngle();
}

float MT6701::getTotalAngleDegrees() {
  getRawAngle();
  correctAngle();
  return (calculateTotalAngle() / (2 * PI)) * 360;
}