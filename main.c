// CAF'e 2019 invitro source code
// Credits (alphabetically):
// Adam Bazaroff, mr287cc, n1k-o, TmK

#include "snake_rattle_and_roll.h"
#include "neslib.h"
#include "nesdoug.h"

#define	PLASMA16_POS_X						8
#define	PLASMA16_POS_Y						5

#define	FX_START							0
#define	FX_FADE_IN_FROM_MAX					1
#define	FX_FADE_IN_FROM_MIN					2

const unsigned char sinTbl1[]={4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2};
const unsigned char sinTbl2[]={12,15,18,20,22,23,24,24,23,22,20,17,14,11,9,6,4,2,1,0,0,1,3,5,7,10,13,16,19,21,23,24,24,24,23,21,19,16,13,10,7,5,3,1,0,0,1,2,4,6,9,11,14,17,20,22,23,24,24,23,22,20,18,15,12,9,6,4,2,1,0,0,1,2,4,7,10,13,15,18,20,22,23,24,24,23,21,19,17,14,11,8,5,3,1,0,0,0,1,3,5,8,11,14,17,19,21,23,24,24,23,22,20,18,15,13,10,7,4,2,1,0,0,1,2,4,6,9,12,15,18,20,22,23,24,24,23,22,20,17,14,11,9,6,4,2,1,0,0,1,3,5,7,10,13,16,19,21,23,24,24,24,23,21,19,16,13,10,7,5,3,1,0,0,1,2,4,6,9,11,14,17,20,22,23,24,24,23,22,20,18,15,12,9,6,4,2,1,0,0,1,2,4,7,10,13,15,18,20,22,23,24,24,23,21,19,17,14,11,8,5,3,1,0,0,0,1,3,5,8,11,14,17,19,21,23,24,24,23,22,20,18,15,13,10,7,4,2,1,0,0,1,2,4,6,9};
const unsigned char sinTbl3[]={8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6};
const unsigned char twisterSin[]={ 63,63,63,63,63,63,63,63,63,63,63,63,63,62,62,62,62,61,61,61,60,60,59,59,59,58,58,57,57,56,56,55,55,54,53,53,52,52,51,50,50,49,48,48,47,46,46,45,44,44,43,42,41,41,40,39,38,37,37,36,35,34,34,33,32,31,30,30,29,28,27,27,26,25,24,23,23,22,21,20,20,19,18,18,17,16,16,15,14,14,13,12,12,11,11,10,9,9,8,8,7,7,6,6,5,5,5,4,4,3,3,3,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,5,6,6,7,7,8,8,9,9,10,11,11,12,12,13,14,14,15,16,16,17,18,18,19,20,20,21,22,23,23,24,25,26,27,27,28,29,30,30,31,32,33,34,34,35,36,37,37,38,39,40,41,41,42,43,44,44,45,46,46,47,48,48,49,50,50,51,52,52,53,53,54,55,55,56,56,57,57,58,58,59,59,59,60,60,61,61,61,62,62,62,62,63,63,63,63,63,63,63,63,63,63,63,63};
const unsigned char twisterData[]={0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,2,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,2,0,1,1,1,1,1,1,0,0,0,0,0,0,0,2,2,2,0,1,1,1,1,1,0,0,0,0,0,0,0,2,2,2,0,1,1,1,1,1,0,0,0,0,0,0,0,2,2,2,2,0,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,0,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,0,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,0,1,1,1,1,0,0,0,0,0,0,0,2,2,2,2,2,0,1,1,1,0,0,0,0,0,0,0,2,2,2,2,2,0,1,1,1,0,0,0,0,0,0,0,2,2,2,2,2,2,0,1,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,1,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0};
const unsigned char twisterSinX[]={16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,13,13,13,13,13,13,12,12,12,12,12,12,11,11,11,11,11,11,10,10,10,10,10,9,9,9,9,9,8,8,8,8,8,7,7,7,7,7,6,6,6,6,6,5,5,5,5,5,5,4,4,4,4,4,4,3,3,3,3,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,7,7,7,7,7,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16};

