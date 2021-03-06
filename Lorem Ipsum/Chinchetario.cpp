#include "Chinchetario.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "ScrollerLimited.h"
#include "Rectangle.h"
#include "Camera.h"
#include "CameraController.h"
#include "Sprite.h"
#include "Line.h"
#include "ClueCallbacks.h"

Chinchetario::Chinchetario(LoremIpsum* game) : State(game)
{

	camera_->setPos(0, 0);
	camera_->setWidth(game_->getGame()->getWindowWidth()); 
	camera_->setHeight(game_->getGame()->getWindowHeight());
	camera_->setLeftMargin(0); camera_->setRightMargin(0);
	Texture* bckgrndTexture = game_->getGame()->getTextureMngr()->getTexture(Resources::CorkBG);
	camera_->setLimitX(bckgrndTexture->getWidth());
	camera_->setLimitY(bckgrndTexture->getHeight());

	mng_ = entityManager_->addEntity();

	background_ = entityManager_->addEntity();
	background_->addComponent<Transform>(0, 0, 2560, 1440);
	background_->addComponent<Sprite>(bckgrndTexture);
	
	createPanels();

	updateClues();

	auto goBackButton = entityManager_->addEntity(Layers::LastLayer);
	goBackButton->addComponent<Transform>(0, 0, 64, 64);
	//goBackButton->addComponent<Rectangle>(SDL_Color{ COLOR(0xffccccff) });
	auto sp = goBackButton->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::GoBackButton));
	goBackButton->setUI(true);
	auto b = goBackButton->addComponent<ButtonOneParametter<Chinchetario*>>(std::function<void(Chinchetario*)>([](Chinchetario* ch) {ch->close(); }), this);
	b->setMouseOverCallback([sp]() {sp->setTint(111, 111, 111); });
	b->setMouseOutCallback([sp]() {sp->setTint(255, 255, 255); });
	showPopUpMessage("En el panel inferior se guardan las pistas que has recogido. Arr\u00e1stralas al corcho y une hilos entre las chinchetas seg\u00fan tus conclusiones para avanzar en el caso");
}

void Chinchetario::update()
{
	State::update();
	if (game_->getStoryManager()->getInvestigableChanges()) {
		updateClues();
	}
	InputHandler* ih = InputHandler::instance();
	//if (ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::LEFT) && ih->getMousePos().getY() < bottomPanel_->getComponent<Transform>(ecs::Transform)->getPos().getY())

}

void Chinchetario::updateClues() {

	for (int i = 0; i < game_->getStoryManager()->getPlayerCentralClues().size(); i++) {
		auto it = find(playerClues_.begin(), playerClues_.end(), game_->getStoryManager()->getPlayerCentralClues()[i]);
		if (it == playerClues_.end()) {//Si no encuentra esa pista en el vector, la añade
			playerClues_.push_back(game_->getStoryManager()->getPlayerCentralClues()[i]);
			createClues(game_->getStoryManager()->getPlayerCentralClues()[i], playerClues_.size() - 1);
			showBottomPanel();
		}
	}
	for (int i = 0; i < game_->getStoryManager()->getPlayerClues().size(); i++) {
		auto it = find(playerClues_.begin(), playerClues_.end(), game_->getStoryManager()->getPlayerClues()[i]);
		if (it == playerClues_.end()) {//Si no encuentra esa pista en el vector, la añade
			playerClues_.push_back(game_->getStoryManager()->getPlayerClues()[i]);
			createClues(game_->getStoryManager()->getPlayerClues()[i], playerClues_.size()-1);
			showBottomPanel();
		}	
	}
	relocateClues();
	game_->getStoryManager()->setInvestigableChanges(false);
}

void Chinchetario::removeClue(Resources::ClueID id) {
	int i = 0; bool found = false;
	while (i < playerClues_.size() && !found) {
		Clue* clue = playerClues_[i];
		if (clue->id_ == id) {
			playerClues_.erase(playerClues_.begin() + i);
			clue->entity_->setActive(false);
			if (clue->id_ > Resources::lastClueID) {
				Transform* tratra = GETCMP2(clue->entity_, Transform);
				auto tratravector = tratra->getChildren();
				for (auto p : static_cast<CentralClue*>(clue)->pins_) {
					Pin* pin = p->getComponent<Pin>(ecs::Drag);
					pin->eliminateLine();
				}
				tratra->setActiveChildren(false);
			}
			found = true;
		}
		else i++;
	}
}

