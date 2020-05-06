#pragma once
#include "State.h"
class MainMenu :
	public State
{
public:
	MainMenu(LoremIpsum* game);
	virtual ~MainMenu() {  }
	virtual void update() override;
private:
	void init();
	void createBackground();
	Entity* buildingLine3=nullptr;
	Entity* buildingLine2=nullptr;
	Entity* buildingLine1=nullptr;

	Entity* buildingLine3r = nullptr;
	Entity* buildingLine2r = nullptr;
	Entity* buildingLine1r = nullptr;
	vector<Entity*>buildings;
	uint32_t lastMove = 0;
	uint32_t speed = 15;
};

