#include "Options.h"
#include "LoremIpsum.h"
#include "VolumeSlider.h"

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
	title->addComponent<Text>(titleStr, titleTr->getPos(), titleStr.size() * 24, Resources::RobotoTest24, 0);

	//Barras para musica y sonidos varios
	createBar(400, 300, 350, 50, 0, "Music or musica");
	createBar(400, 400, 350, 50, 1, "Other u otros");

	//boton para el full Screen
	Entity* fullScreen = entityManager_->addEntity(1);
	fullScreen->addComponent<Transform>(500, 600, 100, 100);
	fullScreen->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::Pixel));
	fullScreen->addComponent<ButtonOneParametter<SDLGame*>>(std::function<void(SDLGame*)>([](SDLGame* b) { b->toggleFullScreen(); }), game);
}

void Options::createBar(int x, int y, int w, int h, int channel, string text)
{

	Texture* bar = game_->getGame()->getTextureMngr()->getTexture(Resources::OptionBars);
	int barWidth = bar->getWidth();
	int barHeight = bar->getHeight();

	Entity* musicBar = entityManager_->addEntity(1);
	Transform* musicBarTr = musicBar->addComponent<Transform>(x, y, w, h);
	musicBar->addComponent<Sprite>(bar)->setSourceRect({ 0, 0, barWidth, barHeight / 2 });
	musicBar->addComponent<Text>(text, musicBarTr->getPos() - Vector2D(350, h / 24), text.size() * 24, Resources::RobotoTest24, 0);
	
	Entity* musicBorder = entityManager_->addEntity(3);
	Transform* musicBorderTr = musicBorder->addComponent<Transform>(x, y, w, h);
	musicBorder->addComponent<Sprite>(bar)->setSourceRect({ 0, barHeight / 2, barWidth, barHeight / 2 });
	
	Entity* slidingPart = entityManager_->addEntity(4);
	Transform* slidingTr = slidingPart->addComponent<Transform>(x + w / 2, y + h / 2, 30, 10);
	slidingPart->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::Pixel));
	slidingPart->addComponent<VolumeSlider>(slidingTr, channel, true, musicBarTr->getPos().getX(), musicBarTr->getPos().getX() + musicBarTr->getW());

}