;this file for FamiTone2 library generated by text2data tool

music_music_data:
	.byte 1
	.word @instruments
	.word @samples-3
	.word @song0ch0,@song0ch1,@song0ch2,@song0ch3,@song0ch4,307,256

@instruments:
	.byte $b0 ;instrument $00
	.word @env1,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $01
	.word @env4,@env0,@env0
	.byte $00
	.byte $f0 ;instrument $02
	.word @env2,@env15,@env0
	.byte $00
	.byte $f0 ;instrument $03
	.word @env3,@env15,@env0
	.byte $00
	.byte $f0 ;instrument $04
	.word @env2,@env16,@env0
	.byte $00
	.byte $f0 ;instrument $05
	.word @env3,@env16,@env0
	.byte $00
	.byte $f0 ;instrument $06
	.word @env2,@env17,@env0
	.byte $00
	.byte $f0 ;instrument $07
	.word @env3,@env17,@env0
	.byte $00
	.byte $f0 ;instrument $08
	.word @env2,@env18,@env0
	.byte $00
	.byte $f0 ;instrument $09
	.word @env3,@env18,@env0
	.byte $00
	.byte $30 ;instrument $0a
	.word @env1,@env14,@env0
	.byte $00
	.byte $30 ;instrument $0b
	.word @env1,@env19,@env0
	.byte $00
	.byte $30 ;instrument $0c
	.word @env5,@env20,@env0
	.byte $00
	.byte $30 ;instrument $0d
	.word @env6,@env21,@env0
	.byte $00
	.byte $30 ;instrument $0e
	.word @env7,@env22,@env0
	.byte $00
	.byte $30 ;instrument $0f
	.word @env8,@env23,@env0
	.byte $00
	.byte $30 ;instrument $10
	.word @env9,@env24,@env0
	.byte $00
	.byte $30 ;instrument $11
	.word @env10,@env25,@env0
	.byte $00
	.byte $30 ;instrument $12
	.word @env11,@env26,@env0
	.byte $00
	.byte $30 ;instrument $13
	.word @env12,@env27,@env0
	.byte $00
	.byte $30 ;instrument $14
	.word @env13,@env28,@env0
	.byte $00

@samples:
@env0:
	.byte $c0,$00,$00
@env1:
	.byte $cf,$00,$00
@env2:
	.byte $c0,$c1,$c1,$c2,$c2,$c3,$c3,$c4,$c4,$c5,$02,$c6,$c6,$c7,$c7,$c8
	.byte $c8,$c9,$c9,$ca,$ca,$cb,$cb,$00,$16
@env3:
	.byte $cd,$02,$cc,$03,$cb,$02,$ca,$03,$c9,$03,$c8,$02,$c7,$03,$c6,$03
	.byte $c5,$02,$c4,$03,$c3,$02,$c2,$03,$c1,$03,$c0,$00,$1a
@env4:
	.byte $c5,$00,$00
@env5:
	.byte $c9,$c5,$c3,$c0,$00,$03
@env6:
	.byte $c0,$c1,$c2,$c2,$c3,$c3,$c4,$c5,$c5,$c6,$c7,$c7,$c8,$c8,$c9,$ca
	.byte $ca,$cb,$cc,$cc,$cd,$cd,$ce,$cf,$cd,$cb,$c9,$c7,$c5,$c3,$c2,$c0
	.byte $00,$1f
@env7:
	.byte $cf,$04,$c0,$00,$02
@env8:
	.byte $c9,$c8,$c7,$c7,$c6,$c6,$c5,$c5,$c4,$c4,$c3,$03,$c2,$03,$c1,$04
	.byte $c0,$00,$10
@env9:
	.byte $cf,$09,$c0,$00,$02
@env10:
	.byte $cf,$ce,$cd,$cc,$cb,$ca,$c9,$c8,$c7,$c6,$c5,$c4,$c3,$c2,$c1,$00
	.byte $0e
