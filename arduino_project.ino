#include <Adafruit_NeoPixel.h>

#define PIN         7
#define NUM_LEDS    20
#define BRIGHTNESS  255
#define SATURATION  255

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int tdel = 50; // delay
int n_leds = 7;
char incomingByte = 0;
int choice = 0;

void Clear(int tdel = 0) {
    pixels.clear();
    pixels.show();
    delay(tdel);
}

void Spectrum(int tdel = 0) { 
  int r,g,b;
  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i == 29 || i == 30) { // elimino i due led al centro/saldatura
        pixels.setPixelColor(i, pixels.Color(0,0,0));
      }
      else {
        r = random(0, 255);
        g = random(0, 255);
        b = random(0, 255);
        pixels.setPixelColor(i, pixels.Color(r,g,b));
        pixels.setPixelColor(NUM_LEDS-i-1, pixels.Color(r,g,b));
      }
    }
    pixels.show();
    delay(tdel);
  }
}

void startUpOrange(int tdel = 0) {
    for (int i=0; i<n_leds; i++) {
        pixels.setPixelColor(i, pixels.Color(255,94,0));
        pixels.setPixelColor(NUM_LEDS-i-1, pixels.Color(255,94,0));
        pixels.show();
        delay(tdel);
    }
    delay(100);
}

void startUpWhite(int tdel = 0) {
  for (int i=0; i<n_leds; i++){
    for (int j=0; j<n_leds-i; j++) {
      pixels.setPixelColor(j, pixels.Color(100,219,255));
      pixels.setPixelColor(NUM_LEDS-j-1, pixels.Color(100,219,255));
      pixels.show();
      delay(tdel);
      if (n_leds-i-1 != j) {
        pixels.setPixelColor(j, pixels.Color(0,0,0));
        pixels.setPixelColor(NUM_LEDS-j-1, pixels.Color(0,0,0));
      }
      
    }
  }
}

void supCar(int tdel = 0){
  for(int i = 1; i < NUM_LEDS; i++){
    pixels.setPixelColor(i-1, pixels.Color(0,0,0));
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();
    delay(tdel);
  }
  for(int i = NUM_LEDS-1; i > 0; i--){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.setPixelColor(i-1, pixels.Color(255,0,0));
    pixels.show();
    delay(tdel);
  }
}

void setup() {
  	Serial.begin(9600);
  	
  	pixels.setBrightness(20);
  	//pixels.setMaxPowerInVoltsAndMilliamps(5, 500);
    pixels.clear();  
  
    // Inizialize led strip  
    pixels.begin();
    pixels.show();

	
    //Start up Orange
    startUpOrange(tdel);
    Clear(300);
    startUpOrange(tdel);
    Clear(300);

    //Start up white
    startUpWhite(tdel);
  
 }

void loop() {
  	
    if(Serial.available()>0) {  	
        incomingByte = Serial.read(); 
      	choice = incomingByte - '0';
        
        switch(choice) { 
          case 0:
            Clear(10);
            break;
          case 1:
            Clear(0);
            Spectrum(25);
          	            break;
          case 2:
            Clear(0);
            break;
          case 3:
            Clear(10);
            supCar(tdel);
            break;
          default:
            Serial.println("Invalid command");
            break;
        }
 	}
}