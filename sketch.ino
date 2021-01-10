
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define ampBufferSize 6
#define inputBufferSize 36
#define audioBands 30
#define threshhold 40

char bandBuffer[1 + 1];
//converted values from buffer above
uint8_t bandBufferValues[audioBands];

char amplitudeBuffer[ampBufferSize];
//converted value from buffer above
float amplitudeValue = 0;

//complete buffer
char inputBuffer[inputBufferSize];

//loop indices
uint8_t i = 0, j = 0;

uint8_t colorMode = 0;

void setup() {
  Serial.begin(9600);
  // init strip
  strip.begin();
  strip.show();
}



void loop() {
  
  //example sequence for inputbuffer 023.43000111111111111100000000000000000
  if (Serial.available() > 0) {
    //read 36 + 1 bytes for end of line char
    Serial.readBytesUntil('\n', inputBuffer, 37);

    //fill char arrays from buffer
    for (i = 0; i < ampBufferSize; i++) amplitudeBuffer[i] = inputBuffer[i];
    amplitudeValue = atof(amplitudeBuffer);
   
    //get audio bands
    for (i = 0; i < audioBands; i++) {
      bandBuffer[0] = inputBuffer[ampBufferSize + i];
      bandBufferValues[i] = atoi(bandBuffer) * (int)amplitudeValue;
    }

    if (amplitudeValue >= threshhold) colorMode < 9 ? colorMode++ : colorMode = 0;
    
    for (i = audioBands; i > 0; i--) AudioVis(bandBufferValues[audioBands - i]);
    for (i = audioBands; i < NUMPIXELS; i++) AudioVis(bandBufferValues[i - audioBands]);
    
    strip.show();
      }
}
void AudioVis(uint8_t value) {
  
  switch (colorMode) {
    case 0:
      if (i % 3 == 0) {
        rgb(i, value, value, 0);
      } else if (i % 2 == 0) {
        rgb(i, 0, value, value);
      } else {
        rgb(i, value, 0, value);
      }
      break;
    case 1:
      //pink
      rgb(i, value * 3, value, 0);
      break;
    case 2:
      if (i % 5 == 0) {
        rgb(i, value * 5, value, 0);
      } else if (i % 7 == 0) {
        rgb(i, 0, value * 6, value);
      } else {
        rgb(i, value, 0, value*4);
      }
      break;
    case 3:
      //orange
      rgb(i, value * 8, 0, value);
      break;
    case 4:
      if (i % 3 == 0) {
        rgb(i, value / 2, value, 0);
      } else if (i % 2 == 0) {
        rgb(i, 0, value / 3, value);
      } else {
        rgb(i, value / 4, 0, value);
      }
      break;
    case 5:
      //violet
      rgb(i, value, 0, value);
      break;
    case 6:
      if (i % 3 == 0) {
        rgb(i, value / 5, value, 0);
      } else if (i % 4 == 0) {
        rgb(i, 0, value / 6, value);
      } else {
        rgb(i, value / 7, 0, value);
      }
      break;
    case 7:
      //cyan
      rgb(i, 0, value, value);
      break;
    case 8:
      //yellow
      rgb(i, value*2, value*2, 0);
      break;
    case 9:
      //red
      rgb(i, value, 0, 0);
      break;
  }
}

void clamp(uint8_t *a, uint8_t mini, uint8_t maxi) {
  if (*a < mini) {
    *a = mini;
  } else if (*a > maxi) {
    *a = maxi;
  }
}

void rgb(char id, uint8_t r, uint8_t g, uint8_t b) {
  clamp(&r, 0, 255);
  clamp(&g, 0, 255);
  clamp(&b, 0, 255);
  strip.setPixelColor(id, strip.Color(r, b, g));
}
