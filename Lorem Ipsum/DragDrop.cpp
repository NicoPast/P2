#include "DragDrop.h"
#include "SDL_image.h"
#include "Chinchetario.h"
DragDrop::DragDrop(Chinchetario* ch) : Component(ecs::DragDrop), tr_(nullptr), ch_(ch) {
}
void DragDrop::init() {
	//M�todos cambiar cursor, dejado para saber
	//SDL_Surface* surface = IMG_Load("../assets/images/star.png");
	//SDL_SetCursor(SDL_CreateColorCursor(surface, 25, 25));
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
}
void DragDrop::update() {	//Al siguiente frame de estar arrastrando empieza a actualizar su posici�n
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		if (!lastInLayer_) {
			lastInLayer_ = true;
			entity_->getEntityMangr()->setLastInLayer(entity_, entity_->getLayer());
		}
		Vector2D pos = ih->getMousePos();	//Posici�n del rat�n en este frame
		Vector2D newPos = { pos.getX() + dragPos_.getX(),  pos.getY() + dragPos_.getY() };
		tr_->setPos(newPos);
	}
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {	//�Parametrizar el bot�n para configurarlo?
			Vector2D pos = ih->getMousePos();			//Guarda la posici�n del rat�n
			SDL_Point p = { pos.getX(), pos.getY() };
			rect_ = SDL_Rect RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
			//CAMBIAR
			if (SDL_PointInRect(&p, &rect_) && ch_->compareDragLayerIndex(entity_->getLayerIndex(), entity_->getLayer())) {			//Si es click dentro del sprite, activa el drag y guarda su posici�n relativa
				dragging_ = true;
				dragPos_ = {rect_.x - pos.getX(), rect_.y - pos.getY()};
			}
		}
	}
	else if (!ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) && dragging_) 
	{
		dragging_ = false;	//Si suelta el bot�n deja de arrastrar
		lastInLayer_ = false;
		ch_->resetDragLayerIndex();	//Si suelta, no tiene ning�n objeto agarrado
	}

}
