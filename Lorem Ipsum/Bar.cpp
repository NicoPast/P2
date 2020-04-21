#include "Bar.h"

void Bar::init()
{
	tr_ = GETCMP1_(Transform);
	int lockY = tr_->getPos().getY() + tr_->getH() + 20;
	lockEntity_ = entityManager_->addEntity(3);
	lockEntity_->addComponent<Transform>(tr_->getPos().getX(), lockY, tr_->getW(), tr_->getW());
	lockEntity_->addComponent<Rectangle>(SDL_Color{COLOR(0xff00ff00)});
	lockEntity_->addComponent<ButtonOneParametter<Bar*>>(std::function<void(Bar*)>([](Bar* b) {b->setLocked(); }), this);
	lockEntity_->setActive(false);

}
void Bar::update()
{
	if (!isLocked_) {
		tr_->setH(tr_->getH() + downSpeed_);
	}
	if (tr_->getH() < winningZone_->getPos().getY()) {
		//llama al Tuner para que aumente el valor de estrés
	}
}
void Bar::grow() {

	if (!isLocked_) {
		tr_->setH(tr_->getH() - upSpeed_);
	}
}

bool Bar::isInWinningZone() {
	bool win = false;
	if (tr_->getH() > winningZone_->getPos().getY() && tr_->getH() < winningZone_->getPos().getY() + winningZone_->getH()) win = true;
	return (win);
}



