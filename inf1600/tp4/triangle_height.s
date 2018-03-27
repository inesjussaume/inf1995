# float CTriangle::HeightCpp() const {
#	float A = AreaCpp();
#	return 2.0f*A/mSides[2];
#}

.data
        factor: .float 2.0 
.text

.globl	_ZNK9CTriangle9HeightAsmEv


_ZNK9CTriangle9HeightAsmEv:
        push %ebp               /* save old base pointer */
        mov %esp, %ebp          /* set ebp to current esp */
        /*
        mov 8(%ebp), %eax       # objet triangle dans %eax
        mov 0(%eax), %ecx       # VTable dans %ecx pour pouvoir faire l'appel de fonction
        
        #push %eax
        
        call *16(%ebx)          # appel de la fonction ArecCpp()
        fld factor              # factor sur la pile st[0]=factor
        fmulp                   # multiplication st[0] = st[1] * st[0]
                                #                st[0] = 2.0f  *  A
        fld 12(%eax)            # mSides[2] sur la pile
        fdivrp                  # division st[0] = st[1]  / st[0]
                                #          st[0] = 2.0f*a / mSides[2]
        
      */
        leave                   /* restore ebp and esp */
        ret                     /* return to the caller */
