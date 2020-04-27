#include "Bar.h"
#include "Tuner.h"

void Bar::init()
{
	tr_ = GETCMP1_(Transform);
	int lockY = tr_->getPos().getY() + tr_->getH() + 20;
	lockEntity_ = entityManager_->addEntity(3);
	lockEntity_->addComponent<Transform>(tr_->getPos().getX(), lockY, tr_->getW(), tr_->getW());
	Texture* temp = game_->getTextureMngr()->getTexture(Resources::Lock);
 	lockSprite_ = lockEntity_->addComponent<Sprite>(temp);
	lockSprite_->setSourceRect({ temp->getWidth() / 2, 0, temp->getWidth() / 2, temp->getHeight() });
	lockEntity_->addComponent<ButtonOneParametter<Bar*>>(std::function<void(Bar*)>([](Bar* b) {b->setLocked(); }), this);

	Entity* lockBar = entityManager_->addEntity(3);
	lockProgress_ = lockBar->addComponent<Transform>(tr_->getPos().getX(), lockY + tr_->getW() + 5, 0, 10);
	lockBar->addComponent<Rectangle>(SDL_Color{ COLOR(0x0000ffff) });

	pxPercLock_ = tr_->getW() / 100.0;

}
void Bar::update()
{
	if (!isLocked_ && percentage_ >= 0) {
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
	else {
		Uint32 time = ((double)(game_->getTime() - lockStarted_) / (double)lockDelay_) * 100;
		lockProgress_->setW(tr_->getW() - (time * pxPercLock_));
		if (time > 100) {
			setLocked();
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

void Bar::setLocked() {
	isLocked_ = !isLocked_;
	Texture* temp = game_->getTextureMngr()->getTexture(Resources::Lock);
	if (isLocked_)
	{
		lockSprite_->setSourceRect({ 0, 0, temp->getWidth() / 2, temp->getHeight() });
		lockStarted_ = game_->getTime();
	}
	else {
		lockSprite_->setSourceRect({ temp->getWidth() / 2, 0, temp->getWidth() / 2, temp->getHeight() });
	}
}