#include "CreditsState.h"
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
#include "Tween.h"
#include "Text.h"
#include "SimpleMoveBehavior.h"

CreditsState::CreditsState(LoremIpsum* game) :State(game)
{
	camera_->setPos(0, 0);
	camera_->setWidth(1080); camera_->setHeight(720);
	camera_->setLeftMargin(0); camera_->setRightMargin(0);
	Texture* background = game_->getGame()->getTextureMngr()->getTexture(Resources::MainMenuNoText);
	camera_->setLimitX(background->getWidth());
	camera_->setLimitY(background->getHeight());
	Entity* bG = entityManager_->addEntity(0);
	bG->addComponent<Transform>(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
	bG->addComponent<Sprite>(background);


	texts.push_back("Equipo art\u00edstico:\n	Eva Lucas \n Tom\u00e1s L\u00f3pez");
	texts.push_back("Equipo musical:\n	Jorge Bello\n Nicol\u00e1s Pastore");
	texts.push_back("Equipo de dise\u00F1o:\n	Jorge Bello\n Nicol\u00e1s Pastore\n Ricardo Sulbar\u00e1n \n Ana Mart\u00edn \n Rub\u00e9n Bueno \n Eva Lucas\n David Godoy");
	texts.push_back("Equipo de dise\u00F1o:\n	Ricardo Sulbar\u00e1n \n Ana Mart\u00edn \n David Godoy \n Aitor Garc\u00eda");
	texts.push_back("Agradecimientos:\n	Laura Mart\u00edn \n Samir Genaim \n Agonay Socas \n Cleon");

	text_ = entityManager_->addEntity(1);
	int w = 50;
	Transform* tr = text_->addComponent<Transform>(background->getWidth() / 2, background->getHeight(), w, 200);
	Text* t = text_->addComponent<Text>("", tr->getPos(), w, Resources::RobotoTest24, 0);
	t->setText(texts[0]);
	SimpleMoveBehavior* move = text_->addComponent<SimpleMoveBehavior>();
	tr->setVelY(-5);

}

void CreditsState::update()
{
	Transform* tr = GETCMP2(text_, Transform);
	if (tr->getPos().getY() <= 0 && i<texts.size()) {
		tr->setPos(1080 / 2, 720);
		Text* t = GETCMP2(text_, Text);
		t->setText(texts[i+1]);
		i++;
	}
	State::update();
}
