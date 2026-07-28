[![Version: 1.0 Release](https://img.shields.io/badge/Version-1.0%20Release-green.svg)](https://github.com/0x007e/drivers-display-font) ![Build](https://github.com/0x007e/drivers-display-font/actions/workflows/release.yml/badge.svg) [![License GPLv3](https://img.shields.io/badge/License-GPLv3-lightgrey)](https://www.gnu.org/licenses/gpl-3.0.html)

# `Font for display driver libraries`

[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/0x007E/drivers-display-font)

These font set(s) is/are a generic set of `ASCII` characters that can be used on differnt displays (`oled`/`lcd`/`matrix`) and across multiple platforms.

## File Structure

![File Structure](https://blog.sunriax.at/drivers-display-font/font_8h__dep__incl.png)

```
drivers/
└── display/
    └── font/
        ├── font.h
        ├── font.c
        └── fonts/
            └── font_5x7_ascii.c
```

> With the macros in `font.h` the storage area and character size can be defined.

If there are different fonts availabe, it is possible to select the font by defining the `FONT_TYPE` in `font.h`. Note that the maximum font size is `undef` x `8` pixels (`width` x `length`), and the minimum font size is `1` x `1` pixel.

```
-  | - LENGTH -  |
|  # # # # # # # #
W  # # # # # # # #
I  # # # # # # # #
D  # # # # # # # #
T  # # # # # # # #
H  # # # # # # # #
|  # # # # # # # #
-
```

The start address is at `ARRAY[0]` -> `Bit[0]` (top left corner on the display).
Example (Character B):

```
-  | - LENGTH -  |
|  1 1 1 1 1 1 1 1
W  1 0 0 0 1 0 0 1
D  1 0 0 0 1 0 0 1
T  1 0 0 0 1 0 0 1
|  0 1 1 1 0 1 1 0
-
```

## Downloads

The font can be downloaded as (`zip` or `tar`), cloned or used as submodule in a project.

| Type      | File               | Description              |
|:---------:|:------------------:|:-------------------------|
| Library   | [zip](https://github.com/0x007E/drivers-display-font/releases/latest/download/library.zip) / [tar](https://github.com/0x007E/drivers-display-font/releases/latest/download/library.tar.gz) | Font for display driver library |

### Using with `git clone`

```sh
mkdir -p ./drivers/display
git clone https://github.com/0x007E/drivers-display-font.git ./drivers/display
mv ./drivers/display/drivers-display-font                    ./drivers/display/font
```

### Using as `git submodule`

```sh
git submodule add https://github.com/0x007E/drivers-display-font.git ./drivers/display/font
```

## Programming

```c
#include "../lib/drivers/display/font/font.h"

static unsigned char pixel_map[FONT_WIDTH];

int main(void)
{
    font_get_bitmap('A', pixel_map);

    // Send pixel_map to display...
}
```

---

R. GAECHTER
