.data
        factor: .float 2.0 /* use this to multiply by two */

.text
.globl _ZNK7CCircle12PerimeterAsmEv

_ZNK7CCircle12PerimeterAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */

        /* Write your solution here */
        
        flds factor			#factor sur la pile
        fldpi				#pi sur la pile
        fmulp				#st[0] = st[1] = pi x 2.00
        mov 8(%ebp),%eax	#Objet cercle dans %eax
        fld 4(%eax)			#attributs de Cercle sur la pile
        fmulp				#st[0] = st[1] = pi x 2.00 x mRadius
        leave         		/* restore ebp and esp */
        ret            		/* return to the caller */
