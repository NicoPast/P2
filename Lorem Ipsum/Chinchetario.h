#pragma once

#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "ScrollerLimited.h"

//10000000 puntos de caradura. Esto es provisional y se leera de json me lo prometio ricardo
class CentralClue 
{
public:
	CentralClue(Resources::ClueIDs id, vector<Resources::ClueIDs> l) : id_(id), links_(l) {};
	~CentralClue() {};
	Resources::ClueIDs id_;
	vector<Resources::ClueIDs> links_;

};


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
	int dragIndex_;
	int dragLayerIndex = -1;									//Objeto arrastrandose segun su capa

	void showBottomPanel() { bottomPanel_->setActive(true); setUnplacedClues(true); };
	void hideBottomPanel() { bottomPanel_->setActive(false); setUnplacedClues(false);};
	void showRightPanel() { rightPanel_->setActive(true); };
	void hideRightPanel()  { rightPanel_->setActive(false); };
	void setUnplacedClues(bool b);
};