#include "StoryManager.h"
#include "DialogComponent.h"
#include "LoremIpsum.h"
#include "SDLGame.h"
#include "DragDrop.h"
#include "ButtonIcon.h"
#include "Rectangle.h"
#include "Phone.h"
#include "ScrollerLimited.h"
#include "PlayerKBCtrl.h"
#include "PlayerMovement.h"
#include "Interactable.h"
#include "InteractableLogic.h"
#include "Sprite.h"
#include "Phone.h"
#include "DirReader.h"

#include "Tween.h"

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
	//por ahora le meto un rect porque no tiene sprite component
	entity_->addComponent<Transform>(info.x_, info.y_, w, h);
	entity_->addComponent<Rectangle>(SDL_Color{COLOR(0x55ff75ff)});
	Interactable* in = entity_->addComponent<Interactable>("Prueba", false);
	sm->interactables_.push_back(in);

	if (info.dialog_ != "")
	{
		entity_->addComponent<DialogComponent>(sm->getPlayer(), this,sm)->setDialog(sm->getDialog(info.dialog_));
		in->setCallback([](Entity* player, Entity* other) {other->getComponent<DialogComponent>(ecs::DialogComponent)->interact(); }, entity_);
	}
};

void StoryManager::init()
{
	backgroundViewer_ = addEntity(0);
	backgroundViewer_->addComponent<Transform>(0, 0, LoremIpsum_->getGame()->getWindowWidth(), LoremIpsum_->getGame()->getWindowHeight());
	bgSprite_ = backgroundViewer_->addComponent<Sprite>(nullptr);
	backgroundViewer_->setActive(true);

	dialogBox_ = addEntity(1);
	dialogBox_->setActive(true);
	int h = LoremIpsum_->getGame()->getWindowHeight() / 5;
	int wh = LoremIpsum_->getGame()->getWindowHeight();
	dialogBox_->addComponent<Transform>(0,wh-h,  LoremIpsum_->getGame()->getWindowWidth(),h);
	dialogBox_->addComponent<Rectangle>(SDL_Color{COLOR(0xcc8866ff)})->setEnabled(false);
	
	

	Vector2D p2 = { 0.0, LoremIpsum_->getGame()->getWindowHeight() - 150.0 };
	dialogBoxText_ = dialogBox_->addComponent<Text>("", p2+Vector2D(10,30), LoremIpsum_->getGame()->getWindowWidth(), Resources::RobotoTest24, 100);
	dialogBoxText_->addSoundFX(Resources::Bip);
	dialogBoxText_->addSoundFX(Resources::Paddle_Hit);
	dialogBoxActorName_ = dialogBox_->addComponent<Text>("", p2, GETCMP2(dialogBox_,Transform)->getW(), Resources::RobotoTest24, 0);


	phone_ = createPhone(entityManager_, LoremIpsum_);
	player_ = createPlayer(entityManager_, GETCMP2(phone_, Phone));

	std::string extension = ".dialog";
	auto files = findFiles("../assets/dialogs/", extension);
	for (auto file : files)
	{
		Dialog d = Dialog(file);
		d.dialogName_ = file.path().filename().string();
		d.dialogName_ = d.dialogName_.substr(0, d.dialogName_.size() - extension.size());
		dialogs_[d.dialogName_] = d;
	}


	for (int i  = 0; i<Resources::SceneID::lastSceneID;i++)
	{
		scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].backgroundId_), static_cast<Resources::SceneID>(i));
		scenes_[i]->mapPos = Resources::scenes_[i].mapPos_;
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

	availableScenes_.push_back(scenes_[Resources::calleProfesor]);
	availableScenes_.push_back(scenes_[Resources::Casa_Del_Profesor]);
}


Entity* StoryManager::createInteractable(EntityManager* EM, list<Interactable*>&interactables, int layer, Vector2D pos, 
	int textSize, string name, const SDL_Color& color, Resources::FontId font, int w, int h)
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

	mobTr->setPos(loremIpsum->getGame()->getWindowWidth()-mobTr->getW()-60, loremIpsum->getGame()->getWindowHeight());
	//mobTr->setPos(loremIpsum->getGame()->getWindowWidth() / 2, loremIpsum->getGame()->getWindowHeight() /2);
	Phone* mobileComp = mobile->addComponent<Phone>();
	mobile->addComponent<Tween>(mobTr->getPos().getX(), loremIpsum->getGame()->getWindowHeight() - mobTr->getH(), 10, mobTr->getW() + 30, mobTr->getH() + 30);
	//mobile->addComponent<Tween>(mobTr->getPos().getX(), mobTr->getPos().getY(), 10, mobTr->getW() + 30, mobTr->getH() + 30);
	vector<Transform*> icons;
	for (int i = 0; i < 13; i++) {
		Entity* icon = EM->addEntity(3);
		Transform* itr = icon->addComponent<Transform>();
		icon->addComponent<Rectangle>();
		icon->addComponent<ButtonIcon>([](LoremIpsum* game, StoryManager* sm) { game->getStateMachine()->PlayApp(StateMachine::APPS::Maps, sm); }, loremIpsum, this);
		itr->setWH(mobTr->getW()/4, mobTr->getW() / 4);
		itr->setPos(mobTr->getPos().getX() + offset + (i % 3) * (itr->getW()+ offset), mobTr->getPos().getY()+ offset + (i / 3) * (itr->getH() + offset));
		icons.push_back(itr);
		itr->setParent(mobTr);
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