#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LED_PIN    11

#define LED_COUNT 21

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

double sens = 0.5;
uint32_t colour = strip.Color(sens*255, 0, 255*(1-sens));
uint32_t inverse_colour = strip.Color((1-sens)*255, 255*sens, 0);
double newsens = sens/2;


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
    i = floor(((x+sens)*100)/(sens*2*100/21))+1;
    j = floor(((x+newsens)*100)/(newsens*2*100/21))+1;
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
    if (i == 11){
      strip.setPixelColor(i-1, strip.Color(0, 255, 0));
      strip.setPixelColor(i, strip.Color(0, 255, 0));
      strip.setPixelColor(i+1, strip.Color(0, 255, 0));  
      strip.setBrightness(100);
      strip.show();
      delay(10);
      strip.setBrightness(50);
      strip.setPixelColor(i-1, strip.Color(0, 0, 0));
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.setPixelColor(i+1, strip.Color(0, 0, 0));  
    }
    else {
      strip.setPixelColor(i, colour);
      strip.setPixelColor(j, inverse_colour);
      strip.show();
      delay(10);
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor(j, strip.Color(0,0,0));
    }
  }
}