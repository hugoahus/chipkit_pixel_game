  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  # 
.data
.global delay
.global hexasc
.global time2string
.global enable_interrupt

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
.text

mytime:	.word 0x5957
timstr:	.ascii
	
delay:
	li	$a2,2000000   # a2 = ms = 10
	li	$t0,4711      # t0 = 4711
	loop: 	
		blt	$a2, $0, finish 
		nop
		addi	$a2, $a2,-1    # ms = ms �C 1;
		addi	$t3, $t3, 0    # t3 = i = 0
		looptwo:
			addi	$t3, $t3, 1    # i = i + 1
			ble	$t3, $t0, looptwo
			nop
		j loop
		nop


finish:
	jr 	$ra
	nop

hexasc:
	sll 	$a0, $a0, 28
	srl 	$a0, $a0, 28	# we only need the last 4 bits, shifting left and shifting right can remove all other bits
	
	addi	$t0, $0, 0x09    
	ble	$a0, $t0,single	# if the number is less than 10 
	nop                    # delay slot filler (just in case)
	
	addi	$v0, $v0, 0x37 # if the number is more than 9, add 7 because there are 7 characters between A and 9
 
single:
	add	$v0, $a0, 0x30
	jr	$ra
	nop                    # delay slot filler (just in case)

time2string:
	move    $t0, $a1   # get time string, t0 from a1
	move    $t7, $a0
	sll 	$t0, $t0, 16   # we only need the last 16 bits, shifting left and shifting right can remove all other bits
	srl 	$t0, $t0, 16   # time info(equivalent to andi $t0, $a1, 0xffff) 
	
	andi    $t1, $t0, 0x000f  # make t1 the last 4 bits, which is the second's 2nd digit
	andi    $t2, $t0, 0x00f0  # make t2 to represent the second's 1st digit
	andi    $t3, $t0, 0x0f00  # make t3 to represent the minute's 2nd digit
	andi    $t4, $t0, 0xf000  # make t4 to represent the minute's 1st digit
	
	srl     $t2, $t2, 4   # make the useful time infomation in the last 4 bits 
	srl     $t3, $t3, 8
	srl     $t4, $t4, 12
	PUSH	$ra
	move 	$a0, $t4
	jal 	hexasc
	nop
	POP	$ra
	sb 	$v0, 0($t7)

	PUSH	$ra
	move 	$a0, $t3
	jal 	hexasc
	nop
	POP	$ra
	sb 	$v0, 1($t7)	
	
	addi 	$t5, $0, 0x3a   # add the colon, which is 0x3a in ACSII
	sb	$t5, 2($t7)
	
	PUSH    $ra
	move 	$a0, $t2
	jal 	hexasc
	nop
	POP     $ra
	sb	$v0, 3($t7)
	
	PUSH	$ra
	move 	$a0, $t1
	jal 	hexasc
	nop
	POP	$ra
	sb 	$v0, 4($t7)
		
	addi 	$t6, $0, 0x00    # add the NULL byte, which is 0x00 in ACSII
	sb	$t6, 5($t7)
	
	jr	$ra
	nop
	
# ei enables the interrupt register
 enable_interrupt:
 	ei
 	jr $ra
 	nop