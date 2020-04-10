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
	void setColor(Uint8 r, Uint8 g, Uint8 b) { r_ = r; g_ = g; b_ = b; };
	//[Getters]
	bool getEnded() { return fullText_.size() == 0; }
	string getText() { return lines_[0]; }
	vector<string> getLines() { return lines_; }
	int getNumLines() { return lines_.size(); }
	int getCharW() { return w_; }
	int getCharH() { return h_; }
	Vector2D getPos() { return p_; }
	int getMaxW() { return objW_; }

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
	//=====VARIABLES=====

	//[Texto]
	Resources::FontId fontId_;
	Font* font_;
	Texture* t_;						//Textura con los glifos
	vector<string> lines_;				//Líneas de texto
	int currentLine_ = 0;
	string fullText_;					//Texto que queda por escribir
	char nextChar_;
	//[Tiempo]
	Uint32 time_;						//Variable para llevar el tiempo
	Uint32 textDelay_ = 1000;			//Tiempo que tiene que pasar para dibujar el siguiente carácter(en ms)	- 0 para instantáneo
	//[Tamaño-Posición]
	Vector2D p_;
	int h_;								//Alto de carácter
	int w_;								//Ancho de carácter
	int objW_;							//Ancho objetivo
	int currentIndex=0;					//pos en text[currentLine]
	Uint8 r_= 0;
	Uint8 g_= 0;
	Uint8 b_= 0;
	//[Sonido]
	vector<Resources::AudioId> sounds_;	//Todos los sonidos posibles
	bool soundActive_ = true;
};

