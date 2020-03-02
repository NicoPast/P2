#include "State.h"
#include "LoremIpsum.h"
State::State(LoremIpsum* game)
{
	game_ = game;
	entityManager_ = new EntityManager(game->getGame(), this);
}

void State::update()
{
	entityManager_->update();
}

void State::render()
{
	entityManager_->draw();
}
