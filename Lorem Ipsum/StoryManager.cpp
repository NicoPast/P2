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
#include "Phone.h"
Entity*  StoryManager::addEntity(int layer)
{
	Entity* e = entityManager_->addEntity(layer);
	e->setActive(false);
	return e;
}

Clue::Clue(Resources::ClueInfo info)
{
	title_ = info.title_;
	description_ = info.description_;
	type_ = info.type_;
	id_ = info.id_;
}


Actor::Actor(StoryManager* sm, Resources::ActorInfo info, Vector2D pos, int w, int h, Resources::SceneID currentScene)
{
	name_ = info.name_;
	currentScene_ = sm->getScene(currentScene);
	sprite_ = nullptr; //todo
	portrait_ = nullptr; //todo
	entity_ = sm->addEntity(1);
	entity_->addComponent<Transform>(pos.getX(), pos.getY(), w, h);
	entity_->addComponent<Rectangle>();
	entity_->addComponent<Text>("", Vector2D(pos.getX(), pos.getY() - 26), pos.getX()+w)->setTextDelay(0);
	Interactable* in = entity_->addComponent<Interactable>("Prueba", false);
	sm->interactables_.push_back(in);
};

void StoryManager::init()
{
	backgroundViewer_ = addEntity(0);
	bgSprite_ = backgroundViewer_->addComponent<Sprite>(nullptr);
	backgroundViewer_->addComponent<Transform>(0,0,1280,720);

	phone_ = createPhone(entityManager_, LoremIpsum_);
	player_ = createPlayer(entityManager_, GETCMP2(phone_, Phone));



	for (int i  = 0; i<Resources::SceneID::lastSceneID;i++)
	{
		scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Boooo));
	}
	for (auto& a : Resources::actors_)
	{
		Actor* e = new Actor(this, a, a.startScene_);
		scenes_[a.startScene_]->entities.push_back(e->getEntity());
		actors_[a.id_] = e;
	}
	for (auto& c : Resources::clues_)
	{
		clues_[c.id_] = new Clue(c);
	}
	Entity* e = addEntity(1);
	e->addComponent<InteractableLogic>(interactables_, GETCMP2(player_, Transform));
	e->setActive(true);
	playerClues_.push_back(clues_[Resources::Retratrato_De_Dovahkiin]);
	playerClues_.push_back(clues_[Resources::Alfombra_Rota]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida2]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida3]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida4]);
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
	for (int i = 0; i < scenes_.size(); i++)
	{
		delete scenes_[i];
	};
	for (int i = 0; i < clues_.size(); i++)
	{
		delete clues_[i];
	};
	for (size_t i = 0; i < Resources::lastActorID; i++)
	{
		delete actors_[i];
	};
}
void StoryManager::changeScene(Resources::SceneID newScene)
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
	currentScene = scenes_[newScene];
	getBackgroundSprite()->setTexture(currentScene->background);
	for (Entity* e : currentScene->entities)
	{
		e->setActive(true);
		Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
		if ( it!= nullptr)
			it->setActive(true);
	}
}