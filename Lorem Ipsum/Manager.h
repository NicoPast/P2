#pragma once
#include "SDLGame.h"
#include <list>
class State;
class Entity;
const int layers = 5;
class EntityManager {
public:
	EntityManager(SDLGame* game, State* state);
	virtual ~EntityManager();

	void update();
	void draw();
	Entity* addEntity(int layer);
	void setLastInLayer(Entity* e, int layer);
	int getLayerSize(int layer) { return drawLayers[layer].size(); }
	std::vector<std::shared_ptr<Entity>> getLayer(int layer) { return drawLayers[layer]; }

protected:
	SDLGame* game_;
	State* state_;
	void adjustIndex(int layer);
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Entity>> drawLayers[layers];		//Capas de dibujado
};
