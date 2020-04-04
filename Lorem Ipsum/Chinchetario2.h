#pragma once
#include "State.h"
#include "StoryManager.h"

class Chinchetario2 : public State
{
public:
	Chinchetario2(LoremIpsum* game);
	virtual ~Chinchetario2() {};

	virtual void update() override;
	virtual void render() override;

	bool compareDragLayerIndex(int index, int layer);
	void resetDragLayerIndex() { dragLayerIndex = -1; }
	void clueDropped(Entity* e);
	void relocateClues();

protected:
	bool checkClueInBottomPanel(Entity* e);
	SDL_Rect camera_;
	vector<Entity*> clueEntities_;
	Entity* bottomPanel_;
	Entity* rightPanel_;
	int dragIndex_;
	int dragLayerIndex = -1;									//Objeto arrastrandose segun su capa


};