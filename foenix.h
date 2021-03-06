#ifndef FOENIX_H
#define FOENIX_H

#include <sys/types.h>
#include "defs/VKYII_CFP9553_GENERAL_def.h"
#include "defs/VKYII_CFP9553_TILEMAP_def.h"
#include "defs/VKYII_CFP9553_SPRITE_def.h"
#include "defs/interrupt_def.h"
#include "defs/keyboard_def.h"
#include "defs/RTC_def.h"
#include "defs/GABE_Control_Registers_def.h"
#include "defs/Trinity_CFP9301_def.h"
#include "defs/Math_def.h"
#include "defs/timer_def.h"
#include "defs/super_io_def.h"

/* helpers */

#define u8(addr)    (*(volatile unsigned char *)addr)
#define u16(addr)   (*(volatile unsigned short *)addr)
#define u32(addr)   (*(volatile unsigned long *)addr)
#define i8(addr)    (*(volatile signed char *)addr)
#define i16(addr)   (*(volatile signed short *)addr)
#define i32(addr)   (*(volatile signed long *)addr)
#define u8Ptr(addr) ((volatile unsigned char *)addr)

#define setBits8(addr, bits) u8(addr) = u8(addr) | (bits)
#define unsetBits8(addr, bits) u8(addr) = u8(addr) & ~(bits)

/* addr should be a 24/32 bit unsigned int, target an array of bytes */
#define copy24BitAddr(addr, target) \
	(target)[0] = (u8_t)(addr); \
	(target)[1] = (u8_t)((addr) >> 8); \
	(target)[2] = (u8_t)((addr) >> 16)

/* math */

/* quo and rem must be assignable u16_t variables */
#define UNSIGNED_DIV(num, dem, quo, rem) u16(UNSIGNED_DIV_NUM_LO) = num;\
    u16(UNSIGNED_DIV_DEM_LO) = dem;\
    quo = u16(UNSIGNED_DIV_QUO_LO);\
    rem = u16(UNSIGNED_DIV_REM_LO)

/* a and b are i16_t, res is i32_t */
#define SIGNED_MULT(a, b, res)  i16(SIGNED_MULT_A_LO) = a;\
	i16(SIGNED_MULT_B_LO) = b;\
	res = i32(SIGNED_MULT_AL_LO)

/* keyboard */

#define keyIsPressed(code) !((code) & 0x80)
#define keyIsReleased(code) ((code) & 0x80)
#define keyScanCode(code) ((code) & 0x7F)

#define KEY_UP      0x48
#define KEY_DOWN    0x50
#define KEY_LEFT    0x4B
#define KEY_RIGHT   0x4D
#define KEY_F1      0x3B
#define KEY_F2      0x3C
#define KEY_F3      0x3D
#define KEY_F4      0x3E

/* mouse */

#define mousePointerEnable() setBits8(MOUSE_PTR_CTRL_REG_L, 1)
#define mousePointerDisable() unsetBits8(MOUSE_PTR_CTRL_REG_L, 1)

/* this only works if vicky is being fed incoming bytes from the PS/2 port
   during mouse interrupts, as the kernel does */
#define mouseGetXVicky() u16(MOUSE_PTR_X_POS_L)
#define mouseGetYVicky() u16(MOUSE_PTR_Y_POS_L)

/* joystick */

#define JOY_UP      0x01
#define JOY_DOWN    0x02
#define JOY_LEFT    0x04
#define JOY_RIGHT   0x08
#define JOY_BUTTON1 0x10
#define JOY_BUTTON2 0x40
#define JOY_BUTTON3 0x40

#define JOY_0_1_MASK (JOY_UP | JOY_DOWN | JOY_LEFT | JOY_RIGHT | JOY_BUTTON1 | JOY_BUTTON2 | JOY_BUTTON3)
#define JOY_2_3_MASK (JOY_UP | JOY_DOWN | JOY_LEFT | JOY_RIGHT | JOY_BUTTON1)

