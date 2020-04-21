#include "StateMachine.h"
#include "Chinchetario.h"
#include "Tuner.h"
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
			states_.push(new Chinchetario(game_));
			break;
		case APPS::Tuner:
			//añade el state de la aplicación Tuner
			states_.push(new Tuner(game_));
			break;
	}

	InputHandler::instance()->clearState();
}