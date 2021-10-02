#include <STRING.H>
#include "engine.h"

extern void POLL_PADDLE(void);
extern u8_t WHICH_PADDLE;
extern u8_t RETURN_PADDLE;

/* state */

u16_t _VideoFlags;
u32_t _VideoRAM;
u8_t _VideoRes;

u8_t _VideoBorderX;
u8_t _VideoBorderY;
BGRColor _VideoBorderColor;
BGRColor _VideoBackgroundColor;

u16_t _VideoFrameCounter;
u16_t _VideoLastFrame;

bool  _textEnabled;
bool  _textScreenWidth;
bool  _textScreenHeight;
bool  _textCursorEnabled;
TextCursorControl _textCursorControl;
bool  _textClearScreen;

EngineUpdateCallback _UpdateCallback;

u16_t _SpriteCount;
u32_t _SpriteRAM;
Sprite _SpriteControlBuffer[SPRITE_MAX];

KeyCodes _KeyCodes;
KeyCodes _KeyCodesCopy;

u16_t _PSG_Timers[4];
u16_t _PSG_NoteVals[12] = {
	0x3f9,
	0x3c0,
	0x38a,
	0x357,
	0x327,
	0x2fa,
	0x2cf,
	0x2a7,
	0x281,
	0x25d,
	0x23b,
	0x21b
};

bool _RNGinitiated = false;

volatile u16_t _Timer0Counter;

/* interrupt callbacks */

void COPHandler(void) {
}

void BRKHandler(void) {
}

void IRQHandler(void) {
	if (INT_PENDING_REG0) {
		if (u8(INT_PENDING_REG0) & FNX0_INT00_SOF) {
			u8(INT_PENDING_REG0) = FNX0_INT00_SOF;
			_VideoFrameCounter++;
		}
		if (u8(INT_PENDING_REG0) & FNX0_INT02_TMR0) {
			u8(INT_PENDING_REG0) = FNX0_INT02_TMR0;
			_Timer0Counter++;
		}
	}
	if (u8(INT_PENDING_REG1) & FNX1_INT00_KBD) {
		u8(INT_PENDING_REG1) = FNX1_INT00_KBD;
		if (_KeyCodes.count < KEY_CODE_BUFFER_SIZE - 1) {
			_KeyCodes.buffer[_KeyCodes.count++] = keyGetCode();
		}
	}
}

/* engine */

void engineInit(void) {
	u16_t i;
	/* disable all interrupts */
	u8(INT_MASK_REG0) = 0xFF;
	u8(INT_MASK_REG1) = 0xFF;
	u8(INT_MASK_REG2) = 0xFF;
	u8(INT_MASK_REG3) = 0xFF;

	_VideoFlags = 0;
	_VideoRAM = 0;
	_VideoRes = VIDEO_RES_320x240;
    _VideoBorderX = 0;
    _VideoBorderY = 0;
	_VideoBorderColor.r = 0;
	_VideoBorderColor.g = 0;
	_VideoBorderColor.b = 0;
	_VideoBackgroundColor.r = 0;
	_VideoBackgroundColor.g = 0;
	_VideoBackgroundColor.b = 0;


	_VideoFrameCounter = 0;
	_VideoLastFrame = 0;

	_textEnabled = false;
	_textScreenWidth = 80;
	_textScreenWidth = 60;
	_textCursorEnabled = false;
	_textCursorControl.control = 0;
	_textCursorControl.textBufferOffset = 0;
	_textCursorControl.locX = 0;
	_textCursorControl.locY = 0;
	_textCursorControl.character = 0xB1; /* filled block */
	_textCursorControl.color = 0xF0;
	_textClearScreen = false;

	_SpriteCount = 0;
	_SpriteRAM = 0;

	_KeyCodes.count = 0;

	for(i = 0; i < 4; ++i) {
		_PSG_Timers[i] = 0;
	}

	/* initialize sprite control buffer to zeroes */
	memset((void *)_SpriteControlBuffer, 0, SPRITE_MAX * sizeof(Sprite));

	if (!_RNGinitiated) {
		rngInit();
		_RNGinitiated = true;
	}
}

