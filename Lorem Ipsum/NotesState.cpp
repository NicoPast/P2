#include "NotesState.h"
#include "LoremIpsum.h"
#include <iostream>
#include "checkML.h"


NotesState::NotesState(LoremIpsum* game) : State(game) {
	init();
	loadText();
};

void NotesState::init() {
	e_ = entityManager_->addEntity();
	text_ = e_->addComponent<Text>();
	text_->setTextDelay(0);
	e_->addComponent<InputText<NotesState*>>(text_, [](NotesState* ns) {ns->saveText(); }, this);
};

void NotesState::loadText() {
	ifstream ifs(DIR);
	string s((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());
	text_->setText(s);
	ifs.close();
	cout << ifs.is_open();
}

void NotesState::saveText() {
	ofstream ofs(DIR);
	ofs << text_->getText();
	ofs.close();
}