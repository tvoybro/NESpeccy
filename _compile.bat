@cd /d "%~dp0"

@set name="nespeccy"

@echo off

del %name%.nes

rem compile game

cc65\bin\cc65 -Oi %name%.c --add-source

cc65\bin\ca65 crt0.s
cc65\bin\ca65 %name%.s

cc65\bin\ld65 -C cnrom_horz.cfg -o %name%.nes crt0.o %name%.o runtime.lib -Ln labels.txt


%name%.nes

del %name%.s
del %name%.o
del crt0.o

pause 0