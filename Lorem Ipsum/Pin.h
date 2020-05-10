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
	Pin(Chinchetario* ch, CentralClue* c, Resources::ClueID i, Resources::ClueType t, CallBackPin cb) : Drag(ch), centralClue_(c), correctLink_(i), type_(t), f_(cb) {};
	~Pin() {};
	void init();
	void update();
	virtual void deactivateDrag();
	bool isSameType(Resources::ClueType ct) { return ct == type_; }
	bool isCorrect();
	void setActualLink(Clue* c) { actualLink_ = c; state_ = true; }
	void resetActualLink() { actualLink_ = nullptr; state_ = false; }
	Clue* getActualLink() { return actualLink_; }
	void setState(bool s) { state_ = s; }
	bool getState() { return state_; }
	Line* getLine() { return l_; }
	void associateLine(DragDrop* dd) { dd->setLine(l_); }
	void eliminateLine() { l_->eraseLine(); }
	CentralClue* getCentralClue() { return centralClue_; }
	void setColor(SDL_Color c) { if (l_ != nullptr)l_->setColor(c); }
private:
	virtual void func() { f_(ch_, entity_); }
	CentralClue* centralClue_ = nullptr;
	Clue* actualLink_ = nullptr;				//Pista a la que esta enganchada actualmente
	Resources::ClueID correctLink_;			//Pista correcta
	Resources::ClueType type_;					//Tipo de la pista
	Line* l_ = nullptr;
	CallBackPin* f_ = nullptr;
	bool state_ = false;						//Si esta enganchado a algo o no
};

