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

};

void PlayState::update() 
{
	State::update();
}