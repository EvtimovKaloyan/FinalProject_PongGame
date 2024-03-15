#include "Game.h"
#include "TextureManager.h"

#include <iostream>

Game::Game()
	:	player1("Player1", 0, 10, 260),
		player2("Player2", 0, 1076, 260),
		ball(535, 491)
{
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window != 0)		// window init success... otherwise will return NULL
		{
			std::cout << "window creation success\n";

			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				TextureManager::Instance()->loadTexture("C:/Users/kaloyan.evtimov/Desktop/Programming/C++EGT/Code/PongGame/x64/Debug/assets/table4.bmp", "table", renderer);

				TextureManager::Instance()->loadTexture("C:/Users/kaloyan.evtimov/Desktop/Programming/C++EGT/Code/PongGame/x64/Debug/assets/Barricade.bmp", "barricade", renderer);

				TextureManager::Instance()->loadTexture("C:/Users/kaloyan.evtimov/Desktop/Programming/C++EGT/Code/PongGame/x64/Debug/assets/Ball6.bmp", "ball", renderer);

				TextureManager::Instance()->loadTexture("C:/Users/kaloyan.evtimov/Desktop/Programming/C++EGT/Code/PongGame/x64/Debug/assets/Paddle1.bmp", "paddle1", renderer);

				TextureManager::Instance()->loadTexture("C:/Users/kaloyan.evtimov/Desktop/Programming/C++EGT/Code/PongGame/x64/Debug/assets/Paddle2.bmp", "paddle2", renderer);				
			}
			else
			{
				std::cout << "renderer init failed\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init failed\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init failed\n";
		return false;
	}

	std::cout << "init success\n";
	running = true;

	ttf_init();

	return true;
}

bool Game::ttf_init() {
	if (TTF_Init() == -1)
	{
		return false;
	}
	
	font1 = TTF_OpenFont("C:/Users/kaloyan.evtimov/Desktop/Programming/C++EGT/Code/PongGame/x64/Debug/fonts/Arcade.ttf", 48);
	
	if (font1 == NULL)
	{
		return false;
	}

	return true;
}

void Game::renderText(std::string text)
{
	SDL_Surface* tempSurfaceText = NULL;

	tempSurfaceText = TTF_RenderText_Blended(font1, text.c_str(), {0, 0, 255, 255});
	textTextureFont1 = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	int tw, th;

	SDL_QueryTexture(textTextureFont1, 0, 0, &tw, &th);
	dRectFont1 = { 498, 5, tw, th };

	SDL_FreeSurface(tempSurfaceText);
	
	SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);
}

void Game::renderText(std::string text, int xPos, int yPos)
{
	SDL_Surface* tempSurfaceText = NULL;

	tempSurfaceText = TTF_RenderText_Blended(font1, text.c_str(), { 0, 0, 255, 255 });
	textTextureFont1 = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	int tw, th;

	SDL_QueryTexture(textTextureFont1, 0, 0, &tw, &th);
	dRectFont1 = { xPos, yPos, tw, th };

	SDL_FreeSurface(tempSurfaceText);

	SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);
}

void Game::render() {
	SDL_RenderClear(renderer);

	TextureManager::Instance()->drawTexture("table", 0, 0, 1096, 608, renderer);

	TextureManager::Instance()->drawTexture("barricade", 541, 203, 15, 203, renderer);

	TextureManager::Instance()->drawTexture("ball", ball.getPosition().x, ball.getPosition().y, 26, 26, renderer);

	TextureManager::Instance()->drawTexture("paddle1", player1.getPosition().x, player1.getPosition().y, 10, 90, renderer);

	TextureManager::Instance()->drawTexture("paddle2", player2.getPosition().x, player2.getPosition().y, 10, 90, renderer);
	
	renderText(std::to_string(player1.getPoints()) + " : " + std::to_string(player2.getPoints()));
	
	if (player1.getPoints() == 5)
	{
		renderText("Congratulations, Player1, you've won the game!", 30, 458);
		renderText("Start new game? (press any key)", 30, 508);

		Game::gameOverFlag = true;
	}

	if (player2.getPoints() == 5)
	{
		renderText("Congratulations, Player2, you've won the game!", 30, 458);
		renderText("Start new game? (press any key)", 30, 508);

		Game::gameOverFlag = true;
	}
	
	SDL_RenderPresent(renderer);

	SDL_Surface* surface = NULL;
}

