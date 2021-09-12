#include <STRING.H>
#include "engine.h"

/* state */

u16_t _VideoFlags;
u32_t _VideoRAM;
u8_t _VideoRes;

u8_t _VideoBorderX;
u8_t _VideoBorderY;
u8_t _VideoBorderRed;
u8_t _VideoBorderGreen;
u8_t _VideoBorderBlue;

u16_t _VideoFrameCounter;
u16_t _VideoLastFrame;

EngineUpdateCallback _UpdateCallback;

u16_t _SpriteCount;
u32_t _SpriteRAM;
Sprite _SpriteControlBuffer[SPRITE_MAX];

KeyCodes _KeyCodes;
KeyCodes _KeyCodesCopy;

bool _RNGinitiated = false;

/* interrupt callbacks */

void COPHandler(void) {
}

void BRKHandler(void) {
}

void IRQHandler(void) {
	if (u8(INT_PENDING_REG0) & FNX0_INT00_SOF) {
		u8(INT_PENDING_REG0) = FNX0_INT00_SOF;
		_VideoFrameCounter++;
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
    _VideoBorderRed = 0;
    _VideoBorderGreen = 0;
    _VideoBorderBlue = 0;

	_VideoFrameCounter = 0;
	_VideoLastFrame = 0;

	_SpriteCount = 0;
	_SpriteRAM = 0;

	_KeyCodes.count = 0;

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

void engineSetResolution(u8_t videoRes) {
	_VideoRes = videoRes;
}

void engineSetBorderSize(u8_t x, u8_t y) {
	_VideoBorderX = x;
	_VideoBorderY = y;
}

void engineSetBorderColor(u8_t r, u8_t g, u8_t b) {
	_VideoBorderRed = r;
	_VideoBorderGreen = g;
	_VideoBorderBlue = b;
}

void engineSetUpdateCallback(EngineUpdateCallback callback) {
	_UpdateCallback = callback;
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