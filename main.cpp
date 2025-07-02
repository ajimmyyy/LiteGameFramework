#include "include/Core/Game.h"

int main(int argc, char** argv) {
    Game* game = new Game;
    game->init();
    game->run();
}
