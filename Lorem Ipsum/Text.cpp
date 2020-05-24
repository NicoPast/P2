#include "Text.h"
#include "Transform.h"
#include "Entity.h"
Text::Text(string t) : Text(t, { 0, 0 }, -1, Resources::RobotoTest24) {

}
Text::Text() : Text("", { 0, 0 }, -1, Resources::RobotoTest24) {

}
Text::Text(string t, Vector2D pos, int w) : Text(t, pos, w, Resources::RobotoTest24) {

}
Text::Text(string t, Vector2D pos, int w, Resources::FontId f, Uint32 time) : Component(ecs::Text), textDelay_(time), p_(pos), objW_(w), fontId_(f) {
	//Vuelca todo el texto en una linea
	lines_.push_back(t);
	t_ = nullptr;
}
void Text::init() {
	//Si no recibe límite derecho, lo iguala al de la pantalla
	if (objW_ == -1)
		objW_ = game_->getWindowWidth() - p_.getX();
	setFont(fontId_);
	if (fullText_.size() >= 0 && textDelay_ == 0) {
		instantText();
	}
	//Hace que la linea gigante pase a estar bien 
	while (fullText_ != "" && changesLine())
		advanceLine();
}
void Text::draw() {
	if (t_ != nullptr)
	{
		canScroll = false;
		t_->setColorMod(r_, g_, b_);
		for (int i = 0; i < lines_.size(); i++) {
			if (i == coloredLine_) t_->setColorMod(rLine_, gLine_, bLine_);
			for (int j = 0; j < lines_[i].size(); j++) {
				SDL_Rect dest = RECT(p_.getX() + j * w_, p_.getY() + i * h_, w_, h_);
				char c = lines_[i][j];
				SDL_Rect src;
				SDL_Rect res = {0,0,0,0};
				if (c >= 0)
					src = RECT((lines_[i][j] - 32) * w_, 0, w_, h_);		  //No se que hacer con estos numeros magicos
				else src = RECT((lines_[i][j] + 190) * w_, 0, w_, h_);		  //No se que hacer con estos numeros magicos
				textIn_ = SDL_IntersectRect(&dest, &scrollRect_, &res);
				if (scrollRect_.h != -1)
				{
					if (textIn_) 
					{
						int realYOffset= dest.y - res.y;
						int realWOffset= res.w;
						int realHOffset= res.h;

						dest.y -= realYOffset;
						dest.h = realHOffset;
						src.y =- realYOffset;
						src.h = realHOffset;
						src.w = realWOffset;
						t_->render(dest, src);
						SDL_RenderDrawRect(game_->getRenderer(), &scrollRect_);
					}
					else 
					{
						canScroll = true;
						SDL_RenderDrawRect(game_->getRenderer(), &scrollRect_);
					}
				}
				if(scrollRect_.h == -1)
				{
					t_->render(dest, src);
				}
			}
			if (i == coloredLine_) t_->setColorMod(r_, g_, b_);
		}
		t_->setColorMod(255, 255, 255);
	}
}
void Text::update() {
	if (fullText_.size() > 0) {
		if (game_->getTime() - time_ >= textDelay_) {
			advanceText();
			time_ = game_->getTime();
		}
	}
	if (canScroll)
	{
		checkScroll();
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

//Crea la capacidad al jugador de scrollear en el texto. La H será la altura a la que desaparece el texto. Por defecto será la H del objeto menos la Y de la pos del texto
void Text::setScroll(int x, int y, int w, int h)
{
	Transform* tr = GETCMP1_(Transform);
	scrollRect_.x = x;
	scrollRect_.y = y;
	scrollRect_.w = w;
	scrollRect_.h = h;
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
	if (fullText_.front() == 'n')
	{
		nextChar_ = *(fullText_.begin() + 1);
		fullText_.erase(0, 2);
		advanceLine();
	}
}

void Text::checkScroll()
{
	InputHandler* ih = InputHandler::instance();
	int vMotion = ih->getMouseWheelMotion()*5;
	if ( vMotion != 0)
	{
		if (vMotion < 0)
		{
			if (p_.getY()+h_*(lines_.size()+1) > scrollRect_.y+scrollRect_.h)
			{
				p_.setY(p_.getY() + vMotion);
			}
		}
		else
		{
			if (p_.getY()  < scrollRect_.y)
			{
				p_.setY(p_.getY() + vMotion);
			}
		}
	}
}

bool Text::clickOnText(Vector2D mousePos, int& charIndex, int& lineIndex)
{
	bool res = false;
	for (int i = 0; i < lines_.size() && !res; i++)
	{
		string line = lines_[i];
		SDL_Rect lineBox{ p_.getX(), p_.getY() + h_ * i, w_ * line.size(),h_ };
		SDL_Point mouseP = { mousePos.getX(), mousePos.getY() };
		if (SDL_PointInRect(&mouseP, &lineBox))
		{
			charIndex = ((int)(mousePos.getX() - p_.getX()) / w_) + 1;
			lineIndex = i;
			res = true;
		}
	}
	return res;
}