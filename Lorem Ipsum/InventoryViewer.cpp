#include "InventoryViewer.h"
#include "Chinchetario.h"
InventoryViewer::InventoryViewer(Chinchetario* ch) : Component(ecs::InventoryViewer), tr_(nullptr), dd_(nullptr), chinchetario_(ch) {

}
void InventoryViewer::init() {
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
	view_ = false;
	ini_ = 0;
}

void InventoryViewer::renderizaPistas() {
	//Comprobar que el vector de pistas sea mayor o igual que 5 
	if (pistas_.size() > 0) {
		if (pistas_.size() >= 5) {

			for (int i = 0; i < 5; i++) {
				Transform* pTR = pistas_[i + ini_]->getComponent<Transform>(ecs::Transform);
				Vector2D offset = Vector2D(pTR->getW() / 2, pTR->getH() / 2);
				double posX = (tr_->getW() / 5);
				double posY = tr_->getPos().getY();
				pTR->setPos((posX * i) + offset.getX(), posY + offset.getY());
			}

		}
		else {
			for (int i = 0; i < pistas_.size(); i++) {
				Transform* pTR = pistas_.at(i + ini_)->getComponent<Transform>(ecs::Transform);
				double posX = (tr_->getW() / (pistas_.size() + 1));
				double posY = tr_->getPos().getY();

				Vector2D offset = Vector2D(pTR->getW() / 2, pTR->getH() / 2);

				pTR->setPos((posX * (i + 1)) - offset.getX(), posY + offset.getY());
			}
		}
	}
	
}

void InventoryViewer::update() {
	//Comprobar que las pistas sigan dentro del inventario
	//Comprobar que las pistas NO entren en el visor del text (aka que no salga a la derecha del visor del inventario)
	InputHandler* ih = InputHandler::instance();

	Vector2D mousePos = ih->getMousePos();			 //Guarda la posición del ratón
	SDL_Point p = { mousePos.getX(), mousePos.getY() };
	if (dd_ != nullptr) {
		//Si acaba de soltar la pista agarrada
		if (!dd_->getDragging()) {

			Transform* pTR = pistas_.at(index_)->getComponent<Transform>(ecs::Transform);

			rect_ = SDL_Rect RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
			if (!SDL_PointInRect(&p, &rect_)) {
				//la vuelve a poner en la posición inicial
				chinchetario_->activePista(pistas_.at(index_));
				pistas_.erase(pistas_.begin()+index_);
				chinchetario_->inactivePistas_.erase(chinchetario_->inactivePistas_.begin()+index_);
				cout << chinchetario_->activePistas_.size() << "//" << chinchetario_->inactivePistas_.size()<< endl;

			}
			renderizaPistas();
			dd_ = nullptr;
		}
	}
	else if(pistas_.size() >0){
		//pilla qué pista está siendo agarrada
		int i = ini_, j;
		if (pistas_.size() >= 5) j = 5;
		else j = pistas_.size();

		dd_ = pistas_.at(i)->getComponent<DragDrop>(ecs::DragDrop);
		while (!dd_->getDragging() && i < j-1) {
			i++;
			dd_ = pistas_.at(i)->getComponent<DragDrop>(ecs::DragDrop);
		}
		if (!dd_->getDragging()) dd_ = nullptr;
		else index_ = i;
	}
	
	

	
	

}




