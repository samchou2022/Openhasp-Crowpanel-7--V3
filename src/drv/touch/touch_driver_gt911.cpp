/* MIT License - Copyright (c) 2019-2024 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#if defined(ARDUINO) && (TOUCH_DRIVER == 0x0911) && defined(HASP_USE_TAMC_GT911)
#include <Arduino.h>
#include "ArduinoLog.h"
#include "hasp_conf.h"
#include "touch_driver_gt911.h"

#include <esp_task_wdt.h> // for watchdog reset
#include <Wire.h>
#include "TAMC_GT911.h"

#if ESP32
#include "esp_task_wdt.h"
#endif

#include "touch_driver.h" // base class
#include "touch_helper.h" // i2c scanner

#include "../../hasp/hasp.h" // for hasp_sleep_state
extern uint8_t hasp_sleep_state;

static TAMC_GT911 touch = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_IRQ, TOUCH_RST, max(TOUCH_WIDTH, TOUCH_HEIGHT), min(TOUCH_WIDTH, TOUCH_HEIGHT));
// static int8_t GT911_num_touches;
// static GTPoint* GT911_points;

// Touch state variables (for debugging if needed)
static bool touch_pressed = false;
static uint16_t touch_x = 0;
static uint16_t touch_y = 0;

namespace dev {

IRAM_ATTR bool TouchGt911::read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
{
    // Feed watchdog to prevent timeout
    //esp_task_wdt_reset();

    // Read touch data from TAMC_GT911
    touch.read();

    if(touch.isTouched) {
        if(hasp_sleep_state != HASP_SLEEP_OFF) hasp_update_sleep_state(); // update Idle

        // Get raw coordinates from TAMC_GT911
        uint16_t raw_x = touch.points[0].x;
        uint16_t raw_y = touch.points[0].y;

        // Apply coordinate mapping/calibration (based on your v0.6 working solution)
        // X axis: invert (800 - x)
        // Y axis: invert (480 - y)
        uint16_t corrected_x = TFT_WIDTH - raw_x;
        uint16_t corrected_y = TFT_HEIGHT - raw_y;

        // Ensure coordinates are within bounds
        if(corrected_x >= TFT_WIDTH) corrected_x = TFT_WIDTH - 1;
        if(corrected_y >= TFT_HEIGHT) corrected_y = TFT_HEIGHT - 1;

        // DEBUG: Uncomment for calibration testing
        // Serial.printf("Touch: RAW(%d,%d) -> CORRECTED(%d,%d)\n", raw_x, raw_y, corrected_x, corrected_y);

        data->point.x = corrected_x;
        data->point.y = corrected_y;
        data->state   = LV_INDEV_STATE_PR;

        hasp_set_sleep_offset(0); // Reset the offset
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}

void TouchGt911::init(int w, int h)
{
    // Feed watchdog during initialization
    //esp_task_wdt_reset();

    // Add delay for stability
    delay(100);
    //esp_task_wdt_reset();

    // Initialize I2C with lower frequency for stability
    Wire.begin(TOUCH_SDA, TOUCH_SCL, 100000);
    delay(50);
    //esp_task_wdt_reset();

    // Initialize TAMC_GT911
    touch.begin();
    delay(100);
    //esp_task_wdt_reset();

    // Simple log without memory debug to avoid watchdog timeout
    Serial.println("TAMC_GT911 Touch Driver Started");

    // Final delay for stability
    delay(50);
    //esp_task_wdt_reset();
}

} // namespace dev

dev::TouchGt911 haspTouch;

#endif // ARDUINO
