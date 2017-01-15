CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -c
CPP = -DEXPORT_API_GiDS_DLL

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

LIBNAME = GiDS

DLL = $(LIBNAME).dll
DLLRES = $(LIBNAME)_DLLversion.rc

DLLRESOBJ = $(patsubst %.rc, %.o, $(DLLRES))

STATIC = lib$(LIBNAME).a
DEFFILE =lib$(LIBNAME).def

.PHONY: clean all
all: $(DLL)


$(OBJS): %.o: %.c
	$(CC) $(CPP) $(CFLAGS) $< -o $@

#$(STATIC): $(OBJS)
#	ar rcs  -o $@ $^

$(DLLRESOBJ): $(DLLRES)
	windres $(DLLRES) $(DLLRESOBJ)

$(DLL): $(DLLRESOBJ) $(OBJS)
	$(CC) -shared -o $@ $^ -Wl,--output-def=$(DEFFILE) -Wl,--dll -Wl,-no-undefined,--enable-runtime-pseudo-reloc,--out-implib,$(STATIC)
	@echo off
	@copy $@ tests /Y
	@echo on

clean:
	@echo off
	@del *.o *.exe *.a *.lib *.dll *.def
	@echo on
