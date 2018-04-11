#float CTriangle::AreaCpp() const {
#   /* Heron's Formula for the area of a triangle */
#   float p = PerimeterCpp() / 2.0f;
#   return ::sqrt(p*(p-mSides[0])*(p-mSides[1])*(p-mSides[2]));
#}

.data
		factor: .float 2.0
		a: .float 0
		b: .float 0
		c: .float 0
		
		

.globl _ZNK9CTriangle7AreaAsmEv

_ZNK9CTriangle7AreaAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        /* Write your solution here */
        
        mov 8(%ebp), %eax       # objet triangle dans %eax
        mov 0(%eax), %ecx       # VTable dans %ecx pour pouvoir faire l'appel de fonction
        
        push %eax               # enregistrer l'objet triangle
                                # 0(%eax)  --> VTable 
                                # 4(%eax)  --> mSides[0]
                                # 8(%eax)  --> mSides[1]
                                # 12(%eax) --> mSides[2]
                                
        call *8(%ecx)		    # Appele la fonction PerimeterCpp()
                                # PerimeterCpp() --> st[0]
        
       
        
        fld factor			    # st[0] = 2.0f et st[1] = PerimeterCpp() 
        
                
        fdivrp 				    # st[0] = st[1] = PerimeterCpp() /2.0f
        fstp c      	        # p --> st[0] (st[0] est vide et st[1] = PerimeterCpp() /2.0f), c = p
        
        
        #### a = p-mSides[0]
        
        fld c                   # st[0] = p
        fld 4(%eax)             # on ajoute mSides[0] sur la pile ==> st[0] = mSides[0]
        fsubrp                   # soustraction st[1] - st[0]
                                # st[0] = p - mSides[0]
        fstp a                  # Retire l’élément st[0] (p - mSides[0]) pour le mettre en mémoire principale à l’adresse p. st[1] devient st[0]
                                # a = p - mSides[0]
        
        
        #### b = p-mSides[1]
        
        fld 8(%eax)             # on ajoute mSides[1] sur la pile ==> st[0] = mSides[1]
        fld c                   # st[0] = c
        fsubp                   # soustraction st[0] - st[1]
                                # st[0] = p - mSides[1]
        fstp b                  # Retire l’élément st[0] (p - mSides[1]) pour le mettre en mémoire principale à l’adresse p. st[1] devient st[0]
                                # b = p - mSides[1]
                                
                                
        #### st[0] = p-mSides[2]                        
                                
        fld 12(%eax)            # on ajoute mSides[2] sur la pile ==> st[0] = mSides[2]
        fld c                   # st[0] = c
        fsubp                   # soustraction st[0] - st[1]
                                # st[0] = p - mSides[2]
                                
                                
        fld a                   # (p-mSides[0]) --> st[0]
                                # st[0] = a, st[1] = (p-mSides[2])
        fmulp                   # st[0] = a * (p-mSides[2])
        fld b                   # st[0] = b
        fmulp                   # st[0] = a * b * (p-mSides[2])
        fld c                   # st[0] = c
        fmulp                   # st[0] = st[0] = p* a * b * (p-mSides[2])
        fsqrt                   # st[0] = sqrt(p * a * b * (p-mSides[2]))
                                
                                
        
        
        
        leave         		/* restore ebp and esp */
        ret            		/* return to the caller */
