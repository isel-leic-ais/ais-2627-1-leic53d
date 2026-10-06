.text

.global mywrite_32

/*
 * write system call using "int" instruction as
 * system call mechanism
 */

mywrite_32:

    // adjust parameters for 32 bit call
    
	pushq %rbx
	movl %edi, %ebx
	movl %esi, %ecx
	
     
	movl $4, %eax
	int $128
	
	popq %rbx
	ret  

.section .note.GNU-stack,"",@progbits

.end
