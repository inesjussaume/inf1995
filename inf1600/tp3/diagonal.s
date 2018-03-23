.global matrix_diagonal_asm

matrix_diagonal_asm:
    push %ebp      			/* Save old base pointer */
    mov %esp, %ebp 			/* Set ebp to current esp */
    mov $-1,%esi    #r dans esi
       
boucle1:
    movl $0,%edi        
    inc %esi  #++r   
    cmp 16(%ebp),%esi 
    je fin
    
boucle2:
   
    cmp 16(%ebp),%edi         #c - mat  <= 0 alors jump boucle1
    je boucle1
    
    mov 16(%ebp),%edx       #matorder dans %edx
    mov 8(%ebp),%ecx        #ecx = inmatdata
    mov 12(%ebp),%ebx       #ebx = outmatdata
    movl %esi,%eax          #eax = r
    mull %edx               #eax = matorder * r 
    add %edi, %eax          #eax = matorder * r + c
    
    
    
if:
    cmp %esi,%edi
    jne else
    
    pushl (%ecx,%eax,4)

    jmp equals
   

fin:
    leave          /* Restore ebp and esp */
    ret            /* Return to the caller */

else:
   push $0


equals:
    
    pop %ecx
    movl %ecx,(%ebx,%eax,4)
    inc %edi
    jmp boucle2