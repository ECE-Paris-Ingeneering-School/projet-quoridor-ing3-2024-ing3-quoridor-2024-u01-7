#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include <windows.h>

void set_text_color(int color);
void display_colored_token(char token, int color);
void display_board(Game *game);
int getMouseClickPosition(int *row, int *col);

#endif
