#include "part1_zx_loading_nam.h"
#include "part1_zx_pilotone_nam.h"

const unsigned char pal_zx_loading[16]={ 0x0f,0x05,0x2c,0x10,0x0f,0x20,0x10,0x05,0x0f,0x3d,0x3d,0x0f,0x0f,0x0f,0x0f,0x0f };

const unsigned char nametable_part1_bytes[22*1]={
	0x54,0x55,0x56,0x0b,0x57,0x06,0x07,0x05,0x01,0x0d,0x59,0x5a,0x5b,0x5b,0x68,0x07,0x66,0x05,0x67,0x07,0x07
};

const unsigned char nametable_part1_visuals[22*1]={
	0x5d,0x5e,0x57,0x5f,0x04,0x60,0x57,0x06,0x07,0x09,0x61,0x04,0x05,0x07,0x54,0x04,0x62,0x04,0x01,0x02,0x63,0x63
};

const unsigned char nametable_part1_music[22*1]={
	0x58,0x5f,0x57,0x5e,0x5b,0x06,0x07,0x64,0x0f,0x65,0x5c,0x02,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07
};

void setup_scene1(void) {
	ppu_off();
	cnrom_set_bank(TILESET_FIRE_CHUNKS_ZX);
	pal_bg(pal_zx_loading);
	vram_adr(NAMETABLE_B);
	vram_unrle(part1_zx_loading_nam);
	vram_adr(NAMETABLE_A);
	vram_unrle(part1_zx_pilotone_nam);
// "Program" title reset
	pal_col(9,0x10);
	pal_col(10,0x10);

// "Bill Gilbert" reset
	pal_col(5,0x10);
	pal_col(6,0x10);
	pal_col(7,0x10);

	ppu_on_all();
}

void zx_loading(unsigned int length, unsigned char color1, unsigned char color2, unsigned char freq, unsigned int scroll_pos){
unsigned char i;
	scroll(scroll_pos,0);
	//for (i=0; i<length; ++i){
	i = 0;
	while (muspos < length) {
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
		muspos = get_mus_pos();
		i++;
	}
}

void skip_frames(unsigned char length){
unsigned char i;
	for (i=0; i<length; ++i){
		ppu_wait_nmi();
	}
}

void zx_border(unsigned char color){
	pal_col(1,color);
	pal_col(2,color);
}

void scene1_ZXloading(void) {
	// Block 1:
	// Pilotone
	zx_loading(192, 0x2c, 0x05, 4, 0);
	// Loading header
	zx_loading(192+5, 0x28, 0x01, 3, 256);

	// Enable "Program"
	pal_col(9,0x0f);

	// Border white...
	zx_border(0x10);

	// ...for 95 frames
	//skip_frames(95);
	while (muspos < 250) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}
	

	// Border red
	zx_border(0x05);

	//skip_frames(70);
	while (muspos < 290) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	// Block 2:
	// Pilotone
	zx_loading(290+192, 0x2c, 0x05, 4, 0);
	// Loadind basic code
	zx_loading(290+192+6, 0x28, 0x01, 5, 256);

	// "Program" off
	pal_col(9,0x20);
	pal_col(10,0x0f);

	// Paper 0, "Bill Gilbert" enable
	pal_col(5,0x30);
	pal_col(6,0x0f);
	pal_col(7,0x06);


	zx_border(0x2c);

	//skip_frames(10);
	while (muspos < 290+192+20+10) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	zx_border(0x05);

	//skip_frames(25);
	while (muspos < 290+192+20+10+25) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	// Block 3:
	zx_loading(290+192+192, 0x06, 0x0f, 2, 0);

	multi_vram_buffer_horz((unsigned char *) nametable_part1_bytes, 22, NAMETABLE_A+32 * 7 + 4);
	multi_vram_buffer_horz((unsigned char *) nametable_part1_bytes, 22, NAMETABLE_B+32 * 7 + 4);

	zx_loading(290+192+192+5, 0x10, 0x01, 3, 256);

	zx_border(0x06);

	//skip_frames(40);
	while (muspos < 290+192+192+5+25) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}
	
	zx_border(0x0f);

	//skip_frames(55);
	while (muspos < 290+192+192+5+50) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	// Block 4:
	zx_loading(290+192+192+192, 0x14, 0x07, 4, 0);
	
	clear_vram_buffer();
	multi_vram_buffer_horz((unsigned char *) nametable_part1_visuals, 22, NAMETABLE_A+32 * 9 + 4);
	multi_vram_buffer_horz((unsigned char *) nametable_part1_visuals, 22, NAMETABLE_B+32 * 9 + 4);

	zx_loading(290+192+192+192+5, 0x1c, 0x05, 5, 256);

	zx_border(0x04);

	//skip_frames(40);
	while (muspos < 290+192+192+192+5+25) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	zx_border(0x0f);

	//skip_frames(55);
	while (muspos < 290+192+192+192+5+50) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	// Block 5:
	zx_loading(290+192+192+192+192, 0x2c, 0x0c, 4, 0);

	clear_vram_buffer();
	multi_vram_buffer_horz((unsigned char *) nametable_part1_music, 22, NAMETABLE_A+32 * 11 + 4);
	multi_vram_buffer_horz((unsigned char *) nametable_part1_music, 22, NAMETABLE_B+32 * 11 + 4);

	zx_loading(290+192+192+192+192+5, 0x28, 0x01, 3, 256);

	zx_border(0x02);

	//skip_frames(30);
	while (muspos < 290+192+192+192+192+5+25) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	zx_border(0x2c);

	//skip_frames(25);
	while (muspos < 290+192+192+192+192+5+50) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}

	// Block 6:
	zx_loading(290+192+192+192+192+192, 0x27, 0x05, 2, 0);
	zx_loading(290+192+192+192+192+192+5, 0x28, 0x01, 6, 256);

	zx_border(0x05);

//	skip_frames(45);

//	zx_border(0x02);

	_pal_fade_to(0);
	scroll(0,0);
	clear_vram_buffer();

//	zx_border(0x0f);
//	pal_col(5, 0x0f);
//	pal_col(6, 0x0f);
//	pal_col(7, 0x0f);
//	pal_col(9,0x0f);
//
	//skip_frames(15);
	
	while (muspos < 290+192+192+192+192+192 +32) {
		ppu_wait_nmi();
		muspos = get_mus_pos();
	}
	
//	_pal_fade_to(0);
}
