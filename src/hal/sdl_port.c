#include "sdl_port.h"

#include "lvgl/src/drivers/sdl/lv_sdl_keyboard.h"
#include "lvgl/src/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/src/drivers/sdl/lv_sdl_mousewheel.h"
#include "lvgl/src/drivers/sdl/lv_sdl_window.h"

#define LV_DEMO_HOR_RES 800
#define LV_DEMO_VER_RES 480

void lv_port_sdl_init(void) {
    lv_display_t * disp = lv_sdl_window_create(LV_DEMO_HOR_RES, LV_DEMO_VER_RES);
    if(!disp) {
        LV_LOG_ERROR("SDL window create failed");
        return;
    }

    lv_sdl_window_set_title(disp, "LVGL SDL Demo");
    lv_display_set_default(disp);

    lv_indev_t * mouse = lv_sdl_mouse_create();
    if(mouse) {
        lv_indev_set_display(mouse, disp);
    }

    lv_indev_t * wheel = lv_sdl_mousewheel_create();
    if(wheel) {
        lv_indev_set_display(wheel, disp);
    }

    lv_indev_t * keyboard = lv_sdl_keyboard_create();
    if(keyboard) {
        lv_indev_set_display(keyboard, disp);
    }
}
