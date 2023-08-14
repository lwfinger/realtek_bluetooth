SHELL := /bin/sh
FW_DIR	:= /lib/firmware/rtl_bt/
MDL_DIR	:= /lib/modules/$(shell uname -r)
DRV_DIR	:= $(MDL_DIR)/kernel/drivers/bluetooth
EXTRA_CFLAGS += -DCONFIG_BT_RTL

#Handle the compression option for modules in 3.18+
ifneq ("","$(wildcard $(DRV_DIR)/*.ko.gz)")
COMPRESS_GZIP := y
endif
ifneq ("","$(wildcard $(DRV_DIR)/*.ko.xz)")
COMPRESS_XZ := y
endif

ifneq ($(KERNELRELEASE),)

obj-m := btusb.o btrtl.o btintel.o btbcm.o
obj-m += hci_vhci.o
obj-m += hci_uart.o
hci_uart-m	:= hci_ldisc.o
hci_uart-m	+= hci_serdev.o
hci_uart-m	+= hci_h4.o
hci_uart-m	+= hci_bcsp.o
hci_uart-m	+= hci_ll.o
hci_uart-m	+= hci_ath.o
hci_uart-m	+= hci_h5.o
hci_uart-m	+= hci_intel.o
hci_uart-m	+= hci_bcm.o
hci_uart-m	+= hci_qca.o
hci_uart-m	+= hci_ag6xx.o
hci_uart-m	+= hci_mrvl.o

else
	PWD := $(shell pwd)
	KVER := $(shell uname -r)
	KDIR := /lib/modules/$(KVER)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.mod.c *.mod.o *.ko *.symvers *.order *.a
endif

install:
	@mkdir -p $(FW_DIR)
	@cp -f firmware/*_fw.bin $(FW_DIR)/.
	@cp -f firmware/*_config.bin $(FW_DIR)/.
	@cp -f *.ko $(DRV_DIR)/.
ifeq ($(COMPRESS_GZIP), y)
	@gzip -f $(DRV_DIR)/btusb.ko
	@gzip -f $(DRV_DIR)/btbcm.ko
	@gzip -f $(DRV_DIR)/btintel.ko
	@gzip -f $(DRV_DIR)/btrtl.ko
endif
ifeq ($(COMPRESS_XZ), y)
	@xz -f $(DRV_DIR)/btusb.ko
	@xz -f $(DRV_DIR)/btbcm.ko
	@xz -f $(DRV_DIR)/btintel.ko
	@xz -f $(DRV_DIR)/btrtl.ko
endif
	@depmod -a
	@echo "installed revised btusb"

uninstall:
	rm -f $(DRV_DIR)/btusb.ko*
	depmod -a $(MDL_DIR)
	echo "uninstalled revised btusb"
