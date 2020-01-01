
CC=gcc
CCFLAG=-g -Wall
TARGET=recv_udp
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC))


ifeq ($(pi), y)
	CC=arm-linux-gcc
endif

ifeq ($(ap), y)
	CC=mipsel-openwrt-linux-gcc
	CCFLAG += -static
endif


$(TARGET):$(SRC)
	$(CC) $(CCFLAG) -o $@ $^


.PHONY:
clean:
	$(RM) $(OBJS) $(TARGET)



uppi:
	scp $(TARGET) pi@192.168.123.185:/home/pi/pedometer

upap:
	scp $(TARGET) admin@192.168.123.1:/home/root
