#pragma once
#include "Manager.h"

class LoremIpsum;

class State
{
protected:
	LoremIpsum* game_;
	EntityManager* entityManager_;

public:
	State(LoremIpsum* game);
	virtual ~State() { delete entityManager_; };
	EntityManager* getEntityManager() { return entityManager_; };
	virtual void update();
	void render(); 
};

