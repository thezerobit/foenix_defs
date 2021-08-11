#ifndef GABE_CONTROL_REGISTERS_DEF_H
#define GABE_CONTROL_REGISTERS_DEF_H
/* GABE Control Registers */

/* $AFE880..$AFE887 */

#define GABE_MSTR_CTRL     0xAFE880
#define GABE_CTRL_PWR_LED  0x01    /* Controls the LED in the Front of the case (Next to the reset button) */
#define GABE_CTRL_SDC_LED  0x02    /* Controls the LED in the Front of the Case (Next to SDCard) */
#define GABE_CTRL_STS_LED0 0x04    /* Control Status LED0 (General Use) - C256 Foenix U Only */
#define GABE_CTRL_STS_LED1 0x08    /* Control Status LED0 (General Use) - C256 Foenix U Only */
#define GABE_CTRL_BUZZER   0x10    /* Controls the Buzzer */
#define GABE_CTRL_WRM_RST  0x80    /* Warm Reset (needs to Setup other registers) */

#define GABE_LED_FLASH_CTRL  0xAFE881 /* Flashing LED Control */
#define GABE_LED0_FLASH_CTRL 0x01    /* 0- Automatic Flash 1 - Bypass Flash Timer (Use GABE_CTRL_STS_LED0 to manually control) */
#define GABE_LED1_FLASH_CTRL 0x02    /* 0- Automatic Flash 1 - Bypass Flash Timer (Use GABE_CTRL_STS_LED1 to manually control) */

#define GABE_LD0_FLASH_FRQ0 0x10 /* 1 - Bypass Flash Timer (Use GABE_CTRL_STS_LED0 to manually control) */
#define GABE_LD0_FLASH_FRQ1 0x20 /* 1 - Bypass Flash Timer (Use GABE_CTRL_STS_LED0 to manually control) */
/* 00 - 1Hz */
/* 01 - 2hz */
/* 10 - 4hz */
/* 11 - 5hz */
#define GABE_LD1_FLASH_FRQ0 0x40 /* 1 - Bypass Flash Timer (Use GABE_CTRL_STS_LED0 to manually control) */
#define GABE_LD1_FLASH_FRQ1 0x80 /* 1 - Bypass Flash Timer (Use GABE_CTRL_STS_LED0 to manually control) */



#define GABE_RST_AUTH0 0xAFE882 /* Must Contain the BYTE $AD for Reset to Activate */
#define GABE_RST_AUTH1 0xAFE883 /* Must Contain the BYTE $DE for Reset to Activate */

/* READ */
#define GABE_RNG_DAT_LO 0xAFE884 /* Low Part of 16Bit RNG Generator */
#define GABE_RNG_DAT_HI 0xAFE885 /* Hi Part of 16Bit RNG Generator */

/* WRITE */
#define GABE_RNG_SEED_LO 0xAFE884 /* Low Part of 16Bit RNG Generator */
#define GABE_RNG_SEED_HI 0xAFE885 /* Hi Part of 16Bit RNG Generator */

/* READ */
#define GABE_RNG_STAT      0xAFE886
#define GABE_RNG_LFSR_DONE 0x80    /* indicates that Output = SEED Database */

/* WRITE */
#define GABE_RNG_CTRL    0xAFE886
#define GABE_RNG_CTRL_EN 0x01    /* Enable the LFSR BLOCK_LEN */
#define GABE_RNG_CTRL_DV 0x02    /* After Setting the Seed Value, Toggle that Bit for it be registered */

#define GABE_SYS_STAT      0xAFE887
#define GABE_SYS_STAT_MID0 0x01    /* Machine ID -- LSB */
#define GABE_SYS_STAT_MID1 0x02    /* Machine ID -- */
#define GABE_SYS_STAT_MID2 0x04    /* Machine ID -- MSB */
/* Bit 2, Bit 1, Bit 0 */
/* $000: FMX */
/* $100: FMX (Future C5A) */
/* $001: U 2Meg */
/* $101: U+ 4Meg U+ */
/* $010: TBD (Reserved) */
/* $110: TBD (Reserved) */
/* $011: A2560 Dev */
/* $111: A2560 Keyboard */
#define GABE_SYS_STAT_EXP 0x10 /* if Zero, there is an Expansion Card Preset */

#define GABE_SYS_STAT_CPUA 0x40 /* Indicates the (8bit/16bit) Size of the Accumulator - Not Implemented */
#define GABE_SYS_STAT_CPUX 0x80 /* Indicates the (8bit/16bit) Size of the Accumulator - Not Implemented */

#define GABE_SUBVERSION_LO 0xAFE88A
#define GABE_SUBVERSION_HI 0xAFE88B
#define GABE_VERSION_LO    0xAFE88C
#define GABE_VERSION_HI    0xAFE88D
#define GABE_MODEL_LO      0xAFE88E
#define GABE_MODEL_HI      0xAFE88F
/* OLD Machine ID Definition - Deprecated */
/* $00 = FMX - Development Platform */
/* $01 = C256 Foenix - Dev Platform */
/* $10 = C256 Foenix - User Version (65C816) */
/* $11 = TBD */
#endif