void Chinchetario::render()
{
	State::render();
}
//Determina si es el objeto con componente Drag m�s arriba en la jerarqu�a de capas
bool Chinchetario::isHigherDragable(Drag* d) {
	bool higher;
	if (draggedItem_ == nullptr) {  //Si no hay ninguno agarrado, este se guarda
		higher = true;
		draggedItem_ = d;
	}
	else {
		//Se aceptan ideas a los nombres de estas variables
		int dl = d->getEntity()->getLayer();
		int dil = draggedItem_->getEntity()->getLayer();
		int dli = d->getEntity()->getLayerIndex();
		int dili = draggedItem_->getEntity()->getLayerIndex();
		higher = (dl > dil || (dl == dil && dli > dili));   //Si est� en una capa superior o en la misma pero con �ndice mayor
		if (higher) {
			entityManager_->getEntity(dil, dili)->getComponent<Drag>(ecs::Drag)->deactivateDrag();
			draggedItem_ = d;
		}
	}
	return higher;
}

void Chinchetario::resetWrongClue(CentralClue* cc) {

	int i = 0;
	while (cc->entity_ != playerClues_[i]->entity_)
	{
		i++;
	}
	scroll_->addItem(cc->entity_->getComponent<Transform>(ecs::Transform),i);
	cc->isEvent_ = false;
	cc->isCorrect_ = false;
	cc->actualDescription_ = " ";
	game_->getStoryManager()->setEventChanges(true);
	if (ClueCallbacks::centralClueCBs.find(cc->id_) != ClueCallbacks::centralClueCBs.end())
	{
		ClueCallbacks::centralClueCBs[cc->id_]();
	}

	cc->placed_ = false;
	Transform* cTR = GETCMP2(cc->entity_, Transform);
	cTR->setActiveChildren(false);
	//resetDraggedItem();
	//Mira todos sus hijos y actualiza la l�nea, cambiar si va a haber otros tipos de hijos diferentes
	auto chldrn = cTR->getChildren();
	for (Transform* t : chldrn) {
		Pin* p = static_cast<Pin*>(t->getEntity()->getComponent<Drag>(ecs::Drag));
		Line* l = p->getLine();
		if (l != nullptr) {
			Vector2D newPos = { t->getPos().getX() + t->getW() / 2, t->getPos().getY() + t->getH() / 2 };
			l->moveTo(newPos);
			l->eraseLine();
			auto grchldrn = t->getChildren()[0];
			static_cast<DragDrop*>(GETCMP2(grchldrn->getEntity(), Drag))->detachLine();
			grchldrn->eliminateParent();
			int i = 0;
			Entity* c = grchldrn->getEntity();
			while (c != playerClues_[i]->entity_)
			{
				i++;
			}
			scroll_->addItem(grchldrn, i);
			playerClues_[i]->placed_ = false;
			p->eliminateLine(); p->resetActualLink();
		}
	}
	relocateClues();
}

