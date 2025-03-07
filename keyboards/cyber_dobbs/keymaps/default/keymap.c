// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//Source: https://gist.github.com/joe-scotto/dfa2da0fb0d14291d295aeef6728707d
#ifdef OLED_ENABLE

// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

// Animation parameters
#define FRAME_DURATION 333 // How long each frame lasts in milliseconds

// Animation variables
uint32_t timer = 0;
uint8_t current_frame = 0;

// Render animation
static void render_animation(void) {
    // Frame 1
    static const char epd_bitmap_frame_1_delay_0 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xfe, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x0f, 0x03, 
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 
        0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xfc, 0xfe, 0x1e, 0x0f, 0x07, 0x07, 
        0x03, 0x03, 0x06, 0x0e, 0x1c, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 
        0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x1f, 0x3f, 0x3f, 0x3c, 0x7c, 0x78, 
        0x78, 0x38, 0x38, 0x3c, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
        0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf8, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
        0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xfe, 
        0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0x87, 0x87, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xfc, 0x7c, 0x3e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x3e, 0xfc, 0xf8, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 
        0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xc3, 0xc3, 0xc0, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x38, 0x70, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x70, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xf8, 0x7c, 0x3c, 0x3c, 0x1c, 
        0x3c, 0x38, 0x78, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0xf1, 0xf1, 
        0xf1, 0xf1, 0xf1, 0xf1, 0xe1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x3f, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x7f, 0x7f, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 
        0xc0, 0xe0, 0xe0, 0x79, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
        0xfe, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xc0, 
        0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 
        0x0d, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1f, 0x1f, 0x3f, 0x7f, 
        0x03, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 
        0xfe, 0xfe, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfe, 0xff, 0x9f, 0x07, 0x03, 
        0x03, 0x03, 0x03, 0x03, 0x07, 0x0f, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xe0, 0xf0, 0xf8, 0xff, 0xff, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0x87, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0e, 0x0c, 
        0x1c, 0x1c, 0x1c, 0x1c, 0x0e, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x3e, 0x3e, 0x7c, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x80, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 
        0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    // Frame 2
    static const char epd_bitmap_frame_0_delay_0 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xfe, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x0f, 0x03, 
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
        0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 
        0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xe0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xfc, 0xfe, 0x1e, 0x0f, 0x07, 0x07, 
        0x03, 0x03, 0x06, 0x0e, 0x1c, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
        0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x1f, 0x3f, 0x3f, 0x3c, 0x7c, 0x78, 
        0x78, 0x38, 0x38, 0x3c, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 
        0xf8, 0x78, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf8, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
        0xff, 0x3e, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 
        0x0f, 0x0f, 0x0e, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xfe, 
        0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xfc, 0x7c, 0x3e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x3e, 0xfc, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 
        0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x38, 0x70, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x70, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xf8, 0x7c, 0x3c, 0x3c, 0x1c, 
        0x3c, 0x38, 0x78, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe1, 0xe1, 0xe1, 
        0xe1, 0xe1, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x3f, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x7f, 0x7f, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 
        0xc0, 0xe0, 0xe0, 0x79, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xc0, 
        0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 
        0x3f, 0x3f, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1f, 0x1f, 0x3f, 0x7f, 
        0x03, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 
        0x1e, 0xfe, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfe, 0xff, 0x9f, 0x07, 0x03, 
        0x03, 0x03, 0x03, 0x03, 0x07, 0x0f, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xe0, 0xf0, 0xf8, 0xff, 0xff, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xc0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0e, 0x0c, 
        0x1c, 0x1c, 0x1c, 0x1c, 0x0e, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 
        0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x3e, 0x3e, 0x7c, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 
        0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    // Animation frames array
    const char* epd_bitmap_allArray [] = {
        epd_bitmap_frame_0_delay_0,
        epd_bitmap_frame_1_delay_0
    };  

    // Frame sizes array
    uint16_t frame_sizes[2] = {
        sizeof(epd_bitmap_frame_0_delay_0),
        sizeof(epd_bitmap_frame_1_delay_0)
    };

    // Run animation
    if (timer_elapsed(timer) > FRAME_DURATION) {
        // Set timer to updated time
        timer = timer_read();
        
        // Increment frame
        current_frame = (current_frame + 1) % (sizeof(epd_bitmap_allArray) / sizeof(epd_bitmap_allArray[0]));

        // Draw frame to OLED
        oled_write_raw_P(epd_bitmap_allArray[current_frame], frame_sizes[current_frame]); 
    }
}

// Draw to OLED
bool oled_task_user() {
    // Run Animation
    render_animation(); 

    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┼─
     * │ 4 │ 5 │ 6 │ 
     * ├───┼───┼───┼
     * │ 1 │ 2 │ 3 │ 
     * ├───┼───┼───┼─
     */

    [0] = LAYOUT(
        KC_A,   KC_B,   KC_C,
        KC_D,   KC_E,   KC_F,
        KC_G,   KC_H,   KC_I
    )
};
