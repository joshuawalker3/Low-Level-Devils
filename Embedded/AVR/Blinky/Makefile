MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
CFLAGS = -std=gnu11 -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
OBJ = main.o
TARGET = main
PORT = COM3

all: $(TARGET).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET).elf

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	avrdude -v -p $(MCU) -c arduino -P $(PORT) -b 115200 -D -U flash:w:$(TARGET).hex:i

clean:
	del *.o *.elf *.hex
