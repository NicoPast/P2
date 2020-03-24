#include "PlayState.h"
#include "LoremIpsum.h"
PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {
	Entity* t = entityManager_->addEntity();
	//t->addComponent<TextTest>("En un lugar de la Mancha2, de cuyo nombre no quiero acordarme3, no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua", 100);

	Entity* t2 = entityManager_->addEntity();
	Vector2D p = { 20, 0 };
	Text* texto = t->addComponent<Text>("Morbidolorsapien, sollicitudin at lacinia eget, sodales vel tellus. Nullam condimentum nunc id lorem facilisis, id viverra est blandit. ", p, 200, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 100);
	texto->setNextText("Hola wenas soy ÜNÁ");
	texto->addSoundFX(Resources::Bip);
	texto->addSoundFX(Resources::Paddle_Hit);
	
	Entity* e = entityManager_->addEntity();
	Transform* te = e->addComponent<Transform>();
	e->addComponent<Rectangle>();
	e->addComponent<DragDrop>();
	te->setPos(200, 200);
	te->setWH(20, 20);
	
}