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
#include "DirReader.h"
#include "FollowedByCamera.h"
#include "Tween.h"
#include "Animator.h"
#include "DialogSelectors.h"
#include "ClueCallbacks.h"

inline void StoryManager::addPlayerClue(Resources::ClueID id) {
	if (clues_[id] != nullptr) {
		//solo a�ade una pista una vez
		int i = 0;
		while (i < playerClues_.size() && playerClues_[i]->id_ != id)
			i++;
		if (i >= playerClues_.size())
		{
			playerClues_.push_back(clues_[id]);
			setInvestigableChanges(true);
		}
	}
	else if (centralClues_[id] != nullptr) {
		//solo a�ade una pista una vez
		int i = 0;
		while (i < playerCentralClues_.size() && playerCentralClues_[i]->id_ != id)
			i++;
		if (i >= playerCentralClues_.size())
		{
			playerCentralClues_.push_back(centralClues_[id]);
			setInvestigableChanges(true);
		}
	}
	if (ClueCallbacks::clueCBs.find(id) != ClueCallbacks::clueCBs.end())
	{
		ClueCallbacks::clueCBs[id]();
	}
}
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

void Actor::addDialog(Dialog*d)
{
	if(entity_==nullptr||!entity_->hasComponent(ecs::DialogComponent))return;
	auto dial = entity_->getComponent<DialogComponent>(ecs::DialogComponent); 
	dial->addDialog(d); 
	if(GETCMP2(entity_, Interactable)->getCallback() == nullptr)
		GETCMP2(entity_, Interactable)->setCallback([dial](Entity* e, Entity* e2) {dial->interact();},entity_);
}

Dialog* Actor::getDialog(int id)
{
	 return entity_->getComponent<DialogComponent>(ecs::DialogComponent)->getDialog(id);
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
}

Investigable::Investigable(StoryManager* sm, Resources::InvestigableInfo info) {
	currentScene_ = sm->getScene(info.startScene_);
	sprite_ = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);

	entity_ = sm->addEntity(1);
	Transform* tr = entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>();
	in->setIcon(Resources::TextureID::ClueInteraction);
	sm->interactables_.push_back(in);
	entity_->setActive(false);
	in->setEnabled(false);

	Resources::InvestigableInfo i = info;
	in->setCallback([sm, i](Entity* player, Entity* other) { sm->addPlayerClue(i.unlockable_); sm->thinkOutLoud(i.thought_); });

	if (info.sprite_ == Resources::Blank)entity_->addComponent<Rectangle>(SDL_Color{ COLOR(0x55ff75ff) });
	else
	{
		Texture* t = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);
		entity_->addComponent<Sprite>(t);
		tr->setWH((double)t->getWidth() * 8.0, (double)t->getHeight() * 8.0);		
	}
}

