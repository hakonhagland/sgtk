# sgtk

## Installation

```
git clone git@github.com:hakonhagland/sgtk.git
cd sgtk
make
make install
```

## Compiling a test program

```
INSTALL_PATH=/name/of/directory/where/you/installed
gcc -I"$INSTALL_PATH" -L"$INSTALL_PATH"/lib test.c `pkg-config --libs gtk+-3.0` -lsgtk
```

## Running the test program

This is a test
```
LD_LIBRARY_PATH=$INSTALL_PATH/lib a.out

```
