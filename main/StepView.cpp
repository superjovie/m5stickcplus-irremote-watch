#include <M5StickCPlus.h>
#include "View.h"
#include "StepView.h"
#include <midea_ir.h>


static const char *TAG = "STEP_VIEW";

extern RTC_TimeTypeDef RTC_TimeStruct;
extern RTC_DateTypeDef RTC_DateStruct;
extern String days[7];

StepView::StepView()
{
    M5.begin();
    pinMode(M5_BUTTON_RST, INPUT_PULLUP);
    pinMode(M5_BUTTON_HOME, INPUT_PULLUP);
    M5.Lcd.setRotation(0);
    M5.Lcd.setSwapBytes(false);
    M5.Axp.EnableCoulombcounter();
    midea_ir_init(&ir, MIDEA_RMT_CHANNEL, MIDEA_TX_PIN);
    pinMode(10, OUTPUT);
    // set mode, temperature and fan level and internal state to enabled
    ir.enabled = true;
    ir.mode = MODE_HEAT;
    ir.fan_level = 3;
    ir.temperature = 27;

    disp_buffer = new TFT_eSprite(&M5.Lcd);

    disp_buffer->setSwapBytes(false);
    disp_buffer->createSprite(135, 240);
    disp_buffer->fillRect(0, 0, 135, 240, BLACK);
    disp_buffer->pushSprite(0, 0);
    disp_buffer->setTextSize(2);
    disp_buffer->setTextColor(TFT_RED, TFT_BLACK);
    disp_buffer->drawString("Midea", 30, 200, 2);
    disp_buffer->setTextSize(5);
    disp_buffer->setTextColor(TFT_WHITE, TFT_BLACK);
    
}

StepView::~StepView()
{
    ESP_LOGD(TAG, "Destructor called");
    disp_buffer->deleteSprite();
    delete disp_buffer;
    ir.~MideaIR();
    ESP_LOGD(TAG, "Destructor finished");
    midea_ir_stop(MIDEA_RMT_CHANNEL);
}

void StepView::render()
{
    M5.update();
    if (digitalRead(M5_BUTTON_HOME) == LOW)
    {
        if(ir.temperature==30){ir.temperature=18;}
        else{ir.temperature++;}
        
        midea_ir_send(&ir);
        blinkenLight();
        
    }
    
    delay(100);
    if (M5.BtnB.isPressed())
    {
        if(ir.mode==MODE_HEAT){ir.mode=MODE_COOL;}
        else{ir.mode=MODE_HEAT;}
    }
    disp_buffer->setTextSize(3);
    disp_buffer->setTextColor(grey, TFT_BLACK);
    if(ir.mode==MODE_HEAT){disp_buffer->drawString("HAET", 25, 25, 2);}
    if(ir.mode==MODE_COOL){disp_buffer->drawString("COOL", 25, 25, 2);}
    disp_buffer->setTextSize(5);
    disp_buffer->setTextColor(TFT_WHITE, TFT_BLACK);
    disp_buffer->drawString(String(ir.temperature), 30, 110, 2);

    disp_buffer->pushSprite(0, 0);
    
}




void StepView::blinkenLight()
{
    digitalWrite(10, LOW);
    delay(100);
    digitalWrite(10, HIGH);
}