/* each sprite image takes 1K (1024) bytes of Video RAM 
   numSprites can be as high as 64
*/
void engineEnableSprites(u16_t numSpriteImages, u16_t numSprites) {
	_SpriteCount = numSprites;
	_VideoFlags = _VideoFlags | VIDEO_SPRITE | VIDEO_GRAPHICS;
	_SpriteRAM = _VideoRAM;
	_VideoRAM = _VideoRAM + SPRITE_SIZE * numSpriteImages;
	memset((void * )(_SpriteRAM + VICKY_RAM_OFFSET), 0, SPRITE_SIZE * numSpriteImages);
}

void engineEnableText(bool clearScreen, bool cursorEnabled) {
	_textEnabled = true;
	_textCursorEnabled = cursorEnabled;
	_VideoFlags = _VideoFlags | VIDEO_TEXT | VIDEO_TEXT_OVERLAY;
	_textClearScreen = clearScreen;
}

void engineSetResolution(u8_t videoRes) {
	_VideoRes = videoRes;
	switch (videoRes) {
		case VIDEO_RES_320x240:
			_textScreenWidth = 40;
			_textScreenHeight = 30;
			break;
		case VIDEO_RES_400x300:
			_textScreenWidth = 50;
			_textScreenHeight = 37;
			break;
		case VIDEO_RES_640x480:
			_textScreenWidth = 80;
			_textScreenHeight = 60;
			break;
		case VIDEO_RES_800x600:
			_textScreenWidth = 100;
			_textScreenHeight = 75;
			break;
	}
}

void engineSetBorderSize(u8_t x, u8_t y) {
	_VideoBorderX = x;
	_VideoBorderY = y;
}

void engineSetBorderColor(u8_t r, u8_t g, u8_t b) {
	_VideoBorderColor.r = r;
	_VideoBorderColor.g = g;
	_VideoBorderColor.b = b;
}

void engineSetBackgroundColor(u8_t r, u8_t g, u8_t b) {
	_VideoBackgroundColor.r = r;
	_VideoBackgroundColor.g = g;
	_VideoBackgroundColor.b = b;
}

void engineSetUpdateCallback(EngineUpdateCallback callback) {
	_UpdateCallback = callback;
}

void updatePSG(void) {
	u16_t tone;
	/* psg */
	for (tone = 0; tone < 4; ++tone) {
		if (_PSG_Timers[tone]) {
			if (!--_PSG_Timers[tone]) {
				psgSetVol(tone, 0);
			}
		}
	}
}

void engineRun(void) {
	switch (_VideoRes) {
		case VIDEO_RES_320x240:
			video320x240();
			break;
		case VIDEO_RES_400x300:
			video400x300();
			break;
		case VIDEO_RES_640x480:
			video640x480();
			break;
		case VIDEO_RES_800x600:
			video800x600();
			break;
	}
	videoMode(_VideoFlags);
	videoBorderSize(_VideoBorderX, _VideoBorderY);
	VIDEO_BORDER_COLOR = _VideoBorderColor;
	VIDEO_BACKGROUND_COLOR = _VideoBackgroundColor;


	if (_textEnabled) {
		if (_textCursorEnabled) {
			memcpy((void *)VKY_TXT_CURSOR_CTRL_REG, (void *)&_textCursorControl, sizeof(TextCursorControl));
		}
		if (_textClearScreen) {
			memset((void *)textScreen, ' ', 0x2000);
			memset((void *)textColor, 0xF0, 0x2000);
		}
	}

	mouseDisable();

	irqEnableStartOfFrame();
	irqEnableKeyboard();
	irqEnable();
	while (true) {
		irqWait();
		if (_VideoFrameCounter != _VideoLastFrame) {
			_VideoLastFrame = _VideoFrameCounter;

			/* copy sprite control data */
			memcpy((void *)SP00_CONTROL_REG, (void *)_SpriteControlBuffer, _SpriteCount * sizeof(Sprite));

			if (_textCursorEnabled) {
				memcpy((void *)VKY_TXT_CURSOR_CTRL_REG, (void *)&_textCursorControl, sizeof(TextCursorControl));
			}

			updatePSG();

			/* disabling IRQ to copy _KeyCodes structure which otherwise can be modified
			   by an interrupt at any time */
			irqDisable();
			_KeyCodesCopy = _KeyCodes;
			_KeyCodes.count = 0; /* reset key codes counter */
			irqEnable();

			_UpdateCallback(_VideoFrameCounter, &_KeyCodesCopy);
		}
	}
}