@env11:
	.byte $cf,$cf,$c0,$cf,$cf,$c0,$cf,$cf,$c0,$cf,$04,$c0,$00,$0b
@env12:
	.byte $cf,$cb,$c5,$cf,$cb,$c5,$cf,$cb,$c5,$cf,$cb,$c5,$c4,$c3,$c2,$c1
	.byte $00,$0f
@env13:
	.byte $c9,$c5,$c3,$03,$c2,$07,$c1,$08,$c0,$00,$08
@env14:
	.byte $c0,$02,$bf,$04,$be,$03,$bd,$04,$bc,$03,$bb,$04,$ba,$03,$b9,$03
	.byte $b8,$04,$b7,$03,$b6,$b6,$b5,$b5,$b4,$00,$18
@env15:
	.byte $c0,$c0,$c3,$c3,$c7,$c7,$ca,$cc,$cf,$00,$00
@env16:
	.byte $c0,$c0,$c2,$c2,$c7,$c7,$ca,$cc,$ce,$00,$00
@env17:
	.byte $c0,$c0,$c2,$c2,$c5,$c5,$ca,$cc,$ce,$00,$00
@env18:
	.byte $c0,$c0,$c4,$c4,$c7,$c7,$c9,$cc,$c4,$00,$00
@env19:
	.byte $ab,$ac,$ad,$ad,$ae,$ae,$af,$02,$b0,$b0,$b1,$02,$b2,$b2,$b3,$b3
	.byte $b4,$02,$b5,$b5,$b6,$02,$b7,$b7,$b8,$b8,$b9,$02,$ba,$ba,$bb,$02
	.byte $bc,$bc,$bd,$bd,$be,$02,$bf,$bf,$c0,$00,$28
@env20:
	.byte $bc,$be,$bf,$c0,$00,$03
@env21:
	.byte $b5,$b5,$b6,$b6,$b7,$b7,$b8,$02,$b9,$b9,$ba,$ba,$bb,$bb,$bc,$bc
	.byte $bd,$bd,$be,$be,$bf,$bf,$c0,$00,$16
@env22:
	.byte $bc,$b8,$ae,$a9,$00,$03
@env23:
	.byte $c0,$09,$bf,$0b,$be,$0a,$bd,$0a,$bc,$02,$bc,$00,$0a
@env24:
	.byte $c0,$be,$bc,$ba,$b8,$b6,$b4,$b2,$b0,$00,$08
@env25:
	.byte $c6,$c3,$c0,$bd,$c0,$bd,$c0,$bd,$c0,$bd,$00,$09
@env26:
	.byte $c0,$bb,$b6,$c0,$bb,$b6,$c0,$bb,$b6,$c0,$bb,$b6,$b4,$b2,$b0,$00
	.byte $0e
@env27:
	.byte $c6,$c3,$c0,$c6,$c3,$c0,$c6,$c3,$c0,$bd,$c0,$bd,$c0,$bd,$c0,$bd
	.byte $00,$0f
@env28:
	.byte $bc,$be,$00,$01


@song0ch0:
	.byte $fb,$03
@ref0:
	.byte $fb,$0c,$80,$5a,$9d,$fb,$03,$82,$63,$00,$85,$fb,$08,$93,$fb,$0c
	.byte $80,$5a,$9d,$fb,$03,$82,$63,$00,$99
@ref1:
	.byte $80,$5a,$dd,$82,$63,$00,$99
	.byte $ff,$05
	.word @ref1
@ref3:
	.byte $80,$58,$dd,$82,$5f,$00,$99
	.byte $ff,$05
	.word @ref3
@ref5:
	.byte $80,$5a,$85,$43,$82,$5b,$80,$4d,$82,$43,$80,$5b,$82,$4d,$80,$43
	.byte $82,$5b,$80,$4d,$82,$43,$80,$5b,$82,$4d,$80,$43,$82,$5b,$80,$3d
	.byte $82,$43,$80,$43,$82,$3d,$80,$4d,$82,$43,$80,$43,$82,$4d,$80,$43
	.byte $82,$43,$80,$4d,$82,$43,$80,$55,$82,$4d,$80,$4d,$82,$54,$81
