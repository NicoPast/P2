#pragma once
#include "Manager.h"

class LoremIpsum;

class State
{
protected:
	LoremIpsum* game_;
	EntityManager* entityManager_;

	bool active_ = true;

public:
	State(LoremIpsum* game);
	virtual ~State() { delete entityManager_; };
	EntityManager* getEntityManager() { return entityManager_; };
	virtual void update();
	virtual void render();

	bool isActive() { return active_; }
	void deactivate() { active_ = false; }
	void destroy();
};