void engineCursorSetLocation(u16_t x, u16_t y) {
	_textCursorControl.locX = x;
	_textCursorControl.locY = y;
}

void engineCursorShow(void) {
	_textCursorControl.control = _textCursorControl.control | Vky_Cursor_Enable;
}
void engineCursorHide(void) {
	_textCursorControl.control = _textCursorControl.control & ~Vky_Cursor_Enable;
}

void engineCursorSetCharacter(u8_t c) {
	_textCursorControl.character = c;
}

void _engineCursorNewLine(void) {
	_textCursorControl.locX = 0;
	_textCursorControl.locY++;
	if (_textCursorControl.locY >= _textScreenHeight) {
		_textCursorControl.locY = _textScreenHeight - 1;
		_textCursorControl.textBufferOffset++; /* TODO reset to top if we get too far down */
	}
}

void enginePutChar(u8_t c) {
	switch (c)
	{
	case '\n':
		_engineCursorNewLine();
		break;
	default:
		textScreen[_textCursorControl.locX + (_textCursorControl.locY + _textCursorControl.textBufferOffset) * _textScreenWidth] = c;
		_textCursorControl.locX ++;
		if (_textCursorControl.locX >= _textScreenWidth) {
			_engineCursorNewLine();
		}
		break;
	}
}

void enginePlaceText(u8_t * text, u16_t x, u16_t y) {
	u16_t i = 0;
	u8_t nextChar;
	while (nextChar = text[i++]) {
		textScreen[x + i + y * _textScreenWidth] = nextChar;
	}
}

void enginePlaceU16(u16_t value, u16_t x, u16_t y) {
	u16_t nextDigit, i;
	u8_t digits[6];
	digits[5] = 0;
	for (i = 0; i < 5; ++i) {
		digits[i] = ' ';
	}
	for (i = 4; i <= 4 && value; --i) {
		UNSIGNED_DIV(value, 10, value, nextDigit);
		digits[i] = nextDigit + 48;
	}
	enginePlaceText(digits, x, y);
}

void enginePlaceI16(i16_t value, u16_t x, u16_t y) {
	u16_t nextDigit, i;
	u8_t digits[7];
	bool negative = value < 0;
	u16_t displayVal = negative ? (-value) : value;
	digits[6] = 0;
	for (i = 0; i < 6; ++i) {
		digits[i] = ' ';
	}
	if (displayVal == 0) {
		digits[5] = '0';
	}
	for (i = 5; i <= 5 && displayVal; --i) {
		UNSIGNED_DIV(displayVal, 10, displayVal, nextDigit);
		digits[i] = nextDigit + 48;
	}
	if (negative) {
		digits[i] = '-';
	}
	enginePlaceText(digits, x, y);
}

void engineClearText(u8_t fillChar) {
	memset((void *)textScreen, fillChar, 0x2000);
}

u8_t * spriteGetImage(u16_t spriteImg) {
	return (u8_t *)(VICKY_RAM_OFFSET + _SpriteRAM + spriteImg * SPRITE_SIZE);
}

void spriteImageCopyToVideo(u16_t spriteImg, void * src, u16_t numImages) {
	memcpy(spriteGetImage(spriteImg), src, numImages * SPRITE_SIZE);
}

void spriteEnable(u16_t idx, bool enable) {
	if (enable) {
		_SpriteControlBuffer[idx].control = _SpriteControlBuffer[idx].control | SPRITE_Enable;
	} else {
		_SpriteControlBuffer[idx].control = _SpriteControlBuffer[idx].control & ~SPRITE_Enable;
	}
}

void spritePosition(u16_t idx, u16_t x, u16_t y) {
	_SpriteControlBuffer[idx].x = x;
	_SpriteControlBuffer[idx].y = y;
}

void spriteImage(u16_t sprite, u16_t image) {
	u32_t addr = _SpriteRAM + image * SPRITE_SIZE;
	copy24BitAddr(addr, _SpriteControlBuffer[sprite].address);
}

u8_t toHexChar(u8_t val) {
	if (val < 10) {
		return val + 48;
	} else {
		return val + 55;
	}
}

void printHexByte(u8_t value) {
	enginePutChar(toHexChar((value & 0xF0) >> 4));
	enginePutChar(toHexChar(value & 0x0F));
}

