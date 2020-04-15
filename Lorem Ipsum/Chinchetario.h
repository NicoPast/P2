#pragma once

#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "ScrollerLimited.h"
#include "Pin.h"

class Chinchetario : public State
{
public:
	Chinchetario(LoremIpsum* game);
	virtual ~Chinchetario() {};

	virtual void update() override;
	virtual void render() override;

	bool compareDragLayerIndex(int index, int layer);
	void resetDragLayerIndex() { dragLayerIndex = -1; }
	void clueDropped(Entity* e);
	void relocateClues();

	void toggleBottomPanel() { bottomPanel_->getActive() ? hideBottomPanel() : showBottomPanel(); };


protected:
	bool checkClueInBottomPanel(Entity* e);
	SDL_Rect camera_;
	vector<Entity*> clueEntities_;
	Entity* bottomPanel_;
	Entity* rightPanel_;
	Entity* mng_;
	ScrollerLimited* scroll_;
	vector<Clue*> playerClues_;
	int dragIndex_;
	int dragLayerIndex = -1;									//Objeto arrastrandose segun su capa

	void showBottomPanel() { bottomPanel_->setActive(true); setUnplacedClues(true); };
	void hideBottomPanel() { bottomPanel_->setActive(false); setUnplacedClues(false);};
	void showRightPanel() { rightPanel_->setActive(true); };
	void hideRightPanel()  { rightPanel_->setActive(false); };
	void setUnplacedClues(bool b);
};