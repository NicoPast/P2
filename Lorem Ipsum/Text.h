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
	Text(string t, Vector2D pos, int w, Font* f, Uint32 time = 100, bool canClose = true);
	~Text() { clear(); };
	void init() override;
	void draw() override;
	void update() override;
	void addSoundFX(Resources::AudioId sound);			//Buscar forma de meter indeterminado nº de sonidos de golpe ¿mArgs?
	//[Setters]
	void resetText();
	void setText(string s);
	void setTextDelay(Uint32 t) { textDelay_ = t; }
	void setPos(Vector2D pos) { p_ = pos; }
	void setRightLimit(int rl) { rightLimit_ = rl; };
	void setNextText(string s) { nextText_ = s; }
	void setFont(Font* f);
	void setSoundActive(bool b) { soundActive_ = b; }
	void setCanClose(bool b) { canClose_ = b; }

private:
	//=====MÉTODOS=====

	void advanceText();
	bool changesLine();
	void advanceLine();
	//bool autoLineChange();
	void createTexture();
	void wordJump(string& s);
	void instantText();
	void clear();
	void askNextText() {};		//POR DETERMINAR -> Le pide al StoryManager el siguiente texto a escribir -> "" = nada más
	void playSoundFX();

	//=====VARIABLES=====

	//[Texto]
	Font* font_;
	vector<string> lines_;				//Líneas de texto
	Texture* t_;						//Una textura por línea
	int currentLine_ = 0;
	string fullText_;					//Texto que queda por escribir
	char nextChar_;
	string nextText_;					//Próximo texto a escribir
	bool canClose_ = true;				//Si puede cerrar el cuadro de diálogo
	//[Tiempo]
	Uint32 time_;						//Variable para llevar el tiempo
	Uint32 textDelay_ = 1000;			//Tiempo que tiene que pasar para dibujar el siguiente carácter(en ms)	- 0 para instantáneo
	const Uint32 skipTextDelay_ = 20;	//Velocidad de texto al darle a saltar
	//[Tamaño-Posición]
	Vector2D p_;
	int rightLimit_;					//Límite derecho
	int h_;								//Alto de carácter
	int w_;
	int objW_;								//Ancho objetivo
	vector<int> texPos_;
	//[Input]
	SDL_Keycode inputNext_ = SDLK_SPACE;
	//[Sonido]
	vector<Resources::AudioId> sounds_;	//Todos los sonidos posibles
	bool soundActive_ = true;
};

