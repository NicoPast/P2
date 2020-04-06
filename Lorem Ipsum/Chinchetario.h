#pragma once
#include "State.h"
#include "Rectangle.h";
#include "DragDrop.h"
#include "Text.h"

class StoryManager;
class LoremIpsum;

class Chinchetario : public State
{
public:
	Chinchetario(LoremIpsum* game, StoryManager* storyManager);
	virtual ~Chinchetario() {  }
	void update();
	void activatePista(Entity* p) { activePistas_.push_back(p); scroll_->removeItem(p->getComponent<Transform>(ecs::Transform)); }
	void a�adePista();
	vector<Entity*>* getPistas_(bool isActive);
	bool compareDragLayerIndex(int index, int layer);
	void resetDragLayerIndex() { dragLayerIndex = -1; }
	Entity* getTxtPanel() { return txtP_; }

private:
	void init();
	vector<Entity*> inactivePistas_;
	vector<Entity*> activePistas_;
	Entity* inv_;
	Entity* txtP_;
	Entity* mng_;
	ScrollerLimited* scroll_;
	Text* txtPTXT_;
	Text* textTitle_;
	Text* textDescription_;
	DragDrop* dd_ = nullptr;
	int dragIndex_;
	int dragLayerIndex = -1;									//Objeto arrastrandose segun su capa
	Vector2D initPistaPos_;										//Posici�n auxiliar de una pista para comprobaciones
	StoryManager* storyManager_;
};

