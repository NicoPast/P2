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
		if (cc[i]->timeline_ && cc[i]->isEvent_) upPlayerEvents_.push_back(cc[i]);		//solo podrá aparecer en la timeline todo evento que esté formado y esté pensado para aparecer en la timeline.
	}
	Entity* bg = entityManager_->addEntity(0);
	bg->addComponent<Transform>(0, 0, 1280, 720);
	bg->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::TextureID::TimelineBG));

	createPanels();
	if (upPlayerEvents_.size() > 0) {
		setActualEvent(upPlayerEvents_[0]);
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
	auto it = find(upPlayerEvents_.begin(), upPlayerEvents_.end(), actualEvent_);
	int i = distance(upPlayerEvents_.begin(), it);
	if (dir) {
		if (i>0) {	//Si no está en el borde izquierdo, se cambia el evento que se ve al que esté colocado en la izquierda
			upEventEntities_[i]->setActive(false);
			upEventEntities_[i-1]->setActive(true);
			setActualEvent(upPlayerEvents_[i - 1]);
			changeText();
		}
	}
	else {
		if (it != upPlayerEvents_.end()-1) {	//Si no está en el borde derecho, se cambia el evento que se ve al que esté colocado en la derecha
			upEventEntities_[i]->setActive(false);
			upEventEntities_[i + 1]->setActive(true);
			setActualEvent(upPlayerEvents_[i + 1]);
			changeText();
		}
	}
}
void Timeline::setActualEvent(CentralClue* event) {
	if (actualEvent_ != event) {
		actualEvent_ = event;
	}
}


void Timeline::eventReleased(Entity* event) {

	Transform* eventTR = GETCMP2(event, Transform);
	SDL_Rect eventRect = RECT(eventTR->getPos().getX(), eventTR->getPos().getY(), eventTR->getW(), eventTR->getH());	//Forma un rect para las comprobaciones 
	//Busca si el evento está arriba o abajo
	auto upit = find(upEventEntities_.begin(), upEventEntities_.end(), event);
	if (upit != upEventEntities_.end()) { //Si el evento está arriba
		int i = 0; bool found = false;
		while (i < rectPlaceHolders_.size() && !found) {	//Busca con qué rectangulo de la timeline colisiona
			if (SDL_HasIntersection(&eventRect, &rectPlaceHolders_[i])) found = true;
			else i++;
		}
		if (found) {	//Si colisiona con alguno, lo pone abajo y lo saca de arriba
			//Añade la entidad abajo y la quita de arriba
			eventTR->setPos(rectPlaceHolders_[i].x, rectPlaceHolders_[i].y);
			downEventEntities_.push_back(event);
			auto it = find(upEventEntities_.begin(), upEventEntities_.end(), event);
			if (upEventEntities_.size() >= 2) {
				if (it != upEventEntities_.begin()) { it--;  (*it)->setActive(true); it++; }
				else { it++;  (*it)->setActive(true); it--; }
			}
			upEventEntities_.erase(it); 
		}
		else eventTR->setPos(eventPos_);	//Si no colisiona, lo devuelve a la posición original
	}
	else {//Si el evento está abajo
		int i = 0; bool found = false;
		while (i < rectPlaceHolders_.size() && !found) {	//Busca con qué rectangulo de la timeline colisiona
			if (SDL_HasIntersection(&eventRect, &rectPlaceHolders_[i])) found = true;
			else i++;
		}
		if (found) eventTR->setPos(rectPlaceHolders_[i].x, rectPlaceHolders_[i].y);	//Si colisiona con alguno, lo deja en la posición del rectángulo
		else {	//Si no, colisiona con los rectángulos, lo devuelve a la lista de arriba
			//Añade la entidad arriba y la quita de abajo
			eventTR->setPos(eventPos_);
			upEventEntities_.push_back(event);
			auto it = find(downEventEntities_.begin(), downEventEntities_.end(), event);
			downEventEntities_.erase(it);
		}	
	}
	
	////Aquí tiene que cambiar el panel del texto y desactivar o activar los botones
	//if (upEventEntities_.size() <= 1) {//Si arriba hay menos de un evento
	//	if (leftButton_->getActive()) leftButton_->setActive(false); rightButton_->setActive(false);	//Si los botones están activos, debe desactivarlos
	//	if(upEventEntities_.size() ==1) setActualEvent(playerEvents_[0]);
	//	else {
	//		textDescription_->setText(" ");
	//		textTitle_->setText(" ");
	//	}
	//}
	//else {//Si hay más de un evento arriba
	//	if (!leftButton_->getActive())leftButton_->setActive(true); rightButton_->setActive(true);		//Si los botones están desactivos, debe activarlos
	//	setActualEvent(playerEvents_[0]);
	//}
}

