//this example code shows how to put some text in nametable
//it assumes that you have ASCII-encoded font in the CHR tiles $00-$3f
//it also shows how to detect PAL/NTSC video system

#include "neslib.h"
#include "nesdoug.h"
// #include "plasma.h"

const unsigned char sinTbl1[]={4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2,4,6,7,8,8,8,7,6,4,2,1,0,0,0,1,2};
const unsigned char sinTbl2[]={12,15,18,20,22,23,24,24,23,22,20,17,14,11,9,6,4,2,1,0,0,1,3,5,7,10,13,16,19,21,23,24,24,24,23,21,19,16,13,10,7,5,3,1,0,0,1,2,4,6,9,11,14,17,20,22,23,24,24,23,22,20,18,15,12,9,6,4,2,1,0,0,1,2,4,7,10,13,15,18,20,22,23,24,24,23,21,19,17,14,11,8,5,3,1,0,0,0,1,3,5,8,11,14,17,19,21,23,24,24,23,22,20,18,15,13,10,7,4,2,1,0,0,1,2,4,6,9,12,15,18,20,22,23,24,24,23,22,20,17,14,11,9,6,4,2,1,0,0,1,3,5,7,10,13,16,19,21,23,24,24,24,23,21,19,16,13,10,7,5,3,1,0,0,1,2,4,6,9,11,14,17,20,22,23,24,24,23,22,20,18,15,12,9,6,4,2,1,0,0,1,2,4,7,10,13,15,18,20,22,23,24,24,23,21,19,17,14,11,8,5,3,1,0,0,0,1,3,5,8,11,14,17,19,21,23,24,24,23,22,20,18,15,13,10,7,4,2,1,0,0,1,2,4,6,9};
const unsigned char sinTbl3[]={8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6,8,10,11,12,14,15,15,16,16,16,15,15,14,12,11,10,8,6,5,4,2,1,1,0,0,0,1,1,2,4,5,6};

