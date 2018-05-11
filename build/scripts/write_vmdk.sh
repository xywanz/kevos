
wd=..
mnt=/mnt/kevos


g++ -S -c -m32 -o $wd/boot.32.cpp.S -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++11 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding ../../kevos/src/arch/x64/boot.32.cpp
g++ -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++11 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/boot.32.cpp.o $wd/boot.32.cpp.S
# g++ -Wl,-T -Wl,../../kevos/src/arch/x64/kernel-ld-script.ld -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++11 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -o $wd/kernel.bin $wd/boot.32.cpp.o
ld -o $wd/kernel.bin -e entry32 -melf_x86_64 -z max-page-size=0x1000 -T ../../kevos/src/arch/x64/kernel-ld-script.ld $wd/boot.32.cpp.o 

sudo losetup /dev/loop0 $wd/vd.img
sudo kpartx -av /dev/loop0

sudo mount /dev/mapper/loop0p1 $mnt
sudo cp $wd/kernel.bin $mnt


sudo umount $mnt
sudo kpartx -dv /dev/loop0
sudo losetup -d /dev/loop0

sudo rm -rf $wd/vd.vdi $wd/vd.vmdk
vboxmanage convertdd $wd/vd.img $wd/vd.vdi
vboxmanage clonehd $wd/vd.vdi $wd/vd.vmdk --format vmdk