void Timeline::createEvents() {
	//Aquí se crea el panel donde salen las pistas y las entidades de las pistas (arriba a la izquierda)
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = 110;
	eventPos_ = Vector2D{ (w / 2) - (eventSize / 2), (h / 2) - (eventSize) };
	for (int i = 0; i < upPlayerEvents_.size(); i++) {
		CentralClue* e = upPlayerEvents_[i];
		Entity* event = entityManager_->addEntity(Layers::DragDropLayer);
		Transform* eventTR = event->addComponent<Transform>(eventPos_.getX(), eventPos_.getY(), eventSize, eventSize);
		event->addComponent<Rectangle>(SDL_Color{ COLOR(0xFFFFFFFF) });
		event->addComponent<DragTL>(this, [](Timeline* tl, Entity* e) { tl->eventReleased(e); });
		event->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([e](Timeline* tl) {tl->setActualEvent(e); tl->changeText(); }), this);
		event->setActive(false);
		upEventEntities_.push_back(event);
	}
	upEventEntities_[0]->setActive(true);	

	//Aquí se crean los botones para cambiar la pista que se ve, solamente si hay más de una pista disponible
	if (upPlayerEvents_.size() >1) {
		double buttonSize = 30;
		leftButton_ = entityManager_->addEntity(2);
		leftButton_->addComponent<Transform>(0,0, buttonSize, buttonSize);	//esto ahora funciona pero está hecho a pelo y mal
		leftButton_->addComponent<Rectangle>(SDL_Color{ COLOR(0x000FFFFF) });
		leftButton_->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(true); }), this);

		rightButton_ = entityManager_->addEntity(2);
		rightButton_->addComponent<Transform>(buttonSize, buttonSize,buttonSize, buttonSize);	//esto ahora funciona pero está hecho a pelo y mal
		rightButton_->addComponent<Rectangle>(SDL_Color{ COLOR(0x000FFFFF) });
		rightButton_->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(false); }), this);

	}

}
void Timeline::createPanels() {

	//Aquí se crea el panel que contiene el texto cuando pulsas en un evento
	Entity* textPanel = entityManager_->addEntity(Layers::LastLayer);
	double textPanelW = game_->getGame()->getWindowWidth() / 3;
	double textPanelH = game_->getGame()->getWindowHeight()/3;
	Transform* textPanelTR = textPanel->addComponent<Transform>(textPanelW, 27, textPanelW*2 -27, textPanelH);

	textTitle_ = textPanel->addComponent<Text>("", textPanelTR->getPos(), -1, Resources::RobotoTest24, 0);
	textTitle_->setSoundActive(false);
	textDescription_ = textPanel->addComponent<Text>("", textPanelTR->getPos() + Vector2D(0, 80), textPanelTR->getW(), Resources::RobotoTest24, 0);
	textDescription_->setSoundActive(false);

	//Aquí se crea el panel inferior, donde se colocarán los eventos
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = 110;
	vector<CentralClue*> tlEvents;					//Vector que guarda los eventos que aparecerán en la timeline (en playerEvents_ están solo los formados)
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
