// CAF'e 2019 invitro source code
// Credits (alphabetically):
// Adam Bazaroff, mr287cc, n1k-o, TmK

#define txtS(chr) ((int)chr + 0xDA - 65)
#define txtN(chr) ((int)chr + 0xD0 - 48)

#include "Include\chr.h"

#include "Include\nam_Invites.h"

#include "Include\snake_rattle_and_roll.h"
#include "Include\neslib.h"
#include "Include\nesdoug.h"

// #include "Include\nam_finalScreen_qr.h"

#include "Include\nam_invadersA.h"
#include "Include\nam_invadersB.h"

#include "Include\nam_scroll_squaresA.h"
#include "Include\nam_scroll_squaresB.h"

// #include "Include\nam_scrollFX_arrowsA.h"
// #include "Include\nam_scrollFX_arrowsB.h"

#include "Include\nam_scroll_gridA.h"
#include "Include\nam_scroll_gridB.h"

// 1026#include "Include\nam_paletteFX.h"

#include "Include\nam_BigText.h"

#define	PLASMA16_POS_X						8
#define	PLASMA16_POS_Y						4

#define	TILESET_FIRE_CHUNKS_ZX				0
#define	TILESET_CHUNKS_FONT_INVADERS		1
#define	TILESET_SCROLLER_FX					2
#define	TILESET_BIG_FONT_RHOMBUS			3

// Паттерн - условное название квадрата из 4 реальных паттернов
#define MUS_PATTERN							4*192
// Bar - реальный паттерн, 1/4 квадрата.
#define MUS_BAR								192
#define MUS_HALF_BAR						96
#define MUS_QUARTER_BAR						48

#pragma bss-name (push,"ZEROPAGE")

unsigned char bigTextX, bigTextY;

unsigned char pal_i, fr, i, spr, sq_scroll_pos, imsb, scrollRow;
unsigned int scrollPage;
unsigned char from_x;

unsigned int frame, musCheckpoint;

unsigned char p, fx, fy, bright, to_bright;
unsigned int gfrm;

static unsigned char fire_array[256]={};

unsigned int muspos = 0;
unsigned int fxFrame = 0;
unsigned char scrSwap = 0;
unsigned char frm = 0;
unsigned char xa = 0;
unsigned char ya = 0;
unsigned char za = 0;
unsigned char xya = 0;
unsigned char colorAdd = 0;
unsigned char xx = 0;
unsigned char yy = 0;
unsigned char xy = 0;
unsigned char buffAdr = 0;
unsigned val = 0;

unsigned char palRoll = 0;
unsigned char scrollFXpos = 0;

unsigned char platforms[5*4] = {
// Platform title 1:
	0, 50, 30, 0, 0,
// 2 etc
	0, 190, 80, 0, 4,
	0, 50, 160, 0, 8,
	0, 200, 190, 0, 12
};

#pragma bss-name (pop);

unsigned char buffa[256];

#define OBJ_ID 					0
#define OBJ_X					1
#define OBJ_Y					2
#define OBJ_TIMER				3
#define OBJ_FRAME				4

#define OBJ_NULL				0
#define OBJ_ZX					1
#define OBJ_NES					2
#define OBJ_C64					3
#define OBJ_PC					4
#define OBJ_AMIGA				5
#define OBJ_ATARI				6
#define OBJ_BK					7
#define OBJ_OTHER				8

const unsigned char infoPage1[9][16] = {
	"CAFEPARTY 2019: ",
	"TRUE DEMOSCENE  ",
	"WEEKEND IN      ",
	"KAZAN, RUSSIA.  ",
	"MULTIPLATFORM   ",
	"DEMOPARTY AT    ",
	"25-27 OCTOBER   ",
	"NEWSKOOL AND    ", 
	"OLDSKOOL ENTRIES"
};

const unsigned char infoPage2[9][16] = {
	"UP TO 400 PPL!  ",
	"BBQ ZONE, HOME  ",
	"FOOD AND DRINKS,",
	"VIP LOUNGE FOR  ",
	"SCENERS WITH    ", 
	"PRODS, RETRO-   ", 
	"MUSEUM, CALM    ",
	"FOREST OUTDOOR, ",
	"CHEAP HOTEL.    "
};

const unsigned char infoPage3[9][16] = {
	"WARM, FRIENDLY  ",
	"AND WELCOMING   ",
	"ATHMOSPHERE,    ", 
	"GREAT PRIZES,   ",
	"SPECIAL GUESTS: ",
	"SCENE STARS.    ",
	"NON-STOP PARTY! ", 
	"REMOTE ENTRIES  ",
	"ARE ALLOWED!    "
};

const unsigned char features_attrs[6*8]={
	4, 5, 4, 5, 5, 1, 0, 0,
	4, 5, 5, 5, 4, 5, 5, 0,
	4, 5, 5, 5, 1, 0, 0, 0,
	4, 1, 5, 5, 0, 0, 0, 0,
	4, 5, 5, 5, 4, 5, 1, 0,
	4, 4, 5, 1, 5, 5, 1, 0
};

const unsigned char features1[32*2]={
	0xa5,0xa6,0x28,0x29,0x46,0x47,0x42,0x43,0xa4,0xa5,0x6a,0x6b,0x2a,0x2b,0x68,0x69,0x2e,0x2f,0x2e,0x2f,0x60,0x61,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0x00,
	0xa6,0xa4,0x38,0x39,0x56,0x57,0x52,0x53,0xa5,0xa6,0x7a,0x7b,0x3a,0x3b,0x78,0x79,0x3e,0x3f,0x3e,0x3f,0x70,0x71,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0x00
};

const unsigned char features2[32*2]={
	0xa6,0xa4,0x4e,0x4f,0x26,0x27,0x6a,0x6b,0x6a,0x6b,0x46,0x47,0x80,0x81,0x2e,0x2f,0xa9,0xaa,0x26,0x27,0x6e,0x6f,0x2c,0x2d,0x46,0x47,0x62,0x63,0xa9,0xaa,0xa8,0x00,
	0xa4,0xa5,0x5e,0x5f,0x36,0x37,0x7a,0x7b,0x7a,0x7b,0x56,0x57,0x90,0x91,0x3e,0x3f,0xa8,0xa9,0x36,0x37,0x7e,0x7f,0x3c,0x3d,0x56,0x57,0x72,0x73,0xa8,0xa9,0xaa,0x00
};

const unsigned char features3[32*2]={
	0xa4,0xa5,0x6a,0x6b,0x2e,0x2f,0x4e,0x4f,0x46,0x47,0x60,0x61,0x26,0x27,0x68,0x69,0x6a,0x6b,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0xaa,0x00,
	0xa5,0xa6,0x7a,0x7b,0x3e,0x3f,0x5e,0x5f,0x56,0x57,0x70,0x71,0x36,0x37,0x78,0x79,0x7a,0x7b,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0xaa,0xa8,0xa9,0x00
};

const unsigned char features4[32*2]={
	0xb9,0xb8,0x2c,0x2d,0x00,0x49,0xb9,0xb8,0x6a,0x6b,0x2e,0x2f,0x6c,0x6d,0x6a,0x6b,0xb4,0xb6,0xb5,0xb4,0xb6,0xb5,0xb4,0xb5,0xb4,0xb6,0xb5,0xb4,0xb6,0xb5,0xb4,0x00,
	0xb7,0xb9,0x3c,0x3d,0x58,0x59,0xb7,0xb9,0x7a,0x7b,0x3e,0x3f,0x7c,0x7d,0x7a,0x7b,0xb6,0xb5,0xb4,0xb6,0xb5,0xb4,0xb6,0xb4,0xb6,0xb5,0xb4,0xb6,0xb5,0xb4,0xb6,0x00
};

const unsigned char features5[32*2]={
	0xb7,0xb9,0x62,0x63,0x6e,0x6f,0x6c,0x6d,0x2c,0x2d,0x62,0x63,0x62,0x63,0x68,0x69,0xb5,0xb4,0x26,0x27,0x68,0x69,0x2e,0x2f,0x26,0x27,0xb4,0xb6,0xb5,0xb4,0xb6,0x00,
	0xb8,0xb7,0x72,0x73,0x7e,0x7f,0x7c,0x7d,0x3c,0x3d,0x72,0x73,0x72,0x73,0x78,0x79,0xb4,0xb6,0x36,0x37,0x78,0x79,0x3e,0x3f,0x36,0x37,0xb6,0xb5,0xb4,0xb6,0xb5,0x00
};

