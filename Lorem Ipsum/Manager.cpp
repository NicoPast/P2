#include "Manager.h"
#include "Entity.h"

EntityManager::EntityManager(SDLGame *game, State* state) :
		game_(game),state_(state) {
}

EntityManager::~EntityManager() {
}

void EntityManager::update() {
	for (auto& e : entities) {
		e->update();
	}
}

void EntityManager::draw() {
	for (auto &l : drawLayers) {
		for (auto& e : l) {
			e->draw();
		}
	}
}
Entity* EntityManager::addEntity(int layer) {
	Entity* e = new Entity(game_,state_);
	//Ajustado para capas
	std::shared_ptr<Entity> shPtr(e);
	entities.push_back(shPtr);
	drawLayers[layer].push_back(shPtr);
	int x = drawLayers[layer].size() - 1;
	e->setLayerIndex(x);
	e->setLayer(layer);
	return e;
}
void EntityManager::setLastInLayer(Entity* e, int layer) {
	int i = e->getLayerIndex();
	int x = drawLayers[layer].size() - 1;
	if (i != x) {
	drawLayers[layer].push_back(drawLayers[layer].at(i));
	drawLayers[layer].erase(drawLayers[layer].begin() + i);
	adjustIndex(layer);
	}
}
//Ajusta el descompensado de los índices internos de los entities
void EntityManager::adjustIndex(int layer) {
	int x = drawLayers[layer].size();
	for (int i = 0; i < x; i++)
		drawLayers[layer][i].get()->setLayerIndex(i);
}