@ref6:
	.byte $80,$5b,$82,$4d,$80,$41,$82,$5b,$80,$47,$82,$41,$80,$5b,$82,$47
	.byte $80,$41,$82,$5b,$80,$47,$82,$41,$80,$59,$82,$47,$80,$41,$82,$59
	.byte $80,$47,$82,$41,$80,$5f,$82,$47,$80,$41,$82,$5f,$80,$47,$82,$41
	.byte $80,$59,$82,$47,$80,$41,$82,$59,$80,$51,$82,$41,$80,$47,$82,$50
	.byte $81
@ref7:
	.byte $80,$59,$82,$47,$80,$41,$82,$59,$80,$51,$82,$41,$80,$5f,$82,$51
	.byte $80,$41,$82,$5f,$80,$51,$82,$41,$80,$59,$82,$51,$80,$41,$82,$59
	.byte $80,$51,$82,$41,$80,$5f,$82,$51,$80,$41,$82,$5f,$80,$51,$82,$41
	.byte $80,$59,$82,$51,$80,$47,$82,$59,$80,$55,$82,$47,$80,$51,$82,$54
	.byte $81
@ref8:
	.byte $80,$59,$82,$51,$80,$41,$82,$59,$80,$51,$82,$41,$80,$5f,$82,$51
	.byte $80,$41,$82,$5f,$80,$51,$82,$41,$80,$59,$82,$51,$80,$41,$82,$59
	.byte $80,$51,$82,$41,$80,$5f,$82,$51,$80,$41,$82,$5f,$80,$51,$82,$41
	.byte $80,$59,$82,$51,$01,$59,$00,$8d
@song0ch0loop:
@ref9:
	.byte $80,$62,$64,$8b,$00,$85,$62,$89,$01,$58,$5a,$83,$01,$59,$00,$85
	.byte $58,$5a,$8b,$00,$85,$58,$89,$00,$89,$4e,$50,$83,$00,$85
@ref10:
	.byte $5c,$5e,$8b,$00,$85,$62,$89,$01,$58,$5a,$83,$01,$59,$00,$85,$5c
	.byte $5e,$8b,$00,$85,$5a,$89,$01,$4d,$51,$55,$4d,$55,$58,$81
@ref11:
	.byte $58,$5a,$87,$01,$58,$85,$00,$85,$54,$85,$58,$85,$00,$85,$58,$5a
	.byte $87,$01,$5e,$85,$01,$5a,$85,$01,$54,$58,$83,$55,$51,$47,$41,$47
	.byte $50,$81
@ref12:
	.byte $56,$58,$87,$55,$00,$85,$5c,$5e,$87,$59,$00,$85,$60,$62,$8b,$69
	.byte $5f,$63,$59,$5e,$54,$58,$50,$54,$4a,$50,$46,$4a,$50,$54,$50,$54
	.byte $58,$54,$58,$5e,$58,$5e,$60,$62,$85
@ref13:
	.byte $00,$85,$58,$5a,$83,$58,$85,$5a,$85,$00,$85,$54,$85,$00,$85,$5a
	.byte $85,$00,$85,$62,$64,$83,$5a,$85,$58,$85,$00,$85,$60,$62,$83,$58
	.byte $85,$54,$85
@ref14:
	.byte $00,$85,$54,$58,$83,$54,$85,$58,$85,$00,$85,$5e,$85,$00,$85,$62
	.byte $85,$00,$85,$66,$68,$83,$62,$85,$58,$85,$60,$62,$83,$58,$85,$54
	.byte $85,$58,$85
