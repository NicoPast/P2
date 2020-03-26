#include "Chinchetario.h"

Chinchetario::Chinchetario(LoremIpsum* game) : State(game) {
	init();
};

void Chinchetario::init() {
	//dos entidades principales: visor de texto y visor del inventario

	//visor del inventario
	Entity* inv = entityManager_->addEntity();
	Transform* invTR = inv->addComponent<Transform>();
	InventoryViewer* invV = inv->addComponent<InventoryViewer>(this);
	inv->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	invTR->setWH(500, 100);
	invTR->setPos(0, (480 - invTR->getH()));

	//creamos un vector de pistas (provisional hasta que sepamos como meter las pistas)
	for (int i = 0; i < 20; i++) {
		Entity* pista = entityManager_->addEntity();
		Transform* pTR = pista->addComponent<Transform>();
		pista->addComponent<Rectangle>(SDL_Color{ COLOR(0x00FF00FF) });
		pista->addComponent<DragDrop>();
		pTR->setWH(50, 50);
		pTR->setPos(800, 800);
		inactivePistas_.push_back(pista);
	}
	invV->setPistas(inactivePistas_);
	invV->renderizaPistas();




	//visor del texto de las pistas
	Entity* txt = entityManager_->addEntity();
	Transform* txtTR = txt->addComponent<Transform>();
	/*inv->addComponent<InventoryViewer>();*/
	txt->addComponent<Rectangle>(SDL_Color{ COLOR(0x604E4B00) });
	txtTR->setWH(140, 480);
	txtTR->setPos(500, 0);

}
