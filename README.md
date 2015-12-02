Aeris robot
===========

Source code for the first revision of aeris robot.

Compilation instructions:
-------------------------

Dependencies:
* make
* cmake - <b>latest</b> <s>debian</s> stable release recommended (>= 3.4.0)
* arm-none-eabi-gcc - any recent version should be fine
* [dfu-util](http://dfu-util.gnumonks.org)


Build:

1. git clone 'https://github.com/richese/aeris_robot.git'
2. mkdir aeris_robot/build
3. cd aeris_robot/build
4. cmake ..
5. make

Flash:

1. Change to project root directory:<br>
    cd aeris_robot
2. Run <b>stm32f_write_dfu_usb.sh</b> script with path to binary you want to flash:<br>
    ./stm32f_write_dfu_usb.sh build/tests.bin<br>
    ./stm32f_write_dfu_usb.sh build/line_follower.bin<br>
    ./stm32f_write_dfu_usb.sh build/template.bin<br>
