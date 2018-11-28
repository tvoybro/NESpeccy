// CAF'e 2019 invitro source code
// Credits (alphabetically):
// Adam Bazaroff, mr287cc, n1k-o, TmK

#define txtS(chr) ((int)chr + 0xDA - 65)
#define txtN(chr) ((int)chr + 0xD0 - 48)

#include "Include\snake_rattle_and_roll.h"
#include "Include\neslib.h"
#include "Include\nesdoug.h"

#include "Include\nam_finalScreen_qr.h"

#include "Include\nam_invadersA.h"
#include "Include\nam_invadersB.h"
#include "Include\nam_scroll_squaresA.h"
#include "Include\nam_scroll_squaresB.h"
#include "Include\nam_scrollFX_arrowsA.h"
#include "Include\nam_scrollFX_arrowsB.h"
#include "Include\nam_scroll_gridA.h"
#include "Include\nam_scroll_gridB.h"
#include "Include\nam_paletteFX.h"
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

unsigned char pal_i, fr, i, spr, p, sq_scroll_pos, pause, imsb, scrollRow;
unsigned int scrollPage;
unsigned char from_x, tick;

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
unsigned buffAdr = 0;
unsigned val = 0;

unsigned char palRoll = 0;
unsigned char scrollFXpos = 0;

#pragma bss-name (pop);

// Данные здесь:
#include "Include\consttables.h"

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


#include "Include\sceneZXloading.h"

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

#define twLines 6
#define twTextDelay1 5
#define twTextDelay2 60


unsigned int twTextAdr = 0;
const unsigned char twisterText[] = {
	0 * twTextDelay1, twTextDelay2 - 3 * twTextDelay1,
	0, 3*32+4,
	6,
	0xDE, 0xF1, 0xDC, 0xDE, 0xEC, 0xEC,
	
	1 * twTextDelay1, twTextDelay2 - 2 * twTextDelay1,
	1, 3*32+20,
	6,
	0xDE, 0xF1, 0xDC, 0xDE, 0xEC, 0xEC,
	
	2 * twTextDelay1, twTextDelay2 - 1 * twTextDelay1,
	2, 3*32+4,
	6,
	0xDE, 0xF1, 0xDC, 0xDE, 0xEC, 0xEC,
	
	3 * twTextDelay1, twTextDelay2 - 0 * twTextDelay1,
	3, 3*32+20,
	6,
	0xDE, 0xF1, 0xDC, 0xDE, 0xEC, 0xEC,
	
    //-------------------------
    
	0 * twTextDelay1, twTextDelay2 - 4 * twTextDelay1,
	0, 3*32+4,
	3,
	0xEC, 0xEC, 0xEC,
	
	1 * twTextDelay1, twTextDelay2 - 3 * twTextDelay1,
	1, 3*32+20,
	6,
	0xDE, 0xF1, 0xDC, 0xDE, 0xEC, 0xEC,
	
	2 * twTextDelay1, twTextDelay2 - 2 * twTextDelay1,
	2, 3*32+4,
	6,
	0xDE, 0xF1, 0xDC, 0xDE, 0xEC, 0xEC,
	
	3 * twTextDelay1, twTextDelay2 - 1 * twTextDelay1,
	3, 3*32+20,
	6,
	0xDE, 0xF1, 0xDC, 0xDE, 0xEC, 0xEC,
    
    //-------------------------
    255 //no text code
    
};


/*
для каждого frm мы строим 6 строк

1б - начиная с какого фрейма показывать
1б - длительность показа
1б - номер frm
1б - адрес
1б - длина сообщения
Xб - само сообщение
*/


void fxTwisterFrame(frm) {
	unsigned char x, y, twisterAdr, yyy, x1, x2, y1, chunk, chunkAdr, yfrom, yto, tadr, tqty, txtadr;
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
		if (
			(twisterText[txtadr + 2] == frm)
			&& (twisterText[txtadr + 0] <= fxFrame)
			&& (twisterText[txtadr + 1] >= fxFrame)
		) {
			tadr = twisterText[txtadr + 3];
			for (x = 0; x < twisterText[txtadr + 4]; x++) {
				fire_array[tadr] = twisterText[txtadr + 5 + x];
				tadr++;
			}
		}
		txtadr += twisterText[txtadr + 4] + 5;
		--tqty;
	}
	
    if (fxFrame >= twTextDelay2 - 1) {
        fxFrame = 0;
        twTextAdr = txtadr;
    }
	
}

