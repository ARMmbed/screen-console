// ----------------------------------------------------------------------------
// Copyright 2016-2019 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

/**
 * Screen size and font combinations:
 *
 * Font8
 * Width:  159
 * Height: 61
 * Font:    1
 *
 * Font12
 * Width:  114
 * Height: 41
 * Font:    2
 *
 * Font16
 * Width:  72
 * Height: 31
 * Font:    3
 *
 * Font20
 * Width:  57
 * Height: 25
 * Font:    4
 *
 * Font24
 * Width:  47
 * Height: 21
 * Font:    5
 *
 */

#include "screen_console_api.h"

#include "stm32f769i_discovery_lcd.h"

#ifndef MBED_CONF_SCREEN_CONSOLE_PORTRAIT_MODE
#define MBED_CONF_SCREEN_CONSOLE_PORTRAIT_MODE 1
#endif

#ifndef MBED_CONF_SCREEN_CONSOLE_FONT_SIZE
#define MBED_CONF_SCREEN_CONSOLE_FONT_SIZE 1
#endif

#ifndef MBED_CONF_SCREEN_CONSOLE_BACKGROUND_COLOR
#define MBED_CONF_SCREEN_CONSOLE_BACKGROUND_COLOR LCD_COLOR_GREEN
#endif

#ifndef MBED_CONF_SCREEN_CONSOLE_TEXT_COLOR
#define MBED_CONF_SCREEN_CONSOLE_TEXT_COLOR LCD_COLOR_BLACK
#endif

void screen_console_init(void)
{
    /* set orientation. */
    if (MBED_CONF_SCREEN_CONSOLE_PORTRAIT_MODE) {
        BSP_LCD_InitEx(LCD_ORIENTATION_PORTRAIT);
    } else {
        BSP_LCD_InitEx(LCD_ORIENTATION_LANDSCAPE);
    }

    BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);

    /* set font size. */
    if (MBED_CONF_SCREEN_CONSOLE_FONT_SIZE <= 1) {
        BSP_LCD_SetFont(&Font8);
    } else if (MBED_CONF_SCREEN_CONSOLE_FONT_SIZE <= 2) {
        BSP_LCD_SetFont(&Font12);
    } else if (MBED_CONF_SCREEN_CONSOLE_FONT_SIZE <= 3) {
        BSP_LCD_SetFont(&Font16);
    } else if (MBED_CONF_SCREEN_CONSOLE_FONT_SIZE <= 4) {
        BSP_LCD_SetFont(&Font20);
    } else {
        BSP_LCD_SetFont(&Font24);
    }

    /* set colors */
    BSP_LCD_Clear(MBED_CONF_SCREEN_CONSOLE_BACKGROUND_COLOR);
    BSP_LCD_SetBackColor(MBED_CONF_SCREEN_CONSOLE_BACKGROUND_COLOR);
    BSP_LCD_SetTextColor(MBED_CONF_SCREEN_CONSOLE_TEXT_COLOR);
}

void screen_console_clear_line(size_t line)
{
    BSP_LCD_ClearStringLine(line);
}

void screen_console_write_line(size_t line, const char* string)
{
    BSP_LCD_DisplayStringAtLine(line, (uint8_t*) string);
}
