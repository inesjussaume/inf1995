.globl matrix_transpose_asm

matrix_transpose_asm:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        /* Write your solution here */
        mov $0,%eax #eax = r
        mov $0,%ecx #ebx= c
        
           /* return to the caller */
for1: #r plus petit que matorder
    
    cmp %eax,16(%ebp) #16(ebp) - eax -> matorder - r
    jna end #si = 0, end. sinon for2
    
    
for2:

    cmp %ecx,16(%ebp) #
    jna egale #si ok, fait l'affectation
    jmp for1
    
egale:
	mul %ebx #eax= eax * ebx
    add %ecx,%eax #eax eax = c + r * matorder
    
    mov 8(%ebp), %ebx #int* inmatdata dans edx
    
    mov (%ebx,%eax,4),%edx #edx = inmatdata[c + r * matorder] 
    
    mov 12(%ebp),%ebx #ebx = outmatdata

    mov %edx,(%ebx,%eax,4) #(%ebx,%eax,4) = dex = inmatdata[c + r * matorder] 
    
    inc %ecx
    
    jmp for2

fin:        
        leave          /* restore ebp and esp */
        ret     
