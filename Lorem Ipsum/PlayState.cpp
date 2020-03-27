#include "PlayState.h"
#include "LoremIpsum.h"
PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {


	//t->addComponent<TextTest>("En un lugar de la Mancha2, de cuyo nombre no quiero acordarme3, no ha mucho tiempo que viv�a un hidalgo de los de lanza en astillero, adarga antigua", 100);

	Vector2D p = { 20, 0 };
	Entity* t = entityManager_->addEntity(1);
	Text* texto = t->addComponent<Text>("ey", p, 200, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 100);
	texto->setNextText("Hola wenas soy wario");
	texto->addSoundFX(Resources::Bip);
	texto->addSoundFX(Resources::Paddle_Hit);
	
	Entity* e3 = entityManager_->addEntity(1);
	Transform* te3 = e3->addComponent<Transform>();
	SDL_Color c = { COLOR(0x00FF00FF) };
	e3->addComponent<Rectangle>(c);
	e3->addComponent<DragDrop>(this);
	te3->setPos(250, 200);
	te3->setWH(200, 200);

	c = { COLOR(0xFF0000FF) };
	Entity* e = entityManager_->addEntity(1);
	Entity* t2 = entityManager_->addEntity(0);
	Transform* te = e->addComponent<Transform>();
	Entity* mobile = entityManager_->addEntity(2);
	Transform* mobTr = mobile->addComponent<Transform>();
	Phone* mobileComp = mobile->addComponent<Phone>();
	mobile->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	mobTr->setPos(400, 500);
	mobTr->setWH(160, 260);
	vector<Transform*> icons;
	for (int i = 0; i < 13; i++) {
		Entity* icon = entityManager_->addEntity();
		Transform* itr = icon->addComponent<Transform>();
		icon->addComponent<Rectangle>();
		switch (i % 3)
		{
		case 0:
			icon->addComponent<Button>(callbackTest0);
			break;
		case 1:
			icon->addComponent<Button>(callbackTest1);
			break;
		case 2:
			icon->addComponent<Button>(callbackTest2);
			break;
		default:
			break;
		}
		itr->setPos(410 + (i % 3) * 50, 510 + (i / 3) * 50);
		itr->setWH(40, 40);
		icons.push_back(itr);
	}


	mobileComp->initIcons(icons);

	Entity* gameManager = entityManager_->addEntity(0);
	Scroller* scroller = gameManager->addComponent<Scroller>();
	//ScrollerLimited* scroller = gameManager->addComponent<ScrollerLimited>();
	scroller->addItem(te);

	Entity* player = entityManager_->addEntity(0);
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>();
	player->addComponent<PlayerMovement>();
	player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	tp->setPos(200, 250);
	tp->setWH(30, 30);
	e->addComponent<Rectangle>(c);
	e->addComponent<DragDrop>(this);
	te->setPos(200, 250);
	te->setWH(200, 200);

	c = { COLOR(0x0000FFFF) };
	Entity* e2 = entityManager_->addEntity(1);
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