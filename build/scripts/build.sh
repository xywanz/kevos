
if [ ! -f "../vd.img" ]; then
echo 'Generating a new hard disk image...'
cp -r ../../../kevos ~/
cd ~/kevos/kevos
dd if=/dev/zero of=vd.img bs=1M count=32 1>/dev/null
fdisk vd.img<<EOF 1>/dev/null
x
c
64
h
16
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
sudo losetup /dev/loop0 vd.img 1>/dev/null
sudo kpartx -av /dev/loop0 1>/dev/null
sudo mkfs.ext2 /dev/mapper/loop0p1 1>/dev/null
sudo mount /dev/mapper/loop0p1 /mnt/kevos
sudo cp -r /mnt/shared/kevos/img/boot /mnt/kevos
echo 'Install grub2 into image...'
sudo grub-install --no-floppy --root-directory=/mnt/kevos /dev/loop0 1>/dev/null
sudo umount /mnt/kevos
sudo kpartx -dv /dev/loop0 1>/dev/null
sudo losetup -d /dev/loop0 1>/dev/null
sudo cp ../vd.img /mnt/shared/kevos/build/
sudo rm -rf ~/kevos
cd /mnt/shared/kevos/build/scripts
fi

wd=../tmp
mnt=/mnt/kevos

cd ../../kevos/src
echo 'Generating kernel.bin...'
sudo make all 1>/dev/null
cd ../../build/scripts

# g++-7 -S -c -m32 -o $wd/boot.32.cpp.S -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding ../../kevos/src/arch/x64/boot/boot.32.cpp -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/boot.32.o $wd/boot.32.cpp.S -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/vm.o ../../kevos/src/arch/x64/vm.cpp -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/gdt.o ../../kevos/src/arch/x64/gdt.cpp -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/boot.64.o ../../kevos/src/arch/x64/boot/boot.64.cpp -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/page_mgr.o ../../kevos/src/kernel/mm/page_mgr.cpp -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/kmem_mgr.o ../../kevos/src/kernel/mm/kmem_mgr.cpp -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/bitmap.o ../../kevos/src/kernel/common/bitmap.cpp -I../../kevos/include/lib/stdinc
# g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I../../kevos/include -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $wd/interrupt.o ../../kevos/src/arch/x64/interrupt.S -I../../kevos/include/lib/stdinc
# ld -o $wd/kernel.bin -z max-page-size=0x1000 -T ../lds/x64/kernel-ld-script.ld $wd/boot.32.o $wd/boot.64.o $wd/vm.o $wd/gdt.o $wd/page_mgr.o $wd/bitmap.o $wd/kmem_mgr.o $wd/interrupt.o

echo 'Copy kernel.bin to img...'
sudo cp ../vd.img ~
cd ~
sudo losetup /dev/loop0 vd.img 1>/dev/null
sudo kpartx -av /dev/loop0 1>/dev/null

sudo mount /dev/mapper/loop0p1 $mnt
sudo cp /mnt/shared/kevos/build/tmp/kernel.bin $mnt


sudo umount $mnt
sudo kpartx -dv /dev/loop0 1>/dev/null
sudo losetup -d /dev/loop0 1>/dev/null

echo 'Generating vmdk from img...'

sudo rm -rf vd.vdi vd.vmdk
vboxmanage convertdd vd.img vd.vdi 1>/dev/null
vboxmanage clonehd vd.vdi vd.vmdk --format vmdk 1>/dev/null
sudo mv vd.img /mnt/shared/kevos/build/
sudo mv vd.vmdk /mnt/shared/kevos/build/
sudo mv vd.vdi /mnt/shared/kevos/build/tmp/

cd /mnt/shared/kevos/build/scripts

rm -rf ../vd.vdi ../*.S