# Week5-Lab-CS391

### Xavier Hunter and Ashe Visavale

## Setting up

1. Install this library
   
   Use the library manager to install this library. Find it by entering "heltec_esp32" in the library manager search box.

2. Add ESP32 URL to settings
   ```https://espressif.github.io/arduino-esp32/package_esp32_index.json```

   ![board_manager_url.png](https://github.com/ropg/heltec_esp32_lora_v3/blob/main/images/board_manager_url.png?raw=true)
   
   to the additional board manager URL to the Settings of the Arduino IDE.

	>(Make sure this and any URLs that might be already there are seperated by commas. If you hit OK the IDE will then load the files needed.)

3. Install ESP32
   
   Go to board manager and install "esp32 by Espressif Systems". At the time of writing this, the latest version is 2.0.16.
   
4. Select the board
   Start Arduino IDE and from the board dropdown select "Select another board and port" and enter "heltec" in the search box. Select the board named "Heltec WiFi LoRa 32(V3) / Wireless shell(V3)" as in the image below. Do not use any of the other boards, even if they look right.

   [![](https://github.com/ropg/heltec_esp32_lora_v3/raw/main/images/select_board.png)](https://github.com/ropg/heltec_esp32_lora_v3/blob/main/images/select_board.png)
5. Run the specified .ino file in Arduino for the task and board, i.e Task 1/rx or Task 2/tx, for the Task 1 Receiver and Task 2 Transmitter respectively.

## Special Notes

### Libraries Used

- [ESP8266 and ESP32 OLED driver for SSD1306 displays *by Thingpulse, Fabrice Weinberg*](https://github.com/ThingPulse/esp8266-oled-ssd1306)
- [Heltec ESP32 LoRa v3 *by Rop Gonggrijp*](https://github.com/ropg/Heltec_ESP32_LoRa_v3)
- [HotButton *by Rop Gonggrijp*](https://github.com/ropg/HotButton)
- [RadioLib *by Jan Gromes*](https://github.com/jgromes/RadioLib)

### Baud Rate

Use 115200 in the Serial Monitor
