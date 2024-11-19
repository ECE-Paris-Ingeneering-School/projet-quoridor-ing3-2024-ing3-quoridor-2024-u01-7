#include "game.h"
#include "player.h"
#include "display.h"
#include "save.h"
#include <stdio.h>
#include <windows.h>

void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}
