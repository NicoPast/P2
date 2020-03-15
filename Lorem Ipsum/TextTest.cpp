#include "TextTest.h"
TextTest::TextTest(string t) : TextTest(t, 100, 0, -1, JUMP_WORD) {
	
}
TextTest::TextTest(string t, Uint32 time) : TextTest(t, time, 0, -1, JUMP_WORD) {

}
TextTest::TextTest(string t, Uint32 time, int leftLimit, int rightLimit) : TextTest(t, time, leftLimit, rightLimit, JUMP_WORD) {
	
}
TextTest::TextTest(string t, Uint32 time, int leftLimit, int rightLimit, LINEJUMP ljump, LINETYPE ltype, TEXTMODE mode) : Component(ecs::TextTest), fullText_(t), timePass_(time), mode_(mode),lineType_(ltype), leftLimit_(leftLimit), rightLimit_(rightLimit) {
	lines_.push_back("");
	t_.push_back(nullptr);
	mode_ = mode;
	lineType_ = ltype;
	jumpType_ = ljump;
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
	lines_[currentLine_] = lines_[currentLine_] + fullText_.front();
	fullText_.erase(0, 1);
	createTexture(currentLine_);
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
	char c = ' ';
	char last = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
	if (last != c) {
		if (jumpType_ == JUMP_WORD) {
			searchSpace(lines_[currentLine_]);
		}
		else
		{
			char bLast = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 2];
			if (last != c) {
				if (bLast != c) {	//Si el carácter anterior no es un espacio
					lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1] = '-';
				}
				else {
					lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1] = ' ';
				}
				lines_[currentLine_] = lines_[currentLine_] + last;
			}
		}
		createTexture(currentLine_ - 1);
	}
}
//true = cambia de línea
bool TextTest::autoLineChange() {
	int w = 0;
	//cout << TTF_SizeText(font_->getTTF_Font(), lines_[currentLine_].c_str(), &w, NULL);
	TTF_SizeText(font_->getTTF_Font(), lines_[currentLine_].c_str(), &w, NULL);
	return w > w_;
}
//Crea la textura de la línea correspondiente
void TextTest::createTexture(int line) {
	if (t_[line] != nullptr)		//Si es una línea que tiene textura, se borra (seguridad)
		delete t_[line];
	t_[line] = new Texture(game_->getRenderer(), lines_[line], font_, { COLOR(0xffffffff) });	//Crea la textura
}
//Busca el espacio anterior a la palabra y traslada esta a la línea (string) correspondiente
void TextTest::searchSpace(string& s) {
	char c = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
	while (c != ' ') {
		lines_[currentLine_ - 1].pop_back();
		s = c + s;
		c = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
	}
}