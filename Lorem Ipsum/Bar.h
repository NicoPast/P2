#pragma once
#include "Manager.h"
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "ButtonOneParametter.h"

class Bar : public Component
{
public:
	Bar(EntityManager* eM, double upSp = 5, double downSp = 1) : Component(ecs::Bar), entityManager_(eM),upSpeed_(upSp), downSpeed_(downSp), isLocked_(false), tr_(nullptr), winningZone_(nullptr){};
	~Bar();
	void update();
	void init();
	void setWinningZone(Transform* tr) { winningZone_ = tr; }
	void setLocked() { isLocked_ = !isLocked_; }
	void grow();
	bool isInWinningZone();
	double getDownSpeed() { return downSpeed_; }
	void setLockActive(bool act) { lockEntity_->setActive(act); }
private:
	Transform* tr_;
	double upSpeed_;
	double downSpeed_;
	bool isLocked_;
	Transform* winningZone_;
	EntityManager* entityManager_;
	Entity* lockEntity_ = nullptr;
};

