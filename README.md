# LVGL SDL Starter

A minimal LVGL project that targets the desktop SDL driver so you can experiment with widgets without any hardware. The repo keeps LVGL as a git submodule and builds a tiny launcher that runs lv_demo_widgets().

## Prerequisites

- CMake 3.22+
- A C11 compiler toolchain (MSVC/Clang/GCC)
- SDL2 development libraries available on your system (SDL2/SDL.h must be discoverable). On Windows the easiest option is cpkg install sdl2, on Linux sudo apt install libsdl2-dev works, and on macOS you can rew install sdl2.

## Getting started

`powershell
# grab the repo and its submodules
git clone <your fork url> lvgl-sdl-starter
cd lvgl-sdl-starter
git submodule update --init --recursive

# configure + build
cmake -S . -B build -G "Ninja"
cmake --build build

# run the sample
./build/lvgl_demo
`

The app opens an 800x480 SDL window and shows the stock LVGL widget demo. Close the window or hit Ctrl+C in the terminal to exit.

## Customizing

- Update lv_conf.h if you need fonts, themes, different resolutions, etc.
- Drop your own UI code in src/main.c and call it instead of lv_demo_widgets().
- You can tweak the helper in src/hal/sdl_port.c if you want to change the default resolution, window title, or connect extra SDL input devices.

## Publishing to GitHub

1. Create a new (empty) repo on GitHub.
2. In this folder run:
   `powershell
   git remote add origin https://github.com/<user>/<repo>.git
   git branch -M main
   git add .
   git commit -m "Initial LVGL SDL starter"
   git push -u origin main
   `
3. Share the repo and start iterating on your app.

Happy hacking!
