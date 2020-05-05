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

	Entity* e = entityManager_->addEntity(2);
	int w = game_->getGame()->getWindowWidth() / 3;
	int h = game_->getGame()->getWindowHeight() / 10;
	Transform* etr = e->addComponent<Transform>(game_->getGame()->getWindowWidth() / 2 - w / 2, game_->getGame()->getWindowHeight() / 2 - h / 2, w, h);
	e->addComponent<Rectangle>(SDL_Color{ COLOR(0xccccccff) });
	e->addComponent<ButtonOneParametter<LoremIpsum*>>(std::function<void(LoremIpsum*)>([](LoremIpsum* g) { g->getStateMachine()->PlayGame(); }), game_);
	string buttonText = "PLAY O JUGAR";
	e->addComponent<Text>(buttonText, etr->getPos() + Vector2D(etr->getW() / 2 - (buttonText.size() * 24 / 4), etr->getH() / 2 - 12), -1, Resources::RobotoTest24, 0);
	
	
	Entity* e3 = entityManager_->addEntity(2);
	etr = e3->addComponent<Transform>(game_->getGame()->getWindowWidth() / 2 - w / 2, game_->getGame()->getWindowHeight() / 2 + h , w, h);
	e3->addComponent<Rectangle>(SDL_Color{ COLOR(0xccccccff) });
	e3->addComponent<ButtonOneParametter<LoremIpsum*>>(std::function<void(LoremIpsum*)>([](LoremIpsum* g) { g->getStateMachine()->PlayEditor(); }), game_);
	buttonText = "Dialog Editor";
	e3->addComponent<Text>(buttonText, etr->getPos() + Vector2D(etr->getW() / 2 - (buttonText.size() * 24 / 4), etr->getH() / 2 - 12), -1, Resources::RobotoTest24, 0);
	
	
	Entity* e2 = entityManager_->addEntity(0);
	e2->addComponent<Transform>(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
	e2->addComponent<Sprite>(background);

	game_->getGame()->getAudioMngr()->playMusic(Resources::MTint, 0);
	game_->getGame()->getAudioMngr()->nextMusic(Resources::MTloo, -1);
	game_->getGame()->getAudioMngr()->setMusicVolume(15);
	game_->getGame()->getAudioMngr()->setChannelVolume(10);
}
