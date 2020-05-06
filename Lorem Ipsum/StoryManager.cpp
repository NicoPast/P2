#include "StoryManager.h"
#include "DialogComponent.h"
#include "LoremIpsum.h"
#include "SDLGame.h"
#include "DragDrop.h"
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
	spriteId_ = info.image_;
	placed_ = false;
	entity_ = nullptr;
}
void Actor::addDialog(Dialog*d, bool active)
{
	if(entity_==nullptr||!entity_->hasComponent(ecs::DialogComponent))return;
	auto dial = entity_->getComponent<DialogComponent>(ecs::DialogComponent); 
	dial->addDialog(d, active); 
	GETCMP2(entity_, Interactable)->setCallback([](Entity* e, Entity* e2) {GETCMP2(e2, DialogComponent)->interact();},entity_);
}


Actor::Actor(StoryManager* sm, Resources::ActorInfo info, Vector2D pos, int w, int h)
{
	name_ = info.name_;
	currentScene_ = sm->getScene(info.startScene_);
	sprite_ = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);
	portrait_ = info.sprite_;
	id_ = info.id_;
	entity_ = sm->addEntity(1);
	//por ahora le meto un rect porque no tiene sprite component
	entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>();
	in->setIcon(Resources::ChatInteraction);
	sm->interactables_.push_back(in);
	entity_->setActive(false);
	in->setEnabled(false);

	entity_->addComponent<DialogComponent>(sm->getPlayer(), this, sm);
	if (info.anim_ != Resources::noAnim)
	{
		entity_->addComponent<Animator<int*>>()->changeAnim(info.anim_);
	}
	else
		entity_->addComponent<Rectangle>(SDL_Color{ COLOR(0x55ff75ff) });
};

Door::Door(StoryManager* sm, Resources::DoorInfo info) {
	currentScene_ = sm->getScene(info.startScene_);
	sprite_ = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);
	id_ = info.id_;

	entity_ = sm->addEntity(1);
	entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>();
	in->setIcon(Resources::DoorInteraction);
	sm->interactables_.push_back(in);
	entity_->setActive(false);
	in->setEnabled(false);
	
	Resources::DoorInfo i = info;
	in->setCallback([sm, i](Entity* player, Entity* other) { sm->changeScene(i.goTo_);  player->getComponent<Transform>(ecs::Transform)->setPosX(i.spawnPoint_.getX()); });

	entity_->addComponent<Rectangle>(SDL_Color{ COLOR(0x55ff75ff) });
}

Investigable::Investigable(StoryManager* sm, Resources::InvestigableInfo info) {
	currentScene_ = sm->getScene(info.startScene_);
	sprite_ = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);

	entity_ = sm->addEntity(1);
	entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>();
	in->setIcon(Resources::TextureID::ClueInteraction);
	sm->interactables_.push_back(in);
	entity_->setActive(false);
	in->setEnabled(false);

	Resources::InvestigableInfo i = info;
	in->setCallback([sm, i](Entity* player, Entity* other) { sm->addPlayerClue(i.unlockable_); sm->thinkOutLoud(i.thought_); });

	entity_->addComponent<Rectangle>(SDL_Color{ COLOR(0x55ff75ff) });
}

