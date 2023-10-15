#define ASM 1

.text

.globl load_page_directory, enablePaging, allowMixedPages

load_page_directory:
    pushl %ebp
    mov %esp, %ebp
    mov 8(%ebp), %eax
    mov %eax, %cr3
    mov %ebp, %esp
    popl %ebp
    ret


enablePaging:
    pushl %ebp
    mov %esp, %ebp
    mov %cr0, %eax
    #or $0x80000000, %eax
    or $0x80000001, %eax
    mov %eax, %cr0
    mov %ebp, %esp
    popl %ebp
    ret

allowMixedPages:
    push %ebp
    mov %esp, %ebp
    mov %cr4, %eax
    or $0x00000010, %eax
    mov %eax, %cr4
    mov %ebp, %esp
    pop %ebp
    ret