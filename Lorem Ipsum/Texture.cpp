#include "Texture.h"
#include <SDL_image.h>

#include <iostream>

using namespace std;

Texture::Texture() :
	texture_(nullptr), renderer_(nullptr), width_(0), height_(0), pivot_({ 0, 0 }) {
	flip_ = SDL_FLIP_NONE;
}

Texture::Texture(SDL_Renderer *renderer, const string& fileName) :
		texture_(nullptr), width_(0), height_(0), pivot_({ 0, 0 }) {
	loadFromImg(renderer, fileName);
	flip_ = SDL_FLIP_NONE;
}

Texture::Texture(SDL_Renderer *renderer, const string& text, const Font *font,
		const SDL_Color& color) :
		texture_(nullptr), width_(0), height_(0), pivot_({ 0, 0 }) {
	loadFromText(renderer, text, font, color);
	flip_ = SDL_FLIP_NONE;
}

Texture::~Texture() {
	close();
}

void Texture::close() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_); // delete current texture
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
		pivot_ = { 0, 0 };
	}
}

bool Texture::loadFromImg(SDL_Renderer *renderer, const string& fileName) {
	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (surface != nullptr) {
		close(); // destroy current texture
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		//SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xAF, 0xCA));
		if (texture_ != nullptr) {
			width_ = surface->w;
			height_ = surface->h;
			pivot_ = { width_ / 2, height_ / 2 };
		}
		SDL_FreeSurface(surface);
	} else {
		throw "Couldn't load image: " + fileName;
	}
	renderer_ = renderer;
	return texture_ != nullptr;
}

bool Texture::loadFromText(SDL_Renderer *renderer, const string& text, const Font *font,
		const SDL_Color& color) {
	SDL_Surface *textSurface = font->renderText(text, color);
	if (textSurface != nullptr) {
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture_ != nullptr) {
			width_ = textSurface->w;
			height_ = textSurface->h;
			pivot_ = { width_ / 2, height_ / 2 };
		}
		SDL_FreeSurface(textSurface);
	} else {
		throw "Couldn't create text: " + text;
	}
	renderer_ = renderer;
	return texture_ != nullptr;
}

void Texture::render(int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;
	render(dest);
}

void Texture::render(const SDL_Rect &dest, const SDL_Rect& clip) const {
	if (texture_) {
		SDL_RenderCopyEx(renderer_, texture_, &clip, &dest, 0, &pivot_, flip_);
	}
}

void Texture::render(const SDL_Rect &dest) const {
	SDL_Rect clip = {0, 0, width_, height_ };
	render(dest, clip);
}


void Texture::render(const SDL_Rect &dest, double angle,
		const SDL_Rect &clip) const {
	if (texture_) {
		SDL_RenderCopyEx(renderer_, texture_, &clip, &dest, angle, &pivot_,
				flip_);
	}
}

void Texture::render(const SDL_Rect &dest, double angle) const {
	SDL_Rect clip = {0, 0, width_, height_ };
	render(dest, angle, clip);
}
//asi que haha dunno
//supongo que es por el spritesheet, ni idea

void Texture::flipHorizontal(bool flip)
{
	if (flip)
		flip_ = SDL_FLIP_HORIZONTAL;
	else
		flip_ = SDL_FLIP_NONE;
}

void Texture::flipVertical(bool flip)
{
	if (flip)
		flip_ = SDL_FLIP_VERTICAL;
	else
		flip_ = SDL_FLIP_NONE;
}