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
#ifdef _DEBUG
	if (funcChanged && !StoryManager::instance()->showingHitbox_)
		return;
#endif // _DEBUG

	
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		if (!entity_->isLastInLayer()) {
			entity_->getEntityMangr()->setLastInLayer(entity_);
			auto chldrn = tr_->getChildren();
			for (int i = 0; i < chldrn.size(); i++) {
				auto grchldrn = chldrn[i]->getChildren();
				for (int j = 0; j < grchldrn.size(); j++) {
					entity_->getEntityMangr()->setLastInLayer(grchldrn[j]->getEntity());
				}
			}
		}
		Vector2D pos = ih->getMousePos();	//Posici�n del rat�n en este frame
		Vector2D newPos = { pos.getX() + dragPos_.getX(),  pos.getY() + dragPos_.getY()};
		
		if (!entity_->isUI())
			newPos = newPos + game_->getCamera()->getPos();
		tr_->setPos(newPos);
		//Si tiene una línea enganchada, la actualiza
		if (l_ != nullptr) {
			l_->setFin(tr_->getPos() + linePos_);
		}
	}
	Drag::update();
}
