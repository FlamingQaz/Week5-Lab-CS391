#include <heltec_unofficial.h>
#define PAUSE               300
#define FREQUENCY           905.2
#define BANDWIDTH           250.0
#define SPREADING_FACTOR    9
#define TRANSMIT_POWER      3

String rxdata;
volatile bool rxFlag = false;
uint64_t last_tx = 0;
uint64_t tx_time;
uint64_t minimum_pause;

void VextON(void) {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, HIGH);
}

void displayReset(void) {
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
  RADIOLIB_OR_HALT(radio.begin());
  
  radio.setDio1Action(rx);
  
  RADIOLIB_OR_HALT(radio.setFrequency(FREQUENCY));
  RADIOLIB_OR_HALT(radio.setBandwidth(BANDWIDTH));
  RADIOLIB_OR_HALT(radio.setSpreadingFactor(SPREADING_FACTOR));
  RADIOLIB_OR_HALT(radio.setOutputPower(TRANSMIT_POWER));
}

void loop() {
  heltec_loop();

  VextON();
  displayReset();
  display.init();
  display.flipScreenVertically();
  
  bool tx_legal = millis() > last_tx + minimum_pause;
  
  if ((PAUSE && tx_legal && millis() - last_tx > (PAUSE * 1000)) || button.isSingleClick()) {
    
    if (!tx_legal) {
      RADIOLIB(radio.transmit("banana"));
      both.printf("banana transmitted!\n");
      return;
    }
    
    radio.clearDio1Action();
    
    heltec_led(50);
    tx_time = millis();
    
    RADIOLIB(radio.transmit("apple"));
    both.printf("apple transmitted!\n");
    
    tx_time = millis() - tx_time;
    heltec_led(0);
    
    if (_radiolib_status == RADIOLIB_ERR_NONE) {
      both.printf("DISPLAYED! (%i ms)\n", (int)tx_time);
    } else {
      both.printf("Something went wrong... (%i)\n", _radiolib_status);
    }
    
    minimum_pause = tx_time * 100;
    last_tx = millis();
    radio.setDio1Action(rx);
  }
}

void rx() {
  rxFlag = true;
}
