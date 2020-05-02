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
#include "DirReader.h"
#include "FollowedByCamera.h"
#include "Tween.h"
#include "Animator.h"

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
	eventText_ = info.eventText_;
	type_ = info.type_;
	id_ = info.id_;
	placed_ = false;
	entity_ = nullptr;
}


Actor::Actor(StoryManager* sm, Resources::ActorInfo info, Vector2D pos, int w, int h, Resources::SceneID currentScene)
{
	name_ = info.name_;
	currentScene_ = sm->getScene(currentScene);
	sprite_ = nullptr; //todo
	
	entity_ = sm->addEntity(1);
	//por ahora le meto un rect porque no tiene sprite component
	entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>("Prueba", false);
	in->setIcon(Resources::ChatInteraction);
	sm->interactables_.push_back(in);

	if (info.dialogId_ != -1)
	{
		entity_->addComponent<DialogComponent>(sm->getPlayer(), this, sm)->setDialog(sm->getDialog(info.dialogId_));
		in->setCallback([](Entity* player, Entity* other) {other->getComponent<DialogComponent>(ecs::DialogComponent)->interact(); }, entity_);
	}
	if (info.anim_ != Resources::noAnim)
	{
		entity_->addComponent<Animator<int*>>()->changeAnim(info.anim_);
	}
	else
		entity_->addComponent<Rectangle>(SDL_Color{ COLOR(0x55ff75ff) });
};