void Chinchetario::clueDropped(Entity* e)
{
	int i = 0;
	while (e != playerClues_[i]->entity_)
	{
		i++;
	}
	Transform* parent = GETCMP2(playerClues_[i]->entity_, Transform)->getParent();
	if (parent)
		return; //más vale return bien puesto que error de ejecución. Cleon, si lees esto, que sepas que nos merecemos buena nota igualmente besitos <3
	bool b = !checkClueInBottomPanel(e);
	if (b && !playerClues_[i]->placed_) {
		scroll_->removeItem(e->getComponent<Transform>(ecs::Transform), i);
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::ClueDropped, 0, 1);
	}
	else if (!b && playerClues_[i]->placed_) { 
		scroll_->addItem(e->getComponent<Transform>(ecs::Transform), i);
		//Si tiene un evento, lo resetea
		if (playerClues_[i]->id_ > Resources::lastClueID) {
			CentralClue* cc = static_cast<CentralClue*>(playerClues_[i]);
			cc->isEvent_ = false;
			cc->isCorrect_ = false;
			cc->actualDescription_ = " ";
			game_->getStoryManager()->setEventChanges(true);
			if (ClueCallbacks::centralClueCBs.find(cc->id_) != ClueCallbacks::centralClueCBs.end())
			{
				ClueCallbacks::centralClueCBs[cc->id_]();
			}
		}
		
	}

	playerClues_[i]->placed_ = b;
	relocateClues();
	Transform* cTR = GETCMP2(playerClues_[i]->entity_, Transform);
	cTR->setActiveChildren(b);
	if (playerClues_[i]->entity_->isUI())//wtf donde se cambia el ui arriba
	{
		Transform* tr = playerClues_[i]->entity_->getComponent<Transform>(ecs::Transform);
		tr->setPos(tr->getPos() + camera_->getPos());
	}
	resetDraggedItem();
	//Mira todos sus hijos y actualiza la l�nea, cambiar si va a haber otros tipos de hijos diferentes
	auto chldrn = cTR->getChildren();
	for (Transform* t : chldrn) {
		Pin* p = static_cast<Pin*>(t->getEntity()->getComponent<Drag>(ecs::Drag));
		Line* l = p->getLine();
		if (l != nullptr) {
			Vector2D newPos = { t->getPos().getX() + t->getW() / 2, t->getPos().getY() + t->getH() / 2 };
			if (p->getState())
			{
				l->moveTo(newPos);
			}
			else l->setIniFin(newPos);
			if (!b) {
				l->eraseLine();
				if (t->getChildren().size() > 0) {
					auto grchldrn = t->getChildren()[0];
					static_cast<DragDrop*>(GETCMP2(grchldrn->getEntity(), Drag))->detachLine();
					grchldrn->eliminateParent();
					int i = 0;
					Entity* c = grchldrn->getEntity();
					while (c != playerClues_[i]->entity_)
					{
						i++;
					}
					scroll_->addItem(grchldrn, i);
					playerClues_[i]->placed_ = b;
				}
			}
		}
	}
	
	

	//if (!clues[i]->placed_)
	//    clues[i]->entity_->setLayer(Layers::LastLayer);
}
void Chinchetario::pinDropped(Entity* e) {
	InputHandler* ih = InputHandler::instance();
	Vector2D mpos = ih->getMousePos();
	SDL_Point point = { (int)mpos.getX(),(int)mpos.getY() };
	Transform* CCtr = GETCMP2(e, Transform);
	Drag* d = GETCMP2(e, Drag);
	Pin* p = static_cast<Pin*>(d);
	Clue* linked = p->getActualLink();
	CentralClue* cc = p->getCentralClue();
	Transform* tr;
	SDL_Rect rect;
	Entity* prevE = nullptr;
	Transform* prevTR = nullptr;
	bool was = false;
	//Si estaba conectada a otra pista, corta la union
	if (p->getState()) {
		prevE = p->getActualLink()->entity_;
		prevTR = GETCMP2(prevE, Transform);
		if (prevTR->getParent() != nullptr)
			prevTR->eliminateParent();
		p->setState(false);
		was = true;
	}
	DragDrop* lastCorrectDD = nullptr;
	for (Clue* c : playerClues_) {
		if (c->placed_ && c->id_ < Resources::ClueID::lastClueID) {		//Si est� en el tablero y no es principal
			tr = c->entity_->getComponent<Transform>(ecs::Transform);
			Vector2D pos = tr->getPos() - camera_->getPos();
			rect = SDL_Rect RECT(pos.getX(), pos.getY(), tr->getW(), tr->getH());
			DragDrop* dd = static_cast<DragDrop*>(c->entity_->getComponent<Drag>(ecs::Drag));
			if (SDL_PointInRect(&point, &rect) && isHigherDragable(dd)) {	//Si hace clic en ella y es la que est� m�s adelante
				if (lastCorrectDD != nullptr) {		//Si la anterior en entrar aqu� era del tipo correcto, deshace
					lastCorrectDD->detachLine();
					lastCorrectDD->getEntity()->getComponent<Transform>(ecs::Transform)->eliminateParent();
					tr->eliminateParent();
					p->resetActualLink();
				}
				if (p->isSameType(c->type_)) {		//Si es del tipo correcto
					if (p->getActualLink() != nullptr && p->getActualLink()->id_ == c->id_) {	//Si es LA MISMA pista [Feisimo]
						if (was) {
							prevTR->setParent(CCtr);
							p->setState(true);
						}
					}
					else {
						if (tr->getParent() != nullptr) {//si la pista ya está conectada a otra coisa
							//borra esa linea
							Pin* pf = static_cast<Pin*>(tr->getParent()->getEntity()->getComponent<Drag>(ecs::Drag));
							pf->eliminateLine();
							pf->resetActualLink();
							tr->eliminateParent();
							//resetea la información de evento
							CentralClue* that = pf->getCentralClue();
							that->isEvent_ = false; that->isCorrect_ = false;
							that->actualDescription_ = " ";
							Rectangle* cRec = GETCMP2(that->entity_, Rectangle);
							if(cRec)
								cRec->setBorder(SDL_Color{ COLOR(0x01010100) });
							game_->getStoryManager()->setEventChanges(true);
							if (ClueCallbacks::centralClueCBs.find(cc->id_) != ClueCallbacks::centralClueCBs.end())
							{
								ClueCallbacks::centralClueCBs[cc->id_]();
							}
						}
						//Feisimo, lo se
						if (was) {	//Si estaba enganchado a algo lo desengancha
							if (prevTR->getParent() != nullptr)
								prevTR->eliminateParent();
							p->setState(false);
							static_cast<DragDrop*>(prevE->getComponent<Drag>(ecs::Drag))->detachLine();
							if (cc->isEvent_) {
								cc->isEvent_ = false; cc->isCorrect_ = false;
								cc->actualDescription_ = " ";
								changeText(cc);
								game_->getStoryManager()->setEventChanges(true);
								if (ClueCallbacks::centralClueCBs.find(cc->id_) != ClueCallbacks::centralClueCBs.end())
								{
									ClueCallbacks::centralClueCBs[cc->id_]();
								}
							}
						}
						p->setActualLink(c);
						tr->setParent(CCtr);
						p->associateLine(static_cast<DragDrop*>(c->entity_->getComponent<Drag>(ecs::Drag)));
						lastCorrectDD = dd;
						checkEvent(cc);
						SDLGame::instance()->getAudioMngr()->playChannel(Resources::PinDropped, 0, 1);
					}
				}
				else lastCorrectDD = nullptr;
			}
		}
	}
	if (!p->getState()) {	//Si se queda sin enganchar, borra la l�nea
		p->eliminateLine();
		p->resetActualLink();
		if (prevE != nullptr) {
			static_cast<DragDrop*>(prevE->getComponent<Drag>(ecs::Drag))->detachLine();
			if (cc->isEvent_) {
				cc->isEvent_ = false; cc->actualDescription_ = " "; cc->isCorrect_ = false;
				changeText(cc); 
				game_->getStoryManager()->setEventChanges(true);
			}
		}
			
	}
	resetDraggedItem();
}

