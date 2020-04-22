#include "Text.h"
Text::Text(string t) : Text(t, { 0, 0 }, -1, Resources::RobotoTest24) {

}
Text::Text() : Text("", { 0, 0 }, -1, Resources::RobotoTest24) {

}
Text::Text(string t, Vector2D pos, int w) : Text(t, pos, w, Resources::RobotoTest24) {

}
Text::Text(string t, Vector2D pos, int w, Resources::FontId f, Uint32 time) : Component(ecs::Text), fullText_(t), textDelay_(time), p_(pos), objW_(w), fontId_(f) {
	lines_.push_back("");
	t_ = nullptr;
}
void Text::init() {
	//Si no recibe límite derecho, lo iguala al de la pantalla
	if (objW_ == -1)
		objW_ = game_->getWindowWidth() - p_.getX();
	setFont(fontId_);
	if (fullText_.size() > 0 && textDelay_ == 0) {
		instantText();
	}
}
void Text::draw() {
	if (t_ != nullptr)
	{
		for (int i = 0; i < lines_.size(); i++) {
			for (int j = 0; j < lines_[i].size(); j++) {
				SDL_Rect dest = RECT(p_.getX() + j * w_, p_.getY() + i * h_, w_, h_);
				char c = lines_[i][j];
				SDL_Rect src;
				if (c >= 0)
					src = RECT((lines_[i][j] - 32) * w_, 0, w_, h_);		  //No se que hacer con estos numeros magicos
				else src = RECT((lines_[i][j] + 190) * w_, 0, w_, h_);		  //No se que hacer con estos numeros magicos
				t_->render(dest, src);
			}
		}
	}
}
void Text::update() {
	if (fullText_.size() > 0) {
		if (game_->getTime() - time_ >= textDelay_) {
			advanceText();
			time_ = game_->getTime();
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
	if (textDelay_ == 0)
		instantText();
}
void Text::setFont(Resources::FontId f) {
	font_ = game_->getFontMngr()->getFont(fontId_);
	t_ = game_->getFontMngr()->getGlyphs(fontId_);
	string a = "a";
	TTF_SizeText(font_->getTTF_Font(), a.c_str(), &w_, &h_);		//Obtiene el alto y ancho de carácter
}
//Coge el siguiente carácter del texto y lo mete a la línea correspondiente
void Text::advanceText() {
	nextChar_ = fullText_.front();
	fullText_.erase(0, 1);
	if (detectSpecialChar())
		treatSpecialChar();
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
	char last = lines_[currentLine_ - 1][lines_[currentLine_ - 1].size() - 1];
	if (nextChar_ == ' ') {
		lines_[currentLine_ - 1].push_back(nextChar_);
		nextChar_ = fullText_.front();
		fullText_.erase(0, 1);
	}
	else if (last != ' ') {
		wordJump(lines_[currentLine_]);
	}
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
	currentLine_ = 0;
}
//Elige un sonido aleatorio de los disponibles
void Text::playSoundFX() {
	if (sounds_.empty())return;
	int n = game_->getRandGen()->nextInt(0, sounds_.size());
	game_->getAudioMngr()->playChannel(sounds_[n], 0);
}
//Hace la función especial dependiendo del carácter siguiente [EXPANDIBLE SI NECESARIO]
void Text::treatSpecialChar() {
	if (fullText_.front() == 'n') {
		nextChar_ = *(fullText_.begin() + 1);
		fullText_.erase(0, 2);
		advanceLine();
	}
}