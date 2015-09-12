CC= gcc
CFLAGS= -Wall -O0 -g
LIBS= -lpci

INCLUDES= -I.

SRCS1= smutool.c
SRCS2= smudump.c

OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

TARGET1= smutool
TARGET2= smudump


.PHONY: depend clean

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1) $(SRCS1)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET1) $(OBJS1) $(LIBS)
$(TARGET2): $(OBJS2) $(SRCS2)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET2) $(OBJS2) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm $(TARGET1) $(TARGET2) *.o
