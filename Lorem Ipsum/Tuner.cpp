#include "Tuner.h"

Tuner::Tuner(LoremIpsum* game) : State(game)
{
	stress_ = 0;
	maxStress_ = 90;
	//delay = 3000;

	setBars(); //Pilla el array de entidades de las barras
	createStressMeter(); //crea los visualizadores del estres

	//la velocidad de subida del estrés será una media de todas las velocidades de bajada de las barras
	double auxStress = 0;
	for (int i = 0; i < bars_.size(); i++) {
		Bar* bar = GETCMP2(bars_[i], Bar);
		auxStress += bar->getDownSpeed();
	}
	stressSpeed_ = auxStress / bars_.size();
}

void Tuner::update()
{
	State::update();
	InputHandler* ih = InputHandler::instance();
	int time = game_->getGame()->getTime();
	bool won = true;

	for (int i = 0; i < bars_.size(); i++) {
		Bar* bar = GETCMP2(bars_[i], Bar);
		if (!(bar->isInWinningZone()))
			won = false;
		if (direction_ == 1 && ih->isKeyDown(SDLK_SPACE))
			bar->grow();
		else bar->setGrowing(false);
	}
	if (won) {
		cout << "gane " << ++numVictorias << " veces al fantasma" << endl;
	}
	else {
		stress_ += stressSpeed_ * direction_;
		if (direction_ == -1 && stress_ <= 0) {
			stress_ = 0;
			direction_ = 1;
		}
		else if (stress_ > maxStress_) {
			stress_ = 0;
			cout << "perdi " << ++numDerrotas << " veces contra el fantasma" << endl;
		}
		angle_ = stress_ * 3.6;
		stresTr_->setPos({ stressCenter_.getX() + (cos((angle_ - 90) * (3.1415 / 180.0)) * radius_), stressCenter_.getY() + (sin((angle_ - 90) * (3.1415 / 180.0)) * radius_) });
		stresTr_->setRot(angle_ - 90);
	}
}

void Tuner::render()
{
	State::render();
}

void Tuner::setBars() {
	bars_ = game_->getStoryManager()->createBars(entityManager_);
	
	int contY = game_->getGame()->getWindowHeight() / 5;
	int pxPercent = (contY * 3) / 100;
	//double minWinPerc = 85;
	//double maxWinPerc = 95;

	for (int i = 0; i < bars_.size(); i++) {
		Bar* b = GETCMP2(bars_[i], Bar);

		Entity* cont = entityManager_->addEntity(2);
		Transform* barT = GETCMP2(bars_[i], Transform);
		Transform* contT = cont->addComponent<Transform>(barT->getPos().getX(), contY, barT->getW(), contY * 3);
		cont->addComponent<Rectangle>(SDL_Color{ COLOR(0xff000000) });

		
		Entity* wzone = entityManager_->addEntity(2);
		tuple<double, double> wRange = b->getWinRange();
		wzone->addComponent<Transform>(barT->getPos().getX(), contY + (100 - get<1>(wRange)) * pxPercent, barT->getW(), (get<1>(wRange) - get<0>(wRange)) * pxPercent);
		Transform* wtr = GETCMP2(wzone, Transform);
		wzone->addComponent<Rectangle>(SDL_Color{ COLOR(0x32CD3200) });
		
		b->setLockActive(true);
		b->setGrowthTop(contT->getH());
		bars_[i]->setActive(true);
	}
}

void Tuner::createStressMeter() {
	stressCenter_ = { game_->getGame()->getWindowWidth() * 3.0 / 4.0, game_->getGame()->getWindowHeight() / 2.0 - 60 };
	// 30 es el ancho del cuadrado que gira
	radius_ = game_->getGame()->getWindowWidth() / 4.0 - (2 * 30);

	Entity* stresser = entityManager_->addEntity(3);
	stresTr_ = stresser->addComponent<Transform>(stressCenter_.getX() + (cos(angle_ - 90) * radius_), stressCenter_.getY() + (sin(angle_ - 90) * radius_), 30, 30);
	stresser->addComponent<Rectangle>(SDL_Color{ COLOR(0x32CD3200) });
	stresTr_->setRot(angle_ - 90);

	Entity* stressLimit = entityManager_->addEntity(3);
	// usa radianes en vez de angulos
	Transform* strLimTr = stressLimit->addComponent<Transform>(stressCenter_.getX() + (cos((maxStress_ * 3.6 - 90) * (3.1415 / 180.0)) * radius_), stressCenter_.getY() + (sin((maxStress_ * 3.6 - 90) * (3.1415 / 180.0))* radius_), 30, 30);
	stressLimit->addComponent<Rectangle>(SDL_Color{ COLOR(0xff000000) });
	strLimTr->setRot(maxStress_ * 3.6 - 90);

	Entity* stressWarning = entityManager_->addEntity(3);
	// usa radianes en vez de angulos
	Transform* strWarTr = stressWarning->addComponent<Transform>(stressCenter_.getX() + (cos(((maxStress_ - 10) * 3.6 - 90) * (3.1415 / 180.0)) * radius_), stressCenter_.getY() + (sin(((maxStress_ - 10) * 3.6 - 90) * (3.1415 / 180.0)) * radius_), 30, 10);
	stressWarning->addComponent<Rectangle>(SDL_Color{ COLOR(0xff00ff00) });
	strWarTr->setRot((maxStress_ - 10) * 3.6 - 90);

	Entity* calmStress = entityManager_->addEntity(3);
	Transform* calmStrTr = calmStress->addComponent<Transform>(stressCenter_.getX(), game_->getGame()->getWindowHeight()/5.0 * 4 + 20, 30, 30);
	calmStress->addComponent<Rectangle>(SDL_Color{ COLOR(0x0000ff00) });
	//lockEntity_->addComponent<ButtonOneParametter<Bar*>>(std::function<void(Bar*)>([](Bar* b) {b->setLocked(); }), this);
	calmStress->addComponent<ButtonOneParametter<Tuner*>>(std::function<void(Tuner*)>([](Tuner* t) { t->changeStressDir(-1); }), this);
}
