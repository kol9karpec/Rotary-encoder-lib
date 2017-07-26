DEVICE := atmega2560
F_CPU  := 16000000

PROGRAMMER := wiring
PORT   := /dev/ttyACM0
SPEED  := 115200

CC      := avr-gcc
AVRDUDE := avrdude -v -p$(DEVICE) -c$(PROGRAMMER) -P$(PORT) -b$(SPEED) -D -V

CFLAGS  += -Wall \
			-Os \
			-DF_CPU=$(F_CPU) \
			-DMCU=$(DEVICE) \
			-mmcu=$(DEVICE) \
			-Wl,-u,vfprintf -lprintf_flt

OBJECTS := main.o \
			./src/usart.o \
			./src/timers.o \
			./src/rotary_encoder.o \
			./src/ring_buffer.o
TMPOUT  := main.elf
OUT     := main.hex

all: $(OUT)

flash: $(OUT)
	$(AVRDUDE) -U flash:w:$^:i

clean:
	-rm -f $(OUT) $(TMPOUT) $(OBJECTS)

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TMPOUT) $^
	avr-objcopy -j .text -j .data -O ihex $(TMPOUT) $@
	avr-size --format=avr --mcu=$(DEVICE) $@