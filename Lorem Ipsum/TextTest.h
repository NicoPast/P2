#pragma once
#include "SDL_macros.h"
#include "Component.h"
class TextTest : public Component
{
public:
	TextTest(string t);
	TextTest(string t, Uint32 time);
	~TextTest() {};
	void draw() override;
	void update() override;
private:
	void advanceText();
	bool changeLine();
	vector<Texture*> t_;		//Una textura por l�nea
	string fullText_;			//Texto que queda por escribir
	vector<string> lines_;		//L�neas de texto
	int currentLine_ = 0;
	Uint32 time_;				//Variable para llevar el tiempo
	Uint32 timePass_ = 1000;	//Tiempo que tiene que pasar para dibujar el siguiente car�cter(en ms)
};

