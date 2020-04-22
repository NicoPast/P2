#include "State.h"
#include "LoremIpsum.h"
State::State(LoremIpsum* game)
{
	game_ = game;
	entityManager_ = new EntityManager(game_->getGame(), this);
	camera_ = new Camera();
}
void State::update()
{
	if (active_)
		entityManager_->update();
	else destroy();
}

void State::render()
{

	entityManager_->draw();
}

void State::destroy() 
{
	game_->getStateMachine()->destroyActual();
}
