#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <asm/msr.h>
#include <linux/syscalls.h>

extern void __sysret(void);


#define MSR_LSTAR 0xC000082


/*CPU Initialzation
*for the kernel to receive incoming system calls, it must register the 
*address of the code that will execute when a system call occurs by
* writing its address to the IA32_LSTAR MSR
*/
void syscall_init(){
    wrmsrl(MSR_LSTAR,sys_call);
}

void sys_call(void){
SYSCALL_DEFINE0(getpid); 
}

syscall_init();
__sysret();
