.globl _ZNK7CCircle7AreaAsmEv

_ZNK7CCircle7AreaAsmEv:
        push %ebp               /* save old base pointer */
        mov %esp, %ebp          /* set ebp to current esp */
        
        sub $4, %esp            # ajoute espace pour utiliser rayon
        
        fldpi                   # pi est sur la pile
        mov 8(%ebp), %eax       # cercle mis dans %eax
        fld 4(%eax)             # rayon sur la pile
        fmulp                   # multiplication pi * rayon
        fld 4(%eax)             # remettre rayon sur pile
        fmulp                   # pi*rayon*rayon
    
        leave                   /* restore ebp and esp */
        ret                     /* return to the caller */
