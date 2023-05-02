
0) Have a working "esptool.py" software installed.
1a) Build project with PlatformIO or 
1b) use the prebuilt firmware images. There are 2 firmware files which are showing the import/export plots differently - the filename explains. Rename the firmware file to "firmware.bin" so below command will work.
2) Make shure you have the 3 needed files (bootloader.bin, firmware.bin,and partitions.bin) in the directory where esptool.py is started in.
   (The "bootloader.bin" is for 4MB ESP32s and was originally named: "bootloader_dio_40m.bin" . 
   The original bootloader file can be found here: https://github.com/espressif/arduino-esp32/tree/master/tools/sdk/esp32/bin )
3) Run below (quite long) command to first time flash the ESP32 using a serial to USB port converter (exchange "/dev/ttyUSB0" with your serial port name. "/dev/ttyxxxx" is for Linux , Windows uses COM1 or so...)

esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin
