#pragma once
#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "Rectangle.h"
#include "Sprite.h"
class Maps : public State
{
public: 
	Maps(LoremIpsum* game);
	virtual ~Maps() {};

	virtual void update() override;
	virtual void render() override;
protected:

private:
	StoryManager* sm_;
	vector<Scene*> availableScenes_;	//Vector con las escenas a las que puedes acceder cuando abres la aplicaci�n
	//IMPORTANTE: Como los botones estar�n colocados en sitios concretos del mapa, cada vez que se a�ada una localizaci�n nueva al juego, hay que a�adir su bot�n correspondiente manualmente.								
	Entity* background_;
	vector<Entity*> buttons_;
};

