#pragma once
#include "SDL_macros.h"
#include "checkML.h"
#include "Component.h"
class Text : public Component
{
public:
	Text();
	Text(string t);
	Text(string t, Vector2D pos, int w);
	Text(string t, Vector2D pos, int w, Resources::FontId f, Uint32 time = 100);
	~Text() { clear(); };
	void init() override;
	void draw() override;
	void update() override;
	void addSoundFX(Resources::AudioId sound);			//Buscar forma de meter indeterminado nº de sonidos de golpe ¿mArgs?
	//void setFollowTransform(Transform* t) {  }
	//[Setters]
	void resetText();
	void setText(string s);
	void setTextDelay(Uint32 t) { textDelay_ = t; }
	void setPos(Vector2D pos) { p_ = pos; }
	void setWidth(int w) { objW_ = w; };
	void setFont(Resources::FontId f);
	void setSoundActive(bool b) { soundActive_ = b; };
	void setScroll(int x, int y, int w, int h);
	void setColor(Uint8 r, Uint8 g, Uint8 b) { r_ = r; g_ = g; b_ = b; }; //cambia el color de todo el texto
	void setColor(Uint8 r, Uint8 g, Uint8 b, int line) { rLine_ = r; gLine_ = g; bLine_ = b; coloredLine_ = line; }; //cambia el color de una linea en todo el texto
	//[Getters]
	bool getEnded() { return fullText_.size() == 0; }
	string getText() { string res;  for (string& s : lines_)res += s; return res; }
	vector<string> getLines() { return lines_; }
	int getNumLines() { return (int)lines_.size(); }
	int getCharW() { return w_; }
	int getCharH() { return h_; }
	Vector2D getPos() { return p_; }
	int getMaxW() { return objW_; }
	bool clickOnText(Vector2D mousePos, int& characterIndex, int& lineIndex);
	Uint32 getTextDelay() { return textDelay_; };
private:
	//=====MÉTODOS=====

	void advanceText();
	bool changesLine();
	void advanceLine();
	void wordJump(string& s);
	void instantText();
	void clear();
	void playSoundFX();
	bool detectSpecialChar() { return nextChar_ == '\\'; }		//No se si mejor poner un método que te haga return false si no lo detecta y que haga las cosas si lo detecta
	void treatSpecialChar();
	void checkScroll();
	//=====VARIABLES=====

	//[Texto]
	Resources::FontId fontId_;
	Font* font_ = nullptr;
	Texture* t_ = nullptr;			//Textura con los glifos
	vector<string> lines_;				//Líneas de texto
	int currentLine_ = 0;
	string fullText_ = "";			//Texto que queda por escribir
	char nextChar_ = char();
	//[Tiempo]
	Uint32 time_ = Uint32();						//Variable para llevar el tiempo
	Uint32 textDelay_ = 1000;			//Tiempo que tiene que pasar para dibujar el siguiente carácter(en ms)	- 0 para instantáneo
	//[Tamaño-Posición]
	Vector2D p_ = Vector2D(0, 0);
	int h_ = 0;							//Alto de carácter
	int w_ = 0;							//Ancho de carácter
	int objW_ = 0;						//Ancho objetivo
	int currentIndex = 0;;				//pos en text[currentLine]
	Uint8 r_= 255;
	Uint8 g_= 255;
	Uint8 b_= 255;
	Uint8 rLine_ = 0;
	Uint8 gLine_ = 0;
	Uint8 bLine_ = 0;
	int coloredLine_ = -1;

	//[Recangulo de scroll vertical]
	SDL_Rect scrollRect_ = {-1,-1,-1,-1};

	//[Sonido]
	vector<Resources::AudioId> sounds_;	//Todos los sonidos posibles
	bool soundActive_ = true;
	bool textIn_ = false;
};

