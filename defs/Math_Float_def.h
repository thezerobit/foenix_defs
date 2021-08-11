#ifndef MATH_FLOAT_DEF_H
#define MATH_FLOAT_DEF_H


/* $AFE200..$AFE20F <- Registers */
/* Read/Write */
#define FP_MATH_CTRL0            0xAFE200
#define FP_MATH_CTRL0_INPUT0_MUX 0x01    /* 0: UserInput0 - 1: Converter Fixed (20.12) to FP */
#define FP_MATH_CTRL0_INPUT1_MUX 0x02    /* 0: UserInput1 - 1: Converter Fixed (20.12) to FP */

#define FP_MATH_CTRL0_ADD_SUB      0x08    /* 0: Substraction - 1: Addition */
#define FP_MATH_CTRL0_ADD_IN0_MUX0 0x10    /* 00: Input Mux0, 01: Input Mux1 */
#define FP_MATH_CTRL0_ADD_IN0_MUX1 0x20    /* 10: Mult Out, 11: Div Out */
#define FP_MATH_CTRL0_ADD_IN1_MUX0 0x40    /* 00: Input Mux0, 01: Input Mux1 */
#define FP_MATH_CTRL0_ADD_IN1_MUX1 0x80    /* 10: Mult Out, 11: Div Out */
#define FP_MATH_CTRL1              0xAFE201
#define FP_MATH_CTRL1_OUTPUT_MUX0  0x01    /* 00: Mult Output, 01: Div Output */
#define FP_MATH_CTRL1_OUTPUT_MUX1  0x02    /* 10: Add/Substract Output, 11: '1' */

#define FP_MATH_CTRL2 0xAFE202 /* Not Used - Reserved */
#define FP_MATH_CTRL3 0xAFE203 /* Not Used - Reserved */
/* Read Only */
#define FP_MATH_MULT_STAT     0xAFE204
#define FP_MULT_STAT_NAN      0x01    /* (NAN) Not a Number Status */
#define FP_MULT_STAT_OVF      0x02    /* Overflow */
#define FP_MULT_STAT_UDF      0x04    /* Underflow */
#define FP_MULT_STAT_ZERO     0x08    /* Zero */
#define FP_MATH_DIV_STAT      0xAFE205
#define FP_DIV_STAT_NAN       0x01    /* Not a number Status */
#define FP_DIV_STAT_OVF       0x02    /* Overflow */
#define FP_DIV_STAT_UDF       0x04    /* Underflow */
#define FP_DIV_STAT_ZERO      0x08    /* Zero */
#define FP_DIV_STAT_DIVBYZERO 0x10    /* Division by Zero */
#define FP_MATH_ADD_STAT      0xAFE206
#define FP_ADD_STAT_NAN       0x01    /* Not a number Status */
#define FP_ADD_STAT_OVF       0x02    /* Overflow */
#define FP_ADD_STAT_UDF       0x04    /* Underflow */
#define FP_ADD_STAT_ZERO      0x08    /* Zero */
#define FP_MATH_CONV_STAT     0xAFE207
#define FP_CONV_STAT_NAN      0x01    /* Not a number Status */
#define FP_CONV_STAT_OVF      0x02    /* Overflow */
#define FP_CONV_STAT_UDF      0x04    /* Underflow */
/* Write Input0 (either FP or Fixed (20.12)) - See MUX Setting */
#define FP_MATH_INPUT0_LL 0xAFE208
#define FP_MATH_INPUT0_LH 0xAFE209
#define FP_MATH_INPUT0_HL 0xAFE20A
#define FP_MATH_INPUT0_HH 0xAFE20B
/* Write Input1 (either FP or Fixed (20.12)) - See MUX Setting */
#define FP_MATH_INPUT1_LL 0xAFE20C
#define FP_MATH_INPUT1_LH 0xAFE20D
#define FP_MATH_INPUT1_HL 0xAFE20E
#define FP_MATH_INPUT1_HH 0xAFE20F
/* Read Output */
#define FP_MATH_OUTPUT_FP_LL 0xAFE208
#define FP_MATH_OUTPUT_FP_LH 0xAFE209
#define FP_MATH_OUTPUT_FP_HL 0xAFE20A
#define FP_MATH_OUTPUT_FP_HH 0xAFE20B
/* Read FIXED Output (20.12) Format */
#define FP_MATH_OUTPUT_FIXED_LL 0xAFE20C
#define FP_MATH_OUTPUT_FIXED_LH 0xAFE20D
#define FP_MATH_OUTPUT_FIXED_HL 0xAFE20E
#define FP_MATH_OUTPUT_FIXED_HH 0xAFE20F

/* DATAA[]  DATAB[]   SIGN BIT  RESULT[]  Overflow Underflow Zero NaN */
/* Normal   Normal    0         Zero      0       0           1   0 */
/* Normal   Normal    0/1       Normal    0       0           0   0 */
/* Normal   Normal    0/1       Denormal  0       1           1   0 */
/* Normal   Normal    0/1       Infinity  1       0           0   0 */
/* Normal   Denormal  0/1       Normal    0       0           0   0 */
/* Normal   Zero      0/1       Normal    0       0           0   0 */
/* Normal   Infinity  0/1       Infinity  1       0           0   0 */
/* Normal   NaN       X         NaN       0       0           0   1 */
/* Denormal Normal    0/1       Normal    0       0           0   0 */
/* Denormal Denormal  0/1       Normal    0       0           0   0 */
/* Denormal Zero      0/1       Zero      0       0           1   0 */
/* Denormal Infinity  0/1       Infinity  1       0           0   0 */
/* Denormal NaN       X         NaN       0       0           0   1 */
/* Zero     Normal    0/1       Normal    0       0           0   0 */
/* Zero     Denormal  0/1       Zero      0       0           1   0 */
/* Zero     Zero      0/1       Zero      0       0           1   0 */
/* Zero     Infinity  0/1       Infinity  1       0           0   0 */
/* Zero     NaN       X         NaN       0       0           0   1 */
/* Infinity Normal    0/1       Infinity  1       0           0   0 */
/* Infinity Denormal  0/1       Infinity  1       0           0   0 */
/* Infinity Zero      0/1       Infinity  1       0           0   0 */
/* Infinity Infinity  0/1       Infinity  1       0           0   0 */
/* Infinity NaN       X         NaN       0       0           0   1 */
/* NaN      Normal    X         NaN       0       0           0   1 */
/* NaN      Denormal  X         NaN       0       0           0   1 */
/* NaN      Zero      X         NaN       0       0           0   1 */
/* NaN      Infinity  X         NaN       0       0           0   1 */
/* NaN      NaN       X         NaN       0       0           0   1 */
#endif
