#include "TextTest.h"
TextTest::TextTest(string t) : TextTest(t, 100) {
	
}
TextTest::TextTest(string t, Uint32 time) : Component(ecs::TextTest), fullText_(t), timePass_(time) {
	lines_.push_back("");
	t_.push_back(nullptr);
}
void TextTest::update() {
	InputHandler* ih = InputHandler::instance();
	//Si pulsa la tecla aumenta la velocidad -> ¿Mantener pulsado o solo darle una vez?
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_SPACE)) {	//¿Parametrizar?
			timePass_ = 2;
		}
	}//Si es hora de dibujar el siguiente caracter, avanza el texto
	if (game_->getTime() - time_ >= timePass_ && fullText_.size() > 0) {
		advanceText();
		time_ = game_->getTime();
	}
}
void TextTest::draw() {
	//Dibuja todas las texturas separadas
	for (int i = 0; i < t_.size(); i++) {
		if(t_[i] != nullptr)
			t_[i]->render(game_->getWindowWidth() / 2 - t_[currentLine_]->getWidth() / 2, 50 + (i * 20));
	}
}
//Coge el siguiente carácter del texto y lo mete a la línea correspondiente
void TextTest::advanceText() {
	if (lines_[currentLine_].size() > 50) {	//Si sale por la derecha, avanzar línea -> ¿Parametrizar el valor/Comprobar el ancho?
		currentLine_++;
		lines_.push_back("");
		t_.push_back(nullptr);
	}
	if (t_[currentLine_] != nullptr)		//Si es una línea que tiene textura, se borra (seguridad)
		delete t_[currentLine_];
	lines_[currentLine_] = lines_[currentLine_] + fullText_.front();
	fullText_.erase(0, 1);
	t_[currentLine_] = new Texture(game_->getRenderer(), lines_[currentLine_], game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xffffffff) });	//Crea la textura
}
//WIP/Ignorar
bool TextTest::changeLine() {
	//if()
	return true;
}