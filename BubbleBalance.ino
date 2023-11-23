#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LED_PIN    11

#define LED_COUNT 21

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);



double sens = 0.5;
double newsens = sens/2;

uint32_t colour = strip.Color(sens*255, 0, 255*(1-sens));
uint32_t inverse_colour = strip.Color((1-sens)*255, 255*sens, 0);
uint32_t black = strip.Color(0,0,0);
uint32_t white = strip.Color(255,255,255);
uint32_t red = strip.Color(255,0,0);
uint32_t green = strip.Color(0,255,0);

int mode = 2;

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  
  strip.begin();          
  strip.show();           
  strip.setBrightness(50);

  Serial.begin(9600);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
  
}

void loop() {
  float x, y, z;
  int i;
  int j;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    i = floor(((x+sens)*100)/(sens*2*100/21));
    j = floor(((x+newsens)*100)/(newsens*2*100/21));
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
    if (mode == 1){
      if (i == 10){
        strip.setPixelColor(i-1, green);
        strip.setPixelColor(i, green);
        strip.setPixelColor(i+1, green);  
        strip.setBrightness(100);
        strip.show();
        delay(10);
        strip.setBrightness(50);
        strip.setPixelColor(i-1, black);
        strip.setPixelColor(i, black);
        strip.setPixelColor(i+1, black);  
      }
      else {
        strip.setPixelColor(i, colour);
        strip.setPixelColor(j, inverse_colour);
        strip.show();
        delay(10);
        strip.setPixelColor(i, black);
        strip.setPixelColor(j, black);
      }
    }
    if (mode == 2){
      if (i==10){
        for (int x=0; x<strip.numPixels(); x++){
          if (x != 0){
            strip.setPixelColor(x, green);
          }
          else {
            strip.setPixelColor(x, black);
          }
        }
        strip.show();
        delay(10);
      }
      else{
        for (int x=0; x<strip.numPixels(); x++){
          if (x != i){
            strip.setPixelColor(x, red);
          }
          else {
            strip.setPixelColor(x, black);
          }
        }
        strip.show();
        delay(10);
    } 
    
    } 
  }
}