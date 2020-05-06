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
	void updateEvents();		//A este método habría que llamarlo cada vez que se haga un evento en el chinchetario (si se ha creado una timeline)
	bool getFinished() { return (downPlayerEvents_.size() == nEvents_); }			//getFinished es para desbloquear el momento sherlock holmes
	bool getCorrectEvents();	//Estos dos métodos devuelven las condiciones de victoria. Lo que conlleve esa victoria (aka hacer gameCase++ en storyManager y mas cosas) lo hará el que llame a esto
	bool getCorrectOrder();
	void resetTimeline(); //A este método habría que llamarlo una vez el momento sherlock holmes te diga que no es correcto, para resetear los eventos erroneos (esto también los resetea en el chinchetario)
private:
	void createEvent(CentralClue* cc);
	void createButtons();
	void updateButtons();
	void createPanels();
	void changeText();
	void moveActualEvent(bool dir);
	void setActualEvent(CentralClue* event);
	void eventReleased(Entity* event);
	void eventClicked(CentralClue* cc);
	void moveDown(Entity* event, int pos);
	void moveUp(Entity* event);
	void deleteUpEvent(Entity* event);
	void deleteDownEvent(Entity* event);
	Vector2D eventPos_;
	Entity* leftButton_ = nullptr, * rightButton_ = nullptr;
	vector<CentralClue*> upPlayerEvents_;		//información de las pistas principales (saber si tienen un evento formado, si es correcto, si deben estar en la timeline...)
	vector<CentralClue*> downPlayerEvents_;		//información de las pistas principales (saber si tienen un evento formado, si es correcto, si deben estar en la timeline...)
	vector<Entity*> upEventEntities_;
	vector<Entity*> downEventEntities_;
	vector<SDL_Rect> rectPlaceHolders_;
	CentralClue* actualEvent_;						//evento que se ve en el panel donde escoges el evento a arrastrar
	Text* textTitle_, * textDescription_;			//contenedores de la info del evento en pantalla
	int nEvents_ = 0;	//número de eventos que llenan la timeline
};

