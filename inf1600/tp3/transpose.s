.globl matrix_transpose_asm

matrix_transpose_asm:
        push %ebp      /* Save old base pointer */
        mov %esp, %ebp /* Set ebp to current esp */
        
        /* Write your solution here */

        leave          /* Restore ebp and esp */
        ret            /* Return to the caller */
