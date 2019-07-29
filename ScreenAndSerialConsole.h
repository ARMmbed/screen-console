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

#ifndef SCREEN_AND_SERIAL_CONSOLE_H
#define SCREEN_AND_SERIAL_CONSOLE_H

#include "ScreenConsole.h"
#include "mbed.h"

/**
 * Macros for setting console flow control.
 */
#define CONSOLE_FLOWCONTROL_RTS     1
#define CONSOLE_FLOWCONTROL_CTS     2
#define CONSOLE_FLOWCONTROL_RTSCTS  3
#define mbed_console_concat_(x) CONSOLE_FLOWCONTROL_##x
#define mbed_console_concat(x) mbed_console_concat_(x)
#define CONSOLE_FLOWCONTROL mbed_console_concat(MBED_CONF_TARGET_CONSOLE_UART_FLOW_CONTROL)

class ScreenAndSerialConsole : public FileHandle {

public:
    ScreenAndSerialConsole(void)
        : _screen(), _console(STDIO_UART_TX, STDIO_UART_RX, MBED_CONF_PLATFORM_STDIO_BAUD_RATE)
    {
#if   CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_RTS
        _console.set_flow_control(SerialBase::RTS, STDIO_UART_RTS, NC);
#elif CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_CTS
        _console.set_flow_control(SerialBase::CTS, NC, STDIO_UART_CTS);
#elif CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_RTSCTS
        _console.set_flow_control(SerialBase::RTSCTS, STDIO_UART_RTS, STDIO_UART_CTS);
#endif
    }

    virtual ssize_t write(const void *buffer, size_t size)
    {
        _screen.write(buffer, size);

        return _console.write(buffer, size);
    }

    virtual ssize_t read(void *buffer, size_t size)
    {
        /* Reading is not supported by this file handle */
        return -EBADF;
    }

    virtual off_t seek(off_t offset, int whence = SEEK_SET)
    {
        /* Seeking is not support by this file handler */
        return -ESPIPE;
    }

    virtual off_t size()
    {
        /* Size is not defined for this file handle */
        return -EINVAL;
    }

    virtual int isatty()
    {
        /* File handle is used for terminal output */
        return true;
    }

    virtual int close()
    {
        return 0;
    }

private:
    ScreenConsole _screen;
    UARTSerial    _console;
};

#endif
