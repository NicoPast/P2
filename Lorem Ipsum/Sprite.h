#pragma once
#include "Component.h"
#include "Transform.h"
class Sprite
	: public Component
{
public:
	Sprite(Texture* texture);
	Sprite();
	virtual ~Sprite() {};
	virtual void draw() override;
	virtual void init() override;
	inline void setTexture(Texture* texture) { texture_ = texture; sourceRect_ = { 0, 0, texture_->getWidth(), texture_->getHeight() }; };
	inline void setTexture(Resources::TextureID texture) { texture_ = game_->getTextureMngr()->getTexture(texture); sourceRect_ = { 0, 0, texture_->getWidth(), texture_->getHeight() }; };
	inline void setSubTexture(Resources::TextureID texture) {subTexture_ = game_->getTextureMngr()->getTexture(texture); sourceRect_ = { 0, 0, texture_->getWidth(), texture_->getHeight() }; };
	inline void setSourceRect(SDL_Rect clip) { sourceRect_ = clip; };
	inline void showSubtexture(bool show) { showSubtexture_ = show; }
	inline void setTint(int r, int g, int b) { r_ = r; g_ = g; b_ = b; }
	inline void clearTint() { r_ = 255; g_ = 255; b_ = 255; }
	inline void setBorder(SDL_Color c) { borderColor_ = c; }
	void ignoreCamera(bool b) { ignoreCamera_ = b; }
	void inline flipHor(bool flip) { isflipH_ = flip; };
	void inline flipVer(bool flip) { isflipV_ = flip; };
private:
	Transform* tr_ = nullptr;
	Texture* texture_ = nullptr;
	Texture* subTexture_ = nullptr;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
	SDL_Rect sourceRect_ = {};
	bool ignoreCamera_ = false;
	int r_ = 255;
	int g_ = 255;
	int b_ = 255;
	SDL_Color borderColor_ = {0,0,0,0};
	bool showSubtexture_ = false;
	bool isflipH_ = false;
	bool isflipV_ = false;

};