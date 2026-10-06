.text

.global mygetpid_32


mygetpid_32:
 
	movl $20, %eax
	int $128

	ret  

.section .note.GNU-stack,"",@progbits

.end
