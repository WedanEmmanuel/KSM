#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


#define ASM_VMX_VMFUNC   ".byte 0x0f, 0x01, 0xd4"
#define PAGE_SIZE       0x1000
typedef unsigned char   u8; 
typedef unsigned int    u32;



static inline u8 __vmx_vmfunc(u32 eptp, u32 func)
{
        u8 error;
        __asm __volatile(ASM_VMX_VMFUNC "; setna %0"
                         : "=q" (error) : "c" (eptp), "a" (func)
                         : "cc");
        return error;
}



int main(){
        int eptp=0;
        
        int fdmem=open("/dev/mem",O_RDWR |O_SYNC);
        if (fdmem<0) {
                perror("Error mem: ");
                goto out;
        }

        void* mmap_base   =  mmap(NULL ,PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fdmem, 0x42e7ff000); //0x42e7ff000
        void* mmap_base1 = mmap(NULL ,PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fdmem,0x42e7ff000-PAGE_SIZE); //0x42e7ff000
        //void* mmap_base2 = mmap(NULL ,PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fdmem, 0x42e801000); //0x42e7ff000
                

        if (mmap_base==(void*)-1 || mmap_base1==(void*)-1){
        //if (mmap_base==(void*)-1){
                        perror("error: ");
                        goto out; 
                        }
                
        for(int i=0; i<4; i++) {
                printf("provide eptp index >  ");
                scanf("%d",&eptp);

                printf("Before @mmap_base :%p     mmap_base: %#llx \n",mmap_base,*(unsigned long long *)mmap_base);
                memset(mmap_base1,0xbb,PAGE_SIZE);

                __vmx_vmfunc((eptp-1),0);
                //void *mmap_base1   =  mmap(NULL ,PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fdmem, 0x42e7ff000+(eptp-1)*PAGE_SIZE); 

                memset(mmap_base,0xaa,PAGE_SIZE);
                printf("eptp : %d     @mmap_base :%p     mmap_base: %#llx \n",eptp-1, mmap_base,*(unsigned long long *)mmap_base);

                __vmx_vmfunc(eptp,0);
                //void *mmap_base2   =  mmap(NULL ,PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fdmem, 0x42e7ff000+eptp*PAGE_SIZE); 
                //memset(mmap_base,eptp,PAGE_SIZE);
                printf("eptp : %d     @mmap_base :%p     mmap_base: %#llx \n",eptp,mmap_base,*(unsigned long long *)mmap_base);
                
                __vmx_vmfunc((eptp-1),0);
                printf("eptp : %d     @mmap_base :%p     mmap_base: %#llx \n",eptp -1,mmap_base,*(unsigned long long *)mmap_base);
        
        }       
        out:
                close(fdmem);
        return 0;
                
}
