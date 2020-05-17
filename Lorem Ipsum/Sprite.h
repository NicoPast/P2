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
	inline void setSourceRect(SDL_Rect clip) { sourceRect_ = clip; };
	inline void setTint(int r, int g, int b) { r_ = r; g_ = g; b_ = b; }
	inline void clearTint() { r_ = 255; g_ = 255; b_ = 255; }
	inline void setBorder(SDL_Color c) { borderColor_ = c; }
	void ignoreCamera(bool b) { ignoreCamera_ = b; }
private:
	Transform* tr_ = nullptr;
	Texture* texture_ = nullptr;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
	SDL_Rect sourceRect_ = {};
	bool ignoreCamera_ = false;
	int r_ = 255;
	int g_ = 255;
	int b_ = 255;
	SDL_Color borderColor_ = {0,0,0,0};

};