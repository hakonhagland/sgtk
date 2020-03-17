# sgtk
## Prerequisites for installation

Note, that some packages need to be installed before building.
### Linux (Ubuntu)

For Ubuntu the following command should be used:
```
sudo apt-get install -y cmake gtk+-3.0 g++
```

### Windows

- Install MSYS2, see: https://www.msys2.org/
- Open the MSYS2 terminal (and from the dialog popup window choose from three options, the Mingw-w64 64 bit shell)

Then install the following packages:
- `pacman -S git` 
- `pacman -S make`
- `pacman -S mingw64/mingw-w64-x86_64-gtk3`
- `pacman -S mingw-w64-x86_64-toolchain`

<!-- - export PKG_CONFIG_PATH=/mingw64/lib/pkgconfig:$PGK_CONFIG_PATH
mingw-w64-x86_64-cmake -->

Note: if the `pacman` download server is slow, you  might have to add option
  `--disable-download-timeout` to the above commands.

<!--
Ubuntu: /usr/lib/x86_64-linux-gnu/pkgconfig/gtk+-3.0.pc
Windows: /mingw64/lib/pkgconfig/gtk+-3.0.pc -->


## Installation
### Linux


```
git clone https://github.com/hakonhagland/sgtk.git
cd sgtk
mkdir build
cd build
cmake ..
make
sudo make install
```

### Windows (MSYS2)
```
git clone https://github.com/hakonhagland/sgtk.git
cd sgtk
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=. -G "MSYS Makefiles" ..
make
make install
```
Note: We are compiling to the current directory since it is not
possible to install the library `libsgtk.dll` to `C:\Window\System32` without admistrator
privileges.

Then, append the following lines to the MSYS2 `~/.bashrc` file:

```
export SGTK_DIR=<build dir>
export PATH="$SGTK_DIR/lib":$PATH
```

NOTE: In the the above commands, you should replace `<build_dir>` with the
absolute path of the build directory.

Then, update the variables from the MSYS2 terminal window:

```
source ~/.bashrc
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

## Compiling and running the test program

### Linux

```
gcc test.c -lsgtk `pkg-config --libs gtk+-3.0`
```

Note: It is important that you link with `libsgtk.so` before you link
with the GTK3 libraries in the above command. So
```
gcc test.c `pkg-config --libs gtk+-3.0` -lsgtk
```
would **not** work.

Then, run the test program:

```
./a.out

```

### Windows (MSYS2)

Compile with:

```
gcc -I"$SGTK_DIR/include" -L"$SGTK_DIR/lib" test.c -lsgtk `pkg-config --libs gtk+-3.0`
```

Then, run the program:

```
./a.exe
```
