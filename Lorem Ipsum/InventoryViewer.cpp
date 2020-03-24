#include "InventoryViewer.h"

InventoryViewer::InventoryViewer() : Component(ecs::InventoryViewer), tr_(nullptr) {

}
void InventoryViewer::init() {
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
	view_ = false;
}

void InventoryViewer::renderizaPistas(int ini) {
	//Comprobar que el vector de pistas sea mayor o igual que 5 
	if (pistas_.size() > 0) {
		if (pistas_.size() >= 5) {

			for (int i = 0; i < 5; i++) {
				Transform* pTR = pistas_.at(i + ini);
				Vector2D offset = Vector2D(pTR->getW() / 2, pTR->getH() / 2);
				double posX = (tr_->getW() / 5);
				double posY = tr_->getPos().getY();
				pTR->setPos((posX * i) + offset.getX(), posY + offset.getY());
			}

		}
		else {
			for (int i = 0; i < pistas_.size(); i++) {
				Transform* pTR = pistas_.at(i);
				double posX = (tr_->getW() / (pistas_.size() + 1));
				double posY = tr_->getPos().getY();

				Vector2D offset = Vector2D(pTR->getW() / 2, pTR->getH() / 2);

				pTR->setPos((posX * (i + 1)) - offset.getX(), posY + offset.getY());
			}
		}
	}
	
	
}