@ref15:
	.byte $00,$85,$56,$58,$83,$54,$85,$58,$85,$50,$85,$46,$85,$50,$85,$5c
	.byte $5e,$83,$00,$85,$58,$85,$00,$85,$62,$85,$00,$85,$56,$58,$83,$54
	.byte $85,$58,$85
@ref16:
	.byte $00,$85,$5c,$5e,$87,$4a,$85,$82,$5f,$80,$4e,$50,$83,$5c,$5e,$87
	.byte $4a,$85,$82,$5f,$80,$52,$54,$83,$5e,$85,$4b,$51,$55,$4b,$51,$59
	.byte $4b,$59,$60,$62,$8b
@ref17:
	.byte $00,$85,$65,$01,$65,$01,$63,$01,$63,$01,$5b,$01,$58,$5a,$87,$01
	.byte $5b,$01,$5b,$01,$59,$01,$59,$01,$56,$58,$83,$51,$01,$4e,$50,$83
	.byte $4b,$00,$81
@ref18:
	.byte $87,$63,$01,$63,$01,$48,$4a,$83,$59,$01,$59,$00,$89,$52,$54,$83
	.byte $59,$01,$59,$01,$4e,$50,$83,$63,$01,$60,$62,$83,$00,$85,$5c,$5e
	.byte $87,$00,$81
@ref19:
	.byte $87,$5f,$01,$5f,$01,$51,$01,$59,$01,$59,$00,$89,$55,$01,$59,$01
	.byte $59,$01,$51,$01,$55,$01,$52,$54,$83,$00,$85,$4e,$50,$83,$00,$85
@ref20:
	.byte $87,$59,$01,$59,$01,$55,$01,$58,$00,$59,$01,$55,$01,$5e,$00,$5f
	.byte $01,$59,$01,$62,$00,$63,$5c,$5e,$83,$68,$00,$69,$60,$62,$83,$6c
	.byte $68,$62,$5e,$68,$62,$5e,$58,$62,$5e,$58,$50
@ref21:
	.byte $00,$f9,$83
@ref22:
	.byte $00,$f9,$83
@ref23:
	.byte $f9,$85
@ref24:
	.byte $f9,$85
@ref25:
	.byte $5a,$a5,$82,$5a,$85
	.byte $fd
	.word @song0ch0loop

@song0ch1:
@ref26:
	.byte $00,$f9,$83
@ref27:
	.byte $84,$3c,$dd,$86,$3c,$9d
@ref28:
	.byte $88,$3c,$dd,$8a,$3c,$9d
@ref29:
	.byte $8c,$3c,$dd,$8e,$3c,$9d
@ref30:
	.byte $90,$38,$dd,$92,$38,$9d
	.byte $ff,$04
	.word @ref27
	.byte $ff,$04
	.word @ref28
	.byte $ff,$04
	.word @ref29
	.byte $ff,$04
	.word @ref30
@song0ch1loop:
@ref35:
	.byte $86,$3c,$95,$3c,$a5,$3c,$95,$3c,$a5
@ref36:
	.byte $8a,$3c,$95,$3c,$a5,$3c,$95,$3c,$95,$3c,$8d
@ref37:
	.byte $8e,$3c,$95,$3c,$a5,$3c,$95,$3c,$a5
@ref38:
	.byte $92,$38,$95,$38,$a5,$38,$95,$38,$95,$38,$8d
	.byte $ff,$08
	.word @ref35
	.byte $ff,$0a
	.word @ref36
	.byte $ff,$08
	.word @ref37
	.byte $ff,$0a
	.word @ref38
	.byte $ff,$08
	.word @ref35
	.byte $ff,$0a
	.word @ref36
	.byte $ff,$08
	.word @ref37
	.byte $ff,$0a
	.word @ref38
@ref47:
	.byte $86,$3c,$95,$3c,$a5,$3c,$95,$3c,$95,$40,$8d
@ref48:
	.byte $3c,$95,$3c,$a5,$3c,$95,$3c,$95,$40,$8d
