#include "Chinchetario.h"
#include "LoremIpsum.h"

Chinchetario::Chinchetario(LoremIpsum* game) : State(game) {
	init();
};

void Chinchetario::init() {
	//dos entidades principales: visor de texto y visor del inventario

	//visor del inventario
	inv_ = entityManager_->addEntity();
	Transform* invTR = inv_->addComponent<Transform>();
	InventoryViewer* invV = inv_->addComponent<InventoryViewer>(this);
	inv_->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	invTR->setWH(500, 100);
	invTR->setPos(0, (480 - invTR->getH()));
	SDL_Color c = { COLOR(0xFF00FFFF) };

	Entity* pista = entityManager_->addEntity(Layers::DragDropLayer);
	Transform* pTR = pista->addComponent<Transform>();
	pista->addComponent<Rectangle>(c);
	DragDrop* drdr = pista->addComponent<DragDrop>(this);
	drdr->setTxt("jajasi 0");
	pista->addComponent<Button>(pistaCB, drdr);
	pTR->setWH(50, 50);
	pTR->setPos(800, 800);
	inactivePistas_.push_back(pista);

	c = { COLOR(0x00FF00FF) };
	//creamos un vector de pistas (provisional hasta que sepamos como meter las pistas)
	for (int i = 0; i < 6; i++) {
		Entity* pista = entityManager_->addEntity(Layers::DragDropLayer);
		Transform* pTR = pista->addComponent<Transform>();
		pista->addComponent<Rectangle>(c);
		drdr = pista->addComponent<DragDrop>(this);	
		drdr->setTxt("jajasi " + i +1);
		pista->addComponent<Button>(pistaCB, drdr);

		pTR->setWH(50, 50);
		pTR->setPos(800, 800);
		inactivePistas_.push_back(pista);
	}
	invV->setPistas(&inactivePistas_);
	invV->renderizaPistas();

	//visor del texto de las pistas
	txtP_ = entityManager_->addEntity(Layers::LastLayer);
	Transform* txtTR = txtP_->addComponent<Transform>();
	txtP_->addComponent<Rectangle>(SDL_Color{ COLOR(0x604E4B00) });
	txtTR->setWH(140, 480);
	txtTR->setPos(500, 0);
	//txtPTXT_ = txtP_->addComponent<Text>("", txtTR->getPos(), -1, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 0, false);
	txtPTXT_ = txtP_->addComponent<Text>();

}

vector<Entity*>* Chinchetario::getPistas_(bool isActive) {
	//true = pistas activas
	//false = pistas inactivas, aka pistas en el inventario
	if (isActive) return &activePistas_;
	else return &inactivePistas_;
}

void Chinchetario::update() {
	State::update();
	añadePista();
}

void Chinchetario::añadePista() {
	InputHandler* ih = InputHandler::instance();
	if (dd_ != nullptr) {
		//Si acaba de soltar la pista agarrada
		if (!dd_->getDragging()) {


			Vector2D mousePos = ih->getMousePos();			 //Guarda la posición del ratón
			SDL_Point p = { mousePos.getX(), mousePos.getY() };

			Transform* pTR = activePistas_.at(dragIndex_)->getComponent<Transform>(ecs::Transform);
			Transform* invTR = inv_->getComponent<Transform>(ecs::Transform);
			Transform* txtpTR = txtP_->getComponent<Transform>(ecs::Transform);

			SDL_Rect invRect = RECT(invTR->getPos().getX(), invTR->getPos().getY(), invTR->getW(), invTR->getH());
			SDL_Rect txtRect = RECT(txtpTR->getPos().getX(), txtpTR->getPos().getY(), txtpTR->getW(), txtpTR->getH());
			if (SDL_PointInRect(&p, &invRect)) {
				//la vuelve a poner en la posición inicial
				inactivePistas_.push_back(activePistas_.at(dragIndex_));
				activePistas_.erase(activePistas_.begin() + dragIndex_);
				InventoryViewer* invV = inv_->getComponent<InventoryViewer>(ecs::InventoryViewer);
				if (inactivePistas_.size() >= 5) {
					pTR->setPos(800, 800);
				}
				invV->renderizaPistas();
			}
			else if (SDL_PointInRect(&p, &txtRect)) {
				pTR->setPos(initPistaPos_);
			}

			dd_ = nullptr;
		}
	}
	else if (activePistas_.size() > 0) {
		//pilla qué pista está siendo agarrada
		int i = 0, j = activePistas_.size();

		dd_ = activePistas_.at(i)->getComponent<DragDrop>(ecs::DragDrop);
		while (!dd_->getDragging() && i < j - 1) {
			i++;
			dd_ = activePistas_.at(i)->getComponent<DragDrop>(ecs::DragDrop);
		}
		if (!dd_->getDragging()) dd_ = nullptr;
		else {
			dragIndex_ = i;
			Transform* pTR = activePistas_.at(i)->getComponent<Transform>(ecs::Transform);
			initPistaPos_ = pTR->getPos();
		}
	}
}
bool Chinchetario::compareDragLayerIndex(int index, int layer) {
	bool bigger = (index > dragLayerIndex);
	if (bigger) {
		if (dragLayerIndex >= 0) {
			auto actualLayer = entityManager_->getLayer(layer);
			actualLayer[dragLayerIndex].get()->getComponent<DragDrop>(ecs::DragDrop)->deactivateDrag();
		}
		dragLayerIndex = index;
	}
	return bigger;
}

void Chinchetario::pistaCB(DragDrop* dd) {
	//Le pasamos dd porque PROVISIONALMENTE el texto lo tenemos aquí ya que necesitamos almacenar las pistas
	txtPTXT_->setText(dd->getTxt());
}