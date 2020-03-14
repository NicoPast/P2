#pragma once
#include "SDL_macros.h"
#include "Component.h"
enum TEXTMODE{TEXT_NORMAL, TEXT_TYPEWRITER};		//Texto normal y con el efecto de máquina de escribir
enum LINETYPE{LINE_MANUAL, LINE_AUTO};				//Avance de línea manual o automático
class TextTest : public Component
{
public:
	TextTest(string t);
	TextTest(string t, Uint32 time);
	TextTest(string t, Uint32 time, TEXTMODE mode);
	TextTest(string t, Uint32 time, TEXTMODE mode, LINETYPE ltype, int leftLimit, int rightLimit);
	~TextTest() {};
	void init() override;
	void draw() override;
	void update() override;
private:
	void advanceText();
	bool changesLine();
	void advanceLine();
	bool autoLineChange();
	vector<Texture*> t_;				//Una textura por línea
	Font* font_;
	string fullText_;					//Texto que queda por escribir
	vector<string> lines_;				//Líneas de texto
	int currentLine_ = 0;
	int lineSize_ = 50;					//Tamaño de línea (solo aplica si LINETYPE = LINE_MANUAL
	Uint32 time_;						//Variable para llevar el tiempo
	Uint32 timePass_ = 1000;			//Tiempo que tiene que pasar para dibujar el siguiente carácter(en ms)
	TEXTMODE mode_ = TEXT_NORMAL;
	LINETYPE lineType_ = LINE_MANUAL;
	int leftLimit_ = 0;					//Límite izquierdo
	int rightLimit_;					//y derecho
	int size_;							//Alto de carácter
	int w_;								//Ancho objetivo
};

