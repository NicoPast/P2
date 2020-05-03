#pragma once
#include <functional>
#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "Text.h"
//using callbackInteractbale = void(Entity* player, Entity* other);
class Entity;
class Interactable : public Component {
public:
	Interactable();
	virtual ~Interactable();
	void init() override;
	void update() override {
		if (colliding_) {
			//if (text_ != nullptr) text_->setText(name_);
			if (InputHandler::instance()->isKeyDown(SDLK_e))
			{
				if (function_ != nullptr)callback();
			}
		}
		//else if (text_ != nullptr) text_->resetText();
	};
	void changeColl(bool coll) { colliding_ = coll; };
	bool getColl() { return colliding_; };
	Transform* GetTransform() { return tr_; };

	Resources::TextureID inline getIcon() { return iconInfo_; }
	void inline setIcon(Resources::TextureID icon) { iconInfo_ = icon; }

	void setPlayer(Entity* p) { player_ = p; }
	void setOther(Entity* o) { other_= o; }
	inline Entity* getOther() { return other_; }
	void setCallback(std::function<void(Entity*, Entity*)> cb, Entity* o = nullptr) { function_ = cb; if (o != nullptr)other_ = o; };
	std::function<void(Entity*, Entity*)> getCallback() { return function_; }


private:	
	std::function<void(Entity*, Entity*)> function_ = nullptr;
	void callback()
	{
		if(function_)function_(player_, other_);
		colliding_ = false;
	}

	//si colisionan estos apuntaran a lo que toque
	Entity* player_=nullptr; 
	Entity* other_= nullptr;

	Transform* tr_;
	bool colliding_;
	Text* text_;
	Resources::TextureID iconInfo_;

	friend class InteractableLogic;
};

