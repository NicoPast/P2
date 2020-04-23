#include "Chinchetario.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "ButtonClue.h"
#include "ScrollerLimited.h"
#include "Rectangle.h"
#include "Camera.h"
#include "CameraController.h"
#include "Sprite.h"
#include "Line.h"


Chinchetario::Chinchetario(LoremIpsum* game) : State(game)
{

	camera_ = new Camera(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight(), 0, 0);
	camera_->setLimitX(game_->getGame()->getTextureMngr()->getTexture(Resources::CorkBG)->getWidth());
	camera_->setLimitY(game_->getGame()->getTextureMngr()->getTexture(Resources::CorkBG)->getHeight());
	mng_ = entityManager_->addEntity();

	background_ = entityManager_->addEntity();
	background_->addComponent<Transform>(0, 0, 2560, 1440);
	background_->addComponent<Sprite>(game_->getGame()->getTextureMngr()->getTexture(Resources::CorkBG));

	bottomPanel_ = entityManager_->addEntity(Layers::CharacterLayer);
	rightPanel_ = entityManager_->addEntity(Layers::LastLayer);
	double rightPanelW = game_->getGame()->getWindowWidth() / 6;
	double rightPanelH = game_->getGame()->getWindowHeight();
	Transform* rpTr = rightPanel_->addComponent<Transform>(game_->getGame()->getWindowWidth() - rightPanelW, 0.0, rightPanelW, rightPanelH);
	rightPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x00FFFFFF) });
	rightPanel_->setUI(true);


	auto textTitle_ = rightPanel_->addComponent<Text>("", rpTr->getPos(), -1, Resources::RobotoTest24, 0);
	textTitle_->setSoundActive(false);
	auto textDescription_ = rightPanel_->addComponent<Text>("", rpTr->getPos() + Vector2D(0, 116), rpTr->getW(), Resources::RobotoTest24, 0);
	textDescription_->setSoundActive(false);



	double bottomPanelW = game_->getGame()->getWindowWidth() - rightPanelW;
	double bottomPanelH = game_->getGame()->getWindowHeight() / 5;
	bottomPanel_->addComponent<Transform>(0, game_->getGame()->getWindowHeight() - bottomPanelH, bottomPanelW, bottomPanelH);
	bottomPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x00FF00FF) });
	bottomPanel_->setUI(true);

	scroll_ = mng_->addComponent<ScrollerLimited>(0, bottomPanelW);

	cursor_ = entityManager_->addEntity();
	cursor_->addComponent<CameraController>(camera_);

	auto hidePannelButton = entityManager_->addEntity(Layers::LastLayer);
	hidePannelButton->addComponent<Transform>(5, game_->getGame()->getWindowHeight() - 10 - bottomPanelH / 2, 40, 20);
	hidePannelButton->addComponent<Rectangle>(SDL_Color{ COLOR(0xffccccff) });
	hidePannelButton->setUI(true);


	hidePannelButton->addComponent<ButtonOneParametter<Chinchetario*>>(std::function<void(Chinchetario*)>([](Chinchetario* ch) {ch->toggleBottomPanel(); }), this);

	playerClues_ = game_->getStoryManager()->getPlayerClues();
	for (int i = 0; i < game_->getStoryManager()->getPlayerCentralClues().size(); i++) {
		playerClues_.push_back(game_->getStoryManager()->getPlayerCentralClues()[i]);
	}
	for (int i = 0; i < playerClues_.size(); i++)
	{
		//A�adimos la informaci�n com�n de las pistas centrales y normales a la entidad
		Clue* c = playerClues_[i];
		Entity* entity = (c->entity_ = entityManager_->addEntity(Layers::DragDropLayer));
		double clueSize = 80;
		scroll_->addItem(entity->addComponent<Transform>(clueSize + (2 * clueSize) * i, game_->getGame()->getWindowHeight() - (bottomPanelH / 2 + clueSize / 2), clueSize, clueSize), i);
		entity->addComponent<DragDrop>(this, [](Chinchetario* ch, Entity* e) {ch->clueDropped(e); });
		entity->addComponent<ButtonClue>([](Text* title, Text* description, string newT, string newD)
			{title->setText(newT); description->setText(newD); }, textTitle_, textDescription_, playerClues_[i]->title_, playerClues_[i]->description_);
		//Si no es una pista central
		SDL_Color col;
		if (c->id_ < Resources::ClueIDs::lastClueID) {
			switch (c->type_) {
			case Resources::ClueType::Object:
				col = SDL_Color{ COLOR(0xff000000) };
				break;
			case Resources::ClueType::Person:
				col = SDL_Color{ COLOR(0x00ff0000) };
				break;
			case Resources::ClueType::Place:
				col = SDL_Color{ COLOR(0x0000ffff) };
				break;
			}
			entity->addComponent<Rectangle>(col);
		}
		//si es una pista central
		else {
			entity->addComponent<Rectangle>(SDL_Color{ COLOR(0xff00ffff) });
			//Guardamos los datos necesarios de la pista central
			Transform* clueTR = GETCMP2(entity, Transform);
			double nLinks = static_cast<CentralClue*>(c)->links_.size();
			//Las pistas se dibujar�n alrededor de la circunferencia definida por estos datos:
			double angle = 360 / (nLinks);
			double rd = clueTR->getH() / 2;
			//Colocamos cada chincheta en su sitio (cada pista central tendr� x n�mero de chinchetas)
			for (int j = 0; j < nLinks; j++) {
				Resources::ClueIDs thisLinkID = static_cast<CentralClue*>(c)->links_[j];
				Resources::ClueType thisLinkType = game_->getStoryManager()->getClues().at(thisLinkID)->type_;
				double rad = M_PI / 180;
				double pinY = rd * cos(rad * (180 + angle * j)); //posici�n en X y en Y LOCALES de la chincheta
				double pinX = rd * sin(rad * (180 + angle * j));
				Vector2D pinPos = Vector2D(pinX + rd, pinY + rd); //posici�n en X y en Y GLOBALES de la chincheta
				pinPos = pinPos + clueTR->getPos();
				//Creamos una entidad para la chincheta con la posici�n que acabamos de calcular
				Entity* pin = entityManager_->addEntity(Layers::LastLayer); //La layer la puse para testear porque es la que est� m�s arriba
				pin->setActive(false);
				int pinSize = 10; int pinOffset = pinSize / 2;
				pin->addComponent<Transform>(pinPos.getX() - pinOffset, pinPos.getY() - pinOffset, pinSize, pinSize)->setParent(clueTR);
				//pin->addComponent<Line>(Vector2D{ pinPos.getX() - pinOffset, pinPos.getY() - pinOffset }, Vector2D{ pinPos.getX() - pinOffset, pinPos.getY() - pinOffset }, 4);
				pin->addComponent<Pin>(this, static_cast<CentralClue*>(c), thisLinkID, thisLinkType, [](Chinchetario* ch, Entity* pin) {ch->pinDropped(pin); });
				switch (thisLinkType)
				{
				case Resources::ClueType::Object:
					col = SDL_Color{ COLOR(0xff000000) };
					break;
				case Resources::ClueType::Person:
					col = SDL_Color{ COLOR(0x00ff0000) };
					break;
				case Resources::ClueType::Place:
					col = SDL_Color{ COLOR(0x0000ffff) };
					break;
				}
				pin->addComponent<Rectangle>(col);
			}
			clueEntities_.push_back(entity);
		}
	}
	relocateClues();
}

