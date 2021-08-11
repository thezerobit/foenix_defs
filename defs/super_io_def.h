#ifndef SUPER_IO_DEF_H
#define SUPER_IO_DEF_H
/* ;; */
/* ;; Super IO Registers */
/* ;; */

#define SIO_KB               0xAF1060
#define PME_STS_REG          0xAF1100
#define PME_EN_REG           0xAF1102
#define PME_STS1_REG         0xAF1104
#define PME_STS2_REG         0xAF1105
#define PME_STS3_REG         0xAF1106
#define PME_STS4_REG         0xAF1107
#define PME_STS5_REG         0xAF1108
#define PME_EN1_REG          0xAF110A
#define PME_EN2_REG          0xAF110B
#define PME_EN3_REG          0xAF110C
#define PME_EN4_REG          0xAF110D
#define PME_EN5_REG          0xAF110E
#define SMI_STS1_REG         0xAF1110
#define SMI_STS2_REG         0xAF1111
#define SMI_STS3_REG         0xAF1112
#define SMI_STS4_REG         0xAF1113
#define SMI_STS5_REG         0xAF1114
#define SMI_EN1_REG          0xAF1116
#define SMI_EN2_REG          0xAF1117
#define SMI_EN3_REG          0xAF1118
#define SMI_EN4_REG          0xAF1119
#define SMI_EN5_REG          0xAF111A
#define MSC_ST_REG           0xAF111C
#define FORCE_DISK_CHANGE    0xAF111E
#define FLOPPY_DATA_RATE     0xAF111F
#define UART1_FIFO_CTRL_SHDW 0xAF1120
#define UART2_FIFO_CTRL_SHDW 0xAF1121
#define DEV_DISABLE_REG      0xAF1122
#define GP10_REG             0xAF1123
#define GP11_REG             0xAF1124
#define GP12_REG             0xAF1125
#define GP13_REG             0xAF1126
#define GP14_REG             0xAF1127
#define GP15_REG             0xAF1128
#define GP16_REG             0xAF1129
#define GP17_REG             0xAF112A
#define GP20_REG             0xAF112B
#define GP21_REG             0xAF112C
#define GP22_REG             0xAF112D
#define GP24_REG             0xAF112F
#define GP25_REG             0xAF1130
#define GP26_REG             0xAF1131
#define GP27_REG             0xAF1132
#define GP30_REG             0xAF1133
#define GP31_REG             0xAF1134
#define GP32_REG             0xAF1135
#define GP33_REG             0xAF1136
#define GP34_REG             0xAF1137
#define GP35_REG             0xAF1138
#define GP36_REG             0xAF1139
#define GP37_REG             0xAF113A
#define GP40_REG             0xAF113B
#define GP41_REG             0xAF113C
#define GP42_REG             0xAF113D
#define GP43_REG             0xAF113E
#define GP50_REG             0xAF113F
#define GP51_REG             0xAF1140
#define GP52_REG             0xAF1141
#define GP53_REG             0xAF1142
#define GP54_REG             0xAF1143
#define GP55_REG             0xAF1144
#define GP56_REG             0xAF1145
#define GP57_REG             0xAF1146
#define GP60_REG             0xAF1147
#define GP61_REG             0xAF1148
#define GP1_REG              0xAF114B
#define GP2_REG              0xAF114C
#define GP3_REG              0xAF114D
#define GP4_REG              0xAF114E
#define GP5_REG              0xAF114F
#define GP6_REG              0xAF1150
#define FAN1_REG             0xAF1156
#define FAN2_REG             0xAF1157
#define FAN_CTRL_REG         0xAF1158
#define FAN1_TACH_REG        0xAF1159
#define FAN2_TACH_REG        0xAF115A
#define FAN1_PRELOAD_REG     0xAF115B
#define FAN2_PRELOAD_REG     0xAF115C
#define LED1_REG             0xAF115D
#define LED2_REG             0xAF115E
#define KEYBOARD_SCAN_CODE   0xAF115F

#define SIO_JOY  0xAF1200
#define SIO_COM1 0xAF12F8
#define SIO_MPU  0xAF1330
#define SIO_LPT0 0xAF1378

#define SIO_FDC     0xAF13F0
#define SIO_FDC_SRA 0xAF13F0 /* Read Only - Status Register A */
#define SIO_FDC_SRB 0xAF13F1 /* Read Only - Status Register B */
#define SIO_FDC_DOR 0xAF13F2 /* Read/Write - Digital Output Register */
#define SIO_FDC_TSR 0xAF13F3 /* Read/Write - Tape Drive Status */
#define SIO_FDC_MSR 0xAF13F4 /* Read - Main Status Register */
#define SIO_FDC_DSR 0xAF13F4 /* Write - Data Select Register */
#define SIO_FDC_DTA 0xAF13F5 /* Read/Write - Data - FIFO */
#define SIO_FDC_RSV 0xAF13F6 /* Reserved */
#define SIO_FDC_DIR 0xAF13F7 /* Read - Digital Input Register */
#define SIO_FDC_CCR 0xAF13F8 /* Write - Configuration Control Register */

#define SIO_COM0 0xAF13F8
#endif
