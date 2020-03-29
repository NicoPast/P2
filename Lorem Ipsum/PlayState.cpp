#include "PlayState.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "ButtonIcon.h"
#include "Rectangle.h"
#include "Phone.h"
#include "Scroller.h"
#include "ScrollerLimited.h"
#include "PlayerKBCtrl.h"
#include "PlayerMovement.h"
#include "Interactable.h"
#include "InteractableLogic.h"

static void callbackChinchetario(LoremIpsum* game) { game->getStateMachine()->PlayApp(StateMachine::APPS::Chinchetario); };

PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {

	list<Interactable*> interactables;

	Entity* siYeah = entityManager_->addEntity(3);
	Transform* ti = siYeah->addComponent<Transform>();
	siYeah->addComponent<Text>("", Vector2D(400, 200), 500, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 0);
	Interactable* in = siYeah->addComponent<Interactable>("Silla");
	siYeah->addComponent<Rectangle>(SDL_Color{ COLOR(0xFFC0C0C0) });
	ti->setPos(400, 250);
	ti->setWH(30, 30);

	interactables.push_back(in);

	Entity* meSah = entityManager_->addEntity(3);
	Transform* ti2 = meSah->addComponent<Transform>();
	meSah->addComponent<Text>("", Vector2D(450, 200), 500, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 0);
	Interactable* in2 = meSah->addComponent<Interactable>("Mesa");
	meSah->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	ti2->setPos(450, 250);
	ti2->setWH(30, 30);

	interactables.push_back(in2);


	Vector2D p = { 20, 0 };
	Entity* t = entityManager_->addEntity(1);
	Text* texto = t->addComponent<Text>("ey", p, 200, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 100);
	texto->setNextText("Hola wenas soy wario");
	texto->addSoundFX(Resources::Bip);
	texto->addSoundFX(Resources::Paddle_Hit);
	
	Entity* mobile = entityManager_->addEntity(2);
	Transform* mobTr = mobile->addComponent<Transform>();
	Phone* mobileComp = mobile->addComponent<Phone>();
	mobile->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	mobTr->setPos(400, 500);
	mobTr->setWH(160, 260);
	vector<Transform*> icons;
	for (int i = 0; i < 13; i++) {
		Entity* icon = entityManager_->addEntity(3);
		Transform* itr = icon->addComponent<Transform>();
		icon->addComponent<Rectangle>();
		icon->addComponent<ButtonIcon>(callbackChinchetario, game_);
		itr->setPos(410 + (i % 3) * 50, 510 + (i / 3) * 50);
		itr->setWH(40, 40);
		icons.push_back(itr);
	}


	mobileComp->initIcons(icons);



	Entity* player = entityManager_->addEntity(0);
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>();
	player->addComponent<PlayerMovement>();
	player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	tp->setPos(200, 250);
	tp->setWH(30, 30);


	Entity* iLog = entityManager_->addEntity(4);
	iLog->addComponent<InteractableLogic>(interactables, tp);

	//Entity* e3 = entityManager_->addEntity(1);
	//Transform* te3 = e3->addComponent<Transform>();
	//SDL_Color c = { COLOR(0x00FF00FF) };
	//e3->addComponent<Rectangle>(c);
	//e3->addComponent<DragDrop>(this);
	//te3->setPos(250, 200);
	//te3->setWH(200, 200);

	//
	//c = { COLOR(0xFF0000FF) };
	//Entity* e = entityManager_->addEntity(1);
	//Entity* t2 = entityManager_->addEntity(0);
	//Transform* te = e->addComponent<Transform>();
	//e->addComponent<Rectangle>(c);
	//e->addComponent<DragDrop>(this);
	//te->setPos(200, 250);
	//te->setWH(200, 200);



	//c = { COLOR(0x0000FFFF) };
	//Entity* e2 = entityManager_->addEntity(1);
	//Transform* te2 = e2->addComponent<Transform>();
	//e2->addComponent<Rectangle>(c);
	//e2->addComponent<DragDrop>(this);
	//te2->setPos(200, 200);
	//te2->setWH(200, 200);


	Entity* gameManager = entityManager_->addEntity(0);
	Scroller* scroller = gameManager->addComponent<Scroller>();
	//ScrollerLimited* scroller = gameManager->addComponent<ScrollerLimited>();
	scroller->addItem(t->getComponent<Transform>(ecs::Transform));
	
}
