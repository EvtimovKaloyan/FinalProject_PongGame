#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Player.h"
#include "Ball.h"
#include <SDL_ttf.h>
#include <string>

class Game {
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();

	void paddleImpactCheck();

	void pointScoredCheck();

	void winnerCheck();

	void renderText(std::string);

	void renderText(std::string, int, int);

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* surface = NULL;
	bool running;
	bool gameOverFlag;

	Ball ball;
	Player player1;
	Player player2;

	SDL_Texture* textTextureFont1;
	SDL_Rect dRectFont1;

	TTF_Font* font1;
};