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
        
        mov 8(%ebp), %eax       # objet triangle dans %eax
        mov 0(%eax), %ecx       # VTable dans %ecx pour pouvoir faire l'appel de fonction
        
        push %eax               # enregistrer l'objet triangle
                                # 0(%eax)  --> VTable 
                                # 4(%eax)  --> mSides[0]
                                # 8(%eax)  --> mSides[1]
                                # 12(%eax) --> mSides[2]
        
        call *16(%ecx)          # appel de la fonction AreaCpp()
                                 
        mov 4(%eax), %ecx       # mSides[ ] dans %ecx
                                
        fld 12(%eax)            # mSides[2] sur la pile
        fdivrp                  # division st[0] = st[1]  / st[0]
                                #          st[0] =   A    / mSides[2] 
                                
        fld factor              # factor sur la pile st[0]=factor
        fmulp                   # multiplication st[0] = st[1] * st[0]
                                #                st[0] = (A / mSides[2]) * 2.0f
      
                                
        pop %eax
        leave                   /* restore ebp and esp */
        ret                     /* return to the caller */
