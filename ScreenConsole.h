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

#ifndef SCREEN_CONSOLE_H
#define SCREEN_CONSOLE_H

#include "mbed.h"

#define SCREEN_WIDTH MBED_CONF_SCREEN_CONSOLE_WIDTH
#define SCREEN_HEIGHT MBED_CONF_SCREEN_CONSOLE_HEIGHT

class ScreenConsole : public FileHandle {

public:
    ScreenConsole(void);

    virtual ssize_t write(const void *buffer, size_t size);
    virtual ssize_t read(void *buffer, size_t size);
    virtual off_t seek(off_t offset, int whence = SEEK_SET);
    virtual off_t size();
    virtual int isatty();
    virtual int close();

private:
    char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    size_t currentLine;
    size_t currentPosition;
};

#endif
