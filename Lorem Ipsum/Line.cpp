#include "Line.h"
Line::Line(Vector2D ini, Vector2D fin, int w) : Line(ini, fin, w, { COLOR(0x00FF00FF) }) {

}
Line::Line(Vector2D ini, Vector2D fin, int w, SDL_Color c) : Component(ecs::Line), ini_(ini), fin_(fin), w_(w), color_(c){

}
void Line::init() {

}
void Line::draw() {
	if (enabled_) {
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
		SDL_RenderDrawLine(game_->getRenderer(), ini_.getX(), ini_.getY(), fin_.getX(), fin_.getY());
		for (int i = 1; i < w_ / 2 + 1; i++) {
			SDL_RenderDrawLine(game_->getRenderer(), ini_.getX() - i, ini_.getY() - i, fin_.getX() - i, fin_.getY() - i);
			SDL_RenderDrawLine(game_->getRenderer(), ini_.getX() + i, ini_.getY() + i, fin_.getX() + i, fin_.getY() + i);
		}
	}
}