const unsigned char features6[32*2]={
	0xb8,0xb7,0x04,0x05,0xb7,0xb9,0x6a,0x6b,0x6c,0x6d,0x2e,0x2f,0x64,0x65,0xb9,0xa7,0x44,0x45,0x62,0x63,0x6c,0x6d,0x2e,0x2f,0x4c,0x00,0xb6,0xb5,0xb4,0xb6,0xb5,0x00,
	0xb9,0xb8,0x14,0x15,0xb8,0xb7,0x7a,0x7b,0x7c,0x7d,0x3e,0x3f,0x74,0x75,0xb7,0xac,0x54,0x55,0x72,0x73,0x7c,0x7d,0x3e,0x3f,0x5c,0x5d,0xb5,0xb4,0xb6,0xb5,0xb4,0x00
};

const unsigned char sinTbl1[]={4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2};
const unsigned char sinTbl2[]={12,15,18,20,22,23,24,24,23,22,20,17,14,11,9,6,4,2,1,0,0,1,3,5,7,10,13,16,19,21,23,24,24,24,23,21,19,16,13,10,7,5,3,1,0,0,1,2,4,6,9,11,14,17,20,22,23,24,24,23,22,20,18,15,12,9,6,4,2,1,0,0,1,2,4,7,10,13,15,18,20,22,23,24,24,23,21,19,17,14,11,8,5,3,1,0,0,0,1,3,5,8,11,14,17,19,21,23,24,24,23,22,20,18,15,13,10,7,4,2,1,0,0,1,2,4,6,9,12,15,18,20,22,23,24,24,23,22,20,17,14,11,9,6,4,2,1,0,0,1,3,5,7,10,13,16,19,21,23,24,24,24,23,21,19,16,13,10,7,5,3,1,0,0,1,2,4,6,9,11,14,17,20,22,23,24,24,23,22,20,18,15,12,9,6,4,2,1,0,0,1,2,4,7,10,13,15,18,20,22,23,24,24,23,21,19,17,14,11,8,5,3,1,0,0,0,1,3,5,8,11,14,17,19,21,23,24,24,23,22,20,18,15,13,10,7,4,2,1,0,0,1,2,4,6,9};
const unsigned char sinTbl3[]={8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6};
const unsigned char twisterSin[]={63,63,63,63,63,63,63,63,63,63,63,63,63,62,62,62,62,61,61,61,60,60,59,59,59,58,58,57,57,56,56,55,55,54,53,53,52,52,51,50,50,49,48,48,47,46,46,45,44,44,43,42,41,41,40,39,38,37,37,36,35,34,34,33,32,31,30,30,29,28,27,27,26,25,24,23,23,22,21,20,20,19,18,18,17,16,16,15,14,14,13,12,12,11,11,10,9,9,8,8,7,7,6,6,5,5,5,4,4,3,3,3,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,5,6,6,7,7,8,8,9,9,10,11,11,12,12,13,14,14,15,16,16,17,18,18,19,20,20,21,22,23,23,24,25,26,27,27,28,29,30,30,31,32,33,34,34,35,36,37,37,38,39,40,41,41,42,43,44,44,45,46,46,47,48,48,49,50,50,51,52,52,53,53,54,55,55,56,56,57,57,58,58,59,59,59,60,60,61,61,61,62,62,62,62,63,63,63,63,63,63,63,63,63,63,63,63};
const unsigned char twisterData[]={0,0,0,0,0,16,16,16,16,16,16,16,0,0,0,0,0,0,0,0,0,16,16,16,16,15,15,15,0,0,0,0,0,0,0,0,1,0,15,15,15,15,14,14,0,0,0,0,0,0,0,0,1,0,15,14,14,14,14,13,0,0,0,0,0,0,0,1,1,2,0,14,14,13,13,12,0,0,0,0,0,0,0,1,2,2,0,13,13,13,12,12,0,0,0,0,0,0,0,1,2,2,3,0,13,12,12,11,11,0,0,0,0,0,0,2,2,3,3,0,12,12,11,11,10,0,0,0,0,0,0,2,3,3,4,4,0,11,11,10,10,0,0,0,0,0,0,3,3,4,4,5,0,11,10,10,9,0,0,0,0,0,0,0,4,4,5,5,5,0,10,10,9,0,0,0,0,0,0,0,4,5,5,6,6,0,10,9,9,0,0,0,0,0,0,0,5,6,6,6,6,7,0,9,0,0,0,0,0,0,0,0,6,6,7,7,7,7,0,9,0,0,0,0,0,0,0,0,7,7,7,8,8,8,8,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,0,0,0,0,0};
const unsigned char twisterSinX[]={16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,13,13,13,13,13,13,12,12,12,12,12,12,11,11,11,11,11,11,10,10,10,10,10,9,9,9,9,9,8,8,8,8,8,7,7,7,7,7,6,6,6,6,6,5,5,5,5,5,5,4,4,4,4,4,4,3,3,3,3,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,7,7,7,7,7,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16};

const unsigned char twisterChunks[]={
	0, 0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,	0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0, 0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0, 0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,	0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0, 0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

#define rotorColor0 0x8b
#define rotorColor1 0x96

const unsigned char rotorData[]={

rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,
rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,
rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,
rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,

rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,
rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,
rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,
rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,

rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,
rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,
rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,
rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1,

rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,
rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,
rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,
rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0, rotorColor1,rotorColor1,rotorColor1,rotorColor1, rotorColor0,rotorColor0,rotorColor0,rotorColor0,
};


const unsigned char string_we_like_to[32*1]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6a,0x6b,0xd7,0xa0,0xa1,0xa2,0xa3,0xdc,0xbb,0xbc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char string_invite_you_to[32*1]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff
};

const unsigned int attr_tbl1[16]={ 0x23d2,0x23d3,0x23d4,0x23d5,0x23d6,0x23d7,0x27d0,0x27d1,0x27d2,0x27d3,0x27d4,0x27d5,0x27d6,0x27d7,0x23d0,0x23d1 };
const unsigned int attr_tbl2[16]={ 0x23d3,0x23d4,0x23d5,0x23d6,0x23d7,0x27d0,0x27d1,0x27d2,0x27d3,0x27d4,0x27d5,0x27d6,0x27d7,0x23d0,0x23d1,0x23d2 };
const unsigned int attr_tbl3[16]={ 0x23d4,0x23d5,0x23d6,0x23d7,0x27d0,0x27d1,0x27d2,0x27d3,0x27d4,0x27d5,0x27d6,0x27d7,0x23d0,0x23d1,0x23d2,0x23d3 };

const unsigned char restoreBGscrollGrid[64*4]={
	0x00,0x02,0x32,0x22,0x33,0x0c,0x34,0x35,0x36,0x10,0x37,0x38,0x39,0x14,0x3a,0x3b,0x3c,0x15,0x3d,0x14,0x3e,0x11,0x3f,0x40,0x41,0x0d,0x42,0x43,0x44,0x09,0x45,0x04,
	0x00,0x07,0x00,0x02,0x00,0x05,0x08,0x00,0x00,0x03,0x06,0x00,0x00,0x01,0x04,0x00,0x00,0x01,0x02,0x00,0x00,0x03,0x04,0x00,0x00,0x05,0x06,0x00,0x00,0x07,0x08,0x00,

	0x4c,0x2c,0x4d,0x07,0x08,0x00,0x00,0x05,0x06,0x00,0x00,0x03,0x04,0x00,0x00,0x01,0x07,0x00,0x00,0x00,0x4e,0x00,0x00,0x08,0x03,0x00,0x00,0x06,0x01,0x00,0x4f,0x50,
	0x51,0x3c,0x3d,0x52,0x53,0x54,0x55,0x10,0x56,0x57,0x58,0x0c,0x59,0x1e,0x5a,0x09,0x09,0x1e,0x0a,0x09,0x0c,0x0b,0x0e,0x0d,0x10,0x0f,0x12,0x11,0x14,0x13,0x16,0x15,

	0x44,0x09,0x45,0x04,0x03,0x00,0x00,0x06,0x05,0x00,0x00,0x08,0x07,0x00,0x00,0x00,0x5d,0x00,0x00,0x01,0x06,0x00,0x00,0x03,0x08,0x00,0x00,0x05,0x00,0x02,0x32,0x22,
	0x5e,0x5f,0x60,0x0d,0x46,0x47,0x48,0x11,0x49,0x61,0x62,0x15,0x4c,0x20,0x63,0x20,0x20,0x23,0x21,0x20,0x15,0x24,0x25,0x14,0x11,0x19,0x1a,0x10,0x0d,0x26,0x27,0x0c,

	0x01,0x00,0x4f,0x50,0x64,0x15,0x3d,0x65,0x66,0x11,0x3f,0x40,0x67,0x0d,0x42,0x0c,0x68,0x0c,0x34,0x69,0x36,0x10,0x37,0x38,0x6a,0x14,0x3a,0x6b,0x4c,0x2c,0x4d,0x07,
	0x00,0x04,0x01,0x00,0x00,0x06,0x03,0x00,0x00,0x08,0x05,0x00,0x00,0x00,0x6c,0x00,0x00,0x08,0x07,0x00,0x00,0x06,0x05,0x00,0x00,0x04,0x03,0x00,0x00,0x02,0x01,0x00
};

