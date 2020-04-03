#include "Text.h"
Text::Text(string t) : Text(t, { 0, 0 }, -1, nullptr) {
	
}
Text::Text() : Text("", { 0, 0 }, -1, nullptr) {

}
Text::Text(string t, Vector2D pos, int rightLimit) : Text(t, pos, rightLimit, nullptr) {

}
Text::Text(string t, Vector2D pos, int rightLimit, Font* f, Uint32 time, bool canClose) : Component(ecs::Text), fullText_(t), textDelay_(time), p_(pos), rightLimit_(rightLimit), font_(f), canClose_(canClose) {
	lines_.push_back("");
	t_.push_back(nullptr);
}
//Text::Text(string t, Uint32 time, int leftLimit, int rightLimit, LINEJUMP ljump, LINETYPE ltype, TEXTMODE mode) : Component(ecs::Text), fullText_(t), timePass_(time), mode_(mode),lineType_(ltype), leftLimit_(leftLimit), rightLimit_(rightLimit) {
//	lines_.push_back("");
//	t_.push_back(nullptr);
//	mode_ = mode;
//	lineType_ = ltype;
//	jumpType_ = ljump;
//	jumpTypeNext_ = ljump;
//}
void Text::init() {
	//Si no recibe límite derecho, lo iguala al de la pantalla
	if (rightLimit_ == -1)
		rightLimit_ = game_->getWindowWidth();
	if (font_ == nullptr) {
	font_ = game_->getFontMngr()->getFont(Resources::ARIAL24);	//Fuente predeterminada
	}
	h_ = TTF_FontHeight(font_->getTTF_Font());
	w_ = rightLimit_ - p_.getX();
	if (textDelay_ == 0) {
		instantText();
	}
}
void Text::draw() {
	//Dibuja todas las texturas separadas
	for (int i = 0; i < t_.size(); i++) {
		if(t_[i] != nullptr)
			//if (mode_ == TEXT_NORMAL) {
			t_[i]->render(p_.getX(), p_.getY() + (i * h_));
			//}
			//else
			//{
			//	t_[i]->render(game_->getWindowWidth() / 2 - t_[currentLine_]->getWidth() / 2, 50 + (i * 20));
			//}
	}
}
void Text::update() {
	InputHandler* ih = InputHandler::instance();
	//Seguir dibujando
	if (fullText_.size() > 0) {
		if (ih->keyDownEvent()) {		//Si pulsa la tecla aumenta la velocidad -> ¿Mantener pulsado o solo darle una vez?
			if (ih->isKeyDown(inputNext_)) {	
				textDelay_ = skipTextDelay_;
				soundActive_ = false;			//Desactiva el sonido porque se lo carga
			}
		}//Si es hora de dibujar el siguiente caracter, avanza el texto
		if (game_->getTime() - time_ >= textDelay_) {
			advanceText();
			time_ = game_->getTime();
		}
	}
	//Esperar input de jugador para continuar
	else
	{
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(inputNext_)) {
				if (nextText_ != "") {
					cout << "Hay más texto" << endl;
					clear();
					//setTextDelay(100);
					setText(nextText_);
					font_ = game_->getFontMngr()->getFont(Resources::ARIAL24);
					nextText_ = "";
					askNextText();
				}
				else if (canClose_) {
					cout << "No más" << endl;
					//Cerrar caja de diálogo o lo que sea
				}
			}
		}
	}

}
void Text::addSoundFX(Resources::AudioId sound) {
	sounds_.push_back(sound);
}
void Text::setText(string s) {
	clear();
	fullText_ = s;
	if (textDelay_ == 0)
		instantText();
}
void Text::setFont(Font* f) {
	font_ = f;
	h_ = TTF_FontHeight(font_->getTTF_Font());
}
//Coge el siguiente carácter del texto y lo mete a la línea correspondiente
void Text::advanceText() {
	nextChar_ = fullText_.front();
	fullText_.erase(0, 1);
	if (changesLine())
		advanceLine();
	lines_[currentLine_] = lines_[currentLine_] + nextChar_;
	createTexture(currentLine_);
	if (soundActive_ && nextChar_ != ' ')	//Sonidos evitan espacios
		playSoundFX();
}
//True = cambia de línea
bool Text::changesLine() {
	int w = 0;
	//cout << TTF_SizeText(font_->getTTF_Font(), lines_[currentLine_].c_str(), &w, NULL);
	TTF_SizeText(font_->getTTF_Font(), lines_[currentLine_].c_str(), &w, NULL);
	return w > w_;
}
//Salta de línea
void Text::advanceLine() {
	currentLine_++;
	lines_.push_back("");
	t_.push_back(nullptr);
	char c = ' ';
	char last = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
	if (nextChar_ == ' ') {
		nextChar_ = fullText_.front();
		fullText_.erase(0, 1);
	}
	else if (last != c) {
		//if (jumpType_ == JUMP_WORD) {
			wordJump(lines_[currentLine_]);
		//}
		//else
		//{
		//	char bLast = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 2];
		//	if (last != c) {
		//		if (bLast != c) {	//Si el carácter anterior no es un espacio
		//			lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1] = '-';
		//		}
		//		else {
		//			lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1] = ' ';
		//		}
		//		lines_[currentLine_] = lines_[currentLine_] + last;
		//	}
		//}
		createTexture(currentLine_ - 1);
	}
	//if (jumpTypeNext_ != jumpType_)
	//	jumpTypeNext_ = jumpType_;
}
//true = cambia de línea
//bool Text::autoLineChange() {
//	int w = 0;
//	//cout << TTF_SizeText(font_->getTTF_Font(), lines_[currentLine_].c_str(), &w, NULL);
//	TTF_SizeText(font_->getTTF_Font(), lines_[currentLine_].c_str(), &w, NULL);
//	return w > w_;
//}
//Crea la textura de la línea correspondiente
void Text::createTexture(int line) {
	if (t_[line] != nullptr)		//Si es una línea que tiene textura, se borra (seguridad)
		delete t_[line];
	t_[line] = new Texture(game_->getRenderer(), lines_[line], font_, { COLOR(0xffffffff) });	//Crea la textura
}
//Busca el espacio anterior a la palabra y traslada esta a la línea (string) correspondiente
void Text::wordJump(string& s) {
	size_t size = lines_[currentLine_ - 1].size();
	bool hasSpace = false;
	char c;
	for (int i = 0; i < size; i++) {
		c = lines_[currentLine_ - 1][i];
		if (c == ' ')
			hasSpace = true;
	}
	//Si la línea contiene algún espacio, corta ahí
	if (hasSpace) {
		while (c != ' ') {
			lines_[currentLine_ - 1].pop_back();
			s = c + s;
			c = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
		}
	}
	else {
		//Si el último carácter es , o . no hace falta cortar
		if (c == ',' || c == '.') {
			advanceText();
			s[0] = s[1];
			s.pop_back();
		}
		else {
			s = c + s;
			lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1] = '-';
		}
	}
	//else {
	//	jumpTypeNext_ = JUMP_LINE;
	//}
	//while (c != ' ') {
	//	lines_[currentLine_ - 1].pop_back();
	//	s = c + s;
	//	if (lines_[currentLine_ - 1].size() > 0) {
	//		c = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
	//	}
	//	else c = ' ';
	//}
	//if (autoLineChange()) {
	//	jumpTypeNext_ = JUMP_LINE;
	//}
}
//Muestra todo el texto instantáneamente
void Text::instantText() {
	bool sndActv = soundActive_;
	soundActive_ = false;
	while (fullText_.size() > 0)
		advanceText();
	if (sndActv && sounds_.size() > 0) {
		playSoundFX();
		soundActive_ = true;
	}
}
//Resetea el texto
void Text::clear() {
	lines_.clear();
	for (int i = 0; i < t_.size(); i++) {
		delete t_[i];
	}
	t_.clear();
	lines_.push_back("");
	t_.push_back(nullptr);
	currentLine_ = 0;
}
//Elige un sonido aleatorio de los disponibles
void Text::playSoundFX() {
	int n = game_->getRandGen()->nextInt(0, sounds_.size());
	game_->getAudioMngr()->playChannel(sounds_[n], 0);
}