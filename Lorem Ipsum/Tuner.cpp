#include "Tuner.h"

Tuner::Tuner(LoremIpsum* game) : State(game)
{
	stress_ = 0;
	maxStress_ = 90;
	win_ = false;
	delay = 3000;
	setBars(); //Pilla el array de entidades de las barras
	//la velocidad de subida del estrés será una media de todas las velocidades de bajada de las barras
	double auxStress = 0;
	for (int i = 0; i < bars_.size(); i++) {
		Bar* bar = GETCMP2(bars_[i], Bar);
		auxStress += bar->getDownSpeed();
	}
	stressSpeed_ = auxStress / bars_.size();

}

void Tuner::update()
{
	State::update();
	InputHandler* ih = InputHandler::instance();
	if (ih->isKeyDown(SDLK_SPACE)) {
		game_->getGame()->getTime();
		for (int i = 0; i < bars_.size(); i++) {
			Bar* bar = GETCMP2(bars_[i], Bar);
			bar->grow();
		}
	}
}

void Tuner::render()
{
	State::render();
}

void Tuner::setBars() {
	bars_ = game_->getStoryManager()->createBars(entityManager_);
	int contY = game_->getGame()->getWindowHeight() / 5;
	int wzoneH = 30;

	for (int i = 0; i < bars_.size(); i++) {
		Entity* cont = entityManager_->addEntity(2);
		Transform* barT = GETCMP2(bars_[i], Transform);
		Transform* contT = cont->addComponent<Transform>(barT->getPos().getX(), contY, barT->getW(), contY *3);
		cont->addComponent<Rectangle>(SDL_Color{ COLOR(0xff000000) });
		

		Entity* wzone = entityManager_->addEntity(2);
		wzone->addComponent<Transform>(barT->getPos().getX(), contY + wzoneH, barT->getW(), wzoneH);
		Transform* wtr = GETCMP2(wzone, Transform);
		wzone->addComponent<Rectangle>(SDL_Color{ COLOR(0x32CD3200) });

		Bar* b = GETCMP2(bars_[i], Bar);
		b->setWinningZone(wtr);
		b->setLockActive(true);
		b->setGrowthTop(contT->getH());
		bars_[i]->setActive(true);
	}
}
