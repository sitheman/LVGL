cmake_minimum_required(VERSION 3.22)
project(lvgl_sdl_starter LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

list(PREPEND CMAKE_MODULE_PATH "/cmake")

set(LV_BUILD_CONF_PATH "/lv_conf.h" CACHE PATH "")
set(CONFIG_LV_BUILD_DEMOS ON CACHE BOOL "" FORCE)
set(CONFIG_LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/lvgl)

find_package(SDL2 REQUIRED)

add_executable(lvgl_demo
    src/main.c
    src/hal/sdl_port.c)

if(TARGET SDL2::SDL2main)
    target_link_libraries(lvgl_demo PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(lvgl_demo PRIVATE lvgl lvgl_demos SDL2::SDL2)

target_include_directories(lvgl_demo PRIVATE
    
    /src)

set_target_properties(lvgl_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "/bin")
