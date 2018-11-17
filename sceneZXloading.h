void sceneZXloading(void) {
	// "Program" title reset
	pal_col(9,0x10);
	pal_col(10,0x10);

	// "Bill Gilbert" reset
	pal_col(5,0x10);
	pal_col(6,0x10);
	pal_col(7,0x10);


	set_vram_update(titles_list);
	ppu_on_all();

	music_play(0);

	// Block 1:
	// Pilotone
	zx_loading(192, 0x2c, 0x05, 4, 0);
	// Loading header
	zx_loading(5, 0x28, 0x01, 3, 256);

	// Enable "Program"
	pal_col(9,0x0f);

	// Border white...
	zx_border(0x10);

	// ...for 95 frames
	skip_frames(95);

	// Border red
	zx_border(0x05);

	skip_frames(70);

	// Block 2:
	// Pilotone
	zx_loading(122, 0x2c, 0x05, 4, 0);
	// Loadind basic code
	zx_loading(20, 0x28, 0x01, 5, 256);

	// "Program" off
	pal_col(9,0x20);
	pal_col(10,0x0f);

	// Paper 0, "Bill Gilbert" enable
	pal_col(5,0x30);
	pal_col(6,0x0f);
	pal_col(7,0x06);


	zx_border(0x2c);

	skip_frames(10);

	zx_border(0x05);

	skip_frames(25);

	// Block 3:
	zx_loading(142, 0x06, 0x0f, 2, 0);

	memcpy((unsigned char*) titles_list+3, nametable_part1_bytes, 22);
	memcpy((unsigned char*) titles_list+3+25, nametable_part1_bytes, 22);

	zx_loading(5, 0x10, 0x01, 3, 256);

	zx_border(0x06);

	skip_frames(40);
	
	zx_border(0x0f);

	skip_frames(55);

	// Block 4:
	zx_loading(90, 0x14, 0x07, 4, 0);
	
	titles_list[0]=MSB(NTADR_A(4,9))|NT_UPD_HORZ;
	titles_list[1]=LSB(NTADR_A(4,9));
	titles_list[25]=MSB(NTADR_B(4,9))|NT_UPD_HORZ;
	titles_list[26]=LSB(NTADR_B(4,9));

	memcpy((unsigned char*) titles_list+3, nametable_part1_visuals, 22);
	memcpy((unsigned char*) titles_list+3+25, nametable_part1_visuals, 22);

	zx_loading(5, 0x1c, 0x05, 5, 256);

	zx_border(0x04);

	skip_frames(40);

	zx_border(0x0f);

	skip_frames(55);

	// Block 5:
	zx_loading(90, 0x2c, 0x0c, 4, 0);

	titles_list[0]=MSB(NTADR_A(4,11))|NT_UPD_HORZ;
	titles_list[1]=LSB(NTADR_A(4,11));
	titles_list[25]=MSB(NTADR_B(4,11))|NT_UPD_HORZ;
	titles_list[26]=LSB(NTADR_B(4,11));

	memcpy((unsigned char*) titles_list+3, nametable_part1_music, 22);
	memcpy((unsigned char*) titles_list+3+25, nametable_part1_music, 22);

	zx_loading(5, 0x28, 0x01, 3, 256);

	zx_border(0x02);

	skip_frames(30);

	zx_border(0x2c);

	skip_frames(25);

	// Block 6:
	zx_loading(130, 0x27, 0x05, 2, 0);
	zx_loading(5, 0x28, 0x01, 6, 256);

	zx_border(0x05);

//	skip_frames(45);

//	zx_border(0x02);

	_pal_fade_to(0);
//	zx_border(0x0f);
//	pal_col(5, 0x0f);
//	pal_col(6, 0x0f);
//	pal_col(7, 0x0f);
//	pal_col(9,0x0f);
//
//	skip_frames(25);
//	_pal_fade_to(0);
}