@ref49:
	.byte $92,$38,$95,$38,$a5,$38,$95,$38,$95,$8a,$3c,$8d
	.byte $ff,$0a
	.word @ref49
@ref51:
	.byte $00,$ad
	.byte $fd
	.word @song0ch1loop

@song0ch2:
@ref52:
	.byte $00,$dd,$96,$34,$9d
@ref53:
	.byte $94,$34,$dd,$00,$9d
@ref54:
	.byte $80,$1a,$dd,$96,$20,$9d
@ref55:
	.byte $80,$20,$dd,$96,$16,$9d
@ref56:
	.byte $80,$16,$dd,$96,$34,$9d
@ref57:
	.byte $94,$34,$bd,$00,$85,$80,$1c,$85,$00,$8d,$1c,$85,$00,$85,$1c,$85
	.byte $00,$85
@ref58:
	.byte $1a,$bd,$94,$1a,$9d,$96,$20,$9d
@ref59:
	.byte $80,$20,$bd,$00,$85,$20,$85,$00,$8d,$20,$85,$00,$85,$20,$85,$00
	.byte $85
@ref60:
	.byte $16,$bd,$94,$16,$9d,$00,$9d
@song0ch2loop:
@ref61:
	.byte $9c,$41,$80,$1d,$01,$1d,$a0,$49,$80,$2b,$9c,$41,$80,$35,$9c,$41
	.byte $80,$35,$25,$2b,$a0,$49,$80,$2b,$21,$1d,$9c,$41,$80,$1d,$01,$1d
	.byte $a0,$49,$80,$2b,$9c,$41,$80,$35,$9c,$41,$80,$35,$25,$2b,$a0,$49
	.byte $80,$2b,$21,$a4,$48,$81
@ref62:
	.byte $9c,$41,$80,$1b,$33,$01,$a0,$49,$80,$25,$9c,$41,$80,$25,$9c,$41
	.byte $80,$2b,$25,$01,$a0,$49,$80,$2b,$25,$33,$9c,$41,$80,$1b,$33,$a4
	.byte $49,$a0,$49,$80,$25,$9c,$41,$80,$25,$a0,$49,$80,$2b,$25,$9c,$41
	.byte $a0,$49,$80,$2b,$9c,$41,$80,$32,$81
@ref63:
	.byte $9c,$41,$80,$29,$2f,$29,$a0,$49,$80,$39,$9c,$41,$80,$2f,$9c,$41
	.byte $80,$2f,$39,$41,$a0,$49,$80,$2f,$29,$01,$9c,$41,$80,$29,$9c,$41
	.byte $80,$29,$a0,$49,$80,$39,$9c,$41,$80,$2f,$9c,$41,$80,$2f,$29,$a4
	.byte $49,$a0,$49,$80,$39,$2f,$a0,$48,$81
@ref64:
	.byte $9c,$41,$80,$1b,$33,$01,$a0,$49,$80,$33,$9c,$41,$80,$25,$9c,$41
	.byte $80,$25,$33,$01,$a0,$49,$80,$25,$21,$29,$9c,$41,$80,$1b,$33,$9c
	.byte $41,$a0,$49,$80,$33,$9c,$41,$80,$25,$a0,$48,$85,$80,$21,$29,$a0
	.byte $49,$80,$25,$21,$a4,$48,$81
	.byte $ff,$21
	.word @ref61
	.byte $ff,$21
	.word @ref62
	.byte $ff,$21
	.word @ref63
	.byte $ff,$21
	.word @ref64
	.byte $ff,$21
	.word @ref61
	.byte $ff,$21
	.word @ref62
	.byte $ff,$21
	.word @ref63
	.byte $ff,$21
	.word @ref64
