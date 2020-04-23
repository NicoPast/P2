#include "Bar.h"
#include "Tuner.h"

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
		if (!growing_) {
			percentage_ -= downSpeed_;
			if (percentage_ < 0)
				percentage_ = 0;
		}
		tr_->setH(-(percentage_ * pxPerPercent_));
		// si se pasa de la winZone, hace que aumente el estres
		if (!inDangerZone_) {
			if (percentage_ > maxWinPerc_) {
				inDangerZone_ = true;
				static_cast<Tuner*>(entity_->getState())->increaseStressSpeed(downSpeed_);
			}
		}
		else if (percentage_ < maxWinPerc_) {
			inDangerZone_ = false;
			static_cast<Tuner*>(entity_->getState())->increaseStressSpeed(-downSpeed_);
		}
	}
}
void Bar::grow() {
	growing_ = true;
	if (!isLocked_ && percentage_ < 100) {
		percentage_ += upSpeed_;
		if (percentage_ > 100)
			percentage_ = 100;
		tr_->setH(-(percentage_ * pxPerPercent_));
	}
}

bool Bar::isInWinningZone() {
	bool win = false;
	int height = growthTop_ + tr_->getH();
	if (percentage_ >= minWinPerc_ && percentage_ <= maxWinPerc_) win = true;
	return (win);
}