void StoryManager::init()
{
	PLAYABLEHIGHT = LoremIpsum_->getGame()->getWindowHeight();

	backgroundViewer_ = addEntity(0);
	backgroundViewer_->addComponent<Transform>(0, 0, 1280, 720);
	bgSprite_ = backgroundViewer_->addComponent<Sprite>(nullptr);
	backgroundViewer_->addComponent<Animator<int>>()->setEnabled(false);
	backgroundViewer_->setActive(true);

	phone_ = createPhone(entityManager_, LoremIpsum_);
	player_ = createPlayer(entityManager_, GETCMP2(phone_, Phone));

	Vector2D p2 = { 0.0, LoremIpsum_->getGame()->getWindowHeight() - 150.0 };
	
	dialogBox_ = addEntity(2);
	dialogBox_->setActive(true);
	int h = LoremIpsum_->getGame()->getWindowHeight() / 5;
	int wh = LoremIpsum_->getGame()->getWindowHeight();
	dialogBox_->addComponent<Transform>(0, wh, LoremIpsum_->getGame()->getWindowWidth(), h);
	//dialogBox_->addComponent<Rectangle>(SDL_Color{ COLOR(0xcc8866cc) });
	dialogBox_->addComponent<Sprite>(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::DialogBox));
	dialogBoxText_ = dialogBox_->addComponent<Text>("", p2 + Vector2D(15.0 + 5.0 + 128.0, 35.0), LoremIpsum_->getGame()->getWindowWidth() - (15.0 + 5.0 + 128.0 + p2.getX()), Resources::RobotoTest24, 100);
	dialogBoxText_->addSoundFX(Resources::Bip);
	dialogBoxText_->addSoundFX(Resources::Paddle_Hit);
	dialogBoxActorName_ = dialogBox_->addComponent<Text>("", p2 + Vector2D(128.0 + 5.0 + 8.0, 12.0), GETCMP2(dialogBox_, Transform)->getW(), Resources::RobotoTest24, 0);
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
	dialogPortrait->setActive(true);
	dialogPortrait->addComponent<DialogComponent>(player_, nullptr, this);


	for (int i  = 0; i<Resources::SceneID::lastSceneID;i++)
	{
		scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].backgroundId_), static_cast<Resources::SceneID>(i), LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].ghBackgroundId_), Resources::scenes_[i].moveLine_);
		//scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].backgroundId_), (Resources::SceneID)(i), Resources::scenes_[i].moveLine_);
		scenes_[i]->mapPos = Resources::scenes_[i].mapPos_;
	}
	for (auto& a : Resources::actors_)
	{
		Actor* e = new Actor(this, a);
		if(a.ghWorld_)
			scenes_[a.startScene_]->ghEntities.push_back(e->getEntity());
		else scenes_[a.startScene_]->entities.push_back(e->getEntity());
		//GETCMP2(e->getEntity(), Transform)->setPosY(PLAYABLEHIGHT - GETCMP2(e->getEntity(), Transform)->getPos().getY());
		actors_[a.id_] = e;
	}
	for (auto& ds : Resources::doors_) {
		Door* d = new Door(this, ds);
		//GETCMP2(d->getEntity(), Transform)->setPosY(PLAYABLEHIGHT - GETCMP2(d->getEntity(), Transform)->getPos().getY());
		scenes_[ds.startScene_]->entities.push_back(d->getEntity());
		doors_.push_back(d);

		//le metemos el callback a cada puerta
		if (DoorSelectors::functions_.find(d->getId()) != DoorSelectors::functions_.end())
			d->setFunc(DoorSelectors::functions_[d->getId()]);

		std::function<bool(Door*)> doorCallback = d->getFunc();

		Interactable* in = d->getEntity()->getComponent<Interactable>(ecs::Interactable);
		in->setCallback([doorCallback, d](Entity* player, Entity* other)
			{
				bool change = false;
				if (doorCallback != nullptr)
					change = doorCallback(d);
				if (!change)
				{
					StoryManager::instance()->changeScene(Resources::doors_[d->getId()].goTo_);
					player->getComponent<Transform>(ecs::Transform)->setPos(Resources::doors_[d->getId()].spawnPoint_.getX(),
						Resources::doors_[d->getId()].spawnPoint_.getY());
				}
			}
		);
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
	for (int i = 0; i < Resources::timelineSolutions_.size(); i++)
	{
		timelineSolutions_.push_back(Resources::timelineSolutions_[i].order_);
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
		actors_[dialog->actorID_]->addDialog(dialog);
	}


	Entity* e = addEntity(1);
	Transform* eTr = e->addComponent<Transform>(0,0,30,30);
	Sprite* eSprite = e->addComponent<Sprite>(nullptr);
	ButtonOneParametter<Interactable*>* eBut = e->addComponent<ButtonOneParametter<Interactable*>>(std::function<void(Interactable*)>([](Interactable* i) {}), nullptr);
	e->addComponent<InteractableLogic>(interactables_, GETCMP2(player_, Transform), eTr, eSprite, eBut);
	e->setActive(true);

	addPlayerClue(Resources::Tut_Cent_DesordenHabitacion);
	//playerCentralClues_.push_back(centralClues_[]); //ESTO NO IR� AQU�. DESBLOQUEARLO CUANDO TOQUE
	//playerCentralClues_.push_back(centralClues_[Resources::Tut_Cent_MotivoEntrada]);

	StoryManager* sm = this;
	//actors_[Resources::ActorID::MacarenaMartinez]->setDialogActive(0, false);
	for (auto pair : DialogSelectors::functions)
	{
		actors_[pair.first]->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->setFunc(pair.second);
	}
}

