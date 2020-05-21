#include "Notes.h"
#include "StoryManager.h"
#include <iostream>
#include "checkML.h"

Notes::Notes(StoryManager* game, int width, double posx, double posy) : game_(game) {
	//Lee el texto del archivo
	ifstream ifs(DIR);
	string s((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());

	//Inicializa la entidad y sus componentes
	e_ = game_->addEntity(3);
	text_ = e_->addComponent<Text>(s, Vector2D(posx, posy), width);
	text_->setTextDelay(0);
	text_->setJump(false);
	it_ = e_->addComponent<InputText<Notes*>>(text_, [](Notes* ns) {ns->saveText(); }, this, false);
	e_->setActive(false);
	//Cierra el archivo
	ifs.close();
};

//Guarda el texto en un archivo
void Notes::saveText() {
	ofstream ofs(DIR);
	ofs << text_->getText();
	ofs.close();
	game_->deactivateNotes();
}
