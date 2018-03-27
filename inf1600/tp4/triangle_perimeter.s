.globl _ZNK9CTriangle12PerimeterAsmEv

_ZNK9CTriangle12PerimeterAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        /* Write your solution here */ 
        mov 8(%ebp),%eax		#objet dans eax
        mov 4(%eax),%ebx 		#mSides[3] dans ebx
        mov $1,%ebx				#1 dans #ebx
        fld (%eax,%ebx,4)		#met sur la pile mSide[0]
        inc %ebx				#%ebx++
        fld (%eax,%ebx,4)		#met sur la pile mSide[1]
        faddp 					#mSides[0] + mSides[1] = st[0] = st[1]
        inc %ebx				#%ebx++
        fld (%eax,%ebx,4)		#met sur la pile mSide[2]
        faddp
       
        leave          			/* restore ebp and esp */
        ret            			/* return to the caller */
