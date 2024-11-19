#include "game.h"
#include "player.h"
#include "display.h"
#include <stdio.h>

void set_text_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
