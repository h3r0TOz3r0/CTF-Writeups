# Reverse Engineering Pre-Instruction

6 February 2019

Basic Instruction... Static Analysis

1. file *

	ELF = linux executable; 32 vs 64 bits = type of architecture

2. objdump -d <file> ((OPTIONAL) > file_name_to_write_to )

	disassemble 

3. xxd <file>

4. strings <file>

5. readelf -s

	gives all the functions in the ELF

6. IDA Pro

	use F5 for it to translate assembly to c code

Basic Instruction... Dynamic Analysis

1. gdb

# Reverse Engineering Lesson 1 from Chris Eagle

1. Input Operations

	- gets(): Never use this function. If you see this, then this is where the vulnerability is. Reads until character return.

	The only thing that matters is line feed (0x0A ln)

	- fgets(): reading stops at end of file or new line; safer than gets

	- read(): doesn't care about any particular characters; system call

	libc function vs. system call = instant transition from linux space to kernel space, kernel can read/write bytes (never looks at bytes)

	- write(): output or read()

	- scanf()

# Reverse Engineering Lesson 2 from Chris Eagle

mprotect/brk or sbrk

mmap: takes 6 arguments (permissions of pages

malloc

What happens if malloc runs out of memory?

	- 
