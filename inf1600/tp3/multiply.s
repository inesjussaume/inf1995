
.globl matrix_multiply_asm

matrix_multiply_asm:
	push %ebp      				/* save old base pointer */
	mov %esp, %ebp 				/* set ebp to current esp */
        
    subl $8, %esp				    #make room for variables (i, elem)
    pusha
    ###                             # matorder =  20(%ebp)
    movl $0, %edi			        # r = 0 --> edi
    movl $0, %esi			        # c = 0 --> esi
	movl $0, -4(%ebp)			    # i = 0 --> -4(%ebp)
	###                             # elem --> -8(%ebp)
	
		
for1:
# for(r = 0; r < matorder; ++r)

	cmp %edi, %ebx			        # condition du for (matorder - r)
	jle end						    # jump to end if matorder = r
	
for2:
# for(c = 0; c < matorder; ++c)
# 	elem = 0;

	cmp %esi, %ebx					# condition du for (matorder - c)
	movl $0, -8(%ebp)		        # elem = 0
	jne for3						# jump to for3 if matorder is NOT equal to c
	movl $0, %esi					# réinitialisation de c (c=0)
	incl %edi						# incrémentation de r
	jmp for1						# retour au début du for1
	
for3:
# for(i = 0; i < matorder; ++i)

	cmp -4(%ebp), %ebx				# condition du for (matorder - i)
	jne multiplierMatrice 			# jump to multiplierMatrice if matorder is NOT equal to i
	movl $0, -4(%ebp)				# réinitialisation de i (i=0)
	incl %esi						# incrémentation de c
	jmp for2						# retour au début du for2
	
multiplierMatrice:
# 	elem += inmatdata1[i + r * matorder] * inmatdata2[c + i * matorder];
# outmatdata[c + r * matorder] = elem;

    # ce qu'on veut faire:
    # inmatdata1 --> %ecx
    # inmatdata2 --> %ebx
    # elem += %ecx * %ebx
    # outmatdata[ %esi + %edi * 20(%ebp) ] = elem

	# inmatdata1[i + r * matorder]
	movl %edi, %eax					# on met r dans eax pour faciliter les manipulations
	mull 20(%ebp)					# multiplication de r par matorder
	addl -4(%ebp), %eax				# i + (r * matorder)
	movl 8(%ebp), %ecx				# inmatdata1 dans %ecx
	movl (%ecx, %eax, 4), %ecx		# ecx reçoit inmatdata1[i + (r*matorder)]
	
	#inmatdata2[c + i * matorder]
	#idem que pour inmatdata1 mais avec c et i plutot que i et r
	movl -4(%ebp), %eax				# on met i dans eax pour faciliter les manipulations
	mull 20(%ebp)					# multiplication de i par matorder
	addl %esi, %eax					# c + (i * matorder)
	movl 12(%ebp), %edx				# inmatdata2 dans %edx
	movl (%edx, %eax, 4), %edx		# edx reçoit inmatdata1[c + (i*matorder)]
	
	#elem += inmatdata1[i + r * matorder] * inmatdata2[c + i * matorder]
	movl %edx, %eax					# %edx est transféré dans %eax pour pouvoir faire la multiplication
	mull %ecx						# inmatdata1 * inmatdata2
	addl %eax, -8(%ebp)				# résultat de la multiplication ajouté à elem (elem += inmatdata1 * inmatdata2)
	
	#outmatdata[c + r * matorder] = elem
	movl %edi, %eax					# on met i dans eax pour faciliter les manipulations
	mull 20(%ebp) 					# multiplication de r par matorder
	addl %esi, %eax					# c + (i * matorder)
	movl 16(%ebp), %ecx				# outmatdata dans %ecx
	movl -8(%ebp), %edx				# elem dans %edx
	movl %edx, (%ecx, %eax, 4)		# elem = outmatdata[c + (r*matorder)]
	
	incl -4(%ebp)					# incrémentation de i
	jmp for3						# retour au début du for3
 
end:
	popa
	addl $8, (%esp) 			    # free memory space used 
	leave          				    /* restore ebp and esp */
	ret            				    /* return to the caller */
