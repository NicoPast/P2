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
	ScrollerLimited(int minX, int maxX): Component(ecs::ScrollerLimited), maxX_(maxX), minX_(minX) {}
	virtual ~ScrollerLimited() {}
	//Agrega un transform a la lista de objetos que se mueven con el fondo, se llama varias veces al entrar a una escena nueva
	void addItem(Transform* item) { items_.push_back(item); }

	//Limpia la lista de objetos, se llama al cambiar de escena
	void clear(Transform* item) { items_.clear(); }

	//Elimina un objeto en concreto, se llama si desaparece una pista/persona dentro de una escena
	void removeItem(Transform* item) { items_.erase(std::find(items_.begin(), items_.end(), item)); }

	//Igual que Scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	void scroll(int speed);

	//Igual que Scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	void scrollLimited(int speed);

	void stopScrolling();
	virtual void update();
private:
	int maxX_;
	int minX_;

	//Vector de objetos de fondo, que se mueven junto a este
	vector<Transform*> items_;
	Transform* player_;
	int scrollSpeed = 2.5;
};