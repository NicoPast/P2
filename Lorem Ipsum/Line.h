#pragma once
#include <SDL_rect.h>
#include "Component.h"
#include "SDL_macros.h"
#include "Transform.h"
class LoremIpsum;
class Line : public Component {
public:
	Line(Vector2D ini, Vector2D fin, int w);
	Line(Vector2D ini, Vector2D fin, int w, SDL_Color c);
	virtual ~Line() {};
	void init();
	void draw();
private:
	SDL_Color color_;
	Vector2D ini_;
	Vector2D fin_;
	int w_;					//Ancho de la línea
	Texture* t_;
	Transform* tr_;
};