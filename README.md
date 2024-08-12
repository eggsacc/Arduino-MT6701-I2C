# Arduino MT6701 library

A simple library to read and calculate MT6701 angle values using I2C.

## Encoder setup

````cpp
MT6701 object(int8_t dir, bool zero_angle);
````

MT6701 class requires 2 parameters. `dir` determines if the angle values increase or decrease with clockwise rotation and should be either 1 or -1. `zero_angle` is a boolean to determine if the starting angle should be automatically zeroed, 1 for True and 0 for False.

````cpp
//example setup:
#define DIRECTION -1     // invert direction
#define ZERO_ANGLE 0     // zero angle on start False

MT6701 sensor(DIRECTION, ZERO_ANGLE);

void Setup() {
    
    sensor.initEncoder();

}
````

## Functions
1) `sensor.initEncoder`: initialize I2C communication. No return value
2) `sensor.getRawAngle`: read the raw 14-bit encoder output (0-16383), returns `int`
3) `sensor.getAbsoluteAngle`: calculates absolute angle in radians (0-2pi), returns `float`
4) `sensor.getAbsoluteAngleDegrees`: calculates absolute angle in degrees (0-360), returns `float`
5) `sensor.getAngle`: calculates total rotation angle in radians, returns `float`
6) `sensor.getAngleDegrees`: calculates total rotation angle in degrees, returns `float`
