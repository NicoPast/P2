#include "Chinchetario.h"

Chinchetario::Chinchetario(LoremIpsum* game) : State(game) {
	init();
};

void Chinchetario::init() {
	//dos entidades principales: visor de texto y visor del inventario

	//Componente TextViewer

	Entity* inv = entityManager_->addEntity();
	Transform* invTR = inv->addComponent<Transform>();
	inv->addComponent<InventoryViewer>();
	inv->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	invTR->setWH(400,200);
	invTR->setPos(0, (640 - 200));

}
