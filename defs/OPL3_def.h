#ifndef OPL3_DEF_H
#define OPL3_DEF_H
/* Direct Access to Right Channel */
/* R = Right */
#define OPL3_R_BASE               0xAFE600
#define OPL3_R_BASE_LL            0xE600 
#define OPL3_R_BASE_HL            0x00AF 
#define OPL3_R_TEST               0xAFE601 /* TEST */
#define OPL3_R_TIMER1             0xAFE602 /* TIMER-1 */
#define OPL3_R_TIMER2             0xAFE603 /* TIMER-2 */
#define OPL3_R_IRQ                0xAFE604
#define OPL3_R_OPL3_MODE          0xAFE605 /* Set bit 0 to 1 if you want to use in OPL3 Mode */
#define OPL3_R_CSM                0xAFE608
#define OPL3_R_AM_VID_EG_KSR_MULT 0xAFE620 /* $40..$35 (21 Registers) */
#define OPL3_R_KSL_TL             0xAFE640 /* $40..$55 (21 Registers) */
#define OPL3_R_AR_DR              0xAFE660 /* $60..$75 (21 Registers) */
#define OPL3_R_SL_RR              0xAFE680 /* $80..$95 (21 Registers) */
#define OPL3_R_FNumber            0xAFE6A0 /* $A0..$A8 */
#define OPL3_R_KON_BLOCK_FNumber  0xAFE6B0 /* $B0..$B9 */
#define OPL3_R_DPTH_RHYTM         0xAFE6BD /* $BD */
#define OPL3_R_FEEDBACK           0xAFE6C0 /* $C0..$C9 */
#define OPL3_R_WAVE_SELECT        0xAFE6E0 /* $E0..$F5 */

/* Direct Access to Left Channel */
/* L = Left */
#define OPL3_L_BASE               0xAFE700
#define OPL3_L_BASE_LL            0xE700 
#define OPL3_L_BASE_HL            0x00AF 
#define OPL3_L_TEST               0xAFE701 /* TEST */
#define OPL3_L_TIMER1             0xAFE702 /* TIMER-1 */
#define OPL3_L_TIMER2             0xAFE703 /* TIMER-2 */
#define OPL3_L_IRQ                0xAFE704
#define OPL3_L_CSM                0xAFE708
#define OPL3_L_AM_VID_EG_KSR_MULT 0xAFE720 /* $40..$35 (21 Registers) */
#define OPL3_L_KSL_TL             0xAFE740 /* $40..$55 (21 Registers) */
#define OPL3_L_AR_DR              0xAFE760 /* $60..$75 (21 Registers) */
#define OPL3_L_SL_RR              0xAFE780 /* $80..$95 (21 Registers) */
#define OPL3_L_FNumber            0xAFE7A0 /* $A0..$A8 */
#define OPL3_L_KON_BLOCK_FNumber  0xAFE7B0 /* $B0..$B9 */
#define OPL3_L_DPTH_RHYTM         0xAFE7BD /* $BD */
#define OPL3_L_FEEDBACK           0xAFE7C0 /* $C0..$C9 */
#define OPL3_L_WAVE_SELECT        0xAFE7E0 /* $E0..$F5 */

#define TREMOLO    0x80
#define VIBRATO    0x40
#define SUSTAINING 0x20
#define KSR        0x10
#define MULTIPLIER 0x0F

#define KEY_SCALE  0xC0
#define OP_LEVEL   0x3F
#define ATTACK_RT  0xF0
#define DECAY_RT   0x0F
#define SUSTAIN_RT 0xF0
#define RELEASE_RT 0x0F

#define FEEDBACK  0x0E
#define ALGORITHM 0x01

/* ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; */
/* ; All the code for the C256 Foenix support is coming from */
/* ; https://github.com/DhrBaksteen/ArduinoOPL2/ */
/* ; The OPL2 for the Arduino Project created by DhrBaksteen */
/* ; All the code in the Foenix has been translated from it for the 65C816 */
/* ; Coding for the C256 Foenix has been coded by Stefany Allaire */
/* Copy of the GIT Hub License File: */

/* MIT License */

/* Copyright (c) 2016-2018 Maarten Janssen */

/* Permission is hereby granted, free of charge, to any person obtaining a copy */
/* of this software and associated documentation files (the "Software"), to deal */
/* in the Software without restriction, including without limitation the rights */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell */
/* copies of the Software, and to permit persons to whom the Software is */
/* furnished to do so, subject to the following conditions: */

/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software. */

/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE. */
/* Macro from the C Code */
/* #define min(a, b) ((a) < (b) ? (a) : (b)) */
/* #define max(a, b) ((a) > (b) ? (a) : (b)) */

/* General OPL2 definitions. */
#define OPL2_NUM_CHANNELS 9

/* Operator definitions. */
#define OPERATOR1 0
#define OPERATOR2 1
#define MODULATOR 0
#define CARRIER   1

/* Synthesis type definitions. */
#define FREQ_MODULATION 0
#define ADDITIVE_SYNTH  1

/* Drum sounds. */
#define DRUM_BASS   0x10
#define DRUM_SNARE  0x08
#define DRUM_TOM    0x04
#define DRUM_CYMBAL 0x02
#define DRUM_HI_HAT 0x01

/* Note to frequency mapping.  -- 0 is no note and F is key-off */
#define NOTE_CS 1 
#define NOTE_D  2 
#define NOTE_DS 3 
#define NOTE_E  4 
#define NOTE_F  5 
#define NOTE_FS 6 
#define NOTE_G  7 
#define NOTE_GS 8 
#define NOTE_A  9 
#define NOTE_AS 10
#define NOTE_B  11
#define NOTE_C  12

/* const float fIntervals[8] = { */
/* 0.048, 0.095, 0.190, 0.379, 0.759, 1.517, 3.034, 6.069 */
/* }; */


/* const float blockFrequencies[8] = { */
/* 48.503,   97.006,  194.013,  388.026, */
/* 776.053, 1552.107, 3104.215, 6208.431 */
/* }; */
/* initializers for operator 1  */
/* initializers for operator 2  */



#endif
