#include "DragTL.h"

void DragTL::update()
{
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		if (!entity_->isLastInLayer()) {
			entity_->getEntityMangr()->setLastInLayer(entity_);
		}
		Vector2D pos = ih->getMousePos();	//Posici�n del rat�n en este frame
		Vector2D newPos = { pos.getX() + dragPos_.getX(),  pos.getY() + dragPos_.getY() };
		tr_->setPos(newPos);

	}
	Drag::update();
}
