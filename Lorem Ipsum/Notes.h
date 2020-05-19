#pragma once
#include "State.h"
#include "Text.h"
#include "InputText.h"
#include "Entity.h"
class StoryManager;
const string DIR = "../saves/notes.txt";

class Notes {
public:
	Notes(StoryManager* game, int width, double posx, double posy);
	virtual ~Notes() {};
	void init();
	void saveText();
	//Activa la entidad
	void inline activate() { e_->setActive(true); it_->setEnabled(true); }
	//Desactiva la entidad
	void inline deactivate() { e_->setActive(false); }
private:
	StoryManager* game_;
	Entity* e_;
	Text* text_;
	InputText<Notes*>* it_;
};