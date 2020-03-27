#pragma once
#include <vector>
#include "Transform.h"
#include "ecs.h"

class Scroller : public Component
{
public:
	Scroller():Component(ecs::Scroller) {}
	virtual ~Scroller() {}
	//Mueve todos los objetos de la escena en una direccion (positivo a la derecha, negativo a la izquierda)
	void scroll(int distance);
	//Igual que scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	void scrollLimited(int distance);
	//Agrega un transform a la lista de objetos que se mueven con el fondo, se llama varias veces al entrar a una escena nueva
	void addItem(Transform* item) { items_.push_back(item); }
	//Limpia la lista de objetos, se llama al cambiar de escena
	void clear(Transform* item) { items_.clear(); }
	//Elimina un objeto en concreto, se llama si desaparece una pista/persona dentro de una escena (no es seguro de que sea 100% necesario)
	void removeItem(Transform* item) { items_.erase(std::find(items_.begin(), items_.end(), item)); }

	virtual void update();
private:
	//Vector de objetos de fondo, que se mueven junto a este
	vector<Transform*> items_;
};

