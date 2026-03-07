AS = i686-elf-as
CC = i686-elf-gcc

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I include -I src
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

OBJS = build/boot.o build/kernel.o
KERNEL = build/codepurple.bin
ISO = codepurple.iso

all: $(ISO)

build/boot.o: src/boot.s
	$(AS) src/boot.s -o build/boot.o

build/kernel.o: src/kernel.c
	$(CC) -c src/kernel.c -o build/kernel.o $(CFLAGS)

$(KERNEL): $(OBJS)
	$(CC) $(LDFLAGS) -o $(KERNEL) $(OBJS)

$(ISO): $(KERNEL)
	cp $(KERNEL) isodir/boot/codepurple.bin
	grub-mkrescue -o $(ISO) isodir

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f build/*.o build/*.bin $(ISO) isodir/boot/codepurple.bin
