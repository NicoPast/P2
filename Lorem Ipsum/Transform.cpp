#include "Transform.h"
#include "Entity.h"
#include "StoryManager.h"
Transform::Transform() :
	Component(ecs::Transform), position_(), //
	velocity_(), //
	width_(), //
	height_(), //
	rotation_() //
{
};


Transform::Transform(Vector2D pos, Vector2D vel, double width,
		double height, double rotation, Transform* parent) :
		Component(ecs::Transform), position_(pos), //
		velocity_(vel), //
		width_(width), //
		height_(height), //
		rotation_(0.0), //
		parent_(parent) //
{
}

Transform::Transform(double x, double y, double width, double height, Transform* parent) :
	Component(ecs::Transform),
	position_({ x, y }),
	velocity_({ 0.0, 0.0 }),
	width_(width),
	height_(height),
	rotation_(0.0),
	parent_(parent)
{
}

Transform::~Transform() {
}
#ifdef _DEBUG
void Transform::draw()
{
	if (!StoryManager::instance()->showingHitbox_)return;
	SDL_SetRenderDrawColor(game_->getRenderer(), 255, 255, 0, 255);
	SDL_Rect r{ position_.getX(),position_.getY(),width_, height_ };
	SDL_RenderDrawRect(game_->getRenderer(), &r);
}
#endif // _DEBUG

void Transform::setPos(double x, double y)
{
	setPos(Vector2D(x, y));
	if (entity_->hasComponent(ecs::Text))GETCMP1_(Text)->setPos(Vector2D(x, y));
}
void Transform::setActiveChildren(bool b) {
	for (auto tr : children_) {
		tr->getEntity()->setActive(b);
	}
}

void Transform::setPos(const Vector2D& pos)
{
	setPosX(pos.getX());
	setPosY(pos.getY());

}