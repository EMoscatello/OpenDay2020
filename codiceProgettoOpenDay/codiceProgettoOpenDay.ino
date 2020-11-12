#include <FastLED.h>
#define NUM_LEDS 50 

#define DATA_PIN 5
#define CLOCK_PIN 13

#define DATA_PIN 5
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
int num=0;

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("resetting");
  LEDS.addLeds<WS2811,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);

  attachInterrupt(0,interruptBottone,RISING);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  leds[25]=CRGB::Green;

  for(int i=0;i<NUM_LEDS;i++){
    num=i;
    leds[i]=CRGB::Red;
    FastLED.show(); 
    delay(100);
    leds[i] = CRGB::Black;
  }
}

void interruptBottone(){
  if(num==25){
    static uint8_t hue = 0;
    for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  }
}