void fxTwister(void) {
	set_nmi_user_call_on();
	set_nmi_user_vram_lines_qty(twLines);
	for (frm = 0; frm < 4; frm++) {
		if (scrSwap == 0) {
			scroll(0,0);
			fxTwisterFrame(frm);
			gray_line();
			set_nmi_user_vram_adr(NAMETABLE_B + 64+32 + frm*32*twLines);
			ppu_wait_nmi();
		} else {
			scroll(256,0);
			fxTwisterFrame(frm);
			gray_line();
			set_nmi_user_vram_adr(NAMETABLE_A + 64+32 + frm*32*twLines);
			ppu_wait_nmi();
		}
	}
	xa += 8;
	za += 12;
	ya += 4;
	scrSwap ^= 1;
	fxFrame++;
}

//----------------------------------------------------------------------
#define plsmLines 5
#define plsmTextDelay1 0
#define plsmTextDelay2 60


unsigned int plsmTextAdr = 0;
const unsigned char plsmText[] = {
	0 * plsmTextDelay1, plsmTextDelay2 - 3 * plsmTextDelay1,
	1, 1*32+10,
	6,
	txtS('E'),txtS('X'),txtS('C'),txtS('E'),txtS('S'),txtS('S'),
	
	1 * plsmTextDelay1, plsmTextDelay2 - 2 * plsmTextDelay1,
	2, 2*32+20,
	6,
	txtS('E'),txtS('X'),txtS('C'),txtS('E'),txtS('S'),txtS('S'),
	
	2 * plsmTextDelay1, plsmTextDelay2 - 1 * plsmTextDelay1,
	3, 2*32+4,
	6,
	txtS('E'),txtS('X'),txtS('C'),txtS('E'),txtS('S'),txtS('S'),
	
	3 * plsmTextDelay1, plsmTextDelay2 - 0 * plsmTextDelay1,
	4, 3*32+16,
	6,
	txtS('E'),txtS('X'),txtS('C'),txtS('E'),txtS('S'),txtS('S'),
	
    //-------------------------
    
	0 * plsmTextDelay1, plsmTextDelay2 - 3 * plsmTextDelay1,
	1, 1*32+10,
	6,
	txtS('E'),txtS('X'),txtS('C'),txtS('E'),txtS('S'),txtS('S'),
	
	1 * plsmTextDelay1, plsmTextDelay2 - 2 * plsmTextDelay1,
	2, 2*32+20,
	8,
	txtS('D'),txtS('E'),txtS('M'),txtS('A'),txtS('R'),txtS('C'),txtS('H'),txtS('E'),
	
	2 * plsmTextDelay1, plsmTextDelay2 - 1 * plsmTextDelay1,
	3, 2*32+4,
	8,
	txtS('T'),txtS('H'),txtS('E'),txtS('S'),txtS('U'),txtS('P'),txtS('E'),txtS('R'),
	
	3 * plsmTextDelay1, plsmTextDelay2 - 0 * plsmTextDelay1,
	4, 3*32+16,
	3,
	txtS('A'),txtS('S'),txtS('D'),
    
    //-------------------------
    255 //no text code
    
};


void fxPlasmSetup(void) {
	ppu_off();
    
    pal_col(0,0x09);
    pal_col(2,0x19);
    pal_col(1,0x30);
    pal_col(3,0x29);
    
	vram_adr(NAMETABLE_A);
	vram_fill(0,1024);
	vram_adr(NAMETABLE_B);
	vram_fill(0,1024);

	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	ppu_on_all();
	
	fxFrame = 0;
}