const unsigned char restoreBGscrollSquares[64*4]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x6d,0x6d,0x00,0x00,0x6e,0x6f,0x00,0x00,0x70,0x71,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x71,0x00,0x00,0x6e,0x6f,0x00,0x00,0x6d,0x6d,0x00,
	0x00,0x6d,0x6d,0x00,0x00,0x6d,0x72,0x00,0x00,0x6d,0x73,0x00,0x00,0x74,0x75,0x00,0x00,0x76,0x00,0x00,0x00,0x77,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x00,0x00,0x00,0x76,0x00,0x00,0x00,0x74,0x75,0x00,0x00,0x6d,0x73,0x00,0x00,0x6d,0x72,0x00,0x00,0x6d,0x6d,0x00,
	0x00,0x6d,0x6d,0x00,0x00,0x6d,0x72,0x00,0x00,0x6d,0x73,0x00,0x00,0x6d,0x78,0x00,0x00,0x6d,0x00,0x00,0x00,0x72,0x00,0x00,0x00,0x79,0x00,0x00,0x00,0x7a,0x00,0x00,
	0x00,0x7a,0x00,0x00,0x00,0x79,0x00,0x00,0x00,0x72,0x00,0x00,0x00,0x6d,0x00,0x00,0x00,0x6d,0x78,0x00,0x00,0x6d,0x73,0x00,0x00,0x6d,0x72,0x00,0x00,0x6d,0x6d,0x00
};

unsigned char pad;

const unsigned char pal_part1[16]={ 0x0f,0x05,0x2c,0x10,0x0f,0x30,0x10,0x06,0x0f,0x0f,0x10,0x0f,0x0f,0x0f,0x0f,0x0f };
const unsigned char pal_water[16]={ 0x0f,0x0c,0x21,0x1c,0x0f,0x0b,0x1b,0x2b,0x0f,0x2d,0x20,0x10,0x0f,0x3d,0x3d,0x0f };
const unsigned char pal_scrollerFX[16]={ 0x0f,0x0f,0x03,0x02,0x0f,0x0f,0x28,0x11,0x0f,0x07,0x17,0x27,0x0f,0x0b,0x1b,0x2b };
const unsigned char pal_bigText[16]={ 0x0f,0x16,0x27,0x0f,0x0f,0x01,0x1c,0x2c,0x0f,0x05,0x15,0x25,0x0f,0x0f,0x0f,0x0f };
const unsigned char pal_wewill[16]={ 0x0f,0x01,0x03,0x10,0x0f,0x30,0x05,0x10,0x0f,0x06,0x08,0x27,0x0f,0x27,0x0c,0x02 };

const unsigned char bus_conflict[4]={ 0x00,0x01,0x02,0x03 };

const unsigned char logo_bottom1_BG[4*4]={
	0xb0,0xb1,0xb2,0xb3,
	0xc0,0xc1,0xc2,0xc3,
	0xd0,0xd1,0xd2,0xd3,
	0xe0,0xe1,0xe2,0xe3
};

const unsigned char logo_bottom2_BG[4*4]={
	0xb4,0xb5,0xb6,0xb7,
	0xc4,0xc5,0xc6,0xc7,
	0xd4,0xd5,0xd6,0xd7,
	0xe4,0xe5,0xe6,0xe7
};

const unsigned char logo_bottom[]={
	  0,  0,0xb8,1,
	  8,  0,0xb9,1,
	 16,  0,0xba,1,
	 24,  0,0xbb,1,
	 32,  0,0xbc,1,
	 40,  0,0xbd,1,
	 48,  0,0xbe,1,
	 56,  0,0xbf,1,
	  0,  8,0xc8,1,
	  8,  8,0xc9,1,
	 16,  8,0xca,1,
	 24,  8,0xcb,1,
	 32,  8,0xcc,1,
	 40,  8,0xcd,1,
	 48,  8,0xce,1,
	 56,  8,0xcf,1,
	  0, 16,0xd8,1,
	  8, 16,0xd9,1,
	 16, 16,0xda,1,
	 24, 16,0xdb,1,
	 32, 16,0xdc,1,
	 40, 16,0xdd,1,
	 48, 16,0xde,1,
	 56, 16,0xdf,1,
	  0, 24,0xe8,1,
	  8, 24,0xe9,1,
	 16, 24,0xea,1,
	 24, 24,0xeb,1,
	 32, 24,0xec,1,
	 40, 24,0xed,1,
	 48, 24,0xee,1,
	 56, 24,0xef,1,
	128
};

const unsigned char logo_title[]={
	  0,  0,0xf0,1,
	  8,  0,0xf1,1,
	 16,  0,0xf2,1,
	 24,  0,0xf3,1,
	 32,  0,0xf4,1,
	 40,  0,0xf5,1,
	 48,  0,0xf6,1,
	 56,  0,0xf7,1,
	  0,  8,0xf8,1,
	  8,  8,0xf9,1,
	 16,  8,0xfa,1,
	 24,  8,0xfb,1,
	 32,  8,0xfc,1,
	 40,  8,0xfd,1,
	 48,  8,0xfe,1,
	 56,  8,0xff,1,
	128
};

const unsigned char pal_Invites[16]={ 0x0f,0x0f,0x30,0x0f,0x0f,0x1a,0x27,0x24,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f };
const unsigned char pal_Platforms[16]={ 0x0f,0x1b,0x2b,0x3b,0x0f,0x16,0x26,0x36,0x0f,0x14,0x24,0x34,0x0f,0x17,0x27,0x37 };

const unsigned char platforms_0_data[]={

	-32,  0,0xec,0,
	-24,  0,0xe9,1,
	-16,  0,0xde,2,
	- 8,  0,0xdc,3,
	  0,  0,0xed,0,
	  8,  0,0xeb,1,
	 16,  0,0xee,2,
	 24,  0,0xe6,3,
	128

};

const unsigned char platforms_1_data[]={

	-28,  0,0xdf,0,
	-20,  0,0xda,1,
	-12,  0,0xe6,2,
	- 4,  0,0xe2,3,
	  4,  0,0xdc,0,
	 12,  0,0xe8,1,
	 20,  0,0xe6,2,
	128

};

const unsigned char platforms_2_data[]={

	-12,  0,0xdc,0,
	- 4,  0,0xd6,1,
	  4,  0,0xd4,2,
	128

};

const unsigned char platforms_3_data[]={

	-32,  0,0xe9,1,
	-24,  0,0xdc,2,
	-16,  0,0xfe,3,
	- 8,  0,0xe9,0,
	  0,  0,0xe2,1,
	  8,  0,0xdc,2,
	 16,  0,0xe8,3,
	 24,  0,0xd8,0,
	128

};

const unsigned char platforms_4_data[]={

	-19,  0,0xda,3,
	-11,  0,0xe6,0,
	- 3,  0,0xe2,1,
	  5,  0,0xe0,2,
	 13,  0,0xda,3,
	128

};

const unsigned char platforms_5_data[]={

	-19,  0,0xda,0,
	-11,  0,0xed,1,
	- 3,  0,0xda,2,
	  5,  0,0xeb,3,
	 13,  0,0xe2,0,
	128

};

