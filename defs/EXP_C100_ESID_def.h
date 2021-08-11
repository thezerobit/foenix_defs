#ifndef EXP_C100_ESID_DEF_H
#define EXP_C100_ESID_DEF_H
#define ESID_EXP_CARD_INFO      0xAE0000 /* Read Only (32 Bytes Card ID - READ ONLY) */
#define ESID_ID_NAME_ASCII      0xAE0000 /* 15 Characters + $00 */
#define ESID_ID_VENDOR_ID_Lo    0xAE0010 /* Foenix Project Reserved ID: $F0E1 */
#define ESID_ID_VENDOR_ID_Hi    0xAE0011
#define ESID_ID_CARD_ID_Lo      0xAE0012 /* $9172 - C100-ESID */
#define ESID_ID_CARD_ID_Hi      0xAE0013
#define ESID_ID_CARD_CLASS_Lo   0xAE0014 /* TBD */
#define ESID_ID_CARD_CLASS_Hi   0xAE0015 /* TBD */
#define ESID_ID_CARD_SUBCLSS_Lo 0xAE0016 /* TBD */
#define ESID_ID_CARD_SUBCLSS_Hi 0xAE0017 /* TBD */
#define ESID_ID_CARD_UNDEFINED0 0xAE0018 /* TBD */
#define ESID_ID_CARD_UNDEFINED1 0xAE0019 /* TBD */
#define ESID_ID_CARD_HW_Rev     0xAE001A /* 00 - in Hex */
#define ESID_ID_CARD_FPGA_Rev   0xAE001B /* 00 - in Hex */
#define ESID_ID_CARD_UNDEFINED2 0xAE001C /* TBD */
#define ESID_ID_CARD_UNDEFINED3 0xAE001D /* TBD */
#define ESID_ID_CARD_CHKSUM0    0xAE001E /* Not Supported Yet */
#define ESID_ID_CARD_CHKSUM1    0xAE001F /* Not Supported Yet */
/* ESIDANSION CARD ESID-C100-ESID */
#define ESID_SIDL_V1_FREQ_LO   0xAED000 /* SID - L - Voice 1 (Write Only) - FREQ LOW */
#define ESID_SIDL_V1_FREQ_HI   0xAED001 /* SID - L - Voice 1 (Write Only) - FREQ HI */
#define ESID_SIDL_V1_PW_LO     0xAED002 /* SID - L - Voice 1 (Write Only) - PW LOW */
#define ESID_SIDL_V1_PW_HI     0xAED003 /* SID - L - Voice 1 (Write Only) - PW HI */
#define ESID_SIDL_V1_CTRL      0xAED004 /* SID - L - Voice 1 (Write Only) - CTRL REG */
#define ESID_SIDL_V1_ATCK_DECY 0xAED005 /* SID - L - Voice 1 (Write Only) - ATTACK / DECAY */
#define ESID_SIDL_V1_SSTN_RLSE 0xAED006 /* SID - L - Voice 1 (Write Only) - SUSTAIN / RELEASE */
#define ESID_SIDL_V2_FREQ_LO   0xAED007 /* SID - L - Voice 2 (Write Only) - FREQ LOW */
#define ESID_SIDL_V2_FREQ_HI   0xAED008 /* SID - L - Voice 2 (Write Only) - FREQ HI */
#define ESID_SIDL_V2_PW_LO     0xAED009 /* SID - L - Voice 2 (Write Only) - PW LOW */
#define ESID_SIDL_V2_PW_HI     0xAED00A /* SID - L - Voice 2 (Write Only) - PW HI */
#define ESID_SIDL_V2_CTRL      0xAED00B /* SID - L - Voice 2 (Write Only) - CTRL REG */
#define ESID_SIDL_V2_ATCK_DECY 0xAED00C /* SID - L - Voice 2 (Write Only) - ATTACK / DECAY */
#define ESID_SIDL_V2_SSTN_RLSE 0xAED00D /* SID - L - Voice 2 (Write Only) - SUSTAIN / RELEASE */
#define ESID_SIDL_V3_FREQ_LO   0xAED00E /* SID - L - Voice 3 (Write Only) - FREQ LOW */
#define ESID_SIDL_V3_FREQ_HI   0xAED00F /* SID - L - Voice 3 (Write Only) - FREQ HI */
#define ESID_SIDL_V3_PW_LO     0xAED010 /* SID - L - Voice 3 (Write Only) - PW LOW */
#define ESID_SIDL_V3_PW_HI     0xAED011 /* SID - L - Voice 3 (Write Only) - PW HI */
#define ESID_SIDL_V3_CTRL      0xAED012 /* SID - L - Voice 3 (Write Only) - CTRL REG */
#define ESID_SIDL_V3_ATCK_DECY 0xAED013 /* SID - L - Voice 3 (Write Only) - ATTACK / DECAY */
#define ESID_SIDL_V3_SSTN_RLSE 0xAED014 /* SID - L - Voice 3 (Write Only) - SUSTAIN / RELEASE */
#define ESID_SIDL_FC_LO        0xAED015 /* SID - L - Filter (Write Only) - FC LOW */
#define ESID_SIDL_FC_HI        0xAED016 /* SID - L - Filter (Write Only) - FC HI */
#define ESID_SIDL_RES_FILT     0xAED017 /* SID - L - Filter (Write Only) - RES / FILT */
#define ESID_SIDL_MODE_VOL     0xAED018 /* SID - L - Filter (Write Only) - MODE / VOL */
#define ESID_SIDL_POT_X        0xAED019 /* SID - L - Misc (Read Only) - POT X (C256 - NOT USED) */
#define ESID_SIDL_POT_Y        0xAED01A /* SID - L - Misc (Read Only) - POT Y (C256 - NOT USED) */
#define ESID_SIDL_OSC3_RND     0xAED01B /* SID - L - Misc (Read Only) - OSC3 / RANDOM */
#define ESID_SIDL_ENV3         0xAED01C /* SID - L - Misc (Read Only)  - ENV3 */
#define ESID_SIDL_NOT_USED0    0xAED01D /* SID - L - NOT USED */
#define ESID_SIDL_NOT_USED1    0xAED01E /* SID - L - NOT USED */
#define ESID_SIDL_NOT_USED2    0xAED01F /* SID - L - NOT USED */

