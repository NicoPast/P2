#pragma once
#include "Component.h"
#include "Chinchetario.h"
class Pin : public Component
{
	//Este componente debe comprobar la logica de las pistas
	//Debe tenera acceso a la pista a la que está asociada
	//Debe tambien tener una referencia al tipo de esta chincheta
	//Debe tener acceso a su propio rect
	//Cuando pinchas dentro del cuadrado de esta entidad, debe activarse un booleano
	//Mientras se tenga el raton pulsado, en el update, se hace un render draw line de SDL desde el inicio (que se indica en el start) hasta la posición del ratón
	//Cuando se suelta un raton, si está encima de una pista que no sea una pista principal Y que sea del tipo compatible a la chincheta, no elimina la linea y hace hijo a esa pista enlazada
	//Si no está sobre una pista compatible, elimina la línea
public:
	Pin(CentralClue* c, Resources::ClueIDs i, Resources::ClueType t) : Component(ecs::Pin), centralClue_(c), correctLink_(i), type_(t) {};
	~Pin();


private:
	CentralClue* centralClue_;
	Resources::ClueIDs correctLink_;
	Resources::ClueType type_;

};

