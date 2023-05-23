# Initial flash Instructions
1) Have a working "esptool.py" software installed. It can be found here: https://github.com/espressif/esptool

2) Get Firmware (works only for ESP32)
     1) Use the prebuilt firmware.bin image "firmware.bin" from this directory: [ESP32-binaries](https://github.com/ehorvat1/NES-MEP-Reader/tree/main/ESP32-binaries). For initial flash of ESP32 you will need three files: firmware.bin , partitions.bin and bootloader.bin. The latest bootloader file you can get from Arduino ESP32 bootloader https://github.com/espressif/arduino-esp32/tree/master/tools/sdk/esp32/bin . The default bootloader for a 4MB ESP32 is "bootloader_dio_40m.bin" and it was just renamed here to "bootloader.bin". 
        
     2) or Build project with PlatformIO.

3) Make shure you have the 3 needed files (bootloader.bin, firmware.bin,and partitions.bin) in the directory where esptool.py is started in.

4) Run below (quite long) command to first time flash the ESP32 using a serial to USB port converter (exchange "port_name" with your serial port name. "/dev/ttyxxxx" is for Linux , Windows uses COM1 or so...)

## Initial ESP32 flashing Command:
If you also want to delete old config data (which is advised), do a full erase of flash before. See bottom of this file.

esptool.py --chip esp32 --port port_name --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin

Example for Linux:

esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin


# Update flash Instructions
If you want to update the firmware on a working ESP32 go to: [ESP32-binaries](https://github.com/ehorvat1/NES-MEP-Reader/tree/main/ESP32-binaries)
# Erase flash
If the device stops responding or unpredictable behaviour, a flash erase might be needed before flashing.
  
## Erase ESP32 flash Command:
esptool.py --port port_name erase_flash
  
Again, substitute "port_name" with correct COM port your device is connected to. Something like /dev/ttyUSB0 for Linux or COM1 for Windows.

Example: esptool.py --port /dev/ttyUSB0 erase_flash 
