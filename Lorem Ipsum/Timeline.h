#pragma once
#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "Drag.h"
class Timeline : public State
{
public:
	Timeline(LoremIpsum* g);
	virtual ~Timeline() {};
	virtual void update() override;
	virtual void render() override;
private:
	void createEvents();
	void createPanels();
	void changeText();
	void moveActualEvent(bool dir);
	void eventReleased(Transform* eventTR);
	Vector2D eventPos_;
	vector<CentralClue*> playerEvents_;		//información de las pistas principales (saber si tienen un evento formado, si es correcto, si deben estar en la timeline...)
	vector<Entity*> upEventEntities_;
	vector<Entity*> downEventEntities_;
	vector<SDL_Rect> rectPlaceHolders_;
	CentralClue* actualEvent_;						//evento que se ve en el panel donde escoges el evento a arrastrar
	Text* textTitle_, * textDescription_;			//contenedores de la info del evento en pantalla
};

