#pragma once
#include "SDLGame.h"
#include <list>
#include "checkML.h"

class State;
class Entity;
const int layers = 5;
enum Layers{BackgroundLayer, CharacterLayer, TestLayer, DragDropLayer, LastLayer};
class EntityManager {
public:
	EntityManager(SDLGame* game, State* state);
	virtual ~EntityManager();

	void update();
	void draw();
	Entity* addEntity(int layer = 0);
	void setLastInLayer(Entity* e, int layer);
	size_t getLayerSize(int layer) { return drawLayers[layer].size(); }
	std::vector<std::shared_ptr<Entity>> getLayer(int layer) { return drawLayers[layer]; }
	Entity* getEntity(int layer, int index) { return drawLayers[layer][index].get(); }

protected:
	SDLGame* game_;
	State* state_;
	void adjustIndex(int layer);
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Entity>> drawLayers[layers];		//Capas de dibujado
};