void StoryManager::init()
{
	PLAYABLEHIGHT = LoremIpsum_->getGame()->getWindowHeight();

	backgroundViewer_ = addEntity(0);
	backgroundViewer_->addComponent<Transform>(0, 0, 1280, 720);
	bgSprite_ = backgroundViewer_->addComponent<Sprite>(nullptr);
	backgroundViewer_->addComponent<Animator<int>>()->setEnabled(false);
	backgroundViewer_->setActive(true);




	Vector2D p2 = { 0.0, LoremIpsum_->getGame()->getWindowHeight() - 150.0 };
	
	dialogBox_ = addEntity(2);
	dialogBox_->setActive(true);
	int h = LoremIpsum_->getGame()->getWindowHeight() / 5;
	int wh = LoremIpsum_->getGame()->getWindowHeight();
	dialogBox_->addComponent<Transform>(0, wh, LoremIpsum_->getGame()->getWindowWidth(), h);
	//dialogBox_->addComponent<Rectangle>(SDL_Color{ COLOR(0xcc8866cc) });
	dialogBox_->addComponent<Sprite>(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::DialogBox));
	dialogBoxText_ = dialogBox_->addComponent<Text>("", p2 + Vector2D(15+5+128, 35), LoremIpsum_->getGame()->getWindowWidth()-(15 + 5 + 128 +p2.getX()), Resources::RobotoTest24, 100);
	dialogBoxText_->addSoundFX(Resources::Bip);
	dialogBoxText_->addSoundFX(Resources::Paddle_Hit);
	dialogBoxActorName_ = dialogBox_->addComponent<Text>("", p2 + Vector2D(128+5+8, 12), GETCMP2(dialogBox_, Transform)->getW(), Resources::RobotoTest24, 0);
	Text* dText = dialogBoxText_;
	Text* dName = dialogBoxActorName_;
	auto tween = dialogBox_->addComponent<Tween>(0, wh - h, 5);
	tween->setFunc([dText, dName](Entity* e)
		{
			dText->setEnabled(true);
			dName->setEnabled(true);
		}, player_);
	dialogPortrait = addEntity(2);
	dialogPortrait->addComponent<Transform>(5 + 5, wh + 8, 128,128)->setParent(GETCMP2(dialogBox_, Transform));
	dialogPortrait->addComponent<Sprite>(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::LazaroPortrait));
	dialogPortrait->addComponent<DialogComponent>(player_, nullptr, this);
	dialogPortrait->setActive(true);


	phone_ = createPhone(entityManager_, LoremIpsum_);
	player_ = createPlayer(entityManager_, GETCMP2(phone_, Phone));


	for (int i  = 0; i<Resources::SceneID::lastSceneID;i++)
	{
		scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].backgroundId_), (Resources::SceneID)(i), Resources::scenes_[i].moveLine_);
		scenes_[i]->mapPos = Resources::scenes_[i].mapPos_;
	}
	for (auto& a : Resources::actors_)
	{
		Actor* e = new Actor(this, a);
		//GETCMP2(e->getEntity(), Transform)->setPosY(PLAYABLEHIGHT - GETCMP2(e->getEntity(), Transform)->getPos().getY());
		scenes_[a.startScene_]->entities.push_back(e->getEntity());
		actors_[a.id_] = e;
	}
	for (auto& ds : Resources::doors_) {
		Door* d = new Door(this, ds);
		//GETCMP2(d->getEntity(), Transform)->setPosY(PLAYABLEHIGHT - GETCMP2(d->getEntity(), Transform)->getPos().getY());
		scenes_[ds.startScene_]->entities.push_back(d->getEntity());
		doors_.push_back(d);
	}
	for (auto& i : Resources::investigables_) {
		Investigable* inv = new Investigable(this, i);
		//GETCMP2(inv->getEntity(), Transform)->setPosY(PLAYABLEHIGHT - GETCMP2(inv->getEntity(), Transform)->getPos().getY());
		scenes_[i.startScene_]->entities.push_back(inv->getEntity());
		investigables_.push_back(inv);
	}
	for (auto& c : Resources::clues_)
	{
		clues_[c.id_] = new Clue(c);
	}
	for (auto& c : Resources::centralClues_)
	{
		centralClues_[c.id_] = new CentralClue(c);
	}
	std::fstream dialogListFile;
	dialogListFile.open("../assets/dialogs/dialogList.conf");
	int size = -1;
	assert(dialogListFile.is_open());
	dialogListFile >> size;

	for (int i = 0; i < size; i++)
	{
		string nameOfDialog;
		dialogListFile >> nameOfDialog;
		int index;
		dialogListFile >> index;
		Dialog* dialog = new Dialog("../assets/dialogs/" + nameOfDialog + ".dialog", index);
		dialogs_[index] = dialog;
		dialog->dialogName_ = nameOfDialog;
		actors_[dialog->actorID_]->addDialog(dialog, dialog->active_);
	}


	Entity* e = addEntity(1);
	Transform* eTr = e->addComponent<Transform>(0,0,30,30);
	Sprite* eSprite = e->addComponent<Sprite>(nullptr);
	ButtonOneParametter<Interactable*>* eBut = e->addComponent<ButtonOneParametter<Interactable*>>(std::function<void(Interactable*)>([](Interactable* i) {}), nullptr);
	e->addComponent<InteractableLogic>(interactables_, GETCMP2(player_, Transform), eTr, eSprite, eBut);
	e->setActive(true);

	playerCentralClues_.push_back(centralClues_[Resources::Tut_Cent_DesordenHabitacion]);
	playerCentralClues_.push_back(centralClues_[Resources::Tut_Cent_MotivoEntrada]);

	availableScenes_.push_back(scenes_[Resources::EntradaDespacho]);
}

