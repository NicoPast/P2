#include "InventoryViewer.h"

InventoryViewer::InventoryViewer() : Component(ecs::InventoryViewer), tr_(nullptr) {

}
void InventoryViewer::init() {
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
	view_ = false;
}


