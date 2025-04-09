#Kompilátor és beállítások
CC = gcc
CFLAGS = -Wall -O2 -I. -I"C:/msys64/mingw64/include"
LDFLAGS = -L"C:/msys64/mingw64/lib" -lmingw32 -lSDL2main -lSDL2 -mconsole

#Objektumfájlok
OBJS = main.o render.o selection.o camera.o

#Célnév
TARGET = main.exe

#Alapértelmezett célt
all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    del /Q .o.exe 2> NUL || true


#all:
 #    gcc -Iinclude/ src/main.c src/camera.c src/render.c src/selection.c -o test.exe -lmingw32 -lSDL2main -lSDL2 -mconsole