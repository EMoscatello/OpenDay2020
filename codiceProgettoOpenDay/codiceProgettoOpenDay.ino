#include "FastLED.h"

//indico il numero di led
#define NUM_LEDS 50 

//indico il led centrale
#define CENTER_LED 21

//indico il pin 
#define DATA_PIN 5 

//indico il modello dei led
#define LED_TYPE WS2811
#define COLOR_ORDER RGB 

//indico la luminosità
#define BRIGHTNESS 50

//definisco le difficoltà 
#define EASY 1
#define MEDIUM 2
#define HARD 3
#define ON_SPEED 4
#define SONIC_SPEED 5
#define ROCKET_SPEED 6
#define LIGHT_SPEED 7
#define MISSION_IMPOSSIBLE 8

//dichiarazione variabile difficulty(difficoltà del livello)
int difficulty = 1;

//definiamo il numero di led
CRGB leds[NUM_LEDS];

//quando il giocatore vince questo tag è usato per il parametro della difficolta
bool wonThisRound = false;

//inizializzo la posizione per i led
int LEDaddress = 0;

//variabile booleana per vedere se si sta giocando
bool Playing = true;

//variabile booleana per verificare se è la prima vittoria
bool CycleEnded = true;

//dichiarazioni per il pulsante
const int buttonPin = 2;
int buttonState = 0;


void setup() 
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}


//due modi - gioco e fine del gioco
void loop() 
{
  //fine del gioco
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH)
  {
    Playing = false;
    //il gicocatore ha schiacciato il bottone, e il led si è fermato sopra al led vincente
     for (int i = 0; i < NUM_LEDS; i++)
     {
      //imposto il led i al colore nero
      leds[i] = CRGB::Black;
     }

    //setto tutti i led di colore rosso
    leds[CENTER_LED] = CRGB::Red;
    //setto il led vincente di colore verde
    leds[LEDaddress] = CRGB::Green;
    //faccio accendere i led
    FastLED.show();
    
    if (CycleEnded = true)
    {
      //calcolo la distanza tra il led su cui mi sono fermato e il led vincente
      int diff = abs(CENTER_LED - LEDaddress);
      //se la differenza è 0 allora ho vinto
      if (diff == 0)
      {
        //ho vinto il livello
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
    //se il bottone non è stato premuto
    if (buttonState == LOW)
    {
     Playing = true;
    }
  }
  
  //se sto giocando
  if(Playing)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      //reimpostiamo il led i al colore nero
      leds[i] = CRGB::Black;
    }
    //setto tutti i led di colore rosso
    leds[CENTER_LED] = CRGB::Red;
    //setto il led vincente di colore verde
    leds[LEDaddress] = CRGB::Green;
    //faccio accendere i led
    FastLED.show();
    //faccio accendere un led alla volta
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

//parametri per i livelli
int getTime(int diff) //ritorna il delay dei led in base alla difficoltà
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
  //ritorna il valore del delay
  return timeValue;
}

//a ogni vincita incremento i parametri della difficoltà
void increaseDifficulty() 
{
  if (difficulty != MISSION_IMPOSSIBLE && wonThisRound) 
  {
    difficulty++;
  }
}

//accensione dei led alla perdita
void flash()
{ 
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(500);
}

//accensione dei led alla vincita
void fadeall()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].nscale8(250); 
  }
}

//accensione dei led in caso di vittoria
void cylon() 
{ 
  static uint8_t hue = 0;
  Serial.print("x");
  //prima slido i led in una direzione
  for(int i = 0; i < NUM_LEDS; i++) {
    //setto il led i rosso 
    leds[i] = CHSV(hue++, 255, 255);
    //faccio accendere i led
    FastLED.show(); 
    //ora che li abbiamo accesi, li reimpostiamo al colore nero
    //leds[i] = CRGB::Black;
    //richiamo il metodo per accendere i led alla vincita
    fadeall();
    //aspettiamo un piccolo tempo prima di ripetere il metodo
    delay(10);
  }
  Serial.print("x");

  //adesso andiamo nell'altra direzione  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) 
  {
    //setto il led i rosso 
    leds[i] = CHSV(hue++, 255, 255);
    //faccio accendere i led
    FastLED.show();
    //ora che li abbiamo accesi, li reimpostiamo al colore nero
    //leds[i] = CRGB::Black;
    //richiamo il metodo per accendere i led alla vincita
    fadeall();
    //aspettiamo un piccolo tempo prima di ripetere il metodo
    delay(10);
  }
}
