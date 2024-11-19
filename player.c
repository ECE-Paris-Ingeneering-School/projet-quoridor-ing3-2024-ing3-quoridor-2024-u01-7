#include "game.h"
#include "player.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_symbol_unique(Player *players, int num_players, char symbol) {
    for (int i = 0; i < num_players; i++) {
        if (players[i].symbol == symbol) {
            return false;
        }
    }
    return true;
}
