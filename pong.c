#include "engine.h"

void Update(u16_t frame, KeyCodes * keyCodes);

typedef struct Vec {
	i16_t x;
	i16_t y;
} Vec;

typedef struct Thing {
	Vec loc; // 16 units per pixel
	Vec offset; // pixel offset
	u16_t colorIdx;
	u16_t spriteImage;
	u16_t spriteIdx;
} Thing;

void setPosition(Thing thing) {
	spritePosition(thing.spriteIdx, (thing.loc.x >> 4) - thing.offset.x + 32, (thing.loc.y >> 4) - thing.offset.y + 32);
}

typedef enum State {
	Waiting,
	Playing
} State;

const PuckSize = 2;
const PaddleWidth = 2;
const PaddleHeight = 20;
const PaddleMoveSpeed = 3 << 4;
const PaddleMinY = 0;
const PaddleMaxY = 240 << 4;

Thing Puck, LeftPaddle, RightPaddle;
Vec PuckVel;
State GameState;
u16_t WaitTimer;

void main(void) {
	u16_t x, y;

	engineInit();
	engineEnableSprites(3, 3);
	engineEnableText(true, true);

	Puck.loc.x = 160 << 4;
	Puck.loc.y = 120 << 4;
	Puck.offset.x = 1;
	Puck.offset.y = 1;
	Puck.colorIdx = 1;
	Puck.spriteImage = 0;
	Puck.spriteIdx = 0;

	LeftPaddle.loc.x = 20 << 4;
	LeftPaddle.loc.y = 120 << 4;
	LeftPaddle.offset.x = 1;
	LeftPaddle.offset.y = 10;
	LeftPaddle.colorIdx = 2;
	LeftPaddle.spriteImage = 1;
	LeftPaddle.spriteIdx = 1;

	RightPaddle.loc.x = 300 << 4;
	RightPaddle.loc.y = 120 << 4;
	RightPaddle.offset.x = 1;
	RightPaddle.offset.y = 10;
	RightPaddle.colorIdx = 3;
	RightPaddle.spriteImage = 2;
	RightPaddle.spriteIdx = 2;

	PuckVel.x = -2 * 16;
	PuckVel.y = 1 * 16;

	WaitTimer = 60;
	GameState = Waiting;
	spriteEnable(Puck.spriteIdx, false);

	/* draw puck */
	for (y = 0; y < PuckSize; ++y) {
		for (x = 0; x < PuckSize; ++x) {
			spriteGetImage(Puck.spriteImage)[x + y * SPRITE_WIDTH] = Puck.colorIdx;
		}
	}

	/* set color 1 of palette 0 to white */
	getPalette(0)[Puck.colorIdx].r = 0xFF;
	getPalette(0)[Puck.colorIdx].g = 0xFF;
	getPalette(0)[Puck.colorIdx].b = 0xFF;

	getPalette(0)[LeftPaddle.colorIdx].r = 0x80;
	getPalette(0)[LeftPaddle.colorIdx].g = 0x80;
	getPalette(0)[LeftPaddle.colorIdx].b = 0xFF;

	getPalette(0)[RightPaddle.colorIdx].r = 0xFF;
	getPalette(0)[RightPaddle.colorIdx].g = 0x80;
	getPalette(0)[RightPaddle.colorIdx].b = 0x80;

	/* draw paddles */
	for (y = 0; y < PaddleHeight; ++y) {
		for (x = 0; x < PaddleWidth; ++x) {
			spriteGetImage(LeftPaddle.spriteImage)[x + y * SPRITE_WIDTH] = LeftPaddle.colorIdx;
			spriteGetImage(RightPaddle.spriteImage)[x + y * SPRITE_WIDTH] = RightPaddle.colorIdx;
		}
	}

	spriteEnable(Puck.spriteIdx, true);
	spriteEnable(LeftPaddle.spriteIdx, true);
	spriteEnable(RightPaddle.spriteIdx, true);

	spriteImage(Puck.spriteIdx, Puck.spriteImage);
	spriteImage(LeftPaddle.spriteIdx, LeftPaddle.spriteImage);
	spriteImage(RightPaddle.spriteIdx, RightPaddle.spriteImage);

	setPosition(Puck);
	setPosition(LeftPaddle);
	setPosition(RightPaddle);

	engineSetResolution(VIDEO_RES_320x240);
	engineSetUpdateCallback(Update);
	engineRun();
}

