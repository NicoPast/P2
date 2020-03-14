#include "TextTest.h"
TextTest::TextTest(string t) : TextTest(t, 100, TEXT_NORMAL, LINE_MANUAL, 0, game_->getWindowWidth()) {
	
}
TextTest::TextTest(string t, Uint32 time) : TextTest(t, time, TEXT_NORMAL, LINE_MANUAL, 0, -1) {

}
TextTest::TextTest(string t, Uint32 time, TEXTMODE mode) : TextTest(t, time, mode, LINE_MANUAL, 0, -1) {
	
}
TextTest::TextTest(string t, Uint32 time, TEXTMODE mode, LINETYPE ltype, int leftLimit, int rightLimit) : Component(ecs::TextTest), fullText_(t), timePass_(time), mode_(mode),lineType_(ltype), leftLimit_(leftLimit), rightLimit_(rightLimit) {
	lines_.push_back("");
	t_.push_back(nullptr);
}
void TextTest::init() {
	if (rightLimit_ == -1)
		rightLimit_ = game_->getWindowWidth();
	font_ = game_->getFontMngr()->getFont(Resources::ARIAL24);
	size_ = font_->getSize();
	w_ = rightLimit_ - leftLimit_;
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
			if (mode_ == TEXT_NORMAL) {
				t_[i]->render(leftLimit_, 50 + (i * 20));
			}
			else
			{
				t_[i]->render(game_->getWindowWidth() / 2 - t_[currentLine_]->getWidth() / 2, 50 + (i * 20));
			}
	}
	//cout << TTF_SizeText(font_->getTTF_Font(), , &w, &size);
}
//Coge el siguiente carácter del texto y lo mete a la línea correspondiente
void TextTest::advanceText() {
	if (changesLine())
		advanceLine();
	if (t_[currentLine_] != nullptr)		//Si es una línea que tiene textura, se borra (seguridad)
		delete t_[currentLine_];
	lines_[currentLine_] = lines_[currentLine_] + fullText_.front();
	fullText_.erase(0, 1);
	t_[currentLine_] = new Texture(game_->getRenderer(), lines_[currentLine_], font_, { COLOR(0xffffffff) });	//Crea la textura
}
//WIP/Ignorar
//Si sale por la derecha, avanzar línea -> ¿Parametrizar el valor/Comprobar el ancho?
bool TextTest::changesLine() {
	if (lineType_ == LINE_MANUAL) {
		return (lines_[currentLine_].size() > lineSize_);
	}
	else return autoLineChange();
	
}
//Salta de línea
void TextTest::advanceLine() {
	currentLine_++;
	lines_.push_back("");
	t_.push_back(nullptr);
}
//true = cambia de línea
bool TextTest::autoLineChange() {
	int w = 0;
	cout << TTF_SizeText(font_->getTTF_Font(), lines_[currentLine_].c_str(), &w, NULL);
	return w > w_;
}