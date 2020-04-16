#include "DragDrop.h"
#include "SDL_image.h"
#include "Chinchetario.h"

DragDrop::DragDrop(Chinchetario* ch, CallBackDD* cb) : Drag(ch), f_(cb){
}
//void DragDrop::init() {
//	//M�todos cambiar cursor, dejado para saber
//	//SDL_Surface* surface = IMG_Load("../assets/images/star.png");
//	//SDL_SetCursor(SDL_CreateColorCursor(surface, 25, 25));
//}
void DragDrop::update() {	//Al siguiente frame de estar arrastrando empieza a actualizar su posici�n
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		if (!entity_->isLastInLayer()) {
			entity_->getEntityMangr()->setLastInLayer(entity_, entity_->getLayer());
		}
		Vector2D pos = ih->getMousePos();	//Posicion del raton en este frame
		Vector2D newPos = { pos.getX() + dragPos_.getX(),  pos.getY() + dragPos_.getY() };
		tr_->setPos(newPos);
	}
	Drag::update();
}
