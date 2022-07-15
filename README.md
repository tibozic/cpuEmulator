# CPU emulator in C
The purpose of this project is to improve my knowledge of some low-level concepts and the workings
of a CPU, and to get some C programming experience other than the basic print or array-sorting exercises.

## More information
I will be trying to emulate a 6502 CPU. <br>
The goal is to understand how most of the instructions work and support them. <br>

My main reference was [6502 Introduction](https://web.archive.org/web/20210909190432/http://www.obelisk.me.uk/6502/), which lists all the instructions, what each
instruction does and how it works (what flags it effects). <br>
When I got stuck I also used [this youtube playlist](https://youtube.com/playlist?list=PLLwK93hM93Z13TRzPx9JqTIn33feefl37) which is doing the same thing I am
but in C++. <br>

## Files
*cpu.c\/cpu.h* are the main CPU emulation files. <br>
*main.c* is includes tests for the basic functionality. <br>
*makefile* compiles the files on linux. <br>
*mytests.c/mytests.h* a [simple tests library](https://github.com/tibozic/mytests). <br>

## Sources:
[6502 Introduction](https://web.archive.org/web/20210909190432/http://www.obelisk.me.uk/6502/) <br>
[6502 CPU Emulator in C++](https://youtube.com/playlist?list=PLLwK93hM93Z13TRzPx9JqTIn33feefl37) <br>
Google <br>

## Some other interesting/useful things:
https://www.reddit.com/r/C_Programming/comments/9dzkhw/how_would_one_write_an_emulator_in_c/ <br>
http://www.emulator101.com/ <br>
http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf <br>
https://phoenix.goucher.edu/~jillz/cs220/cpuEmulatorTutorial.pdf <br>
https://stackoverflow.com/questions/1215777/writing-a-graphical-z80-emulator-in-c-or-c <br>
https://drakeor.com/uploads/8080-Programmers-Manual.pdf <br>
