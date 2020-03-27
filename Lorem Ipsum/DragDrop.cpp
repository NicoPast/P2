#include "DragDrop.h"
#include "SDL_image.h"
#include "PlayState.h"
DragDrop::DragDrop(PlayState* ps) : Component(ecs::DragDrop), tr_(nullptr), ps_(ps) {
}
void DragDrop::init() {
	//Métodos cambiar cursor, dejado para saber
	//SDL_Surface* surface = IMG_Load("../assets/images/star.png");
	//SDL_SetCursor(SDL_CreateColorCursor(surface, 25, 25));
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
}
void DragDrop::update() {	//Al siguiente frame de estar arrastrando empieza a actualizar su posición
	//cout << tr_->getPos() << "||" << tr_->getW() << tr_->getH() << endl;	//Debug
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		if (!lastInLayer_) {
			lastInLayer_ = true;
			entity_->getEntityMangr()->setLastInLayer(entity_, 0);
		}
		Vector2D pos = ih->getMousePos();	//Posición del ratón en este frame
		Vector2D newPos = { pos.getX() + dragPos_.getX(),  pos.getY() + dragPos_.getY() };
		tr_->setPos(newPos);
	}
	if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {	//¿Parametrizar el botón para configurarlo?
		Vector2D pos = ih->getMousePos();			//Guarda la posición del ratón
		SDL_Point p = { pos.getX(), pos.getY() };
		rect_ = SDL_Rect RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
		if (SDL_PointInRect(&p, &rect_) && ps_->compareDragItemIndex(entity_->getLayerIndex(), 0)) {			//Si es click dentro del sprite, activa el drag y guarda su posición relativa
			dragging_ = true;
			dragPos_ = {rect_.x - pos.getX(), rect_.y - pos.getY()};
		}
	}
	else if (!ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) && dragging_) 
	{
		dragging_ = false;	//Si suelta el botón deja de arrastrar
		lastInLayer_ = false;
		ps_->resetDragItemIndex();	//Si suelta, no tiene ningún objeto agarrado
	}

}