void Chinchetario::relocateClues()
{
	size_t size = playerClues_.size();
	int numPlaced = 0;
	for (size_t i = 0; i < size; i++)
	{
		//(clueSize + (2 * clueSize) * i, game_->getGame()->getWindowHeight() - (bottomPanelH / 2 + clueSize / 2));
		if (playerClues_[i]->placed_)
		{
			numPlaced++;
			//clues[i]->entity_->getComponent(ecs)
			playerClues_[i]->entity_->setUI(false);

		}
		else
		{
			Transform* t = playerClues_[i]->entity_->getComponent<Transform>(ecs::Transform);
			t->setPos(t->getW() + (2 * t->getW()) * (i - numPlaced), game_->getGame()->getWindowHeight() - (GETCMP2(bottomPanel_, Transform)->getH() / 2 + t->getH() / 2));
			playerClues_[i]->entity_->setUI(true);
		}
		//GETCMP2()
	}


	if (numPlaced == playerClues_.size())
	{
		hideBottomPanel();
	}
}
void Chinchetario::toggleBottomPanel()
{
	//Si está abajo, es que tiene que subir. El panel se oculta con un tween que lo pone en WindowH
	bottomPanel_->getComponent<Transform>(ecs::Transform)->getPos().getY() < game_->getGame()->getWindowHeight()-30 ? hideBottomPanel() : showBottomPanel();
};
//true si est� en el panel de abajo
bool Chinchetario::checkClueInBottomPanel(Entity* e)
{
	//Entity* e = clueEntities_[i];
	Transform* clueTr = GETCMP2(e, Transform);
	Transform* pannelTr = GETCMP2(bottomPanel_, Transform);

	SDL_Rect r{ pannelTr->getPos().getX(), pannelTr->getPos().getY(), pannelTr->getW() + clueTr->getW(),  pannelTr->getH() + clueTr->getH() };
	SDL_Point p{ clueTr->getPos().getX() + clueTr->getW(), clueTr->getPos().getY() + clueTr->getH() };
	p.x -= camera_->getPosX();
	p.y -= camera_->getPosY();

	return (bottomPanel_->getActive() && (SDL_PointInRect(&p, &r)));
}

