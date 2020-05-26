#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Drag.h"
#include "Line.h"
class Chinchetario;
using CallBackDD = void(Chinchetario*, Entity*);


class DragDrop : public Drag
{
public:
	DragDrop(Chinchetario* ch, CallBackDD* cb);
	~DragDrop() {};
	void update() override;
	//Se engancha a la línea
	void setLine(Line* l) { l_ = l; linePos_ = { l_->getFin().getX() - tr_->getPos().getX(), l_->getFin().getY() - tr_->getPos().getY() }; parent_ = tr_->getParent(); }
	//Se desengancha de la línea
	void detachLine() { l_ = nullptr; parent_ = nullptr; }
#ifdef _DEBUG
		virtual void clearFuncs() { funcChanged = true; };
	bool funcChanged = false;
#endif // _DEBUG
private:
	//Hace la función asociada y se reengancha al padre que tenía al hacer func2
	virtual void func() 
	{
#ifdef _DEBUG
		if (funcChanged)
		{
			entity_->getComponent<Transform>(ecs::Transform)->finalPos = this->dragPos_;
		}
		else
#endif // _DEBUG
		{
			if (parent_ != nullptr) 
				tr_->setParent(parent_);
			f_(ch_, entity_); 
		}
	}
	//Si tiene padre, se desengancha de él
	virtual void func2() { if (tr_->getParent() != nullptr) tr_->eliminateParent(); }
	CallBackDD* f_ = nullptr;
	Line* l_ = nullptr;
	Vector2D linePos_ = Vector2D(0, 0);
	Transform* parent_ = nullptr;


};

