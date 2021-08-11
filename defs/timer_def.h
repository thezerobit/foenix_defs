#ifndef TIMER_DEF_H
#define TIMER_DEF_H
/* Pending Interrupt (Read and Write Back to Clear) */
/* TIMER0 */
#define TIMER0_CTRL_REG 0x000160 /* (Write - Control, Read Status) */
/* Control Register Definitions */
#define TMR0_EN    0x01
#define TMR0_SCLR  0x02
#define TMR0_SLOAD 0x04 /* Use SLOAD is */
#define TMR0_UPDWN 0x08

#define TIMER0_CHARGE_L 0x000161 /* Use if you want to Precharge and countdown */
#define TIMER0_CHARGE_M 0x000162
#define TIMER0_CHARGE_H 0x000163
/* Compare Block */
#define TIMER0_CMP_REG  0x000164
#define TMR0_CMP_RECLR  0x01    /* set to one for it to cycle when Counting up */
#define TMR0_CMP_RELOAD 0x02    /* Set to one for it to reload when Counting Down */

#define TIMER0_CMP_L 0x000165 /* Load this Value for Countup */
#define TIMER0_CMP_M 0x000166
#define TIMER0_CMP_H 0x000167
/* Pending Interrupt (Read and Write Back to Clear) */
/* TIMER1 */
#define TIMER1_CTRL_REG 0x000168
#define TMR1_EN         0x01   
#define TMR1_SCLR       0x02   
#define TMR1_SLOAD      0x04   
#define TMR1_UPDWN      0x08    /* 1 = Up, 0 = Down */
#define TIMER1_CHARGE_L 0x000169 /* Use if you want to Precharge and countdown */
#define TIMER1_CHARGE_M 0x00016A
#define TIMER1_CHARGE_H 0x00016B
/* Compare Block */
#define TIMER1_CMP_REG  0x00016C
#define TMR1_CMP_RECLR  0x01    /* set to one for it to cycle when Counting up */
#define TMR1_CMP_RELOAD 0x02    /* Set to one for it to reload when Counting Down */
#define TIMER1_CMP_L    0x00016D
#define TIMER1_CMP_M    0x00016E
#define TIMER1_CMP_H    0x00016F
#endif