const unsigned char platforms_6_data[]={

	-28,  0,0xdb,0,
	-20,  0,0xe4,1,
	-12,  0,0xd0,2,
	- 4,  0,0xd0,3,
	  4,  0,0xd1,0,
	 12,  0,0xd1,1,
	 20,  0,0xe6,2,
	128

};

const unsigned char platforms_7_data[]={

	-32,  0,0xda,0,
	-24,  0,0xe7,1,
	-16,  0,0xdd,2,
	- 4,  0,0xe8,3,
	  4,  0,0xed,0,
	 12,  0,0xe1,1,
	 20,  0,0xde,2,
	 28,  0,0xeb,3,
	128

};

const unsigned char wewill_1_data[]={

	-28,- 4,0xf0,0,
	-20,- 4,0xde,1,
	- 4,- 4,0xf0,2,
	  4,- 4,0xe2,3,
	 12,- 4,0xe5,0,
	 20,- 4,0xe5,1,
	128

};

const unsigned char wewill_2_data[]={

	-40,- 4,0xf0,1,
	-32,- 4,0xda,2,
	-24,- 4,0xe2,3,
	-16,- 4,0xed,0,
	  0,- 4,0xd4,1,
	 16,- 4,0xf2,2,
	 24,- 4,0xe8,3,
	 32,- 4,0xee,1,
	128

};


const unsigned char* const platforms_list[]={
	platforms_0_data,
	platforms_1_data,
	platforms_2_data,
	platforms_3_data,
	platforms_4_data,
	platforms_5_data,
	platforms_6_data,
	platforms_7_data,
	wewill_1_data,
	wewill_2_data
};

const unsigned int sineTableAtoB[48]={
0, 0, 1, 2, 4, 7, 10, 13, 17, 22, 27, 33, 39, 45, 52, 59, 
66, 74, 81, 90, 98, 106, 115, 123, 132, 140, 149, 157, 165, 174, 181, 
189, 196, 203, 210, 216, 222, 228, 233, 238, 242, 245, 248, 251, 253, 254, 
255, 255
};

const unsigned int sineTableTextBobbling[32]={
0, 0, 0, 0, 1, 2, 2, 3, 4, 5, 6, 6, 7, 7, 7, 8, 
7, 7, 7, 6, 6, 5, 4, 3, 2, 2, 1, 0, 0, 0, 0, 
0
};


void cnrom_set_bank(unsigned char bank)
{
	unsigned char *ptr;
	bank&=3;
	ptr=(unsigned char*)&bus_conflict[bank];
	*ptr=bank;
}

void _pal_fade_to(unsigned to)
{
	while(bright!=to)
	{
		delay(4);
		if(bright<to) ++bright; else --bright;
		pal_bright(bright);
	}
} 

/*
void showmuspos(void)
{
	unsigned char muspos_l, muspos_h;

	ppu_off();
    
    pal_col(0,0x09);
	pal_col(1,0x30);
    pal_col(2,0x19);
    pal_col(3,0x29);
    
	vram_adr(NAMETABLE_A);
	vram_fill(0,1024);

	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	ppu_on_all();

	muspos = get_mus_pos();
	muspos_h = muspos / 256;
	muspos_l = muspos & 255;
	
	fire_array[0] = 0xD0 + (muspos_h / 16);
	fire_array[1] = 0xD0 + (muspos_h & 15);
	fire_array[2] = 0xD0 + (muspos_l / 16);
	fire_array[3] = 0xD0 + (muspos_l & 15);
	
	ppu_wait_nmi();
	scroll(0,0);
	clear_vram_buffer();
	multi_vram_buffer_horz((unsigned char*) fire_array, 4, NAMETABLE_A + 64);
	ppu_wait_nmi();
	
	while(1){}
}
*/

#include "Include\sceneZXloading.h"

#define twLines 6
#define twTextDelay 192
unsigned char x, y, twisterAdr, yyy, x1, x2, y1, chunk, chunkAdr, yfrom, yto, tadr, tqty, txtadr;
unsigned int twTextTimer = 0;
unsigned int twTextAdr = 0;


void fxTwisterSetup() {

	ppu_off();
	
	cnrom_set_bank(TILESET_FIRE_CHUNKS_ZX);
	bank_bg(1);
	
	vram_adr(NAMETABLE_A);
	vram_fill(0,1024);
	vram_adr(NAMETABLE_B);
	vram_fill(0,1024);

	pal_col(0,0x0D);
	pal_col(1,0x20);
	pal_col(2,0x21);
	pal_col(3,0x13);

	ppu_on_all();
	
	fxFrame = 0;
}

/*
NEWSKOOL
OLDSKOOL
DEMO
INTRO
GRAPHICS
MUSIC
GAMES
REALITME
PROCEDURAL
TEXTMODE
WILD
BBQ COMPO : )
*/

const unsigned char twisterText[] = {
	0, 3*32+8,
	//NEWSKOOL
	8, txtS('N'),txtS('E'),txtS('W'),txtS('S'),txtS('K'),txtS('O'),txtS('O'),txtS('L'),

	1, 3*32+20,
	//OLDSKOOL
	8, txtS('O'),txtS('L'),txtS('D'),txtS('S'),txtS('K'),txtS('O'),txtS('O'),txtS('L'),

	2, 3*32+4,
	//DEMO
	4, txtS('D'),txtS('E'),txtS('M'),txtS('O'),

	3, 3*32+16,
	//INTRO
	5, txtS('I'),txtS('N'),txtS('T'),txtS('R'),txtS('O'),

	//--------------------------------
	
	0, 3*32+16,
	//GRAPHICS
	8, txtS('G'),txtS('R'),txtS('A'),txtS('P'),txtS('H'),txtS('I'),txtS('C'),txtS('S'),

	1, 3*32+4,
	//MUSIC
	5, txtS('M'),txtS('U'),txtS('S'),txtS('I'),txtS('C'),

	2, 3*32+20,
	//GAMES
	5, txtS('G'),txtS('A'),txtS('M'),txtS('E'),txtS('S'),

	3, 3*32+8,
	//REALITME
	8, txtS('R'),txtS('E'),txtS('A'),txtS('L'),txtS('I'),txtS('T'),txtS('M'),txtS('E'),

	//--------------------------------

	0, 3*32+8,
	//PROCEDURAL
	10, txtS('P'),txtS('R'),txtS('O'),txtS('C'),txtS('E'),txtS('D'),txtS('U'),txtS('R'),txtS('A'),txtS('L'),

	1, 3*32+20,
	//TEXTMODE
	8, txtS('T'),txtS('E'),txtS('X'),txtS('T'),txtS('M'),txtS('O'),txtS('D'),txtS('E'),

	2, 3*32+4,
	//WILD
	4, txtS('W'),txtS('I'),txtS('L'),txtS('D'),

	3, 3*32+16,
	//BBQ COMPO : )
	11, txtS('B'),txtS('B'),txtS('Q'),0x00,txtS('C'),txtS('O'),txtS('M'),txtS('P'),txtS('O'),0x00,0xf6,
	
	//--------------------------------
	
	0, 3*32+16,
	//AND
	3, txtS('A'),txtS('N'),txtS('D'),

	1, 3*32+4,
	//SO
	2, txtS('S'),txtS('O'),

	2, 3*32+20,
	//MUCH
	4, txtS('M'),txtS('U'),txtS('C'),txtS('H'),

	3, 3*32+8,
	//MORE!
	5, txtS('M'),txtS('O'),txtS('R'),txtS('E'),0xf6,
    255 //no text code
    
};


/*
для каждого frm мы строим 6 строк
1б - длина сообщения
1б - номер frm
1б - адрес
Xб - само сообщение
*/

void fxTwisterFrame(frm) {
	memfill32(fire_array, 0, twLines);
	yfrom = frm * twLines;
	yto = yfrom + twLines;
	yyy = 0;
	for (y = yfrom; y < yto; y++) {
		x1 = xa + 6*y;
		x2 = za + 6*y;
		y1 = ya + y;
		chunkAdr = 32 * (twisterSin[y1] / 16);
		twisterAdr = (twisterSin[y1] & 15) * 16;
		buffAdr = yyy*32 + (twisterSinX[x1] + twisterSinX[x2]) / 2;
		for (x = 0; x < 16; x++) {
			chunk = twisterData[twisterAdr];
			fire_array[buffAdr] = twisterChunks[chunk + chunkAdr];
			buffAdr += 1;
			twisterAdr += 1;
		}
		yyy++;
	}
	
	tqty = 4;
	txtadr = twTextAdr;
    if (twisterText[txtadr] == 255) {
        return;
    }
    
	while (tqty > 0) {
		if (twisterText[txtadr] == frm) {
			tadr = twisterText[txtadr + 1];
			for (x = 0; x < twisterText[txtadr + 2]; x++) {
				fire_array[tadr] = twisterText[txtadr + 3 + x];
				tadr++;
			}
		}
		txtadr += twisterText[txtadr + 2] + 3;
		--tqty;
	}

}

