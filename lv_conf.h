#ifndef LV_CONF_H
#define LV_CONF_H

/* Enable lv_conf.h inclusion without relative paths */
#define LV_CONF_INCLUDE_SIMPLE

#include <stdint.h>

#define LV_COLOR_DEPTH 32
#define LV_COLOR_SCREEN_TRANSP 0
#define LV_COLOR_CHROMA_KEY   lv_color_hex(0x00ff00)

#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (256U * 1024U)

#define LV_USE_DRAW_SW 1
#define LV_USE_GPU_SDL 0

#define LV_USE_LOG 1
#define LV_LOG_LEVEL LV_LOG_LEVEL_INFO
#define LV_LOG_PRINTF 1

#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_DEFAULT &lv_font_montserrat_16

#define LV_USE_DEMO_WIDGETS 1
#define LV_USE_DEMO_MUSIC 0
#define LV_USE_DEMO_BENCHMARK 0
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0

#define LV_USE_SDL 1
#define LV_SDL_INCLUDE_PATH <SDL2/SDL.h>
#define LV_SDL_DIRECT_EXIT 0
#define LV_SDL_RENDER_MODE LV_DISPLAY_RENDER_MODE_FULL

#endif /* LV_CONF_H */