void Chinchetario::update()
{
	State::update();
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

void Chinchetario::clueDropped(Entity* e)
{
	size_t i = 0;
	while (e != playerClues_[i]->entity_)
	{
		i++;
	}
	bool b = !checkClueInBottomPanel(e);
	if (b && !playerClues_[i]->placed_) scroll_->removeItem(e->getComponent<Transform>(ecs::Transform), i);
	else if (!b && playerClues_[i]->placed_) {
		scroll_->addItem(e->getComponent<Transform>(ecs::Transform), i);
	}
	playerClues_[i]->placed_ = b;
	Transform* cTR = GETCMP2(playerClues_[i]->entity_, Transform);
	cTR->setActiveChildren(b);
	if (playerClues_[i]->entity_->isUI())
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
			//Drag* d = GETCMP2(t->getEntity(), Drag);
			//Pin* p = static_cast<Pin*>(d);
			Vector2D newPos = { t->getPos().getX() + t->getW() / 2, t->getPos().getY() + t->getH() / 2 };
			if (p->getState())
				l->moveTo(newPos);
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
	relocateClues();
	//if (!clues[i]->placed_)
	//    clues[i]->entity_->setLayer(Layers::LastLayer);
}
void Chinchetario::pinDropped(Entity* e) {
	InputHandler* ih = InputHandler::instance();
	Vector2D mpos = ih->getMousePos();
	SDL_Point point = { mpos.getX(), mpos.getY() };
	Transform* CCtr = GETCMP2(e, Transform);
	Drag* d = GETCMP2(e, Drag);
	Pin* p = static_cast<Pin*>(d);
	Clue* linked = p->getActualLink();
	Transform* tr;
	SDL_Rect rect;
	Entity* prevE = nullptr;
	//Si estaba conectada a otra pista, corta la union
	if (p->getState()) {
		prevE = p->getActualLink()->entity_;
		Transform* prevTR = GETCMP2(prevE, Transform);
		if (prevTR->getParent() != nullptr)
			prevTR->eliminateParent();
		p->setState(false);
	}
	DragDrop* lastCorrectDD = nullptr;
	for (Clue* c : playerClues_) {
		if (c->placed_ && c->id_ < Resources::ClueIDs::lastClueID) {		//Si est� en el tablero y no es principal
			tr = c->entity_->getComponent<Transform>(ecs::Transform);
			Vector2D pos = tr->getPos() - camera_->getPos();
			rect = SDL_Rect RECT(pos.getX(), pos.getY(), tr->getW(), tr->getH());
			DragDrop* dd = static_cast<DragDrop*>(c->entity_->getComponent<Drag>(ecs::Drag));
			if (SDL_PointInRect(&point, &rect) && isHigherDragable(dd)) {	//Si hace clic en ella y es la que est� m�s adelante
				if (lastCorrectDD != nullptr) {		//Si la anterior en entrar aqu� era del tipo correcto, deshace
					lastCorrectDD->detachLine();
					tr->eliminateParent();
					p->resetActualLink();
				}
				if (p->isSameType(c->type_)) {		//Si es del tipo correcto
					p->setActualLink(c);
					tr->setParent(CCtr);
					p->associateLine(static_cast<DragDrop*>(c->entity_->getComponent<Drag>(ecs::Drag)));
					lastCorrectDD = dd;
				}
				else lastCorrectDD = nullptr;
			}
		}
	}
	if (!p->getState()) {	//Si se queda sin enganchar, borra la l�nea
		p->eliminateLine();
		if (prevE != nullptr)
			static_cast<DragDrop*>(prevE->getComponent<Drag>(ecs::Drag))->detachLine();
	}
	resetDraggedItem();
}

void Chinchetario::relocateClues()
{
	size_t size = playerClues_.size();
	int numPlaced = 0;
	for (int i = 0; i < size; i++)
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
		hideBottomPanel();
}
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
			c->entity_->setActive(b);
	}
}