#include "Chinchetario.h"
#include "LoremIpsum.h"
#include "InventoryViewer.h"
#include "ButtonClue.h"
#include "ButtonIcon.h"
#include "StoryManager.h"

Chinchetario::Chinchetario(LoremIpsum* game, StoryManager* storyManager) : State(game), storyManager_(storyManager) {
	init();
};

void Chinchetario::init() {
	//dos entidades principales: visor de texto y visor del inventario

		//visor del texto de las pistas
	txtP_ = entityManager_->addEntity(Layers::LastLayer);
	Transform* txtTR = txtP_->addComponent<Transform>();
	txtP_->addComponent<Rectangle>(SDL_Color{ COLOR(0x604E4B00) });
	txtTR->setWH(game_->getGame()->getWindowWidth()/6, game_->getGame()->getWindowHeight());
	txtTR->setPos(game_->getGame()->getWindowWidth()-txtTR->getW(), 0);
	textTitle_ = txtP_->addComponent<Text>("", txtTR->getPos(), -1, game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 0, false);
	textTitle_->setSoundActive(false);
	textDescription_ = txtP_->addComponent<Text>("", txtTR->getPos()+Vector2D(0, 100+16), txtTR->getPos().getX()+txtTR->getW(), game_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 0, false);
	textDescription_->setSoundActive(false);

	//visor del inventario
	inv_ = entityManager_->addEntity();
	Transform* invTR = inv_->addComponent<Transform>();
	InventoryViewer* invV = inv_->addComponent<InventoryViewer>(this);
	inv_->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	invTR->setWH(game_->getGame()->getWindowWidth()-txtTR->getW(), game_->getGame()->getWindowHeight()/5);
	invTR->setPos(0, (game_->getGame()->getWindowHeight() - invTR->getH()));
	SDL_Color c = { COLOR(0xFF00FFFF) };

	//Entity* pista = entityManager_->addEntity(Layers::DragDropLayer);
	//Transform* pTR = pista->addComponent<Transform>();
	//pista->addComponent<Rectangle>(c);
	//DragDrop* drdr = pista->addComponent<DragDrop>(this);
	//pista->addComponent<ButtonClue>([](Text* title, Text* description, string newT, string newD)
	//	{title->setText(newT); description->setText(newD); },
	//	textTitle_, textDescription_, storyManager_->getPlayerClues()[0]->title_, storyManager_->getPlayerClues()[0]->description_);
	//pTR->setWH(50, 50);
	//pTR->setPos(800, 800);
	//inactivePistas_.push_back(pista);
	
	vector<string>clueTitles;
	
	SDL_Color c2[6] = { COLOR(0x00FF00FF),  { COLOR(0xFF0000FF) },  { COLOR(0x0000FFFF) }, { COLOR(0xFFFF00FF) }, { COLOR(0x00FFFFFF) }, { COLOR(0xFFFFFFFF) } };
	ClueIDs ids[6] = { ClueIDs::Alfombra_Rota, ClueIDs::Arma_Homicida, ClueIDs::Cuadro_De_Van_Damme, ClueIDs::Retratrato_De_Dovahkiin,ClueIDs::Retratrato_De_Dovahkiin,ClueIDs::Retratrato_De_Dovahkiin };
	
	//c = { COLOR(0x00FF00FF) };
	//creamos un vector de pistas (provisional hasta que sepamos como meter las pistas)
	auto clues = storyManager_->getPlayerClues();
	for (auto c : clues)
	{
		Entity* pista = entityManager_->addEntity(Layers::DragDropLayer);
		Transform* pTR = pista->addComponent<Transform>();
		pista->addComponent<Rectangle>(c2[0]);
		pista->addComponent<DragDrop>(this);
		pista->addComponent<ButtonClue>([](Text* title, Text* description, string newT, string newD)
			{title->setText(newT); description->setText(newD); },
			textTitle_, textDescription_, c->title_, c->description_);

		pTR->setWH(50, 50);
		pTR->setPos(800, 800);
		inactivePistas_.push_back(pista);
	}
	//^^^^^^^Las pistas actuales las lleva el storyManager, no hace falta crearlas aquí de nuevo
	//for (int i = 0; i < 6; i++) {
	//	Entity* pista = entityManager_->addEntity(Layers::DragDropLayer);
	//	Transform* pTR = pista->addComponent<Transform>();
	//	pista->addComponent<Rectangle>(c2[i]);
	//	drdr = pista->addComponent<DragDrop>(this);	
	//	pista->addComponent<ButtonClue>([](Text* title, Text* description, string newT, string newD)
	//		{title->setText(newT); description->setText(newD); },
	//		textTitle_, textDescription_, storyManager_->getPlayerClues()[0]->title_, storyManager_->getPlayerClues()[0]->description_);

	//	pTR->setWH(50, 50);
	//	pTR->setPos(800, 800);
	//	inactivePistas_.push_back(pista);
	//}
	invV->setPistas(&inactivePistas_);
	invV->renderizaPistas();


	Entity* quitBut = entityManager_->addEntity(4);
	Transform* qBtr = quitBut->addComponent<Transform>();
	quitBut->addComponent<Rectangle>();
	quitBut->addComponent<ButtonIcon>([](LoremIpsum* game, StoryManager* sm) {game->getStateMachine()->actualState()->deactivate(); }, game_);
	qBtr->setPos(0, 0);
	qBtr->setWH(40, 40);
}

