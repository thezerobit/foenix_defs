wdc816as -DUSING_816 -DLARGE -V -L fxloader.asm -O fxloader.obj
wdc816as -DUSING_816 -DLARGE -V -L paddles.asm -O paddles.obj
wdc816cc -ML -LT -LW -SI -SP pong.c
wdc816cc -ML -LT -LW -SI -SP engine.c
wdcln -HIE -V -T -P00 fxloader.obj paddles.obj pong.obj engine.obj -LCL -O pong.hex -C10000 -D20000
