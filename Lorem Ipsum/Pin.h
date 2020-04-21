#pragma once
#include "Component.h"
#include "Chinchetario.h"
#include "Line.h"
#include "Drag.h"
#include "DragDrop.h"
using CallBackPin = void(Chinchetario*, Entity*);	//Not sure if necesario
class Pin : public Drag
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
	Pin(Chinchetario* ch, CentralClue* c, Resources::ClueIDs i, Resources::ClueType t, CallBackPin cb) : Drag(ch), centralClue_(c), correctLink_(i), type_(t), f_(cb) {};
	~Pin() {};
	void init();
	void update();
	virtual void deactivateDrag();
	bool isSameType(Resources::ClueType ct) { return ct == type_; }
	bool isCorrect();
	void setActualLink(Clue* c) { actualLink_ = c; state_ = true; }
	void resetActualLink() { actualLink_ = nullptr; state_ = false; }
	bool getState() { return state_; }
	Clue* getActualLink() { return actualLink_; }
	void associateLine(DragDrop* dd) { dd->setLine(l_); }
	void setState(bool s) { state_ = s; }
	void eliminateLine() { l_->eraseLine(); }
private:
	virtual void func() { f_(ch_, entity_); }
	CentralClue* centralClue_;
	Clue* actualLink_ = nullptr;
	Resources::ClueIDs correctLink_;
	Resources::ClueType type_;
	Line* l_;
	CallBackPin* f_;
	bool state_ = false;
};

