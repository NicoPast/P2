#include "Bar.h"

void Bar::init()
{
	tr_ = GETCMP1_(Transform);
	int lockY = tr_->getPos().getY() + tr_->getH() + 20;
	lockEntity_ = entityManager_->addEntity(3);
	lockEntity_->addComponent<Transform>(tr_->getPos().getX(), lockY, tr_->getW(), tr_->getW());
	lockEntity_->addComponent<Rectangle>(SDL_Color{COLOR(0x0000ff00)});
	lockEntity_->addComponent<ButtonOneParametter<Bar*>>(std::function<void(Bar*)>([](Bar* b) {b->setLocked(); }), this);
	lockEntity_->setActive(false);
}
void Bar::update()
{
	if (!isLocked_ && percentage_ > 0) {
		percentage_ -= downSpeed_;
		if (percentage_ < 0)
			percentage_ = 0;
		tr_->setH(-(percentage_ * pxPerPercent_));
	}
	if (tr_->getH() < winningZone_->getPos().getY()) {
		//llama al Tuner para que aumente el valor de estrés
	}
}
void Bar::grow() {

	if (!isLocked_ && percentage_ < 100) {
		percentage_ += upSpeed_;
		if (percentage_ > 100)
			percentage_ = 100;
		tr_->setH(-(percentage_ * pxPerPercent_));
		//if (abs(tr_->getH()) > abs(growthTop_)) tr_->setH(-growthTop_);
	}
}

bool Bar::isInWinningZone() {
	bool win = false;
	int height = growthTop_ + tr_->getH();
	if (percentage_ >= minWinPerc_ && percentage_ <= maxWinPerc_) win = true;
	//if (tr_->getH() > winningZone_->getPos().getY() && tr_->getH() < winningZone_->getPos().getY() + winningZone_->getH()) win = true;
	return (win);
}