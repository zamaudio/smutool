# Free/Libre SMU firmware
# Copyright (C) 2015  Damien Zammit <damien@zamaudio.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# See <http://www.gnu.org/licenses/>.-
#

CC = lm32-elf-gcc
LD = lm32-elf-ld
OC = lm32-elf-objcopy

LIBS=-L/opt/lm32/lib/gcc/lm32-elf/4.5.4
SRCS=memcpy.c smu.c interrupts.c
ASMS=MicoSleepHelper.S crt0ram-smu.S
OBJS=$(SRCS:.c=.o)
OBJS2=$(ASMS:.S=.o)
TARGET=smu.elf

all: $(TARGET)

$(TARGET): $(OBJS) $(OBJS2)
	$(LD) $(LIBS) $(OBJS) $(OBJS2) -static -M -T smu.ld -o $(TARGET)
	$(OC) -S -I elf32-lm32 -O binary $(TARGET) smu.rom

.c.o:
	$(CC) $(LIBS) -O0 -Wall -ffreestanding -c $< -o $@

.S.o:
	$(CC) $(LIBS) -O0 -Wall -ffreestanding -c $< -o $@

clean:
	rm -f *.o *~ $(TARGET) smu.rom
