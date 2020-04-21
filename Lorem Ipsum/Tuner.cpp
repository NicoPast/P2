#include "Tuner.h"

Tuner::Tuner(LoremIpsum* game) : State(game)
{
	stress_ = 0;
	maxStress_ = 90;
	win_ = false;
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
		Transform* contT = GETCMP2(bars_[i], Transform);
		cont->addComponent<Transform>(contT->getPos().getX(), contY, contT->getW(), contY *3);
		cont->addComponent<Rectangle>(SDL_Color{ COLOR(0xff000000) });
		

		Entity* wzone = entityManager_->addEntity(2);
		wzone->addComponent<Transform>(contT->getPos().getX(), contY + wzoneH, contT->getW(), wzoneH);
		Transform* wtr = GETCMP2(wzone, Transform);
		wzone->addComponent<Rectangle>(SDL_Color{ COLOR(0x32CD3200) });

		GETCMP2(bars_[i], Bar)->setWinningZone(wtr);

		bars_[i]->setActive(true);
		GETCMP2(bars_[i], Bar)->setLockActive(true);
	}
	//el storyManager debe crear:
		//una entidad para la barra que se mueve
		//una entidad para la winning zone
		//un entidad para el container de la barra

	//bars = game_->getStoryManager()->getBars     hacer un metodo en storyManager que lea las barras según el minijuego que sea.
}
