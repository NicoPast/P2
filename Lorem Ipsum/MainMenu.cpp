#include "MainMenu.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "StoryManager.h"
#include "Sprite.h"
#include "Animator.h"
#include "Text.h"
#include "Line.h"
#include "DialogComponent.h"
#include "ButtonOneParametter.h"
#include "LoremIpsum.h"

MainMenu::MainMenu(LoremIpsum* game) : State(game) {
	init();
};

void MainMenu::init() {

	camera_->setPos(0, 0);
	camera_->setWidth(1080); camera_->setHeight(720);
	camera_->setLeftMargin(0); camera_->setRightMargin(0);
	Texture* background = game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuBG);
	camera_->setLimitX(background->getWidth());
	camera_->setLimitY(background->getHeight());
	Entity* bG = entityManager_->addEntity(0);
	bG->addComponent<Transform>(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
	auto anim = bG->addComponent<Animator<int>>();
	createBackground();

	Entity* e = entityManager_->addEntity(4);
	int w = game_->getGame()->getWindowWidth() / 3;
	int h = game_->getGame()->getWindowHeight() / 10;
	Transform* etr = e->addComponent<Transform>(game_->getGame()->getWindowWidth() / 2 - w / 2, game_->getGame()->getWindowHeight(), w, h);

	Vector2D finishPlayPos(game_->getGame()->getWindowWidth() / 2 - w / 2, game_->getGame()->getWindowHeight() / 2 - h / 2);
	Vector2D finishEditorPos(game_->getGame()->getWindowWidth() / 2 - w / 2, game_->getGame()->getWindowHeight() / 2 + h);

	e->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuBut));
	string buttonText = "";
	Text* t1 = e->addComponent<Text>(buttonText, finishPlayPos + Vector2D(20, etr->getH() / 2 - 17), -1, Resources::RobotoTest24, 0);
	auto but = e->addComponent<ButtonOneParametter<LoremIpsum*>>(std::function<void(LoremIpsum*)>([](LoremIpsum* g) { g->getStateMachine()->PlayGame(); }), game_);
	but->setMouseOverCallback([e]() {GETCMP2(e, Sprite)->setTint(220,220,220); });
	but->setMouseOutCallback([e](){GETCMP2(e, Sprite)->clearTint(); });
	
	Entity* e3 = entityManager_->addEntity(4);
	etr = e3->addComponent<Transform>(game_->getGame()->getWindowWidth() / 2 - w / 2, game_->getGame()->getWindowHeight(), w, h);
	e3->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuBut));
	but = e3->addComponent<ButtonOneParametter<LoremIpsum*>>(std::function<void(LoremIpsum*)>([](LoremIpsum* g) { g->getStateMachine()->PlayEditor(); }), game_);
	buttonText = "";
	Text* t2 = e3->addComponent<Text>(buttonText, finishEditorPos + Vector2D(20, etr->getH() / 2 - 17), -1, Resources::RobotoTest24, 0);
	but->setMouseOverCallback([e3]() {GETCMP2(e3, Sprite)->setTint(220, 220, 220); });
	but->setMouseOutCallback([e3]() {GETCMP2(e3, Sprite)->clearTint(); });


	auto tween = e->addComponent<Tween>(finishPlayPos, 20);
	auto tween2 = e3->addComponent<Tween>(finishEditorPos, 20);
	tween->setFunc([t1, t2, tween2](Entity* e)
	{
		t1->setText("Comienza la historia");
		t1->setColor(88,88,88);
		tween2->GoToB();
	}, nullptr);
	tween2->setFunc([t2](Entity* e)
	{
		t2->setText("Dialog Editor");
		t2->setColor(88, 88, 88);
	}, nullptr);


	anim->changeAnim(Resources::MainMenuAnim);
	anim->setFinishFunc([tween](int a) {tween->GoToA(); }, 0);
	
	game_->getGame()->getAudioMngr()->playMusic(Resources::MTint, 0);
	game_->getGame()->getAudioMngr()->nextMusic(Resources::MTloo, -1);
	game_->getGame()->getAudioMngr()->setMusicVolume(15);
	game_->getGame()->getAudioMngr()->setChannelVolume(10);
}
void MainMenu::createBackground()
{
	double sp1 = 1.5;
	double sp2 = 1;
	double sp3 = 0.5;
	Entity* smoke = entityManager_->addEntity(2);
	smoke->addComponent<Transform>(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
	smoke->addComponent<Animator<int>>()->changeAnim(Resources::AnimID::Humo1Anim);

	smoke = entityManager_->addEntity(1);
	smoke->addComponent<Transform>(0, -50, game_->getGame()->getWindowWidth()*2, game_->getGame()->getWindowHeight());
	smoke->addComponent<Animator<int>>()->changeAnim(Resources::AnimID::Humo1Anim);

	buildingLine3 = entityManager_->addEntity(0);
	buildingLine3->setUI(false);
	Texture* background3 = game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuBG3);
	auto tr3 = buildingLine3->addComponent<Transform>(0, 0,
		background3->getWidth()*4, game_->getGame()->getWindowHeight());
	buildingLine3->addComponent<Sprite>(background3);
	tr3->setVelX(-sp3);
	buildings.push_back(buildingLine3);

	buildingLine2 = entityManager_->addEntity(1);
	buildingLine2->setUI(false);
	Texture* background2 = game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuBG2);
	auto tr2 = buildingLine2->addComponent<Transform>(0, 0,
		background2->getWidth()*4, game_->getGame()->getWindowHeight());
	buildingLine2->addComponent<Sprite>(background2);
	tr2->setVelX(-sp2);
	buildings.push_back(buildingLine2);


	buildingLine1 = entityManager_->addEntity(2);
	buildingLine1->setUI(false);
	Texture* background1 = game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuBG1);
	auto tr1 = buildingLine1->addComponent<Transform>(0, 4,
		background1->getWidth()*4, game_->getGame()->getWindowHeight());
	buildingLine1->addComponent<Sprite>(background1);
	tr1->setVelX(-sp1);
	buildings.push_back(buildingLine1);




	buildingLine3r = entityManager_->addEntity(0);
	buildingLine3r->setUI(false);
	tr3 = buildingLine3r->addComponent<Transform>(background3->getWidth() * 4 - 30, 0,
	background3->getWidth() * 4, game_->getGame()->getWindowHeight());
	buildingLine3r->addComponent<Sprite>(background3);
	tr3->setVelX(-sp3);
	buildings.push_back(buildingLine3r);


	buildingLine2r = entityManager_->addEntity(1);
	buildingLine2r->setUI(false);
	tr2 = buildingLine2r->addComponent<Transform>(background2->getWidth() * 4 - 30, 0,
		background2->getWidth() * 4, game_->getGame()->getWindowHeight());
	buildingLine2r->addComponent<Sprite>(background2);
	tr2->setVelX(-sp2);
	buildings.push_back(buildingLine2r);


	buildingLine1r = entityManager_->addEntity(2);
	buildingLine1r->setUI(false);
	tr1 = buildingLine1r->addComponent<Transform>(background1->getWidth() * 4 - 30, 4,
		background1->getWidth() * 4, game_->getGame()->getWindowHeight());
	buildingLine1r->addComponent<Sprite>(background1);
	tr1->setVelX(-sp1);
	buildings.push_back(buildingLine1r);
	for (auto e : buildings)
		e->getComponent<Sprite>(ecs::Sprite)->ignoreCamera(1);

}

void MainMenu::update()
{
	if (game_->getGame()->getTime()  > lastMove + speed)
	{
		Transform* tr;
		for (auto e : buildings)
		{
			tr = e->getComponent<Transform>(ecs::Transform);
			tr->setPosX(tr->getPos().getX() + tr->getVel().getX());
			if (tr->getPos().getX() + tr->getW() < 50)
				tr->setPosX(tr->getW() - 50);
		}
		lastMove = game_->getGame()->getTime();
	}
	if (InputHandler::instance()->isKeyDown(SDLK_UP))
	{
		
	};
	
	if (InputHandler::instance()->isKeyDown(SDLK_DOWN))
	{

	}
	State::update();
}