@ref73:
	.byte $9c,$41,$80,$1d,$01,$1c,$85,$2b,$9c,$41,$80,$35,$a0,$49,$80,$35
	.byte $25,$2b,$01,$2b,$21,$1d,$9c,$41,$80,$1d,$01,$1d,$01,$2b,$9c,$41
	.byte $80,$35,$a0,$49,$80,$35,$25,$2b,$01,$2b,$21,$a4,$48,$81
	.byte $ff,$21
	.word @ref73
@ref75:
	.byte $9c,$41,$80,$1b,$33,$00,$85,$33,$9c,$41,$80,$25,$a0,$49,$80,$25
	.byte $33,$00,$85,$25,$21,$29,$9c,$41,$80,$1b,$33,$9c,$40,$85,$80,$33
	.byte $9c,$41,$80,$25,$a0,$48,$85,$80,$21,$28,$85,$25,$21,$a4,$48,$81
@ref76:
	.byte $9c,$41,$80,$1b,$33,$00,$85,$33,$9c,$41,$80,$25,$a0,$49,$80,$25
	.byte $33,$00,$85,$25,$21,$29,$9c,$41,$80,$1b,$33,$9c,$41,$a0,$49,$80
	.byte $33,$9c,$41,$80,$25,$a0,$48,$85,$80,$21,$29,$a0,$49,$80,$25,$21
	.byte $a4,$48,$81
@ref77:
	.byte $00,$ad
	.byte $fd
	.word @song0ch2loop

@song0ch3:
@ref78:
	.byte $00,$9d,$80,$14,$0f,$20,$00,$b5,$14,$0f,$20,$00,$95
@ref79:
	.byte $02,$04,$06,$08,$0a,$0a,$0c,$0c,$0e,$0e,$10,$10,$12,$12,$14,$14
	.byte $16,$16,$18,$18,$1a,$1a,$1c,$1c,$1e,$1e,$00,$a9,$14,$0f,$20,$00
	.byte $95
@ref80:
	.byte $df,$14,$0f,$20,$00,$95
	.byte $ff,$06
	.word @ref80
	.byte $ff,$06
	.word @ref80
@ref83:
	.byte $02,$04,$06,$08,$0a,$0a,$0c,$0c,$0e,$0e,$10,$10,$12,$12,$14,$14
	.byte $16,$16,$18,$18,$1a,$1a,$1c,$1c,$1e,$1e,$01,$98,$02,$85,$1c,$85
	.byte $02,$95,$80,$14,$0f,$20,$00,$85,$98,$1c,$8d
@ref84:
	.byte $1c,$9d,$1c,$95,$02,$85,$1c,$85,$02,$95,$80,$14,$0f,$20,$98,$02
	.byte $8d,$02,$85
@ref85:
	.byte $1c,$9d,$1c,$95,$02,$85,$1c,$85,$02,$95,$80,$14,$0f,$20,$00,$85
	.byte $98,$02,$8d
@ref86:
	.byte $1c,$9d,$1c,$95,$02,$85,$1c,$8d,$20,$8d,$20,$85,$02,$85,$9a,$1e
	.byte $8d
@song0ch3loop:
@ref87:
	.byte $9e,$18,$85,$98,$1d,$21,$a2,$12,$85,$a8,$1c,$85,$98,$1d,$21,$03
	.byte $1d,$a2,$14,$85,$98,$1d,$21,$9e,$18,$85,$98,$1d,$21,$a2,$12,$85
	.byte $a8,$1c,$85,$98,$1d,$21,$03,$1d,$a2,$14,$85,$98,$1d,$a6,$12,$81
@ref88:
	.byte $9e,$18,$85,$98,$1d,$21,$a2,$12,$85,$a8,$1c,$85,$98,$1d,$21,$03
	.byte $1d,$a2,$14,$85,$98,$1d,$21,$9e,$18,$85,$98,$1d,$a6,$13,$a2,$12
	.byte $85,$a8,$1c,$85,$a2,$12,$85,$98,$03,$1d,$a2,$14,$85,$a8,$1d,$98
	.byte $20,$81
