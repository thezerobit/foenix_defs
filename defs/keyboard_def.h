#ifndef KEYBOARD_DEF_H
#define KEYBOARD_DEF_H
/* ;; */
/* ;; Register address and constant definitions for the keyboard interface */
/* ;; */

/* Register addresses */

#define STATUS_PORT  0xAF1064
#define KBD_STATUS   0xAF1064
#define KBD_OUT_BUF  0xAF1060
#define KBD_INPT_BUF 0xAF1060
#define KBD_CMD_BUF  0xAF1064
#define KBD_DATA_BUF 0xAF1060
#define PORT_A       0xAF1060
#define PORT_B       0xAF1061

#define STATUS_PORT  0xAF1807
#define KBD_STATUS   0xAF1807
#define KBD_CMD_BUF  0xAF1807
#define KBD_OUT_BUF  0xAF1803
#define KBD_INPT_BUF 0xAF1803
#define KBD_DATA_BUF 0xAF1803
#define PORT_A       0xAF180A /* This is a Timing Register, the value is hard coded, so there is no need to use those */
#define PORT_B       0xAF180B /* This is a Timing Register, the value is hard coded, so there is no need to use those */


/* Status */
#define OUT_BUF_FULL  0x01
#define INPT_BUF_FULL 0x02
#define SYS_FLAG      0x04
#define CMD_DATA      0x08
#define KEYBD_INH     0x10
#define TRANS_TMOUT   0x20
#define RCV_TMOUT     0x40
#define PARITY_EVEN   0x80
#define INH_KEYBOARD  0x10
#define KBD_ENA       0xAE
#define KBD_DIS       0xAD

/* Keyboard Commands */
#define KB_MENU      0xF1
#define KB_ENABLE    0xF4
#define KB_MAKEBREAK 0xF7
#define KB_ECHO      0xFE
#define KB_RESET     0xFF
#define KB_LED_CMD   0xED

/* Keyboard responses */
#define KB_OK      0xAA
#define KB_ACK     0xFA
#define KB_OVERRUN 0xFF
#define KB_RESEND  0xFE
#define KB_BREAK   0xF0
#define KB_FA      0x10
#define KB_FE      0x20
#define KB_PR_LED  0x40

/* Lock Key Flags */
#define KB_SCROLL_LOCK 0x01
#define KB_NUM_LOCK    0x02
#define KB_CAPS_LOCK   0x04

/* Special key flags */
#define KB_CTRL_C  0x80 /* CTRL-C was pressed */
#define KB_CREDITS 0x60 /* Credits key was pressed */
#endif