void printHexWord(u16_t value) {
	printHexByte(value >> 8);
	printHexByte(value & 0xFF);
	enginePutChar('\n');
}

/*
tone is 0 to 2, note is 0 to 11 (A to G#), octave is 0 to 5-ish, volume is 0 to 15
*/
void psgPlayNote(u16_t tone, u16_t note, u16_t octave, u16_t volume, u16_t frames) {
	u16_t val = _PSG_NoteVals[note] >> octave;
	u8_t sendByte;
	sendByte = 0x80 | tone << 5 | (val & 0x0F);
	psgSendByte(0x80 | tone << 5 | (val & 0x0F));

	sendByte = (val >> 4) & 0x3F;
	psgSendByte((val >> 4) & 0x3F);
	psgSetVol(tone, volume);
	_PSG_Timers[tone] = frames;
}

void rngInit(void) {
	/* Pause updates to the clock registers */
	u8(RTC_CTRL) = u8(RTC_CTRL) | 0x08;
	/* Set the random number generator seed */
	u8(GABE_RNG_SEED_LO) = u8(RTC_SEC);
	u8(GABE_RNG_SEED_HI) = u8(RTC_MIN);
	/* Load the seed into the generator */
	u8(GABE_RNG_CTRL) = GABE_RNG_CTRL_DV | GABE_RNG_CTRL_EN;
	/* Re-enable updates to the clock registers */
	u8(RTC_CTRL) = u8(RTC_CTRL) & (~0x08);
	asm { nop; nop; nop; }
	/* Turn on the random number generator */
	u8(GABE_RNG_CTRL) = GABE_RNG_CTRL_EN;
}

/* whichPaddle is 0 - 3 */
u16_t pollPaddle(u8_t whichPaddle) {
	u16_t time, ignore, result;
	u32_t savedInterrupts;

	savedInterrupts = u32(INT_MASK_REG0);
	u32(INT_MASK_REG0) = ~FNX0_INT02_TMR0; /* only timer 0 IRQ */

    u8(TIMER0_CTRL_REG) = TMR0_SCLR; /* disable timer, allow Output to be reset */
    u8(TIMER0_CMP_REG) = TMR0_CMP_RECLR; /* allow Output to be reset */

	u16(TIMER0_CHARGE_L) = 0;
	u8(TIMER0_CHARGE_H) = 0;

	u16(TIMER0_CMP_L) = u16(TIMER0_CHARGE_L); /* reset timer Output to 0 */
    u8(TIMER0_CMP_H) = u8(TIMER0_CHARGE_H);

	u16(TIMER0_CMP_L) = 1600;
    u8(TIMER0_CMP_H) = 0;

	WHICH_PADDLE = 1 << whichPaddle; /* the POLL_PADDLE function uses this */

	u8(SIO_JOY) = 0x00; /* initiate analog read */

    u8(TIMER0_CTRL_REG) = TMR0_EN | TMR0_UPDWN | TMR0_SCLR; /* start timer */

	POLL_PADDLE();

	time = u16(TIMER0_CHARGE_L);

	irqWait();
	u8(TIMER0_CTRL_REG) = 0; /* disable Timer 0 */

	u32(INT_MASK_REG0) = savedInterrupts; 
	irqEnable();

	UNSIGNED_DIV(time - 46, 19, result, ignore);

	return result;
}

void delayCycles(u16_t cycles) {
	irqDisableKeyboard();
	irqDisableStartOfFrame();

	u8(TIMER0_CTRL_REG) = 0;
	irqEnableTimer0();
	u8(TIMER0_CHARGE_L) = 0;
	u8(TIMER0_CHARGE_M) = 0;
	u8(TIMER0_CHARGE_H) = 0;

	u8(TIMER0_CMP_L) = cycles & 0xFF;
    u8(TIMER0_CMP_M) = cycles >> 8;
    u8(TIMER0_CMP_H) = 0;

    u8(TIMER0_CMP_REG) = TMR0_CMP_RECLR;
    u8(TIMER0_CTRL_REG) = TMR0_EN | TMR0_UPDWN | TMR0_SCLR;

	irqWait();

	irqDisableTimer0();

	u8(TIMER0_CTRL_REG) = 0; /* disable Timer 0 if it is running */

	irqEnableKeyboard();
	irqEnableStartOfFrame();
}