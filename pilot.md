# Pilot

CSAW Quals 2017

# Points: 75

# Write-Up

Can I take your order?

	file *
	pilot: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=6ed26a43b94fd3ff1dd15964e4106df72c01dc6c, stripped

	./pilot
	*]Welcome DropShip Pilot...
	[*]I am your assitant A.I....
	[*]I will be guiding you through the tutorial....
	[*]As a first step, lets learn how to land at the designated location....
	[*]Your mission is to lead the dropship to the right location and execute sequence of instructions to save Marines & Medics...
	[*]Good Luck Pilot!....
	[*]Location:0x7ffcc3c86d80
	[*]Command:d
	[*]There are no commands....
	[*]Mission Failed....

You want to run it in as close to the environment it is suppose to run

	z3r0@ubuntu:~/Desktop/pilot$ strings pilot 
	/lib64/ld-linux-x86-64.so.2
	libstdc++.so.6
	__gmon_start__
	_Jv_RegisterClasses
	_ITM_deregisterTMCloneTable
	_ITM_registerTMCloneTable
	_ZNSt8ios_base4InitD1Ev
	_ZNSolsEPFRSoS_E
	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	_ZNSolsEPKv
	_ZNSt8ios_base4InitC1Ev
	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	_ZSt4cout
	libc.so.6
	stdin
	__cxa_atexit
	read
	stdout
	setvbuf
	__libc_start_main
	GLIBCXX_3.4
	GLIBC_2.2.5
	UH-x `
	AWAVA
	AUATL
	[]A\A]A^A_
	[*]Welcome DropShip Pilot...
	[*]I am your assitant A.I....
	[*]I will be guiding you through the tutorial....
	[*]As a first step, lets learn how to land at the designated location....
	[*]Your mission is to lead the dropship to the right location and execute sequence of instructions to save Marines & Medics...
	[*]Good Luck Pilot!....
	[*]Location:
	[*]Command:
	[*]There are no commands....
	[*]Mission Failed....
	;*3$"
	GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609
	.shstrtab
	.interp
	.note.ABI-tag
	.note.gnu.build-id
	.gnu.hash
	.dynsym
	.dynstr
	.gnu.version
	.gnu.version_r
	.rela.dyn
	.rela.plt
	.init
	.plt.got
	.text
	.fini
	.rodata
	.eh_frame_hdr
	.eh_frame
	.init_array
	.fini_array
	.jcr
	.dynamic
	.got.plt
	.data
	.bss
	.comment

These specifically are name mangling:

        _ZNSt8ios_base4InitD1Ev
        _ZNSolsEPFRSoS_E
        _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
        _ZNSolsEPKv
        _ZNSt8ios_base4InitC1Ev
        _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
        _ZSt4cout

Name mangling is the encoding of function and variable names into unique names so that linkers can separate common names in the language. 

Type names may also be mangled. 

Name mangling is commonly used to facilitate the overloading feature and visibility within different scopes.

We now will use objdump -p, which shows the program headers

	z3r0@ubuntu:~/Desktop/pilot$ objdump -p pilot
	
	pilot:     file format elf64-x86-64
	
	Program Header:
	    PHDR off    0x0000000000000040 vaddr 0x0000000000400040 paddr 0x0000000000400040 align 2**3
	         filesz 0x00000000000001f8 memsz 0x00000000000001f8 flags r-x
	  INTERP off    0x0000000000000238 vaddr 0x0000000000400238 paddr 0x0000000000400238 align 2**0
	         filesz 0x000000000000001c memsz 0x000000000000001c flags r--
	    LOAD off    0x0000000000000000 vaddr 0x0000000000400000 paddr 0x0000000000400000 align 2**21
	         filesz 0x0000000000000f3c memsz 0x0000000000000f3c flags r-x
	    LOAD off    0x0000000000001df8 vaddr 0x0000000000601df8 paddr 0x0000000000601df8 align 2**21
	         filesz 0x0000000000000280 memsz 0x00000000000003c8 flags rw-
	 DYNAMIC off    0x0000000000001e18 vaddr 0x0000000000601e18 paddr 0x0000000000601e18 align 2**3
	         filesz 0x00000000000001e0 memsz 0x00000000000001e0 flags rw-
	    NOTE off    0x0000000000000254 vaddr 0x0000000000400254 paddr 0x0000000000400254 align 2**2
	         filesz 0x0000000000000044 memsz 0x0000000000000044 flags r--
	EH_FRAME off    0x0000000000000dc4 vaddr 0x0000000000400dc4 paddr 0x0000000000400dc4 align 2**2
	         filesz 0x0000000000000044 memsz 0x0000000000000044 flags r--
	   STACK off    0x0000000000000000 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**4
	         filesz 0x0000000000000000 memsz 0x0000000000000000 flags rwx
	   RELRO off    0x0000000000001df8 vaddr 0x0000000000601df8 paddr 0x0000000000601df8 align 2**0
	         filesz 0x0000000000000208 memsz 0x0000000000000208 flags r--

	Dynamic Section:
	  NEEDED               libstdc++.so.6
	  NEEDED               libc.so.6
	  INIT                 0x00000000004007c8
	  FINI                 0x0000000000400c04
	  INIT_ARRAY           0x0000000000601df8
	  INIT_ARRAYSZ         0x0000000000000010
	  FINI_ARRAY           0x0000000000601e08
	  FINI_ARRAYSZ         0x0000000000000008
	  GNU_HASH             0x0000000000400298
	  STRTAB               0x0000000000400480
	  SYMTAB               0x00000000004002d0
	  STRSZ                0x000000000000018e
	  SYMENT               0x0000000000000018
	  DEBUG                0x0000000000000000
	  PLTGOT               0x0000000000602000
	  PLTRELSZ             0x00000000000000f0
	  PLTREL               0x0000000000000007
	  JMPREL               0x00000000004006d8
	  RELA                 0x0000000000400678
	  RELASZ               0x0000000000000060
	  RELAENT              0x0000000000000018
	  VERNEED              0x0000000000400638
	  VERNEEDNUM           0x0000000000000002
	  VERSYM               0x000000000040060e

	Version References:
	  required from libstdc++.so.6:
	    0x08922974 0x00 03 GLIBCXX_3.4
	  required from libc.so.6:
	    0x09691a75 0x00 02 GLIBC_2.2.5

Now if we use objdump -h, we get section headers

	z3r0@ubuntu:~/Desktop/pilot$ objdump -h pilot

	pilot:     file format elf64-x86-64
	
	Sections:
	Idx Name          Size      VMA               LMA               File off  Algn
	  0 .interp       0000001c  0000000000400238  0000000000400238  00000238  2**0
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  1 .note.ABI-tag 00000020  0000000000400254  0000000000400254  00000254  2**2
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  2 .note.gnu.build-id 00000024  0000000000400274  0000000000400274  00000274  2**2
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  3 .gnu.hash     00000038  0000000000400298  0000000000400298  00000298  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  4 .dynsym       000001b0  00000000004002d0  00000000004002d0  000002d0  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  5 .dynstr       0000018e  0000000000400480  0000000000400480  00000480  2**0
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  6 .gnu.version  00000024  000000000040060e  000000000040060e  0000060e  2**1
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  7 .gnu.version_r 00000040  0000000000400638  0000000000400638  00000638  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  8 .rela.dyn     00000060  0000000000400678  0000000000400678  00000678  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	  9 .rela.plt     000000f0  00000000004006d8  00000000004006d8  000006d8  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	 10 .init         0000001a  00000000004007c8  00000000004007c8  000007c8  2**2
	                  CONTENTS, ALLOC, LOAD, READONLY, CODE
	 11 .plt          000000b0  00000000004007f0  00000000004007f0  000007f0  2**4
	                  CONTENTS, ALLOC, LOAD, READONLY, CODE
	 12 .plt.got      00000008  00000000004008a0  00000000004008a0  000008a0  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, CODE
	 13 .text         00000352  00000000004008b0  00000000004008b0  000008b0  2**4
	                  CONTENTS, ALLOC, LOAD, READONLY, CODE
	 14 .fini         00000009  0000000000400c04  0000000000400c04  00000c04  2**2
	                  CONTENTS, ALLOC, LOAD, READONLY, CODE
	 15 .rodata       000001b3  0000000000400c10  0000000000400c10  00000c10  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	 16 .eh_frame_hdr 00000044  0000000000400dc4  0000000000400dc4  00000dc4  2**2
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	 17 .eh_frame     00000134  0000000000400e08  0000000000400e08  00000e08  2**3
	                  CONTENTS, ALLOC, LOAD, READONLY, DATA
	 18 .init_array   00000010  0000000000601df8  0000000000601df8  00001df8  2**3
	                  CONTENTS, ALLOC, LOAD, DATA
	 19 .fini_array   00000008  0000000000601e08  0000000000601e08  00001e08  2**3
	                  CONTENTS, ALLOC, LOAD, DATA
	 20 .jcr          00000008  0000000000601e10  0000000000601e10  00001e10  2**3
	                  CONTENTS, ALLOC, LOAD, DATA
	 21 .dynamic      000001e0  0000000000601e18  0000000000601e18  00001e18  2**3
	                  CONTENTS, ALLOC, LOAD, DATA
	 22 .got          00000008  0000000000601ff8  0000000000601ff8  00001ff8  2**3
	                  CONTENTS, ALLOC, LOAD, DATA
	 23 .got.plt      00000068  0000000000602000  0000000000602000  00002000  2**3
	                  CONTENTS, ALLOC, LOAD, DATA
	 24 .data         00000010  0000000000602068  0000000000602068  00002068  2**3
	                  CONTENTS, ALLOC, LOAD, DATA
	 25 .bss          00000140  0000000000602080  0000000000602080  00002078  2**5
	                  ALLOC
	 26 .comment      00000034  0000000000000000  0000000000000000  00002078  2**0
	                  CONTENTS, READONLY

Now we need to work our way to main.

	z3r0@ubuntu:~/Desktop/pilot$ strings pilot | grep main
	__libc_start_main

For the 64 bit architecture, we will use the following registers: rdi, rsi, rdx, rcx, r8, r9

Now if we have more than 6 variables, the 7th+ variable will "spill" over into the stack



# Main Sections in a Binary

.text: machine code; permissions are r,x (readable and executable); its read-only, cannot write to it

.rodata: read-only data; static storage class

.data: static storage class

.bss: static storage class

NOTE: in static storage class, you can only put globals and static in it

const int x =5; const int a[]={1, 2, 3, 4}; const char *p = "hello";