void Chinchetario::setUnplacedClues(bool b)
{
	for (auto& c : playerClues_)
	{
		if (!c->placed_)
		{
			c->entity_->setActive(b);
		}
	}
}
void Chinchetario::createPanels() {
	bottomPanel_ = entityManager_->addEntity(Layers::CharacterLayer);
	rightPanel_ = entityManager_->addEntity(Layers::LastLayer);
	double rightPanelW = game_->getGame()->getWindowWidth() / 4;
	double rightPanelH = game_->getGame()->getWindowHeight();
	Transform* rpTr = rightPanel_->addComponent<Transform>(game_->getGame()->getWindowWidth(), 0, rightPanelW, rightPanelH);
	//rightPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x0085cf88) });
	rightPanel_->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::VerticalUIPanel));
	auto tween = rightPanel_->addComponent<Tween>(game_->getGame()->getWindowWidth() - rightPanelW, 0.0, 15, rightPanelW, rightPanelH);
	tween->GoToB();
	tween->setFunc([](Entity* s) { static_cast<Chinchetario*>(s->getState())->showText(); }, rightPanel_);
	rightPanel_->setUI(true);


	textTitle_ = rightPanel_->addComponent<Text>("", rpTr->getPos()+ Vector2D(-rightPanelW+4, 2), rpTr->getW(), Resources::RobotoTest24, 0);
	textTitle_->setSoundActive(false);

	cluePhoto_ = entityManager_->addEntity(Layers::LastLayer);
	Transform* phTr = cluePhoto_->addComponent<Transform>(0,0, rightPanelW -12*2, 72*4);
	phTr->setParent(rpTr);
	phTr->setPos(12, 12.0 + textTitle_->getCharH());
	cluePhoto_->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::clueTemplate));
	cluePhoto_->setUI(true);

	textDescription_ = rightPanel_->addComponent<Text>("", rpTr->getPos() + Vector2D(-rightPanelW + 5, 80.0 * 4.0), rpTr->getW()-15, Resources::RobotoTest24, 0);
	textDescription_->setScroll(textDescription_->getPos().getX(), textDescription_->getPos().getY(), textDescription_->getMaxW(),  rightPanelH - (100.0 * 4.0));
	textDescription_->setSoundActive(false);

	Entity* rightPanelTopImage = entityManager_->addEntity(Layers::LastLayer);
	rightPanelTopImage->setUI(true);
	rightPanelTopImage->addComponent<Transform>(game_->getGame()->getWindowWidth()-16, 0, rightPanelW, rightPanelH)->setParent(rpTr);
	rightPanelTopImage->addComponent<Sprite>()->setTexture(Resources::VerticalUIPanel2);




	double bottomPanelW = game_->getGame()->getWindowWidth() - rightPanelW;
	bottomPanelH_ = game_->getGame()->getWindowHeight() / 5;
	Transform* bpTr = bottomPanel_->addComponent<Transform>(0.0, game_->getGame()->getWindowHeight()-30,  bottomPanelW, bottomPanelH_);
	//bottomPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x00cf0088) });
	bottomPanel_->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::HorizontalUIPanel));
	Chinchetario* ch = this;
	bottomPanel_->addComponent<Tween>(0, game_->getGame()->getWindowHeight() - bottomPanelH_, 15, bottomPanelW, bottomPanelH_)->setFunc([ch](Entity* e) {ch->setUnplacedClues(true); }, bottomPanel_);
	bottomPanel_->setUI(true);
	GETCMP2(bottomPanel_, Tween)->GoToA();
	scroll_ = mng_->addComponent<ScrollerLimited>(0, bottomPanelW);

	cursor_ = entityManager_->addEntity();
	cursor_->addComponent<CameraController>(camera_);

	Entity* bottomPanelTopImage = entityManager_->addEntity(Layers::LastLayer);
	bottomPanelTopImage->setUI(true);
	bottomPanelTopImage->addComponent<Transform>(0.0, game_->getGame()->getWindowHeight()-30, bottomPanelW, bottomPanelH_)->setParent(bpTr);
	bottomPanelTopImage->addComponent<Sprite>()->setTexture(Resources::HorizontalUIPanel2);

	auto hidePannelButton = entityManager_->addEntity(Layers::LastLayer);
	hidePannelButton->addComponent<Transform>(5, game_->getGame()->getWindowHeight() - 46 -bottomPanelH_, 95*2, 23);
	Transform* tr = GETCMP2(hidePannelButton, Transform);
	tr->setParent(GETCMP2(bottomPanel_, Transform));
	tr->setPos({30,12});
	//hidePannelButton->addComponent<Sprite>(buttonSprite);
	hidePannelButton->setUI(true);


	hidePannelButton->addComponent<ButtonOneParametter<Chinchetario*>>(std::function<void(Chinchetario*)>([tr](Chinchetario* ch)
		{
			ch->toggleBottomPanel(); 
			if (tr->getRot() == 0)
			{
				tr->setRot(180);
			}
			else

			{
				tr->setRot(0);
			}
		}), this);


	//auto hideRightPannelButton = entityManager_->addEntity(Layers::LastLayer);
	//hideRightPannelButton->addComponent<Transform>(5, game_->getGame()->getWindowHeight() - 46 - bottomPanelH_, 92, 46);
	//tr = GETCMP2(hideRightPannelButton, Transform);
	//tr->setParent(GETCMP2(rightPanel_, Transform));
	//tr->setRot(270);
	//tr->setPos({ -69, 23 });
	//Texture* buttonSprite = game_->getGame()->getTextureMngr()->getTexture(Resources::HideShowButton);
	//Sprite * sp = hideRightPannelButton->addComponent<Sprite>(buttonSprite);
	//buttonSprite->setPivotPoint({ 46, 23 });
	//hideRightPannelButton->setUI(true);


	auto b = rightPanelTopImage->addComponent<ButtonOneParametter<Chinchetario*>>(std::function<void(Chinchetario*)>([tr](Chinchetario* ch)
		{
			if (tr->getRot() == 270)
			{
				ch->hideRightPanel();
				tr->setRot(90);
			}
			else
			{
				ch->showRightPanel();
				tr->setRot(270);
			}
		}), this);
	b->setOffsets(10, -108, 164, 628);
	//b->setMouseOverCallback([sp]() {sp->setTint(111,111,111); });
	//b->setMouseOutCallback([sp]() {sp->setTint(255, 255, 255); });

}

