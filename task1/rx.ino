#include <Wire.h>
#include <heltec_unofficial.h>

long counter = 0;

void setup() {
  // initialize serial setup!
  heltec_setup();

  Serial.print(F("Initializing ... "));
  RADIOLIB_OR_HALT(radio.begin());
  if (_radiolib_status == RADIOLIB_ERR_NONE) {
    Serial.println(F("Initialization successful!"));
  } else {
    Serial.print(F("Initialization failed, code "));
    Serial.println(_radiolib_status);
    while (true)
      ;
  }
  RADIOLIB_OR_HALT(radio.setFrequency(905.2));
  RADIOLIB_OR_HALT(radio.startReceive());
}

void loop() {
  // Receive a packet

  String str;
  int state = radio.receive(str);

  if (state == RADIOLIB_ERR_NONE) {
    // packet received successfully 
    Serial.println("Received packet successfully!");

    Serial.print("[SX1262] RSSI:\t\t");
    Serial.print(radio.getRSSI());
    Serial.println(" dBm");

    Serial.print("[SX1262] SNR:\t\t");
    Serial.print(radio.getSNR());
    Serial.println(" dB");

    // Print the received data
    Serial.print("[SX1262] Message:\t\t");
    Serial.println(str);

  } else if (state != RADIOLIB_ERR_RX_TIMEOUT && state != RADIOLIB_ERR_CRC_MISMATCH) {
    Serial.print("Failed to receive packet, code ");
    Serial.println(_radiolib_status);
  }
}
