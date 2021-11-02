#pragma once

#include <M5StickCPlus.h>
#include "View.h"



    
class DiceView : public View
{
public:
    DiceView();
    ~DiceView();
    void draw_dice(int16_t x, int16_t y, int n);
    void render();
    bool receive_event(EVENTS::event event){ return false; };

private:
    
    
    TFT_eSprite *disp_buffer;


};
