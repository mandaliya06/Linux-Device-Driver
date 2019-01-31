
@Date : 14/1/2019
@Name : Kishan Mandaliya

/*********************************************************************************************/
					Session-7
/*********************************************************************************************/
1.Interrupts Handling

File : My_INT.c

Description :
               This file for Registering an Interrupt Handler. 
		

Steps to compile LKM :
1.Run                           make
2.Insert module                 sudo insmod My_SysFs.ko
  kernel ring buffer
3.see the sysfs entry in 
/sys/kernel directroy 		cat /sys/kernel/My_SysFs/My_value
4. write in My_proc             echo 1234 > /sys/kernel/My_sysFs/My_value
5.Remove module                 sudo rmmod My_SysFs
6.Run                           make clean

Key points :

-> /* request_irq: allocate a given interrupt line */
int request_irq(unsigned int irq,
                irq_handler_t handler,
                unsigned long flags,
                const char *name,
                void *dev)

->  The first parameter, irq, specifies the interrupt number to allocate

    For some devices (e.g. legacy PC devices such as the system timer or keyboard), this value is typically hard-coded.
    For most other devices, it is probed or otherwise determined programmatically and dynamically.

->  The second parameter, handler, is a function pointer to the actual interrupt handler that services this interrupt. This function is invoked whenever the operating system receives the interrupt.

-> Interrupt Handler Flags
	->IRQF_SHARED. This flag specifies that the interrupt line can be shared among multiple interrupt handlers. Each handler registered on a given line must specify this flag; otherwise, only one handler can exist per line.

-> The fourth parameter, name, is name of the device associated with the interrupt. For example, this value for the keyboard interrupt on a PC is "keyboard". These text names are used by /proc/irq and /proc/interrupts.

-> The fifth parameter, dev, is used for shared interrupt lines. When an interrupt handler is freed (discussed later), dev provides a unique cookie to enable the removal of only the desired interrupt handler from the interrupt line. Without this parameter, it would be impossible for the kernel to know which handler to remove on a given interrupt line. You can pass NULL here if the line is not shared, but you must pass a unique cookie if your interrupt line is shared. This pointer is also passed into the interrupt handler on each invocation. A common practice is to pass the driver's device structure. This pointer is unique and might be useful to have within the handlers.

-> request_irq() returns zero on success and nonzero value indicates an error, in which case the specified interrupt handler was not registered. A common error is -EBUSY, which denotes that the given interrupt line is already in use (and either the current user or you did not specify IRQF_SHARED).

request_irq() cannot be called from interrupt context (other situations where code cannot block), because it can block. It is a common mistake to call request_irq() when it is unsafe to sleep. On registration, an entry corresponding to the interrupt is created in /proc/irq. The function proc_mkdir() creates new procfs entries. This function calls proc_create() to set up the new procfs entries, which in turn calls kmalloc() to allocate memory. kmalloc() can sleep 

Freeing an Interrupt Handler

-> When your driver unloads, you need to unregister your interrupt handler and disable the interrupt line, by calling:
void free_irq(unsigned int irq, void *dev)

->  if the specified interrupt line is not shared, this function removes the handler and disables the line.
    If the interrupt line is shared, the handler identified via dev is removed, but the interrupt line is disabled only when the last handler is removed. With shared interrupt lines, a unique cookie is required to differentiate between the multiple handlers that can exist on a single line and enable free_irq() to remove only the correct handler.

-> In either case (shared or unshared), if dev is non-NULL, it must match the desired handler. A call to free_irq() must be made from process context.
