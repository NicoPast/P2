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
	//Creación de pistas
	clues.resize(ClueIDs::lastClueID);

	clues[ClueIDs::Arma_Homicida] = 
		new Clue(string("Arma Homicida"), 
			string("Un cuchillo ensangrentado con un adorno en la empuñadura"),
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
	addPlayerClue(ClueIDs::Cuadro_De_Van_Damme);
	addPlayerClue(ClueIDs::Retratrato_De_Dovahkiin);

	//Crear background, jugador y telefono
	Entity* bg =entityManager_->addEntity(0);
	bg->addComponent<Transform>(0, 0, LoremIpsum_->getGame()->getWindowWidth(), LoremIpsum_->getGame()->getWindowHeight());
	createPhone(entityManager_, LoremIpsum_);
	Entity* player = createPlayer(entityManager_);
	
	//-----------------------------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------------CREACIÓN DE ESCENAS----------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------------------------//
	scenes.resize(lastSceneID);
	//-----------------------CalleDelProfesor-----------------------//
	Scene* calleProfesor = new Scene();
	scenes[SceneIDs::calleProfesor] = calleProfesor;

	Entity* profesor = addEntity(4);
	Vector2D p2 = { 200, 0 };
	Text* texto2 = profesor->addComponent<Text>("ESTOY AQUI", p2, 600, LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 0);
	texto2->addSoundFX(Resources::Bip);
	texto2->addSoundFX(Resources::Paddle_Hit);
	Dialog* profesorDialog = profesor->addComponent<Dialog>(ActorID::Profesor, texto2,1);

	Dialog::dialogOption profesorOption1;
	Dialog::dialogLine line;
	line.line_ = "Esto es un dialogo. Si pulsas l cambias de escena";
	line.name_ = ActorID::Profesor;
	profesorOption1.conversation_[0]=line;

	profesorDialog->getOptions().push_back(profesorOption1);
	calleProfesor->entities.push_back(profesor);


	//-----------------------CasaDelProfesor-----------------------//
	Scene* casaDelProfesor = new Scene();
	casaDelProfesor->background = LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::BlackHole);
	scenes[SceneIDs::Casa_Del_Profesor] = casaDelProfesor;
	bgSprite_= bg->addComponent<Sprite>(casaDelProfesor->background);

			//---------------Interactuables----------------//
	list<Interactable*> interactables;
	Entity* siYeah = createInteractable(entityManager_, interactables, 3, Vector2D(400, 250), 500, "Silla", SDL_Color{ COLOR(0xFFC0C0C0) },
		LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 30, 30);
	casaDelProfesor->entities.push_back(siYeah);
	Entity* meSah = createInteractable(entityManager_, interactables, 3, Vector2D(450, 250), 500, "Mesa", SDL_Color{ COLOR(0xC0C0C0C0) },
		LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 30, 30);
	casaDelProfesor->entities.push_back(meSah);

	Entity* iLog = entityManager_->addEntity(4);
	iLog->addComponent<InteractableLogic>(interactables, player->getComponent<Transform>(ecs::Transform));

			//---------------Texto----------------//
	Vector2D p = { 20, 0 };
	Entity* t = addEntity(1);
	Text* texto = t->addComponent<Text>("ey", p, 200, LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 100);
	texto->setNextText("Hola wenas soy wario");
	texto->addSoundFX(Resources::Bip);
	texto->addSoundFX(Resources::Paddle_Hit);
	casaDelProfesor->entities.push_back(t);



			//---------------Scroller----------------//
	Entity* gameManager = entityManager_->addEntity(0);
	Scroller* scroller = gameManager->addComponent<Scroller>();
	//ScrollerLimited* scroller = gameManager->addComponent<ScrollerLimited>();
	scroller->addItem(player->getComponent<Transform>(ecs::Transform));

}
Entity* StoryManager::createInteractable(EntityManager* EM, list<Interactable*>&interactables, int layer, Vector2D pos, int textSize, string name, const SDL_Color& color, Font* font, int w, int h)
{
	Entity* e = EM->addEntity(3);
	
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
	int offset = mobTr->getW()/16.0;

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

Entity* StoryManager::createPlayer(EntityManager* EM)
{
	Entity* player = EM->addEntity(0);
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>();
	player->addComponent<PlayerMovement>();
	player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	tp->setPos(200, 250);
	tp->setWH(30, 30);
	return player;
}
void StoryManager::changeScene(SceneIDs newScene)
{
	if (currentScene!=nullptr)
	{
		for (Entity* e : currentScene->entities)
		{
			e->setActive(false);
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