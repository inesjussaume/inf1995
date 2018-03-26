.globl matrix_equals_asm

matrix_equals_asm:
    push %ebp      /* Save old base pointer */
    mov %esp, %ebp /* Set ebp to current esp */
    mov $-1,%esi    #r dans esi
       
boucle1:
    movl $0,%edi            #c dans edi
    inc %esi                #++r                      
    cmp 16(%ebp),%esi      
    je fin1                 #r - mat <= 0 alors jump fin1   
                            
 
boucle2:
   
    cmp 16(%ebp),%edi       #c - mat  <= 0 alors jump boucle1
    je boucle1

equals:
    mov 16(%ebp),%edx       #matorder dans %edx
    mov 8(%ebp),%ecx        #ecx = inmatdata1
    mov 12(%ebp),%ebx       #ebx = inmatdata2
    movl %esi,%eax          #eax = r
    mull %edx               #eax = matorder * r 
    add %edi, %eax          #eax = matorder * r +c
    
    pushl (%ecx,%eax,4)     #-4(%ebp) = inmatdata1[c + r * matorder]
    pushl (%ebx,%eax,4)     #-8(ebp) = inmatdata2[c + r * matorder]
    pop %eax                #eax = inmatdata2[c + r * matorder]
    pop %edx                #edx = inmatdata1[c + r * matorder]
    
    inc %edi                #c++
    cmp %eax,%edx           #inmatdata1[c + r * matorder] - inmatdata2[c + r * matorder]
    je boucle2              #si egale, recommence la boucle2
    movl $0,%eax            #si pas egale, 0 dans eax et on sort de la fonctionne (return 0;)
 
fin: 
    leave          /* Restore ebp and esp */
    ret            /* Return to the caller */
fin1 :
    movl $1,%eax            #return 1;
    jmp fin
     
