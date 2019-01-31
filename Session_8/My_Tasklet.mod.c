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
	{ 0xef894695, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x69bc1dfe, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0x272a93ec, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x42478974, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x67cddac, __VMLINUX_SYMBOL_STR(sysfs_remove_file_ns) },
	{ 0x559fce34, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0x17661d23, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9166146e, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2072ee9b, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x18f1756b, __VMLINUX_SYMBOL_STR(sysfs_create_file_ns) },
	{ 0x78e84890, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x6a63ab7a, __VMLINUX_SYMBOL_STR(kernel_kobj) },
	{ 0x64e9dfd0, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xaafe7238, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x25e5fb21, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x5f25fde6, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "89EC514AC6A5BE7401F182E");
