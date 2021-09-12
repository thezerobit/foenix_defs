A collection of C header files for the C256 Foenix.

The convertdefs.py Python script will convert the *_def.asm files from the https://github.com/Trinity-11/Kernel_FMX 
repo if it is cloned in the same parent folder as this repo.

For now, the conversion just defines the raw hex and decimal values.
You will have to cast memory addresses to the appropriate C types in your own code.

Building on the generated header files, foenix.h file contains a growing number of
definitions and macros for interacting directly with the Foenix hardware.

The engine.h / engine.c files represent a proof-of-concept level implementation
of a game engine that takes care of interrupt handling and makes building games
a tiny bit simpler. pong.c is a simple pong-like game.

These files in the "defs" folder are distributed under the same license as
the source assembly files. The convertdefs.py, foenix.h and other files are
available under the Apache 2.0 license as specified in the LICENSE file.