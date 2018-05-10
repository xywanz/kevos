cp -r ../../kevos ~/
cd ~/kevos/kevos

g++ -S -c -m32 -o boot.32.cpp.S -fno-builtin -nostdinc -nostdinc++ -nostdlib -Iinclude -std=c++11 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding src/arch/x64/boot.32.cpp
g++ -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -Iinclude -std=c++11 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o boot.32.cpp.o boot.32.cpp.S
ld -o kernel.bin boot.32.cpp.o -e entry32 -s -melf_x86_64

# g++-7 -c -std=c++11 -o boot.32.o -m32 -fno-builtin src/arch/x64/boot.32.cpp -Iinclude -nostdinc -nostdlib -nostdinc++
# ld -o kernel.bin -Ttext 0x100000 -m elf_i386 -e entry32 boot.32.o -T src/arch/x64/kernel-ld-script.ld

dd if=/dev/zero of=vd.img bs=1M count=32
fdisk vd.img<<EOF
x
c
16
h
64
s
63
r
n
p
1


a
1
w
EOF

sudo losetup /dev/loop0 vd.img
sudo kpartx -av /dev/loop0
sudo mkfs.ext2 /dev/mapper/loop0p1

sudo mount /dev/mapper/loop0p1 /mnt/kevos
sudo cp -r /mnt/shared/kevos/img/boot /mnt/kevos
sudo cp kernel.bin /mnt/kevos

sudo grub-install --no-floppy --root-directory=/mnt/kevos /dev/loop0

sudo umount /mnt/kevos
sudo kpartx -dv /dev/loop0
sudo losetup -d /dev/loop0

rm -rf vd.vdi vd.vmdk
vboxmanage convertdd vd.img vd.vdi
vboxmanage clonehd vd.vdi vd.vmdk --format vmdk

sudo cp vd.vmdk /mnt/shared/
sudo cp vd.img /mnt/shared/kevos/build/
sudo cp kernel.bin /mnt/shared/kevos/build/

rm -rf ~/kevos

cd /mnt/shared/kevos/utils/