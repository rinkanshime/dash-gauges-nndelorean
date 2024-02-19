/*
 * -------------------------------------------------------------------
 * NNDeLorean Dash Gauges
 * DeLorean DMC-12 Time Machine Plutonium Gauges Panel prop
 * from Back to the Future trilogy 
 * created for NNDeLorean - first russian DMC-12 Time Machine
 * (C) 2024 Mark Michurin (Rinkanshime)
 * -------------------------------------------------------------------
 * Панель Индикаторов NNDeLorean
 * Реплика панели Плутониевых Индикаторов машины времени DeLorean DMC-12
 * из трилогии Назад в Будущее
 * создано для NNDeLorean - первой российской конвертации DMC-12 в машину времени
 * (С) 2024 Марк Мичурин (Rinkanshime)
 * -------------------------------------------------------------------
 * https://github.com/rinkanshime/dash-gauges-nndelorean
 * https://nndelorean.ru
 * -------------------------------------------------------------------
 * License: AGPLv3
 * -------------------------------------------------------------------
 * !!! WARNING !!!
 * Функция analogSetWidth() отключена в файле dg_audio.cpp:129, т.к. она отсутствует в ESP32S2
 * Снова включена для  NodeMCU-32S
 * -------------------------------------------------------------------
 */

#include "dg_global.h"

#include <Arduino.h>
#include <Wire.h>

#include "dg_audio.h"
#include "dg_settings.h"
#include "dg_wifi.h"
#include "dg_main.h"

void setup()
{
    powerupMillis = millis();
    
    Serial.begin(115200);
    Serial.println();

    Wire.begin(-1, -1, 100000);

    main_boot();
    settings_setup();
    main_boot2();
    wifi_setup();
    audio_setup();
    main_setup();
    bttfn_loop();
}

void loop()
{    
    main_loop();
    audio_loop();
    wifi_loop();
    audio_loop();
    bttfn_loop();
}