void fxPlasmFrame(frm) {
unsigned char y, x, yfrom, yto, tqty, txtadr, tadr;
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
    
	tqty = 4;
	txtadr = plsmTextAdr;
    if (plsmText[txtadr] == 255) {
        return;
    }
    
	while (tqty > 0) {
		if (
			(plsmText[txtadr + 2] == frm)
			&& (plsmText[txtadr + 0] <= fxFrame)
			&& (plsmText[txtadr + 1] >= fxFrame)
		) {
			tadr = plsmText[txtadr + 3];
			for (x = 0; x < plsmText[txtadr + 4]; x++) {
				fire_array[tadr] = plsmText[txtadr + 5 + x];
				++tadr;
			}
		}
		txtadr += plsmText[txtadr + 4] + 5;
		--tqty;
	}
	
    if (fxFrame >= twTextDelay2 - 1) {
        fxFrame = 0;
        plsmTextAdr = txtadr;
    }
    
    
}

void fxPlasm(void) {
	for (frm = 0; frm < 6; frm++) {
        set_nmi_user_call_on();
        set_nmi_user_vram_lines_qty(plsmLines);
		if (scrSwap == 0) {
			scroll(0,0);
			fxPlasmFrame(frm);
			gray_line();
            set_nmi_user_vram_adr(NAMETABLE_B + frm*32*plsmLines);
			ppu_wait_nmi();
		} else {
            scroll(256,0);
			fxPlasmFrame(frm);
			gray_line();
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
/*
#define rotorLines 8
void fxRotorSetup(void) {
	ppu_off();
    
    pal_col(0,0x09);
    pal_col(2,0x19);
    pal_col(1,0x30);
    pal_col(3,0x29);
    
	vram_adr(NAMETABLE_A);
	vram_fill(0,1024-24);
	vram_adr(NAMETABLE_B);
	vram_fill(0,1024-24);

	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	ppu_on_all();
	
	fxFrame = 0;
}

void fxRotorFrame(frm) {
unsigned char y, x;
unsigned int tx, ty, tdx, tdy, stx, sty;
	buffAdr = 0;
	
	tdx = twisterSin[xya];
	tdy = twisterSin[(xya + 64) & 255];
	
	tx = 0; //frm * rotorLines * tdy;
	ty = 0; //-frm * rotorLines * tdx;
	
	for (y = rotorLines; y > 0; --y) {
		stx = tx;
		sty = ty;
		for (x = 32; x > 0; --x) {
			fire_array[buffAdr] = 0x80 + (twisterSin[128+((ty/16))+((tx/256))] & 31);
			tx += tdx;
			ty += tdy;
			++buffAdr;
		}
		tx = stx + tdy;
		ty = sty - tdx;
	}
}

void fxRotor(void) {
	for (frm = 0; frm < 1; frm++) {
        set_nmi_user_call_on();
        set_nmi_user_vram_lines_qty(rotorLines);
		if (scrSwap == 0) {
			scroll(0,0);
			fxRotorFrame(frm);
			gray_line();
            set_nmi_user_vram_adr(NAMETABLE_B + 64+ frm*32*rotorLines);
			ppu_wait_nmi();
		} else {
            scroll(256,0);
			fxRotorFrame(frm);
			gray_line();
            set_nmi_user_vram_adr(NAMETABLE_A + 64+ frm*32*rotorLines);
			ppu_wait_nmi();
		}

	}
	//xa+=1;
	//ya+=1;
	xya+=5;
	scrSwap ^= 1;
}
*/

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
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_paletteFX);
	cnrom_set_bank(TILESET_BIG_FONT_RHOMBUS);
	pal_col(1,0x01);
	pal_col(2,0x19);
	pal_col(3,0x28);
	scroll(0,0);
	ppu_on_all();
}

void setupGridFX(void) {
	cnrom_set_bank(TILESET_SCROLLER_FX);
	ppu_off();
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_scroll_gridA);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_scroll_gridB);
	pal_bg(pal_scrollerFX);
	pal_spr(pal_scrollerFX);
	ppu_on_all();
}

