#include "StateMachine.h"
#include "Chinchetario.h"
#include "Maps.h"

void StateMachine::PlayApp(APPS app, StoryManager* storyManager) {
	switch (app) {
		case APPS::Contacts:
			//a�ade el state de la aplicaci�n Contactos
			break;
		case APPS::Maps:
			//a�ade el state de la aplicaci�n Maps
			states_.push(new Maps(game_));
			break;
		case APPS::Options:
			//a�ade el state de la aplicaci�n Options
			break;
		case APPS::Chinchetario:
			//a�ade el state de la aplicaci�n Chinchetario
			states_.push(new Chinchetario(game_));
			break;
	}

	InputHandler::instance()->clearState();
}