.globl matrix_transpose_asm

matrix_transpose_asm:
    push %ebp      /* Save old base pointer */
    mov %esp, %ebp /* Set ebp to current esp */
    /* Write your solution here */
    movl $-1,%esi   #esi = r
        
boucle1:
    movl $0,%edi            #edi = c 
    inc %esi                #++r                   
    cmp 16(%ebp),%esi      
    je fin                  #r - mat <= 0 alors jump fin   
    
 
boucle2:
   
    cmp 16(%ebp),%edi       #c - mat  <= 0 alors jump boucle1
    je boucle1

equals:
    mov 16(%ebp),%edx       #matorder dans %edx
    mov 8(%ebp),%ecx        #ecx = inmatdata
    mov 12(%ebp),%ebx       #ebx = outmatdata
    movl %edi,%eax          #eax = c
    mull %edx               #eax = matorder * c 
    add %esi, %eax          #eax = matorder * c + r
    pushl (%ecx,%eax,4)     #-4(%ebp) = inmatdata1[r + c * matorder]
    mov 16(%ebp),%edx       #matorder dans %edx
    movl %esi,%eax          #eax = r
    mull %edx               #eax = matorder * r 
    addl %edi, %eax         #eax = matorder * r + c   
    pop %ecx                #ecx = inmatdata1[r + c * matorder]
    movl %ecx,(%ebx,%eax,4)
    inc %edi
    jmp boucle2              #si egale, recommence la boucle2
    
fin:

        leave          /* Restore ebp and esp */
        ret            /* Return to the caller */
