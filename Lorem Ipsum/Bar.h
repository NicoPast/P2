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
	Bar(EntityManager* eM, double upSp = 5, double downSp = 1, double minWinPerc = 85, double maxWinPerc = 90) : 
		Component(ecs::Bar), entityManager_(eM), upSpeed_(upSp * 0.1), downSpeed_(downSp * 0.1), //hago el 0.1, porque se ejecutan 10 updates por segundo 
		minWinPerc_(minWinPerc), maxWinPerc_(maxWinPerc), 
		isLocked_(false), tr_(nullptr) {};
	~Bar() {}
	void update() override;
	void init() override;
	void setWinningRange(double min, double max) { minWinPerc_ = min; maxWinPerc_ = max; };
	void setLocked() { isLocked_ = !isLocked_; }
	void grow();
	void setGrowthTop(int g) { growthTop_ = g; pxPerPercent_ = growthTop_ / 100.0; }
	bool isInWinningZone();
	double getDownSpeed() { return downSpeed_; }
	inline void setLockActive(bool act) { lockEntity_->setActive(act); }
	inline void setGrowing(bool g) { growing_ = g; };
	tuple<double, double> getWinRange() { return { minWinPerc_, maxWinPerc_ }; };
private:
	Transform* tr_;
	double upSpeed_;
	double downSpeed_;
	int growthTop_;
	bool isLocked_;
	EntityManager* entityManager_;
	Entity* lockEntity_ = nullptr;

	double pxPerPercent_ = 0;
	double percentage_ = 0;
	double minWinPerc_;
	double maxWinPerc_;
	// hace que solo sume el estres una vez
	bool inDangerZone_ = false; 
	bool growing_ = false;
};