/* num is 0 to 3 */
#define joyGetState(num) (~u8Ptr(JOYSTICK0)[num] & ((num < 2) ? JOY_0_1_MASK : JOY_2_3_MASK))

/* video */

#define video320x240() u8(MASTER_CTRL_REG_H) = Mstr_Ctrl_Video_Mode1
#define video400x300() u8(MASTER_CTRL_REG_H) = Mstr_Ctrl_Video_Mode0 | Mstr_Ctrl_Video_Mode1
#define video640x480() u8(MASTER_CTRL_REG_H) = 0
#define video800x600() u8(MASTER_CTRL_REG_H) = Mstr_Ctrl_Video_Mode0

typedef struct BGRColor {
	u8_t b;
	u8_t g;
	u8_t r;
} BGRColor;

#define VIDEO_BORDER_COLOR (*(BGRColor *)BORDER_COLOR_B)
#define VIDEO_BACKGROUND_COLOR (*(BGRColor *)BORDER_COLOR_B)

#define videoBorderSize(x, y) u8(BORDER_X_SIZE) = x; u8(BORDER_Y_SIZE) = y
#define videoBorderColor(r, g, b) u8(BORDER_COLOR_R) = r; \
	u8(BORDER_COLOR_G) = g; \
	u8(BORDER_COLOR_B) = b
#define videoBackgroundColor(r, g, b) u8(BACKGROUND_COLOR_R) = r; \
	u8(BACKGROUND_COLOR_G) = g; \
	u8(BACKGROUND_COLOR_B) = b

#define VIDEO_TEXT         Mstr_Ctrl_Text_Mode_En
#define VIDEO_TEXT_OVERLAY Mstr_Ctrl_Text_Overlay
#define VIDEO_GRAPHICS     Mstr_Ctrl_Graph_Mode_En 
#define VIDEO_BITMAP       Mstr_Ctrl_Bitmap_En     
#define VIDEO_TILEMAP      Mstr_Ctrl_TileMap_En    
#define VIDEO_SPRITE       Mstr_Ctrl_Sprite_En     
#define VIDEO_GAMMA        Mstr_Ctrl_GAMMA_En     
#define VIDEO_DISABLE      Mstr_Ctrl_Disable_Vid   
#define videoMode(flags)   u8(MASTER_CTRL_REG_L) = (flags)
/* example: videoMode(VIDEO_GRAPHICS | VIDEO_SPRITE | VIDEO_TEXT | VIDEO_TEXT_OVERLAY); */

/* SOUND */

#define PSG_BASE_ADDRESS 0xAFF100
#define PSG_CLOCK_FREQ_HZ 3579545
#define PSG_X_DEC 111860.78125
#define PSG_X_INT 111861

#define PSG_NOTE_A  0x3f9
#define PSG_NOTE_As 0x3c0
#define PSG_NOTE_B  0x38a
#define PSG_NOTE_C  0x357
#define PSG_NOTE_Cs 0x327
#define PSG_NOTE_D  0x2fa
#define PSG_NOTE_Ds 0x2cf
#define PSG_NOTE_E  0x2a7
#define PSG_NOTE_F  0x281
#define PSG_NOTE_Fs 0x25d
#define PSG_NOTE_G  0x23b
#define PSG_NOTE_Gs 0x21b
/* tone is from 0 to 3 (3 = noise) */
/* vol is from 0 (off) to 15 (loudest) */
#define psgSetVol(tone, vol) u8(PSG_BASE_ADDRESS) = 0x90 | ((tone) << 5) | (15 - (vol))
#define psgSendByte(byte) u8(PSG_BASE_ADDRESS) = (byte)

/* text */

#define TEXT_SCREEN_SIZE 0x2000

#define textScreen u8Ptr(CS_TEXT_MEM_PTR)
#define textColor  u8Ptr(CS_COLOR_MEM_PTR)

