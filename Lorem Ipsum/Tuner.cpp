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
	//el storyManager debe crear:
		//una entidad para la barra que se mueve
		//una entidad para la winning zone
		//un entidad para el container de la barra

	//bars = game_->getStoryManager()->getBars     hacer un metodo en storyManager que lea las barras según el minijuego que sea.
}