vector<Entity*>* Chinchetario::getPistas_(bool isActive) {
	//true = pistas activas
	//false = pistas inactivas, aka pistas en el inventario
	if (isActive) return &activePistas_;
	else return &inactivePistas_;
}

void Chinchetario::update() {
	añadePista();
	State::update();
}

void Chinchetario::añadePista() {
	InputHandler* ih = InputHandler::instance();
	if (dd_ != nullptr) {
		//Si acaba de soltar la pista agarrada
		if (!dd_->getDragging()) {


			Vector2D mousePos = ih->getMousePos();			 //Guarda la posición del ratón
			SDL_Point p = { mousePos.getX(), mousePos.getY() };

			Transform* pTR = activePistas_.at(dragIndex_)->getComponent<Transform>(ecs::Transform);
			Transform* invTR = inv_->getComponent<Transform>(ecs::Transform);
			Transform* txtpTR = txtP_->getComponent<Transform>(ecs::Transform);

			SDL_Rect invRect = RECT(invTR->getPos().getX(), invTR->getPos().getY(), invTR->getW(), invTR->getH());
			SDL_Rect txtRect = RECT(txtpTR->getPos().getX(), txtpTR->getPos().getY(), txtpTR->getW(), txtpTR->getH());
			if (SDL_PointInRect(&p, &invRect)) {
				//la vuelve a poner en la posición inicial
				inactivePistas_.push_back(activePistas_.at(dragIndex_));
				activePistas_.erase(activePistas_.begin() + dragIndex_);
				InventoryViewer* invV = inv_->getComponent<InventoryViewer>(ecs::InventoryViewer);
				if (inactivePistas_.size() >= 5) {
					pTR->setPos(800, 800);
				}
				invV->renderizaPistas();
			}
			else if (SDL_PointInRect(&p, &txtRect)) {
				pTR->setPos(initPistaPos_);
			}

			dd_ = nullptr;
		}
	}
	else if (activePistas_.size() > 0) {
		//pilla qué pista está siendo agarrada
		int i = 0, j = activePistas_.size();

		dd_ = activePistas_.at(i)->getComponent<DragDrop>(ecs::DragDrop);
		while (!dd_->getDragging() && i < j - 1) {
			i++;
			dd_ = activePistas_.at(i)->getComponent<DragDrop>(ecs::DragDrop);
		}
		if (!dd_->getDragging()) dd_ = nullptr;
		else {
			dragIndex_ = i;
			Transform* pTR = activePistas_.at(i)->getComponent<Transform>(ecs::Transform);
			initPistaPos_ = pTR->getPos();
		}
	}
}
bool Chinchetario::compareDragLayerIndex(int index, int layer) {
	bool bigger = (index > dragLayerIndex);
	if (bigger) {
		if (dragLayerIndex >= 0) {
			auto actualLayer = entityManager_->getLayer(layer);
			actualLayer[dragLayerIndex].get()->getComponent<DragDrop>(ecs::DragDrop)->deactivateDrag();
		}
		dragLayerIndex = index;
	}
	return bigger;
}

