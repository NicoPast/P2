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
	void update() override;
	void changeColl(bool coll) { colliding_ = coll; };
	bool getColl() { return colliding_; };
	Transform* GetTransform() { return tr_; };

	Resources::TextureID inline getIcon() { return iconInfo_; }
	void inline setIcon(Resources::TextureID icon) { iconInfo_ = icon; }

	void setPlayer(Entity* p) { player_ = p; }
	void setOther(Entity* o) { other_= o; }
	inline Entity* getOther() { return other_; }
	void setCallback(std::function<void(Entity*, Entity*)> cb, Entity* o = nullptr) { f_ = cb; if (o != nullptr)other_ = o; };
	std::function<void(Entity*, Entity*)> getCallback() { return f_; }


private:	
	std::function<void(Entity*, Entity*)> f_ = nullptr;
	void callback()
	{
		if(f_)f_(player_, other_);
		colliding_ = false;
	}

	//si colisionan estos apuntaran a lo que toque
	Entity* player_=nullptr; 
	Entity* other_= nullptr;

	Transform* tr_ = nullptr;
	bool colliding_ = false;
	Text* text_ = nullptr;
	Resources::TextureID iconInfo_ = Resources::TextureID::Blank;

	friend class InteractableLogic;
};

