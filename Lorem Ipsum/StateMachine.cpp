#include "StateMachine.h"
#include "Chinchetario.h"
#include "Maps.h"

void StateMachine::PlayApp(APPS app, StoryManager* storyManager) {
	switch (app) {
		case APPS::ContactsApp:
			//añade el state de la aplicación Contactos
			break;
		case APPS::MapsApp:
			//añade el state de la aplicación Maps
			states_.push(new Maps(game_));
			break;
		case APPS::OptionsApp:
			//añade el state de la aplicación Options
			break;
		case APPS::ChinchetarioApp:
			//añade el state de la aplicación Chinchetario
			if (ch_ == nullptr)
				ch_ = new Chinchetario(game_);
			states_.push(ch_);
			break;
	}

	InputHandler::instance()->clearState();
}