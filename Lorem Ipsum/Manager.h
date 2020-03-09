#pragma once
#include "SDLGame.h"

class State;
class Entity;

class EntityManager {
public:
	EntityManager(SDLGame* game, State* state);
	virtual ~EntityManager();

	void update();
	void draw();
	Entity* addEntity();


protected:
	SDLGame* game_;
	State* state_;
	std::vector<std::unique_ptr<Entity>> entities;
};
