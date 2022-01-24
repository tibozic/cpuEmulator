# CPU emulator in C

-6502 <br>
-8080 <br>

## currently at:
https://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c
http://www.emulator101.com/disassembler-pt-1.html

## sources:
https://web.archive.org/web/20210909190432/http://www.obelisk.me.uk/6502/ <br>
https://youtu.be/qJgsuQoy9bc <br>
http://www.emulator101.com/ <br>
https://www.reddit.com/r/C_Programming/comments/9dzkhw/how_would_one_write_an_emulator_in_c/ <br>
http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf <br>
https://github.com/Gekkio/mooneye-gb <br>
https://phoenix.goucher.edu/~jillz/cs220/cpuEmulatorTutorial.pdf <br>
https://stackoverflow.com/questions/1215777/writing-a-graphical-z80-emulator-in-c-or-c <br>
https://drakeor.com/uploads/8080-Programmers-Manual.pdf <br>

## notes:
HEX/BIN/DEC:
hex: 0xff
bin: 0b10
dec: default

### CPU (8080):
5 registers (A, B, C, D, E) -> like variables
program counter (PC) -> like a pointer
the time of to run an instruction is given by manufacturer (in cycles) -> move takes 1 cycle
