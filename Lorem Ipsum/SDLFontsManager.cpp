#include "SDLFontsManager.h"
#include <assert.h>
#include "SDL_macros.h"
#include <iostream>
SDLFontsManager::SDLFontsManager(SDL_Renderer* renderer) :
	initialized_(false), renderer_(renderer) {
}

SDLFontsManager::~SDLFontsManager() {
	if (!initialized_)
		return;

	// free all sound effect chucks
	for (const auto& font : fonts_) {
		if (font.second != nullptr)
			delete font.second;
	}
	for (const auto& glyph : glyphs_) {
		if (glyph.second != nullptr)
			delete glyph.second;
	}
	TTF_Quit();
}

bool SDLFontsManager::init() {
	if (initialized_)
		return false;

	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);
	/*
	 if ( r != 0 ) {
	 throw "Something went wrong with TTF_init";
	 }
	 */
	initialized_ = true;

	return true;
}

Font* SDLFontsManager::getFont(std::size_t tag) {
	return fonts_[tag];
}

bool SDLFontsManager::loadFont(std::size_t tag, const string& fileName, int size) {
	if (!initialized_)
		return false;

	Font* font = new Font();
	if (font->load(fileName, size)) {
		Font* curr = fonts_[tag];
		if (curr != nullptr)
			delete curr;
		fonts_[tag] = font;
		if (createGlyphs(renderer_, tag, font, SDL_Color({ COLOR(0xFFFFFFFF) })))
			return true;
		else {
			delete font;
			return false;
		}
	}
	else {
		delete font;
		return false;
	}
}

bool SDLFontsManager::createGlyphs(SDL_Renderer* renderer, std::size_t tag, const Font* font, const SDL_Color& color) {
	if (!initialized_)
		return false;
	Texture* texture = new Texture();
	texture->loadFromText(renderer, glyphList_, font, color);
	if (texture->isReady()) {
		glyphs_[tag] = texture;
		return true;
	}

	// if we get here something went wrong
	return false;

}
