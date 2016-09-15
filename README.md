# realtek_bluetooth
A backport of the current kernel code for most Realtek Bluetooth devices

The intent of this repo is to backport the version of Bluetooth drivers
contained in the current kernel so that they can be used in earlier
kernels. Even though this repo includes drivers for all BT devices
currently in the kernel, the Makefile will only install the USB versions.

Realtek devices handled by this repo include all the USB varieties. As a
result, the BT part of RTL8723BS is not yet covered; however, implementation
of that device is the reason that the UART code is here.

Implementation of this repo is normal. Using the following commands as a
normal user will build and install the driver:

make
sudo make install

Only firmware for the Realtek devices will be installed using this code.

At the moment, only kernel 4.5 and newer will build. I plan to adapt to older
kernels in the future.

