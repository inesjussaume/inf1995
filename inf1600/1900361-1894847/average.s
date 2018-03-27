
.global matrix_row_aver_asm

matrix_row_aver_asm:
	push %ebp      			/* Save old base pointer */
    mov %esp, %ebp 			/* Set ebp to current esp */

    subl $8, %esp                       # allocation de l'espace mémoire pour les variables locale
    pusha
  	
    xorl %esi, %esi                     # r = 0 dans %esi
    xorl %edi, %edi                     # c = 0 dans %edi



for1:                                   # r plus petit que matorder
# for(r = 0; r < matorder; ++r)
# 	elem = 0;

    cmp %esi, 16(%ebp)                  # comparaison de matorder et r
    movl $0, -4(%ebp)					# elem = 0
	jle end                           	# jump to end if r = matorder
    xorl %edi, %edi                       # c remis à 0


for2:                                   # c plus petit que matorder
# for(c = 0; c < matorder; ++c)
# 	elem += inmatdata[c + r * matorder]

    cmp %edi, 16(%ebp)                  # comparaison de c et de matorder 
    jle outmatdataR                     # jump to outmatdataR if c = matorder

    # elem += inmatdata[c + r * matorder]

    movl %esi, %eax                     # r est mis dans %eax
    mull 16(%ebp)                       # multiplication de r et de matorder
    addl %edi, %eax                     # c + r * matorder
    movl 8(%ebp), %ecx					# inmatdata dans %ecx                               #####
    movl (%ecx,%eax,4), %eax            # inmatdata[ c + r * matorder ]
    addl %eax, -4(%ebp)                 # elem += inmatdata[ c + r * matorder ]

    incl %edi                           # c est incrémenté
    jmp for2                            # retour au début de la boucle

outmatdataR:

    # outmatdata[r] = elem/matorder
    movl -4(%ebp), %eax                 # elem dans le registre %eax (utilise pour la multiplication)
    divl 16(%ebp)                       # division (%eax = elem/matorder)
    movl 12(%ebp), %ebx					# outmatdata dans %ebx                              #####
    movl %eax, (%ebx,%esi,4)            # outmatdata[r] = elem/matorder;

    xorl %edi, %edi                       # c remis à 0
    incl %esi                           # r est incrémenté
    jmp for1                            # jmp au debut du for1

end:
    popa
    addl $8, %esp                      # libérer espace variables locales

                        
    leave          			           /* Restore ebp and esp */
    ret           			           /* Return to the caller */
		
