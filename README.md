# screen-console

Turn LCD screen into a debug terminal.

## Usage

Use Mbed OS console override feature to add or replace UART output with LCD screen output. Insert in any computational unit:

### Screen only
```
#include "ScreenConsole.h"

FileHandle *mbed::mbed_override_console(int fd) {
    static ScreenConsole screen_console;
    return &screen_console;
}
```

### Screen and Serial
```
#include "ScreenAndSerialConsole.h"

FileHandle *mbed::mbed_override_console(int fd) {
    static ScreenAndSerialConsole screen_console;
    return &screen_console;
}
```

Configuration options:
```
{
    "name": "screen-console",
    "config": {
        "width": {
            "help": "Characters on each line.",
            "value": 0
        },
        "height": {
            "help": "Lines on screen.",
            "value": 0
        },
        "font-size": {
            "help": "Relative font size.",
            "value": 0
        },
        "text-color": {
            "help": "Text color.",
            "value": null
        },
        "background-color": {
            "help": "Background color.",
            "value": null
        },
        "portrait-mode": {
            "help": "Use portrait mode instead of landscape.",
            "value": 0
        }
    }
}
```

`text-color` and `background-color` are hardware specific.

