
wd=..
mnt=/mnt/kevos


g++-7 -S -c -m32 -o $wd/boot.32.cpp.S -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding ../../kevos/src/arch/x64/boot.32.cpp -I../../kevos/include/lib/stdinc
g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/boot.32.cpp.o $wd/boot.32.cpp.S -I../../kevos/include/lib/stdinc
g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/vm.o ../../kevos/src/arch/x64/vm.cpp -I../../kevos/include/lib/stdinc
g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/boot.64.cpp.o ../../kevos/src/arch/x64/boot.64.cpp -I../../kevos/include/lib/stdinc
ld -o $wd/kernel.bin -e entry32 -melf_x86_64 -z max-page-size=0x1000 -T ../../kevos/src/arch/x64/kernel-ld-script.ld $wd/boot.32.cpp.o $wd/vm.o $wd/boot.64.cpp.o

sudo cp $wd/vd.img ~
cd ~
sudo losetup /dev/loop0 vd.img
sudo kpartx -av /dev/loop0

sudo mount /dev/mapper/loop0p1 $mnt
sudo cp /mnt/shared/kevos/build/kernel.bin $mnt


sudo umount $mnt
sudo kpartx -dv /dev/loop0
sudo losetup -d /dev/loop0

sudo rm -rf vd.vdi vd.vmdk
vboxmanage convertdd vd.img vd.vdi
vboxmanage clonehd vd.vdi vd.vmdk --format vmdk
sudo cp vd.img /mnt/shared/kevos/build/
sudo cp vd.vmdk /mnt/shared/kevos/build/
sudo cp vd.vdi /mnt/shared/kevos/build/
sudo rm -rf ~/vd.vdi ~/vd.vmdk

cd /mnt/shared/kevos/build/scripts