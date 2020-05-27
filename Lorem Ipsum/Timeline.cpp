#include "Timeline.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "Rectangle.h"
#include "Sprite.h"
#include "DragTL.h"
Timeline::Timeline(LoremIpsum* g) : State(g)
{
	showPopUpMessage("Esto es la l\u00ednea de tiempo. Aqu\u00ed, ver\u00e1s los eventos importantes que han ocurrido en el caso. Arr\u00e1stralos y col\u00f3calos en orden para montar tu hip\u00f3tesis, y en cuanto creas que has acabado, podr\u00e1s acusar a los culpables.");
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = game_->getGame()->getWindowWidth() / 9;
	eventPos_ = Vector2D{ (w / 2) - (eventSize / 2), (h / 2) - (eventSize) };

	Entity* bg = entityManager_->addEntity(0);
	bg->addComponent<Transform>(0, 0, 1280, 720);
	bg->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::TextureID::TimelineBG));

	nEvents_ = 4; //tenemos cuatro pistas principales en este caso

	downPlayerEvents_.resize(nEvents_);
	downEventEntities_.resize(nEvents_);
	createButtons();
	createPanels();
	Transform* tr = GETCMP2(textPanel_, Transform);
	auto tex = SDLGame::instance()->getTextureMngr()->getTexture(Resources::AcursarButton);
	presentCaseButton_ = entityManager_->addEntity(2);
	presentCaseButton_->addComponent<Transform>(tr->getPos().getX()+ (tr->getW()/2) , tr->getPos().getY() + tr->getH(),tex->getWidth()/2, tex->getHeight()/3);
	auto s = presentCaseButton_->addComponent<Sprite>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::AcursarButton));
	s->setSourceRect({ 0, 0,tex->getWidth(), tex->getHeight() / 2 });
	presentCaseButton_->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) {
		if (tl->getFinished())
		{
			StoryManager::instance()->presentCase();
		};
}), this);
	updateEvents();
}

void Timeline::updateEvents() {
	//Actualiza los eventos que salen en la timeline y su información en el panel si es necesario
	vector<CentralClue*>cc = game_->getStoryManager()->getPlayerCentralClues();
	for (int i = 0; i < cc.size(); i++) {
		if (cc[i]->timeline_ && cc[i]->isEvent_) 
		{
			auto it = find(upPlayerEvents_.begin(), upPlayerEvents_.end(), cc[i]);
			auto it2 = find(downPlayerEvents_.begin(), downPlayerEvents_.end(), cc[i]);
			if (it == upPlayerEvents_.end()) {
				if (it2 == downPlayerEvents_.end()) //Si no está ni arriba ni abajo, lo añade arriba. Si no lo encuentra, no lo añade
				{
					upPlayerEvents_.push_back(cc[i]);		//solo podrá aparecer en la timeline todo evento que esté formado y esté pensado para aparecer en la timeline.
					createEvent(cc[i]);
				}
				//else eventClicked(cc[i]);
			}	
		}
	}
	//Si en el caso de que al actualizar, algún evento se haya borrado en el chinchetario, debe eliminar la entidad también
	for (int i = 0; i < downPlayerEvents_.size(); i++) {
		if (downPlayerEvents_[i] != nullptr && !downPlayerEvents_[i]->isEvent_) 
		{
			setActualEvent(downPlayerEvents_[i]);
			downEventEntities_[i]->setActive(false); //Esto deberia hacerse eliminadolas creo pero no he conseguido hacer bien los deletes y eso
			deleteDownEvent(downEventEntities_[i], downPlayerEvents_[i]);
		}
	}
	for (int i = 0; i < upPlayerEvents_.size(); i++) {
		if (!upPlayerEvents_[i]->isEvent_) {
			setActualEvent(upPlayerEvents_[i]);
			upEventEntities_[i]->setActive(false);
			deleteUpEvent(upEventEntities_[i], upPlayerEvents_[i]); i--;
		}
	}
	//Pone como evento actual un evento de arriba si es que lo hay. Si no hay, el evento actual se colocara cuando se haga click en alguna pista que esté abajo
	if (upEventEntities_.size() > 0) 
	{
		eventClicked(upPlayerEvents_[0]);
		upEventEntities_[0]->setActive(true);
	} 
	else {
		textDescription_->setText(" ");
		textTitle_->setText(" ");
	}
	//Comprueba si debe cambiar los botones a activos o inactivos
	updateButtons();
	game_->getStoryManager()->setEventChanges(false);
}

