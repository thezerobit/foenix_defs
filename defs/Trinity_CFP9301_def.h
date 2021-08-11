#ifndef TRINITY_CFP9301_DEF_H
#define TRINITY_CFP9301_DEF_H
/* TRINITY CHIPSET */
/* CFP9301 Memory Map */

/* Joystick Ports */
#define JOYSTICK0     0xAFE800 /* (R) Joystick 0 - J7 (next to SD Card) */
#define JOYSTICK1     0xAFE801 /* (R) Joystick 1 - J8 */
#define JOYSTICK2     0xAFE802 /* (R) Joystick 2 - J9 */
#define JOYSTICK3     0xAFE803 /* (R) Joystick 3 - J10 (Next to Buzzer) */
#define JOYSTICK_MODE 0xAFE804
#define NES_SNES_EN0  0x01    /* Enable the NES/SNES Mode on Port 0 */
#define NES_SNES_EN1  0x02    /* Enable the NES/SNES Mode on Port 1 */
#define NES_SNES_JOY  0x04    /* 0 = NES, 1 = SNES */
#define NES_SNES_DONE 0x40    /* Poll to see if the Deserializer is done */
#define NES_SNES_TRIG 0x80    /* Set to start the Serializer */

/* SNES Controller Bit Mapping: (6us Transaction Time) */
/* NES_SNES0_DAT_LO */
/* Bit 0 - "RIGHT" */
/* Bit 1 - "LEFT" */
/* Bit 2 - "DOWN" */
/* Bit 3 - "UP" */
/* Bit 4 - "START" */
/* Bit 5 - "SELECT" */
/* Bit 6 - "Y" */
/* Bit 7 - "B" */
/* SNES0_DAT_HI0 */
/* Bit 0 - "R" */
/* Bit 1 - "L" */
/* Bit 2 - "X" */
/* Bit 3 - "A" */

/* NES Controller Bit Mapping: */
/* NES_SNES0_DAT_LO */
/* Bit 0 - "RIGHT" */
/* Bit 1 - "LEFT" */
/* Bit 2 - "DOWN" */
/* Bit 3 - "UP" */
/* Bit 4 - "START" */
/* Bit 5 - "SELECT" */
/* Bit 6 - "B" */
/* Bit 7 - "A" */

/* JOYSTICK Normal Mode Port 0 */
/* Bit 0 - "UP" */
/* Bit 1 - "DOWN" */
/* Bit 2 - "LEFT" */
/* Bit 3 - "RIGHT" */
/* Bit 4 - "BUTTON" */
/* Bit 5 - 0 */
/* Bit 6 - "BUTTON1" */
/* Bit 7 - "BUTTON2" */

/* JOYSTICK Normal Mode Port 1 */
/* Bit 0 - "UP" */
/* Bit 1 - "DOWN" */
/* Bit 2 - "LEFT" */
/* Bit 3 - "RIGHT" */
/* Bit 4 - "BUTTON" */
/* Bit 5 - 0 */
/* Bit 6 - "BUTTON1" */
/* Bit 7 - "BUTTON2" */

/* JOYSTICK Normal Mode Port 2 */
/* Bit 0 - "UP" */
/* Bit 1 - "DOWN" */
/* Bit 2 - "LEFT" */
/* Bit 3 - "RIGHT" */
/* Bit 4 - "BUTTON" */
/* Bit 5 - 0 */
/* Bit 6 - 0 */
/* Bit 7 - 0 */

/* JOYSTICK Normal Mode Port 3 */
/* Bit 0 - "UP" */
/* Bit 1 - "DOWN" */
/* Bit 2 - "LEFT" */
/* Bit 3 - "RIGHT" */
/* Bit 4 - "BUTTON" */
/* Bit 5 - 0 */
/* Bit 6 - 0 */
/* Bit 7 - 0 */

/* Board identification registers */
#define REVOFPCB_C 0xAFE805 /* You should read the ASCCII for "C" */
#define REVOFPCB_4 0xAFE806 /* You should read the ASCCII for "4" */
#define REVOFPCB_A 0xAFE807 /* You should read the ASCCII for "A" */

/* NES/SNES Data Output from Deserializer Port 0 */
#define NES_SNES0_DAT_LO 0xAFE808 /* Contains the 8bits From NES and SNES */
#define SNES0_DAT_HI0    0xAFE809 /* Contains the extra 4 bit from the SNES Controller */

/* NES/SNES Data Output from Deserializer Port 1 */
#define NES_SNES1_DAT_LO 0xAFE80A
#define SNES1_DAT_HI0    0xAFE80B

/* CPLD Revsion */
#define CFP9301_REV 0xAFE80C /* Hardware Revision of the CPLD Code */

/* Dip switch Ports */
#define DIP_USER        0xAFE80D /* Dip Switch 3/4/5 can be user Defined */
#define DIP_BOOTMODE    0xAFE80E
#define BOOT_MODE0      0x01   
#define BOOT_MODE1      0x02   
#define HD_INSTALLED    0x80   
#define DIP_BOOT_IDE    0x00   
#define DIP_BOOT_SDCARD 0x01   
#define DIP_BOOT_FLOPPY 0x02   
#define DIP_BOOT_BASIC  0x03   

/* Boot modes */
/* DIP1  DIP2 */
/* ----  ---- */
/* OFF   OFF (1,1): Boot on BASIC */
/* ON    OFF (0,1): Boot from SD CARD */
/* OFF   ON  (1,0): Boot from Floppy (Illegal if MachineID doesn't specify a Floppy) */
/* ON    ON  (0,0): Boot from HDD (Illegal if Dip switch 8 is OFF (1)) */
#endif
