.global matrix_row_aver_asm

matrix_row_aver_asm:
        push %ebp      			/* Save old base pointer */
        mov %esp, %ebp 			/* Set ebp to current esp */

		/* Write your solution here */
        pushl %eax                          #
        subl $16, %esp                      # allocation de l'espace mémoire pour les variables locales

        movl 16(%ebp), %ebx                 # matorder est dans ebx
        movl 12(%ebp), %ecx                 # outmatdata est dans ecx
        movl 8(%ebp), %edx                  # inmatdata est dans edx

        movl $0, -4(%ebp)                   # r = 0
        movl $0, -8(%ebp)                   # c = 0


for1:                                       # r plus petit que matorder

        cmp -4(%ebp), %ebx                  # comparaison avec flag de matorder et r
        jna end                             # jmp si r > matorder
        movl $0, -8(%ebp)                   # c remis à 0
        movl $0, -12(%ebp)                  # elem remis à 0

for2:                                       # c plus petit que matorder

        cmp -8(%ebp), %ebx                  # comparaison de c et de matorder avec un flag
        jna endFor2                         # jmp si c > matorder

        movl -4(%ebp), %eax                 # r est mis dans le registre eax
        mul %ebx                            # multiplication de r et de matorder
        addl -8(%ebp), %eax                 # eax -> c + r * matorder
        movl (%edx,%eax,4), %eax            # inmatdata[ c + r * matorder ]
        addl %eax, -12(%ebp)                # elem += inmatdata[ c + r * matorder ]

        incl -8(%ebp)                       # c est incrémenté
        jmp for2                            # retour au début de la boucle

endFor2:

        movl -12(%ebp), %eax                # sauvegrade de elem dans le registre %eax
        divl %ebx                           # division de elem par matorder
        movl -4(%ebp), %edi                 # r est placé dans edi
        movl  %eax, (%ecx,%edi,4)           # outmatdata[r] = elem/matorder;

        movl $0, -8(%ebp)                   # c remis à 0
        movl $0, %edi                       # r remis à 0

        incl -4(%ebp)                       # r est incrémenté
        jmp for1                            # jmp au for1

end:

        addl $16, %esp                      # libérer espace variables locales
        pop %eax                            #
        leave          			/* Restore ebp and esp */
        ret           			/* Return to the caller */
		
