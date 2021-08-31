#include<asm/irqflags.h>
#include "../linux-4.9/arch/x86/entry/calling.h"
#include "syscall.h"

.global __sysret
__sysret:
        RESTORE_C_REGS_EXCEPT_RCX_R11
        SWITCH_USER_CR3
        movq RSP(%rsp), %rsp
        USERGS_SYSRET64
