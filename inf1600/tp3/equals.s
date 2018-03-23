.globl matrix_equals_asm

matrix_equals_asm:
        push %ebp      /* Save old base pointer */
        mov %esp, %ebp /* Set ebp to current esp */
        
        /* Write your solution here */
        mov $0,%esi        #r dans ESI
       
        mov 8(%ebp),%ecx   #inmatdata1 dans ecx
        mov 12(%ebp),%ebx  #inmatdata2 dans ebx
        
        
boucle1:
    mov $0,%edi            #c dans EDI             
    cmp %esi,16(%ebp)      
    je fin1                #r - mat <= 0 alors jump fin   
    inc %esi  #++r

boucle2:
   
    cmp %edi,16(%ebp)           #c - mat  <= 0 alors jump boucle1
    je boucle1
    inc %edi

 if:   
    mov 16(%ebp),%edx       #matorder dans %edx
    movl %esi,%eax          #eax = r
    mull %edx               #eax = matorder * r 
    add %edi, %eax          #eax = matorder * r +c
    pushl (%ecx,%eax,4)     #-4(%ebp) = inmatdata1[c + r * matorder]
    pushl (%ebx,%eax,4)     #-8(ebp) = inmatdata2[c + r * matorder]
    pop %eax
    pop %edx
    cmp %eax,%edx
    je boucle2              #si egale, recommence la boucle2
    
    movl $0,%eax
fin: 
    leave          /* Restore ebp and esp */
    ret            /* Return to the caller */
fin1 :
    movl $1,%eax
    jmp fin
    
    