const unsigned char twisterChunks[]={
	0,0x86,0x92,
	0,0x92,0x7f,
	0,0x7f,0x8c,
	0,0x8c,0x86
};

const unsigned char string_we_like_to[32*1]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6a,0x6b,0xd7,0xa0,0xa1,0xa2,0xa3,0xdc,0xbb,0xbc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char string_invite_you_to[32*1]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff
};



#pragma bss-name (push,"ZEROPAGE")

unsigned char p, fx, fy, bright, to_bright;
unsigned int gfrm;

static unsigned char fire_array[16*16]={};

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

#pragma bss-name (pop);

unsigned char pad;
unsigned char tileset;

const unsigned char pal_part1[16]={ 0x0f,0x05,0x2c,0x10,0x0f,0x30,0x10,0x06,0x0f,0x0f,0x10,0x0f,0x0f,0x0f,0x0f,0x0f };
const unsigned char pal_water[16]={ 0x0f,0x0c,0x21,0x1c,0x0f,0x0b,0x1b,0x2b,0x0f,0x2d,0x20,0x10,0x0f,0x3d,0x3d,0x0f };

const unsigned char bus_conflict[4]={ 0x00,0x01,0x02,0x03 };

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

#include "sceneZXloading.h"

// quality: mask (15/31) 
void fxPlasmFrame(frm, quality) {  
unsigned char y, x, yfrom, yto;
	buffAdr = 0;
	yfrom = frm*3;
	yto = frm*3 + 3;
	yy = ya + yfrom;
	for (y = yfrom; y < yto; y++) {
		xx = xa;
		xy = y + xya;
		for (x = 0; x < 32; x++) {
			fire_array[buffAdr] = 0x80 + ((colorAdd + sinTbl1[xx] + sinTbl2[yy] + sinTbl3[xy]) & quality);
			buffAdr+=1;
			xx+=1;
			xy+=1;
		}
		yy+=1;
	}
}

const twLines = 5;

