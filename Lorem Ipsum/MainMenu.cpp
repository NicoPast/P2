#include "MainMenu.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "ButtonIcon.h"

MainMenu::MainMenu(LoremIpsum* game) : State(game) {
	init();
};

void MainMenu::init() {
	Entity* e = entityManager_->addEntity();
	Transform* etr = e->addComponent<Transform>(200, 200, 300, 100);
	e->addComponent<Rectangle>();
	e->addComponent<ButtonIcon>(callbackLaunchGame, game_);
}

void MainMenu::callbackLaunchGame(LoremIpsum* game)
{
	game->getStateMachine()->PlayGame();
}
