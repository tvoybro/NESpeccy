@set name="main"

@echo off

del %name%.nes

rem compile game

cc65 -Oi %name%.c --add-source

ca65 crt0.s
ca65 %name%.s

ld65 -C cnrom_horz.cfg -o %name%.nes crt0.o %name%.o runtime.lib


c:\Emuls\Nes\FCEux\fceux.exe %name%.nes

del %name%.s
del %name%.o
del crt0.o