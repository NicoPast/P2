#include "Tuner.h"

Tuner::Tuner(LoremIpsum* game, int n) : State(game)
{
	nBars = n;
	heat = 0;
	maxHeath = 90;
}

void Tuner::update()
{
	State::update();
}

void Tuner::render()
{
	State::render();
}
