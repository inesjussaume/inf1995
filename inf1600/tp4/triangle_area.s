.globl _ZNK9CTriangle7AreaAsmEv

_ZNK9CTriangle7AreaAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        /* Write your solution here */
        mov 8(%ebp), %eax	#Triangle dans eax
        mov (%eax), %ebx	#VTable de Triangle dans ebx
        call *8(%ebx)		#Appele la fonction PerimeterCpp()
        
        fld 2			#st[0] = 2.0f et st[1] = PerimeterCpp() 
        
        fdivrp 				#st[0] = st[1] = PerimeterCpp() /2.0f
        
        #fstp %ecx			#ecx = p
        
        
        
        
        
        
        leave         		/* restore ebp and esp */
        ret            		/* return to the caller */
