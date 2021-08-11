#ifndef EXP_C200_EVID_DEF_H
#define EXP_C200_EVID_DEF_H
#define EVID_EXP_CARD_INFO      0xAE0000 /* Read Only (32 Bytes Card ID - READ ONLY) */
#define EVID_ID_NAME_ASCII      0xAE0000 /* 15 Characters + $00 */
#define EVID_ID_VENDOR_ID_Lo    0xAE0010 /* Foenix Project Reserved ID: $F0E1 */
#define EVID_ID_VENDOR_ID_Hi    0xAE0011
#define EVID_ID_CARD_ID_Lo      0xAE0012 /* $9236 - C200-EVID */
#define EVID_ID_CARD_ID_Hi      0xAE0013
#define EVID_ID_CARD_CLASS_Lo   0xAE0014 /* TBD */
#define EVID_ID_CARD_CLASS_Hi   0xAE0015 /* TBD */
#define EVID_ID_CARD_SUBCLSS_Lo 0xAE0016 /* TBD */
#define EVID_ID_CARD_SUBCLSS_Hi 0xAE0017 /* TBD */
#define EVID_ID_CARD_UNDEFINED0 0xAE0018 /* TBD */
#define EVID_ID_CARD_UNDEFINED1 0xAE0019 /* TBD */
#define EVID_ID_CARD_HW_Rev     0xAE001A /* 00 - in Hex */
#define EVID_ID_CARD_FPGA_Rev   0xAE001B /* 00 - in Hex */
#define EVID_ID_CARD_UNDEFINED2 0xAE001C /* TBD */
#define EVID_ID_CARD_UNDEFINED3 0xAE001D /* TBD */
#define EVID_ID_CARD_CHKSUM0    0xAE001E /* Not Supported Yet */
#define EVID_ID_CARD_CHKSUM1    0xAE001F /* Not Supported Yet */

/* EVID_MOUSEPTR_MEM       = $AE0400    ; Not Instantiated */
/* EVID_MOUSEPTR_REG       = $AE0600    ; Not Instantiated */

#define EVID_FONT_MEM 0xAE1000
#define EVID_FG_LUT   0xAE1B00
#define EVID_BG_LUT   0xAE1B40
/* Internal EVID Registers and Internal Memory Locations (LUTs) */
#define EVID_MSTR_CTRL_REG_L   0xAE1E00
#define EVID_Ctrl_Text_Mode_En 0x01    /* Enable the Text Mode */

#define EVID_MSTR_CTRL_REG_H   0xAE1E01
#define EVID_800x600ModeEnable 0x01    /* 0 - 640x480 (Clock @ 25.175Mhz), 1 - 800x600 (Clock @ 40Mhz) */

#define EVID_Border_Ctrl_Enable 0x01   
#define EVID_BORDER_CTRL_REG    0xAE1E04 /* Bit[0] - Enable (1 by default)  Bit[4..6]: X Scroll Offset ( Will scroll Left) (Acceptable Value: 0..7) */
#define EVID_BORDER_COLOR_B     0xAE1E05
#define EVID_BORDER_COLOR_G     0xAE1E06
#define EVID_BORDER_COLOR_R     0xAE1E07
#define EVID_BORDER_X_SIZE      0xAE1E08 /* X-  Values: 0 - 32 (Default: 32) */
#define EVID_BORDER_Y_SIZE      0xAE1E09 /* Y- Values 0 -32 (Default: 32) */

#define EVID_TXT_CURSOR_CTRL_REG 0xAE1E10 /* [0]  Enable Text Mode */
#define EVID_Cursor_Enable       0x01   
#define EVID_Cursor_Flash_Rate0  0x02    /* 00 - 1/Sec, 01 - 2/Sec, 10 - 4/Sec, 11 - 5/Sec */
#define EVID_Cursor_Flash_Rate1  0x04   
#define EVID_Cursor_FONT_Page0   0x08    /* Pick Font Page 0 or Font Page 1 */
#define EVID_Cursor_FONT_Page1   0x10    /* Pick Font Page 0 or Font Page 1 */
#define EVID_TXT_CURSOR_CHAR_REG 0xAE1E12

#define EVID_TXT_CURSOR_COLR_REG 0xAE1E13
#define EVID_TXT_CURSOR_X_REG_L  0xAE1E14
#define EVID_TXT_CURSOR_X_REG_H  0xAE1E15
#define EVID_TXT_CURSOR_Y_REG_L  0xAE1E16
#define EVID_TXT_CURSOR_Y_REG_H  0xAE1E17
/* When you Read the Register */
#define EVID_INFO_CHIP_NUM_L 0xAE1E1C
#define EVID_INFO_CHIP_NUM_H 0xAE1E1D
#define EVID_INFO_CHIP_VER_L 0xAE1E1E
#define EVID_INFO_CHIP_VER_H 0xAE1E1F

#define EVID_TEXT_MEM     0xAE2000
#define EVID_COLOR_MEM    0xAE4000
#define EVID_ETHERNET_REG 0xAEE000

#endif
