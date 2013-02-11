#
# Windows command line tools Makefile for MinGW.
#
# Example: make -f Makefile_mingw.mk
#

# For Japanese Shift-JIS
CC	= gcc -finput-charset=cp932 -fexec-charset=cp932

OPTIONS	= -O3



all: sleepsec.exe startbg.exe

sleepsec.exe: sleepsec.c
	$(CC) $(OPTIONS) -o $@ $^

startbg.exe: startbg.c
	$(CC) $(OPTIONS) -o $@ $^



.PHONY : clean
clean:
	rm -f *.o