void Game::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			//const int pace = 20;
			SDL_Point position1 = player1.getPosition();
			if (event.key.keysym.sym == SDLK_UP)
			{
				if (position1.y == 518)
				{
					position1.y = position1.y - 18;
				}
				else if (position1.y > 0)
				{
					position1.y = position1.y - 20;
				}				
				//std::cout << "up arrow key pressed\n";				
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if (position1.y < 500)
				{
					position1.y = position1.y + 20;
				}
				else if (position1.y == 500)
				{
					position1.y = position1.y + 18;
				}
				//std::cout << "down arrow key pressed\n";
			}
			player1.setPosition(position1);
			std::cout << player1.getPosition().y << std::endl;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << "mouse is moving\n";
			
			SDL_Point position2 = player2.getPosition();
			int msx, msy;
			SDL_GetMouseState(&msx, &msy);
			
			//std::cout << msx << ':' << msy << "\n";
			if (msy >= 0 && msy <= 518 && position2.y != msy)
			{
				position2.y = msy;
			}
			player2.setPosition(position2);
			std::cout << msy << "\n";
			break;
		default:
			break;
		}
	}
}

void Game::paddleImpactCheck()
{
	SDL_Point ballPosition = ball.getPosition();
	SDL_Point currentPace = ball.getPace();
	SDL_Point paddle1Position = player1.getPosition();
	SDL_Point paddle2Position = player2.getPosition();

	if (ballPosition.x <= (paddle1Position.x + 10) && ballPosition.y >= (paddle1Position.y - 27) && ballPosition.y <= (paddle1Position.y + 90))
	{
		currentPace.x *= -1;
		ball.setPace(currentPace);
	}

	if (ballPosition.x >= (paddle2Position.x - 26) && ballPosition.y >= (paddle2Position.y - 27) && ballPosition.y <= (paddle2Position.y + 90))
	{
		currentPace.x *= -1;
		ball.setPace(currentPace);
	}
}

void Game::pointScoredCheck()
{
	SDL_Point ballPosition = ball.getPosition();
	SDL_Point currentPace = ball.getPace();
	SDL_Point paddle1Position = player1.getPosition();
	SDL_Point paddle2Position = player2.getPosition();

	if (ballPosition.x <= 0)
	{		
			player2.setPoints(player2.getPoints() + 1);

			SDL_Point ballInitialPosition;
			ballInitialPosition.x = 535;
			ballInitialPosition.y = 491;
			ball.setPosition(ballInitialPosition);
			SDL_Point ballInitialDirection = ball.setInitialDirection();
			ball.setPace(ballInitialDirection);
			SDL_Delay(500);
	}

	if (ballPosition.x >= 1070)
	{
		player1.setPoints(player1.getPoints() + 1);

		SDL_Point ballInitialPosition;
		ballInitialPosition.x = 535;
		ballInitialPosition.y = 491;
		ball.setPosition(ballInitialPosition);
		SDL_Point ballInitialDirection = ball.setInitialDirection();
		ball.setPace(ballInitialDirection);
		SDL_Delay(500);
	}
}

void Game::winnerCheck()
{
	if (Game::gameOverFlag)
	{
		SDL_Event event2;
		if (SDL_WaitEvent(&event2)) 
		{
			switch (event2.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				player1.setPoints(0);
				player2.setPoints(0);
				ball.Move();
				break;
			default:
				break;
			}
		}
		
	}
}

void Game::update() {
	ball.Move();
	
	this->paddleImpactCheck();
	this->pointScoredCheck();
	this->winnerCheck();
}

void Game::clean() {
	std::cout << "cleaning game\n";

	TTF_CloseFont(font1);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::isRunning() {
	return Game::running;
}

Game::~Game() {};