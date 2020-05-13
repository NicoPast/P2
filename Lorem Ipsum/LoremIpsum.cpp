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
		cam->setLeftMargin(150); cam->setRightMargin(150);
		
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
	game_ = SDLGame::init("Lorem Ipsum", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	game_->setLoremIpsum(this);
	SDL_ShowCursor(SDL_ENABLE);
	states_ = new StateMachine(this);
	story_ = StoryManager::Singleton::init(this, states_->playState_->getEntityManager());
	states_->PlayMenu();

}

void LoremIpsum::handleInput()
{
	InputHandler* ih = InputHandler::instance();

	ih->update();

	
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_F4) && ih->isKeyDown(SDLK_LALT))
		{
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_ESCAPE)) {
			if (states_->states_.size() > 1)(states_->actualState() != states_->playState_) ? states_->PlayGame() : states_->PlayMenu();
			else exit_ = true;
			//game_->toggleFullScreen();
		}
	}
	
}

void LoremIpsum::update()
{
	states_->actualState()->update();
	game_->getCamera()->update();
#ifdef _DEBUG
	if (InputHandler::instance()->keyDownEvent() && InputHandler::instance()->isKeyDown(SDLK_F3))
	{
		StoryManager::instance()->showingHitbox_ = !StoryManager::instance()->showingHitbox_;
	}
	if (InputHandler::instance()->keyDownEvent() && InputHandler::instance()->isKeyDown(SDLK_F4))
	{
		StoryManager::instance()->chopMovement_ = !StoryManager::instance()->chopMovement_;
	}
#endif // _DEBUG

}

void LoremIpsum::render()
{
	SDL_SetRenderDrawColor(game_->getRenderer(), 0, 0, 0, 1);
	SDL_RenderClear(game_->getRenderer());

	states_->actualState()->render();

	SDL_RenderPresent(game_->getRenderer());
}
