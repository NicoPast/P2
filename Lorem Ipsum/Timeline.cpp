#include "Timeline.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "Rectangle.h"
#include "Sprite.h"

Timeline::Timeline(LoremIpsum* g) : State(g)
{
	vector<CentralClue*>cc = game_->getStoryManager()->getPlayerCentralClues();
	for (int i = 0; i < game_->getStoryManager()->getPlayerCentralClues().size(); i++) {
		if (cc[i]->timeline_ && cc[i]->isEvent_) playerTimelineClues_.push_back(cc[i]);		//solo podrá aparecer en la timeline todo evento que esté formado y esté pensado para aparecer en la timeline.
	}
	Entity* bg = entityManager_->addEntity(0);
	bg->addComponent<Transform>(0, 0, 1080, 720);
	bg->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::TextureId::TimelineBG));


	if (playerTimelineClues_.size() > 0) {
		actualEvent_ = playerTimelineClues_[0];
		createTextPanel();
		createEvents();
	}
}

void Timeline::update()
{
	State::update();
}

void Timeline::render()
{
	State::render();
}

void Timeline::changeText() {
	textDescription_->setText(actualEvent_->actualDescription_);
	textTitle_->setText(actualEvent_->title_);	
}

void Timeline::moveActualEvent(bool dir) {
	//true = mover a la izquierda, false = mover a la derecha
	auto it = find(playerTimelineClues_.begin(), playerTimelineClues_.end(), actualEvent_);
	int i = distance(playerTimelineClues_.begin(), it);
	if (dir) {
		if (i>0) {	//Si no está en el borde izquierdo, se cambia el evento que se ve al que esté colocado en la izquierda
			actualEvent_ = playerTimelineClues_[i - 1];
		}
	}
	else {
		if (i < playerTimelineClues_.size()-1) {	//Si no está en el borde izquierdo, se cambia el evento que se ve al que esté colocado en la izquierda
			actualEvent_ = playerTimelineClues_[i+1];
		}
	}
	changeText();
}

void Timeline::createEvents() {
	//Aquí se crea el panel donde salen las pistas y las entidades de las pistas (arriba a la izquierda)
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = 110;
	for (int i = 0; i < playerTimelineClues_.size(); i++) {
		Entity* clue = entityManager_->addEntity(Layers::DragDropLayer);
		clue->addComponent<Transform>((w / 2) - (eventSize / 2), (h / 2) - (eventSize), eventSize, eventSize);
		clue->addComponent<Rectangle>(SDL_Color{ COLOR(0xFFFFFFFF) });
	}
	changeText();	//aparece el texto de la primera. El texto cambiará cada vez que se pulsen los botones que se crearán a continuación.

	//Aquí se crean los botones para cambiar la pista que se ve, solamente si hay más de una pista disponible
	if (playerTimelineClues_.size() >1) {
		double buttonSize = 30;
		Entity* leftButton = entityManager_->addEntity(2);
		leftButton->addComponent<Transform>(0,0, buttonSize, buttonSize);	//esto ahora funciona pero está hecho a pelo y mal
		leftButton->addComponent<Rectangle>(SDL_Color{ COLOR(0x000FFFFF) });
		leftButton->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(true); }), this);

		Entity* rightButton = entityManager_->addEntity(2);
		rightButton->addComponent<Transform>(buttonSize, buttonSize,buttonSize, buttonSize);	//esto ahora funciona pero está hecho a pelo y mal
		rightButton->addComponent<Rectangle>(SDL_Color{ COLOR(0x000FFFFF) });
		rightButton->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(false); }), this);

	}

}
void Timeline::createTextPanel() {

	//Aquí se crea el panel que contiene el texto cuando pulsas en un evento
	Entity* textPanel = entityManager_->addEntity(Layers::LastLayer);
	double textPanelW = game_->getGame()->getWindowWidth() / 3;
	double textPanelH = game_->getGame()->getWindowHeight()/3;
	Transform* textPanelTR = textPanel->addComponent<Transform>(textPanelW, 27, textPanelW*2 -27, textPanelH);

	textTitle_ = textPanel->addComponent<Text>("", textPanelTR->getPos(), -1, Resources::RobotoTest24, 0);
	textTitle_->setSoundActive(false);
	textDescription_ = textPanel->addComponent<Text>("", textPanelTR->getPos() + Vector2D(0, 80), textPanelTR->getW(), Resources::RobotoTest24, 0);
	textDescription_->setSoundActive(false);
}
