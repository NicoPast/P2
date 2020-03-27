#include "Entity.h"
#include "State.h"

Entity::Entity(SDLGame *game, State* state) :
		game_(game), //
		state_(state),
		mngr_(nullptr)
{
	mngr_ = state->getEntityManager();
}

Entity::~Entity() {
}