const unsigned char string_we_like_to[32*1]={
	0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xc0,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

const unsigned char string_invite_you_to[32*1]={
	0xff,0xff,0xff,0xff,0xff,0xff,0xce,0xcf,0xff,0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};


#include "part1_zx_loading_nam.h"
#include "part1_zx_pilotone_nam.h"

#define	PLASMA16_POS_X						8
#define	PLASMA16_POS_Y						5

#pragma bss-name (push,"ZEROPAGE")

unsigned int i, p, fx, fy, bright;

static unsigned char fire_array[16*16]={};

unsigned char scrSwap = 0;
unsigned char frm = 0;
unsigned char xa = 0;
unsigned char ya = 0;
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

const unsigned char nametable_part1_bytes[22*1]={
	0x54,0x55,0x56,0x0b,0x57,0x06,0x07,0x05,0x01,0x0d,0x59,0x5a,0x5b,0x5b,0x68,0x07,0x66,0x05,0x67,0x07,0x07
};

const unsigned char nametable_part1_visuals[22*1]={
	0x5d,0x5e,0x57,0x5f,0x04,0x60,0x57,0x06,0x07,0x09,0x61,0x04,0x05,0x07,0x54,0x04,0x62,0x04,0x01,0x02,0x63,0x63
};

const unsigned char nametable_part1_music[22*1]={
	0x58,0x5f,0x57,0x5e,0x5b,0x06,0x07,0x64,0x0f,0x65,0x5c,0x02,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07
};

static unsigned char titles_list[25+25+1]={
	MSB(NTADR_A(4,7))|NT_UPD_HORZ,LSB(NTADR_A(4,7)),22,7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,
	MSB(NTADR_B(4,7))|NT_UPD_HORZ,LSB(NTADR_B(4,7)),22,7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,7,7, 7,
	NT_UPD_EOF
};

const unsigned char pal_part1[16]={ 0x0f,0x05,0x2c,0x10,0x0f,0x30,0x10,0x06,0x0f,0x0f,0x10,0x0f,0x0f,0x0f,0x0f,0x0f };
const unsigned char palette[16]={ 0x0f,0x05,0x2c,0x10,0x0f,0x20,0x10,0x05,0x0f,0x3d,0x3d,0x0f,0x0f,0x0f,0x0f,0x0f };
const unsigned char pal_water[16]={ 0x0f,0x0c,0x21,0x1c,0x0f,0x0c,0x21,0x1c,0x0f,0x3d,0x3d,0x0f,0x0f,0x0f,0x0f,0x0f };


const unsigned char bus_conflict[4]={ 0x00,0x01,0x02,0x03 };

void cnrom_set_bank(unsigned char bank)
{
	unsigned char *ptr;
	bank&=3;
	ptr=(unsigned char*)&bus_conflict[bank];
	*ptr=bank;
}

void zx_loading(unsigned char length, unsigned char color1, unsigned char color2, unsigned char freq, unsigned int scroll_pos){
	scroll(scroll_pos,0);
	for (i=0; i<length; ++i){
		if (!(i&freq)){
			pal_col(1,color1);
			pal_col(2,color2);
		}
		else {
			pal_col(2,color1);
			pal_col(1,color2);				
		}
/*
		if(scroll_pos==0)
		if (!(i&15))
			scroll(256,0);
		else
			scroll(0,0);
*/
		ppu_wait_nmi();
	}
}

void skip_frames(unsigned char length){
	for (i=0; i<length; ++i){
		ppu_wait_nmi();
	}
}

void zx_border(unsigned char color){
	pal_col(1,color);
	pal_col(2,color);
}

void _pal_fade_to(unsigned to)
{
	while(bright!=to)
	{
		delay(4);
		if(bright<to) ++bright; else --bright;
		pal_bright(bright);
	}

	if(!bright)
	{
		ppu_off();
		set_vram_update(NULL);
		scroll(0,0);
	}
} 


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

void rollpalette(void) {
unsigned char i;

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
			fxPlasmFrame(frm, 15);
//			gray_line();
			clear_vram_buffer();
			multi_vram_buffer_horz((unsigned char*) fire_array+0,16,NAMETABLE_B+frm*64+32+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			multi_vram_buffer_horz((unsigned char*) fire_array+32,16,NAMETABLE_B+frm*64+64+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			ppu_wait_nmi();
			scroll(256,0);
		} else {
			fxPlasmFrame(frm, 15);
//			gray_line();
			clear_vram_buffer();
			multi_vram_buffer_horz((unsigned char*) fire_array+0,16,NAMETABLE_A+frm*64+32+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			multi_vram_buffer_horz((unsigned char*) fire_array+32,16,NAMETABLE_A+frm*64+64+PLASMA16_POS_X + PLASMA16_POS_Y*32);
			ppu_wait_nmi();
		}

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

#include "sceneZXloading.h"

void main(void)
{
unsigned int i;
signed char k;
unsigned char off;

	tileset=0;
	cnrom_set_bank(tileset);
	
	pal_bg(palette);

	vram_adr(NAMETABLE_B);
	vram_unrle(part1_zx_loading_nam);

	vram_adr(NAMETABLE_A);
	vram_unrle(part1_zx_pilotone_nam);

	bright=4;

	sceneZXloading();

	ppu_off();


	pal_bg(pal_water);

	k=1;
	i=15;

	vram_adr(NAMETABLE_A);
	vram_fill(0,1024*2);
//	vram_unrle(nam_border16x16);
	vram_adr(NAMETABLE_B);
//	vram_unrle(nam_border16x16);

	vram_adr(NAMETABLE_A+25*32);
	vram_write(string_we_like_to,32);
	vram_adr(NAMETABLE_B+25*32);
	vram_write(string_we_like_to,32);

	set_vram_buffer();

	ppu_on_all();
	_pal_fade_to(4);

	off=15;

	pad=pad_trigger(0);
	while(!(pad&PAD_START)){

		i+=k;
		if (i>28 || i<3) k=-k;

//		if (!(i&15)) {
//			rollpalette();
//		}

		pad=pad_trigger(0);
		fxPlasm16();	
		
	}

	_pal_fade_to(0);

	vram_adr(NAMETABLE_A+25*32);
	vram_write(string_invite_you_to,32);


	set_vram_buffer();

	pal_col(1,0x06);
	pal_col(2,0x16);
	pal_col(3,0x28);

	for (fy=0;fy<256;++fy){
		fire_array[fy]=0x70;
	}

	ppu_on_all();

	for (fy=0;fy<6;++fy) fxFire();
	_pal_fade_to(4);

	pad=pad_trigger(0);

	while(!(pad&PAD_START)){

		pad=pad_trigger(0);
		fxFire();

	}

	ppu_off();

	while(1)
	{
	}
}