#pragma once

#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "ScrollerLimited.h"
#include "Pin.h"
#include "Drag.h"
#include "checkML.h"

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
	void showText() { textDescription_->setEnabled(true); textTitle_->setEnabled(true); GETCMP2(cluePhoto_, Sprite)->setEnabled(true);}

	void close();
	void showRightPanel() { rightPanel_->getComponent<Tween>(ecs::Tween)->GoToB(); };
	void hideRightPanel() { rightPanel_->getComponent<Tween>(ecs::Tween)->GoToA(); textTitle_->setEnabled(false); textDescription_->setEnabled(false);  GETCMP2(cluePhoto_, Sprite)->setEnabled(false);
	};
protected:
	bool checkClueInBottomPanel(Entity* e);
	void showBottomPanel() { bottomPanel_->getComponent<Tween>(ecs::Tween)->GoToB(); };
	void hideBottomPanel() { bottomPanel_->getComponent<Tween>(ecs::Tween)->GoToA(); setUnplacedClues(false);};

	void setUnplacedClues(bool b);
	void createPanels();
	void createClues(Clue* c, int i);
	void changeText(Clue* c);
	void checkEvent(CentralClue* cc);
	void updateClues();
	vector<Entity*> clueEntities_;
	Entity* bottomPanel_ = nullptr;
	Entity* rightPanel_ = nullptr;
	Entity* cluePhoto_ = nullptr;
	Entity* mng_ = nullptr;
	ScrollerLimited* scroll_ = nullptr;
	Entity* cursor_ = nullptr;										//De momento solo sirve para mover la c�mara
	Entity* background_ = nullptr;
	vector<Clue*> playerClues_;
	Drag* draggedItem_ = nullptr;							//Objeto arrastrandose
	Text* textTitle_ = nullptr;
	Text* textDescription_ = nullptr;
	int bottomPanelH_ = 0;
};