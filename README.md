# RPi-AlarmClock

A few simple programs to get a Raspberry Pi to talk to various peripherals.

##Adafruit 1.2" 4-Digit 7-Segment Display w/I2C Backpack (https://www.adafruit.com/product/1270)

The [Adafruit LED backpack](https://github.com/adafruit/Adafruit_LED_Backpack) Arduino library was partially ported to work on the Raspberry Pi in C++. There is also a [python based library](https://learn.adafruit.com/matrix-7-segment-led-backpack-with-the-raspberry-pi/overview) for this display, but I needed to interface it with the C++ library from Sparkfun below, so I ported the Arduino version. Note that I have disabled:

* 8x16matrix
* 8x16minimatrix
* 8x8matrix
* BicolorMatrix

These are disabled so that I did not need to port the Adafruit_GFX library.

##SparkFun 16 Output I/O Expander Breakout - SX1509 (https://www.sparkfun.com/products/13601)

The [Sparkfun library](https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library) was ported from Arduino.

##IQaudIO Pi-DigiAMP (http://iqaudio.co.uk/hats/9-pi-digiamp.html)
I will use this sound card to play MP3 alarms. This sound card does not require much setup.