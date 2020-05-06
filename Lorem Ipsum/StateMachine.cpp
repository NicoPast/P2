#include "StateMachine.h"
#include "Chinchetario.h"
#include "Maps.h"
#include "Tuner.h"
#include "Options.h"
#include "Timeline.h"
void StateMachine::PlayApp(APPS app, StoryManager* storyManager) {
	switch (app) {
		case APPS::ContactsApp:
			//a�ade el state de la aplicaci�n Contactos
			break;
		case APPS::MapsApp:
			//a�ade el state de la aplicaci�n Maps
			states_.push(new Maps(game_));
			break;
		case APPS::OptionsApp:
			//a�ade el state de la aplicaci�n Options
			states_.push(new Options(game_));
			break;
		case APPS::ChinchetarioApp:
			//a�ade el state de la aplicaci�n Chinchetario
			if (ch_ == nullptr)
				ch_ = new Chinchetario(game_);
			states_.push(ch_);
			break;
		case APPS::TunerApp:
			//a�ade el state de la aplicaci�n Tuner
			states_.push(new Tuner(game_));
			break;
		case APPS::TimelineApp:
			//a�ade el state de la aplicaci�n Timeline
			if (tl_ == nullptr)
				tl_ = new Timeline(game_);
			states_.push(tl_);
			break;
	}

	InputHandler::instance()->clearState();
}