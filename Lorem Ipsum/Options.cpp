#include "Options.h"
#include "LoremIpsum.h"
#include "VolumeSlider.h"

Options::Options(LoremIpsum* game): State(game)
{
	init();
}

Options::~Options()
{
	ofstream config(game_->getConfigFileName());
	config << fullscreen << endl;
	config << game_->getGame()->getAudioMngr()->setMusicVolume(-1) << endl;
	config << game_->getGame()->getAudioMngr()->setChannelVolume(-1) << endl;
	config.close();
}

void Options::init()
{
	SDLGame* game = game_->getGame();
	//setters de la cámara
	camera_->setPos(0, 0);
	camera_->setWidth(1080); camera_->setHeight(720);
	camera_->setLeftMargin(0); camera_->setRightMargin(0);
	Texture* backgroundTex = game->getTextureMngr()->getTexture(Resources::OptionsUIBG);
	camera_->setLimitX(backgroundTex->getWidth());
	camera_->setLimitY(backgroundTex->getHeight());

	fullscreen = game->isFullScreen();

	//fondo
	Entity* background = entityManager_->addEntity(0);
	background->addComponent<Transform>(0, 0, game->getWindowWidth(), game->getWindowHeight());
	background->addComponent<Sprite>(backgroundTex);
	//background->addComponent<Animator<int*>>()->changeAnim(Resources::MainMenuAnim);
	//titulito que se puede quitar
	//Entity* title = entityManager_->addEntity(1);
	//string titleStr = "Opciones";
	//Transform* titleTr = title->addComponent<Transform>(game->getWindowWidth() / 2, 100, 250, 150);
	//Text* tx = title->addComponent<Text>(titleStr, titleTr->getPos(), titleStr.size() * 24, Resources::RobotoTest24, 0);tx->setColor(210, 145, 52);
	//tx->setPos(tx->getPos() - Vector2D(titleStr.size() / 2 * tx->getCharW(),0));
	auto mngr = SDLGame::instance()->getTextureMngr();
	int iconW = mngr->getTexture(Resources::OptionsUISoundIcon)->getWidth() / 2;
	int iconH = mngr->getTexture(Resources::OptionsUISoundIcon)->getHeight() / 2;
	//Barras para musica y sonidos varios
	createBar(640 - 175, 300, 350, 50, 0, "Music or musica", Resources::TextureID::OptionsUISoundIcon, {0,0,iconW,iconH});
	createBar(640 - 175, 400, 350, 50, 1, "Other u otros", Resources::TextureID::OptionsUISoundIcon,   { 0,iconH,iconW,iconH });

	//boton para el full Screen
	Entity* fullScreen = entityManager_->addEntity(1);
	int butW = mngr->getTexture(Resources::OptionsUIButton)->getWidth();
	int butH = mngr->getTexture(Resources::OptionsUIButton)->getHeight();
	fullScreen->addComponent<Transform>(game->getWindowWidth()/2-50,550, 100, 100);
	Sprite* s = fullScreen->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::OptionsUIButton));
	if (fullScreen) {
		s->setSourceRect({ 0,butH / 2, butW, butH / 2 });
	}
	else {
		s->setSourceRect({ 0, 0, butW, butH / 2 });;
	}
	Options* p = this;
	fullScreen->addComponent<ButtonOneParametter<SDLGame*>>(std::function<void(SDLGame*)>([butW, butH, p, fullScreen](SDLGame* b)
		{
			b->toggleFullScreen();
			p->fullscreen = !p->fullscreen;
			int y;
			if (p->fullscreen)
				y = butH / 2;
			else y = 0;
			fullScreen->getComponent<Sprite>(ecs::Sprite)->setSourceRect({0, y, butW, butH / 2});
		}), game);
}

