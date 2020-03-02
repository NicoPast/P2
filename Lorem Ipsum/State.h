#pragma once
#include "Manager.h"


class LoremIpsum;
class State
{
private:
	LoremIpsum* game_;
	EntityManager* entityManager_;

public:
	State(LoremIpsum* game);

	EntityManager* getEntityManager() { return entityManager_; };
	void update();
	void render(); 
};

