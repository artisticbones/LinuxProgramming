#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x2005612d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6a4ecc4a, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0xe84a02e9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x2befa3be, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xada1f064, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xf3b1a893, __VMLINUX_SYMBOL_STR(alloc_etherdev_mqs) },
	{ 0x62a0145d, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x5dae5487, __VMLINUX_SYMBOL_STR(skb_tstamp_tx) },
	{ 0xbb4e0564, __VMLINUX_SYMBOL_STR(consume_skb) },
	{  0xa3e8e, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xb21790ab, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D9CC9D36702299E11AA0F96");
