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

#include "ScreenConsole.h"

#include "screen_console_api.h"

ScreenConsole::ScreenConsole(void)
    : currentLine(0), currentPosition(0)
{
    screen_console_init();
}

ssize_t ScreenConsole::write(const void *buffer, size_t size)
{
    const char* input = (const char*) buffer;
    bool redrawFullScreen = false;

    for (size_t index = 0; index < size; index++) {

        char character = input[index];

        switch (character) {
            case '\r':
                /* carriage return, move cursor to beginning of line. */
                currentPosition = 0;
                break;
            case '\n':
                /* new line, move cursor to beginning of line, increment line. */
                currentPosition = 0;
                currentLine++;

                /* wrap around when line crosses screen. */
                currentLine = (currentLine % SCREEN_HEIGHT);

                /* NULL terminate new line before using it. */
                screenBuffer[currentLine][0] = '\0';

                /* new line moves old line up, redraw screen. */
                redrawFullScreen = true;
                break;
            default:
                /* non-control character, put in screen buffer. */
                screenBuffer[currentLine][currentPosition] = character;

                /* increment cursor and NULL terminate line. */
                currentPosition++;
                screenBuffer[currentLine][currentPosition] = '\0';

                /* move to new line when screen wrap. */
                if (currentPosition >= SCREEN_WIDTH) {

                    /* move cursor to new line and NULL terminate. */
                    currentPosition = 0;
                    currentLine++;
                    screenBuffer[currentLine][0] = '\0';

                    /* redraw full screen to scroll lines up. */
                    redrawFullScreen = true;
                }
                currentLine = (currentLine % SCREEN_HEIGHT);
                break;
        }
    }

    /* redraw full screen when more than one line has changed. */
    if (redrawFullScreen) {
        /* send all lines to screen one at a time. */
        for (size_t index = 0; index < SCREEN_HEIGHT; index++) {

            /* offset by one to put the active line at the bottom. */
            size_t bufferLine = (currentLine + 1 + index) % SCREEN_HEIGHT;

            /* erase old line, print new line. */
            screen_console_clear_line(index);
            screen_console_write_line(index, screenBuffer[bufferLine]);
        }
    } else {
        /* only update last line, keep the rest unchanged. */
        screen_console_clear_line(SCREEN_HEIGHT - 1);
        screen_console_write_line(SCREEN_HEIGHT - 1, screenBuffer[currentLine]);
    }

    return size;
}

ssize_t ScreenConsole::read(void *buffer, size_t size)
{
    /* Reading is not supported by this file handle */
    return -EBADF;
}

off_t ScreenConsole::seek(off_t offset, int whence)
{
    /* Seeking is not support by this file handler */
    return -ESPIPE;
}

off_t ScreenConsole::size()
{
    /* Size is not defined for this file handle */
    return -EINVAL;
}

int ScreenConsole::isatty()
{
    /* File handle is used for terminal output */
    return true;
}

int ScreenConsole::close()
{
    return 0;
}
