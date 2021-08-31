#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<syscall.h>
#include<sys/types.h> 
#include<errno.h>
#include <sys/mman.h>
#include<string.h>
#include <fcntl.h>
#include<time.h>

#define ASM_VMX_VMFUNC            ".byte 0x0f, 0x01, 0xd4"
typedef unsigned char u8; 
typedef unsigned int u32;
#define PAGE_SIZE 0x1000


static inline u8 __vmx_vmfunc(u32 eptp, u32 func)
{
        u8 error;
        __asm __volatile(ASM_VMX_VMFUNC "; setna %0"
                         : "=q" (error) : "c" (eptp), "a" (func)
                         : "cc");
        return error;
}

int main ()
{
    //unsigned long syscall_nr =60;  //exit
    unsigned long getpid_nr=548;     //548 new getpid
   // unsigned long open_nr=2;
   // long syscall_status=42; 
    //const char * file="/dev/mem";
    //int flags=O_RDWR | O_SYNC;
    //int fd;
    pid_t pid;
    
    //__vmx_vmfunc(1,0);
  /* asm( 
        "syscall"
        :"=a"(fd)
        //rax             rdi     rsi
        :"a"(open_nr),"D"(file),"S"(flags)
        :
    ); 

   
    if (fd<0) {
                perror("Error mem: ");
                goto out;
        }

    void* mmap_base   =  mmap(NULL ,PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x42e7ff000);
    if (mmap_base==(void*)-1){
                        perror("error: ");
                        goto out; 
                        }
    memset(mmap_base,0xaa,PAGE_SIZE);
        printf("@mmap_base :%p     mmap_base: %#llx \n", mmap_base,*(unsigned long long *)mmap_base);
*/



//__vmx_vmfunc(1,0);
asm( 
        "syscall\n" 
        :"=a"(pid)
        :"a"(getpid_nr)
        
    );

    
   // printf("PID : %d\n",pid);
    //printf("PID : %d  #  %d\n",pid,getpid());

   
    /*out:
            close(fd);*/

    return 0; 

}
