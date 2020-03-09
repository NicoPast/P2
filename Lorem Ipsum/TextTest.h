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
	vector<Texture*> t_;
	string fullText_;
	vector<string> lines_;
	int currentLine_ = 0;
	Uint32 time_;
	Uint32 timePass_ = 1000;
};

