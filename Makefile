C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

all: os-image.bin

os-image.bin: boot/bootsect.bin kernel.bin
	@cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	@ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	@ld -melf_i386 -o $@ -Ttext 0x1000 $^

boot/bootsect.bin: boot/boot_sect.asm
	@nasm -f bin -o boot/bootsect.bin boot/boot_sect.asm

run: os-image.bin
	@qemu-system-i386 -drive format=raw,file=os-image.bin

%.o: %.c ${HEADERS}
	@gcc -ffreestanding -m32 -o $@ -c $<

%.o: %.asm
	@nasm $< -f elf -o $@

%.bin: %.asm
	@nasm $< -f bin -o $@

debug: os-image.bin kernel.elf
	@qemu-system-i386 -s -fda os-image.bin &
	gdb -ex "target remote localhost:1234"

clean:
	@rm -rf *.bin *.dis *.o os-image.bin *.elf
	@rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o

