# 183002, Kragujevski Mihajlo

.data
v1: .space 80
v2: .space 80
index: .word 183002

.text
main:
	la $t7, index				# Adresata na indeksot se smestuva vo registar t7
	
	li $v0, 5				# Chtanje na pochetnata adresa za zbirot na dvata vektori
	syscall
	addi $s0, $v0, 0
	
	
	li $v0, 5				# Chitanje na brojot na elementi shto gi imaat vektorite, max = 20
	syscall
	addi $t0, $v0, 0
	
	mul $t6, $t6, 0
	la $t4, v1
	
	read1:					# Chitanje na elementite od prviot vektor
		beq $t6, $t0, read1_exit
		li $v0, 5
		syscall
		sw $v0, ($t4)
		add $t4, $t4, 4
		add $t6, $t6, 1
    		j read1
	read1_exit:
	mul $t6, $t6, 0
	la $t4, v2
	read2:					# Chitanje na elementite od vtoriot vektor
		beq $t6, $t0, read2_exit
		li $v0, 5
		syscall
		sw $v0, ($t4)
		add $t4, $t4, 4
		add $t6, $t6, 1
    		j read2
	read2_exit:
	mul $t6, $t6, 0
	
	jal presmetki_na_vektori
	
	lw $t7, 0($t7)				# Setiranje na poslednite 16-bits od indeksot vo s1
	lui $t8, 0
	ori $t8, 65535
	and $s1, $t7, $t8
	
	#li $v0, 1				# Test za indeksot
	#add $a0, $s1, $zero
	#syscall
	
	li $v0, 1				# Pechatenje na proizvodot na dva vektori
	add $a0, $t4, $zero
	syscall
	
	# test_sobiranje_vektori: 		# Test za zbirot na dvata vektori
	#	mul $t4, $t4, 0      		
	#	move $s4, $s0				
	#	loop2:
	#		beq $t6, $t0, bla
	#		lw $a0, ($s4)
	#		li $v0, 1
	#		syscall
	#		
	#		addi $t6, $t6, 1
	#		addi $s4, $s4, 4
	#		j loop2
	# bla:
		
	li $v0, 10
	syscall
presmetki_na_vektori:				# Procedura za smetanje na zbir i proizvod na dva vektori
	la $s3, v1
	la $s2, v2
	
	mul $t4, $t4, $zero
	move $s4, $s0
	
	loop:
		beq $t6, $t0, exit
		
		lw $t1, ($s3)
		lw $t2, ($s2)
		mult $t1, $t2
		mflo $t5
		add $t4, $t4, $t5
		add $t5, $t1, $t2
		sw $t5, 0($s4)
		
		addi $s3, $s3, 4
		addi $s2, $s2, 4
		addi $s4, $s4, 4
		addi $t6, $t6, 1
		j loop
	exit:
		mul $t6, $t6, 0
		jr $ra
