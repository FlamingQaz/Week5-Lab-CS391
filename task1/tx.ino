#include <Wire.h>
#include <heltec_unofficial.h>
long counter = 0;

void setup() {
  // initialize serial setup!
  heltec_setup();
  
  Serial.print(F("Initializing ... "));
  RADIOLIB_OR_HALT(radio.begin());
  RADIOLIB_OR_HALT(radio.setFrequency(905.2)); // 900 MHz
}

void loop() {
  Serial.print(F("Transmitting packet ... "));

  Serial.print(F("Hi there!! ^^7 \nSEQUENCE No.: "));
  Serial.println(F(String(counter).c_str()));

  char transm[50] = "Hi there!! ^^7 \n[SX1262] SEQUENCE No.: ";
  strcat(transm, String(counter++).c_str());

  RADIOLIB(radio.transmit(transm));
  
  // check transmission status!
  if (_radiolib_status == RADIOLIB_ERR_NONE) {
      Serial.println(F("\n... success!"));
  } else {
      Serial.print(F("\n...failed, code "));
      Serial.println(_radiolib_status);
  }
  
  delay(5000); // wait for 5 seconds before transmitting again.

}
