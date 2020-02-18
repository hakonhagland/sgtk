# sgtk

## Prerequisites for installation

Note, that some packages need to be installed before building.
### Windows

- Install MSYS2, see: https://www.msys2.org/
- pacman -S git cmake
- pacman -S mingw64/mingw-w64-x86_64-gtk3
- pacman -S gcc
- pacman -S make
- export PKG_CONFIG_PATH=/mingw64/lib/pkgconfig:$PGK_CONFIG_PATH

Ubuntu: /usr/lib/x86_64-linux-gnu/pkgconfig/gtk+-3.0.pc
Windows: /mingw64/lib/pkgconfig/gtk+-3.0.pc
### Ubuntu

For Ubuntu the following command should be used:
```
sudo apt-get install -y cmake gtk+-3.0 g++
```

## Installation

```
git clone https://github.com/hakonhagland/sgtk.git
# git clone git@github.com:hakonhagland/sgtk.git
cd sgtk
mkdir build
cd build
cmake ..
make
sudo make install
```

## A sample test program

```

#include <stdio.h>
#include <stdlib.h>
#include <sgtk.h>

int main() {
    int x = 100;
    int y = 100;
    int width = 600;
    int height = 400;
    if ( !define_window(x, y, width, height) ) {
        printf( "Could not open window!\n" );
        exit(1);
    }
    set_title("Test window");
    set_line_width(2);
    set_line_color( "#0000ff" );
    draw_line(0,0, 100,100);
    show_window();
    return 0;
}
```

## Compiling the test program

```
gcc test.c -lsgtk `pkg-config --libs gtk+-3.0`
```

Note: It is important that you link with `libsgtk.so` before you link
with the GTK3 libraries in the above command. So
```
gcc test.c `pkg-config --libs gtk+-3.0` -lsgtk
```
would **not** work.

## Running the test program

```
./a.out

```
