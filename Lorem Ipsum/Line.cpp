#include "Line.h"
#include "LoremIpsum.h"
Line::Line(Vector2D ini, Vector2D fin, int w) : Line(ini, fin, w, { COLOR(0x00FF00FF) }) {

}
Line::Line(Vector2D ini, Vector2D fin, int w, SDL_Color c) : Component(ecs::Line), ini_(ini), fin_(fin), h_(w), color_(c){

}
void Line::init() {
	t_ = game_->getTextureMngr()->getTexture(Resources::Pixel);
	t_->setPivotPoint({ 0, 0 });
}
void Line::draw() {
	if (enabled_) {
		t_->setColorMod(color_.r, color_.g, color_.b);
		SDL_Rect dest = RECT(ini_.getX(), ini_.getY(), w_, h_);
		t_->render(dest, rot_);
	}
}
//Hace trigonometría para calcular la línea
void Line::calculateAngle() {
	rot_ = atan2(fin_.getY() - ini_.getY(), fin_.getX() - ini_.getX()) * 180 / M_PI;
	w_ = sqrt(pow(fin_.getX() - ini_.getX(), 2) + pow(fin_.getY() - ini_.getY(), 2));
}