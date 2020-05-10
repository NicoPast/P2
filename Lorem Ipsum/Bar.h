#pragma once
#include "Manager.h"
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "ButtonOneParametter.h"
#include "Sprite.h"

class Bar : public Component
{
public:
	Bar(EntityManager* eM, double upSp = 5, double downSp = 1, double minWinPerc = 85, double maxWinPerc = 90) : 
		Component(ecs::Bar), entityManager_(eM), upSpeed_(upSp * 0.01), downSpeed_(downSp * 0.01), //hago el 0.1, porque se ejecutan 10 updates por segundo 
		minWinPerc_(minWinPerc), maxWinPerc_(maxWinPerc), 
		isLocked_(false), tr_(nullptr) {};
	~Bar() {}
	void update() override;
	void init() override;
	void setWinningRange(double min, double max) { minWinPerc_ = min; maxWinPerc_ = max; };
	void setLocked();
	void grow();
	void setGrowthTop(int g) { growthTop_ = g; pxPerPercent_ = growthTop_ / 100.0; }
	bool isInWinningZone();
	double getDownSpeed() { return downSpeed_; }
	inline void setLockActive(bool act) { lockEntity_->setActive(act); }
	inline void setGrowing(bool g) { growing_ = g; };
	tuple<double, double> getWinRange() { return { minWinPerc_, maxWinPerc_ }; };
private:
	Transform* tr_ = nullptr;
	double upSpeed_ = 0;
	double downSpeed_ = 0;
	int growthTop_ = 0;
	bool isLocked_ = false;
	EntityManager* entityManager_ = nullptr;
	Entity* lockEntity_ = nullptr;
	Sprite* lockSprite_ = nullptr;

	double pxPerPercent_ = 0;
	double percentage_ = 0;
	double minWinPerc_ = 0;
	double maxWinPerc_ = 0;
	// hace que solo sume el estres una vez
	bool inDangerZone_ = false; 
	bool growing_ = false;
	Uint32 lockDelay_ = 2000;
	Uint32 lockStarted_ = 0;

	Transform* lockProgress_ = nullptr;
	double percentageLock_ = 0;
	double pxPercLock_ = 0;
};