void doPaddleMovement(u8_t joyState, Thing * paddle) {
	if (joyState & JOY_UP) {
		paddle->loc.y -= PaddleMoveSpeed;
		if (paddle->loc.y < PaddleMinY) {
			paddle->loc.y = PaddleMinY;
		}
	}
	if (joyState & JOY_DOWN) {
		paddle->loc.y += PaddleMoveSpeed;
		if (paddle->loc.y > PaddleMaxY) {
			paddle->loc.y = PaddleMaxY;
		}
	}
}

void UpdatePuck(void) {
	Puck.loc.x += PuckVel.x;
	Puck.loc.y += PuckVel.y;
	/* check paddle collision */
	if ((PuckVel.x < 0) && (Puck.loc.x <= LeftPaddle.loc.x) 
		&& ((Puck.loc.x - PuckVel.x) > LeftPaddle.loc.x)
		&& (Puck.loc.y < (LeftPaddle.loc.y + PaddleHeight * 8))
		&& (Puck.loc.y > (LeftPaddle.loc.y - PaddleHeight * 8))) {
		PuckVel.x = -PuckVel.x; /* simple reflection */
		psgPlayNote(0, 0, 2, 15, 5);
	} else if ((PuckVel.x > 0) && (Puck.loc.x >= RightPaddle.loc.x) 
		&& ((Puck.loc.x - PuckVel.x) < RightPaddle.loc.x)
		&& (Puck.loc.y < (RightPaddle.loc.y + PaddleHeight * 8))
		&& (Puck.loc.y > (RightPaddle.loc.y - PaddleHeight * 8))) {
		PuckVel.x = -PuckVel.x; /* simple reflection */
		psgPlayNote(0, 0, 2, 15, 5);
	} else if (Puck.loc.x < 0) {
		/* score point for player 2 */
		Puck.loc.x = 160 << 4;
		Puck.loc.y = 120 << 4;
		PuckVel.x = -2 * 16;
		PuckVel.y = 1 * 16;
		psgPlayNote(0, 0, 0, 15, 60);
		psgPlayNote(1, 6, 0, 15, 60);
		GameState = Waiting;
		WaitTimer = 60;
		spriteEnable(Puck.spriteIdx, false);
	} else if (Puck.loc.x > (320 << 4)) {
		/* score point for player 1 */
		Puck.loc.x = 160 << 4;
		Puck.loc.y = 120 << 4;
		PuckVel.x = -2 * 16;
		PuckVel.y = 1 * 16;
		psgPlayNote(0, 0, 0, 15, 60);
		psgPlayNote(1, 6, 0, 15, 60);
		GameState = Waiting;
		WaitTimer = 60;
		spriteEnable(Puck.spriteIdx, false);
	} else if ((Puck.loc.y < 0) && (PuckVel.y < 0)) {
		PuckVel.y = -PuckVel.y;
		psgPlayNote(0, 6, 1, 15, 5);
	} else if ((Puck.loc.y > (240 << 4)) && (PuckVel.y > 0)) {
		PuckVel.y = -PuckVel.y;
		psgPlayNote(0, 6, 1, 15, 5);
	}
}

void Update(u16_t frame, KeyCodes * keyCodes) {
	u16_t i;
	u8_t code;
	bool down;
	u16_t volume;
	/* psg set volume based on F1 to F4 */
	for (i = 0; i < keyCodes->count; ++i) {
		code = keyCodes->buffer[i];
		volume = keyIsPressed(code) ? 15 : 0;
		switch (keyScanCode(keyCodes->buffer[i])) {
			case KEY_F1:
				psgSetVol(0, volume);
				break;
			case KEY_F2:
				psgSetVol(1, volume);
				break;
			case KEY_F3:
				psgSetVol(2, volume);
				break;
			case KEY_F4:
				psgSetVol(3, volume);
				break;
		}
	}

	switch (GameState) {
		case Waiting:
			if (!WaitTimer--) {
				GameState = Playing;
				spriteEnable(Puck.spriteIdx, true);
			}
			break;
		case Playing:
			UpdatePuck();
			break;
	}

	doPaddleMovement(joyGetState(0), &LeftPaddle);
	doPaddleMovement(joyGetState(1), &RightPaddle);
	

	setPosition(Puck);
	setPosition(LeftPaddle);
	setPosition(RightPaddle);
}