#ifndef INTERRUPT_DEF_H
#define INTERRUPT_DEF_H
/* Pending Interrupt (Read and Write Back to Clear) */
#define INT_PENDING_REG0 0x000140
#define INT_PENDING_REG1 0x000141
#define INT_PENDING_REG2 0x000142
#define INT_PENDING_REG3 0x000143 /* FMX Model */
/* Polarity Set */
#define INT_POL_REG0 0x000144
#define INT_POL_REG1 0x000145
#define INT_POL_REG2 0x000146
#define INT_POL_REG7 0x000147 /* FMX Model */
/* Edge Detection Enable */
#define INT_EDGE_REG0 0x000148
#define INT_EDGE_REG1 0x000149
#define INT_EDGE_REG2 0x00014A
#define INT_EDGE_REG3 0x00014B /* FMX Model */
/* Mask */
#define INT_MASK_REG0 0x00014C
#define INT_MASK_REG1 0x00014D
#define INT_MASK_REG2 0x00014E
#define INT_MASK_REG3 0x00014F /* FMX Model */
/* Interrupt Bit Definition */
/* Register Block 0 */
#define FNX0_INT00_SOF   0x01 /* Start of Frame @ 60FPS */
#define FNX0_INT01_SOL   0x02 /* Start of Line (Programmable) */
#define FNX0_INT02_TMR0  0x04 /* Timer 0 Interrupt */
#define FNX0_INT03_TMR1  0x08 /* Timer 1 Interrupt */
#define FNX0_INT04_TMR2  0x10 /* Timer 2 Interrupt */
#define FNX0_INT05_RTC   0x20 /* Real-Time Clock Interrupt */
#define FNX0_INT06_FDC   0x40 /* Floppy Disk Controller */
#define FNX0_INT07_MOUSE 0x80 /* Mouse Interrupt (INT12 in SuperIO IOspace) */
/* Register Block 1 */
#define FNX1_INT00_KBD    0x01 /* Keyboard Interrupt */
#define FNX1_INT01_COL0   0x02 /* VICKY_II (INT2) Sprite Collision */
#define FNX1_INT02_COL1   0x04 /* VICKY_II (INT3) Bitmap Collision */
#define FNX1_INT03_COM2   0x08 /* Serial Port 2 */
#define FNX1_INT04_COM1   0x10 /* Serial Port 1 */
#define FNX1_INT05_MPU401 0x20 /* Midi Controller Interrupt */
#define FNX1_INT06_LPT    0x40 /* Parallel Port */
#define FNX1_INT07_SDCARD 0x80 /* SD Card Controller Interrupt (CH376S) */
/* Register Block 2 */
#define FNX2_INT00_OPL3       0x01 /* OPl3 */
#define FNX2_INT01_GABE_INT0  0x02 /* GABE (INT0) - TBD */
#define FNX2_INT02_GABE_INT1  0x04 /* GABE (INT1) - TBD */
#define FNX2_INT03_VDMA       0x08 /* VICKY_II (INT4) - VDMA Interrupt */
#define FNX2_INT04_COL2       0x10 /* VICKY_II (INT5) Tile Collision */
#define FNX2_INT05_GABE_INT2  0x20 /* GABE (INT2) - TBD */
#define FNX2_INT06_EXT        0x40 /* External Expansion */
#define FNX2_INT07_SDCARD_INS 0x80 /* SDCARD Insertion */
/* Register Block 3 (FMX Expansion) */
#define FNX3_INT00_OPN2 0x01 /* OPN2 */
#define FNX3_INT01_OPM  0x02 /* OPM */
#define FNX3_INT02_IDE  0x04 /* HDD IDE INTERRUPT */
#define FNX3_INT03_TBD  0x08 /* TBD */
#define FNX3_INT04_TBD  0x10 /* TBD */
#define FNX3_INT05_TBD  0x20 /* GABE (INT2) - TBD */
#define FNX3_INT06_TBD  0x40 /* External Expansion */
#define FNX3_INT07_TBD  0x80 /* SDCARD Insertion */
#endif
