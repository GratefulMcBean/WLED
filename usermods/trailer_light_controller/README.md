# Trailer light controller

This controller, based on the very straightforward usermod battery_keypad_controller

Using a 4-wire trailer plug with logic-lever converters to drop the signals to ESP-friendly 3.3V
The module is powered from the 12VDC of the marker lights
inputs: 
    left turn
    right turn

Check the input states to determine whether brakes are applied and which if either turn signal is activated.

To install, copy the usermod.cpp file to wled00 folder and recompile