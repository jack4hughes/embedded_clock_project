
# Parts List:
## Display:
I don't have a datasheet for this, so I'm going to make some assumptions here: It looks like a fairly standard 32x64 pixel LCD matrix, so it should be 5V and have a max power draw of about 12W. This means it will have 5V logic in. I'm not planning on getting anywhere close to the maximum power draw of the circuit, as this will be very bright. In the future, I might include auto-brightness using a light-sensitive diode.

[Link to wiki for a similar board:](https://www.waveshare.com/wiki/RGB-Matrix-P4-64x32)

## Microcontroller (ESP32):
[link:](https://docs.espressif.com/projects/esp-idf/en/release-v4.2/esp32/hw-reference/esp32/get-started-devkitc.html)

- Model: ESP32_devkitc_u4
- Clock Speed: 2.4Ghz
- RAM: 520kb

## Power:
I need to power the microcontroller and the screen. The ESP should be able to take a 5V input, which simplifies power, as a single voltage level can be used for everything.

TODO: Need to check if I already have a 5V power supply already.

## Connecting Everything:
To connect everything, I'll start with a breadboard/direct power and then design a circuit in KiCAD that should connect everything nicely.

## Timer Chip:
Once everything is up and running, I need to replace the ESP32's internal clock with a timer chip for more reliable timekeeping.
