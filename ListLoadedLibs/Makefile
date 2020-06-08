CC     := x86_64-w64-mingw32-gcc
SOURCE := $(wildcard *.c)
OBJECT := $(SOURCE:%.c=%.o)
CFLAGS := -fPIC -Qn -s -nostdlib
LFLAGS := -Wl,--enable-stdcall-fixup,--exclude-all-symbols,-eWinMain
LINKER := -lmsvcrt
OUTBIN := ListLoadedLibs.exe

all: $(OUTBIN)

$(OUTBIN): $(OBJECT)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) $(LINKER)

.c.o:
	$(CC) -o $@ -c $< $(CFLAGS) $(LFLAGS) $(LINKER)

clean:
	rm -rf $(OBJECT) $(OUTBIN)
