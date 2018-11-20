;written by Doug Fraker 2018
;v 1.01

.export _set_vram_buffer, _multi_vram_buffer_horz, _multi_vram_buffer_vert, _one_vram_buffer
.export _clear_vram_buffer, _get_pad_new, _get_frame_count, _set_music_speed

.export _gray_line

.segment "CODE"




;void set_vram_buffer(void)
_set_vram_buffer:
	lda #$ff
	sta VRAM_BUF
	ldx #>VRAM_BUF
	lda #<VRAM_BUF
	jmp _set_vram_update
	
	

	
;void multi_vram_buffer_horz(char * data, unsigned char len, int ppu_address);
_multi_vram_buffer_horz:
	;note PTR = TEMP and TEMP+1

	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
	clc
	adc #$40 ; NT_UPD_HORZ
	sta VRAM_BUF, y
	
_multi_vram_buffer_common:
	jsr popa ;len
		sta TEMP+3 ;loop count
		ldy VRAM_INDEX
		sta VRAM_BUF+2, y
	jsr popax ;pointer to data
		sta <PTR
		stx <PTR+1
	ldx VRAM_INDEX ;need y for source, x is for dest and for vram_index
		inx
		inx
		inx
		
	ldy #0
@loop:
	lda (PTR), y
	sta VRAM_BUF, x
	inx
	iny
	cpy TEMP+3
	bne @loop
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, x
	stx VRAM_INDEX
	rts
	
	
	

;void multi_vram_buffer_vert(char * data, unsigned char len, int ppu_address);
_multi_vram_buffer_vert:
	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
	clc
	adc #$80 ; NT_UPD_VERT
	sta VRAM_BUF, y
	
	jmp _multi_vram_buffer_common
	
	
	

;void one_vram_buffer(unsigned char data, int ppu_address);
_one_vram_buffer:
	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
	sta VRAM_BUF, y
	iny
	iny
		sty <TEMP ;popa uses y
	jsr popa
		ldy <TEMP
	sta VRAM_BUF, y
	iny
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, y
	sty VRAM_INDEX
	rts
	
	
	
	
;void clear_vram_buffer(void);	
_clear_vram_buffer:
	lda #0
	sta VRAM_INDEX
	lda #$ff
	sta VRAM_BUF
	rts
	
	
	
	
;unsigned char __fastcall__ get_pad_new(unsigned char pad);	
_get_pad_new:
	tay
	lda <PAD_STATET,y
	ldx #0
	rts
	
	
	
	
;unsigned char __fastcall__ get_frame_count(void);	
_get_frame_count:
	lda <FRAME_CNT1
	ldx #0
	rts
	
	
	
	
;void __fastcall__ set_music_speed(unsigned char tempo);
_set_music_speed:
	sta FT_SONG_SPEED
	rts
	
PTR2 = TEMP+2 ;and TEMP+3

;void gray_line(void);
_gray_line:
	lda <PPU_MASK_VAR
	and #$1f ;no color emphasis bits
	ora #1 ;yes gray bit
	sta PPU_MASK
	
	ldx #20 ;wait
@loop:
	dex
	bne @loop
	
	lda <PPU_MASK_VAR
	and #$1e ;no gray bit
	ora #$e0 ;all color emphasis bits
	sta PPU_MASK
	
	ldx #20 ;wait
@loop2:
	dex
	bne @loop2
	
	lda <PPU_MASK_VAR ;normal
	sta PPU_MASK
	rts
	
	
	
	
;void seed_rng(void);
_seed_rng:
	lda <FRAME_CNT1
	sta <RAND_SEED
	rts
	
	
	
