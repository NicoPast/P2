#pragma once

#include "Vector2D.h"
#include "Component.h"

class Transform : public Component {
public:
	Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation, Transform* parent = nullptr);
	Transform(double x, double y, double width, double height, Transform* parent = nullptr);
	Transform();
	virtual ~Transform();

	// position
	const Vector2D& getPos() const {
		return position_;
	}
	void setPos(const Vector2D& pos) {
		setPosX(pos.getX());
		setPosY(pos.getY());
	}
	void setPos(double x, double y) {
		setPos(Vector2D( x, y ));
	}
	void setPosX(double x) {
		Vector2D prevPos = position_;
		if (parent_ != nullptr) {
			position_.setX(parent_->getPos().getX() + x);
		}
		else position_.setX(x);
		relocateChildren(prevPos);
	}
	void setPosY(double y) {
		Vector2D prevPos = position_;
		if (parent_ != nullptr) {
			position_.setY(parent_->getPos().getY() + y);
		}
		else position_.setY(y);
		relocateChildren(prevPos);
	}
	void addToPosX(double x) {
		setPosX(position_.getX() + x);
	}

	// rotation
	double getRot() const {
		return rotation_;
	}
	void setRot(double angle) {
		if (parent_ != nullptr) {
			rotation_ = parent_->getRot() + angle;
		}
		else rotation_ = angle;
	}

	// velocity
	const Vector2D& getVel() const {
		return velocity_;
	}
	void setVel(const Vector2D& vel) {
		velocity_.set(vel);
	}
	void setVel(double x, double y) {
		velocity_.set(x, y);
	}
	void setVelX(double x) {
		velocity_.setX(x);
	}
	void setVelY(double y) {
		velocity_.setY(y);
	}

	// width && height
	double getW() const {
		return width_;
	}
	void setW(double width) {
		width_ = width;
	}

	double getH() const {
		return height_;
	}
	void setH(double height) {
		height_ = height;
	}

	void setWH(double width, double height) {
		width_ = width;
		height_ = height;
	}

	vector<Transform*>& getChildren() {
		return children_;
	}

	Transform* getParent() {
		return parent_;
	}

	void setParent(Transform* parent) {
		if(parent_ != nullptr)
			parent_->removeChild(this);
		parent_ = parent;
		parent->addChildren(this);
	}

	void setActiveChildren(bool b);
private:
	void addChildren(Transform* child) {
		assert(child != nullptr && child != this); // se asegura que no es el mismo
		children_.push_back(child);
	}

	void removeChild(Transform* child) {
		int i = 0;
		while (i < children_.size() && child != children_[i]) {
			i++;
		}
		if (i < children_.size()) {
			children_[i] = children_[children_.size() - 1];
			children_.pop_back();
		}
	}

	void relocateChildren(Vector2D previousPos) {
		for (Transform* t : children_) {
			t->setPos(t->getPos() - previousPos);
		}
	}

	Transform* parent_ = nullptr;
	vector<Transform*> children_;

	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;
};

