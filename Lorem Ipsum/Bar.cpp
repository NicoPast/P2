#include "Bar.h"
#include "Entity.h"
#include "Rectangle.h"
#include "ButtonOneParametter.h"
void Bar::init()
{
	tr_ = GETCMP1_(Transform);
	int lockY = tr_->getPos().getY() + tr_->getH() + 20;
	Entity* lockEntity = entityManager_->addEntity(3);
	lockEntity->addComponent<Transform*>(tr_->getPos().getX(), lockY, tr_->getW(), tr_->getW());
	lockEntity->addComponent<Rectangle*>(SDL_Color{COLOR(0xff00ff00)});
	lockEntity->addComponent<ButtonOneParametter<Bar*>>(std::function<void(Bar*)>([](Bar* b) {b->setLocked(); }), this);

}
void Bar::update()
{
	if (!isLocked_) tr_->setH(tr_->getH() + downSpeed_);
	if (tr_->getH() < winningZone_->getPos().getY()) {
		//llama al Tuner para que aumente el valor de estrés
	}
}
void Bar::grow() {

	if (!isLocked_) {
		tr_->setH(tr_->getH() - upSpeed_);
	}
}


