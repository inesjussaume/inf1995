.globl matrix_equals_asm

matrix_equals_asm:
        push %ebp      /* Save old base pointer */
        mov %esp, %ebp /* Set ebp to current esp */
        
        /* Write your solution here */
        mov $0,%esi        #r dans ESI
        mov $0,%edi        #c dans EDI
        mov 16(%ebp),%edx  #matorder dans %edx
        mov 8(%ebp),%ecx   #inmatdata1 dans ecx
        mov 12(%ebp),%ebx  #inmatdata2 dans ebx
        
        
boucle1:
    inc %esi                #++r
    cmp %esi,%eax      
    jna fin                #mat - r <= 0 alors jump fin   
    jmp boucle2             #utile ? puisque boucle2 est apres
 

boucle2:
    inc %edi
    cmp %edi,%eax           #mat - c <= 0 alors jump boucle1
    jna boucle1

 if:   
    movl %esi,%eax          #eax = r
    mull %edx               #eax = matorder * r 
    add %edi, %eax          #eax = matorder * r +c
    pushl (%ecx,%eax,4)     #-4(%ebp) = inmatdata1[c + r * matorder]
    pushl (%ebx,%eax,4)     #-8(%ebp) = inmatdata2[c + r * matorder]
    pop %eax                #%eax = inmatdata2[c + r * matorder]
    pop %edx                #edx = inmatdata1[c + r * matorder]
    cmp %eax,%edx
    je boucle2              #si egale, recommence la boucle2
    
    movl $0,%eax
    leave          /* Restore ebp and esp */
    ret            /* Return to the caller */

fin:
        movl $1,%eax
        leave          /* Restore ebp and esp */
        ret            /* Return to the caller */
