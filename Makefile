
# /home/andy/data/clang+llvm-3.4.2-x86_64-linux-gnu-ubuntu-14.04/bin/clang
# /home/andy/data/clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04/bin/clang
# /home/andy/data/clang+llvm-3.2-x86_64-linux-ubuntu-12.04/bin/clang
# /home/andy/data/clang+llvm-3.0-x86_64-linux-Ubuntu-11_04/bin/clang
# /home/andy/data/clang+llvm-3.3-amd64-Ubuntu-12.04.2/bin/clang


SRC = $(shell find . -name *.cpp)


ifeq ($(OS),Windows_NT)
    CC = "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\BIN\x86_amd64\cl.exe"
    CCFLAGS += -D WIN32 gdi32.lib user32.lib shell32.lib
    O = /Fe
    EXE = .exe
else
    UNAME_S := $(shell uname -s)
    O = -o
    EXE = 
    ifeq ($(UNAME_S),Linux)
        CC = clang -I /usr/include/x86_64-linux-gnu/ -I/usr/include/x86_64-linux-gnu/c++/4.8 -fno-inline
        CCFLAGS += -w -g -O2 -lstdc++ -lm
    endif
    ifeq ($(UNAME_S),Darwin)
        CC = clang
        CCFLAGS += -g -O2 -lstdc++
    endif
endif

# add your binary here
BINARIES = \
	bin/1706$(EXE)


all: $(BINARIES)

clean:
	rm -f $(BINARIES)


bin/1706$(EXE): enigmas-1700-1799/1706.cpp
	$(CC) $(CCFLAGS) $< $O$@

