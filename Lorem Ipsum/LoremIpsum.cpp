#include "LoremIpsum.h"

LoremIpsum::LoremIpsum() :
	game_(nullptr), 
	exit_(false)
{
	initGame(); 
}
void LoremIpsum::changeScene(Resources::SceneID id)
{
	if (states_->actualState() == states_->playState_)
	{
		story_->changeScene(id);
		Camera* cam = getStateMachine()->actualState()->getCamera();

		cam->setPos(0, 0);
		cam->setWidth(_WINDOW_WIDTH_);
		cam->setHeight(_WINDOW_HEIGHT_);
		cam->setLeftMargin(50); cam->setRightMargin(50);
		
		Texture* bckgrndTexture  = story_->getCurrentScene()->background;
		cam->setLimitX(bckgrndTexture->getWidth());
		cam->setLimitY(bckgrndTexture->getHeight());


	}
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
	game_->setLoremIpsum(this);
	SDL_ShowCursor(SDL_ENABLE);
	states_ = new StateMachine(this);
	story_ = new StoryManager(this, states_->playState_->getEntityManager());
	states_->PlayMenu();

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
			//game_->toggleFullScreen();
		}
	}
	
}

void LoremIpsum::update()
{
	states_->actualState()->update();
	game_->getCamera()->update();
}

void LoremIpsum::render()
{
	SDL_SetRenderDrawColor(game_->getRenderer(), 0, 0, 0, 1);
	SDL_RenderClear(game_->getRenderer());

	states_->actualState()->render();

	SDL_RenderPresent(game_->getRenderer());
}
