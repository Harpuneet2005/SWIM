#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    11

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 21

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int image[144][1946][3] PROGMEM = {
};

void ShowImage();
void black();


void setup() {
  // put your setup code here, to run once:
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(25);
}

void loop() {
  ShowImage();
  black();
  delay(2000);
}

void White(){
  for (int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    strip.show();
    delay(50);
  }
}
void black(){
  for (int i=0; i<144; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}
void ShowImage(){
  for (int i=0; i<1946; i++){
    for (int y=0; y<144; y++){
      strip.setPixelColor(y, strip.Color(255*pgm_read_byte(&(image[y][i][0])),255*pgm_read_byte(&(image[y][i][1])),255*pgm_read_byte(&(image[y][i][2]))));
    }
    strip.show();
    delay(10);
  }
}
