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
	entities.emplace_back(e);
	drawLayers[layer].emplace_back(e);
	int x = drawLayers[layer].size() - 1;
	e->setLayerIndex(x);
	return e;
}
void EntityManager::setLastInLayer(Entity* e, int layer) {
	int i = e->getLayerIndex();
	if (i != drawLayers[layers].size() - 1) {
	drawLayers[layer].push_back(drawLayers[layer].at(i));
	drawLayers[layer].erase(drawLayers[layer].begin() + i);
	adjustIndex(layer);
	}
}
//Ajusta el descompensado de los índices internos de los entities
void EntityManager::adjustIndex(int layer) {
	int x = drawLayers[layer].size() - 1;
	for (int i = 0; i < x; i++)
		drawLayers[layer][i].get()->setLayerIndex(i);
}