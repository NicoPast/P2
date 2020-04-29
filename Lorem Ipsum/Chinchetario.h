#pragma once

#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "ScrollerLimited.h"
#include "Pin.h"
#include "Drag.h"

class Chinchetario : public State
{
public:
	Chinchetario(LoremIpsum* game);
	virtual ~Chinchetario() {};

	virtual void update() override;
	virtual void render() override;

	bool isHigherDragable(Drag* d);
	void resetDraggedItem() { draggedItem_ = nullptr; }
	void clueDropped(Entity* e);
	void pinDropped(Entity* e);
	void relocateClues();

	void toggleBottomPanel() { bottomPanel_->getActive() ? hideBottomPanel() : showBottomPanel(); };
	void close();

protected:
	bool checkClueInBottomPanel(Entity* e);
	void showBottomPanel() { bottomPanel_->setActive(true); setUnplacedClues(true); };
	void hideBottomPanel() { bottomPanel_->setActive(false); setUnplacedClues(false);};
	void showRightPanel() { rightPanel_->setActive(true); };
	void hideRightPanel()  { rightPanel_->setActive(false); };
	void setUnplacedClues(bool b);
	void createPanels(int& bottomPanelH, Text*& textTitle, Text*& textDescription);
	void createClues(int bottomPanelH, Text* textTitle_, Text* textDescription);
	void changeText(Text* title, Text* description, string newT, string newD);

	vector<Entity*> clueEntities_;
	Entity* bottomPanel_;
	Entity* rightPanel_;
	Entity* mng_;
	ScrollerLimited* scroll_;
	Entity* cursor_;												//De momento solo sirve para mover la c�mara
	Entity* background_;
	vector<Clue*> playerClues_;
	Drag* draggedItem_ = nullptr;							//Objeto arrastrandose

};