#include "Manager.h"
#include "Entity.h"

EntityManager::EntityManager(SDLGame *game, State* state) :
		game_(game),state_(state) {
}

EntityManager::~EntityManager() {
}

void EntityManager::update() {
	for (auto &e : entities) {
		e->update();
	}
}

void EntityManager::draw() {
	for (auto &e : entities) {
		e->draw();
	}
}

Entity* EntityManager::addEntity() {
	Entity* e = new Entity(game_,state_);
	std::unique_ptr<Entity> uPtr( e );
	entities.emplace_back(std::move(uPtr));
	return e;
}
