#include "engine.h"

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

typedef enum State {
	Start,
	TitleScreen,
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
i16_t PuckDirection; /* 0 to 63 from pointing upwards, clockwise */
u16_t PuckSpeed; /* ~ 36 */
Vec PuckVel; /* derived from PuckDirection and PuckSpeed */
State GameState;
u16_t WaitTimer;

typedef enum {
	INPUT_JOY_1,
	INPUT_JOY_2,
	INPUT_PADDLE_1,
	INPUT_PADDLE_2,
	INPUT_KEY_1,
	INPUT_LAST,
} Input;

u8_t Player1Input = INPUT_JOY_1;
u8_t Player2Input = INPUT_JOY_2;
bool UpPressed = false;
bool DownPressed = false;
u16_t Player1Score;
u16_t Player2Score;

i16_t Sin[64] = {
    0, 25, 50, 74, 98, 121, 142, 162, 
    181, 198, 213, 226, 237, 245, 251, 255, 
    256, 255, 251, 245, 237, 226, 213, 198, 
    181, 162, 142, 121, 98, 74, 50, 25, 
    0, -25, -50, -74, -98, -121, -142, -162, 
    -181, -198, -213, -226, -237, -245, -251, -255, 
    -256, -255, -251, -245, -237, -226, -213, -198, 
    -181, -162, -142, -121, -98, -74, -50, -25};
i16_t Cos[64] = {
    256, 255, 251, 245, 237, 226, 213, 198, 
    181, 162, 142, 121, 98, 74, 50, 25, 
    0, -25, -50, -74, -98, -121, -142, -162, 
    -181, -198, -213, -226, -237, -245, -251, -255, 
    -256, -255, -251, -245, -237, -226, -213, -198, 
    -181, -162, -142, -121, -98, -74, -50, -25, 
    0, 25, 50, 74, 98, 121, 142, 162, 
    181, 198, 213, 226, 237, 245, 251, 255};

void setPosition(Thing thing);
void doJoyMovement(u8_t joyState, Thing * paddle);
void doPaddleMovement(u16_t paddlePos, Thing * paddle);
void doKeyboardMovement(Thing * paddle, KeyCodes * keyCodes);
void UpdatePuck(void);
void PlayTritone(void);
void UpdatePuckVelocity(void);
void ResetPuck(void);
void ReflectPuck(Thing * thing);
void WallBounce(void);
void StartAction(void);
u8_t * GetInputName(u8_t input);
void ClearTitleScreen(void);
void DrawTitleScreen(void);
void DrawScores(void);
void doFKeyActions(KeyCodes * keyCodes);
void doInput(Thing * paddle, u8_t input, KeyCodes * keyCodes);
void doInputs(KeyCodes * keyCodes);
void Update(u16_t frame, KeyCodes * keyCodes);


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

	WaitTimer = 60;
	GameState = Start;

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

void setPosition(Thing thing) {
	spritePosition(thing.spriteIdx, (thing.loc.x >> 4) - thing.offset.x + 32, (thing.loc.y >> 4) - thing.offset.y + 32);
}

void doJoyMovement(u8_t joyState, Thing * paddle) {
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

void doPaddleMovement(u16_t paddlePos, Thing * paddle) {
	/* range 15 to 54 */
	if (paddlePos < 15) {
		paddlePos = 15;
	}
	if (paddlePos > 55) {
		paddlePos = 55;
	}
	paddlePos = paddlePos - 15;
	paddle->loc.y = paddlePos * 6 * 16;
}

void doKeyboardMovement(Thing * paddle, KeyCodes * keyCodes) {
	u8_t code;
	bool down;
	u16_t i;
	for (i = 0; i < keyCodes->count; ++i) {
		code = keyCodes->buffer[i];
		down = keyIsPressed(code);
		switch (keyScanCode(code)) {
			case 0x48: // UP
				UpPressed = down;
				break;
			case 0x50: // DOWN
				DownPressed = down;
				break;
			default:
				break;
		};
	}
	if (UpPressed) {
		paddle->loc.y -= PaddleMoveSpeed;
		if (paddle->loc.y < PaddleMinY) {
			paddle->loc.y = PaddleMinY;
		}
	}
	if (DownPressed) {
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
		ReflectPuck(&LeftPaddle);
	} else if ((PuckVel.x > 0) && (Puck.loc.x >= RightPaddle.loc.x) 
		&& ((Puck.loc.x - PuckVel.x) < RightPaddle.loc.x)
		&& (Puck.loc.y < (RightPaddle.loc.y + PaddleHeight * 8))
		&& (Puck.loc.y > (RightPaddle.loc.y - PaddleHeight * 8))) {
		ReflectPuck(&RightPaddle);
	} else if (Puck.loc.x < 0) {
		/* score point for player 2 */
		Player2Score++;
		DrawScores();
		ResetPuck();
		PlayTritone();
	} else if (Puck.loc.x > (320 << 4)) {
		/* score point for player 1 */
		Player1Score++;
		DrawScores();
		ResetPuck();
		PlayTritone();
	} else if ((Puck.loc.y < 0) && (PuckVel.y < 0)) {
		WallBounce();
		psgPlayNote(0, 6, 1, 15, 5);
	} else if ((Puck.loc.y > (240 << 4)) && (PuckVel.y > 0)) {
		WallBounce();
		psgPlayNote(0, 6, 1, 15, 5);
	}
}

void PlayTritone(void) {
	psgPlayNote(0, 0, 0, 15, 60);
	psgPlayNote(1, 6, 0, 15, 60);
}

void UpdatePuckVelocity(void) {
	PuckVel.x = Sin[PuckDirection];
	PuckVel.y = Cos[PuckDirection];
	SIGNED_MULT(PuckVel.x, PuckSpeed, PuckVel.x);
	SIGNED_MULT(PuckVel.y, PuckSpeed, PuckVel.y);
	PuckVel.x = PuckVel.x >> 8;
	PuckVel.y = PuckVel.y >> 8;
}

void ResetPuck(void) {
	Puck.loc.x = 160 << 4;
	Puck.loc.y = 120 << 4;

	PuckDirection = rngGetU8() & 0x1F;
	PuckSpeed = 36;
	if (PuckDirection < 16) {
		PuckDirection = PuckDirection + 8;
	} else {
		PuckDirection = PuckDirection + 24;
	}
	UpdatePuckVelocity();

	GameState = Waiting;
	WaitTimer = 60;
	spriteEnable(Puck.spriteIdx, false);
}

void ReflectPuck(Thing * thing) {
	i16_t diff;
	diff = Puck.loc.y - thing->loc.y;
	PuckDirection = 64 - PuckDirection;
	if (PuckDirection > 32) {
		PuckDirection = PuckDirection + (diff >> 4);
		if (PuckDirection > (64 - 4)) {
			PuckDirection = (64 - 4);
		}
		if (PuckDirection < (32 + 4)) {
			PuckDirection = (32 + 4);
		}
	} else {
		PuckDirection = PuckDirection - (diff >> 4);
		if (PuckDirection > (32 - 4)) {
			PuckDirection = (32 - 4);
		}
		if (PuckDirection < (0 + 4)) {
			PuckDirection = (0 + 4);
		}
	}
	UpdatePuckVelocity();

	psgPlayNote(0, 0, 2, 15, 5);
}

void WallBounce(void) {
	if (PuckDirection < 32) {
		PuckDirection = 32 - PuckDirection;
	} else {
		PuckDirection = 96 - PuckDirection;
	}
	UpdatePuckVelocity();
}

void StartAction(void) {
	spriteEnable(Puck.spriteIdx, false);
	spriteEnable(LeftPaddle.spriteIdx, true);
	spriteEnable(RightPaddle.spriteIdx, true);
	engineClearText(' ');
	Player1Score = 0;
	Player2Score = 0;
	DrawScores();
	ResetPuck();
}

u8_t * GetInputName(u8_t input) {
	switch(input) {
		case INPUT_JOY_1:
			return "JOYSTICK 1";
		case INPUT_JOY_2:
			return "JOYSTICK 2";
		case INPUT_PADDLE_1:
			return "PADDLE 1";
		case INPUT_PADDLE_2:
			return "PADDLE 2";
		case INPUT_KEY_1:
			return "KEYBOARD";
		default:
			return "UNKNOWN";
	}
}

void ClearTitleScreen(void) {
	enginePlaceText("   ", 16, 10);
	enginePlaceText("                              ", 5, 13);
	enginePlaceText("                              ", 5, 16);
	enginePlaceText("                              ", 5, 19);
}

void DrawTitleScreen(void) {
	u8_t * text;
	enginePlaceText("PONG", 16, 10);
	enginePlaceText("(F1) PLAYER 1:", 5, 13);
	text = GetInputName(Player1Input);
	enginePlaceText(text, 20, 13);
	enginePlaceText("(F2) PLAYER 2:", 5, 16);
	text = GetInputName(Player2Input);
	enginePlaceText(text, 20, 16);
	enginePlaceText("(F3) START GAME", 10, 19);
}

void DrawScores(void) {
	enginePlaceU16(Player1Score, 5, 3);
	enginePlaceU16(Player2Score, 22, 3);
}

void doFKeyActions(KeyCodes * keyCodes) {
	u16_t i, code, j;
	bool down;
	for (i = 0; i < keyCodes->count; ++i) {
		code = keyCodes->buffer[i];
		down = keyIsPressed(code);
		switch (keyScanCode(keyCodes->buffer[i])) {
			case KEY_F1:
				if (down) {
					Player1Input++;
					if (Player1Input == INPUT_LAST) {
						Player1Input = INPUT_JOY_1;
					}
				}	
				ClearTitleScreen();
				DrawTitleScreen();
				break;
			case KEY_F2:
				if (down) {
					Player2Input++;
					if (Player2Input == INPUT_LAST) {
						Player2Input = INPUT_JOY_1;
					}
				}
				ClearTitleScreen();
				DrawTitleScreen();
				break;
			case KEY_F3:
				if (down) {
					StartAction();
				}
				break;
			case KEY_F4:
				break;
		}
	}
}

void doInput(Thing * paddle, u8_t input, KeyCodes * keyCodes) {
	u16_t paddleVal;
	switch(input) {
		case INPUT_JOY_1:
			doJoyMovement(joyGetState(0), paddle);
			break;
		case INPUT_JOY_2:
			doJoyMovement(joyGetState(1), paddle);
			break;
		case INPUT_PADDLE_1:
			doPaddleMovement(pollPaddle(0), paddle);
			break;
		case INPUT_PADDLE_2:
			doPaddleMovement(pollPaddle(1), paddle);
			break;
		case INPUT_KEY_1:
			doKeyboardMovement(paddle, keyCodes);
			break;
		default:
			break;
	}
}

void doInputs(KeyCodes * keyCodes) {
	doInput(&LeftPaddle, Player1Input, keyCodes);
	doInput(&RightPaddle, Player2Input, keyCodes);
}

void Update(u16_t frame, KeyCodes * keyCodes) {
	switch (GameState) {
		case Start:
			DrawTitleScreen();
			GameState = TitleScreen;
			break;
		case TitleScreen:
			doFKeyActions(keyCodes);
			break;
		case Waiting:
			doInputs(keyCodes);
			setPosition(LeftPaddle);
			setPosition(RightPaddle);
			if (!WaitTimer--) {
				GameState = Playing;
				spriteEnable(Puck.spriteIdx, true);
			}
			break;
		case Playing:
			doInputs(keyCodes);
			UpdatePuck();
			setPosition(Puck);
			setPosition(LeftPaddle);
			setPosition(RightPaddle);
			break;
	}
}