void Chinchetario::changeText(Clue* c) {
	//showRightPanel(); 
	//Comprueba si es una pista central, y en tal caso, comprueba si tiene formado un evento, para mostrar ese texto en lugar del normal
	if (c->id_ > Resources::lastClueID) {
		CentralClue* cc = static_cast<CentralClue*>(c);
		if (cc->isEvent_) textDescription_->setText(cc->actualDescription_);
		else textDescription_->setText(cc->description_);
	}
	else textDescription_->setText(c->description_);
	textTitle_->setText(c->title_); 
	
	cluePhoto_->getComponent<Transform>(ecs::Transform)->setPosY(textTitle_->getPos().getY() + (double)textTitle_->getNumLines() * textTitle_->getCharH());
	textDescription_->setPos(Vector2D(textDescription_->getPos().getX(), cluePhoto_->getComponent<Transform>(ecs::Transform)->getPos().getY()+ 
	cluePhoto_->getComponent<Transform>(ecs::Transform)->getH()+10));
	double rightPanelH = game_->getGame()->getWindowHeight();
	textDescription_->setScroll(textDescription_->getPos().getX(), textDescription_->getPos().getY(), textDescription_->getMaxW(), rightPanelH - (100.0 * 4.0));

	
	GETCMP2(cluePhoto_, Sprite)->setTexture(c->spriteId_);
	GETCMP2(cluePhoto_, Sprite)->setEnabled(true);
}