void fxTwister(void) {
	set_nmi_user_call_on();
	set_nmi_user_vram_lines_qty(twLines);
	for (frm = 0; frm < 4; frm++) {
		if (scrSwap == 0) {
			scroll(0,0);
			fxTwisterFrame(frm);
			set_nmi_user_vram_adr(NAMETABLE_B + 64+32 + frm*32*twLines);
			ppu_wait_nmi();
		} else {
			scroll(256,0);
			fxTwisterFrame(frm);
			set_nmi_user_vram_adr(NAMETABLE_A + 64+32 + frm*32*twLines);
			ppu_wait_nmi();
		}
	}
	
    if (muspos >= twTextTimer) {
		twTextTimer += twTextDelay;
        twTextAdr = txtadr;
    }
	muspos = get_mus_pos();

	xa += 8;
	za += 12;
	ya += 4;
	scrSwap ^= 1;
}

//----------------------------------------------------------------------
#define plsmLines 5

void fxPlasmSetup(void) {
	ppu_off();
    
    pal_col(0,0x09);
    pal_col(2,0x19);
    pal_col(1,0x30);
    pal_col(3,0x29);
    
	vram_adr(NAMETABLE_A);
	vram_fill(0,2048);

	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	ppu_on_all();
	
	fxFrame = 0;
}

void fxPlasmFrame(frm) {
	buffAdr = 0;
	yfrom = frm * plsmLines;
	yto = frm * plsmLines + plsmLines;
	yy = ya + yfrom;
	for (y = yfrom; y < yto; y++) {
		xx = xa;
		xy = y + xya;
		for (x = 0; x < 32; x++) {
			fire_array[buffAdr] = 0x80 + ((colorAdd + sinTbl1[xx] + sinTbl2[yy] + sinTbl3[xy]) & 31);
			++buffAdr;
			++xx;
			++xy;
		}
		++yy;
	}

}

void fxPlasm(void) {
	for (frm = 0; frm < 6; frm++) {
        set_nmi_user_call_on();
        set_nmi_user_vram_lines_qty(plsmLines);
		if (scrSwap == 0) {
			scroll(0,0);
			fxPlasmFrame(frm);
            set_nmi_user_vram_adr(NAMETABLE_B + frm*32*plsmLines);
			ppu_wait_nmi();
		} else {
            scroll(256,0);
			fxPlasmFrame(frm);
            set_nmi_user_vram_adr(NAMETABLE_A + frm*32*plsmLines);
			ppu_wait_nmi();
		}

	}
	xa+=1;
	ya+=1;
	xya-=1;
	colorAdd += 1;
	scrSwap ^= 1;
    fxFrame++;
}
//----------------------------------------------------------------------

void chr_to_nametable(unsigned int nametable, unsigned char *src) {
unsigned char p;
	for (p=0;p<4;++p) {
		vram_adr((int) src+(p*256));
		vram_read(buffa, 256);
		vram_adr(nametable+(p*256));
		vram_write(buffa, 256);
	}
}

/*
BIG SCREEN
MASSIVE AUDIO
SEMINARS
DJ, VJ SETS
OUTDOOR AREA
1 STEP HOTEL
*/

void fxRotorSetup(void) {
	ppu_off();
    
	platforms[0]=9;
	platforms[1]=128;
	platforms[2]=120-16;

	platforms[5]=10;
	platforms[6]=128;
	platforms[7]=136-16;
	
	platforms[10]=0;
	platforms[15]=0;

	pal_clear();

    pal_col(2,0x01);
    pal_col(3,0x11);
//    pal_col(2,0x04);
//    pal_col(3,0x27);
    
	vram_adr(NAMETABLE_A);
	vram_fill(0,1024-24);
	vram_adr(NAMETABLE_B);
	vram_fill(0,1024-24);

	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	bank_bg(0);
	bank_spr(0);

	pal_spr(pal_Platforms);
	ppu_on_all();

	fxFrame = 0;
}

#define rotorLines 4
#define rotorSz rotorLines*32
unsigned char y, x;
unsigned int tx, ty;
unsigned int tdx, tdy, stx, sty;
unsigned char rtadr;

void fxRotorFrame() {

	buffAdr = 0;

	tdx = 4*(twisterSin[xya] - 16);
	tdy = 4*(twisterSin[(xya + 64) & 255] - 24);

	while (buffAdr < rotorSz) {
		stx = tx;
		sty = ty;
		for (x = 32; x > 0; --x) {
			rtadr = 16*(15&(ty/256)) + (15&(tx/256));
			fire_array[buffAdr] = rotorData[rtadr];
			tx += tdx;
			ty += tdy;
			++buffAdr;
		}
		tx = stx + tdy;
		ty = sty - tdx;
	}
}

unsigned char objPos, objY, objX, objTimer, objFrame, objID;
void showPlatforms(void) {
	for (i=0;i<4;++i)
	{
		objPos=i*5;
		objID=platforms[objPos+OBJ_ID];

		if (objID!=OBJ_NULL) {

			objX=platforms[objPos+OBJ_X];
			objY=platforms[objPos+OBJ_Y];
			objTimer=platforms[objPos+OBJ_TIMER];
			objFrame=platforms[objPos+OBJ_FRAME];

			spr=oam_meta_spr(objX, objY+sineTableTextBobbling[platforms[objPos+OBJ_FRAME]], spr, platforms_list[objID-1]);

			if (!objTimer)
				++objFrame;
			if (objFrame>31) objFrame=0;
			++objTimer;
			objTimer&=1;

			platforms[objPos+OBJ_Y]=objY;
			platforms[objPos+OBJ_TIMER]=objTimer;
			platforms[objPos+OBJ_FRAME]=objFrame;
		}
	}
}


void fxRotor(void) {
	
	tx = 128*twisterSin[xa];
	ty = 64*twisterSin[ya];

	for (frm = 0; frm < 6; frm++) {
        set_nmi_user_call_on();
        set_nmi_user_vram_lines_qty(rotorLines);
		if (scrSwap == 0) {
			scroll(0,0);
			fxRotorFrame();
			//gray_line();
		spr=0;	
		showPlatforms();
            set_nmi_user_vram_adr(NAMETABLE_B + 96 + frm*32*rotorLines);
			ppu_wait_nmi();
		} else {
            scroll(256,0);
			fxRotorFrame();
			//gray_line();
		spr=0;	
		showPlatforms();
            set_nmi_user_vram_adr(NAMETABLE_A + 96 + frm*32*rotorLines);
			ppu_wait_nmi();
		}
	}
	
	xa+=2;
	ya+=3;
	xya+=5;
	scrSwap ^= 1;
}


//----------------------------------------------------------------------------
void fxPlasm16Frame(frm) {  
unsigned char y, x, yfrom, yto;
	buffAdr = 0;
	yfrom = frm*3;
	yto = frm*3 + 3;
	yy = ya + yfrom;
	for (y = yfrom; y < yto; y++) {
		xx = xa;
		xy = y + xya;
		for (x = 0; x < 32; x++) {
			fire_array[buffAdr] = 0x80 + ((colorAdd + sinTbl1[xx] + sinTbl2[yy] + sinTbl3[xy]) & 15);
			buffAdr+=1;
			xx+=1;
			xy+=1;
		}
		yy+=1;
	}
}

