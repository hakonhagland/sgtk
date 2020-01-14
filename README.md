# sgtk

## Installation

```
git clone git@github.com:hakonhagland/sgtk.git
cd sgtk
mkdir build
cd build
cmake ..
make
sudo make install
```

## A sample test program

```

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
INSTALL_PATH=/name/of/directory/where/you/installed
gcc -I"$INSTALL_PATH" -L"$INSTALL_PATH"/lib test.c `pkg-config --libs gtk+-3.0` -lsgtk
```

## Running the test program

```
LD_LIBRARY_PATH=$INSTALL_PATH/lib a.out

```
