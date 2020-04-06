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
	void addSoundFX(Resources::AudioId sound);			//Buscar forma de meter indeterminado n� de sonidos de golpe �mArgs?
	//[Setters]
	void resetText();
	void setText(string s);
	void setTextDelay(Uint32 t) { textDelay_ = t; }
	void setPos(Vector2D pos) { p_ = pos; }
	void setWidth(int w) { objW_ = w; };
	void setFont(Resources::FontId f);
	void setSoundActive(bool b) { soundActive_ = b; }
	//[Getters]
	bool getEnded() { return fullText_.size() == 0; }

private:
	//=====M�TODOS=====

	void advanceText();
	bool changesLine();
	void advanceLine();
	void wordJump(string& s);
	void instantText();
	void clear();
	void playSoundFX();
	bool detectSpecialChar() { return nextChar_ == '\\'; }		//No se si mejor poner un m�todo que te haga return false si no lo detecta y que haga las cosas si lo detecta
	void treatSpecialChar();

	//=====VARIABLES=====

	//[Texto]
	Resources::FontId fontId_;
	Font* font_;
	Texture* t_;						//Textura con los glifos
	vector<string> lines_;				//L�neas de texto
	int currentLine_ = 0;
	string fullText_;					//Texto que queda por escribir
	char nextChar_;
	//[Tiempo]
	Uint32 time_;						//Variable para llevar el tiempo
	Uint32 textDelay_ = 1000;			//Tiempo que tiene que pasar para dibujar el siguiente car�cter(en ms)	- 0 para instant�neo
	//[Tama�o-Posici�n]
	Vector2D p_;
	int h_;								//Alto de car�cter
	int w_;								//Ancho de car�cter
	int objW_;							//Ancho objetivo
	//[Sonido]
	vector<Resources::AudioId> sounds_;	//Todos los sonidos posibles
	bool soundActive_ = true;
};

