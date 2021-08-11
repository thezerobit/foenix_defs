#ifndef IO_DEF_H
#define IO_DEF_H
/* ;; */
/* ;; I/O addresses and definitions */
/* ;; */

/* I/O channel IDs (used for PUTC, GETC*, etc.) */
#define CHAN_CONSOLE 0 /* ID for screen and keyboard access */
#define CHAN_COM1    1 /* ID for serial access on COM1 (external port) */
#define CHAN_COM2    2 /* ID for serial access on COM2 (internal port) */
#define CHAN_LPT     3 /* ID for parallel port */
#define CHAN_EVID    4 /* ID for the second video port */

/* SD Card CH376S Port */
#define SDCARD_DATA 0xAFE810 /* (R/W) SDCARD (CH376S) Data PORT_A (A0 = 0) */
#define SDCARD_CMD  0xAFE811 /* (R/W) SDCARD (CH376S) CMD/STATUS Port (A0 = 1) */

/* SD Card Card Presence / Write Protect Status Reg */
#define SDCARD_STAT   0xAFE812 /* (R) SDCARD (Bit[0] = CD, Bit[1] = WP) */
#define SDC_DETECTED  0x01    /* SD card has been detected (0 = card present, 1 = no card present) */
#define SDC_WRITEPROT 0x02    /* SD card is write protected (0 = card is writeable, 1 = card is write protected or missing) */

/* Audio WM8776 CODEC Control Interface (Write Only) */
#define CODEC_DATA_LO 0xAFE900 /* (W) LSB of Add/Data Reg to Control CODEC See WM8776 Spec */
#define CODEC_DATA_HI 0xAFE901 /* (W) MSB od Add/Data Reg to Control CODEC See WM8776 Spec */
#define CODEC_WR_CTRL 0xAFE902 /* (W) Bit[0] = 1 -> Start Writing the CODEC Control Register */
#endif
