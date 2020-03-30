#pragma once
#include "State.h"
#include "Rectangle.h";
#include "InventoryViewer.h"
#include "Button.h"
#include "Text.h"
class LoremIpsum;

class Chinchetario : public State
{
public:
	Chinchetario(LoremIpsum* game);
	virtual ~Chinchetario() {  }
	void update();
	void activatePista(Entity* p) { activePistas_.push_back(p); scroll_->removeItem(p->getComponent<Transform>(ecs::Transform)); }
	void añadePista();
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
	DragDrop* dd_ = nullptr;
	int dragIndex_;
	int dragLayerIndex = -1;									//Objeto arrastrandose segun su capa
	Vector2D initPistaPos_;										//Posición auxiliar de una pista para comprobaciones
	static void pistaCB(DragDrop* dd, Text* t);
};

