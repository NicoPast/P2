#include "Tuner.h"

Tuner::Tuner(LoremIpsum* game) : State(game)
{
	stress_ = 0;
	maxStress_ = 90;
	//delay = 3000;

	setBars(); //Pilla el array de entidades de las barras
	createStressMeter();

	//la velocidad de subida del estrés será una media de todas las velocidades de bajada de las barras
	double auxStress = 0;
	for (int i = 0; i < bars_.size(); i++) {
		Bar* bar = GETCMP2(bars_[i], Bar);
		auxStress += bar->getDownSpeed();
	}
	stressSpeed_ = auxStress / bars_.size() * 0.1;
}

void Tuner::update()
{
	State::update();
	InputHandler* ih = InputHandler::instance();
	int time = game_->getGame()->getTime();
	bool won = true;
	for (int i = 0; i < bars_.size(); i++) {
		Bar* bar = GETCMP2(bars_[i], Bar);
		if(ih->isKeyDown(SDLK_SPACE))
			bar->grow();
		if (!(bar->isInWinningZone()))
			won = false;
	}

	if (won) {
		cout << "gane " << ++test << " veces al fantasma" << endl;
	}
	else {
		stress_ += stressSpeed_;
		angle_ = stress_ * 3.6;
		stresTr_->setPos({ stressCenter_.getX() + (cos(angle_) * radius_), stressCenter_.getY() + (sin(angle_) * radius_) });
		stresTr_->setRot(angle_);
	}
}

void Tuner::render()
{
	State::render();
}

void Tuner::setBars() {
	bars_ = game_->getStoryManager()->createBars(entityManager_);
	
	int contY = game_->getGame()->getWindowHeight() / 5;
	int pxPercent = (contY * 3) / 100;
	double minWinPerc = 85;
	double maxWinPerc = 95;

	for (int i = 0; i < bars_.size(); i++) {
		Entity* cont = entityManager_->addEntity(2);
		Transform* barT = GETCMP2(bars_[i], Transform);
		Transform* contT = cont->addComponent<Transform>(barT->getPos().getX(), contY, barT->getW(), contY * 3);
		cont->addComponent<Rectangle>(SDL_Color{ COLOR(0xff000000) });

		Entity* wzone = entityManager_->addEntity(2);
		wzone->addComponent<Transform>(barT->getPos().getX(), contY + (100 - maxWinPerc) * pxPercent, barT->getW(), (maxWinPerc - minWinPerc) * pxPercent);
		Transform* wtr = GETCMP2(wzone, Transform);
		wzone->addComponent<Rectangle>(SDL_Color{ COLOR(0x32CD3200) });

		Bar* b = GETCMP2(bars_[i], Bar);
		b->setWinningZone(wtr);
		b->setLockActive(true);
		b->setGrowthTop(contT->getH());
		b->setWinningRange(minWinPerc, maxWinPerc);
		bars_[i]->setActive(true);
	}
}

void Tuner::createStressMeter() {
	stressCenter_ = { game_->getGame()->getWindowWidth() * 3 / 4.0, game_->getGame()->getWindowHeight() / 2.0 };
	radius_ = game_->getGame()->getWindowWidth() / 4.0 - 2 * 30;

	Entity* stresser = entityManager_->addEntity(3);
	stresTr_ = stresser->addComponent<Transform>(stressCenter_.getX() + (cos(angle_) * radius_), stressCenter_.getY() + (sin(angle_) * radius_), 30, 30);
	stresser->addComponent<Rectangle>(SDL_Color{ COLOR(0x32CD3200) });
	stresTr_->setRot(angle_);

	Entity* stressLimit = entityManager_->addEntity(3);
	Transform* strLimTr = stressLimit->addComponent<Transform>(stressCenter_.getX() + (cos(maxStress_ * 3.6) * radius_), stressCenter_.getY() + (sin(maxStress_ * 3.6) * radius_), 30, 30);
	stressLimit->addComponent<Rectangle>(SDL_Color{ COLOR(0xff000000) });
	strLimTr->setRot(maxStress_ * 3.6);
}