Entity* StoryManager::createPhone(EntityManager* EM, LoremIpsum* loremIpsum)
{
	auto textureMngr = LoremIpsum_->getGame()->getTextureMngr();

	Entity* mobile = EM->addEntity(2); 
	Transform* mobTr = mobile->addComponent<Transform>();
	mobile->setUI(true);
	mobTr->setWH(1080/5.0, 720/2.0);
	double offset = mobTr->getW()/16.0;

	mobTr->setPos(loremIpsum->getGame()->getWindowWidth()-mobTr->getW()-60, loremIpsum->getGame()->getWindowHeight());
	Phone* mobileComp = mobile->addComponent<Phone>(this);
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
			iconTexture = textureMngr->getTexture(Resources::DeathAppIcon); //esto no va a ser una app, por eso tiene el icono este 
			break;
		case StateMachine::APPS::OptionsApp:
			iconTexture = textureMngr->getTexture(Resources::OptionsAppIcon);
			break;
		default:
			iconTexture = textureMngr->getTexture(Resources::TextureID::Lock);
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
				game->getStoryManager()->getPlayer()->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->resetTarget();
				if (anim->getAnim() == Resources::LastAnimID)
				{
					anim->changeAnim(Resources::AppPressedAnim);
					anim->setFinishFunc([game, i, anim](Transform* t)
						{
							game->getStateMachine()->PlayApp((StateMachine::APPS)i, game->getStoryManager());
						}, nullptr);
				}
				else anim->restartAnim();

			}, loremIpsum);
		icon->setActive(false);
	}

	//añadimos el icono para la agenda, que no lleva a otro estado diferente
	/*Entity* messagesApp = entityManager_->addEntity(3);
	Transform* messTr = messagesApp->addComponent<Transform>();
	messTr->setWH(mobTr->getW() / 4, mobTr->getW() / 4);
	messTr->setPos(mobTr->getPos().getX() + offset + (StateMachine::APPS::lastApps % 3) * (messTr->getW() + offset), mobTr->getPos().getY() + offset + (StateMachine::APPS::lastApps / 3) * (messTr->getH() + offset) + 25);
	messagesApp->setUI(true);
	icons.push_back(messTr);
	messTr->setParent(mobTr);
	messagesApp->addComponent<Sprite>(textureMngr->getTexture(Resources::PhoneAppIcon));
	messagesApp->addComponent<ButtonOneParametter<Phone*>>(std::function<void(Phone*)>([](Phone* phone) {phone->showContacts(); }), mobileComp);
	messagesApp->setActive(false);
	/**/
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
	Entity* player = EM->addEntity(1);
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>(SDLK_d,SDLK_a,SDLK_w,SDLK_s, p);
	player->addComponent<PlayerMovement>(this);
	Animator<Transform*>* anim = player->addComponent<Animator<Transform*>>();
	//player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	player->addComponent<FollowedByCamera>(LoremIpsum_->getStateMachine()->playState_->getCamera(), tp);
	tp->setPos(200, PLAYABLEHIGHT-LAZAROHEIGHT);
	tp->setWH(80, LAZAROHEIGHT);
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
	for (auto actor : actors_)
	{
		delete actor.second;
	};
	for (size_t i = 0; i < doors_.size(); i++) {
		delete doors_[i];
	};
	for (size_t i = 0; i < investigables_.size(); i++) {
		delete investigables_[i];
	};
	for (auto dialog : dialogs_)
		delete dialog.second;
	for (auto& c : Resources::centralClues_)
	{
		delete centralClues_[c.id_];
	}
}
void StoryManager::changeScene(Resources::SceneID newScene)
{
	PlayerKBCtrl* kbCtrl = player_->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl);
	kbCtrl->setEnabled(false);
	PlayerMovement* playerMove = player_->getComponent<PlayerMovement>(ecs::PlayerMovement);
	playerMove->setEnabled(false);
	Animator<int>* anim = backgroundViewer_->getComponent<Animator<int>>(ecs::Animator);
	anim->setEnabled(true);
	anim->changeAnim(Resources::FadeInAnim);
	anim->setFinishFunc([anim, playerMove, kbCtrl](int a) 
	{
		playerMove->setEnabled(true);
		kbCtrl->setEnabled(true);
		anim->setEnabled(false);
	}, 0);

	if (currentScene!=nullptr)
	{
		for (Entity* e : currentScene->entities)
		{
			e->setActive(false);
			Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
			if (it != nullptr)
				it->setEnabled(false);
		}
	}
	currentScene = scenes_[newScene];
	getBackgroundSprite()->setTexture(currentScene->background);
	for (Entity* e : currentScene->entities)
	{
		e->setActive(true);
		Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
		if ( it!= nullptr)
			it->setEnabled(true);
	}
}
/*


 -> -> ->  [] -> -> -> { ->|  |<- }


*/
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