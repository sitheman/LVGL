# SPDX-License-Identifier: MIT
# Minimal SDL2 finder that creates SDL2::SDL2 and (when available) SDL2::SDL2main targets.

if(SDL2_FOUND)
    return()
endif()

find_path(SDL2_INCLUDE_DIR
    NAMES SDL.h
    HINTS ENV SDL2_DIR
    PATH_SUFFIXES include include/SDL2 SDL2)

find_library(SDL2_LIBRARY
    NAMES SDL2 SDL2-static
    HINTS ENV SDL2_DIR
    PATH_SUFFIXES lib lib64)

find_library(SDL2MAIN_LIBRARY
    NAMES SDL2main SDL2main-static
    HINTS ENV SDL2_DIR
    PATH_SUFFIXES lib lib64)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2
    REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)

if(SDL2_FOUND AND NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 UNKNOWN IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION ""
        INTERFACE_INCLUDE_DIRECTORIES "")
endif()

if(SDL2_FOUND AND SDL2MAIN_LIBRARY AND NOT TARGET SDL2::SDL2main)
    add_library(SDL2::SDL2main UNKNOWN IMPORTED)
    set_target_properties(SDL2::SDL2main PROPERTIES
        IMPORTED_LOCATION ""
        INTERFACE_INCLUDE_DIRECTORIES "")
endif()

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY SDL2MAIN_LIBRARY)
