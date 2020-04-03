#include "MainMenu.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "ButtonIcon.h"
#include "StoryManager.h"
#include "Sprite.h"
#include "Animator.h"
#include "Text.h"
MainMenu::MainMenu(LoremIpsum* game) : State(game) {
	init();
};

void MainMenu::init() {
	Entity* e = entityManager_->addEntity(2);
	int w=game_->getGame()->getWindowWidth()/3;
	int h= game_->getGame()->getWindowHeight() / 10;
	Transform* etr = e->addComponent<Transform>(game_->getGame()->getWindowWidth()/2 - w/2, game_->getGame()->getWindowHeight() / 2 -h/2 , w, h);
	e->addComponent<Rectangle>(SDL_Color{COLOR(0xc0c0c0c0)});
	e->addComponent<ButtonIcon>([](LoremIpsum* li, StoryManager* sm) {li->getStateMachine()->PlayGame(); }, game_);
	string buttonText = "PLAY O JUGAR";
	e->addComponent<Text>(buttonText, etr->getPos()+Vector2D(etr->getW()/2 - (buttonText.size()*24/4), etr->getH()/2 -12), -1, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL24), 0, false);
	Entity* e2 = entityManager_->addEntity(0);
	e2->addComponent<Transform>(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
	e2->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuBG));
	

	Entity* pajarito = entityManager_->addEntity(1);
	pajarito->addComponent<Transform>(0, 0, 60, 60);
	//e2->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::Pajarito))->setAnim(3,3,2000);
	auto a = pajarito->addComponent<Animator<Transform*>>();
	std::function<void(Transform*)> jeje = std::function<void(Transform*)>([](Transform* a) { a->setPosX((int)(a->getPos().getX() + 1) % 1280); });
	
	a->setFunc(jeje, pajarito->getComponent<Transform>(ecs::Transform));
	a->changeAnim(Resources::CoinAnim);

}
void MainMenu::soyUnEnfermo()
{
	
}
