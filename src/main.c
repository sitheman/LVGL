#include <stdbool.h>

#include "lvgl.h"
#include "lv_demos.h"
#include "hal/sdl_port.h"

#include LV_SDL_INCLUDE_PATH

int main(void) {
    lv_init();
    lv_port_sdl_init();

    lv_demo_widgets();

    while(true) {
        lv_timer_handler();
        SDL_Delay(5);
    }

    return 0;
}
