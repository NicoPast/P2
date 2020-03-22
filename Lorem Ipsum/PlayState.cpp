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
	
	Entity* t3 = entityManager_->addEntity();
	Transform* t3tr = t3->addComponent<Transform>();
	t3->addComponent<Rectangle>();
	t3->addComponent<Button>(callbackTest);
	t3tr->setPos(300, 100);
	t3tr->setWH(20, 20);
}