void Timeline::updateButtons() {
	if (leftButton_ != nullptr) {
		//Pone activos los botones si hay más de una pista en el panel de arriba
		leftButton_->setActive((upEventEntities_.size() > 1));
		rightButton_->setActive((upEventEntities_.size() > 1));
	}
}

void Timeline::createButtons() {
	//Aquí se crean los botones para cambiar la pista que se ve
	double eventSize = game_->getGame()->getWindowWidth() / 9;
	double buttonSize = eventSize / 3;
	leftButton_ = entityManager_->addEntity(2);
	leftButton_->addComponent<Transform>(eventPos_.getX() - buttonSize - buttonSize / 2, eventPos_.getY() + eventSize/2 - buttonSize / 2, buttonSize, buttonSize);	//esto ahora funciona pero está hecho a pelo y mal
	leftButton_->addComponent<Sprite>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::FlechaButton))->flipHor(true);
	leftButton_->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(true); }), this);
	leftButton_->setActive(false);

	rightButton_ = entityManager_->addEntity(2);
	rightButton_->addComponent<Transform>(eventPos_.getX()+eventSize+buttonSize/2, eventPos_.getY()+eventSize/2-buttonSize / 2, buttonSize, buttonSize);	//esto ahora funciona pero está hecho a pelo y mal
	rightButton_->addComponent<Sprite>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::FlechaButton));
	rightButton_->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([](Timeline* tl) { tl->moveActualEvent(false); }), this);
	rightButton_->setActive(false);
}

void Timeline::update()
{
	if (game_->getStoryManager()->getEventChanges()) 
		updateEvents();		
	checkFinal();
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
			eventClicked(upPlayerEvents_[i - 1]);
		}
	}
	else {
		if (it != upPlayerEvents_.end()-1) {	//Si no está en el borde derecho, se cambia el evento que se ve al que esté colocado en la derecha
			upEventEntities_[i]->setActive(false);
			upEventEntities_[i + 1]->setActive(true);
			eventClicked(upPlayerEvents_[i + 1]);
		}
	}
}

void Timeline::setActualEvent(CentralClue* event) {
	if (actualEvent_ != event) {
		actualEvent_ = event;
	}
}

void Timeline::deleteUpEvent(Entity* eventEntity, CentralClue* event) {
	auto it = find(upEventEntities_.begin(), upEventEntities_.end(), eventEntity);
	if (upEventEntities_.size() >= 2) {//Comprueba el resto del vector para ver si pone como entidad activa alguna de las colindantes (si las hay)
		if (it != upEventEntities_.begin()) { it--;  (*it)->setActive(true); it++; }
		else { it++;  (*it)->setActive(true); it--; }
	}
	upEventEntities_.erase(it);
	//A continuacion, hace lo mismo para los vectores con la información de los eventos
	auto it2 = find(upPlayerEvents_.begin(), upPlayerEvents_.end(), event);	//El evento que estás agarrando siempre va a ser el evento actual (se modifica al hacer click)
	if(it2!=upPlayerEvents_.end())
		upPlayerEvents_.erase(it2);
}

void Timeline::deleteDownEvent(Entity* eventEntity, CentralClue* event) {
	auto it = find(downEventEntities_.begin(), downEventEntities_.end(), eventEntity);
	(*it) = nullptr;
	//Hace lo mismo para la información de los eventos
	auto it2 = find(downPlayerEvents_.begin(), downPlayerEvents_.end(), event);	//El evento que estás agarrando siempre va a ser el evento actual (se modifica al hacer click)
	(*it2) = nullptr;
}

void Timeline::moveDown(Entity* eventEntity, CentralClue* event, int pos) {
	downEventEntities_[pos] = eventEntity;
	downPlayerEvents_[pos] = event;
	deleteUpEvent(eventEntity, event);
	getFinished();
}

void Timeline::moveUp(Entity* eventEntity, CentralClue* event) {
	Transform* eventTR = GETCMP2(eventEntity, Transform);
	eventTR->setPos(eventPos_);
	upEventEntities_.push_back(eventEntity);
	if (upEventEntities_.size() > 1)
		eventEntity->setActive(false);
	upPlayerEvents_.push_back(event);
	deleteDownEvent(eventEntity, event);
	//Pone como pista actual la que se esté viendo actualmente en el vector de arriba
	int i = 0; bool found = false;
	while (i < upEventEntities_.size() && !found) {//Busca cual de los de arriba esté activo
		if (upEventEntities_[i]->getActive()) found = true;
		else i++;
	}
	if (found) {//Si hay alguno activo, pone como evento actual ese
		eventClicked(upPlayerEvents_[i]);
	}

}

