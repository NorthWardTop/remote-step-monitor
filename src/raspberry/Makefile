
CC=arm-linux-gcc
# CC=gcc
CCFLAG=-g -o

TARGET=recv_udp
SRC=$(wildcard *.c)
# SRC=main.c
OBJS=$(patsubst %.c,%.o,$(SRC))
LIB=-lrt

$(TARGET):$(SRC)
	$(CC) $(CCFLAG) $@ $^


.PHONY:
clean:
	$(RM) $(OBJS) $(TARGET)
