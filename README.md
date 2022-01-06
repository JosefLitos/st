# st - the simple (suckless) terminal

- 2.1.2022 fresh build, all patches updated to latest → underlines are buggy
- originally forked from Luke, but now freshly rebuilt

The [suckless terminal (st)](https://st.suckless.org/) with some additional features that make it
literally the best terminal emulator ever:

## Unique features (using dmenu)

-   **follow urls** by pressing `ctrl-leftclick`

## Bindings for

-   **scrollback** with `ctrl-shift-minus/equal` or `ctrl-shift-pageup/down` or scroll with the
    mouse
-   **change alpha** with `alt-minus/equal`
-   **zoom/change font size** with `ctrl-minus/equal` or `ctrl-shift-btn4/5`, `ctrl-0` to reset
-   **copy text** with `ctrl+alt-c`, **paste** is `ctrl+alt-v`

## Pretty stuff

-   Transparency/alpha, which is also adjustable from your `Xresources`.
-   Default font is “mono” at 19pt, meaning the font will match your system font.

## Other st patches

-   Scrollback
-   font2
-   updated to version 0.8.4, latest commit in 2.1.2022, not updating ever again!!

## Installation for newbs

    git clone https://github.com/JosefLitos/st
    cd st
    sudo make clean install

Obviously, `make` is required to build. `fontconfig` is required for the default build, since it
asks `fontconfig` for your system monospace font. It might be obvious, but `libX11` and `libXft` are
required as well. Chances are, you have all of this installed already.

On OpenBSD, be sure to edit `config.mk` first and remove `-lrt` from the `$LIBS` before compiling.

Be sure to have a composite manager (`xcompmgr`, `picom`, etc.) running if you want transparency.

### Colors

To be clear about the color settings:

-   If there are Xresources colors defined, those will take priority.
-   But if `wal` has run in your session, its colors will take priority.

Note that when you run `wal`, it will negate the transparency of existing windows, but new windows
will continue with the previously defined transparency.

## Notes on Emojis and Special Characters

If st crashes when viewing emojis, install
[libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR.

Note that some special characters may appear truncated if too wide. You might want to manually set
your prefered emoji/special character font to a lower size in the `config.h` file to avoid this. By
default, JoyPixels is used at a smaller size than the usual text.