/* ESIDANSION CARD ESID-C100-ESID */
#define ESID_SIDR_V1_FREQ_LO   0xAED100 /* SID - L - Voice 1 (Write Only) - FREQ LOW */
#define ESID_SIDR_V1_FREQ_HI   0xAED101 /* SID - L - Voice 1 (Write Only) - FREQ HI */
#define ESID_SIDR_V1_PW_LO     0xAED102 /* SID - L - Voice 1 (Write Only) - PW LOW */
#define ESID_SIDR_V1_PW_HI     0xAED103 /* SID - L - Voice 1 (Write Only) - PW HI */
#define ESID_SIDR_V1_CTRL      0xAED104 /* SID - L - Voice 1 (Write Only) - CTRL REG */
#define ESID_SIDR_V1_ATCK_DECY 0xAED105 /* SID - L - Voice 1 (Write Only) - ATTACK / DECAY */
#define ESID_SIDR_V1_SSTN_RLSE 0xAED106 /* SID - L - Voice 1 (Write Only) - SUSTAIN / RELEASE */
#define ESID_SIDR_V2_FREQ_LO   0xAED107 /* SID - L - Voice 2 (Write Only) - FREQ LOW */
#define ESID_SIDR_V2_FREQ_HI   0xAED108 /* SID - L - Voice 2 (Write Only) - FREQ HI */
#define ESID_SIDR_V2_PW_LO     0xAED109 /* SID - L - Voice 2 (Write Only) - PW LOW */
#define ESID_SIDR_V2_PW_HI     0xAED10A /* SID - L - Voice 2 (Write Only) - PW HI */
#define ESID_SIDR_V2_CTRL      0xAED10B /* SID - L - Voice 2 (Write Only) - CTRL REG */
#define ESID_SIDR_V2_ATCK_DECY 0xAED10C /* SID - L - Voice 2 (Write Only) - ATTACK / DECAY */
#define ESID_SIDR_V2_SSTN_RLSE 0xAED10D /* SID - L - Voice 2 (Write Only) - SUSTAIN / RELEASE */
#define ESID_SIDR_V3_FREQ_LO   0xAED10E /* SID - L - Voice 3 (Write Only) - FREQ LOW */
#define ESID_SIDR_V3_FREQ_HI   0xAED10F /* SID - L - Voice 3 (Write Only) - FREQ HI */
#define ESID_SIDR_V3_PW_LO     0xAED110 /* SID - L - Voice 3 (Write Only) - PW LOW */
#define ESID_SIDR_V3_PW_HI     0xAED111 /* SID - L - Voice 3 (Write Only) - PW HI */
#define ESID_SIDR_V3_CTRL      0xAED112 /* SID - L - Voice 3 (Write Only) - CTRL REG */
#define ESID_SIDR_V3_ATCK_DECY 0xAED113 /* SID - L - Voice 3 (Write Only) - ATTACK / DECAY */
#define ESID_SIDR_V3_SSTN_RLSE 0xAED114 /* SID - L - Voice 3 (Write Only) - SUSTAIN / RELEASE */
#define ESID_SIDR_FC_LO        0xAED115 /* SID - L - Filter (Write Only) - FC LOW */
#define ESID_SIDR_FC_HI        0xAED116 /* SID - L - Filter (Write Only) - FC HI */
#define ESID_SIDR_RES_FILT     0xAED117 /* SID - L - Filter (Write Only) - RES / FILT */
#define ESID_SIDR_MODE_VOL     0xAED118 /* SID - L - Filter (Write Only) - MODE / VOL */
#define ESID_SIDR_POT_X        0xAED119 /* SID - L - Misc (Read Only) - POT X (C256 - NOT USED) */
#define ESID_SIDR_POT_Y        0xAED11A /* SID - L - Misc (Read Only) - POT Y (C256 - NOT USED) */
#define ESID_SIDR_OSC3_RND     0xAED11B /* SID - L - Misc (Read Only) - OSC3 / RANDOM */
#define ESID_SIDR_ENV3         0xAED11C /* SID - L - Misc (Read Only)  - ENV3 */
#define ESID_SIDR_NOT_USED0    0xAED11D /* SID - L - NOT USED */
#define ESID_SIDR_NOT_USED1    0xAED11E /* SID - L - NOT USED */
#define ESID_SIDR_NOT_USED2    0xAED11F /* SID - L - NOT USED */

#define ESID_ETHERNET_REG 0xAEE000
#endif
