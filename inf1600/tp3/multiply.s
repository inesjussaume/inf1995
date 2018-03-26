
.globl matrix_multiply_asm

matrix_multiply_asm:
	push %ebp      				/* save old base pointer */
	mov %esp, %ebp 				/* set ebp to current esp */
        
    subl $16, %esp				#make room for variables (r,c,i and elem)
    movl 20(%ebp), %ebx			# put matorder in ebx
    movl $0, -4(%ebp)			# r = 0
    movl $0, -8(%ebp)			# c = 0
	movl $0, -12(%ebp)			# i = 0
		
for1:
# for(r = 0; r < matorder; ++r)

	cmp -4(%ebp), %ebx			# condition du for (matorder - r)
	je end						# jump to end if matorder = r
	
for2:
# for(c = 0; c < matorder; ++c)
# 	elem = 0;

	cmp -8(%ebp), %ebx					# condition du for (matorder - c)
	movl $0, -16(%ebp)					# elem = 0
	jne for3							# jump to for3 if matorder is NOT equal to c
	movl $0, -8(%ebp)					# réinitialisation de c (c=0)
	incl -4(%ebp)						# incrémentation de r
	jmp for1							# retour au début du for1
	
for3:
# for(i = 0; i < matorder; ++i)

	cmp -12(%ebp), %ebx					# condition du for (matorder - i)
	jne multiplierMatrice 				# jump to multiplierMatrice if matorder is NOT equal to i
	movl $0, -12(%ebp)					# réinitialisation de i (i=0)
	incl -8(%ebp)						# incrémentation de c
	jmp for2							# retour au début du for2
	
multiplierMatrice:
# 	elem += inmatdata1[i + r * matorder] * inmatdata2[c + i * matorder];
# outmatdata[c + r * matorder] = elem;

	# inmatdata1[i + r * matorder]
	movl -4(%ebp), %eax					# on met r dans eax pour faciliter les manipulations
	mull 20(%ebp)						# multiplication de r par matorder
	addl -12(%ebp), %eax				# i + (r * matorder)
	movl 8(%ebp), %ecx					# inmatdata1 dans %ecx
	movl (%ecx, %eax, 4), %ecx			# ecx reçoit inmatdata1[i + (r*matorder)]
	
	#inmatdata2[c + i * matorder]
	movl -12(%ebp), %eax				# on met i dans eax pour faciliter les manipulations
	mull 20(%ebp)						# multiplication de i par matorder
	addl -8(%ebp), %eax					# c + (i * matorder)
	movl 12(%ebp), %edx					# inmatdata2 dans %edx
	movl (%edx, %eax, 4), %edx			# edx reçoit inmatdata1[c + (i*matorder)]
	
	#elem += inmatdata1[i + r * matorder] * inmatdata2[c + i * matorder]
	movl %edx, %eax						# %edx est transféré dans %eax pour pouvoir faire la multiplication
	mull %ecx							# inmatdata1 * inmatdata2
	addl %eax, -16(%ebp)				# résultat de la multiplication ajouté à elem (elem += inmatdata1 * inmatdata2)
	
	#outmatdata[c + r * matorder] = elem
	movl -4(%ebp), %eax					# on met i dans eax pour faciliter les manipulations
	mull 20(%ebp) 						# multiplication de r par matorder
	addl -8(%ebp), %eax					# c + (i * matorder)
	movl 16(%ebp), %ecx					# outmatdata dans %ecx
	movl -16(%ebp), %edx				# elem dans %edx
	movl %edx, (%ecx, %eax, 4)			# elem = outmatdata[c + (r*matorder)]
	
	incl -12(%ebp)						# incrémentation de i
	jmp for3							# retour au début du for3
 
end:
	addl $16, (%esp) 			# free memory space used 
	
	leave          				/* restore ebp and esp */
	ret            				/* return to the caller */
