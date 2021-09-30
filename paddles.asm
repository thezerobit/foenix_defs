; Set 8-bit accumulator
setas   .macro
        SEP #$20        ; set A short 
        LONGA OFF
        .endm
                
; Set 16-bit accumulator
setal   .macro
        REP #$20        ; set A long 
        LONGA ON
        .endm

		XDEF	~~WHICH_PADDLE

~~WHICH_PADDLE:
		BYTE

		XDEF	~~POLL_PADDLE

~~POLL_PADDLE:
		.setas
		LDA |~~WHICH_PADDLE
		TAX
		PHB		; save the data bank register

		LDA #$AF ; set DBR to $AF
		PHA
		PLB

		TXA
PB0		BIT $1200
		BNE PB0

		PLB		; restore the data bank register
		.setal
		RTL

