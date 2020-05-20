#pragma once
#include "Manager.h"
#include "Camera.h"
#include "checkML.h"
#include <functional>
class LoremIpsum;

class State
{
protected:

	LoremIpsum* game_ = nullptr;
	EntityManager* entityManager_ = nullptr;

	bool active_ = true;
	Camera* camera_ = nullptr;
	Entity* popUpMessage_ = nullptr;

public:
	State(LoremIpsum* game);
	virtual ~State() { delete entityManager_; delete camera_;	};
	EntityManager* getEntityManager() { return entityManager_; };
	virtual void update();
	virtual void render();

	void showPopUpMessage(string text, std::function<void(int)> f = nullptr);

	void hidePopUpMessage();


	Camera* getCamera() { return camera_; }
	bool isActive() { return active_; }
	void activate() { active_ = true; }
	void deactivate() { active_ = false; }
	void destroy();
};

