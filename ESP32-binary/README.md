# Initial flash Instructions
1) Have a working "esptool.py" software installed. It be found here: https://github.com/espressif/esptool

2) a) Build project with PlatformIO or b) use the prebuilt firmware image "firmware.bin" from this directory. (firmware-de.bin is the german version).

For ESP32 you will need three files to flash the device: firmware.bin , partitions.bin and bootloader.bin you get in the ESP32-binary section of this repository. The latest bootloader file you can get from Arduino ESP32 bootloader https://github.com/espressif/arduino-esp32/tree/master/tools/sdk/esp32/bin . The default bootloader for a 4MB ESP32 is "bootloader_dio_40m.bin" and it was just renamed here to "bootloader.bin".    


3) Make shure you have the 3 needed files (bootloader.bin, firmware.bin,and partitions.bin) in the directory where esptool.py is started in.

4) Run below (quite long) command to first time flash the ESP32 using a serial to USB port converter (exchange "/dev/ttyUSB0" with your serial port name. "/dev/ttyxxxx" is for Linux , Windows uses COM1 or so...)

## Initial ESP32 flashing Command:
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin


# Update flash Instructions
When firmware is already installed and device is running, you can do a update over the air (OTA) by accessing the device web page and go to "System --> Firmware". Browse to a firmware.bin file and upload it to the ESP32 device.

But if you want to use esptool to upgrade to a new version, a shorter command can be used to avoid config being overwritten. Just one file will be uploaded to the device: firmware.bin .

## Update ESP32 flashing Command:
esptool.py --port <port> --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x10000 firmware.bin

# Erase flash
If the device stops responding or unpredictable behaviour, a flash erase might be needed before flashing. Read more here
  
## Erase ESP32 flash Command:
esptool.py --port <port> erase_flash
  
Substitute <port> with correct COM port your device is connected to. Ex /dev/ttyUSB0 for Linux or COM1 for Windows
