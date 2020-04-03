#include "StoryManager.h"
#include "Dialog.h"
#include "LoremIpsum.h"
#include "SDLGame.h"
#include "DragDrop.h"
#include "ButtonIcon.h"
#include "Rectangle.h"
#include "Phone.h"
#include "Scroller.h"
#include "ScrollerLimited.h"
#include "PlayerKBCtrl.h"
#include "PlayerMovement.h"
#include "Interactable.h"
#include "InteractableLogic.h"
#include "Sprite.h"
Entity*  StoryManager::addEntity(int layer)
{
	Entity* e = entityManager_->addEntity(layer);
	e->setActive(false);
	return e;
}

void StoryManager::init()
{
	//-----------------------------------------------------------------------------------------------------------------------------------//
	//  _____   _          _       _                     
	//  |  __ \(_)        | |     (_)                    
	//  | |  | |_ ___  ___| | __ _ _ _ __ ___   ___ _ __ 
	//  | |  | | / __|/ __| |/ _` | | '_ ` _ \ / _ \ '__|
	//  | |__| | \__ \ (__| | (_| | | | | | | |  __/ |   
	//  |_____/|_|___/\___|_|\__,_|_|_| |_| |_|\___|_|   
	//-----------------------------------------------------------------------------------------------------------------------------------//
	//Este m�todo en el futuro leer� todo esto de archivos y ser� m�s automatizado
	//-----------------------------------------------------------------------------------------------------------------------------------//


	//Creaci�n de pistas
	clues.resize(ClueIDs::lastClueID);

	clues[ClueIDs::Arma_Homicida] = 
		new Clue(string("Arma Homicida"), 
			string("Un cuchillo ensangrentado con un adorno en la empu�adura"),
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));
	clues[ClueIDs::Arma_Homicida2] =
		new Clue(string("Arma Homicida"),
			string("Un cuchillo ensangrentado con un adorno en la empu�adura"),
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));
	clues[ClueIDs::Arma_Homicida3] =
		new Clue(string("Arma Homicida"),
			string("Un cuchillo ensangrentado con un adorno en la empu�adura"),
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));
	clues[ClueIDs::Arma_Homicida4] =
		new Clue(string("Arma Homicida"),
			string("Un cuchillo ensangrentado con un adorno en la empu�adura"),
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	clues[ClueIDs::Alfombra_Rota] =
		new Clue("Alfombra Rota",
			"Una pieza de tela que formaba parte de una alfombra en la cocina del profesor.",
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	clues[ClueIDs::Cuadro_De_Van_Damme] =
		new Clue("Cuadro de Van Damme",
			"Un cuadro de Van Damme con una firma. MB",
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	clues[ClueIDs::Retratrato_De_Dovahkiin] =
		new Clue("Retrato de Dovahkiin",
			"El mejor juego de la historia",
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	addPlayerClue(ClueIDs::Alfombra_Rota);
	addPlayerClue(ClueIDs::Arma_Homicida);
	addPlayerClue(ClueIDs::Arma_Homicida2);
	addPlayerClue(ClueIDs::Arma_Homicida3);
	addPlayerClue(ClueIDs::Arma_Homicida4);
	addPlayerClue(ClueIDs::Cuadro_De_Van_Damme);
	addPlayerClue(ClueIDs::Retratrato_De_Dovahkiin);

	//Crear background, jugador y telefono
	Entity* bg =entityManager_->addEntity(0);
	bg->addComponent<Transform>(0, 0, LoremIpsum_->getGame()->getWindowWidth(), LoremIpsum_->getGame()->getWindowHeight());
	Entity* phone = createPhone(entityManager_, LoremIpsum_);
	Entity* player = createPlayer(entityManager_, phone->getComponent<Phone>(ecs::Phone));
	
	//-----------------------------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------------CREACI�N DE ESCENAS----------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------------------//
	scenes.resize(lastSceneID);
	//-----------------------CalleDelProfesor-----------------------//
	Scene* calleProfesor = new Scene();
	scenes[SceneIDs::calleProfesor] = calleProfesor;

	Entity* profesor = addEntity(4);
	profesor->addComponent<Transform>(0, LoremIpsum_->getGame()->getWindowHeight() - 200, LoremIpsum_->getGame()->getWindowWidth(), 200);
	Dialog* profesorDialog = profesor->addComponent<Dialog>(player, ActorID::Profesor, 1);

	Dialog::dialogOption profesorOption1(2);
	Dialog::dialogLine line;
	line.line_ = "Esto es un dialogo. Presiona enter para el siguiente mensaje";
	line.name_ = ActorID::Profesor;

	Dialog::dialogLine line2;
	line2.line_ = "Eso de la derecha es una puerta, guap@";
	line2.name_ = ActorID::Profesor;

	profesorOption1.conversation_[0] = line;
	profesorOption1.conversation_[1] = line2;
	profesorOption1.startLine_ = "";

	profesorDialog->getOptions()[0] = (profesorOption1);
	calleProfesor->entities.push_back(profesor);


	//-----------------------CasaDelProfesor-----------------------//
	Scene* casaDelProfesor = new Scene();
	casaDelProfesor->background = LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::BlackHole);
	scenes[SceneIDs::Casa_Del_Profesor] = casaDelProfesor;
	bgSprite_= bg->addComponent<Sprite>(casaDelProfesor->background);

			//---------------Interactuables----------------//
	list<Interactable*> interactables;
	Entity* profesorCollider = createInteractable(entityManager_, interactables, 3, Vector2D(400, 250), 500, "Presiona E", SDL_Color{ COLOR(0xCC7777) },
		LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 30, 30);
	Interactable* it = profesorCollider->getComponent<Interactable>(ecs::Interactable);
	it->setActive(true);
	it->setCallback([](Entity* player, Entity* other) {other->getComponent<Dialog>(ecs::Dialog)->interact();}, profesor);

	Entity* puerta = createInteractable(entityManager_, interactables, 3, Vector2D(500, 250), 650, "Soy una puerta (E)", SDL_Color{ COLOR(0xCC7777) },
		LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 30, 30);
	Interactable* puertaIt = puerta->getComponent<Interactable>(ecs::Interactable);
	puertaIt->setActive(true);
	puertaIt->setCallback([](Entity* player, Entity* other) { static_cast<PlayState*>(player->getState())->getStoryManager()->changeScene(SceneIDs::Casa_Del_Profesor); }, puerta);


	calleProfesor->entities.push_back(profesorCollider);
	calleProfesor->entities.push_back(puerta);

	Entity* siYeah = createInteractable(entityManager_, interactables, 3, Vector2D(400, 250), 500, "Silla", SDL_Color{ COLOR(0xFFC0C0C0) },
		LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 30, 30);
	casaDelProfesor->entities.push_back(siYeah);

	Entity* meSah = createInteractable(entityManager_, interactables, 3, Vector2D(450, 250), 500, "Mesa", SDL_Color{ COLOR(0xC0C0C0C0) },
		LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 30, 30);
	casaDelProfesor->entities.push_back(meSah);

	Entity* iLog = entityManager_->addEntity(4);
	iLog->addComponent<InteractableLogic>(interactables, player->getComponent<Transform>(ecs::Transform));

			//---------------Texto de wario----------------//
	Vector2D p = { 20, 0 };
	Entity* t = addEntity(1);
	Text* texto = t->addComponent<Text>("ey", p, 200, LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 100);
	texto->addSoundFX(Resources::Bip);
	texto->addSoundFX(Resources::Paddle_Hit);
	casaDelProfesor->entities.push_back(t);



	//		//---------------Scroller----------------//
	//Entity* gameManager = entityManager_->addEntity(0);
	//Scroller* scroller = gameManager->addComponent<Scroller>();
	////ScrollerLimited* scroller = gameManager->addComponent<ScrollerLimited>();
	//scroller->addItem(player->getComponent<Transform>(ecs::Transform));

}
Entity* StoryManager::createInteractable(EntityManager* EM, list<Interactable*>&interactables, int layer, Vector2D pos, 
	int textSize, string name, const SDL_Color& color, Font* font, int w, int h)
{
	Entity* e = EM->addEntity(1);
	
	Transform* t = e->addComponent<Transform>();
	e->setActive(false);
	e->addComponent<Text>("", Vector2D(pos.getX(),pos.getY()-26), textSize, font, 0);
	Interactable* in = e->addComponent<Interactable>(name, false);
	e->addComponent<Rectangle>(color);
	t->setPos(pos);
	t->setWH(w, h);
	interactables.push_back(in);
	return e;
}
Entity* StoryManager::createPhone(EntityManager* EM, LoremIpsum* loremIpsum)
{
	Entity* mobile = EM->addEntity(2); 
	Transform* mobTr = mobile->addComponent<Transform>();
	mobile->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
	mobTr->setWH(loremIpsum->getGame()->getWindowWidth()/5.0, loremIpsum->getGame()->getWindowHeight()/2.0);
	double offset = mobTr->getW()/16.0;

	mobTr->setPos(loremIpsum->getGame()->getWindowWidth()-mobTr->getW()-30, loremIpsum->getGame()->getWindowHeight());
	Phone* mobileComp = mobile->addComponent<Phone>();
	vector<Transform*> icons;
	for (int i = 0; i < 13; i++) {
		Entity* icon = EM->addEntity(3);
		Transform* itr = icon->addComponent<Transform>();
		icon->addComponent<Rectangle>();
		icon->addComponent<ButtonIcon>([](LoremIpsum* game, StoryManager* sm) { game->getStateMachine()->PlayApp(StateMachine::APPS::Chinchetario, sm); }, loremIpsum, this);
		itr->setWH(mobTr->getW()/4, mobTr->getW() / 4);
		itr->setPos(mobTr->getPos().getX() + offset + (i % 3) * (itr->getW()+ offset), mobTr->getPos().getY()+ offset + (i / 3) * (itr->getH() + offset));
		icons.push_back(itr);
	}
	mobileComp->initIcons(icons);
	return mobile;
}

Entity* StoryManager::createPlayer(EntityManager* EM, Phone* p)
{
	Entity* player = EM->addEntity(2);
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>(SDLK_d,SDLK_a,SDLK_w,SDLK_s, p);
	player->addComponent<PlayerMovement>();
	player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	tp->setPos(200, 250);
	tp->setWH(30, 30);
	return player;
}
StoryManager::~StoryManager()
{
	for (int i = 0; i < scenes.size(); i++)
	{
		delete scenes[i];
	};
	for (int i = 0; i < clues.size(); i++)
	{
		delete clues[i];
	};
}
void StoryManager::changeScene(SceneIDs newScene)
{
	if (currentScene!=nullptr)
	{
		for (Entity* e : currentScene->entities)
		{
			e->setActive(false);
			Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
			if (it != nullptr)
				it->setActive(false);
		}
	}
	currentScene = scenes[newScene];
	getBackgroundSprite()->setTexture(currentScene->background);
	for (Entity* e : currentScene->entities)
	{
		e->setActive(true);
		Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
		if ( it!= nullptr)
			it->setActive(true);
	}
}