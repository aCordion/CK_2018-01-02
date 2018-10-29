#pragma once

#define ENTER	13
#define LEFT    75
#define RIGHT   77
#define UP		72
#define DOWN	80
#define SPACE	32
#define KEY_Z	90
#define KEY_z	122
#define KEY_X	88
#define KEY_x	120
#define KEY_C	67
#define KEY_c	99




//enum {BLANK, TARGET, OBJECT};

void gotoxy(int x, int y);

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint( int x, int y, char* string );
void SetColor( unsigned short color );
