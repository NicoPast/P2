#include "Tuner.h"

Tuner::Tuner(LoremIpsum* game) : State(game)
{
	if (StoryManager::instance()->getTunerDificultyLevel() == 0)
		showPopUpMessage("Para entender a los fantasmas, manten pulsado ESPACIO para llevar las barras a la zona verde y sintonizarte con ellos. Regula las barras bloqueando su subida haciendo click en los candados. No dejes que se estresen o no podres entenderlos! Puedes calmarlos haciendo click en el boton de reseteo. ");

	SDLGame::instance()->getAudioMngr()->setChannelVolume(0,4);
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Minigame_W, -1, 4);
	Entity* bg = entityManager_->addEntity(0);
	bg->addComponent<Transform>(0,0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
	bg->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::TextureID::TunerBG));
	stress_ = 0;
	maxStress_ = 100;
	//delay = 3000;

	setBars(); //Pilla el array de entidades de las barras
	createStressMeter(); //crea los visualizadores del estres


	stressSpeed_ = 0.07;
}

void Tuner::update()
{

	InputHandler* ih = InputHandler::instance();
	
	int time = game_->getGame()->getTime();
	
	bool won = true;
	
	int notGrowingBars = bars_.size();
	for (int i = 0; i < bars_.size(); i++) {
		Bar* bar = GETCMP2(bars_[i], Bar);
		if (!(bar->isInWinningZone()))
			won = false;
		if (direction_ > 0 && ih->isKeyDown(SDLK_SPACE))
			bar->grow();
		else {
			bar->setGrowing(false);
			notGrowingBars--;
		}
	}
	if(notGrowingBars == 0) SDLGame::instance()->getAudioMngr()->setChannelVolume(0,4);
#ifdef _DEBUG
	if (ih->isKeyDown(SDLK_RETURN))
		won = true;
#endif // _DEBUG
	if (won) {
		Actor* g = StoryManager::instance()->getActor(ghost_);
		g->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->interact();
		g->setTuend(true);
		StoryManager::instance()->setTunerDificultyLevel(StoryManager::instance()->getTunerDificultyLevel() + 1);
		game_->getStateMachine()->destroyActual();
		SDLGame::instance()->getAudioMngr()->pauseChannel(4);
		SDLGame::instance()->getAudioMngr()->pauseChannel(3);
		return;
	}
	else {
		stress_ += stressSpeed_ * direction_;
		if (direction_ <0 && stress_ <= 0) {
			stress_ = 0;
			direction_ = 1;
			Texture* temp = game_->getGame()->getTextureMngr()->getTexture(Resources::ResetStress);
			stresCalm_->setSourceRect({ 0, 0, temp->getWidth() / 2, temp->getHeight() });
		}
		else if (stress_ > maxStress_) {
			game_->getStateMachine()->destroyActual();
			SDLGame::instance()->getAudioMngr()->pauseChannel(4);
			SDLGame::instance()->getAudioMngr()->pauseChannel(3);
			return;
		}
		angle_ = stress_ * 3.6;
		stresTr_->setRot(angle_);
	}
	State::update();
}

void Tuner::render()
{
	State::render();
}

