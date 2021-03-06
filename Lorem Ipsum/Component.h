#pragma once
#include <SDL.h>
#include "ecs.h"
#include "SDLGame.h"

class Entity;


class Component {
protected:
	Entity* entity_ = nullptr;
	SDLGame* game_ = nullptr;
	ecs::CmpId id_;
	bool enabled_ = true;
public:
	Component(ecs::CmpId id);
	virtual ~Component();

	void setEntity(Entity* entity) {
		entity_ = entity;
	}
	virtual Entity* getEntity() {
		return entity_;
	}

	void setGame(SDLGame* game) {
		game_ = game;
	}

	void setId(ecs::CmpId id) {
		id_ = id;
	}


	ecs::CmpId getId() const {
		return id_;
	}

	void setEnabled(bool e) { enabled_ = e; }
	bool isEnabled() { return enabled_; }

	/**	Para hacer que su posici�n al renderizarse dependa de la camara y no del mundo
	*/
	//void setLocal() { global_ = false; } 

	virtual void init() {
	}
	virtual void update() {
	}
	virtual void draw() {
	}

};