Entity* StoryManager::createPhone(EntityManager* EM, LoremIpsum* loremIpsum)
{
	auto textureMngr = LoremIpsum_->getGame()->getTextureMngr();

	Entity* mobile = EM->addEntity(2);
	Transform* mobTr = mobile->addComponent<Transform>();
	mobile->setUI(true);
	mobTr->setWH(1080 / 5.0, 720 / 2.0);
	double offset = mobTr->getW() / 16.0;
	mobTr->setPos(loremIpsum->getGame()->getWindowWidth() - mobTr->getW() - 60, loremIpsum->getGame()->getWindowHeight() - 25.0);
	Phone* mobileComp = mobile->addComponent<Phone>(this);
	auto but = mobile->addComponent<ButtonOneParametter<int>>([](int) {}, 0);
	but->setOffsets(0, 0, 0, 330);
	but->setMouseOverCallback([mobTr]() {mobTr->setPosY(mobTr->getPos().getY() - 5); });
	but->setMouseOutCallback([mobTr]() {mobTr->setPosY(mobTr->getPos().getY() + 5); });
	int initialY = loremIpsum->getGame()->getWindowHeight() - 30;
	but->setCallback([mobileComp, but, mobTr, initialY](int) {
		if (mobTr->getPos().getY() >= initialY)
			mobileComp->show();
		else
			mobileComp->hide();
	}, 0);
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
		case StateMachine::APPS::TunerApp:
			iconTexture = textureMngr->getTexture(Resources::DeathAppIcon); //esto no va a ser una app, por eso tiene el icono este 
			break;
		case StateMachine::APPS::OptionsApp:
			iconTexture = textureMngr->getTexture(Resources::OptionsAppIcon);
			break;
		case StateMachine::APPS::ContactsApp:
			iconTexture = textureMngr->getTexture(Resources::PhoneAppIcon);
			break;
		case StateMachine::APPS::NotesApp:
			iconTexture = textureMngr->getTexture(Resources::NotesAppIcon);
			break;
		case StateMachine::APPS::Die:
			iconTexture = textureMngr->getTexture(Resources::DeathAppIcon);
			break;
		default:
			iconTexture = textureMngr->getTexture(Resources::TextureID::Lock);
			break;
		}
		icon->addComponent<Sprite>(iconTexture);

		itr->setWH(mobTr->getW() / 4, mobTr->getW() / 4);
		itr->setPos(mobTr->getPos().getX() + offset + (i % 3) * (itr->getW() + offset), mobTr->getPos().getY() + offset + (i / 3) * (itr->getH() + offset) + 25);
		icon->setUI(true);
		icons.push_back(itr);
		itr->setParent(mobTr);
		if (i != StateMachine::APPS::ContactsApp) {
			auto anim = icon->addComponent<Animator<Transform*>>();
			icon->addComponent<ButtonOneParametter<LoremIpsum*>>([i, anim](LoremIpsum* game)
				{
					game->getStoryManager()->getPlayer()->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->resetTarget();
					anim->setEnabled(true);
					if (anim->getAnim() == Resources::LastAnimID)
					{
						anim->changeAnim(Resources::AppPressedAnim);
						anim->setFinishFunc([game, i, anim](Transform* t)
							{
								game->getStateMachine()->PlayApp((StateMachine::APPS)i, game->getStoryManager());
								anim->setEnabled(false);
							}, nullptr);
					}
					else anim->restartAnim();

				}, loremIpsum);
		}
		// los contactos son un caso aparte porque no llevan a otro estado
		else {
			auto anim = icon->addComponent<Animator<Phone*>>();
			icon->addComponent<ButtonOneParametter<LoremIpsum*>>(std::function<void(LoremIpsum*)>([anim, mobileComp](LoremIpsum* game)
				{
					game->getStoryManager()->getPlayer()->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->resetTarget();
					anim->setEnabled(true);
					if (anim->getAnim() == Resources::LastAnimID)
					{
						anim->changeAnim(Resources::AppPressedAnim);
						anim->setFinishFunc([anim](Phone* p)
							{
								//ATENCION
								//no funciona esta Lambda
								p->showContacts();
								anim->setEnabled(false);
							}, mobileComp);
					}
					else anim->restartAnim();
					//mobileComp->showContacts();

				}), loremIpsum);
		}
	icon->setActive(false);
	}
	mobileComp->initIcons(icons);
	//mobileComp->initIcons(icons);
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
	player->addComponent<PlayerKBCtrl>(SDLK_d, SDLK_a, SDLK_w, SDLK_s, p);
	player->addComponent<PlayerMovement>(this);
	Animator<Transform*>* anim = player->addComponent<Animator<Transform*>>();
	//player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	player->addComponent<FollowedByCamera>(LoremIpsum_->getStateMachine()->playState_->getCamera(), tp);
	tp->setPos(200, PLAYABLEHIGHT-2*LAZAROHEIGHT);
	tp->setWH(160, 2*LAZAROHEIGHT);
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
	//for (auto dialog : dialogs_)
	//	delete dialog.second; //ahora los componentes los borran, seamos perdonados hermanos
	for (auto& c : Resources::centralClues_)
	{
		delete centralClues_[c.id_];
	}
}
void StoryManager::changeScene(Resources::SceneID newScene)
{
	PlayerKBCtrl* kbCtrl = player_->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl);
	kbCtrl->resetTarget();
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
		prevScene = currentScene;
		vector<Entity*> vec;
		if (prevScene->ghWorld) {
			vec = currentScene->ghEntities;
			currentScene->ghWorld = false;
		}
		else vec = currentScene->entities;
		setEntitiesActive(vec, false);
	}
	currentScene = scenes_[newScene];
	setBackground();
	if(prevScene == nullptr)		//Si vamos a hacer cambios a escenas con músicas diferentes hay que revisitar esto
		setMusic();
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
		setMusic();
	}
}
void StoryManager::setEntitiesActive(vector<Entity*> vec, bool b) {
	for (Entity* e : vec) {
		e->setActive(b);
		Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
		if (it != nullptr)
			it->setEnabled(b);
	}
}
/*


 -> -> ->  [] -> -> -> { ->|  |<- }


*/
void StoryManager::setBackground() {
	Texture* t = nullptr;
	if (!currentScene->ghWorld)
		t = currentScene->background;
	else t = currentScene->ghBackground;
	getBackgroundSprite()->setTexture(t);
}
void StoryManager::setMusic() {
	auto am = LoremIpsum_->getGame()->getAudioMngr();
	am->haltMusic();
	if (currentScene->ghWorld) {
		am->playMusic(Resources::GhostDraft);
	}
	else am->playMusic(Resources::MTloo);
}
vector<Entity*> StoryManager::createBars(EntityManager* EM) {
	vector<Entity*> bars;

	int pxSprite = 56;
	int pxPerY = (LoremIpsum_->getGame()->getWindowHeight() / 5) * 3 / pxSprite;

	int halfW = LoremIpsum_->getGame()->getWindowWidth()/2;
	int y = (LoremIpsum_->getGame()->getWindowHeight() / 5) * 4 - 2 * pxPerY - 1;
	int barwidth = 40;

	vector<BarInfo> barInfo = { {15, 5, 85, 95}, {15, 5, 85, 95}, {15, 5, 85, 95}, 
		/*{30, 5, 85, 95}, {15, 5, 75, 100}*/ };

	for (int i = 0; i < barInfo.size(); i++) {
		Entity* bar = EM->addEntity(3);
		bar->addComponent<Transform>(halfW + (((halfW / 2.0) / (barInfo.size() + 1.0)) * (i + 1.0) - barwidth / 2.0) - 40.0, (double)y, (double)barwidth, 0.0);
		bar->addComponent<Bar>(EM, barInfo[i].upSpeed, barInfo[i].downSpeed, barInfo[i].minWinPer, barInfo[i].maxWinPer);
		bar->addComponent<Rectangle>(SDL_Color{ COLOR(0x00d3ffCC) });
		bars.push_back(bar);
	}

	return bars;
}