void StoryManager::init()
{

	backgroundViewer_ = addEntity(0);
	backgroundViewer_->addComponent<Transform>(0, 0, 2000, 720);
	bgSprite_ = backgroundViewer_->addComponent<Sprite>(nullptr);
	backgroundViewer_->setActive(true);

	dialogBox_ = addEntity(1);
	dialogBox_->setActive(true);
	int h = LoremIpsum_->getGame()->getWindowHeight() / 5;
	int wh = LoremIpsum_->getGame()->getWindowHeight();
	dialogBox_->addComponent<Transform>(0, wh - h, LoremIpsum_->getGame()->getWindowWidth(), h);
	dialogBox_->addComponent<Rectangle>(SDL_Color{ COLOR(0xcc8866ff) })->setEnabled(false);



	Vector2D p2 = { 0.0, LoremIpsum_->getGame()->getWindowHeight() - 150.0 };
	dialogBoxText_ = dialogBox_->addComponent<Text>("", p2 + Vector2D(10, 30), LoremIpsum_->getGame()->getWindowWidth(), Resources::RobotoTest24, 100);
	dialogBoxText_->addSoundFX(Resources::Bip);
	dialogBoxText_->addSoundFX(Resources::Paddle_Hit);
	dialogBoxActorName_ = dialogBox_->addComponent<Text>("", p2, GETCMP2(dialogBox_, Transform)->getW(), Resources::RobotoTest24, 0);


	phone_ = createPhone(entityManager_, LoremIpsum_);
	player_ = createPlayer(entityManager_, GETCMP2(phone_, Phone));

	std::fstream dialogListFile;
	dialogListFile.open("../assets/dialogs/dialogList.conf");
	int size=-1;
	assert(dialogListFile.is_open());
	dialogListFile >> size;
	
	//crear dialogos antes que actores
	for (int i = 0; i < size; i++)
	{
 		string nameOfDialog;
		dialogListFile >> nameOfDialog;
		int index;
		dialogListFile >> index;
 		Dialog* dialog = new Dialog("../assets/dialogs/" + nameOfDialog + ".dialog", index);
		dialogs_[index] = dialog;
		dialog->dialogName_ = nameOfDialog;
		if (dialog->actorID_ != -1)Resources::actors_[(Resources::ActorID)dialog->actorID_].dialogId_ = dialog->id_;
	}


	for (int i  = 0; i<Resources::SceneID::lastSceneID;i++)
	{
		scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].backgroundId_), static_cast<Resources::SceneID>(i), LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].ghBackgroundId_));
		scenes_[i]->mapPos = Resources::scenes_[i].mapPos_;
	}
	for (auto& a : Resources::actors_)
	{
		Actor* e = new Actor(this, a, a.startScene_);
		if(a.ghWorld_)
			scenes_[a.startScene_]->ghEntities.push_back(e->getEntity());
		else scenes_[a.startScene_]->entities.push_back(e->getEntity());
		actors_[a.id_] = e;
	}
	for (auto& c : Resources::clues_)
	{
		clues_[c.id_] = new Clue(c);
	}
	for (auto& c : Resources::centralClues_)
	{
		centralClues_[c.id_] = new CentralClue(c);
	}

	Entity* e = addEntity(1);
	Transform* eTr = e->addComponent<Transform>(0,0,30,30);
	Sprite* eSprite = e->addComponent<Sprite>(nullptr);
	ButtonOneParametter<Interactable*>* eBut = e->addComponent<ButtonOneParametter<Interactable*>>(std::function<void(Interactable*)>([](Interactable* i) {}), nullptr);
	e->addComponent<InteractableLogic>(interactables_, GETCMP2(player_, Transform), eTr, eSprite, eBut);
	e->setActive(true);

	playerClues_.push_back(clues_[Resources::Retratrato_De_Dovahkiin]);
	playerClues_.push_back(clues_[Resources::Alfombra_Rota]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida2]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida3]);
	playerClues_.push_back(clues_[Resources::Arma_Homicida4]);
	playerClues_.push_back(clues_[Resources::Cuadro_De_Van_Damme]);
	playerCentralClues_.push_back(centralClues_[Resources::Central_Clue_1]);
	playerCentralClues_.push_back(centralClues_[Resources::Central_Clue_3]);

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
	in->setIcon(Resources::GhostInteraction);
	e->addComponent<Rectangle>(color);
	t->setPos(pos);
	t->setWH(w, h);
	interactables.push_back(in);
	return e;
}
Entity* StoryManager::createPhone(EntityManager* EM, LoremIpsum* loremIpsum)
{
	auto textureMngr = LoremIpsum_->getGame()->getTextureMngr();

	Entity* mobile = EM->addEntity(2); 
	Transform* mobTr = mobile->addComponent<Transform>();
	mobile->setUI(true);
	mobTr->setWH(loremIpsum->getGame()->getWindowWidth()/5.0, loremIpsum->getGame()->getWindowHeight()/2.0);
	double offset = mobTr->getW()/16.0;

	mobTr->setPos(loremIpsum->getGame()->getWindowWidth()-mobTr->getW()-60, loremIpsum->getGame()->getWindowHeight());
	Phone* mobileComp = mobile->addComponent<Phone>();
	mobile->addComponent<Sprite>(textureMngr->getTexture(Resources::PhoneOff));
	auto tween = mobile->addComponent<Tween>(mobTr->getPos().getX(), loremIpsum->getGame()->getWindowHeight() - mobTr->getH(), 10, mobTr->getW(), mobTr->getH());
	vector<Transform*> icons;
	for (size_t i = 0; i < StateMachine::APPS::lastApps; i++) {
		Entity* icon = EM->addEntity(3);
		Transform* itr = icon->addComponent<Transform>();
		Texture* iconTexture;
		switch (i)
		{
		case StateMachine::APPS::ChinchetarioApp:
				iconTexture = textureMngr->getTexture(Resources::ChinchetarioAppIcon);
				break;
		case StateMachine::APPS::MapsApp:
			iconTexture = textureMngr->getTexture(Resources::MapAppIcon);
			break;
		case StateMachine::APPS::TunerApp :
			iconTexture = textureMngr->getTexture(Resources::DeathAppIcon);
			break;
		case StateMachine::Die:
			iconTexture = textureMngr->getTexture(Resources::DeathAppIcon);
			break;
		default:
			iconTexture = textureMngr->getTexture(Resources::TextureId::Lock);
			break;
		}
		icon->addComponent<Sprite>(iconTexture);
		auto anim = icon->addComponent<Animator<Transform*>>();

		itr->setWH(mobTr->getW()/4, mobTr->getW() / 4);
		itr->setPos(mobTr->getPos().getX() + offset + (i % 3) * (itr->getW()+ offset), mobTr->getPos().getY()+ offset + (i / 3) * (itr->getH() + offset)+25);
		icon->setUI(true);
		icons.push_back(itr);
		itr->setParent(mobTr);
		icon->addComponent<ButtonOneParametter<LoremIpsum*>>([i, anim](LoremIpsum* game) 
			{ 
				anim->setEnabled(true);
				anim->changeAnim(Resources::AppPressedAnim);
				anim->setFinishFunc([game, i, anim](Transform* t) 
					{
						game->getStateMachine()->PlayApp((StateMachine::APPS)i, game->getStoryManager()); 
						anim->setEnabled(false);
					}, nullptr);
			}, loremIpsum);
		icon->setActive(false);
	}
	mobileComp->initIcons(icons);
	tween->setFunc([icons, mobile, textureMngr, mobileComp](Entity* e)
		{
			for (auto& icon : icons)icon->getEntity()->setActive(true);
			GETCMP2(mobile, Sprite)->setTexture(textureMngr->getTexture((mobileComp->inUse()) ? (Resources::PhoneOff) : (Resources::PhoneOn)));
		}, nullptr);
	return mobile;
}

