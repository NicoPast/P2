#include "PlayState.h"
#include "LoremIpsum.h"
#include "Interactable.h"
#include "InteractableLogic.h"

#include "StoryManager.h"


PlayState::PlayState(LoremIpsum* game) : State(game) {
	
	//CAMARAS
	//SETTERS
	// PLZ
	//	|
	//	|
	//	|
	//	↓
	//camera_ = new Camera(0, 0, 1080, 720, 50, 50);
};
void PlayState::init() {
	//sm_->changeScene(SceneIDs::calleProfesor);
	game_->changeScene(Resources::SceneID::EntradaDespacho);
	LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("Bienvenido al tutorial, mu\u00e9vete con [A] y [D], interactua con [E] y avanza di\u00e1logos con [ENTER]. O directamente usa el rat\u00f3n.");
};

void PlayState::update() 
{
	State::update();
}