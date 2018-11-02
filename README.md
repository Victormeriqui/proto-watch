# proto-watch
Software for an Arduino based smart-watch prototype. Currently runs on a Teensy 3.2 board with extra components. 

This project tries to emulate a smart-watch with several Arduino compatible components:  
  
Main board: Teensy 3.2 (https://www.pjrc.com/teensy/)  
Display: OLED 124x64 monochrome (https://www.adafruit.com/product/938)  
Communications: Bluetooth SH-HC-08  
Power: Cheap LiPo Battery 500mA  
Input: 3 way directional button  
  
proto-watch uses a custom library to manipulate the display, made entirely for this project.  
It's capable of fast bitmap drawing with some optimizations.