void Timeline::relocateDownEvents(Entity* event, int i) {
	int j = 0; bool same = false;
	while (j < downEventEntities_.size() && !same) {	//buscas la anterior pos y la haces nullptr
		if (event == downEventEntities_[j] && j != i) same = true;
		else j++;
	}
	if (same) {
		swap(downEventEntities_[i], downEventEntities_[j]);
		swap(downPlayerEvents_[i], downPlayerEvents_[j]);
		if (downPlayerEvents_[j] != nullptr) //si hay una allí donde quieres moverla, tienes que intercambiarla
		{
			double eventSize = game_->getGame()->getWindowWidth() / 9;
			Transform* eventTR = GETCMP2(downEventEntities_[j], Transform);
			eventTR->setPos(rectPlaceHolders_[j].x + rectPlaceHolders_[j].w * 0.1, rectPlaceHolders_[j].y + rectPlaceHolders_[j].h * 0.1);
		} 
	}
}

void Timeline::eventReleased(Entity* event) {
	double eventSize = game_->getGame()->getWindowWidth() / 9;
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
			eventTR->setPos(rectPlaceHolders_[i].x + rectPlaceHolders_[i].w * 0.1, rectPlaceHolders_[i].y + rectPlaceHolders_[i].h * 0.1);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::ClueDropped, 0, 2);
			if (downEventEntities_[i] != nullptr) moveUp(downEventEntities_[i], downPlayerEvents_[i]);
			moveDown(event, actualEvent_, i);
		}
		else eventTR->setPos(eventPos_);	//Si no colisiona, lo devuelve a la posición original
	}
	else {//Si el evento está abajo
		int i = 0; bool found = false;
		while (i < rectPlaceHolders_.size() && !found) {	//Busca con qué rectangulo de la timeline colisiona
			if (SDL_HasIntersection(&eventRect, &rectPlaceHolders_[i])) found = true;
			else i++;
		}
		if (found) 
		{
			eventTR->setPos(rectPlaceHolders_[i].x + rectPlaceHolders_[i].w*0.1, rectPlaceHolders_[i].y + rectPlaceHolders_[i].h*0.1);	//Si colisiona con alguno, lo deja en la posición del rectángulo
			auto it = find(downEventEntities_.begin(), downEventEntities_.end(), event);
			if(it!=downEventEntities_.end()) relocateDownEvents(event, i);
		}
		else {	//Si no, colisiona con los rectángulos, lo devuelve a la lista de arriba
			moveUp(event, actualEvent_);
		}	
	}
	updateButtons();
	getFinished();
}

void Timeline::eventClicked(CentralClue* cc) {
	setActualEvent(cc); 
	changeText();
}

void Timeline::createEvent(CentralClue* cc) {
	//Cálculos de posiciones y tamaño de la entidad
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = game_->getGame()->getWindowWidth() / 9;
	eventPos_ = Vector2D{ (w / 2) - (eventSize / 2), (h / 2) - (eventSize) };
	//Crea la entidad del evento y la añade arriba
	Entity* event = entityManager_->addEntity(Layers::DragDropLayer);
	Transform* eventTR = event->addComponent<Transform>(eventPos_.getX(), eventPos_.getY(), eventSize-(eventSize*0.2), eventSize-(eventSize*0.2));
	event->addComponent<Sprite>(SDLGame::instance()->getTextureMngr()->getTexture(cc->spriteId_));
	event->addComponent<DragTL>(this, [](Timeline* tl, Entity* e) { tl->eventReleased(e); });
	event->addComponent<ButtonOneParametter<Timeline*>>(std::function<void(Timeline*)>([cc](Timeline* tl) {tl->eventClicked(cc); }), this);
	event->setActive(false);
	upEventEntities_.push_back(event);

}

