#pragma once

#include "FontsManager.h"
#include <map>
#include "Texture.h"
/*
 *
 */
class SDLFontsManager: public FontsManager {
public:
	SDLFontsManager(SDL_Renderer* renderer);
	virtual ~SDLFontsManager();

	// supposed to be called before start using the object
	bool init() override;

	Font* getFont(std::size_t tag) override;
	bool loadFont(std::size_t tag, const string& fileName, int size) override;

	Texture* getGlyphs(std::size_t tag) { return glyphs_[tag]; }
	bool createGlyphs(SDL_Renderer* renderer, std::size_t tag, const Font* font, const SDL_Color& color);
private:
	SDL_Renderer* renderer_;
	map<int, Font*> fonts_;
	bool initialized_;
	map<int, Texture*> glyphs_;
	const char* glyphList_ = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬ ®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ";
};

