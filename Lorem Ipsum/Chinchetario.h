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

	void toggleBottomPanel();
	void showText() { textDescription_->setEnabled(1); textTitle_->setEnabled(1); }

	void close();

protected:
	bool checkClueInBottomPanel(Entity* e);
	void showBottomPanel() { bottomPanel_->getComponent<Tween>(ecs::Tween)->GoToA(); setUnplacedClues(true); };
	void hideBottomPanel() { bottomPanel_->getComponent<Tween>(ecs::Tween)->GoToB(); setUnplacedClues(false);};
	void showRightPanel() { rightPanel_->getComponent<Tween>(ecs::Tween)->GoToB(); };
	void hideRightPanel() { rightPanel_->getComponent<Tween>(ecs::Tween)->GoToA(); textTitle_->setEnabled(false); textDescription_->setEnabled(false); };
	void setUnplacedClues(bool b);
	void createPanels(int& bottomPanelH);
	void createClues(int bottomPanelH);
	void changeText(string newT, string newD);
	void checkEvent(CentralClue* cc);
	vector<Entity*> clueEntities_;
	Entity* bottomPanel_;
	Entity* rightPanel_;
	Entity* mng_;
	ScrollerLimited* scroll_;
	Entity* cursor_;												//De momento solo sirve para mover la c�mara
	Entity* background_;
	vector<Clue*> playerClues_;
	Drag* draggedItem_ = nullptr;							//Objeto arrastrandose
	Text* textTitle_ = nullptr;
	Text* textDescription_ = nullptr;
};