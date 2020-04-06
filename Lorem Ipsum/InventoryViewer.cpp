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

void InventoryViewer::renderizaPistas(int ini) {
	//Comprobar que el vector de pistas sea mayor o igual que 5 
	if (pistas_->size() > 0) {
		//if (pistas_->size() >= 5) {

			for (int i = 0; i < pistas_->size(); i++) {
				Transform* pTR = pistas_->at(i)->getComponent<Transform>(ecs::Transform);
				Vector2D offset = Vector2D(pTR->getW() / 2, pTR->getH() / 2);
				double posX = (tr_->getW() / 5);
				double posY = tr_->getPos().getY();
				pTR->setPos((posX * i + ini) + offset.getX(), posY + offset.getY());
			}

		//}
	//	else {
	//		for (int i = 0; i < pistas_->size(); i++) {
	//			Transform* pTR = pistas_->at(i + ini_)->getComponent<Transform>(ecs::Transform);
	//			double posX = (tr_->getW() / (pistas_->size() + 1));
	//			double posY = tr_->getPos().getY();

	//			Vector2D offset = Vector2D(pTR->getW() / 2, pTR->getH() / 2);

	//			pTR->setPos((posX * (i + 1)) - offset.getX(), posY + offset.getY());
	//		}
	//	}
	}

}

void InventoryViewer::update() {
		
	sacaPista();

	for (auto it : *pistas_) {
		Transform* pTR = it->getComponent<Transform>(ecs::Transform);
		if (pTR->getPos().getX() + pTR->getW() < ini_ ||
			pTR->getPos().getX() > ini_ + 500) {
			it->setActive(false);
		}
		else it->setActive(true);
	}
}

void InventoryViewer::sacaPista() {
	InputHandler* ih = InputHandler::instance();

	if (dd_ != nullptr) {
		//Si acaba de soltar la pista agarrada
		if (!dd_->getDragging()) {

			Vector2D mousePos = ih->getMousePos();			 //Guarda la posición del ratón
			SDL_Point p = { mousePos.getX(), mousePos.getY() };

			Transform* pTR = pistas_->at(index_)->getComponent<Transform>(ecs::Transform);
			Transform* txtpTR = chinchetario_->getTxtPanel()->getComponent<Transform>(ecs::Transform);

			thisRect_ = SDL_Rect RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
			SDL_Rect txtpRect = SDL_Rect RECT(txtpTR->getPos().getX(), txtpTR->getPos().getY(), txtpTR->getW(), txtpTR->getH());

			if (!SDL_PointInRect(&p, &thisRect_) && !SDL_PointInRect(&p, &txtpRect)) {
				chinchetario_->activatePista(pistas_->at(index_));
				pistas_->erase(pistas_->begin() + index_);
			}

			if (pistas_->size() > 0) renderizaPistas(pistas_->front()->getComponent<Transform>(ecs::Transform)->getPos().getX());
			dd_ = nullptr;
			renderizaPistas();
		}
	}
	else if (pistas_->size() > 0) {
		//pilla qué pista está siendo agarrada
		int i = ini_, j = pistas_->size();

		dd_ = pistas_->at(i)->getComponent<DragDrop>(ecs::DragDrop);
		while (!dd_->getDragging() && i < j - 1) {
			i++;
			dd_ = pistas_->at(i)->getComponent<DragDrop>(ecs::DragDrop);
		}
		if (!dd_->getDragging()) dd_ = nullptr;
		else index_ = i;
	}
}




