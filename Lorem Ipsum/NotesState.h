#pragma once
#include "State.h"
#include "Text.h"
#include "InputText.h"
#include "Entity.h"
class LoremIpsum;
const string DIR = "../saves/notes.txt";

class Notes : public State {
public:
	Notes(LoremIpsum* game);
	virtual ~Notes() {};
	void init();
	void saveText();
	void loadText();
private:
	Entity* e_ = nullptr;
	Text* text_ = nullptr;
};