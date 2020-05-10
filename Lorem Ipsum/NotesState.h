#pragma once
#include "State.h"
#include "Text.h"
#include "InputText.h"
#include "Entity.h"
class LoremIpsum;
const string DIR = "../saves/notes.txt";

class NotesState : public State {
public:
	NotesState(LoremIpsum* game);
	virtual ~NotesState() {};
	void init();
	void saveText();
	void loadText();
private:
	Entity* e_ = nullptr;
	Text* text_ = nullptr;
};