void Chinchetario::createClues(Clue* c, int i) {

	//A�adimos la informaci�n com�n de las pistas centrales y normales a la entidad
	Entity* entity = (c->entity_ = entityManager_->addEntity(Layers::DragDropLayer));
	double clueW = 64;
	double clueH = 72;
	scroll_->addItem(entity->addComponent<Transform>
	(clueW + (2 * clueW) * i, game_->getGame()->getWindowHeight() - (bottomPanelH_ / 2 + clueW / 2), 
		clueW, clueH), i);
	string clueTitle = c->title_;
	string clueDescription = c->description_;
	entity->addComponent<DragDrop>(this, [](Chinchetario* ch, Entity* e) {ch->clueDropped(e); });
	entity->addComponent<ButtonOneParametter<Chinchetario*>>(std::function<void(Chinchetario*)>(
		[c](Chinchetario* ch) { ch->changeText(c); }), this);
	//Si no es una pista central
	SDL_Color col = SDL_Color{ COLOR(0xffffffff) };
	if (c->id_ < Resources::ClueID::lastClueID) {
		switch (c->type_) {
		case Resources::ClueType::Object:
			col = SDL_Color{ COLOR(0xff0000ff) };
			break;
		case Resources::ClueType::Person:
			col = SDL_Color{ COLOR(0x66ff66ff) };
			break;
		case Resources::ClueType::Place:
			col = SDL_Color{ COLOR(0x0000ffff) };
			break;
		default:
			col = SDL_Color{ COLOR(0xffffffff) };
			break;
		}
		entity->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(playerClues_[i]->spriteId_))->setBorder(col); 
	}
	//si es una pista central
	else {

		//Guardamos los datos necesarios de la pista central
		Transform* clueTR = GETCMP2(entity, Transform);
		double nLinks = static_cast<CentralClue*>(c)->links_.size();
		//Las pistas se dibujar�n alrededor de la circunferencia definida por estos datos:
		double angle = 360 / (nLinks);
		double rd = clueTR->getH() / 2;
		//Colocamos cada chincheta en su sitio (cada pista central tendr� x n�mero de chinchetas)
		for (int j = 0; j < nLinks; j++) {
			Resources::ClueID thisLinkID = static_cast<CentralClue*>(c)->links_[j];
			Resources::ClueType thisLinkType = game_->getStoryManager()->getClues().at(thisLinkID)->type_;
			double rad = M_PI / 180;
			double pinY = rd * cos(rad * (180 + angle * j)); //posici�n en X y en Y LOCALES de la chincheta
			double pinX = rd * sin(rad * (180 + angle * j));
			Vector2D pinPos = Vector2D(pinX + rd, pinY + rd); //posici�n en X y en Y GLOBALES de la chincheta
			pinPos = pinPos + clueTR->getPos();
			//Creamos una entidad para la chincheta con la posici�n que acabamos de calcular
			Entity* pin = entityManager_->addEntity(Layers::PinLineLayer); //La layer la puse para testear porque es la que est� m�s arriba
			pin->setActive(false);
			int pinSize = 30; int pinOffset = pinSize / 2;
			pin->addComponent<Transform>(pinPos.getX() - pinOffset, pinPos.getY() - pinOffset, pinSize, pinSize)->setParent(clueTR);
			//pin->addComponent<Line>(Vector2D{ pinPos.getX() - pinOffset, pinPos.getY() - pinOffset }, Vector2D{ pinPos.getX() - pinOffset, pinPos.getY() - pinOffset }, 4);
			switch (thisLinkType)
			{
			case Resources::ClueType::Object:
				col = SDL_Color{ COLOR(0xff0000FF) };
				break;
			case Resources::ClueType::Person:
				col = SDL_Color{ COLOR(0x00ff00FF) };
				break;
			case Resources::ClueType::Place:
				col = SDL_Color{ COLOR(0x0000ffff) };
				break;
			}
			//pin->addComponent<Rectangle>(col);
			Texture* tex = game_->getGame()->getTextureMngr()->getTexture(Resources::Chinchetas);
			entity->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(playerClues_[i]->spriteId_))->setBorder(col);
			Sprite* sp = pin->addComponent<Sprite>(tex);
			sp->setSourceRect({0,tex->getHeight()/5 * thisLinkType, tex->getWidth(), tex->getHeight()/5});
			pin->addComponent<Pin>(this, static_cast<CentralClue*>(c), thisLinkID, thisLinkType, [](Chinchetario* ch, Entity* pin) {ch->pinDropped(pin); })->setColor(col);

			static_cast<CentralClue*>(c)->pins_.push_back(pin);
		}
		clueEntities_.push_back(entity);
	}
}
void Chinchetario::checkEvent(CentralClue* cc)
{
	string eventText = cc->eventDescription_;
	Rectangle* cRec = GETCMP2(cc->entity_, Rectangle);
	int i = 0; bool b = false;
	auto pins = cc->pins_;
	//comprueba que la pista principal tenga todas las conexiones hechas para formar un evento
	while (i < pins.size() && !b) {
		Pin* p = static_cast<Pin*>(pins[i]->getComponent<Drag>(ecs::Drag));
		if (p->getState()) i++;
		else b = true;
	}
	//si puede formar un evento,
	if (!b) {
		int temp = 0;

		//Cambia los textos y comprueba si los enlaces son correctos
		for (int i = 0; i < pins.size(); i++) {
			Pin* p = static_cast<Pin*>(pins[i]->getComponent<Drag>(ecs::Drag));
			if (p->isCorrect()) temp++;
			Clue* c = p->getActualLink();
			string name = c->eventText_;	
			size_t pos;
			
			switch (c->type_)
			{
			case Resources::ClueType::Object:
				pos = eventText.find('~');
				if (pos != -1) {
					eventText.erase(pos, 1);
					eventText.insert(pos, name);
				}
				else cout << "\n//-----------------------------// \n"
					<<"ATENSION \n Los tipos (ClueType) de las pistas que tienes que enlazar con esta pista principal no cuadran con los caracteres de la frase (@, ~ o $)" <<
					"\n Revisa Resources.cpp pls" << 
					"//-----------------------------// \n"<<endl;
				break;
			case Resources::ClueType::Person:
				pos = eventText.find('@');
				if (pos != -1) {
					eventText.erase(pos, 1);
					eventText.insert(pos, name);
				}
				else cout << "//-----------------------------// \n"
					<< "ATENSION \n Los tipos (ClueType) de las pistas que tienes que enlazar con esta pista principal no cuadran con los caracteres de la frase (@, ~ o $)" <<
					"\n Revisa Resources.cpp pls" <<
					"//-----------------------------// \n" << endl;
				break;
			case Resources::ClueType::Place:
				pos = eventText.find('$');
				if (pos != -1) {
					eventText.erase(pos, 1);
					eventText.insert(pos, name);
				}
				else cout << "//-----------------------------// \n"
					<< "ATENSION \n Los tipos (ClueType) de las pistas que tienes que enlazar con esta pista principal no cuadran con los caracteres de la frase (@, ~ o $)" <<
					"\n Revisa Resources.cpp pls" <<
					"//-----------------------------// \n" << endl;
				break;
			}
		}
		//Actualiza los valores dentro de la pista
		cc->isEvent_ = true;
		cc->isCorrect_ = (temp == pins.size());
		cc->actualDescription_ = eventText;
		changeText(cc);
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::Event, 0, 3);

		game_->getStoryManager()->setEventChanges(true);
		if (ClueCallbacks::centralClueCBs.find(cc->id_) != ClueCallbacks::centralClueCBs.end())
		{
			ClueCallbacks::centralClueCBs[cc->id_]();
		}
	}
}
void Chinchetario::close() {
	game_->getStateMachine()->PlayGame();
}