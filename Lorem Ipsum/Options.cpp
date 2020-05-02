#include "Options.h"
#include "LoremIpsum.h"

Options::Options(LoremIpsum* game): State(game)
{
	init();
}

void Options::init()
{
	SDLGame* game = game_->getGame();
	//setters de la cámara
	camera_->setPos(0, 0);
	camera_->setWidth(1080); camera_->setHeight(720);
	camera_->setLeftMargin(0); camera_->setRightMargin(0);
	Texture* backgroundTex = game->getTextureMngr()->getTexture(Resources::MainMenuBG);
	camera_->setLimitX(backgroundTex->getWidth());
	camera_->setLimitY(backgroundTex->getHeight());

	//fondo
	Entity* background = entityManager_->addEntity(0);
	background->addComponent<Transform>(0, 0, game->getWindowWidth(), game->getWindowHeight());
	background->addComponent<Sprite>(backgroundTex);
	
	//titulito que se puede quitar
	Entity* title = entityManager_->addEntity(1);
	Transform* titleTr = title->addComponent<Transform>(game->getWindowWidth() / 2 - 150, 100, 250, 150);
	string titleStr = "Options u opciones";
	title->addComponent<Text>(titleStr, titleTr->getPos(), titleStr.size() * 100, Resources::RobotoTest24, 0);

	//Barras para musica y sonidos varios
	createBar(400, 100, 350, 50);
	createBar(400, 200, 350, 50);
}

void Options::createBar(int x, int y, int w, int h)
{

	Texture* bar = game_->getGame()->getTextureMngr()->getTexture(Resources::Bars);
	int barWidth = bar->getWidth();
	int barHeight = bar->getHeight();

	Entity* musicBar = entityManager_->addEntity(1);
	Transform* musicBarTr = musicBar->addComponent<Transform>(x, y, h, w);
	musicBar->addComponent<Sprite>(bar)->setSourceRect({ 0, 0, barWidth / 2, barHeight });
	musicBarTr->setRot(90);

	Entity* musicBorder = entityManager_->addEntity(3);
	Transform* musicBorderTr = musicBorder->addComponent<Transform>(x, y, h, w);
	musicBorder->addComponent<Sprite>(bar)->setSourceRect({ barWidth / 2, 0, barWidth / 2, barHeight });
	musicBorderTr->setRot(90);
	/*
	Entity* slider = entityManager_->addEntity(3);
	Transform* sliderTr = slider->addComponent<Transform>(0, 0, 10, 10, musicBarTr);
	slider->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::Pixel));
	sliderTr->setPosX(barWidth / 2);
	sliderTr->setPosY(barHeight / 2);
	/**/
}