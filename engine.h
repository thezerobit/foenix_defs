#ifndef ENGINE_H
#define ENGINE_H

#include "foenix.h"

/* definitions */

#define VIDEO_RES_320x240 0
#define VIDEO_RES_400x300 1
#define VIDEO_RES_640x480 2
#define VIDEO_RES_800x600 3

/* keyboard */

#define KEY_CODE_BUFFER_SIZE 8
typedef struct KeyCodes {
	u8_t buffer[KEY_CODE_BUFFER_SIZE];
	u8_t count;
} KeyCodes;


/* engine */

typedef void (*EngineUpdateCallback)(u16_t, KeyCodes *);

void engineInit(void);
void engineEnableSprites(u16_t numSpriteImages, u16_t numSprites);
void engineEnableText(bool clearScreen, bool cursorEnabled);
void engineSetResolution(u8_t videoRes);
void engineSetBorderSize(u8_t x, u8_t y);
void engineSetBorderColor(u8_t r, u8_t g, u8_t b);
void engineSetBackgroundColor(u8_t r, u8_t g, u8_t b);
void engineSetUpdateCallback(EngineUpdateCallback callback);
void engineRun(void);

/* text */

void engineCursorSetLocation(u16_t x, u16_t y);
void engineCursorShow(void);
void engineCursorHide(void);
void engineCursorSetCharacter(u8_t c);
void enginePutChar(u8_t c);

/* sprites */

u8_t * spriteGetImage(u16_t spriteImg);
void spriteImageCopyToVideo(u16_t spriteImg, void * src, u16_t numImages);
void spriteEnable(u16_t idx, bool enable);
/* upper left corner of screen is 32,32 */
void spritePosition(u16_t idx, u16_t x, u16_t y);
void spriteImage(u16_t sprite, u16_t image);

/* sound */

void psgPlayNote(u16_t tone, u16_t note, u16_t octave, u16_t volume, u16_t frames);

/* random number generator */

void rngInit(void);

#endif