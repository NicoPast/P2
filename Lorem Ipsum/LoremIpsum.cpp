#include "LoremIpsum.h"

LoremIpsum::LoremIpsum() :
	game_(nullptr), 
	exit_(false)
{
	initGame(); 
}

void LoremIpsum::start()
{
	exit_ = false;
	while (!exit_)
	{
		Uint32 startTime = game_->getTime();
		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	
	}
}

void LoremIpsum::initGame()
{
	game_ = SDLGame::init("YEAH, BOI", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	states_ = new StateMachine(this);
	//states_->PlayGame();
	states_->PlayApp(StateMachine::APPS::Chinchetario);

}

void LoremIpsum::handleInput()
{
	InputHandler* ih = InputHandler::instance();

	ih->update();

	
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else {
				SDL_SetWindowFullscreen(game_->getWindow(),
					SDL_WINDOW_FULLSCREEN);
			}
		}
	}
	
}

void LoremIpsum::update()
{
	states_->actualState()->update();
}

void LoremIpsum::render()
{
	SDL_SetRenderDrawColor(game_->getRenderer(), 0, 0, 0, 1);
	SDL_RenderClear(game_->getRenderer());

	states_->actualState()->render();

	SDL_RenderPresent(game_->getRenderer());
}
