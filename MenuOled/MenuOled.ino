#include <Preferences.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <assets.h>

Preferences pref;
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

const int PushButtonUp =12;
const int PushButtonDown =26;
int brightness;

// Array of all bitmaps for convenience.
const unsigned char* items[9] = {
  bitmap_game,
  bitmap_brightness,
  bitmap_images, 
  bitmap_game,
  bitmap_brightness,
  bitmap_images, 
  bitmap_game,
  bitmap_brightness,
  bitmap_images
};

int previousItem = 0;
int currentItem = 1;
int nextItem = 2;


// Create Sprites
TFT_eSprite sprPrev = TFT_eSprite(&tft);
TFT_eSprite sprCurrent = TFT_eSprite(&tft);
TFT_eSprite sprNext = TFT_eSprite(&tft);
TFT_eSprite sprIndicatorUp = TFT_eSprite(&tft);
TFT_eSprite sprIndicatorDown = TFT_eSprite(&tft);

void setup(void) {
  // Create a namespace called "settings" with read/write mode
  pref.begin("settings", false);
  
  // Read the last brightness from NVS flash memory
  brightness = pref.getInt("brightness", 255);
  analogWrite(5, brightness);
  
  Serial.begin(115200);
  pinMode(PushButtonUp, INPUT);
  pinMode(PushButtonDown, INPUT);
  tft.init();
  tft.fillScreen(TFT_BLACK);

  // Setup sprite dimensions
  sprPrev.createSprite(180, 64);
  sprCurrent.createSprite(180, 64);
  sprNext.createSprite(180, 64);
  sprIndicatorUp.createSprite(180, 9);
  sprIndicatorDown.createSprite(180, 9);

  // Draw initial items to sprites
  drawItems();
}

void drawItems() {
  // Clear sprites before drawing
  sprPrev.fillSprite(TFT_BLACK);
  sprCurrent.fillSprite(TFT_BLACK);
  sprNext.fillSprite(TFT_BLACK);
  sprIndicatorUp.fillSprite(TFT_BLACK);
  sprIndicatorDown.fillSprite(TFT_BLACK);

  // Draw bitmaps onto sprites
  sprPrev.drawBitmap(0, 0, items[previousItem], 180, 64, TFT_WHITE, TFT_BLACK);
  sprCurrent.drawBitmap(0, 0, items[currentItem], 180, 64, TFT_WHITE, TFT_BLACK);
  sprNext.drawBitmap(0, 0, items[nextItem], 180, 64, TFT_WHITE, TFT_BLACK);
  sprIndicatorUp.drawBitmap(0, 0, bitmap_upSel, 180, 9, TFT_WHITE, TFT_BLACK);
  sprIndicatorDown.drawBitmap(0, 0, bitmap_upSel, 180, 9, TFT_WHITE, TFT_BLACK);

  // Push sprites to the display
  sprPrev.pushSprite(30, 0);
  sprCurrent.pushSprite(30, 88);
  sprNext.pushSprite(30, 176);
  sprIndicatorUp.pushSprite(32, 80);
  sprIndicatorDown.pushSprite(30, 148);
}

void loop() {
  int Push_button_state_up = digitalRead(PushButtonUp);
  int Push_button_state_down = digitalRead(PushButtonDown);

  if (Push_button_state_up == HIGH) {  // Button pressed
    
    // Scroll to the next items
    previousItem -= 1;
    currentItem -= 1;
    nextItem -= 1;

    // Wrap around the array index
    previousItem = (previousItem + 9) % 9;
    currentItem = (currentItem + 9) % 9;
    nextItem = (nextItem + 9) % 9;

    // Draw the updated items
    drawItems();
  }
    if (Push_button_state_down == HIGH) {  // Button pressed
    
    // Scroll to the next items
    previousItem += 1;
    currentItem += 1;
    nextItem += 1;

    // Wrap around the array index
    previousItem = (previousItem + 9) % 9;
    currentItem = (currentItem + 9) % 9;
    nextItem = (nextItem + 9) % 9;

    // Draw the updated items
    drawItems();
  }
  
}
