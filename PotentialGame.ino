#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LED_PIN    11

#define LED_COUNT 21

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t black = strip.Color(0, 0, 0);
uint32_t white = strip.Color(255, 255, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);

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
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
    if (x < -0.3){
      Serial.println('Beep');
      do {for (int i=0; i<strip.numPixels(); i++){
            strip.setPixelColor(i, green);
          }
      strip.show();
      IMU.readAcceleration(x, y, z);
      }
      while(x<-0.3);
    }
    if (x > -0.3){
      do {for (int i=0; i<strip.numPixels(); i++){
            strip.setPixelColor(i, black);
          }
      strip.show();
      IMU.readAcceleration(x, y, z);
      }
      while(x>-0.3);
    }
  }
}