void fxPlasm16(void) {

	for (frm = 0; frm < 8; frm++) {
		if (scrSwap == 0) {
			scroll(0,0);
			fxPlasm16Frame(frm);
//			gray_line();
			clear_vram_buffer();
			multi_vram_buffer_horz((unsigned char*) fire_array+0,16,NAMETABLE_B+frm*64+32+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			multi_vram_buffer_horz((unsigned char*) fire_array+32,16,NAMETABLE_B+frm*64+64+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			ppu_wait_nmi();
			scroll(256,0);
		} else {
			fxPlasm16Frame(frm);
//			gray_line();
			clear_vram_buffer();
			multi_vram_buffer_horz((unsigned char*) fire_array+0,16,NAMETABLE_A+frm*64+32+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			multi_vram_buffer_horz((unsigned char*) fire_array+32,16,NAMETABLE_A+frm*64+64+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			ppu_wait_nmi();
		}
//		split(rand8(),0);
//		gray_line();

	}
	xa+=1;
	ya+=1;
	xya-=1;
	colorAdd += 1;
	scrSwap ^= 1;
}

void plotfirehead(void){
unsigned char fx, rn;

	
	for(fx=0;fx<16;++fx){
		rn=rand8();
		if (rn>127) 
			fire_array[14*16+fx]=0x70+14;
		else
			fire_array[14*16+fx]=0x70+13;
	}

	for(fx=0;fx<16;++fx){
		rn=rand8();
		if (rn>127) 
			fire_array[15*16+fx]=0x70+15;
		else
			fire_array[15*16+fx]=0x70+14;
	}

}

void fireloop(void){
unsigned char fx, px;
	for(fx=0;fx<240;++fx){
		px=fire_array[fx];
		if (px==fire_array[fx+16])
			px=0x70;
		else{			
		px-=0x70;
		px+=fire_array[fx+16]-0x70;
		px=(px>>1)+0x70;
		}
		fire_array[fx]=px;
		
	}
	
}

void fxFire(void) {

		plotfirehead();
		fireloop();
		fireloop();

		clear_vram_buffer();
		for (fy=0;fy<4;++fy){
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+5*32+8+fy*32);
		}
		ppu_wait_nmi();

		clear_vram_buffer();
		for (fy=4;fy<8;++fy){
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+5*32+8+fy*32);
		}
		ppu_wait_nmi();

		clear_vram_buffer();
		for (fy=8;fy<12;++fy){
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+5*32+8+fy*32);
		}
		ppu_wait_nmi();

		clear_vram_buffer();
		for (fy=12;fy<16;++fy){
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+5*32+8+fy*32);
		}
		ppu_wait_nmi();
}

void setup_scene_water(void) {
unsigned char attr;
	ppu_off();
	vram_adr(NAMETABLE_A);
	vram_fill(0,1024-24);
	attr=(3 << 6) | (3 << 4) | (0 << 2) | (0 << 0);
	vram_fill(attr,24);
	vram_adr(NAMETABLE_B);
	vram_fill(0,1024-24);
	vram_fill(attr,24);

//	vram_adr(NAMETABLE_A+25*32);
//	vram_write(string_we_like_to,32);
//	vram_adr(NAMETABLE_B+25*32);
//	vram_write(string_we_like_to,32);
	pal_bg(pal_water);
	ppu_on_all();
}

void setup_scene_fire(void) {
	vram_adr(NAMETABLE_A);
	vram_fill(0,960);
	vram_adr(NAMETABLE_B);
	vram_fill(0,960);

	memfill((unsigned char*) fire_array, 0x70, 256);

	pal_col(1,0x06);
	pal_col(2,0x16);
	pal_col(3,0x28);

	scroll(0,0);
	ppu_on_all();
}

void setupRhombusFX(void) {
	ppu_off();
	cnrom_set_bank(TILESET_BIG_FONT_RHOMBUS);
	chr_to_nametable(NAMETABLE_A, nam_rhombus);
	pal_col(1,0x01);
	pal_col(2,0x19);
	pal_col(3,0x28);
	pal_col(5,0x00);
	pal_col(6,0x10);
	pal_col(7,0x30);
	scroll(0,0);
	ppu_on_all();
}

void setupGridFX(unsigned char color) {
	ppu_off();
	cnrom_set_bank(TILESET_SCROLLER_FX);
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_scroll_gridA);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_scroll_gridB);
	pal_bg(pal_scrollerFX);
	pal_spr(pal_scrollerFX);
	pal_col(2,color);
	ppu_on_all();
}

void setupSquaresFX(unsigned char color) {
	ppu_off();
	cnrom_set_bank(TILESET_SCROLLER_FX);
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_scroll_squaresA);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_scroll_squaresB);
	pal_bg(pal_scrollerFX);
	pal_spr(pal_scrollerFX);
	pal_col(2,color);
	ppu_on_all();
}

void setupInvadersFX(void) {
	ppu_off();
	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	bank_spr(0);
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_InvadersA);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_InvadersB);
	pal_bg(pal_scrollerFX);
	pal_spr(pal_Platforms);
	ppu_on_all();
}

void fxSetupFinalScreen(void) {
	ppu_off();
	cnrom_set_bank(TILESET_BIG_FONT_RHOMBUS);
	chr_to_nametable(NAMETABLE_A, nam_qr_A);
	chr_to_nametable(NAMETABLE_B, nam_qr_B);
	cnrom_set_bank(TILESET_SCROLLER_FX);
	bank_bg(1);
	pal_bg(pal_part1);
	pal_col(1,0x0f);
	pal_col(2,0x0f);
	pal_col(3,0x0f);
	pal_col(5,0x0f);
	pal_col(6,0x0f);
	pal_col(7,0x0f);
	ppu_on_all();
}

void fxPaletteRoll(void) {
	switch(palRoll) {
		case 0:
		pal_col(1,0x01);
		pal_col(2,0x19);
		pal_col(3,0x28);
		break;

		case 1:
		pal_col(1,0x19);
		pal_col(2,0x28);
		pal_col(3,0x01);
		break;

		case 2:
		pal_col(1,0x28);
		pal_col(2,0x01);
		pal_col(3,0x19);
		break;
	}
	++palRoll;
	if (palRoll>2) palRoll=0;
}

void fxScroll32(unsigned char* restore_array) {
		clear_vram_buffer();

		// Calculate page and address to restore BG
		if (from_x>5 && from_x<14){
			imsb=(from_x-6)<<2;
			scrollPage=NAMETABLE_B;
		}
		if (from_x<6){
			imsb=8+(from_x<<2);
			scrollPage=NAMETABLE_A;
		}
		if (from_x>13){
			imsb=(from_x-14)<<2;
			scrollPage=NAMETABLE_A;
		}
		// Restore BG
		scrollRow=from_x<<2;
		multi_vram_buffer_horz((unsigned char*) restore_array + scrollRow, 4, scrollPage+32*8+(imsb));
		scrollRow+=64;
		multi_vram_buffer_horz((unsigned char*) restore_array + scrollRow, 4, scrollPage+32*9+(imsb));
		scrollRow+=64;
		multi_vram_buffer_horz((unsigned char*) restore_array + scrollRow, 4, scrollPage+32*10+(imsb));
		scrollRow+=64;
		multi_vram_buffer_horz((unsigned char*) restore_array + scrollRow, 4, scrollPage+32*11+(imsb));

		if (from_x>4 && from_x<13){
			imsb=(from_x-5)<<2;
			scrollPage=NAMETABLE_B;
		}
		if (from_x<5){
			imsb=12+(from_x<<2);
			scrollPage=NAMETABLE_A;
		}
		if (from_x>12){
			imsb=(from_x-13)<<2;
			scrollPage=NAMETABLE_A;
		}
		scrollRow=0;
		multi_vram_buffer_horz((unsigned char*) logo_bottom1_BG + scrollRow, 4, scrollPage+32*8+(imsb));
		multi_vram_buffer_horz((unsigned char*) logo_bottom1_BG + scrollRow+4, 4, scrollPage+32*9+(imsb));
		multi_vram_buffer_horz((unsigned char*) logo_bottom1_BG + scrollRow+8, 4, scrollPage+32*10+(imsb));
		multi_vram_buffer_horz((unsigned char*) logo_bottom1_BG + scrollRow+12, 4, scrollPage+32*11+(imsb));

		if (from_x>3 && from_x<12){
			imsb=(from_x-4)<<2;
			scrollPage=NAMETABLE_B;
		}
		if (from_x<4){
			imsb=16+(from_x<<2);
			scrollPage=NAMETABLE_A;
		}
		if (from_x>11){
			imsb=(from_x-12)<<2;
			scrollPage=NAMETABLE_A;
		}
		scrollRow=0;
		multi_vram_buffer_horz((unsigned char*) logo_bottom2_BG + scrollRow, 4, scrollPage+32*8+(imsb));
		multi_vram_buffer_horz((unsigned char*) logo_bottom2_BG + scrollRow+4, 4, scrollPage+32*9+(imsb));
		multi_vram_buffer_horz((unsigned char*) logo_bottom2_BG + scrollRow+8, 4, scrollPage+32*10+(imsb));
		multi_vram_buffer_horz((unsigned char*) logo_bottom2_BG + scrollRow+12, 4, scrollPage+32*11+(imsb));

		one_vram_buffer(0,attr_tbl1[from_x]);
		one_vram_buffer((1 << 6) | (1 << 4) | (1 << 2) | (1 << 0),attr_tbl2[from_x]);
		one_vram_buffer((1 << 6) | (1 << 4) | (1 << 2) | (1 << 0),attr_tbl3[from_x]);

		scroll(sq_scroll_pos<<5, 0);

		spr=0;
		spr=oam_meta_spr(12*8,12*8-1,spr,logo_bottom);
		spr=oam_meta_spr(12*8,16*8-1,spr,logo_title);

		ppu_wait_nmi();

		if (!(fr&1)) {
			++sq_scroll_pos;
			++from_x;
		}

		++fr;

		if (fr>29) {
			fr=0;
		}

		if (from_x>15) sq_scroll_pos=from_x=0;
		
};

