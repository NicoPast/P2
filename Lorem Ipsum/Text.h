#pragma once
#include "SDL_macros.h"
#include "Component.h"
//enum TEXTMODE{TEXT_NORMAL, TEXT_TYPEWRITER};		//Texto normal y con el efecto de máquina de escribir - DESACTIVADO, ACTIVAR SI QUERER POSIBILIDAD
//enum LINETYPE{LINE_AUTO, LINE_MANUAL};				//Avance de línea manual o automático - DESACTIVADO, ACTIVAR SI QUERER POSIBILIDAD
//enum LINEJUMP{JUMP_WORD, JUMP_LINE};				//Salto de línea por palabra o por guión - DESACTIVADO, ACTIVAR SI QUERER POSIBILIDAD
class Text : public Component
{
public:
	Text();
	Text(string t);
	Text(string t, Vector2D pos, int rightLimit);
	Text(string t, Vector2D pos, int rightLimit, Font* f, Uint32 time = 100, bool canClose = true);
	//Text(string t, Uint32 time, int leftLimit, int rightLimit, LINEJUMP ljump, LINETYPE ltype = LINE_AUTO, TEXTMODE mode = TEXT_NORMAL); - DESACTIVADO, ACTIVAR SI QUERER POSIBILIDAD
	~Text() {};
	void init() override;
	void draw() override;
	void update() override;
	void addSoundFX(Resources::AudioId sound);			//Buscar forma de meter indeterminado nº de sonidos de golpe ¿mArgs?
	//[Setters]
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
	void createTexture(int line);
	void wordJump(string& s);
	void instantText();
	void clear();
	void askNextText() {};		//POR DETERMINAR -> Le pide al StoryManager el siguiente texto a escribir -> "" = nada más
	void playSoundFX();

	//=====VARIABLES=====

	//[Texto]
	Font* font_;
	vector<string> lines_;				//Líneas de texto
	vector<Texture*> t_;				//Una textura por línea
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
	int w_;								//Ancho objetivo
	//[Input]
	SDL_Keycode inputNext_ = SDLK_SPACE;
	//[Sonido]
	vector<Resources::AudioId> sounds_;	//Todos los sonidos posibles
	bool soundActive_ = true;
	//TEXTMODE mode_;					//DESACTIVADO, ACTIVAR SI QUERER POSIBILIDAD
	//LINETYPE lineType_;				//DESACTIVADO, ACTIVAR SI QUERER POSIBILIDAD
	//LINEJUMP jumpType_;				//DESACTIVADO, ACTIVAR SI QUERER POSIBILIDAD
};

