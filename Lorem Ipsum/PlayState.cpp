#include "PlayState.h"
#include "LoremIpsum.h"
PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {


	Entity* t = entityManager_->addEntity();
	//t->addComponent<TextTest>("En un lugar de la Mancha2, de cuyo nombre no quiero acordarme3, no ha mucho tiempo que viv�a un hidalgo de los de lanza en astillero, adarga antigua", 100);

	Entity* t2 = entityManager_->addEntity();
	Vector2D p = { 20, 0 };
	Text* texto = t->addComponent<Text>("", p, 200, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 100);
	texto->setNextText("Hola wenas soy �N�");
	texto->addSoundFX(Resources::Bip);
	texto->addSoundFX(Resources::Paddle_Hit);
	
	Entity* e = entityManager_->addEntity();
	Transform* te = e->addComponent<Transform>();
	e->addComponent<Rectangle>();
	e->addComponent<DragDrop>();
	te->setPos(200, 200);
	te->setWH(20, 20);

	Entity* mobile = entityManager_->addEntity();
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

	Entity* gameManager = entityManager_->addEntity();
	Scroller* scroller = gameManager->addComponent<Scroller>();
	//ScrollerLimited* scroller = gameManager->addComponent<ScrollerLimited>();
	scroller->addItem(te);

	Entity* player = entityManager_->addEntity();
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>();
	player->addComponent<PlayerMovement>();
	player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	tp->setPos(200, 250);
	tp->setWH(30, 30);
}