void Options::createBar(int x, int y, int w, int h, int channel, string text, Resources::TextureID icon, SDL_Rect clip)
{

	Texture* bar = game_->getGame()->getTextureMngr()->getTexture(Resources::OptionsUISlider);
	int barWidth = bar->getWidth();
	int barHeight = bar->getHeight();

	Entity* musicBar = entityManager_->addEntity(1);
	Transform* musicBarTr = musicBar->addComponent<Transform>(x, y, w, h);
	auto mngr = SDLGame::instance()->getTextureMngr();
	musicBar->addComponent<Sprite>(bar);// ->setSourceRect({ 0, 0, barWidth, barHeight / 2 });

	Entity* slidingPart = entityManager_->addEntity(4);
	Transform* slidingTr = slidingPart->addComponent<Transform>(x + w / 2, y + h / 2 - 5, 10, 30);
	//sfxIcon->addComponent<Sprite>(mngr->getTexture(Resources::OptionsUISoundIcon))->setSourceRect({ 0,iconH,iconW,iconH });
	//slidingPart->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::OptionsUISlider));
	slidingPart->addComponent<Rectangle>(SDL_Color{ COLOR(0x966a2bff) })->setBorder(SDL_Color{ COLOR(0x734f2cff) });
	slidingPart->addComponent<VolumeSlider>(slidingTr, channel, true, musicBarTr->getPos().getX(), musicBarTr->getPos().getX() + musicBarTr->getW());

	int iconW = mngr->getTexture(Resources::OptionsUISoundIcon)->getWidth()/2;
	int iconH = mngr->getTexture(Resources::OptionsUISoundIcon)->getHeight()/2;
	Entity* musicIcon = entityManager_->addEntity(1);
	musicIcon->addComponent<Transform>(x - iconW*1.5, y+h/2-iconH/2, iconW, iconW);
	musicIcon->addComponent<Sprite>(mngr->getTexture(icon))->setSourceRect(clip);
	SDL_Rect r=clip;
	/*musicIcon->addComponent<ButtonOneParametter<int*>>([slidingPart,musicIcon, r,channel,iconW](int* e)
		{
			SDL_Rect rect = r;
			if (channel != 0)
			{
				if (SDLGame::instance()->getAudioMngr()->setChannelVolume(channel, -1) == 0)
				{
					SDLGame::instance()->getAudioMngr()->setChannelVolume(channel,slidingPart->getComponent<VolumeSlider>(ecs::VolumeSlider)->prevVal);
					rect.x = 0;
				}
				else
				{
					slidingPart->getComponent<VolumeSlider>(ecs::VolumeSlider)->prevVal = SDLGame::instance()->getAudioMngr()->setChannelVolume(channel, -1);
					SDLGame::instance()->getAudioMngr()->setChannelVolume(channel, 0);
					rect.x = iconW;
				}
			}
			else
			{
				if (SDLGame::instance()->getAudioMngr()->setMusicVolume(-1) == 0)
				{
					SDLGame::instance()->getAudioMngr()->setMusicVolume(slidingPart->getComponent<VolumeSlider>(ecs::VolumeSlider)->prevVal);
					rect.x = 0;
				}
				else {
					slidingPart->getComponent<VolumeSlider>(ecs::VolumeSlider)->prevVal = SDLGame::instance()->getAudioMngr()->setMusicVolume( -1);
					SDLGame::instance()->getAudioMngr()->setMusicVolume(0);
					rect.x = iconW;
				}
			}


			GETCMP2(musicIcon, Sprite)->setSourceRect(rect);
		}, nullptr);*/
	//musicBar->addComponent<Text>(text, musicBarTr->getPos() - Vector2D(350, h / 24), text.size() * 24, Resources::RobotoTest24, 0);
	
	//Entity* musicBorder = entityManager_->addEntity(3);
	//Transform* musicBorderTr = musicBorder->addComponent<Transform>(x, y, w, h);
	//musicBorder->addComponent<Sprite>(bar)->setSourceRect({ 0, barHeight / 2, barWidth, barHeight / 2 });
	


}