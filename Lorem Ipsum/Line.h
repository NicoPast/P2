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
	void setFin(Vector2D fin) { fin_ = fin; calculateAngle(); }
	void setIniFin(Vector2D ini, Vector2D fin) { ini_ = ini; fin_ = fin; calculateAngle(); }
private:
	void calculateAngle();
	SDL_Color color_;
	Vector2D ini_;
	Vector2D fin_;
	int h_;					//Ancho de la línea		---   Si, se que estan invertidos
	int w_;					//Alto de línea			---   Si, se que estan invertidos
	double rot_;
	Texture* t_;
};