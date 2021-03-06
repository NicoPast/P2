#pragma once

#include <iostream>
#include <array>
#include "Component.h"
#include "Manager.h"
#include "SDLGame.h"
#include "State.h"
#include "Transform.h"

class EntityManager;

class Entity {
public:
	Entity(SDLGame *game, State* state);
	virtual ~Entity();

	EntityManager* getEntityMangr() {
		return mngr_;
	}

	template<typename T, typename ... TArgs>
	T* addComponent(TArgs&& ...mArgs) {
		T *c(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Component> uPtr(c);
		components_.push_back(std::move(uPtr));
		componentsArray_[c->getId()] = c;
		c->setEntity(this);
		c->setGame(game_);
		c->init();
		return c;
	}

	template<typename T>
	T* getComponent(ecs::CmpIdType id) {
		return static_cast<T*>(componentsArray_[id]);
	}

	bool hasComponent(ecs::CmpIdType id) {
		return componentsArray_[id] != nullptr;
	}

	void update() {
		for (auto &c : components_) {
			if(c->isEnabled())c->update();
		}
	}

	void draw() {
		for (auto &c : components_) {
			if (c->isEnabled())
				c->draw();
		}
	}
	bool isLastInLayer() {
		return layerIndex_ == (mngr_->getLayerSize(layer_) - 1);
	}
	//Capas de dibujado
	int getLayerIndex() {
		return layerIndex_;
	}
	void setLayerIndex(int index) {
		layerIndex_ = index;
	}
	int getLayer() {
		return layer_;
	}
	void setLayer(int layer) {
		layer_ = layer;
	}
	bool getActive() {
		return active_;
	}
	void setActive(bool actv) {
		active_ = actv;
	}
	//eventually will be game
	State* getState()
	{
		return state_;
	}
	void inline setUI(bool isUI) { UI_ = isUI; }
	bool inline isUI() { return UI_; }
private:
	SDLGame *game_ = nullptr;
	EntityManager* mngr_ = nullptr;
	State* state_ = nullptr;

	std::vector<unique_ptr<Component>> components_;
	std::array<Component*,ecs::maxComponents> componentsArray_ = {};
protected:
	int layer_ = 0;
	int layerIndex_ = 0;
	bool active_ = true;
	bool UI_ = false;
};

