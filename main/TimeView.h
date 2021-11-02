#pragma once

#include <M5StickCPlus.h>
#include "View.h"
#include "7seg20.h"
#include "7seg70.h"
#include "data.h"
#include <midea_ir.h>
#define grey 0x65DB

class TimeView : public View
{
public:
    TimeView();
    ~TimeView();

    void render();
    bool receive_event(EVENTS::event event){ return false; };

private:
    uint8_t h_cache = 25;
    uint8_t m_cache = 60;
    uint8_t s_cache = 60;
    uint8_t d_cache = 10;
    uint8_t dt_cache = 35;
    uint8_t mn_cache = 35;
    uint16_t yr_cache = 0;

    char timeHHMM[5];
    char seconds[2];
    char day[10];
    void switchmidea();
    void blinkenLight();
    const uint8_t MIDEA_RMT_CHANNEL = 0;
    const uint8_t MIDEA_TX_PIN = 9;
    MideaIR ir;
    float accX = 0;
    float accY = 0;
    float accZ = 0;
    TFT_eSprite *disp_buffer;
    TFT_eSprite *disp_buffer2;
};
