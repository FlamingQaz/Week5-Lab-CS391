#include <heltec_unofficial.h>
#include "image.h"

#define PAUSE               300
#define FREQUENCY           905.2
#define BANDWIDTH           250.0
#define SPREADING_FACTOR    9
#define TRANSMIT_POWER      13

String rxdata;
volatile bool rxFlag = false;
long counter = 0;
uint64_t last_tx = 0;
uint64_t tx_time;
uint64_t minimum_pause;

String mode;
long bites = 0;

void VextON(void) {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void)  //Vext default OFF
{
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, HIGH);
}

void displayReset(void) {
  // Send a reset
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, HIGH);
  delay(1);
  digitalWrite(RST_OLED, LOW);
  delay(1);
  digitalWrite(RST_OLED, HIGH);
  delay(1);
}

void setup() {
  heltec_setup();

  // This turns on and resets the OLED on the Heltec boards
  VextON();
  displayReset();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();

  Serial.println("Radio init");
  RADIOLIB_OR_HALT(radio.begin());
  radio.setDio1Action(rx);
  RADIOLIB_OR_HALT(radio.setFrequency(FREQUENCY));
  RADIOLIB_OR_HALT(radio.setBandwidth(BANDWIDTH));
  RADIOLIB_OR_HALT(radio.setSpreadingFactor(SPREADING_FACTOR));
  RADIOLIB_OR_HALT(radio.setOutputPower(TRANSMIT_POWER));

  RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
}

void loop() {
  heltec_loop();

  if (rxFlag) {
    rxFlag = false;
    radio.readData(rxdata);
    if (_radiolib_status == RADIOLIB_ERR_NONE) {
      Serial.printf("RX [%s]\n", rxdata.c_str());
      mode = rxdata;
      bites = 0;
    }
    RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
  }
  
  if (button.isSingleClick())
  {
    bites++;
    
  }
  if (button.isDoubleClick())
  {
    bites += 2;
  }

  display.clear();
  switch (bites)
  {
    case 0:
      if (mode == "apple")
        display.drawXbm(34, 14, apple_width, apple_height, apple0_bits);
      else if (mode == "banana")
        display.drawXbm(34, 14, banana_width, banana_height, banana0_bits);
    break;
    case 1:
      if (mode == "apple")
        display.drawXbm(34, 14, apple_width, apple_height, apple1_bits);
      else if (mode == "banana")
        display.drawXbm(34, 14, banana_width, banana_height, banana1_bits);
    break;
    case 2:
      if (mode == "apple")
        display.drawXbm(34, 14, apple_width, apple_height, apple2_bits);
      else if (mode == "banana")
        display.drawXbm(34, 14, banana_width, banana_height, banana2_bits);
    break;
    default:
      if (mode == "apple")
        display.drawXbm(34, 14, apple_width, apple_height, apple3_bits);
      else if (mode == "banana")
        display.drawXbm(34, 14, banana_width, banana_height, banana3_bits);
  }
  display.display();
}

void rx() {
  rxFlag = true;
}