typedef struct TextCursorControl {
	u8_t control;
	u8_t textBufferOffset;
	u8_t character;
	u8_t color;
	u16_t locX;
	u16_t locY;
} TextCursorControl;

#define TEXT_CURSOR_CTRL (*(TextCursorControl *)VKY_TXT_CURSOR_CTRL_REG)

/* palettes a.k.a color lookup tables "LUT" */

#define PALETTE_SIZE 256
#define PALETTE_SIZE_BYTES 1024

typedef struct PaletteColor {
    u8_t b;
    u8_t g;
    u8_t r;
    u8_t a;
} PaletteColor;

/* palette num from 0 to 7 */
/* returns pointer to raw bytes */
#define getPaletteData(num) u8Ptr(GRPH_LUT0_PTR + PALETTE_SIZE_BYTES * (num))
/* returns pointer to array of PaletteColor */
#define getPalette(num) ((volatile PaletteColor *)(GRPH_LUT0_PTR + PALETTE_SIZE_BYTES * (num)))

/* sprites */

#define VICKY_RAM_OFFSET 0xB00000
#define SPRITE_SIZE 1024
#define SPRITE_SCREEN_OFFSET 32
#define SPRITE_WIDTH 32
#define SPRITE_MAX 64
#define spriteImageLoc(spriteImageNumber, spriteVideoLoc) u8Ptr(VICKY_RAM_OFFSET + (spriteVideoLoc) + (SPRITE_SIZE * (spriteNumber)))

typedef struct Sprite {
    u8_t control;
    u8_t address[3];
    u16_t x;
    u16_t y;
} Sprite;

/* there are 32 or 64 sprites */
#define SPRITE_CONTROL      ((Sprite *)SP00_CONTROL_REG)
#define SPRITE_PALETTE_MASK 0x0E
#define SPRITE_DEPTH_MASK   0x70

/* num is from 0 to 31 or 63 */
/* enable is a bool */
/* palette from 0 to 7 */
/* depth from 0 to 7 */
/* collision is a bool */
#define spriteControl(num, enable, palette, depth, collision) \
	SPRITE_CONTROL[num].control = \
	((enable) ? SPRITE_Enable : 0) | \
	((palette) << 1) | \
	((depth) << 4) | \
	((collision) ? SPRITE_Collision_On : 0)

/* spriteVideoLoc is the location of the beginning of sprite image data
   in the range 0x000000 to 0x3FFFFF */
#define spriteSetImage(num, spriteImageNum, spriteVideoLoc) \
	copy24BitAddr((spriteVideoLoc) + SPRITE_SIZE * (spriteImageNum), SPRITE_CONTROL[num].address)
	
/* relative to the screen, so (0,0) is upper left corner of screen */
#define spriteSetPositionRel(num, locX, locY) \
	SPRITE_CONTROL[num].x = locX + SPRITE_SCREEN_OFFSET; \
	SPRITE_CONTROL[num].y = locY + SPRITE_SCREEN_OFFSET
/* absolute position, so (32,32) is upper left corner of screen */
#define spriteSetPositionAbs(num, locX, locY) \
	SPRITE_CONTROL[num].x = locX; \
	SPRITE_CONTROL[num].y = locY

/* tiles */

typedef struct TileMapCtrl {
    u8_t control;
    u8_t startAddress[3];
    u16_t totalXSize; /* size of map in X tile count (max 1024) */
    u16_t totalYSize; /* size of map in Y tile count (max 1024) */
    /* Top Left Corner Position of the TileMap Window in X + Scroll */
    /* Direction: [14] Scroll: [13:10] Pos: [9:0] in X */
    u16_t windowXPosition; 
    /* Top Left Corner Position of the TileMAp Window in Y */
    /* Direction: [14] Scroll: [13:10] Pos: [9:0] in Y */
    u16_t windowYPosition;
} TileMapCtrl;

