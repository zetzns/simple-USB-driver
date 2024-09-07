#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zn");
MODULE_DESCRIPTION("USB READING AND INITTIALIZING");

#define VENDOR_ID 0x0951
#define PRODUCT_ID 0x16a5

static struct usb_device_id my_usb_table[] = {
    {USB_DEVICE(VENDOR_ID, PRODUCT_ID)},
    {},
};

MODULE_DEVICE_TABLE(usb, my_usb_table);

static int usb_probe(struct usb_interface *intf, const struct usb_device_id *id) {
    printk(KERN_INFO "[+] FLASH DRIVE PROBED");
    return 0;
}

static void usb_disconnect(struct usb_interface *intf) {
    printk(KERN_INFO "[-] FLASH DISCONNECTED"); 
}

static struct usb_driver mydriver = {
    .name = "IAU_FLASH_DRIVER",
    .id_table = my_usb_table,
    .probe = usb_probe,
    .disconnect = usb_disconnect,
};

static int __init module_probe(void) {
    printk(KERN_INFO "[ ] FLASH DRIVE MODULE INITIALISING");
    int result;
    result = usb_register(&mydriver);
    if (!result) {
        printk(KERN_ERR "[-] FLASH DRIVE REGISTRATION FAILED\n");
        return -result;
    }
    printk(KERN_INFO "[+] FLASH DRIVE REGISTERED SUCCESSFULLY\n");
    return 0;
}

static void __exit module_remov(void) {
    printk(KERN_INFO "[ ] Removing FLASH DRIVE MODULE\n");
    usb_deregister(&mydriver);
    printk(KERN_INFO "[+] FLASH DRIVE MODULE REMOVED\n");
}

module_init(module_probe);
module_exit(module_remov);
