CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump
SIZE = arm-none-eabi-size

OCFLAGS = --strip-unneeded

CFLAGS = -I./lpc43xx/Core/CMSIS/Include
CFLAGS += -I./lpc43xx/Core/Device/NXP/LPC43xx/Include
CFLAGS += -I./lpc43xx/Drivers/include
CFLAGS += -I./ -c -fno-common -Os -g -mcpu=cortex-m4 -mthumb -Wall -ffunction-sections -fdata-sections -fno-builtin -Wno-unused-function -ffreestanding
CFLAGS += -DCORE_M4
LFLAGS = -Tevalboard.ld -nostartfiles -Wl,--gc-sections

# our code
OBJS = main.o

# startup files
OBJS += handlers.o startup.o

# SystemInit based on template
OBJS += system_LPC43xx.o

# drivers/lib
OBJS += lpc43xx/Drivers/source/lpc43xx_scu.o
OBJS += lpc43xx/Drivers/source/lpc43xx_cgu.o
OBJS += lpc43xx/Drivers/source/lpc43xx_gpio.o
OBJS += lpc43xx/Drivers/source/lpc43xx_timer.o
OBJS += lpc43xx/Core/Device/NXP/LPC43xx/Source/fpu_init.o
OBJS += lpc43xx/Core/Device/NXP/LPC43xx/Source/fpu_enable.o

all: main.dfu

clean:
	-rm -f $(OBJS) main.lst main.elf main.hex main.map main.bin main.list main.dfu _tmp.dfu _header.bin

main.elf: $(OBJS) evalboard.ld
	$(LD) $(LFLAGS) -o main.elf $(OBJS)
	-@echo ""
	$(SIZE) main.elf
	-@echo ""

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.bin: %.elf
	$(OBJCOPY) $(OCFLAGS) -O binary $< $@

%.dfu: %.bin
	cp $< _tmp.dfu
	dfu-suffix --vid=0x1fc9 --pid=0x000c --did=0x0 -a _tmp.dfu
	python2 -c "import os.path; import struct; print('0000000: da ff ' + ' '.join(map(lambda s: '%02x' % ord(s), struct.pack('<H', os.path.getsize('$<') / 512 + 1))) + 'ff ff ff ff ff ff ff ff ff ff ff ff')" | xxd -g1 -r > _header.bin
	cat _header.bin _tmp.dfu > $@

program: main.dfu
	sudo dfu-util --device 1fc9:000c --alt 0 --download main.dfu
