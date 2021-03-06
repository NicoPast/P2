#pragma once

#include <SDL.h>
#include "Font.h"
#include <string>

using namespace std;

class Texture {
public:
	Texture();
	Texture(SDL_Renderer *renderer, const string& fileName);
	Texture(SDL_Renderer *renderer, const string& text, const Font *font,
			const SDL_Color& color);
	virtual ~Texture();

	inline int getWidth() {
		return width_;
	}

	inline int getHeight() {
		return height_;
	}

	inline bool isReady() {
		return texture_ != nullptr;
	}

	// load from image or text, in both cases we should provide a rendered
	bool loadFromImg(SDL_Renderer *renderer, const string& fileName);
	bool loadFromText(SDL_Renderer *renderer, const string& text, const Font *font,
			const SDL_Color& color = { 0, 0, 0, 255 });

	// render the complete texture at position (x,y).
	void render(int x, int y) const;

	// render part of the texture (clip) to a destination rectangle, if no
	// clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect &dest) const;
	void render(const SDL_Rect &dest, const SDL_Rect& clip) const;

	// render part of the texture (clip) to a destination rectangle with a rotation,
	// if no clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect &dest, double angle,	const SDL_Rect &clip) const;
	void render(const SDL_Rect &dest, double angle) const;

	void flipHorizontal(bool flip);
	void flipVertical(bool flip);
	bool inline isFlippedHorizontally() { return flip_ == SDL_FLIP_HORIZONTAL; };
	bool inline isFlippedVertically() { return flip_ == SDL_FLIP_VERTICAL; };
	void inline setFlip(SDL_RendererFlip flip) { flip_ = flip; };
	SDL_RendererFlip inline getFlip() { return flip_; };

	void close();

	void setColorMod(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(texture_, r, g, b); }
	void setPivotPoint(SDL_Point p) { pivot_ = p; }

	void inline setBlendingMode(SDL_BlendMode mode) { SDL_SetTextureBlendMode(texture_, mode); };
	
private:
	SDL_Texture* texture_ = nullptr;
	SDL_Renderer *renderer_ = nullptr;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
	int width_ = 0;
	int height_ = 0;
	SDL_Point pivot_ = SDL_Point();
};


/*



*/