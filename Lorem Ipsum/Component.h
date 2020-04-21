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
	bool ui_ = false;
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
	bool isUI() { return ui_; }

	/**	Para hacer que su posición al renderizarse dependa de la camara y no del mundo
	*/
	//void setLocal() { global_ = false; } 
	void setUI() { ui_ = true; }
	void setNonUI() { ui_ = false; }

	virtual void init() {
	}
	virtual void update() {
	}
	virtual void draw() {
	}

};

