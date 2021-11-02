#pragma once

#include <M5StickCPlus.h>
#include "View.h"
#include <midea_ir.h>

#define grey 0x65DB

class StepView : public View
{
public:
    StepView();
    ~StepView();

    void render();
    bool receive_event(EVENTS::event event){ return false; };

private:
    
    void blinkenLight();
    const uint8_t MIDEA_RMT_CHANNEL = 0;
    const uint8_t MIDEA_TX_PIN = 9;
    MideaIR ir;
    

    TFT_eSprite *disp_buffer;
};