void Timeline::createPanels() {

	//Aquí se crea el panel que contiene el texto cuando pulsas en un evento
	textPanel_ = entityManager_->addEntity(Layers::LastLayer);
	double textPanelW = game_->getGame()->getWindowWidth() / 3;
	double textPanelH = game_->getGame()->getWindowHeight()/3;
	Transform* textPanelTR = textPanel_->addComponent<Transform>(textPanelW, 27, textPanelW*2 -27, textPanelH);

	textTitle_ = textPanel_->addComponent<Text>("", textPanelTR->getPos(), -1, Resources::RobotoTest24, 0);
	textTitle_->setSoundActive(false);
	textDescription_ = textPanel_->addComponent<Text>("", textPanelTR->getPos() + Vector2D(0, 80), textPanelTR->getW(), Resources::RobotoTest24, 0);
	textDescription_->setSoundActive(false);

	//Aquí se crea el panel inferior, donde se colocarán los eventos
	double w = game_->getGame()->getWindowWidth() / 3;
	double h = game_->getGame()->getWindowWidth() / 3;
	double eventSize = game_->getGame()->getWindowWidth() / 9;
	
	for (int i = 0; i < nEvents_; i++) {//Creamos los rectangulos en los que debemos encajar los eventos
		Entity* r = entityManager_->addEntity(2);
		Transform* rTR = r->addComponent<Transform>(((game_->getGame()->getWindowWidth() / nEvents_) * i) + (eventSize/2),h + (eventSize/10), eventSize, eventSize);
		Texture* tex = game_->getGame()->getTextureMngr()->getTexture(Resources::TimelinePlaceholders);
		Sprite* s = r->addComponent<Sprite>(tex);
		s->setSourceRect({ 0, (tex->getHeight() / 4) * i,tex->getWidth(), tex->getHeight() / 4 });
		r->addComponent<Rectangle>(SDL_Color{ COLOR(0x01010100) })->setBorder(SDL_Color{ COLOR(0xffffffFF) });
		rectPlaceHolders_.push_back(SDL_Rect RECT(rTR->getPos().getX(), rTR->getPos().getY(), rTR->getW(), rTR->getH()));
	}
}

bool Timeline::getCorrectOrder() {
	bool order = true;
	//Comprueba si está acabado
	if (!getFinished()) {
		order = false;
		return order;
	}
	//Comprueba si el orden es correcto
	auto correctTimeline = game_->getStoryManager()->getTimeline();	//te pilla la timeline del caso actual
	int i = 0;
	while (i < correctTimeline.size() && order) {
		if (!(downPlayerEvents_[i]->id_ == correctTimeline[i])) order = false;
		else i++;
	}
	return order;
}

bool Timeline::getCorrectEvents() {
	bool correct = true;
	//Comprueba si está acabado
	if (!getFinished()) {
		correct = false;
		return correct;
	}
	else {
		//Comprueba si los eventos son correctos
		int i = 0;
		while (i < downPlayerEvents_.size() && correct) {
			if (!downPlayerEvents_[i]->isCorrect_) correct = false;
			else i++;
		}
	}

	return correct;
}

void Timeline::resetTimeline() {
	if (!getCorrectOrder()) {
		if (!getCorrectEvents()) {
			for(int i = 0; i<downPlayerEvents_.size(); i++){
				if (!downPlayerEvents_[i]->isCorrect_) 
				{
					StoryManager::instance()->resetTLClue(downPlayerEvents_[i]);
					updateEvents();
				}	
			}
		}
		//Resetea el orden de la timeline	
		auto correctTimeline = game_->getStoryManager()->getTimeline();	//te pilla la timeline del caso actual
		for (int i = 0; i < correctTimeline.size(); i++) {
			if ((downPlayerEvents_[i]!=nullptr)&&(downPlayerEvents_[i]->id_ != correctTimeline[i])) 
				moveUp(downEventEntities_[i], downPlayerEvents_[i]);
		}
	}
	else {
		if (!getCorrectEvents()) {
			for(int i = 0; i<downPlayerEvents_.size(); i++){
				if (!downPlayerEvents_[i]->isCorrect_) {
					StoryManager::instance()->resetTLClue(downPlayerEvents_[i]);
					updateEvents();
				}
			}
		}
	}

}

void Timeline::checkFinal() {
	bool finished = getFinished();
	Sprite* s = GETCMP2(presentCaseButton_, Sprite);
	Texture* tex = game_->getGame()->getTextureMngr()->getTexture(Resources::AcursarButton);
	if (finished) {
		s->setSourceRect({ 0, (tex->getHeight() / 2),tex->getWidth(), tex->getHeight() / 2 });
	}
	else {
		s->setSourceRect({ 0, 0,tex->getWidth(), tex->getHeight() / 2 });
	}
}

bool Timeline::getFinished() {	
	int i = 0;  bool finished = true;
	while (i < downPlayerEvents_.size() && finished) {
		if (downPlayerEvents_[i] == nullptr) finished = false;
		else i++;
	}
	return (finished);
}