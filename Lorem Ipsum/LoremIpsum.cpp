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
	game_ = SDLGame::init("Mortis Causa", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	game_->setLoremIpsum(this);
	SDL_ShowCursor(SDL_ENABLE);
	states_ = new StateMachine(this);
	story_ = StoryManager::Singleton::init(this, states_->playState_->getEntityManager());

	//Lee
	//Fullscreen
	//musicVolume
	//fxVolume
	ifstream config (configFile);
	bool fullscreen = false;
	int musicVolume = 15;
	int fxVolume = 10;
	if (config.is_open()) {
		try {
			config >> fullscreen;
			config >> musicVolume;
			config >> fxVolume;

			cout << "fullscreen: " << fullscreen << "\nmusicVolume: " << musicVolume << "\nfxVolume: " << fxVolume << endl;
		}
		catch(...){
			fullscreen = false;
			musicVolume = 13;
			fxVolume = 7;
			cout << "Error reading config file" << endl;
		}

		//128 maxVolume
		if (musicVolume > SDL_MIX_MAXVOLUME) {
			musicVolume = SDL_MIX_MAXVOLUME;
		}
		else if (musicVolume < 0) {
			musicVolume = 0;
		}

		if (fxVolume > SDL_MIX_MAXVOLUME) {
			fxVolume = SDL_MIX_MAXVOLUME;
		}
		else if (fxVolume < 0) {
			fxVolume = 0;
		}

		if (fullscreen) {
			game_->toggleFullScreen();
		}
	}
	else {
		cout << "Error opening config file" << endl;
	}

	config.close();

	game_->getAudioMngr()->setMusicVolume(musicVolume);
	game_->getAudioMngr()->setChannelVolume(fxVolume);

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

		if (ih->isKeyDown(SDLK_ESCAPE) && !ih->isLocked()) {
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
