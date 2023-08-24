# Trailer light controller

This controller, based on the very straightforward usermod battery_keypad_controller

Using a 4-wire trailer plug with logic-lever converters to drop the signals to ESP-friendly 3.3V
The module is powered from the 12VDC of the marker lights
inputs: 
    left turn
    right turn

Check the input states to determine whether brakes are applied and which if either turn signal is activated.

All changes in core files have been marked up with 'BrewLord!'

To install:
- In platformio.ini comment out:
`default_envs = nodemcuv2, esp8266_2m, esp01_1m_full, esp32dev, ...`

- In platformio.ini add:
`default_envs = esp8266_wreath, esp32dev_wreath`

- Copy the platformio_override.ini in the root folder

- In platformio_override.ini update any pin definitions you may need

- Select your architecture in the PlatformIO Project Environment pulldown on the bottom of the screen

- Run and enjoy