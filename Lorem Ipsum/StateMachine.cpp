#include "StateMachine.h"

void StateMachine::PlayApp(APPS app, StoryManager* storyManager) {
	switch (app) {
		case APPS::Contacts:
			//añade el state de la aplicación Contactos
			break;
		case APPS::Maps:
			//añade el state de la aplicación Maps
			break;
		case APPS::Options:
			//añade el state de la aplicación Options
			break;
		case APPS::Chinchetario:
			//añade el state de la aplicación Chinchetario
			states_.push(new Chinchetario(game_, storyManager));
			break;
	}

	InputHandler::instance()->clearState();
}