#include <linux/usb.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/stat.h>

/* table of devices that work with this driver */
static struct usb_device_id skel_table [ ] = {
	{ USB_DEVICE(USB_SKEL_VENDOR_ID, USB_SKEL_PRODUCT_ID) },
	{ }
	/* Terminating entry */
};

/*register and init usb_driver*/
static struct usb_driver skel_driver = {
	.owner = THIS_MODULE,
	.name = "skeleton",
	.id_table = skel_table,
	.probe = skel_probe,
	.disconnect = skel_disconnect,
};

static void skel_probe(void){
	
	struct usb_skel *dev;
	struct usb_interface *interface;
	int subminor;
	int retval = 0;
	subminor = iminor(inode);
	interface = usb_find_interface(&skel_driver, subminor);
	if (!interface) {
		err ("%s - error, can't find device for minor %d",__FUNCTION__, subminor);
		retval = -ENODEV;
		goto exit;
	}
	dev = usb_get_intfdata(interface);
	if (!dev) {
		retval = -ENODEV;
		goto exit;
	}
	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &skel_class);
	if (retval) {
		/* something prevented us from registering this driver */
		err("Not able to get a minor for this device.");
		usb_set_intfdata(interface, NULL);
		goto error;
	}
        /* set up the endpoint information */
        /* use only the first bulk-in and bulk-out endpoints */
        iface_desc = interface->cur_altsetting;
        for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
                endpoint = &iface_desc->endpoint[i].desc;
                if (!dev->bulk_in_endpointAddr && (endpoint->bEndpointAddress & USB_DIR_IN) && ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)   == USB_ENDPOINT_XFER_BULK)) {
        	        /* we found a bulk in endpoint */
                        buffer_size = endpoint->wMaxPacketSize;
                        dev->bulk_in_size = buffer_size;
                        dev->bulk_in_endpointAddr = endpoint->bEndpointAddress;
                        dev->bulk_in_buffer = kmalloc(buffer_size, GFP_KERNEL);
                        if (!dev->bulk_in_buffer) {
                                err("Could not allocate bulk_in_buffer");
                                goto error;
                        }
			/* save our data pointer in this interface device */
			usb_set_intfdata(interface, dev);
                }
                if (!dev->bulk_out_endpointAddr && !(endpoint->bEndpointAddress & USB_DIR_IN) && ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK)) {
                /* we found a bulk out endpoint */
                        dev->bulk_out_endpointAddr = endpoint->bEndpointAddress;
                }
        }
        if (!(dev->bulk_in_endpointAddr && dev->bulk_out_endpointAddr)) {
                err("Could not find both bulk-in and bulk-out endpoints");
                goto error;
        }

}

static void skel_disconnect(struct usb_interface *interface)
{
	struct usb_skel *dev;
	int minor = interface->minor;
	/* prevent skel_open( ) from racing skel_disconnect( ) */
	lock_kernel( );
	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);
	/* give back our minor */
	usb_deregister_dev(interface, &skel_class);
	unlock_kernel( );
	/* decrement our usage count */
	kref_put(&dev->kref, skel_delete);
	info("USB Skeleton #%d now disconnected", minor);
}

static int __init usb_skel_init(void)
{
	int result;
	/* register this driver with the USB subsystem */
	result = usb_register(&skel_driver);
	if (result)
		err("usb_register failed. Error number %d", result);
	return result;
}

static void __exit usb_skel_exit(void)
{
	/* deregister this driver with the USB subsystem */
	usb_deregister(&skel_driver);
	/*printk();*/
}


MODULE_DEVICE_TABLE (usb, skel_table);
module_init(usb_skel_init);
module_exit(usb_skel_exit);
MODULE_LICESE("GPL");
MODULE_AUTHOR("Cheng Feitian <artisticbones@163.com>");
