#pragma once

#include <SDL_ttf.h>
#include <string>

using namespace std;

class Font {
public:
	Font();
	Font(const string& fileName, int size);
	virtual ~Font();

	bool load(const string& fileName, int size);
	void close();
	SDL_Surface* renderText(const string& text, SDL_Color color) const;

	int getSize() { return size_; }
	TTF_Font* getTTF_Font() { return font_; }
private:
	TTF_Font *font_;

	int size_;
};
