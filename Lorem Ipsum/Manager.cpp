#include "Manager.h"
#include "Entity.h"

EntityManager::EntityManager(SDLGame *game, State* state) :
		game_(game),state_(state) {
}

EntityManager::~EntityManager() {
}

void EntityManager::update() {
	for (auto& e : entities) {
		if(e->getActive())
			e->update();
	}
	for (auto& e : entityQueue) {
		entities.push_back(e);
	}
	entityQueue.clear();
}

void EntityManager::draw() {
	for (auto &l : drawLayers) {
		for (auto& e : l) {
			if(e->getActive())
				//if ((e->isUI()) || (e->getComponent<Transform>(ecs::Transform) && state_->getCamera()->isObjectInCamera(e->getComponent<Transform>(ecs::Transform))))
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
Entity* EntityManager::addEntityInQueue(int layer) {
	Entity* e = new Entity(game_, state_);
	//Ajustado para capas
	std::shared_ptr<Entity> shPtr(e);
	entityQueue.push_back(shPtr);
	drawLayers[layer].push_back(shPtr);
	int x = drawLayers[layer].size() - 1;
	e->setLayerIndex(x);
	e->setLayer(layer);
	return e;
}
void EntityManager::setLastInLayer(Entity* e) {
	int i = e->getLayerIndex();
	int layer = e->getLayer();
	int x = drawLayers[layer].size() - 1;
	if (i != x) {
	drawLayers[layer].push_back(drawLayers[layer].at(i));
	drawLayers[layer].erase(drawLayers[layer].begin() + i);
	adjustIndex(layer);
	}
}
void EntityManager::setLayer(Entity* e, int layer) {
	int i = e->getLayerIndex();
	int l = e->getLayer();
	drawLayers[layer].push_back(drawLayers[l].at(i));
	drawLayers[l].erase(drawLayers[l].begin() + i);
	adjustIndex(layer);
	adjustIndex(l);
}
//Ajusta el descompensado de los índices internos de los entities
void EntityManager::adjustIndex(int layer) {
	int x = drawLayers[layer].size();
	for (int i = 0; i < x; i++)
		drawLayers[layer][i].get()->setLayerIndex(i);
}