Entity* StoryManager::createPlayer(EntityManager* EM, Phone* p)
{
	Entity* player = EM->addEntity(2);
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>(SDLK_d,SDLK_a,SDLK_w,SDLK_s, p);
	player->addComponent<PlayerMovement>();
	Animator<Transform*>* anim = player->addComponent<Animator<Transform*>>();
	//player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	player->addComponent<FollowedByCamera>(LoremIpsum_->getStateMachine()->playState_->getCamera(), tp);
	tp->setPos(200, 250);
	tp->setWH(50, 100);
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
		vector<Entity*> vec;
		if (currentScene->ghWorld) {
			vec = currentScene->ghEntities;
		}
		else vec = currentScene->entities;
		setEntitiesActive(vec, false);
	}
	currentScene = scenes_[newScene];
	setBackground();
	vector<Entity*> vec;
	if (currentScene->ghWorld) {
		vec = currentScene->ghEntities;
	}
	else vec = currentScene->entities;
	setEntitiesActive(vec, true);
}
void StoryManager::changeSceneState() {
	if (currentScene != nullptr) {
		bool st = currentScene->ghWorld;
		setEntitiesActive(currentScene->entities, st);
		setEntitiesActive(currentScene->ghEntities, !st);
		currentScene->ghWorld = !st;
		setBackground();
	}
}
void StoryManager::setEntitiesActive(vector<Entity*> vec, bool b) {
	for (Entity* e : vec) {
		e->setActive(b);
		Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
		if (it != nullptr)
			it->setActive(b);
	}
}
void StoryManager::setBackground() {
	Texture* t = nullptr;
	if (!currentScene->ghWorld)
		t = currentScene->background;
	else t = currentScene->ghBackground;
	getBackgroundSprite()->setTexture(t);
}
vector<Entity*> StoryManager::createBars(EntityManager* EM) {
	
	int pxSprite = 56;
	int pxPerY = (LoremIpsum_->getGame()->getWindowHeight() / 5) * 3 / pxSprite;

	int halfW = LoremIpsum_->getGame()->getWindowWidth()/2;
	int y = (LoremIpsum_->getGame()->getWindowHeight() / 5) * 4 - 2 * pxPerY - 1;
	int barwidth = 40;

	vector<BarInfo> barInfo = { {15, 5, 85, 95}, {15, 5, 85, 95}, {15, 5, 85, 95}, 
		/*{30, 5, 85, 95}, {15, 5, 75, 100}*/ };

	for (int i = 0; i < barInfo.size(); i++) {
		Entity* bar = EM->addEntity(3);
		bar->addComponent<Transform>(halfW + (((halfW/2) / (barInfo.size()+1)) * (i+1) - barwidth / 2) - 40, y, barwidth, 0);
		bar->addComponent<Bar>(EM, barInfo[i].upSpeed, barInfo[i].downSpeed, barInfo[i].minWinPer, barInfo[i].maxWinPer);
		bar->addComponent<Rectangle>(SDL_Color{ COLOR(0x00d3ffCC) });
		bars_.push_back(bar);
	}

	return bars_;
}