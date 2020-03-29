#pragma once
#include <vector>
#include "Transform.h"
#include "ecs.h"

class Scroller : public Component
{
public:
	Scroller() :Component(ecs::Scroller) {}
	virtual ~Scroller() {}

	//Mueve todos los objetos de la escena en una direccion (positivo a la derecha, negativo a la izquierda)
	virtual void scroll(int speed);
	virtual void stopScrolling() { scroll(0); }

	//Agrega un transform a la lista de objetos que se mueven con el fondo, se llama varias veces al entrar a una escena nueva
	virtual void addItem(Transform* item) { items_.push_back(item); }

	//Limpia la lista de objetos, se llama al cambiar de escena
	virtual void clear(Transform* item) { items_.clear(); }

	//Elimina un objeto en concreto, se llama si desaparece una pista/persona dentro de una escena (no es seguro de que sea 100% necesario)
	virtual void removeItem(Transform* item) { items_.erase(std::find(items_.begin(), items_.end(), item)); }

	virtual void update();
protected:
	//Vector de objetos de fondo, que se mueven junto a este
	vector<Transform*> items_;
	int scrollSpeed = 15;
};

