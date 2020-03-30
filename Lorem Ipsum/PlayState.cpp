#include "PlayState.h"
#include "LoremIpsum.h"
#include "Interactable.h"
#include "InteractableLogic.h"

#include "StoryManager.h"


PlayState::PlayState(LoremIpsum* game) : State(game) {
	init();
};
void PlayState::init() {
	sm_.reset(new StoryManager(game_, entityManager_));
	sm_->changeScene(SceneIDs::calleProfesor);
};

void PlayState::update() 
{
	InputHandler* ih= InputHandler::instance();
	if(ih->keyDownEvent())
	{
		if(ih->isKeyDown(SDLK_l))
		{
			sm_->changeScene(SceneIDs::Casa_Del_Profesor);
		}
	}
	State::update();
}