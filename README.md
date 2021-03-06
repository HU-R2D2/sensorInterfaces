# sensorInterfaces

**NOTICE:**
If you would like to implement this library and use it on a Raspberry Pi or any other supported hwlib system, then follow these steps:

* In UltrasonicSensor.hpp uncomment "// #define HWLIB_ENABLED" (see code below)
``` C++
// If we want to compile this code on a system supported by hwlib, then we have 
// to uncomment the define below. There's a check for this define in 
// "get_distance()" that will throw an exception if not defined. This way the 
// code will also be able to compile on non-supported hwlib systems.
#define HWLIB_ENABLED
```
* In your main, or anywhere you use a Sensor with hwlib, we need to include the correct file for the system we are using. See the [hwlib documentation](https://roborescue.nl/index.php/Hwlib) for more info. In our project it was used like this:
``` C++
// The define below will be used to check whether or not we are on a hwlib
// supported system. If not, then hwlib related methods won't be used. 
// This way the code will be able to compile on non-supported hwlib
// systems as well.
#define HWLIB_ENABLED

#ifdef HWLIB_ENABLED
#include "hwlib.c"
#endif

int main() {    
    // If HWLIB_ENABLED was defined, we can call some methods specific for hwlib
    #ifdef HWLIB_ENABLED
    bcm2835_init();
    #endif
    
    return 0;
}
```

## Documentation
You can find the documentation for Sensor Interfaces right [here](https://roborescue.nl/index.php/Sensor_interfaces). Here you will find examples and links to other libraries.

**IMPORTANT NOTE:** This version is based on Clock and TimeStamp from [ADT_Clock_merge](https://github.com/HU-R2D2/ADT_Clock_Merge/tree/develop). Those files will eventually end up in [ADT](https://github.com/HU-R2D2/adt), which is also how our CMakeList.txt works. 
For now you can copy Clock and TimeStamp from ADT_Clock_merge and paste them in the correct folders in [ADT](https://github.com/HU-R2D2/adt).  
