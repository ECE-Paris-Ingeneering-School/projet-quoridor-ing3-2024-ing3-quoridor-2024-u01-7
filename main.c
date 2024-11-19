#include "game.h"
#include "player.h"
#include "menu.h"
#include "display.h"

int main() {
    Game game;

    while (1) {
        main_menu(&game);
        start_game(&game);
    }

    return 0;
}
