#include "Chinchetario.h"

Chinchetario::Chinchetario(LoremIpsum* game) : State(game) {
	init();
};

void Chinchetario::init() {
	//dos entidades principales: visor de texto y visor del inventario
	//Componente Inventory y un componente InventoryViewer
	//Componente TextViewer

	Entity* inv = entityManager_->addEntity();

}
