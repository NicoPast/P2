#include "StateMachine.h"
#include "Chinchetario.h"

void StateMachine::PlayApp(APPS app, StoryManager* storyManager) {
	switch (app) {
		case APPS::Contacts:
			//a�ade el state de la aplicaci�n Contactos
			break;
		case APPS::Maps:
			//a�ade el state de la aplicaci�n Maps
			break;
		case APPS::Options:
			//a�ade el state de la aplicaci�n Options
			break;
		case APPS::ChinchetarioApp:
			//a�ade el state de la aplicaci�n Chinchetario
			states_.push(new Chinchetario(game_));
			break;
	}

	InputHandler::instance()->clearState();
}