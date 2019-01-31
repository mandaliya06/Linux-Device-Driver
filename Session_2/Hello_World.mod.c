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
	{ 0xa3250509, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xb02fd006, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xded67658, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xa00f7f8e, __VMLINUX_SYMBOL_STR(param_get_int) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3191286, __VMLINUX_SYMBOL_STR(param_set_int) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1F5180CF65057AC884B10CF");
