---
aliases:
  - “Arch install guide by Aguiar’s avg dev”
---
# tips

> To see what architecture the machine runs.

`cat /sys/firmware/efi/fw_platform_size`
# network setting
>Before start we have to connect the arch to the Internet. So in my case, I will need to use the “iwctl” interface.

> Display what interface is down 

`ip link`

>How to get internet connection via iwctl with wlan0

`iwctl`

`adapter phy0 set-property Powered on`

`device wlan0 set-property Powered on`

`station list`

`station wlan0 scan`

`station wlan0 show`

`station wlan0 get-networks`

`station wlan0 connect <SSID>`

`station wlan0 show`
# sync date


> Already connect to the (check with curl or ping) sync the clock with UTC. ijdk…

`timedatectl`
# partitions & encryption

> We will use LVM encrypted with LUKS in this setup.
### partitioning

> To see your devices

`lsblk`

`gdisk /dev/<YOUR-DISK>`

> To clean the disk

`o`

>Creating the first partition that will contains the boot

`n`

>press enter to maintain the first sector 

>on the last sector type it

`+4G`

>set the partition type to 1: EFI System

`ef00`

> Create the next partition that will be the lvm partition

`n`

> Default first & second sector this time (the number of the partition is always default too. I forgot to mention)

`8e00`

> Check if everything is ok.

`p`

> Then write everything.

`w`

> Then check again with `lsblk`. Now that everything is done let’s encrypt our disks. 
### creating LUKS encrypted container

>To create the LUKS encrypted container

`cryptsetup luksFormat /dev/<YOUR-DEVICE-NAME-PARTITION-FOR-LVM>`

> Now type your passphrase and we are done.

> Open the container:

`cryptsetup open /dev/<YOUR-DEVICE-NAME-PARTITION-FOR-LVM> cryptlvm`
### preparing the logical volumes

> In this section we basically will create the volumes and mount them.

> Create a physical volume on top

`pvcreate /dev/mapper/cryptlvm`

> Create a volume group. Where is “virgo1” can be whatever you want.

`vgcreate virgo1 /dev/mapper/cryptlvm`

> Now we are just creating the logical volumes (ex: swap, root, home…)

`lvcreate -L 8G virgo1 -n swap`

`lvcreate -L 32G virgo1 -n root`

`lvcreate -L 400G virgo1 -n home`

>Check if everything works with `lvdisplay`

> Now we are just formatting the file system.

`mkfs.fat -F32 /dev/<YOUR-DEVICE-NAME-PARTITION-FOR-EFI>`

`mkfs.ext4 /dev/virgo1/root`

`mkfs.ext4 /dev/virgo1/home`

`mkswap /dev/virgo1/swap`

> now Mounting the file system and activating swap file

`mount /dev/virgo1/root /mnt`

`mount —mkdir /dev/virgo1/home /mnt/home`

`mount —mkdir /dev/<YOUR-DEVICE-PARTITION-FOR-BOOT> /mnt/boot`

`swapon /dev/virgo1/swap`
# installing Arch!
> This really take a long time 

> Download the arch 

`pacstrap /mnt base linux linux-firmware neovim intel-ucode lvm2`

> Generate the fstab

`genfstab -U /mnt >> /mnt/etc/fstab`

> Now access the arch environment

`arch-chroot /mnt`

## inside our fresh install
### time zone & locale

> Setting the timezone

`ln -sf /usr/share/zoneinfo/America/Bahia /etc/localtime`

`hwclock —systohc`

> Now defining our locale

`nvim /etc/locale.gen`

> Uncomment the “en_US.UTF-8 UTF-8” to use the English language

> And to generate the locale

`locale-gen`

> Just adding language entry in locale conf

`nvim /etc/locale.conf`

> Add the following  “LANG=en_US.UTF-8”

### hostname & root password

> First we set the hostname

`nvim /etc/hostname`

> I will set my to “spica”

> Now configure the hosts file

`nvim /ect/hosts`

> And write …

> now change the root password

`passwd`
### configuring GRUB & mkinitcpio
#### packages before installation of GRUB

> First we need to install GRUB and some other packages

`pacman -S grub efibootmgr mtools dosfstools base-devel git bluez bluez-utils pulseaudio-bluetooth xdg-utils xdg-user-dirs NetworkManager network-manager-applet wireless_tools wpa_supplicant dialog`

> until configure GRUB we need to edit the mkinitcpio file
#### mkinitcpio

> Editing the file to able decryption in boot

`nvim /etc/mkinitcpio.conf`

> Then scroll down to the “HOOKS” section and add “encrypt” & “lvm2” (without the quotes) in between “block” and “filesystems”.

`mkinitcpio -p linux`

#### GRUB

`grub-install —target=x86_64-efi —efi-directory=/boot —bootloader-id=GRUB`

> Then let’s pick the uuid from the encrypted device that is your root partition, we will need to put in the GRUB file

`blkid`

> Now we edit the grub file

`nvim /etc/default/grub` 

> Copying the uuid from the output paste it onto the grub file in the line containing “GRUB_CMDLINE_LINUX” this way “cryptdevice=UUID=<…>:cryptlvm”.

> In the same line put the root directory specified in this way “root=/dev/virgo1/root”

`grub-mkconfig -o /boot/grub/grub.cfg`
### default user

> Now we name the user and set zsh to be our default shell

`useradd -mG wheel -s /bin/zsh <YOUR-USERNAME>`

> Change the user password

`passwd <YOUR-USERNAME>`

> Adding the user to sudoers file
> Set the editor environment to the system and run the command to edit the file

`export EDITOR=nvim`

`visudo`

> I will set all users on the “wheel” group to be allowed to use sudo
> Uncomment this line “%wheel ALL=(ALL:ALL) ALL
### packages & wm
#### graphics & yay

`pacman -S mesa vulkan-intel`

`git clone `
#### wm packages
`yay -S hyprland sddm-git swaync-git pipewire polkit-kde-agent qt5-wayland qt6-wayland waybar rofi-wayland clipse wl-clipboard zathura thunderbird nemo gimp zen google-chrome nomacs kitty hyprpaper hyprpicker hypridle hyprlock hyprcursor xdg-desktop-portal-hyprland iwgtk udiskie`

> To build

wlr-randr

> Flatpacks

Obs-studio steam discord zen

> Github

yay

## finishing

`exit`

`umount -R /mnt`

`reboot now`
