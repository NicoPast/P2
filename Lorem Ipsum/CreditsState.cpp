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


	texts.push_back("Equipo art\u00edstico: \\n -Eva Lucas \\n -Tom\u00e1s L\u00f3pez \\nEquipo musical: \\n -Jorge Bello \\n -Nicol\u00e1s Pastore \\nEquipo de dise\u00F1o: \\n -Jorge Bello \\n -Nicol\u00e1s Pastore \\n -Ricardo Sulbar\u00e1n  \\n -Ana Mart\u00edn \\n -Rub\u00e9n Bueno  \\n -Eva Lucas \\n -David Godoy \\n Equipo de dise\u00F1o:	\\n -Ricardo Sulbar\u00e1n \\n -Ana Mart\u00edn \\n -Aitor Garc\u00eda\\n -Agradecimientos:	Laura Mart\u00edn -S amir Genaim - Agonay Socas - Cleon\\n ¡Gracias por jugar!");

	text_ = entityManager_->addEntity(1);
	int w = 400;
	
	Transform* tr = text_->addComponent<Transform>((1280/2)-w/2, background->getHeight()/2, w, 720);
	text_->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::Pixel));
	game_->getGame()->getTextureMngr()->getTexture(Resources::Pixel)->setColorMod(48, 48, 255);
	Text* t = text_->addComponent<Text>("", tr->getPos()+ Vector2D(5, 0), w, Resources::RobotoTest24, 0);
	t->setText(texts[0]);
	SimpleMoveBehavior* move = text_->addComponent<SimpleMoveBehavior>();
	tr->setVelY(-0.5);
	for (int i = 0; i<t->getLines().size();i++)
	{
		t->changeLineColor(i, 255, 140, 140);
	}


}

void CreditsState::update()
{
	Transform* tr = GETCMP2(text_, Transform);
	if (tr->getPos().getY() <= 0) {
		tr->setVel(Vector2D(0, 0));
		GETCMP2(text_, Text)->setPos(tr->getPos() + Vector2D(5, 0));
	}
	if (tr->getVel().getY() != 0)
		GETCMP2(text_, Text)->setPos(tr->getPos() + Vector2D(5, 0));
	State::update();
}
