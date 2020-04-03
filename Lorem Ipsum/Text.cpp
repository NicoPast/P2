#include "Text.h"
Text::Text(string t) : Text(t, { 0, 0 }, -1, nullptr) {

}
Text::Text() : Text("", { 0, 0 }, -1, nullptr) {

}
Text::Text(string t, Vector2D pos, int w) : Text(t, pos, w, nullptr) {

}
Text::Text(string t, Vector2D pos, int w, Font* f, Uint32 time, bool canClose) : Component(ecs::Text), fullText_(t), textDelay_(time), p_(pos), objW_(w), font_(f), canClose_(canClose) {
	lines_.push_back("");
	texPos_.push_back(0);
	t_ = nullptr;
}
void Text::init() {
	//Si no recibe límite derecho, lo iguala al de la pantalla
	if (objW_ == -1)
		objW_ = game_->getWindowWidth() - p_.getX();
	if (font_ == nullptr) {
		font_ = game_->getFontMngr()->getFont(Resources::ARIAL24);	//Fuente predeterminada
	}
	//h_ = TTF_FontHeight(font_->getTTF_Font());
	string a = "a";
	TTF_SizeText(font_->getTTF_Font(), a.c_str(), &w_, &h_);
	if (fullText_.size() > 0) {
		createTexture();
		if (textDelay_ == 0) {
			instantText();
		}
	}
}
void Text::draw() {
	//Dibuja todas las texturas separadas
	if (t_ != nullptr)
	{
		for (int i = 0; i < lines_.size(); i++) {
			SDL_Rect dest = RECT(p_.getX(), p_.getY() + i * h_, lines_[i].size() * w_, h_);
			SDL_Rect src = RECT(texPos_[i], 0, lines_[i].size() * w_, h_);
			t_->render(dest, src);
		}
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
void Text::resetText() {
	clear();
	fullText_ = "";
}
void Text::setText(string s) {
	clear();
	fullText_ = s;
	createTexture();
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
	if (soundActive_ && nextChar_ != ' ')	//Sonidos evitan espacios
		playSoundFX();
}
//True = cambia de línea
bool Text::changesLine() {
	int x;
	x = (lines_[currentLine_].size() + 1) * w_;
	return x > objW_;
}
//Salta de línea
void Text::advanceLine() {
	currentLine_++;
	lines_.push_back("");
	char c = ' ';
	char last = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
	if (nextChar_ == ' ') {
		lines_[currentLine_ - 1].push_back(nextChar_);
		nextChar_ = fullText_.front();
		fullText_.erase(0, 1);
	}
	else if (last != c) {
		wordJump(lines_[currentLine_]);
	}
	texPos_.push_back(texPos_[currentLine_ - 1] + (lines_[currentLine_ - 1].size() * w_));
}
//Crea la textura de la línea correspondiente
void Text::createTexture() {
	t_ = new Texture(game_->getRenderer(), fullText_, font_, { COLOR(0xffffffff) });	//Crea la textura
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
	}
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
	lines_.push_back("");
	delete t_;
	t_ = nullptr;
	currentLine_ = 0;
	texPos_.clear();
	texPos_.push_back(0);
}
//Elige un sonido aleatorio de los disponibles
void Text::playSoundFX() {
	int n = game_->getRandGen()->nextInt(0, sounds_.size());
	game_->getAudioMngr()->playChannel(sounds_[n], 0);
}