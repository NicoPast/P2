#pragma once
#include <vector>
#include "Transform.h"
#include "ecs.h"

class ScrollerLimited : public Component
{
public:
	ScrollerLimited(): Component(ecs::ScrollerLimited) {
		maxX_ = SDLGame::instance()->getWindowWidth();
		minX_ = 0;
	}
	ScrollerLimited(int minX, int maxX, int offset = 50): Component(ecs::ScrollerLimited), minX_(minX + offset), maxX_(maxX - offset) {}
	virtual ~ScrollerLimited() {}
	//Agrega un transform a la lista de objetos que se mueven con el fondo, se llama varias veces al entrar a una escena nueva
	void addItem(Transform* item) { items_.push_back(item); }
	void addItem(Transform* item, int pos);

	//Limpia la lista de objetos, se llama al cambiar de escena
	void clear(Transform* item) { items_.clear(); }

	//Elimina un objeto en concreto, se llama si desaparece una pista/persona dentro de una escena
	void removeItem(Transform* item, int pos) { items_.erase(std::find(items_.begin(), items_.end(), item)); pos_.erase(std::find(pos_.begin(), pos_.end(), pos)); }

	//Igual que Scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	void scroll(int speed);

	//Igual que Scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	void scrollLimited(int speed);

	void stopScrolling();
	virtual void update();
private:
	int maxX_ = 0;
	int minX_ = 0;
	//Vector de objetos de fondo, que se mueven junto a este
	vector<Transform*> items_;
	vector<int> pos_;
	int scrollSpeed = 6;
};