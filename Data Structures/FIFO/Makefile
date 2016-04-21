CC              = gcc
CFLAGS          = -Wall -std=c11
DBGFLAGS        = -g -ggdb
SRC             = FIFOqueue.c
MORE_WARNINGS   = -Wextra -pedantic
LINKER          = -L. -lFIFOqueue

test:
	$(CC) $(CFLAGS) -o testqueue.exe testqueue.c $^ $(LINKER)

dll: $(SRC)
	windres dllversion.rc dllversion.o
	$(CC) $(CFLAGS) -c $^ -o FIFOqueue.o
	$(CC) -shared -o FIFOqueue.dll FIFOqueue.o dllversion.o -Wl,-no-undefined,--enable-runtime-pseudo-reloc,--out-implib,FIFOqueue.dll.a
	del FIFOqueue.o dllversion.o

.PHONY:
clean:
	@del *.exe *.o