void fxInvaders(void) {
	scroll(sq_scroll_pos*96, 0);
	ppu_wait_nmi();
	if (fr>23) {
		++sq_scroll_pos;
		++from_x;
		fr=0;
	}

	++fr;

	if (fr>29) {
		fr=0;
	}

	if (from_x>15) sq_scroll_pos=from_x=0;
	spr=0;	
	showPlatforms();
	oam_hide_rest(spr);
};


unsigned char findsym(unsigned char substr){
unsigned char fs=0;
	
	while(tbl_ascii[fs]!=substr) ++fs;
	return fs;
}

void setupBigTextPage(const unsigned char *page, unsigned char setattr) {
unsigned char x, y, sym;
unsigned int pos;
const unsigned char *bigSymbol;

	ppu_off();
	cnrom_set_bank(TILESET_BIG_FONT_RHOMBUS);
	bank_spr(0);
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_BigText);
	vram_adr(NAMETABLE_B);
	vram_fill(0, 960);
	vram_adr(NAMETABLE_B+960);
	vram_fill((1 << 6) | (1 << 4) | (1 << 2) | (1 << 0), 64);
	pal_bg(pal_bigText);
	pal_spr(pal_bigText);
//	pal_spr(pal_scrollerFX);

	for (y=0;y<9;++y) {
		pos=NAMETABLE_B+3*32+1+(y*96);
		for (x=0;x<16;++x) {
			sym=*page++;
			if (sym!=' ') {
				bigSymbol=tbl_alphabet[findsym(sym)];
				vram_adr(pos);
				vram_write(bigSymbol, 2);
				vram_adr(pos+32);
				vram_write(bigSymbol+2, 2);
				if (sym=='.' || sym==',' || sym=='-' || sym=='!' || sym==':' || sym=='"')
					pos+=1;
				else
					pos+=2;
			}
			else
				pos+=1;
		}
	}


	if (setattr==1) {
		vram_adr(NAMETABLE_B+0x03c0);
		vram_fill((2 << 6) | (2 << 4) | (2 << 2) | (2 << 0),8);
		vram_fill((1 << 6) | (1 << 4) | (2 << 2) | (2 << 0),8);
	};

	if (setattr==2) {
		vram_adr(NAMETABLE_B+0x03c0);
		vram_fill((2 << 6) | (2 << 4) | (2 << 2) | (2 << 0),8);
		vram_fill((1 << 6) | (1 << 4) | (2 << 2) | (2 << 0),8);
	};

	if (setattr==3) {
		vram_adr(NAMETABLE_B+0x03e8);
		vram_fill((2 << 6) | (2 << 4) | (2 << 2) | (2 << 0),8);
	};

	scroll(0,0);
	oam_spr(0,8,0x8c,3,0);
	bigTextX=0;
	bigTextY=0;
	ppu_on_all();

};

void fxBigPage(void) {
	scroll(0,0);
	++gfrm;
	gfrm&=3;
	if (!gfrm) ++fx;
	fx&=1;
	if (fx) {
		pal_col(1,0x16);
		pal_col(2,0x27);
	}
	else
	{
		pal_col(2,0x16);
		pal_col(1,0x27);
	}
	ppu_wait_nmi();
	if (bigTextX<47){
		split(sineTableAtoB[bigTextX],0);
	}
	else
		split(255-8+sineTableTextBobbling[bigTextY],0);
		
	if (bigTextX<47) ++bigTextX;
	++bigTextY;
	if (bigTextY>31) bigTextY=0;
}

/*
void setupArrowsFX(void) {
	ppu_off();
	cnrom_set_bank(TILESET_BIG_FONT_RHOMBUS);

	chr_to_nametable(NAMETABLE_A, nam_scrollFX_arrowsA);
	chr_to_nametable(NAMETABLE_B, nam_scrollFX_arrowsB);

	pal_col(0,0x0D);
	pal_col(1,0x0D);
	pal_col(2,0x03);
	pal_col(3,0x0D);
	pal_bg(pal_water);
	cnrom_set_bank(TILESET_SCROLLER_FX);
	ppu_on_all();
}
*/