@ref89:
	.byte $9e,$18,$85,$98,$1d,$21,$a2,$12,$85,$a8,$1c,$85,$98,$1d,$21,$03
	.byte $1d,$a2,$14,$85,$98,$1d,$21,$9e,$18,$85,$a8,$1d,$98,$21,$a2,$12
	.byte $85,$a8,$1c,$85,$98,$1d,$21,$03,$a6,$13,$a2,$14,$85,$98,$1d,$a2
	.byte $12,$81
@ref90:
	.byte $9e,$18,$85,$98,$1d,$21,$a2,$12,$85,$a8,$1c,$85,$98,$1d,$21,$03
	.byte $1d,$a2,$14,$85,$98,$1d,$21,$9e,$18,$85,$98,$1d,$21,$a2,$12,$85
	.byte $a8,$1c,$85,$a2,$14,$85,$98,$03,$1d,$a2,$14,$85,$98,$1d,$a6,$12
	.byte $81
	.byte $ff,$21
	.word @ref87
	.byte $ff,$21
	.word @ref88
	.byte $ff,$21
	.word @ref89
	.byte $ff,$21
	.word @ref90
	.byte $ff,$21
	.word @ref87
	.byte $ff,$21
	.word @ref88
	.byte $ff,$21
	.word @ref89
	.byte $ff,$21
	.word @ref90
@ref99:
	.byte $9e,$18,$85,$98,$1d,$20,$89,$a8,$1c,$85,$a2,$12,$85,$98,$03,$1c
	.byte $89,$1d,$21,$9e,$18,$85,$98,$1d,$21,$00,$85,$a8,$1c,$85,$a2,$14
	.byte $85,$98,$03,$1c,$89,$1d,$a6,$12,$81
	.byte $ff,$1e
	.word @ref99
@ref101:
	.byte $9e,$18,$85,$98,$1d,$20,$89,$a8,$1c,$85,$a2,$14,$85,$98,$03,$1c
	.byte $89,$1d,$21,$9e,$18,$85,$98,$1d,$20,$89,$a8,$1c,$85,$a2,$14,$85
	.byte $98,$03,$1c,$89,$1d,$a6,$12,$81
@ref102:
	.byte $9e,$18,$85,$98,$1d,$20,$89,$a8,$1c,$85,$a2,$14,$85,$98,$03,$1c
	.byte $89,$1d,$21,$9e,$18,$85,$98,$1d,$21,$a2,$12,$85,$a8,$1c,$85,$a2
	.byte $14,$85,$98,$03,$1d,$a2,$14,$85,$98,$1d,$a6,$12,$81
@ref103:
	.byte $00,$9d,$9a,$1e,$8d
	.byte $fd
	.word @song0ch3loop

@song0ch4:
@ref104:
	.byte $f9,$85
@ref105:
	.byte $f9,$85
@ref106:
	.byte $f9,$85
@ref107:
	.byte $f9,$85
@ref108:
	.byte $f9,$85
@ref109:
	.byte $f9,$85
@ref110:
	.byte $f9,$85
@ref111:
	.byte $f9,$85
@ref112:
	.byte $f9,$85
@song0ch4loop:
@ref113:
	.byte $f9,$85
@ref114:
	.byte $f9,$85
@ref115:
	.byte $f9,$85
@ref116:
	.byte $f9,$85
@ref117:
	.byte $f9,$85
@ref118:
	.byte $f9,$85
@ref119:
	.byte $f9,$85
@ref120:
	.byte $f9,$85
@ref121:
	.byte $f9,$85
@ref122:
	.byte $f9,$85
@ref123:
	.byte $f9,$85
@ref124:
	.byte $f9,$85
@ref125:
	.byte $f9,$85
@ref126:
	.byte $f9,$85
@ref127:
	.byte $f9,$85
@ref128:
	.byte $f9,$85
@ref129:
	.byte $af
	.byte $fd
	.word @song0ch4loop