void Tuner::setBars() {
	bars_ = game_->getStoryManager()->createBars(entityManager_);

	int pxSprite = 56;
	int pxPerY = (game_->getGame()->getWindowHeight() / 5) * 3 / pxSprite;
	
	int contY = game_->getGame()->getWindowHeight() / 5;
  	int pxPercent = (contY * 3) / 100;

	for (int i = 0; i < bars_.size(); i++) {
		Bar* b = GETCMP2(bars_[i], Bar);

		Entity* cont = entityManager_->addEntity(2);
		Transform* barT = GETCMP2(bars_[i], Transform);
		Transform* contT = cont->addComponent<Transform>(barT->getPos().getX(), contY, barT->getW(), contY * 3);
		Texture* temp = game_->getGame()->getTextureMngr()->getTexture(Resources::Bars);
		cont->addComponent<Sprite>(temp)->setSourceRect({ 0, 0, temp->getWidth() / 2, temp->getHeight() });
		
		
		Entity* contBorder = entityManager_->addEntity(3);
		contBorder->addComponent<Transform>(barT->getPos().getX(), contY, barT->getW(), contY * 3);
		contBorder->addComponent<Sprite>(temp)->setSourceRect({ temp->getWidth() / 2, 0, temp->getWidth() / 2, temp->getHeight() });

		Entity* wzone = entityManager_->addEntity(2);
		tuple<double, double> wRange = b->getWinRange();
		wzone->addComponent<Transform>(barT->getPos().getX(), contY + (100.0 - get<1>(wRange)) * pxPercent + pxPerY * 2.0 + 1, barT->getW(), (get<1>(wRange) - get<0>(wRange)) * pxPercent);
		Transform* wtr = GETCMP2(wzone, Transform);
		wzone->addComponent<Rectangle>(SDL_Color{ COLOR(0x649d66FF) });
		
		b->setGrowthTop((int)contT->getH() - (int)(pxPerY * 4.0 - 2));
		bars_[i]->setActive(true);
	}
}

void Tuner::changeStressDir(double dir)
{
	direction_ = (int)dir;
	Texture* temp = game_->getGame()->getTextureMngr()->getTexture(Resources::ResetStress);
	stresCalm_->setSourceRect({ temp->getWidth() / 2, 0, temp->getWidth() / 2, temp->getHeight() });
}


void Tuner::createStressMeter() {
	stressCenter_ = { game_->getGame()->getWindowWidth() * 7.0 / 8.0 - 60, game_->getGame()->getWindowHeight() / 2.0 - 60 };
	// 30 es el ancho del cuadrado que gira
	radius_ = game_->getGame()->getWindowWidth() / 6.0 - (2.0 * 30);

	Texture* temp = game_->getGame()->getTextureMngr()->getTexture(Resources::Manometer);

	Entity* stressMeter = entityManager_->addEntity(1);
	Transform* sMTr = stressMeter->addComponent<Transform>(stressCenter_.getX() - radius_, stressCenter_.getY() - radius_, 2*radius_, 2*radius_);
	stressMeter->addComponent<Sprite>(temp)->setSourceRect({ temp->getWidth() / 2, 0, temp->getWidth() / 2, temp->getHeight() });

	Entity* stressMeterBorder = entityManager_->addEntity(3);
	stressMeterBorder->addComponent<Transform>(stressCenter_.getX() - radius_, stressCenter_.getY() - radius_, 2 * radius_, 2 * radius_);
	stressMeterBorder->addComponent<Sprite>(temp)->setSourceRect({ 0, 0, temp->getWidth() / 2, temp->getHeight() });

	int pxPerX = (int)20/3;
	int pxPerY = radius_ / 14;

	temp = game_->getGame()->getTextureMngr()->getTexture(Resources::ManometerNeedle);
	temp->setPivotPoint({ temp->getWidth() / 2 - pxPerX, temp->getHeight() - 3*pxPerY });

	Entity* stressMeterNeedle = entityManager_->addEntity(2);
	stresTr_ = stressMeterNeedle->addComponent<Transform>(stressCenter_.getX() - 11, stressCenter_.getY() - radius_ + 10, 20, radius_);
	Sprite* needle  = stressMeterNeedle->addComponent<Sprite>(temp);

	temp = game_->getGame()->getTextureMngr()->getTexture(Resources::ResetStress);

	Entity* calmStress = entityManager_->addEntity(3);
	Transform* calmStrTr = calmStress->addComponent<Transform>(stressCenter_.getX() - 40, stressCenter_.getY() + radius_ + 20, 80, 80);
	stresCalm_ = calmStress->addComponent<Sprite>(temp);
	stresCalm_->setSourceRect({ 0, 0, temp->getWidth() / 2, temp->getHeight() });
	calmStress->addComponent<ButtonOneParametter<Tuner*>>(std::function<void(Tuner*)>([](Tuner* t) { t->changeStressDir(-2.5); }), this);
}
