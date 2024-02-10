# Hardware 
Updated Rev2 uploaded 21.Dec 2022

## Used parts:
1) A DC/DC step down converter set to 3.3 Volt (source: https://www.az-delivery.de/en/collections/stromversorgung/products/lm2596s-dc-dc-step-down-modul-1 )
2) A ESP32 D1 Mini Module (source: https://www.az-delivery.de/en/collections/esp32/products/esp32-d1-mini)
3) A "selfmade" printed cirquit board based on attached KICAD project. [Schema in pdf format](https://github.com/ehorvat1/NES-MEP-Reader/blob/main/Hardware/NES-MEP-EHo-shema-Rev2.pdf)

### Issues:
There might be problems with power supply from NES Smart meter. It seems that some meters do not supply sufficient power to ESP32. Or the MAX3232 charge pumps interfering with the step down converter. As a result you might see frequent crashes or the serial communication to MEP port not working. You might also notice that the MAX3232 and the step down converter getting quite warm. 
If this happens try:
1) Try with a (oversized) 470uF or 1000uF capacitor on the +3.3V and GND. This helped a lot, but still 2 or 3 tries to connect may be needed.
2) Always helps: Remove the DCDC converter (!) and power the ESP32 module directly from USB.

### Notes:
1) I have used a small "connector" board to connect to the MEP port and a flat ribbon cable. In this way the signals are transported outside of the meter. The flat ribbon cable fits through the open gap where the meter is mounted into the electric cabinet. This all is done because here in my place the MEP port is not accesable, it is covered by a plastic cover which is sealed off by the power supply company.
2) The spacing of the MEP port terminals is different between NES smart meter models. Therefore just 5 short wires are connected to the "connector" board.
