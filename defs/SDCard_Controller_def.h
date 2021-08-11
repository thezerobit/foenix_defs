#ifndef SDCARD_CONTROLLER_DEF_H
#define SDCARD_CONTROLLER_DEF_H
/* GABE Internal SDCard Controller */

#define SDC_VERSION_REG     0xAFEA00 /* Ought to read 12 */
#define SDC_CONTROL_REG     0xAFEA01 /* Bit0 1 = Reset core logic, and registers. Self clearing */
#define SDC_TRANS_TYPE_REG  0xAFEA02 /* Bit[1:0] */
#define SDC_TRANS_DIRECT    0x00    /* 00 = Direct Access */
#define SDC_TRANS_INIT_SD   0x01    /* 01 = Init SD */
#define SDC_TRANS_READ_BLK  0x02    /* 10 = RW_READ_BLOCK (512 Bytes) */
#define SDC_TRANS_WRITE_BLK 0x03    /* 11 = RW_WRITE_SD_BLOCK */

#define SDC_TRANS_CONTROL_REG 0xAFEA03
#define SDC_TRANS_START       0x01   

#define SDC_TRANS_STATUS_REG 0xAFEA04
#define SDC_TRANS_BUSY       0x01    /* 1= Transaction Busy */

#define SDC_TRANS_ERROR_REG     0xAFEA05
#define SDC_TRANS_INIT_NO_ERR   0x00    /* Init Error Report [1:0] */
#define SDC_TRANS_INIT_CMD0_ERR 0x01   
#define SDC_TRANS_INIT_CMD1_ERR 0x02   

#define SDC_TRANS_RD_NO_ERR    0x00 /* Read Error Report [3:2] */
#define SDC_TRANS_RD_CMD_ERR   0x04
#define SDC_TRANS_RD_TOKEN_ERR 0x08

#define SDC_TRANS_WR_NO_ERR   0x00 /* Write Report Error  [5:4] */
#define SDC_TRANS_WR_CMD_ERR  0x10
#define SDC_TRANS_WR_DATA_ERR 0x20
#define SDC_TRANS_WR_BUSY_ERR 0x30

#define SDC_DIRECT_ACCESS_REG 0xAFEA06 /* SPI Direct Read and Write - Set DATA before initiating direct Access Transaction */

#define SDC_SD_ADDR_7_0_REG   0xAFEA07 /* Set the ADDR before a block read or block write */
#define SDC_SD_ADDR_15_8_REG  0xAFEA08 /* Addr0 [8:0] Always should be 0, since each block is 512Bytes */
#define SDC_SD_ADDR_23_16_REG 0xAFEA09
#define SDC_SD_ADDR_31_24_REG 0xAFEA0A

#define SDC_SPI_CLK_DEL_REG 0xAFEA0B
/* ... */
#define SDC_RX_FIFO_DATA_REG    0xAFEA10 /* Data from the Block Read */
#define SDC_RX_FIFO_DATA_CNT_HI 0xAFEA12 /* How many Bytes in the FIFO HI */
#define SDC_RX_FIFO_DATA_CNT_LO 0xAFEA13 /* How many Bytes in the FIFO LO */
#define SDC_RX_FIFO_CTRL_REG    0xAFEA14 /* Bit0  Force Empty - Set to 1 to clear FIFO, self clearing (the bit) */
/* ... */
#define SDC_TX_FIFO_DATA_REG 0xAFEA20 /* Write Data Block here */
#define SDC_TX_FIFO_CTRL_REG 0xAFEA24 /* Bit0  Force Empty - Set to 1 to clear FIFO, self clearing (the bit) */
#endif
