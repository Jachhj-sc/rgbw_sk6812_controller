// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

//LEDPIXEL
//test
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
//#include <delay.h>


#define LED_PIN     3
#define LED_COUNT   182
#define BRIGHTNESS  255
#define brightnessPot A0
#define huePot A1

#define EX 0
#define NORM 1
#define ANIM 2

#define Button0 4
#define Button1 5
#define Button2 6

bool prevButton1Val;
bool prevButton0Val;
bool prevButton2Val;
bool curButton0Val;
bool curButton1Val;
bool curButton2Val;

int varRes0;
int varRes1;
int aOld;
int r = 110;
int g = 100;
int b = 80;
int w = 80;
int receiveMode = 0; // 0, rgb receive mode 1, animation mode receive.

int o = 0;
int m = 0;
int timeVal;
int brightness;
int whiteness = 0;
int prevWhiteness = 0;

uint32_t color = 0;

char task;//value so only one task is running at a time.
uint32_t hue = 0;
uint32_t reading = 0;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void initPot() {
  pinMode(Button0, INPUT_PULLUP);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  //LED
  initPot();
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
  // Serial.begin(115200);

  //init ledstrip
  strip.fill(strip.Color(r, g, b, w));
  strip.show();
  strip.clear();
  Serial.begin(9600);
  while (!Serial); //wait for serial to initialise
  Serial.println("boot succesfull");


}

int mode = EX;
void _update(void) {
  //digitalWrite(LED_BUILTIN, HIGH);
  curButton0Val = Button0Pressed();
  curButton1Val = Button1Pressed();
  curButton2Val = Button2Pressed();

  if (curButton0Val && !curButton1Val && !curButton2Val) {
    getColorInfo(0);
  }
  if (!curButton0Val && curButton1Val && !curButton2Val) {
    getColorInfo(1);
  }
  if (!curButton0Val && !curButton1Val && curButton2Val) {
    getColorInfo(2);
  }
  static int runcount0 = 0;
  static int runcount1 = 0;

  if (curButton0Val && curButton1Val && !curButton2Val) { //if button 0 and 1
    if (runcount0 == 0) {
      if (mode == EX) {
        mode = NORM;
      } else {
        mode = EX;
      }
      runcount0++;
    }
  } else {
    runcount0 = 0;
  }

  if (!curButton0Val && curButton1Val && curButton2Val) { //if button 1 and 2
    if (runcount1 == 0) {
      if (mode == NORM) {
        mode = ANIM;
      } else {
        mode = NORM;
      }
      runcount1++;
    }
  } else {
    runcount1 = 0;
  }

}

void checkSerial() {
  byte byteIn = 0;
  char input[25] = "";

  if (Serial.available() > 0) {
 // Serial.readBytesUntil('\n', input, 24);//get serial input
  
  
    byteIn = Serial.read();
    switch (byteIn) {
      case 'c':
        r = Serial.parseInt(SKIP_ALL, '\n');
        g = Serial.parseInt(SKIP_ALL, '\n');
        b = Serial.parseInt(SKIP_ALL, '\n');
        w = Serial.parseInt(SKIP_ALL, '\n');

        Serial.print(r);
        Serial.print(",");
        Serial.print(g);
        Serial.print(",");
        Serial.print(b);
        Serial.print(",");        
        Serial.println(w);
        break;

      default:
        Serial.println("Error");
        break;
    }

  
  }  
  while (Serial.available() > 0) {
      Serial.read();
    }
}

void loop() {
  _update();

  checkSerial();
  switch (mode) {
    case EX:
      strip.setBrightness(brightness);
      LEDstripExcluded(12, 41, strip.Color(r, g, b, w), strip.Color(0, 0, 0, 0));
      strip.show();
      break;

    case NORM:
      strip.setBrightness(brightness);
      strip.fill(strip.Color(r, g, b, w));
      strip.show();
      break;

    case ANIM:
      strip.clear();
      recursiveFlow(10, strip.Color(r, g, b, w), 10);
      break;
  }

}

