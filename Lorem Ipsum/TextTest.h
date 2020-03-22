#pragma once
#include "SDL_macros.h"
#include "Component.h"
enum TEXTMODE{TEXT_NORMAL, TEXT_TYPEWRITER};		//Texto normal y con el efecto de m�quina de escribir
enum LINETYPE{LINE_AUTO, LINE_MANUAL};				//Avance de l�nea manual o autom�tico
enum LINEJUMP{JUMP_WORD, JUMP_LINE};				//Salto de l�nea por palabra o por gui�n
class TextTest : public Component
{
public:
	TextTest(string t);
	TextTest(string t, Uint32 time);
	TextTest(string t, Uint32 time, int leftLimit, int rightLimit);
	TextTest(string t, Uint32 time, int leftLimit, int rightLimit, LINEJUMP ljump, LINETYPE ltype = LINE_AUTO, TEXTMODE mode = TEXT_NORMAL);
	~TextTest() {};
	void init() override;
	void draw() override;
	void update() override;
	void setText(string t) { fullText_ = t; }
private:
	void advanceText();
	bool changesLine();
	void advanceLine();
	bool autoLineChange();
	void createTexture(int line);
	void wordJump(string& s);
	vector<Texture*> t_;				//Una textura por l�nea
	Font* font_;
	string fullText_;					//Texto que queda por escribir
	vector<string> lines_;				//L�neas de texto
	int currentLine_ = 0;
	int lineSize_ = 50;					//Tama�o de l�nea (solo aplica si LINETYPE = LINE_MANUAL
	Uint32 time_;						//Variable para llevar el tiempo
	Uint32 timePass_ = 1000;			//Tiempo que tiene que pasar para dibujar el siguiente car�cter(en ms)
	TEXTMODE mode_;
	LINETYPE lineType_;
	LINEJUMP jumpType_;
	int leftLimit_ = 0;					//L�mite izquierdo
	int rightLimit_;					//y derecho
	int size_;							//Alto de car�cter
	int w_;								//Ancho objetivo
};

