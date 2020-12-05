#include "FastLED.h"

#define NUM_LEDS 50 

#define CENTER_LED 21

#define DATA_PIN 5 

#define LED_TYPE WS2811
#define COLOR_ORDER RGB 

#define BRIGHTNESS 50

#define EASY 1
#define MEDIUM 2
#define HARD 3
#define ON_SPEED 4
#define SONIC_SPEED 5
#define ROCKET_SPEED 6
#define LIGHT_SPEED 7
#define MISSION_IMPOSSIBLE 8

int difficulty = 1;

CRGB leds[NUM_LEDS];

bool wonThisRound = false;

int LEDaddress = 0;

bool Playing = true;

bool CycleEnded = true;
s
const int buttonPin = 2;
int buttonState = 0;

void setup() 
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH)
  {
    Playing = false;
     for (int i = 0; i < NUM_LEDS; i++)
     {
      leds [i] = CRGB::Black;
     }
    leds[CENTER_LED] = CRGB::Red;
    leds[LEDaddress] = CRGB::Green;  
    FastLED.show();
    if (CycleEnded = true)
    {
      int diff = abs(CENTER_LED - LEDaddress);
      if (diff == 0)
      {
        wonThisRound = true;
        if (difficulty != MISSION_IMPOSSIBLE)
         {
          for (int i = 0; i < 2; i++)
           {
            cylon();
           }
         }
        if (difficulty == MISSION_IMPOSSIBLE)
         {
          for (int i = 0; i < 8; i++)
           {
            cylon();
           }
          difficulty = 0; 
         }
        increaseDifficulty();      
        wonThisRound = false;
      }
       else
      {
      delay(1000);  
      for (int i = 0; i < 2; i++)
       {
        flash();
       }
      }
        CycleEnded = false;
      }
    LEDaddress = 0; 
    delay(250);
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW)
    {
     Playing = true;
    }
  }
  
  if(Playing)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
    leds[CENTER_LED] = CRGB::Red;
    leds[LEDaddress] = CRGB::Green;
    FastLED.show();
    LEDaddress++;
    if (LEDaddress == NUM_LEDS)
    {
      LEDaddress = 0;
    }
    delay(getTime(difficulty));
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH)
    {
     Playing = false;
     CycleEnded = true;
    }
 }
}

int getTime(int diff)
{
  int timeValue = 0;
  switch (diff) 
  {
    case EASY:
      timeValue = 100;
      break;
    case MEDIUM:
      timeValue = 80;
      break;
    case HARD:
      timeValue = 60;
      break;
    case ON_SPEED:
      timeValue = 40;
      break;
    case SONIC_SPEED:
      timeValue = 30;
      break;
    case ROCKET_SPEED:
      timeValue = 20;
      break;
    case LIGHT_SPEED:
      timeValue = 13;
      break;
    case MISSION_IMPOSSIBLE:
      timeValue = 7;
  }
  return timeValue;
}

void increaseDifficulty() 
{
  if (difficulty != MISSION_IMPOSSIBLE && wonThisRound) 
  {
    difficulty++;
  }
}

void flash()
{ 
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(500);
}

void fadeall() 
{ 
  for(int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i].nscale8(250); 
  } 
}

void cylon() 
{ 
  static uint8_t hue = 0;
  Serial.print("x");
  for(int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
    //leds[i] = CRGB::Black;
    fadeall();
    delay(10);
  }
  Serial.print("x");

  for(int i = (NUM_LEDS)-1; i >= 0; i--) 
  {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    //leds[i] = CRGB::Black;
    fadeall();
    delay(10);
  }
}
