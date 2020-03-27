#include "PlayState.h"
PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {
	Entity* e3 = entityManager_->addEntity(0);
	dragItems.push_back(e3);
	Transform* te3 = e3->addComponent<Transform>();
	SDL_Color c = { COLOR(0x00FF00FF) };
	e3->addComponent<Rectangle>(c);
	e3->addComponent<DragDrop>(this);
	te3->setPos(250, 200);
	te3->setWH(200, 200);

	c = { COLOR(0xFF0000FF) };
	Entity* e = entityManager_->addEntity(0);
	dragItems.push_back(e);
	Transform* te = e->addComponent<Transform>();
	e->addComponent<Rectangle>(c);
	e->addComponent<DragDrop>(this);
	te->setPos(200, 250);
	te->setWH(200, 200);

	c = { COLOR(0x0000FFFF) };
	Entity* e2 = entityManager_->addEntity(0);
	dragItems.push_back(e2);
	Transform* te2 = e2->addComponent<Transform>();
	e2->addComponent<Rectangle>(c);
	e2->addComponent<DragDrop>(this);
	te2->setPos(200, 200);
	te2->setWH(200, 200);


	
}
bool PlayState::compareDragItemIndex(int index, int layer) {
	bool bigger = (index > dragItemIndex);
	if (bigger) {
		if (dragItemIndex >= 0) {
		auto actualLayer = entityManager_->getLayer(layer);
		actualLayer[dragItemIndex].get()->getComponent<DragDrop>(ecs::DragDrop)->deactivateDrag();
		}
		dragItemIndex = index;
	}
	return bigger;
}