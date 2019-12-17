all: libsgtk.so

libsgtk.so: user.o sgtk.o
	$(CXX) -shared -o libsgtk.so sgtk.o user.o `pkg-config --libs gtk+-3.0`

user.o: user.cpp
	$(CXX) `pkg-config --cflags gtk+-3.0` -c -fPIC user.cpp 

sgtk.o: sgtk.cpp
	$(CXX) `pkg-config --cflags gtk+-3.0` -c -fPIC sgtk.cpp

clean:
	 rm user.o sgtk.o

install:
	mkdir -p lib
	mv libsgtk.so lib
