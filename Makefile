CC= gcc
CFLAGS= -Wall -O0 -g
LIBS= -lpci

INCLUDES= -I.

SRCS= smutool.c

OBJS = $(SRCS:.c=.o)

TARGET= smutool


.PHONY: depend clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm $(TARGET) *.o
