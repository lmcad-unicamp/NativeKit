CC=i686-elf-g++
LD=i686-elf-ld
AS=nasm

AFLAGS=-felf
LFLAGS=
CFLAGS=-std=c++0x -O3 -Wall -nostdlib -fno-exceptions -fno-rtti -DDEBUG=0

INCLUDE=-I inc/ -I inc/arch/ -I inc/device/ -I inc/util/ -I inc/manager -I test/ -I lib/ktest/
OBJDIR=bin
ISODIR=$(OBJDIR)/iso
SRCDIR=src
MODDIR=mod
LIBDIR=lib
TSTDIR=test
TSTSRC=$(wildcard $(TSTDIR)/*/*.cpp $(TSTDIR)/*.cpp)
TSTOBJ=$(notdir $(TSTSRC:.cpp=.o))

DMAKER_MODULES :=util/diskmaker/diskmaker.cpp util/diskmaker/native_arch.c */*/device.cpp */*/inputdevice.cpp */*/outputdevice.cpp */ilistener.cpp */*/manager.cpp */*/nfsii.cpp */*/storage.cpp */*/filesystem.cpp
KERNEL_MODULES :=$(addprefix $(OBJDIR)/, arch.o crti.o crtbegin.o core.o debug.o device.o ilistener.o inputdevice.o kernel.o keyboard.o keybuffer.o manager.o memory.o storage.o nfsii.o filesystem.o outputdevice.o scheduler.o process.o posix.o system.o uart.o video.o disk.o brk.o close.o default.o execve.o exit.o fork.o fstat.o getpid.o gettimeofday.o kill.o link.o lseek.o newuname.o open.o read.o reboot.o stat.o times.o unlink.o wait.o write.o syscalls.o crtend.o crtn.o libstdc++.a libm.a libc.a libgcc.a )
TEST_MODULES   :=$(addprefix $(OBJDIR)/, arch.o crti.o crtbegin.o core.o debug.o device.o ilistener.o inputdevice.o $(TSTOBJ) ktest.o keyboard.o keybuffer.o manager.o memory.o storage.o nfsii.o filesystem.o outputdevice.o scheduler.o process.o posix.o system.o uart.o video.o disk.o brk.o close.o default.o execve.o exit.o fork.o fstat.o getpid.o gettimeofday.o kill.o link.o lseek.o newuname.o open.o read.o reboot.o stat.o times.o unlink.o wait.o write.o syscalls.o crtend.o crtn.o libstdc++.a libm.a libc.a libgcc.a )

DISKMAKER :=$(OBJDIR)/diskmaker.out
DISKIMG   :=$(OBJDIR)/disk.img
KERNEL    :=$(OBJDIR)/kernel.bin
LIVECD    :=$(OBJDIR)/kernel.iso
KTEST     :=$(OBJDIR)/test.bin

all: $(OBJDIR) $(ISODIR) $(DISKIMG) $(KERNEL) $(KTEST) $(LIVECD)

$(OBJDIR):
	mkdir $(OBJDIR)

$(ISODIR):
	mkdir $(ISODIR)
	mkdir $(ISODIR)/boot/
	mkdir $(ISODIR)/boot/grub/

$(LIVECD): $(KERNEL) $(KTEST) grub.cfg
	cp grub.cfg $(ISODIR)/boot/grub/ -f
	cp $(KERNEL) $(ISODIR)/boot/
	cp $(KTEST) $(ISODIR)/boot/
	grub-mkrescue -o $(LIVECD) $(ISODIR)/

$(OBJDIR)/crtend.o: $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
	cp $^ $@

$(OBJDIR)/crtbegin.o: $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
	cp $^ $@

$(OBJDIR)/libc.a: $(shell $(CC) $(CFLAGS) -print-file-name=libc.a)
	cp $^ $@

$(OBJDIR)/libm.a: $(shell $(CC) $(CFLAGS) -print-file-name=libm.a)
	cp $^ $@

$(OBJDIR)/libstdc++.a: $(shell $(CC) $(CFLAGS) -print-file-name=libstdc++.a)
	cp $^ $@

$(OBJDIR)/libsupc++.a: $(shell $(CC) $(CFLAGS) -print-file-name=libsupc++.a)
	cp $^ $@

$(OBJDIR)/libgcc.a: $(shell $(CC) $(CFLAGS) -print-file-name=libgcc.a)
	cp $^ $@

$(DISKMAKER): $(DMAKER_MODULES)
	g++ $(INCLUDE) -m32 -std=c++0x $^ -o $@

$(DISKIMG): $(DISKMAKER)
	./$^ fs $@

$(OBJDIR)/%.o : $(SRCDIR)/%.s
	$(AS) $(AFLAGS) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/*/%.s
	$(AS) $(AFLAGS) $^ -o $@

$(OBJDIR)/crt0.o : $(SRCDIR)/*/crt0.s
	$(AS) $(AFLAGS) $^ -o $@
	cp $(OBJDIR)/crt0.o ~/.nk/cross/lib/gcc/i686-elf/4.9.1/

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/*/%.cpp
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@

$(OBJDIR)/posix.o: $(SRCDIR)/*/posix.cpp $(OBJDIR)/crt0.o
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@
	ar -rvs $(shell $(CC) $(CFLAGS) -print-file-name=libc.a) $(OBJDIR)/posix.o

$(KERNEL): linker.ld $(KERNEL_MODULES)
	$(LD) $(LFLAGS) -T $^ -o $@

$(OBJDIR)/%.o : $(LIBDIR)/%.cpp
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o : $(LIBDIR)/*/%.cpp
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o : $(TSTDIR)/%.cpp
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o : $(TSTDIR)/*/%.cpp
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@

$(KTEST): linker.ld $(TEST_MODULES)
	$(LD) $(LFLAGS) -T $^ -o $@

$(OBJDIR)/%.o : $(MODDIR)/%.cpp
	$(CC) $(INCLUDE) -c $^ $(CFLAGS) -o $@

run: $(KERNEL)
	qemu-system-i386 -cdrom $(LIVECD) -serial stdio -m 1G
	# qemu-system-i386 -kernel $(KERNEL) -serial stdio -m 1G

test: $(KTEST)
	qemu-system-i386 -kernel $(KTEST) -serial stdio

clean:
	cd $(OBJDIR) && \
	rm *.o *.bin *.a *.img *.out *.iso build* iso* -rf 
