#include "Line.h"
#include "LoremIpsum.h"
Line::Line(Vector2D ini, Vector2D fin, int w) : Line(ini, fin, w, { COLOR(0x00FF00FF) }) {

}
Line::Line(Vector2D ini, Vector2D fin, int w, SDL_Color c) : Component(ecs::Line), ini_(ini), fin_(fin), w_(w), color_(c){

}
void Line::init() {
	t_ = game_->getTextureMngr()->getTexture(Resources::Pixel);
	tr_ = GETCMP1_(Transform);
	double dgr = atan2(fin_.getY() - ini_.getY(), fin_.getX() - ini_.getX()) * 180 / M_PI;
	Vector2D newPos = Vector2D(cos(dgr) * ini_.getX(), sin(dgr) * ini_.getY());
	int w = sqrt(pow(fin_.getX() - ini_.getX(), 2) + pow(fin_.getY() - ini_.getY(), 2));
	t_->setPivotPoint({ 0, 0 });
	tr_->setPos(ini_);
	tr_->setRot(dgr);
	tr_->setW(w);
	tr_->setH(w_);
	cout << tr_->getRot() << endl;
	cout << tr_->getPos() << endl;
}
void Line::draw() {
	if (enabled_) {
		t_->setColorMod(color_.r, color_.g, color_.b);
		SDL_Rect dest = RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
		t_->render(dest, tr_->getRot());
	}
}