#define TILE_MAP_CTRLS ((TileMapCtrl *)TL0_CONTROL_REG) /* there are 4 tile layers */

typedef struct TILE_DEF_STRUCT {
    u8_t tileNumber;
    u8_t tileSet; /* 0 - 8 */
} TILE_DEF;

/* num is 0 to 3 */
/* enable is bool */
/* collision is bool */
#define tileMapControl(num, enable, collision) \
	TILE_MAP_CTRLS[num].control = ((enable) ? TILE_Enable : 0) | ((collision) ? TILE_Collision_On : 0)
#define tileMapSetMem(num, addr) copy24BitAddr(addr, TILE_MAP_CTRLS[num].startAddress)
/* tile map size can be up to 1024 for width and height */
#define tileMapSetSize(num, width, height) \
	TILE_MAP_CTRLS[num].totalXSize = width; \
	TILE_MAP_CTRLS[num].totalYSize = height
#define tileMapSetWindow(num, x, y) \
	TILE_MAP_CTRLS[num].windowXPosition = (x) & 0x3FFF; \
	TILE_MAP_CTRLS[num].windowYPosition = (y) & 0x3FFF
#define tileMapSetTileNum(num, x, y, tileNum, tileMapWidth, tileMapMemLoc) \
	((TILE_DEF *)(VICKY_RAM_OFFSET + (tileMapMemLoc)))[1 + (x) + (y) * (tileMapWidth)].tileNumber = tileNum
#define tileMapSetTileSet(num, x, y, tileSetNum, tileMapWidth, tileMapMemLoc) \
	((TILE_DEF *)(VICKY_RAM_OFFSET + (tileMapMemLoc)))[1 + (x) + (y) * (tileMapWidth)].tileSet = tileSetNum

#define TILESET_STRIDE_256 0x08

typedef struct TilesetConfig {
    u8_t address[3];
    u8_t config; /* [3] - TileStride256x256 */
} TilesetConfig;

#define TILESET_CFGS ((volatile TilesetConfig *)TILESET0_ADDY_L) /* there are 8 tile sets */

/* tileset num from 0 to 7 */
/* addr in the range of 0x000000 to 0x3FFFFF */
#define tilesetSetMem(num, addr) copy24BitAddr(addr, TILESET_CFGS[num].address)
#define tilesetSetStride1(num) TILESET_CFGS[num].config = TILESET_CFGS[num].config & ~TILESET_STRIDE_256
#define tilesetSetStride256(num) TILESET_CFGS[num].config = TILESET_CFGS[num].config | TILESET_STRIDE_256

/* interrupts */

#define IRQ_VECTOR 0x00FFEE

#define irqEnable()  asm { cli; }
#define irqDisable() asm { sei; }
#define irqWait()    asm { wai; }

#define irqEnableStartOfFrame()  unsetBits8(INT_MASK_REG0, FNX0_INT00_SOF)
#define irqDisableStartOfFrame() setBits8(INT_MASK_REG0, FNX0_INT00_SOF)
#define irqEnableMouse()  unsetBits8(INT_MASK_REG0, FNX0_INT07_MOUSE)
#define irqDisableMouse() setBits8(INT_MASK_REG0, FNX0_INT07_MOUSE)
#define irqEnableKeyboard()  unsetBits8(INT_MASK_REG1, FNX1_INT00_KBD)
#define irqDisableKeyboard() setBits8(INT_MASK_REG1, FNX1_INT00_KBD)
#define irqEnableTimer0()  unsetBits8(INT_MASK_REG0, FNX0_INT02_TMR0)
#define irqDisableTimer0() setBits8(INT_MASK_REG0, FNX0_INT02_TMR0)

/* random number generator */

#define rngGetU8() u8(GABE_RNG_DAT_LO)
#define rngGetU16() u16(GABE_RNG_DAT_LO)

#endif