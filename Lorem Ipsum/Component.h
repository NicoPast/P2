#pragma once
#include <SDL.h>
#include "ecs.h"
#include "SDLGame.h"

class Entity;


class Component {
protected:
	Entity* entity_;
	SDLGame* game_;
	ecs::CmpId id_;
	bool enabled_;
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

	virtual void init() {
	}
	virtual void update() {
	}
	virtual void draw() {
	}

};

