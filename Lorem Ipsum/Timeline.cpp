#include "Timeline.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "Rectangle.h"
#include "Sprite.h"
#include "DragTL.h"
Timeline::Timeline(LoremIpsum* g) : State(g)
{
	vector<CentralClue*>cc = game_->getStoryManager()->getPlayerCentralClues();
	for (int i = 0; i < game_->getStoryManager()->getPlayerCentralClues().size(); i++) {
		if (cc[i]->timeline_ && cc[i]->isEvent_) playerEvents_.push_back(cc[i]);		//solo podr� aparecer en la timeline todo evento que est� formado y est� pensado para aparecer en la timeline.
	}
	Entity* bg = entityManager_->addEntity(0);
	bg->addComponent<Transform>(0, 0, 1080, 720);
	bg->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::TextureId::TimelineBG));

	createPanels();
	if (playerEvents_.size() > 0) {
		actualEvent_ = playerEvents_[0];
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
	auto it = find(playerEvents_.begin(), playerEvents_.end(), actualEvent_);
	int i = distance(playerEvents_.begin(), it);
	if (dir) {
		if (i>0) {	//Si no est� en el borde izquierdo, se cambia el evento que se ve al que est� colocado en la izquierda
			upEventEntities_[i]->setActive(false);
			upEventEntities_[i-1]->setActive(true);
			actualEvent_ = playerEvents_[i - 1];
		}
	}
	else {
		if (i < playerEvents_.size()-1) {	//Si no est� en el borde izquierdo, se cambia el evento que se ve al que est� colocado en la izquierda
			upEventEntities_[i]->setActive(false);
			upEventEntities_[i + 1]->setActive(true);
			actualEvent_ = playerEvents_[i+1];
		}
	}
	changeText();
}

void Timeline::eventReleased(Transform* eventTR) {
	SDL_Rect eventRect = RECT(eventTR->getPos().getX(), eventTR->getPos().getY(), eventTR->getW(), eventTR->getH());
	int i = 0; bool found = false;
	while (i < rectPlaceHolders_.size() && !found) {
		if (SDL_HasIntersection(&eventRect, &rectPlaceHolders_[i])) found = true;
		else i++;
	}
	if (found) {
		downEventEntities_.push_back(eventTR->getEntity());
		auto it = find(upEventEntities_.begin(), upEventEntities_.end(), eventTR->getEntity());
		upEventEntities_.erase(it);
	}
	else eventTR->setPos(eventPos_);


}

void Timeline::createEvents() {
	//Aqu� se crea el panel donde salen las pistas y las entidades de las pistas (arriba a la izquierda)
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = 110;
	eventPos_ = Vector2D{ (w / 2) - (eventSize / 2), (h / 2) - (eventSize) };
	for (int i = 0; i < playerEvents_.size(); i++) {
		Entity* event = entityManager_->addEntity(Layers::DragDropLayer);
		Transform* eventTR = event->addComponent<Transform>(eventPos_.getX(), eventPos_.getY(), eventSize, eventSize);
		event->addComponent<Rectangle>(SDL_Color{ COLOR(0xFFFFFFFF) });
		event->addComponent<DragTL>(this, [eventTR](Timeline* tl) { tl->eventReleased(eventTR); });
		event->setActive(false);
		upEventEntities_.push_back(event);
	}
	upEventEntities_[0]->setActive(true);	
	changeText();	//aparece el texto de la primera. El texto cambiar� cada vez que se pulsen los botones que se crear�n a continuaci�n.

	//Aqu� se crean los botones para cambiar la pista que se ve, solamente si hay m�s de una pista disponible
	if (playerEvents_.size() >1) {
		double buttonSize = 30;
		Entity* leftButton = entityManager_->addEntity(2);
		leftButton->addComponent<Transform>(0,0, buttonSize, buttonSize);	//esto ahora funciona pero est� hecho a pelo y mal
		leftButton->addComponent<Rectangle>(SDL_Color{ COLOR(0x000FFFFF) });
		leftButton->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(true); }), this);

		Entity* rightButton = entityManager_->addEntity(2);
		rightButton->addComponent<Transform>(buttonSize, buttonSize,buttonSize, buttonSize);	//esto ahora funciona pero est� hecho a pelo y mal
		rightButton->addComponent<Rectangle>(SDL_Color{ COLOR(0x000FFFFF) });
		rightButton->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(false); }), this);

	}

}
void Timeline::createPanels() {

	//Aqu� se crea el panel que contiene el texto cuando pulsas en un evento
	Entity* textPanel = entityManager_->addEntity(Layers::LastLayer);
	double textPanelW = game_->getGame()->getWindowWidth() / 3;
	double textPanelH = game_->getGame()->getWindowHeight()/3;
	Transform* textPanelTR = textPanel->addComponent<Transform>(textPanelW, 27, textPanelW*2 -27, textPanelH);

	textTitle_ = textPanel->addComponent<Text>("", textPanelTR->getPos(), -1, Resources::RobotoTest24, 0);
	textTitle_->setSoundActive(false);
	textDescription_ = textPanel->addComponent<Text>("", textPanelTR->getPos() + Vector2D(0, 80), textPanelTR->getW(), Resources::RobotoTest24, 0);
	textDescription_->setSoundActive(false);

	//Aqu� se crea el panel inferior, donde se colocar�n los eventos
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = 110;
	vector<CentralClue*> tlEvents;					//Vector que guarda los eventos que aparecer�n en la timeline (en playerEvents_ est�n solo los formados)
	vector<CentralClue*> temp = game_->getStoryManager()->getPlayerCentralClues();
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i]->timeline_) tlEvents.push_back(temp[i]);
	}
	for (int i = 0; i < tlEvents.size(); i++) {//Creamos los rectangulos en los que debemos encajar los eventos
		Entity* r = entityManager_->addEntity(2);
		Transform* rTR = r->addComponent<Transform>(((game_->getGame()->getWindowWidth() / tlEvents.size()) * i)+eventSize, h*2 - eventSize*2, eventSize, eventSize);
		r->addComponent<Rectangle>(SDL_Color{ COLOR(0x01010100) })->setBorder(SDL_Color{ COLOR(0xffffffFF) });
		rectPlaceHolders_.push_back(SDL_Rect RECT(rTR->getPos().getX(), rTR->getPos().getY(), rTR->getW(), rTR->getH()));
	}
}
