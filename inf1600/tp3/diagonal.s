.global matrix_diagonal_asm

matrix_diagonal_asm:
    push %ebp      			/* Save old base pointer */
    mov %esp, %ebp 			/* Set ebp to current esp */
    mov $-1,%esi    #r dans esi
       
boucle1:
    movl $0,%edi            #remet c a 0
    inc %esi                #++r   
    cmp 16(%ebp),%esi       #compare matorder et r
    je fin                  #si egale, jump fin
    
boucle2:
   
    cmp 16(%ebp),%edi        #c - mat  <= 0 alors jump boucle1
    je boucle1
    
    mov 16(%ebp),%edx       #matorder dans %edx
    mov 8(%ebp),%ecx        #ecx = inmatdata
    mov 12(%ebp),%ebx       #ebx = outmatdata
    movl %esi,%eax          #eax = r
    mull %edx               #eax = matorder * r 
    add %edi, %eax          #eax = matorder * r + c
    
    
    
if:
    cmp %esi,%edi           #c == r
    jne else                #si pas egale -> else 
    
    pushl (%ecx,%eax,4)     #-4(%ebp) = inmatdata[c + r * matorder];

    jmp equals
   

fin:
    leave          /* Restore ebp and esp */
    ret            /* Return to the caller */

else:
   push $0                  #-4(%ebp) = 0


equals:
    
    pop %ecx                #-4(%ebp) correspond soit a 0 ou inmatdata[c + r * matorder] selon le cas
    movl %ecx,(%ebx,%eax,4) #outmatdata[c + r * matorder] = ecx
    inc %edi                #c++
    jmp boucle2