void main(void)
{
	
	set_vram_buffer();
	clear_vram_buffer();
	sq_scroll_pos=0;

	p=0;

	/* part 1 - begin */
	
	setup_scene1();
	music_play(0);
	scene1_ZXloading();

	xa = 0;
	ya = 0;

	setup_scene_water();
	pal_spr(pal_water);

	to_bright=4;

	while (muspos < 1250+MUS_BAR) {
		fxPlasm16(); // 8 frames
		if (muspos > 1250+160){
			if (bright < 8) {
				++bright;
			}
			pal_bright(bright);
		}
		else
		if (bright!=to_bright)
		{
			++bright;
			pal_bright(bright);
		}
		muspos = get_mus_pos();
	}
	

	clear_vram_buffer();
	multi_vram_buffer_horz((unsigned char *) string_we_like_to, 32, NAMETABLE_A+32 * 23);
	multi_vram_buffer_horz((unsigned char *) string_we_like_to, 32, NAMETABLE_B+32 * 23);
	ppu_wait_nmi();


	while (muspos < 1250+MUS_BAR*2) {
		fxPlasm16();	
		if (muspos > 1250+MUS_BAR*2-32){
			if (bright < 8) {
				++bright;
			}
			pal_bright(bright);
		}
		else
		if(bright!=to_bright)
		{
			--bright;
			pal_bright(bright);
		}
		muspos = get_mus_pos();
	}

	ppu_off();
	
	setup_scene_fire();

	to_bright=4;

	while (muspos < 1250+MUS_BAR*3) {
		fxFire();	
		if (muspos > 1250+MUS_BAR*3-32){
			if (bright < 8) {
				++bright;
			}
			pal_bright(bright);
		}
		else
		if(bright!=to_bright)
		{
			--bright;
			pal_bright(bright);
		}
		muspos = get_mus_pos();
	}
	
	clear_vram_buffer();
	multi_vram_buffer_horz((unsigned char *) string_invite_you_to, 32, NAMETABLE_A+32 * 23);
	multi_vram_buffer_horz((unsigned char *) string_invite_you_to, 32, NAMETABLE_B+32 * 23);
	ppu_wait_nmi();

	while (muspos < 1250+MUS_PATTERN+32) {
		fxFire();	
		if (muspos > 1250+MUS_PATTERN){
			if (bright > 0) {
				--bright;
			}
			pal_bright(bright);
		}
		else
		if(bright!=to_bright)
		{
			--bright;
			pal_bright(bright);
		}
		muspos = get_mus_pos();
	}


	clear_vram_buffer();
	ppu_wait_nmi();

//	showmuspos();
		
	// pause
	while(muspos < 0x0814) {
		muspos = get_mus_pos();
	}
	
	// blink
	pal_bright(8);
	setupSquaresFX(0x03);
	ppu_wait_nmi();
	pal_bright(4);

	while(muspos < (0x0814 + MUS_BAR*3)){
		fxScroll32((unsigned char*) restoreBGscrollSquares);
		muspos = get_mus_pos();
	}

	pal_bright(8);
	clear_vram_buffer();
	oam_clear();
	gfrm=255;
	setupBigTextPage(*infoPage1, 1);
	gfrm=0;
	pal_bright(4);
	ppu_wait_nmi();

	while(muspos < (0x0814 + MUS_BAR*3+MUS_BAR*5)){
		fxBigPage();
		muspos = get_mus_pos();
	}

	pal_bright(8);
	setupSquaresFX(0x04);
	pal_bright(4);

	while(muspos < (0x0814 + MUS_PATTERN*2 + MUS_PATTERN)){
		fxScroll32((unsigned char*) restoreBGscrollSquares);
		muspos = get_mus_pos();
	}

	musCheckpoint=muspos;

	// 1:12 - Rhombus
	oam_clear();
	clear_vram_buffer();
	ppu_wait_nmi();

	fy=0;
	fx=0;
	setupRhombusFX();
	while(muspos < (musCheckpoint + MUS_PATTERN)){
		if (!(gfrm&3)) fxPaletteRoll();
		++gfrm;
		if (muspos == musCheckpoint || muspos == musCheckpoint+0x20*3 || muspos == musCheckpoint+0x20*3*2 || muspos == musCheckpoint+0x20*3*4 || muspos == musCheckpoint+0x20*3*5 || muspos == musCheckpoint+0x20*3*6)
		{
			clear_vram_buffer();
			multi_vram_buffer_horz(features1+fy*64, 64, NAMETABLE_A+32*4+fy*128);
			++fy;
		}
		if (muspos == musCheckpoint+0x0f*3 || muspos == musCheckpoint+0x2f*3 || muspos == musCheckpoint+0x4f*3 || muspos == musCheckpoint+0x8f*3  || muspos == musCheckpoint+0x8f*3+96 || muspos == musCheckpoint+0x8f*3+(96*2))
		{
			clear_vram_buffer();
			multi_vram_buffer_horz(features_attrs+fx*8, 8, NAMETABLE_A+0x03c8+fx*8);
			++fx;
		}
		ppu_wait_nmi();
		muspos = get_mus_pos();
	};

	clear_vram_buffer();
	ppu_wait_nmi();

	/// ZX

	ppu_off();
	setup_scene1();

	pal_col(5,0x30);
	pal_col(6,0x0f);
	pal_col(7,0x06);

	pal_col(9,0x0f);
	pal_col(10,0x0f);

	ppu_on_all();

	zx_loading(musCheckpoint + MUS_PATTERN+76, 0x2c, 0x05, 4, 0);

	musCheckpoint=muspos;

	pal_bright(8);
	setupGridFX(0x05);
	pal_bright(4);
	ppu_wait_nmi();

	musCheckpoint=muspos;

	while(muspos < (musCheckpoint + MUS_PATTERN)){
		fxScroll32((unsigned char*) restoreBGscrollGrid);
		muspos = get_mus_pos();
	}

	pal_bright(8);
	clear_vram_buffer();
	oam_clear();
	setupBigTextPage(*infoPage2, 2);
	scroll(0,0);
	pal_bright(4);
	ppu_wait_nmi();

	while(muspos < (musCheckpoint + MUS_PATTERN + MUS_PATTERN)){
		fxBigPage();
		muspos = get_mus_pos();
	}

	pal_bright(8);
	setupGridFX(0x25);
	pal_bright(4);

	while(muspos < (musCheckpoint + MUS_PATTERN + MUS_PATTERN + MUS_PATTERN)){
		fxScroll32((unsigned char*) restoreBGscrollGrid);
		muspos = get_mus_pos();
	}


	clear_vram_buffer();

	oam_clear();
	muspos = get_mus_pos();

	setupInvadersFX();

	fr=0;
	for (p=0;p<8;++p) {
		musCheckpoint=muspos;
		platforms[(p&3)*5]=p+1;
		while(muspos < musCheckpoint+MUS_HALF_BAR){
			fxInvaders();
			muspos = get_mus_pos();
			if (p==3 && muspos==musCheckpoint+MUS_HALF_BAR-24) {
				pal_bright(8);
				ppu_wait_nmi();
				pal_bright(4);
				oam_clear();
				platforms[0]=0;
				platforms[5]=0;
				platforms[10]=0;
				platforms[15]=0;
			} 
		}
	}

	musCheckpoint=muspos;
	ppu_wait_nmi();

	setupSquaresFX(0x0A);

	while(muspos < (musCheckpoint + MUS_PATTERN)){
		fxScroll32((unsigned char*) restoreBGscrollSquares);
		muspos = get_mus_pos();
	}

	pal_bright(8);
	clear_vram_buffer();
	oam_clear();
	setupBigTextPage(*infoPage3, 3);
	scroll(0,0);
	pal_bright(4);
	ppu_wait_nmi();

	while(muspos < (musCheckpoint + MUS_PATTERN + MUS_PATTERN)) {
		fxBigPage();
		muspos = get_mus_pos();
	}

	setupSquaresFX(0x0B);

	musCheckpoint=muspos;
	while(muspos < (musCheckpoint + 0x24*3)){
		fxScroll32((unsigned char*) restoreBGscrollSquares);
		muspos = get_mus_pos();
	}


	// Crash 1
	while(muspos < (musCheckpoint + 0x36*3)){
		vram_adr(NAMETABLE_A);
		vram_put(rand8());
		scroll(rand8(), rand8()&7);
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	gfrm=0;
	// Crash 2
	while(muspos < (musCheckpoint + 0x36*3 + 0x08*3 - 18)){
		if (!(gfrm)&7)
			++p;
		p&=3;
		cnrom_set_bank(p);
		ppu_wait_nmi();
		muspos = get_mus_pos();
		++gfrm;
	}

	clear_vram_buffer();
	oam_clear();
	ppu_off();
	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	vram_adr(NAMETABLE_A);
	vram_write(nam_Invites, 1024);
	scroll(0,0);
	ppu_on_all();
	pal_col(5,0x10);

	// Crash 3
	while(muspos < (musCheckpoint + 0x36*3 + 0x10*3)){
		cnrom_set_bank(rand8()&3);
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}
	pal_col(2,0x10);
	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);

	// Crash 4
	while(muspos < (musCheckpoint + 0x36*3 + 0x1f*3 + 18)){
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	pal_bright(8); ppu_wait_nmi();
	fxPlasmSetup();
	pal_bright(4); ppu_wait_nmi();

	musCheckpoint=muspos;

	// fx plasm 
	while(muspos < (musCheckpoint + MUS_PATTERN)){
		fxPlasm();
		muspos = get_mus_pos();
	}
	set_nmi_user_call_off();

	pal_bright(8); ppu_wait_nmi();
	fxTwisterSetup();
	pal_bright(4); ppu_wait_nmi();

	// fx twister
	twTextTimer = get_mus_pos() + twTextDelay - 12;
	while(muspos < (musCheckpoint + MUS_PATTERN*2)){
		fxTwister();
		muspos = get_mus_pos();
	}
	set_nmi_user_call_off();
	

	pal_bright(8); ppu_wait_nmi();
	fxRotorSetup();
	pal_bright(4); ppu_wait_nmi();
	while(muspos < (musCheckpoint + MUS_PATTERN*3)){
		fxRotor();
		muspos = get_mus_pos();
	}

	set_nmi_user_call_off();

	oam_clear();	
	scroll(0,0); ppu_wait_nmi();
	fxSetupFinalScreen();

	musCheckpoint=muspos=get_mus_pos();

	zx_loading(musCheckpoint+0x14*3, 0x00, 0x0f, 4, 0);
	zx_loading(musCheckpoint+0x18*3, 0x28, 0x01, 5, 256);

	pal_col(5,0x30);
	pal_col(6,0x02);
	pal_col(1,0x0f);
	pal_col(2,0x0f);
	ppu_wait_nmi();
	
	while(muspos < musCheckpoint+0x23*3) {
		ppu_wait_nmi();
		muspos=get_mus_pos();
	}

	zx_loading(musCheckpoint+0x34*3, 0x2c, 0x05, 4, 0);
	zx_loading(musCheckpoint+0x38*3, 0x28, 0x01, 5, 256);
	pal_col(7,0x10);

	zx_border(0x06);

	//skip_frames(40);
	while (muspos < musCheckpoint+0x38*3+25) {
		muspos = get_mus_pos();
	}
	
	zx_border(0x0f);
	music_stop();
	while(1) {};
}