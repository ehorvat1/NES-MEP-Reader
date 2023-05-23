# Initial flash Instructions
go tho this Subfolder: [Initial-flash](https://github.com/ehorvat1/NES-MEP-Reader/edit/main/ESP32-binaries/Initial-flash). 

# Update flash Instructions
## Update ESP32 using OTA update function:
When firmware is already installed and device is running, you can do a firmware update over the air (OTA) by accessing the device web page and go to status page ("i" icon on header). Browse to a firmware.bin file and upload it to the ESP32 device.

## Update ESP32 flashing Command using esptool.py:
But if you want to use esptool.py to update to a new version, a shorter command can be used to avoid config being overwritten. Just one file will be uploaded to the device: firmware.bin .

esptool.py --port port_name --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x10000 firmware.bin

Example on Linux:

esptool.py --port /dev/ttyUSB0 --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x10000 firmware.bin

# Erase flash
If the device stops responding or unpredictable behaviour, a flash erase might be needed before flashing.
  
## Erase ESP32 flash Command:
esptool.py --port port_name erase_flash
  
Again, substitute "port_name" with correct COM port your device is connected to. Something like /dev/ttyUSB0 for Linux or COM1 for Windows.

Example: esptool.py --port /dev/ttyUSB0 erase_flash 
