
.global matrix_row_aver_asm

matrix_row_aver_asm:
	push %ebp      			/* Save old base pointer */
    mov %esp, %ebp 			/* Set ebp to current esp */


    pushl %edi                   
    subl $16, %esp                      # allocation de l'espace mémoire pour les variables locale
  	movl 16(%ebp), %edi					# matorder dans %edi
    movl $0, -4(%ebp)                   # r = 0
    movl $0, -8(%ebp)                   # c = 0


for1:                                   # r plus petit que matorder
# for(r = 0; r < matorder; ++r)
# 	elem = 0;

    cmp -4(%ebp), %edi                  # comparaison de matorder et r
    movl $0, -12(%ebp)					# elem = 0
	je end                           	# jump to end if r = matorder
    movl $0, -8(%ebp)                   # c remis à 0


for2:                                   # c plus petit que matorder
# for(c = 0; c < matorder; ++c)
# 	elem += inmatdata[c + r * matorder]

    cmp -8(%ebp), %edi                  # comparaison de c et de matorder 
    je outmatdata[r]                      		# jump to endFor2 if c = matorder

    # elem += inmatdata[c + r * matorder]
    movl 8(%ebp), %ecx					# inmatdata dans %ecx
    movl 12(%ebp), %ebx					# outmatdata dans %ebx
    movl -4(%ebp), %eax                 # r est mis dans %eax
    mull %edi                           # multiplication de r et de matorder
    addl -8(%ebp), %eax                 # c + r * matorder
    movl (%ecx,%eax,4), %eax            # inmatdata[ c + r * matorder ]
    addl %eax, -12(%ebp)                # elem += inmatdata[ c + r * matorder ]

    incl -8(%ebp)                       # c est incrémenté
    jmp for2                            # retour au début de la boucle

outmatdata[r]:

    # outmatdata[r] = elem/matorder
    movl -12(%ebp), %eax                # elem dans le registre %eax
    divl %edi                           # division (%eax = elem/matorder)
    movl -4(%ebp), %edx                 # r est placé dans %edx
    movl  %eax, (%ebx,%edx,4)           # outmatdata[r] = elem/matorder;

    movl $0, -8(%ebp)                   # c remis à 0
    movl $0, %edi                       # r remis à 0

    incl -4(%ebp)                       # r est incrémenté
    movl 16(%ebp), %edi					# matoder dans %edi
    jmp for1                            # jmp au for1

end:

    addl $16, %esp                      # libérer espace variables locales
    pop %edi      
                        
    leave          			/* Restore ebp and esp */
    ret           			/* Return to the caller */
		
