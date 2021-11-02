/*

A couple of dices on a tiny 80x160px TFT display

Author: Alfonso de Cala <alfonso@el-magnifico.org>

*/

#include <M5StickCPlus.h>
#include "View.h"
#include "DiceView.h"
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
static const char *TAG = "DICE_VIEW";
float accX = 0;
float accY = 0;
float accZ = 0;
    int dot[6][6][2] {
      {{35,35}},
      {{15,15},{55,55}},
      {{15,15},{35,35},{55,55}},
      {{15,15},{15,55},{55,15},{55,55}},
      {{15,15},{15,55},{35,35},{55,15},{55,55}},
      {{15,15},{15,35},{15,55},{55,15},{55,35},{55,55}},
      };
#define DOT_SIZE 6

DiceView::DiceView() {
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setSwapBytes(false);
  M5.Lcd.setRotation(1);
  disp_buffer = new TFT_eSprite(&M5.Lcd);
  disp_buffer->createSprite(240, 135);
  disp_buffer->setSwapBytes(false);
  //disp_buffer->setRotation(1);
  disp_buffer->fillRect(0, 0, 240, 135, TFT_GREEN);
  
  disp_buffer->setTextColor(TFT_BLACK);  // Adding a background colour erases previous text automatically


  disp_buffer->setCursor(10, 30);  
  disp_buffer->setTextSize(3);
  disp_buffer->drawString("SHAKE ME",100,50,2);  
  disp_buffer->pushSprite(0, 0);
  delay(1000);
}
DiceView::~DiceView()
{
    ESP_LOGD(TAG, "Destructor called");
    disp_buffer->deleteSprite();
    delete disp_buffer;
    ESP_LOGD(TAG, "Destructor finished");
}

void DiceView::draw_dice(int16_t x, int16_t y, int n) {

  disp_buffer->fillRect(x, y, 70, 70, WHITE);

  for(int d = 0; d < 6; d++) {
    if (dot[n][d][0] > 0) {
        disp_buffer->fillCircle(x+dot[n][d][0], y+dot[n][d][1], DOT_SIZE, TFT_BLACK);
    }
  }  
  
}


void DiceView::render() { 
    
    M5.IMU.getAccelData(&accX,&accY,&accZ);
    if (accX > 1.5 ||  accY > 1.5 ) {
        disp_buffer->fillRect(0, 0, 240, 135, TFT_GREEN);
      // Draw first dice
        delay(500);  // A little delay to increase suspense :-D
        int number = random(0, 6);
        draw_dice(5,30,number);
      
        // Draw second dice
        delay(500);
        number = random(0, 6);
        draw_dice(85,30,number);
      // Draw third dice
        delay(500);
        number = random(0, 6);
        draw_dice(160,30,number);
        
  }

  

  
  disp_buffer->pushSprite(0, 0);

}