void setupSquaresFX(void) {
	ppu_off();
	cnrom_set_bank(TILESET_SCROLLER_FX);
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_scroll_squaresA);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_scroll_squaresB);
	pal_bg(pal_scrollerFX);
	pal_spr(pal_scrollerFX);
	ppu_on_all();
}

void setupInvadersFX(void) {
	ppu_off();
	cnrom_set_bank(TILESET_CHUNKS_FONT_INVADERS);
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_InvadersA);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_InvadersB);
	pal_bg(pal_scrollerFX);
	pal_spr(pal_scrollerFX);
	ppu_on_all();
}

void setupArrowsFX(void) {
	ppu_off();
	cnrom_set_bank(TILESET_SCROLLER_FX);
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_scrollFX_arrowsA);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_scrollFX_arrowsB);
	pal_col(0,0x0D);
	pal_col(1,0x0D);
	pal_col(2,0x03);
	pal_col(3,0x0D);
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
		
		spr=0;
		spr=oam_meta_spr(12*8,12*8-1,spr,logo_bottom);
		spr=oam_meta_spr(12*8,16*8-1,spr,logo_title);
};

void fxScroll96(void) {
	scroll(sq_scroll_pos*96, 0);

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

void fxScroll64(void) {
	scroll(sq_scroll_pos<<6, 0);

	ppu_wait_nmi();
	if (!(fr&1)) {
		++sq_scroll_pos;
		++from_x;
	}

	++fr;

	if (fr>29) {
		fr=0;
	}

	if (from_x>7) sq_scroll_pos=from_x=0;
	
};

unsigned char findsym(unsigned char substr){
unsigned char fs=0;
	
	while(tbl_ascii[fs]!=substr) ++fs;
	return fs;
}

void setupBigTextPage(const unsigned char *page) {
unsigned char x, y, sym;
unsigned int pos;
const unsigned char *bigSymbol;

	cnrom_set_bank(TILESET_BIG_FONT_RHOMBUS);
	ppu_off();
	vram_adr(NAMETABLE_A);
	vram_unrle(nam_BigText);
	vram_adr(NAMETABLE_B);
	vram_unrle(nam_BigText);
	pal_bg(pal_bigText);
//	pal_spr(pal_scrollerFX);

	for (y=0;y<8;++y) {
		pos=NAMETABLE_B+5*32+1+(y*96);
		for (x=0;x<16;++x) {
			sym=*page++;
			if (sym!=' ') {
				bigSymbol=tbl_alphabet[findsym(sym)];
				vram_adr(pos);
				vram_write(bigSymbol, 2);
				vram_adr(pos+32);
				vram_write(bigSymbol+2, 2);
				pos+=2;
			}
			else
				pos+=1;
		}
	}

	ppu_on_all();

};


const unsigned char infoPage1[8][16] = {
	"I WILL LOOK     ",
	"FORWARD TO MEET ",
	"YOU AT THE PARTY",
	"AND WOULD       ",
	"APPRECIATE IF   ",
	"YOU COULD       ",
	"CONFIRM YOUR    ",
	"PRESENCE        "
};

void main(void)
{
	set_vram_buffer();
	clear_vram_buffer();

	sq_scroll_pos=0;
	pause=10;

	p=0;

	/* part 1 - begin */
	
	bright=4;

/// Testing polygon

	setupBigTextPage(infoPage1[0]);
	while(1) {};

///

	setup_scene1();
	music_play(0);
	scene1_ZXloading();

	ppu_off();

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
		
	/* pause */
	while(muspos < 0x0814) {
		muspos = get_mus_pos();
	}
	
	/* blink */
	pal_bright(8);
	setupSquaresFX();
	pal_bright(4);

	while(muspos < (0x0814 + MUS_BAR*3)){
		fxScroll32((unsigned char*) restoreBGscrollSquares);
		muspos = get_mus_pos();
	}

	pal_bright(8);
	clear_vram_buffer();
	oam_clear();
	setupBigTextPage(infoPage1[0]);
	scroll(0,0);
	pal_bright(4);
	ppu_wait_nmi();

	while(muspos < (0x0814 + MUS_BAR*3+MUS_BAR*5)){
//		fxScroll32((unsigned char*) restoreBGscrollSquares);
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	pal_bright(8);
	setupSquaresFX();
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

	setupRhombusFX();
	while(muspos < (musCheckpoint + MUS_PATTERN)){
		if (!(gfrm&3)) fxPaletteRoll();
		++gfrm;
		ppu_wait_nmi();
		muspos = get_mus_pos();
	};

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

	/* blink */
	pal_bright(8);
	setupGridFX();
	pal_bright(4);

	musCheckpoint=muspos;

	while(muspos < (musCheckpoint + MUS_PATTERN)){
		fxScroll32((unsigned char*) restoreBGscrollGrid);
		muspos = get_mus_pos();
	}

	pal_bright(8);
	clear_vram_buffer();
	oam_clear();
	setupBigTextPage(infoPage1[0]);
	scroll(0,0);
	pal_bright(4);
	ppu_wait_nmi();

	while(muspos < (musCheckpoint + MUS_PATTERN + MUS_PATTERN)){
//		fxScroll32((unsigned char*) restoreBGscrollSquares);
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	pal_bright(8);
	setupGridFX();
	pal_bright(4);

	while(muspos < (musCheckpoint + MUS_PATTERN + MUS_PATTERN + MUS_PATTERN)){
		fxScroll32((unsigned char*) restoreBGscrollGrid);
		muspos = get_mus_pos();
	}


	clear_vram_buffer();
	oam_clear();
	setupInvadersFX();
	
	while(muspos < (musCheckpoint + MUS_PATTERN*4)){
		fxScroll96();
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	musCheckpoint=muspos;
	ppu_wait_nmi();

	setupArrowsFX();

	while(muspos < (musCheckpoint + MUS_PATTERN)) {
		pal_bright(4);
		scroll(scrollFXpos*64,0);
		ppu_wait_nmi();
		++gfrm;
		if (!(gfrm&1)) ++scrollFXpos;
		if (scrollFXpos>15) scrollFXpos=0;
		muspos = get_mus_pos();
	};


	pal_bright(8);
	clear_vram_buffer();
	oam_clear();
	setupBigTextPage(infoPage1[0]);
	scroll(0,0);
	pal_bright(4);
	ppu_wait_nmi();

	while(muspos < (musCheckpoint + MUS_PATTERN + MUS_PATTERN)) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	setupArrowsFX();

	// Обрывок следующего паттерна + "зависон" консоли = 64*3 кадра. "дёргаем" на 0х22*3 и на 0х36*3 кадре
	// остаток "зависона" = 0x1f*3 кадра. глитчи на 0, 0х08*3, 0х10*3 кадрах

	while(muspos < (musCheckpoint + MUS_PATTERN + MUS_PATTERN + MUS_PATTERN)) {
		pal_bright(4);
		scroll(scrollFXpos*64,0);
		ppu_wait_nmi();
		++gfrm;
		if (!(gfrm&1)) ++scrollFXpos;
		if (scrollFXpos>15) scrollFXpos=0;
		muspos = get_mus_pos();
	};


	oam_clear();
	clear_vram_buffer();

	// fx plasm 
	fxPlasmSetup();
	pal_bright(4);
	while(1){
		fxPlasm();
		muspos = get_mus_pos();
	}
	set_nmi_user_call_off();
/*	
	// blink
	pal_bright(8);
	ppu_wait_nmi();

	// fx twister
	fxTwisterSetup();
	pal_bright(4);
	while(muspos < (0x0814 + 192*8)){
		fxTwister();
		muspos = get_mus_pos();
	}

	set_nmi_user_call_off();
	
	// blink
	pal_bright(8);
	ppu_wait_nmi();
	
	// fx arrows
		
	fxPlasmSetup();
	while(get_mus_pos() < 192){
		fxPlasm();
	}

	fxTwisterSetup();
	while(get_mus_pos() < 192*2){
		fxTwister();
	}
*/
	
	while(1)
	{
	}
}