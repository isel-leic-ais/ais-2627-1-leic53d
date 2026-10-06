.text

.global my_write

#my_write(int fd, char *msg, int size)
my_write:

	movq $1, %rax
	syscall
	ret

.section .note.GNU-stack,"",@progbits

.end

