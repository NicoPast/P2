#include "PlayState.h"
PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {
	Entity* t = entityManager_->addEntity();
	//t->addComponent<TextTest>("En un lugar de la Mancha2, de cuyo nombre no quiero acordarme3, no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua", 100);
	
	Entity* t2 = entityManager_->addEntity();
	t->addComponent<TextTest>("Morbi dolor sapien, sollicitudin at lacinia eget, sodales vel tellus. Nullam condimentum nunc id lorem facilisis, id viverra est blandit. ", 100, 20, 200);
	Entity* e = entityManager_->addEntity();
	Transform* te = e->addComponent<Transform>();
	e->addComponent<Rectangle>();
	e->addComponent<DragDrop>();
	te->setPos(200, 200);
	te->setWH(20, 20);

	//visor del inventario
	Entity* inv = entityManager_->addEntity();
	Transform* invTR = inv->addComponent<Transform>();
	InventoryViewer* invV = inv->addComponent<InventoryViewer>();
	inv->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	invTR->setWH(500, 100);
	invTR->setPos(0, (480-invTR->getH()));



	vector<Entity*> pistas;
	for (int i = 0; i < 8; i++) {
		Entity* pista = entityManager_->addEntity();
		Transform* pTR = pista->addComponent<Transform>();
		pista->addComponent<Rectangle>(SDL_Color{COLOR(0x11111111)});
		pTR->setWH(50, 50);
		pistas.push_back(pista);
	}
	invV->setPistas(pistas);


	
	//visor del texto de las pistas
	Entity* txt = entityManager_->addEntity();
	Transform* txtTR = txt->addComponent<Transform>();
	/*inv->addComponent<InventoryViewer>();*/
	txt->addComponent<Rectangle>(SDL_Color{ COLOR(0x604E4B00) });
	txtTR->setWH(140,480);
	txtTR->setPos(500, 0);
}