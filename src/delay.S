

  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Some parts are original code written 2023 by Erik Smit and Hugo Larsson Wilhelmsson
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.global hexasc
.global skip
.global delay
.global while
.global loop
.global delay_finish
.global time2string

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #


hexasc:
    li $t1, 0x0F        # load 0000 1111 or 15
    and $a0, $a0, $t1    # only look at 4 lsb and store those in $t2
    addi $v0, $a0, 48    # increase by offset 48

    
    li $t0, 0x3a        # compare value
    bgt $v0, $t0, skip    # comparitive branch, if value is greater than 0x3a, skip
    nop
    
    
    andi $v0, $v0, 127
    jr $ra
    nop

skip:
    addi $v0, $v0, 0x37    # increase value by 7 to skip unwanted chars
    
    andi $v0, $v0, 127
    jr $ra
    nop
    
delay:
    PUSH $t0
    PUSH $t1
    PUSH $t2
    PUSH $t3

while:
    # while statement
    li $t0, 1
    ble $a0, $t0, delay_finish     # if $a0 is less than 1
    nop
    
    # two complement
    not $t1, $a0        # invert and store in $t1
    addi $t1,$t1, 1
    move $a0, $t1        # copy back to $a0
    
    li $t2, 1         # variable i
    li $t3, 4750     # constant
    
    not $a0, $a0        # invert back
    nop
    
    
loop:
    bgt $t2, $t3, while
    nop
    addi $t2, $t2, 1
    j loop        # repeat
    nop

    
delay_finish:
    POP $t3
    POP $t2
    POP $t1
    POP $t0
    
    jr $ra
     
    
time2string:

	# Save registers to stack
	
	PUSH $ra
	PUSH $t3
	PUSH $t4
	PUSH $t5
	PUSH $t6
	PUSH $t7
	PUSH $t8
	PUSH $t9
	
	PUSH $a0		# push memory address to stack
	
	
	
	li $t3, 15		# mask 
	li $s0, 9

	
	# retrieve digits
	
	and $t4, $a1, $t3	# get ones of seconds
	srl $a1, $a1, 4	  	# shift right 4
	
	
	and $t5, $a1, $t3	# get tens of seconds
	srl $a1, $a1, 4		# shift right 4
	
	and $t7, $a1, $t3	# get ones of minutes
	srl $a1, $a1, 4		# shift right 4
	
	and $t8, $a1, $t3	# get tens of minutes
	
	# store tens of minutes
	
	move $a0, $t8		# copy value
	jal hexasc
	nop
	POP $a0			# pop memory address from stack
	sb $v0, 0($a0)		# store
	
	# store ones of minutes
	
	PUSH $a0
	move $a0, $t7	
	jal hexasc
	nop
	POP $a0			
	sb $v0, 1($a0)		
	
	li $t6, 0x3a		# colon
	sb $t6, 2($a0)
	
	# store tens of seconds
	
	PUSH $a0
	move $a0, $t5		
	jal hexasc
	nop
	POP $a0			
	sb $v0, 3($a0)		
	
	# store ones of seconds
	
	PUSH $a0		
	move $a0, $t4				
	jal hexasc
	nop
	POP $a0		
	sb $v0, 4($a0)		
	
	li $t9, 0x00		# null byte (interprets null byte as end of string)
	sb $t9, 5($a0)
	
	# move on to time2string_finish 
	j time2string_fin
    nop
	
time2string_fin:	

	# Restore registers from stack
	
	POP $t9
	POP $t8
	POP $t7
	POP $t6
	POP $t5
	POP $t4
	POP $t3
	POP $ra
	
	jr $ra
	nop