void LEDstripExcluded(int exStart, int exEnd, uint32_t _color, uint32_t exColor) {
  //Exclude all leds specified
  for (int i = 0; i < exStart; i++) {
    strip.setPixelColor(i, _color);
  }

  for (int i = exStart; i < exEnd; i++) {
    strip.setPixelColor(i, exColor);
  }

  for (int i = exEnd; i < LED_COUNT; i++) {
    strip.setPixelColor(i, _color);
  }

}

bool Button0Pressed() {
  if (digitalRead(Button0) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

bool Button1Pressed() {
  if (digitalRead(Button1) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

bool Button2Pressed() {
  if (digitalRead(Button2) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

bool getColorInfo(int mode1) {
  switch (mode1) {

    case 0:
      brightness = (analogRead(brightnessPot) / 4); //to get max value of 255
      r = analogRead(huePot) / 4; //to get to a max value of 65536 for the hue
      hue *= 64;
      if (r > 255 || r < 0) {
        r = 0;
      }
      if (brightness > 255 || brightness < 0) {
        brightness = 0;
      }
      return 1;
      break;

    case 1:
      brightness = (analogRead(brightnessPot) / 4); //to get max value of 255
      g = analogRead(huePot) / 4; //to get to a max value of 65536 for the hue

      if (g > 255 || g < 0) {

        g = 0;
      }
      if (brightness > 255 || brightness < 0) {
        brightness = 0;
      }

      return 1;
      break;

    case 2:
      int prevw = w;
      w = (analogRead(brightnessPot) / 4); //to get max value of 255
      b = analogRead(huePot) / 4; //to get to a max value of 65536 for the hue

      if (b > 255 || b < 0) {
        b = 0;
      }
      if (w > 255 || w < 0) {
        w = 0;
      }

      if (w > brightness - 10 && w < brightness + 10) {
        w = prevw;
      }

      return 1;
      break;
  }

}

//my functions
void rainbowHue() {

  //int rainbowSpeed, int seconden
  uint32_t firstPixelHue = 0;
  unsigned long firstTime = millis();


  for (int i = 0; i < strip.numPixels(); i++) {

    int pixelHue = firstPixelHue + (i * 65536L * 7 / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    strip.show();
  }


}


void recursiveFlowHue(int colorLength, int delayy, int hueSpeedPMS) {
  for (int i = 0; i < strip.numPixels() + colorLength; i++) {


    if (i <= strip.numPixels())
      //doe huespeed * delayy zodat het hue speed getal per milliseconden is en niet
      //afhankelijk is van de snelheid van de strip dus als je strip sneller gaat
      //gaat de kleurverandering niet sneller.

      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue += hueSpeedPMS * delayy)));
    if (i - colorLength >= 0)
      strip.setPixelColor(i - colorLength, strip.Color(0, 0, 0, 0));

    strip.show();
    delay(delayy);
  }
  for (int i = strip.numPixels(); i > 0 - colorLength; i--) {


    if (i >= 0)
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue += hueSpeedPMS * delayy)));

    if (i + colorLength <= strip.numPixels())
      strip.setPixelColor(i + colorLength, strip.Color(0, 0, 0, 0));

    strip.show();
    delay(delayy);
  }
}

void recursiveFlow(int colorLength, uint32_t color, int delayy) {
  for (int i = 0; i < strip.numPixels() + colorLength; i++) {//forward
    _update();
    if (i <= strip.numPixels())
      strip.setPixelColor(i, color);

    if (i - colorLength >= 0)
      strip.setPixelColor(i - colorLength, strip.Color(0, 0, 0, 0));

    strip.show();
    delay(delayy);
  }

  for (int i = strip.numPixels(); i >= 0 - colorLength; i--) {//backwards
    _update();
    if (i >= 0)
      strip.setPixelColor(i, color);

    if (i + colorLength <= strip.numPixels())
      strip.setPixelColor(i + colorLength, strip.Color(0, 0, 0, 0));

    strip.show();
    delay(delayy);
  }
}



//strandtest functions.
void varLedcount(int a, uint32_t color) {
  if (aOld != a) {
    //enable all the leds to where the resistor is set
    for (int i = 0; i < a; i++) {
      strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
      strip.show();
    }
    //disable the ones that dont need to be on.
    for (int i = 300; i >= a; i--) {
      strip.setPixelColor(i, strip.Color(0, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
    }

  }
  a = aOld;

}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.



void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delayMicroseconds(wait);                           //  Pause for a moment
  }
}

void whiteOverRainbow(int whiteSpeed, int whiteLength) {

  if (whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int      head          = whiteLength - 1;
  int      tail          = 0;
  int      loops         = 3;
  int      loopNum       = 0;
  uint32_t lastTime      = micros();
  uint32_t firstPixelHue = 0;

  for (;;) { // Repeat forever (or until a 'break' or 'return')
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      if (((i >= tail) && (i <= head)) ||     //  If between head & tail...
          ((tail > head) && ((i >= tail) || (i <= head)))) {
        strip.setPixelColor(i, strip.Color(255, 255, 255, 255)); // Set white
      } else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
    }

    strip.show(); // Update strip with new contents
    // There's no delay here, it just runs full-tilt until the timer and
    // counter combination below runs out.

    firstPixelHue += 40; // Advance just a little along the color wheel

    if ((micros() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if (++head >= strip.numPixels()) {     // Advance head, wrap around
        head = 0;
        if (++loopNum >= loops) return;
      }
      if (++tail >= strip.numPixels()) {     // Advance tail, wrap around
        tail = 0;
      }
      lastTime = micros();                   // Save time of last movement
    }
  }
}

void pulseWhite(uint8_t wait) {
  for (int j = 0; j < 256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }

  for (int j = 255; j >= 0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
}

void pulseRed(uint8_t wait) {
  int g = 0;
  int b = 0;
  int s = 0;
  int d = 0;
  for (int j = 0; j < 256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    if (b <= 100 && d == 0) {
      b = b + 2;
    }
    else {
      b = b - 1;
      if (b <= 5) {
        d = 1;
      }
    }
    if (g <= 100 && s == 0) {
      g++;
    }
    else {
      g = g - 2;
      if (g <= 5) {
        s = 1;
      }
    }
    strip.fill(strip.Color(strip.gamma8(g), strip.gamma8(j), strip.gamma8(b), 0));
    strip.show();
    delayMicroseconds(wait);
  }

  for (int j = 255; j >= 0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(strip.gamma8(g), strip.gamma8(j), strip.gamma8(b), 0));
    strip.show();
    delayMicroseconds(wait);
  }
}

void rainbowFade2White(int wait, int rainbowLoops, int whiteLoops) {
  int fadeVal = 50, fadeMax = 255;

  // Hue of first pixel runs 'rainbowLoops' complete loops through the color
  // wheel. Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to rainbowLoops*65536, using steps of 256 so we
  // advance around the wheel at a decent clip.
  for (uint32_t firstPixelHue = 0; firstPixelHue < rainbowLoops * 65536;
       firstPixelHue += 256) {

    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...

      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      uint32_t pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());

      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the three-argument variant, though the
      // second value (saturation) is a constant 255.
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue, 255,
                                           255 * fadeVal / fadeMax)));
    }

    strip.show();
    delayMicroseconds(wait);

    if (firstPixelHue < 65536) {                             // First loop,
      if (fadeVal < fadeMax) fadeVal++;                      // fade in
    } else if (firstPixelHue >= ((rainbowLoops - 10) * 65536)) { // Last loop,
      if (fadeVal > 0) fadeVal--;                            // fade out
    } else {
      fadeVal = fadeMax; // Interim loop, make sure fade is at max
    }
  }

  for (int k = 0; k < whiteLoops; k++) {
    for (int j = 0; j < 256; j++) { // Ramp up 0 to 255
      // Fill entire strip with white at gamma-corrected brightness level 'j':
      strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
      strip.show();
    }
    delay(1000); // Pause 1 second
    for (int j = 255; j >= 0; j--) { // Ramp down 255 to 0
      strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
      strip.show();
    }
  }

  delayMicroseconds(500); // Pause 1/2 second
}
