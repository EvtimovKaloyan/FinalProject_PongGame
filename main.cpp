
#include "Game.h"

#include <iostream>
#include <ctime>

Game* game = NULL;

const int WINDOW_WIDTH = 1096;
const int WINDOW_HEIGHT = 608;

int main(int argc, char* argv[])
{
    game = new Game();
    
    game->init("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    while (game->isRunning()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}