void fxTwisterFrame(frm) {
	unsigned char x, y, twisterAdr, yyy, x1, x2, y1, chunk, chunkAdr, yfrom, yto;
	memfill(fire_array, 0, 32*twLines);
	yfrom = frm * twLines;
	yto = yfrom + twLines;
	yyy = 0;
	for (y = yfrom; y < yto; y++) {
		x1 = xa + 6*y;
		x2 = za + 6*y;
		y1 = ya + y;
		chunkAdr = 3 * (twisterSin[y1] / 16);
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
}


void fxPlasm(void) {

	for (frm = 0; frm < 8; frm++) {
		if (scrSwap == 0) {
			scroll(0,0);
			fxPlasmFrame(frm, 31);
//			gray_line();
			clear_vram_buffer();
			multi_vram_buffer_horz((unsigned char*) fire_array+0,32,NAMETABLE_B+frm*96+32 + 64);
			multi_vram_buffer_horz((unsigned char*) fire_array+32,32,NAMETABLE_B+frm*96+64 + 64);
			multi_vram_buffer_horz((unsigned char*) fire_array+64,32,NAMETABLE_B+frm*96+96 + 64);
			ppu_wait_nmi();
			scroll(256,0);
		} else {
			fxPlasmFrame(frm, 31);
//			gray_line();
			clear_vram_buffer();
			multi_vram_buffer_horz((unsigned char*) fire_array+0,32,NAMETABLE_A+frm*96+32 + 64);
			multi_vram_buffer_horz((unsigned char*) fire_array+32,32,NAMETABLE_A+frm*96+64 + 64);
			multi_vram_buffer_horz((unsigned char*) fire_array+64,32,NAMETABLE_A+frm*96+96 + 64);
			ppu_wait_nmi();
		}

	}
	xa+=1;
	ya+=1;
	xya-=1;
	colorAdd += 1;
	scrSwap ^= 1;
}

void fxPlasm16(void) {

	for (frm = 0; frm < 8; frm++) {
		if (scrSwap == 0) {
			scroll(0,0);
			fxPlasmFrame(frm, 31);
//			gray_line();
			clear_vram_buffer();
			multi_vram_buffer_horz((unsigned char*) fire_array+0,16,NAMETABLE_B+frm*64+32+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			multi_vram_buffer_horz((unsigned char*) fire_array+32,16,NAMETABLE_B+frm*64+64+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			ppu_wait_nmi();
			scroll(256,0);
		} else {
			fxPlasmFrame(frm, 31);
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
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+6*32+8+fy*32);
		}
		ppu_wait_nmi();

		clear_vram_buffer();
		for (fy=4;fy<8;++fy){
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+6*32+8+fy*32);
		}
		ppu_wait_nmi();

		clear_vram_buffer();
		for (fy=8;fy<12;++fy){
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+6*32+8+fy*32);
		}
		ppu_wait_nmi();

		clear_vram_buffer();
		for (fy=12;fy<16;++fy){
			multi_vram_buffer_horz((unsigned char*) fire_array+fy*16,16,NAMETABLE_A+6*32+8+fy*32);
		}
		ppu_wait_nmi();
}

void setup_scene_water(void) {
	vram_adr(NAMETABLE_A);
	vram_fill(0,1024-16);
	vram_fill(255,16);
	vram_adr(NAMETABLE_B);
	vram_fill(0,1024-16);
	vram_fill(255,16);

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


void main(void)
{

	tileset=0;
	cnrom_set_bank(tileset);
	bright=4;

	set_vram_buffer();

	setup_scene1();
	music_play(0);
	scene1_ZXloading();

	ppu_off();

	xa = 0;
	ya = 0;

	setup_scene_water();
	pal_spr(pal_water);

// pal twistor
/*
	pal_col(1,0x11);
	pal_col(2,0x25);
	pal_col(3,0x2a);


	while(!(pad&PAD_START)){
		pad=pad_trigger(0);
		fxTwister();
	}

	set_nmi_user_call_off();
*/


	to_bright=4;

	gfrm=20;
	while(gfrm){
		fxPlasm16();
		if (gfrm<4){
			++bright;
			pal_bright(bright);
		}
		else
		if(bright!=to_bright)
		{
			++bright;
			pal_bright(bright);
		}
		--gfrm;
	}

	clear_vram_buffer();
	multi_vram_buffer_horz((unsigned char *) string_we_like_to, 32, NAMETABLE_A+32 * 25);
	multi_vram_buffer_horz((unsigned char *) string_we_like_to, 32, NAMETABLE_B+32 * 25);
	ppu_wait_nmi();


	gfrm=26;
	while(gfrm){
		fxPlasm16();	
		if (gfrm<5){
			++bright;
			pal_bright(bright);
		}
		else
		if(bright!=to_bright)
		{
			--bright;
			pal_bright(bright);
		}
		--gfrm;
	}

	ppu_off();

	setup_scene_fire();

	to_bright=4;

	gfrm=25;
	while(gfrm){
		fxFire();	
		if (gfrm<5){
			++bright;
			pal_bright(bright);
		}
		else
		if(bright!=to_bright)
		{
			--bright;
			pal_bright(bright);
		}
		--gfrm;
	}

	clear_vram_buffer();
	multi_vram_buffer_horz((unsigned char *) string_invite_you_to, 32, NAMETABLE_A+32 * 25);
	multi_vram_buffer_horz((unsigned char *) string_invite_you_to, 32, NAMETABLE_B+32 * 25);
	ppu_wait_nmi();

	gfrm=28;
	while(gfrm){
		fxFire();	
		if (gfrm<5){
			++bright;
			pal_bright(bright);
		}
		else
		if(bright!=to_bright)
		{
			--bright;
			pal_bright(bright);
		}
		--gfrm;
	}


//	ppu_off();

	while(1)
	{
	}
}