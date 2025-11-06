#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "driver/spi_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

/* 
 * This assumes LVGL is already initialized somewhere in your main setup
 * (for example in main() or before calling this code):
 * 
 * lv_init();
 * driver_init(); // your display/input driver
 * 
 * If not yet, we’ll show you that below.
 */

void create_simple_ui(void) {
    /* Create a screen object */
    lv_obj_t * screen = lv_obj_create(NULL);

    /* Create a label (text element) */
    lv_obj_t * label = lv_label_create(screen);
    lv_label_set_text(label, "Hello, LVGL!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0); // center text

    /* Create a simple button */
    lv_obj_t * btn = lv_btn_create(screen);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 40); // below label

    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click Me!");

    /* Load the screen */
    lv_scr_load(screen);
}

#define LCD_HOST              SPI2_HOST
#define LCD_PIN_NUM_MOSI      23
#define LCD_PIN_NUM_SCLK      18
#define LCD_PIN_NUM_CS        5
#define LCD_PIN_NUM_DC        2
#define LCD_PIN_NUM_RST       4
#define LCD_PIN_NUM_BCKL      15

#define LCD_HOR_RES           240
#define LCD_VER_RES           240

#define LVGL_DRAW_BUF_LINES   40

static esp_lcd_panel_handle_t s_panel_handle;

static void lvgl_tick_cb(void *arg) {
    lv_tick_inc(1);
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
    int x1 = area->x1;
    int y1 = area->y1;
    int x2 = area->x2 + 1;
    int y2 = area->y2 + 1;
    esp_lcd_panel_draw_bitmap(s_panel_handle, x1, y1, x2, y2, color_p);
    lv_disp_flush_ready(drv);
}

static void lvgl_task(void *arg) {
    while (1) {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void) {
    lv_init();

    spi_bus_config_t buscfg = {
        .mosi_io_num = LCD_PIN_NUM_MOSI,
        .miso_io_num = -1,
        .sclk_io_num = LCD_PIN_NUM_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_HOR_RES * LVGL_DRAW_BUF_LINES * sizeof(lv_color_t)
    };
    spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO);

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = LCD_PIN_NUM_DC,
        .cs_gpio_num = LCD_PIN_NUM_CS,
        .pclk_hz = 40000000,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    esp_lcd_new_panel_io_spi(LCD_HOST, &io_config, &io_handle);

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_PIN_NUM_RST,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };
    esp_lcd_new_panel_st7789(io_handle, &panel_config, &s_panel_handle);
    esp_lcd_panel_reset(s_panel_handle);
    esp_lcd_panel_init(s_panel_handle);
    esp_lcd_panel_set_gap(s_panel_handle, 0, 0);

    lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(LCD_HOR_RES * LVGL_DRAW_BUF_LINES * sizeof(lv_color_t), MALLOC_CAP_DMA);
    lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(LCD_HOR_RES * LVGL_DRAW_BUF_LINES * sizeof(lv_color_t), MALLOC_CAP_DMA);
    lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LCD_HOR_RES * LVGL_DRAW_BUF_LINES);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_HOR_RES;
    disp_drv.ver_res = LCD_VER_RES;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lvgl_tick_cb,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "lv_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    esp_timer_create(&periodic_timer_args, &lvgl_tick_timer);
    esp_timer_start_periodic(lvgl_tick_timer, 1000);

    xTaskCreate(lvgl_task, "lvgl", 4096, NULL, 5, NULL);

    create_simple_ui();
}
