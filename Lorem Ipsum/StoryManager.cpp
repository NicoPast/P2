
#include "StoryManager.h"
#include "DialogComponent.h"
#include "LoremIpsum.h"
#include "SDLGame.h"
#include "DragDrop.h"
#include "Rectangle.h"
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
#include "Phone.h"
#include "DialogSelectors.h"
#include "ClueCallbacks.h"
#include "Tuner.h"
#include "Parallax.h"
#include "AnimationSelector.h"


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

			if (ClueCallbacks::clueCBs.find(id) != ClueCallbacks::clueCBs.end())
			{
				ClueCallbacks::clueCBs[id]();
			}
			phone_->getComponent<Phone>(ecs::Phone)->notification(StateMachine::APPS::ChinchetarioApp);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::CameraClick, 0, 1);
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

			if (ClueCallbacks::clueCBs.find(id) != ClueCallbacks::clueCBs.end())
			{
				ClueCallbacks::clueCBs[id]();
			}
			phone_->getComponent<Phone>(ecs::Phone)->notification(StateMachine::APPS::ChinchetarioApp);
		}
	}
}

void StoryManager::removeTutorialClues() {
	removeClue(Resources::ClueID::Tut_Cent_DesordenHabitacion);
	removeClue(Resources::ClueID::Tut_Cent_MotivoEntrada);
	removeClue(Resources::ClueID::Tut_MigajasComida);
	removeClue(Resources::ClueID::Tut_PapelesDesordenados);
	removeClue(Resources::ClueID::Tut_SillaRota);
	setInvestigableActive(Resources::Tut_MigajasComida, false);
	setInvestigableActive(Resources::Tut_PapelesDesordenados, false);
	setInvestigableActive(Resources::Tut_SillaRota, false);
}

void StoryManager::removeClue(Resources::ClueID id) {
	Chinchetario* ch = LoremIpsum_->getStateMachine()->ch_;
	if (id < Resources::lastClueID) {
		auto it = playerClues_.begin();
		while (it != playerClues_.end()) {
			if ((*it)->id_ == id) {
				ch->removeClue(id);
				playerClues_.erase(it);
				return;
			}
			else it++;
		}
	}
	else {
		auto it = playerCentralClues_.begin();
		while (it != playerCentralClues_.end()) {
			if ((*it)->id_ == id) {
				ch->removeClue(id);
				playerCentralClues_.erase(it);
				return;
			}
			else it++;
		}
	}
	
}
Entity*  StoryManager::addEntity(int layer)
{
	Entity* e = entityManager_->addEntity(layer);
	e->setActive(false);
	return e;
}

void StoryManager::removeLayer(Vector2D pos, Resources::SceneID id)
	{
	if (!layerRemover)
	{
		layerRemover = addEntity();
		layerRemover->addComponent<Transform>(pos.getX(), pos.getY(), 45.0, 45.0);
		Interactable* in = layerRemover->addComponent<Interactable>();
		in->setIcon(Resources::ClueInteraction);
		interactables_.push_back(in);
		layerRemoverScene = Resources::Pasillo;
		scenes_[Resources::Pasillo]->entities.push_back(layerRemover);
		GETCMP2(layerRemover, Transform)->setPos(pos);
		in->setCallback([in](Entity* e, Entity* e2)
			{
				StoryManager::instance()->getBackgroundSprite()->showSubtexture(false);
				in->getEntity()->setActive(false);
			});
	}
	else if (id != layerRemoverScene)
	{
		Scene* sc = scenes_[layerRemoverScene];
		int i = 0;
		for (Entity* e : sc->entities)
		{
			if (e == layerRemover)
			{
				sc->entities.erase(sc->entities.begin() + i);
			}
			else i++;
		}
		layerRemoverScene = id;
		scenes_[id]->entities.push_back(layerRemover);
	}

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
	if(GETCMP2(entity_, Interactable)->getCallback() == nullptr && !dead)
		GETCMP2(entity_, Interactable)->setCallback([dial](Entity* e, Entity* e2) {dial->interact();},entity_);
	if (GETCMP2(entity_, Interactable)->getCallback() == nullptr && dead)
	{
		Resources::ActorID id = id_;
		GETCMP2(entity_, Interactable)->setCallback([id, dial](Entity* e, Entity* e2) {
				if (StoryManager::instance()->getActor(id)->isTuned())
				{
					Entity* e = StoryManager::instance()->getActor(id)->getEntity();
					GETCMP2(e, Interactable)->setCallback([dial](Entity* e, Entity* e2) {dial->interact(); }, e);
				}
				else
				{
					LoremIpsum::instance()->getStateMachine()->PlayApp(StateMachine::APPS::TunerApp);
					static_cast<Tuner*>(LoremIpsum::instance()->getStateMachine()->actualState())->setGhost(id);
				}
			}, entity_);
	}

}

void Actor::Move(Resources::SceneID newScene)
{
 	currentScene_ = StoryManager::instance()->moveActorTo(id_, newScene);
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
	entity_ = sm->addEntity(0);
	//por ahora le meto un rect porque no tiene sprite component
	entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>();
	in->setIcon(Resources::ChatInteraction);
	sm->interactables_.push_back(in);
	entity_->setActive(false);
	dead = info.ghWorld_;
	inPhone_ = info.inPhone_;
	contactsName_ = info.contactsName_;

	entity_->addComponent<DialogComponent>(sm->getPlayer(), this, sm);
	if (info.anim_ != Resources::noAnim)
	{
		Animator<int*>* animatorComp = entity_->addComponent<Animator<int*>>();
		animatorComp->changeAnim(info.anim_);
		if (AnimationSelector::functions.find(info.id_) != AnimationSelector::functions.end())
			animatorComp->setSelectorFunction(AnimationSelector::functions[info.id_]);
	}
	else
		entity_->addComponent<Rectangle>(SDL_Color{ COLOR(0x55ff75ff) });
	if (info.portraitAnim_ != Resources::noAnim)
		this->portraitAnim_ = info.portraitAnim_;
	else if (info.sprite_ != Resources::Blank)
		this->portrait_ = info.sprite_;
	if (dead)
		tuned = false;
	
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
}

Investigable::Investigable(StoryManager* sm, Resources::InvestigableInfo info) {
	currentScene_ = sm->getScene(info.startScene_);
	sprite_ = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);

	entity_ = sm->addEntity(0);
	Transform* tr = entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>();
	in->setIcon(Resources::TextureID::ClueInteraction);
	sm->interactables_.push_back(in);
	entity_->setActive(false);
	id_ = info.unlockable_;
	Resources::InvestigableInfo i = info;
	in->setCallback([sm, i](Entity* player, Entity* other) { sm->thinkOutLoud({ i.thought_ }); sm->addPlayerClue(i.unlockable_);  });

	if (info.sprite_ != Resources::Blank)
	{
		Texture* t = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);
		entity_->addComponent<Sprite>(t);
		tr->setWH((double)t->getWidth() * 8.0, (double)t->getHeight() * 8.0);		
	}
}


/*

Este es el metodo que buscas xD

*/
void StoryManager::init()
{
	PLAYABLEHIGHT = LoremIpsum_->getGame()->getWindowHeight();
	/* Lo hago aquí por testear*/
	SDLGame::instance()->getTextureMngr()->getTexture(Resources::BackgroundDeathWorld)->setBlendingMode(SDL_BLENDMODE_MOD);
	/////////////////////////////

	tunerDificultyLevels =
	{
		{ {15, 5, 75, 85},   {15, 5, 85, 95} },
		{ {15, 5, 85, 95},   {25, 10, 65, 85},  {15, 10, 85, 95} },
		{ {25, 15, 85, 95},  {35, 30, 65, 75},  {15, 5, 85, 95} },
		{ {35, 15, 75, 85},  {5, 10, 65, 75},   {15, 5, 85, 95} },
		//{ {15, 5, 75, 85},   {15, 5, 85, 95},  {15, 5, 85, 95} ,  {15, 5, 85, 95} },
		{ {25, 15,  85, 95},  {15, 5, 65, 75},   {10, 5, 65, 55}, {10, 5, 35, 45}  }
	};



	backgroundViewer_ = addEntity(0);
	backgroundViewer_->addComponent<Transform>(0, 0, 1280, 720);
	bgSprite_ = backgroundViewer_->addComponent<Sprite>(nullptr);
	backgroundViewer_->addComponent<Sprite>(nullptr); // mask
	backgroundViewer_->addComponent<Animator<int>>()->setEnabled(false);
	backgroundViewer_->setActive(true);

	
	UiDisplay = addEntity(3);
	UiDisplay->setActive(true);
	UiDisplay->addComponent<Transform>(0,0,2400,720);
	UiDisplay->addComponent<Sprite>();

	phone_ = createPhone(entityManager_, LoremIpsum_);
	player_ = createPlayer(entityManager_, GETCMP2(phone_, Phone));

	//Prometo parametrizar esto en un futuro
	notes_ = new Notes(this, 1080 / 5 - 30, 720 / 2 - 30,  LoremIpsum_->getGame()->getWindowWidth() - 1080 / 5 - 50, LoremIpsum_->getGame()->getWindowHeight() - 720 / 2 + 40);

	Vector2D p2 = { 0.0, LoremIpsum_->getGame()->getWindowHeight() - 150.0 };
	
	dialogBox_ = addEntity(2);
	dialogBox_->setActive(true);
	dialogBox_->setUI(true);
	int h = LoremIpsum_->getGame()->getWindowHeight() / 5;
	int wh = LoremIpsum_->getGame()->getWindowHeight();
	dialogBox_->addComponent<Transform>(0, wh, LoremIpsum_->getGame()->getWindowWidth(), h);
	//dialogBox_->addComponent<Rectangle>(SDL_Color{ COLOR(0xcc8866cc) });
	dialogBox_->addComponent<Sprite>(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::DialogBox));
	dialogBoxText_ = dialogBox_->addComponent<Text>("", p2 + Vector2D(15.0 + 5.0 + 128.0, 35.0), GETCMP2(dialogBox_, Transform)->getW() - 2 * (15.0 + 5.0 + 128.0), Resources::RobotoTest24, 100);
	dialogBoxText_->addSoundFX(Resources::Bip);
	dialogBoxText_->addSoundFX(Resources::Paddle_Hit);
	dialogBoxText_->setScroll(p2.getX()+ (15.0 + 5.0 + 128.0),p2.getY()+35, GETCMP2(dialogBox_, Transform)->getW()-2*(15.0 + 5.0 + 128.0),h-45);
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
	dialogPortrait->setUI(true);
	dialogPortrait->addComponent<Transform>(5 + 5, wh + 8, 128,128)->setParent(GETCMP2(dialogBox_, Transform));
	dialogPortrait->addComponent<Sprite>(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::LazaroPortrait));
	dialogPortrait->addComponent<Animator<int>>();
	dialogPortrait->setActive(true);
	dialogPortrait->addComponent<DialogComponent>(player_, nullptr, this);


	for (int i  = 0; i<Resources::SceneID::lastSceneID;i++)
	{
		scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].backgroundId_), static_cast<Resources::SceneID>(i), LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].ghBackgroundId_), Resources::scenes_[i].moveLine_);
		//scenes_[i] = new Scene(LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].backgroundId_), (Resources::SceneID)(i), Resources::scenes_[i].moveLine_);
		scenes_[i]->mapPos = Resources::scenes_[i].mapPos_;
		scenes_[i]->mapIcon = LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::scenes_[i].mapIcon_);
	}

	Entity* window = addEntity(0);
	window->addComponent<Transform>(120 * 4, 72 * 4, 76 * 4, 28 * 4);
	window->addComponent<Animator<int>>()->changeAnim(Resources::OfficeWindowAnim);
	scenes_[Resources::SceneID::Despacho]->entities.push_back(window);

	Entity* escritorio = addEntity(0);
	escritorio->addComponent<Transform>(440, 360, 384, 264);
	escritorio->addComponent<Sprite>()->setTexture(Resources::TextureID::Escritorio);
	scenes_[Resources::SceneID::Despacho]->entities.push_back(escritorio);

	for (auto& a : Resources::actors_)
	{
		Actor* e = new Actor(this, a);
		if(a.ghWorld_)
			scenes_[a.startScene_]->ghEntities.push_back(e->getEntity());
		else scenes_[a.startScene_]->entities.push_back(e->getEntity());
		//GETCMP2(e->getEntity(), Transform)->setPosY(PLAYABLEHIGHT - GETCMP2(e->getEntity(), Transform)->getPos().getY());
		actors_[a.id_] = e;
#ifdef _DEBUG
		e->getEntity()->addComponent<DragDrop>(nullptr, nullptr)->clearFuncs();
		GETCMP2(e->getEntity(), Transform)->name = actors_[a.id_]->getName();
#endif // _DEBUG
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
				bool change = d->isLocked();
				if (doorCallback != nullptr)
					change = doorCallback(d);
				if (!change)
				{
					player->getComponent<Transform>(ecs::Transform)->setPos(Resources::doors_[d->getId()].spawnPoint_.getX(),
						Resources::doors_[d->getId()].spawnPoint_.getY());
					StoryManager::instance()->changeScene(Resources::doors_[d->getId()].goTo_);
				}
				SDLGame::instance()->getAudioMngr()->playChannel(Resources::Door_open, 0, 2);
			}
		);
#ifdef _DEBUG
		d->getEntity()->addComponent<DragDrop>(nullptr, nullptr)->clearFuncs();
		in->GetTransform()->name = to_string(d->getId());

#endif // _DEBUG
	}
	for (auto& c : Resources::clues_)
	{
		clues_[c.id_] = new Clue(c);
	}
	for (auto& i : Resources::investigables_) {
		Investigable* inv = new Investigable(this, i);
		//GETCMP2(inv->getEntity(), Transform)->setPosY(PLAYABLEHIGHT - GETCMP2(inv->getEntity(), Transform)->getPos().getY());
		scenes_[i.startScene_]->entities.push_back(inv->getEntity());
		investigables_[inv->getId()] = inv;
#ifdef _DEBUG
		inv->getEntity()->addComponent<DragDrop>(nullptr, nullptr)->clearFuncs();
		GETCMP2(inv->getEntity(), Transform)->name = clues_[inv->getId()]->title_;
#endif // _DEBUG
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
	Transform* eTr = e->addComponent<Transform>(0,0,60,60);
	Sprite* eSprite = e->addComponent<Sprite>(nullptr);
	ButtonOneParametter<Interactable*>* eBut = e->addComponent<ButtonOneParametter<Interactable*>>(std::function<void(Interactable*)>([](Interactable* i) {}), nullptr);
	e->addComponent<InteractableLogic>(&interactables_, GETCMP2(player_, Transform), eTr, eSprite, eBut);
	e->setActive(true);



	//playerCentralClues_.push_back(centralClues_[]); //ESTO NO IR� AQU�. DESBLOQUEARLO CUANDO TOQUE
	//playerCentralClues_.push_back(centralClues_[Resources::Tut_Cent_MotivoEntrada]);

	StoryManager* sm = this;
	//actors_[Resources::ActorID::MacarenaMartinez]->setDialogActive(0, false);
	for (auto pair : DialogSelectors::functions)
	{
		actors_[pair.first]->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->setSelectorFunc(pair.second);
	}

	/*
	
	
	ESTO ES PA PROBAR LA ESCENA CON ANIMACIONES CHACHIS Y TAL
	
	
	*/

	

	
	Entity* fan1 = addEntity(1);
	fan1->addComponent<Transform>(51 * 4, 12 * 4, 33 * 8, 3*8);
	fan1->addComponent<Animator<int>>()->changeAnim(Resources::officeFanAnim);
	scenes_[Resources::SceneID::Despacho]->entities.push_back(fan1);

	Entity* fan2 = addEntity(1);
	fan2->addComponent<Transform>(210 * 4, 12 * 4, 33 * 8, 3 * 8);
	fan2->addComponent<Animator<int>>()->changeAnim(Resources::officeFanAnim);
	scenes_[Resources::SceneID::Despacho]->entities.push_back(fan2);
	



	setSceneCallbacks();
	//cerramos las puertas que tienen que estar bloqueadas porque al principio todas están abiertas
	doors_[Resources::DoorID::pEntradaBosque]->setLocked(true);
	doors_[Resources::DoorID::pEntradaCaseta]->setLocked(true);

	//desactivamos las pruebas que tienen que estar desactivadas
	setInvestigableActive(Resources::ClueID::Prin_PanueloRojo, false);
	setInvestigableActive(Resources::ClueID::Prin_PistolaSilenciador, false);
	setInvestigableActive(Resources::ClueID::Prin_Llave, false);
	//setInvestigableActive(Resources::ClueID::Prin_LlaveErnesto, false);
	setInvestigableActive(Resources::ClueID::Prin_ContratoGus, false);
	setInvestigableActive(Resources::ClueID::Prin_PapelesHerencia, false);
	setInvestigableActive(Resources::ClueID::Prin_Foto, false);
	setInvestigableActive(Resources::ClueID::Prin_OrdenAsesinato, false);

	//desactivamos todo lo que queda
	Entity* carlitos = actors_[Resources::F_Afur]->getEntity();
	carlitos->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(false);
	carlitos->getComponent<Interactable>(ecs::Interactable)->setEnabled(false);
	
	Entity* yaya = actors_[Resources::F_MamaCapo]->getEntity();
	yaya->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(false);
	yaya->getComponent<Interactable>(ecs::Interactable)->setEnabled(false);
	
	//createTimeLine();
	setTunerDificultyLevel(0);
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
	for (size_t i = 0; i < StateMachine::APPS::lastIconApp; i++) {
		Entity* icon = EM->addEntity(3);
		apps_[i] = icon;
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
		Sprite* sp = icon->addComponent<Sprite>(iconTexture);
		sp->setSubTexture(Resources::NotificationIcon);

		itr->setWH(mobTr->getW() / 4, mobTr->getW() / 4);
		itr->setPos(mobTr->getPos().getX() + offset + (i % 3) * (itr->getW() + offset), mobTr->getPos().getY() + offset + (i / 3) * (itr->getH() + offset) + 25);
		icon->setUI(true);
		icons.push_back(itr);
		itr->setParent(mobTr);
		if (i != StateMachine::APPS::ContactsApp) {
			auto anim = icon->addComponent<Animator<Transform*>>();
			if (i == StateMachine::APPS::NotesApp) {
				icon->addComponent<ButtonOneParametter<StoryManager*>>([sp,i, anim](StoryManager* game)
				{
					game->getPlayer()->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->resetTarget();
					anim->setEnabled(true);
					if (anim->getAnim() == Resources::LastAnimID)
					{
						anim->changeAnim(Resources::AppPressedAnim);
						anim->setFinishFunc([game, i, anim](Transform* t)
						{
							game->activateNotes();
							anim->setEnabled(false);
						}, nullptr);
					}
					else anim->restartAnim();
				}, this);
			}

			//Esto es para lo normal

			else icon->addComponent<ButtonOneParametter<LoremIpsum*>>([i, anim, sp](LoremIpsum* game)
			{
				game->getStoryManager()->getPlayer()->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->resetTarget();
				sp->showSubtexture(false);
				anim->setEnabled(true);
				if (anim->getAnim() == Resources::LastAnimID)
				{
					anim->changeAnim(Resources::AppPressedAnim);
					anim->setFinishFunc([game, i, anim, sp](Transform* t)
					{
						game->getStateMachine()->PlayApp((StateMachine::APPS)i, game->getStoryManager());
						anim->setEnabled(false);
					}, nullptr);
				}
				else anim->restartAnim();

			}, loremIpsum);
			icon->setActive(false);
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
	Entity* player = EM->addEntity(1);
	Transform* tp = player->addComponent<Transform>();
	player->addComponent<PlayerKBCtrl>(SDLK_d, SDLK_a, SDLK_w, SDLK_s, p);
	player->addComponent<PlayerMovement>(this);
	Animator<Transform*>* anim = player->addComponent<Animator<Transform*>>();
	//player->addComponent<Rectangle>(SDL_Color{ COLOR(0xFF0000FF) });
	player->addComponent<FollowedByCamera>(LoremIpsum_->getStateMachine()->playState_->getCamera(), tp);
	tp->setPos(200, PLAYABLEHIGHT-2*LAZAROHEIGHT);
	tp->setWH(160, 2*LAZAROHEIGHT);
	//anim sounds
	anim->setSelectorFunction([anim](Animator<Transform*>* c)
	{
		if (c->getAnim() == Resources::AnimID::WalkingSDLAnim) {
			if (c->getActualFrame() == 2 || c->getActualFrame() == 6) {
				auto footstep = StoryManager::instance()->selectFootstep();
				SDLGame::instance()->getAudioMngr()->playChannel(footstep, 0, 2);
			}
		}
		/*else if (c->getAnim() == Resources::AnimID::SDLGhostAnim) {
			if (!SDLGame::instance()->getAudioMngr()->isPlaying(2)) {
				SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Levitating, -1, 2);
			}
		}*/
		else if (c->getAnim() == Resources::AnimID::DieFalling) {
			if (SDLGame::instance()->getTime() - c->getData()[0] > 10000) {

			}
		}
	});
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
	for (auto i : investigables_) {
		delete i.second;
	};
	//for (auto dialog : dialogs_)
	//	delete dialog.second; //ahora los componentes los borran, seamos perdonados hermanos
	/*for (auto& c : Resources::centralClues_)
	{
		delete centralClues_[c.id_];
	}*/

	for (int i = 0; i < centralClues_.size(); i++)
	{
		delete centralClues_[i];
	};
	delete notes_;
}
void StoryManager::CheckSceneSpecial(bool b)
{
	bool despacho = currentScene->scene == Resources::SceneID::DespachoPolo;
	bool habitacionSabrina = currentScene->scene == Resources::SceneID::HabitacionSabrina;
	bool pasillo = currentScene->scene == Resources::SceneID::Pasillo;
	bool subTex = false;
	if ( despacho ||
		 habitacionSabrina ||
		 pasillo)
	{
		getBackgroundSprite()->showSubtexture(b);
		subTex = true;
	}
	else if (currentScene->scene == Resources::Bosque)
	{
		UiDisplay->getComponent<Sprite>(ecs::Sprite)->setEnabled(b);
		this->UiDisplay->getComponent<Sprite>(ecs::Sprite)->setTexture(Resources::BosqueOverlay);
	}
	if (b && subTex)
	{
		Resources::TextureID id = (despacho) ? Resources::DespachoCapoOverlay : (habitacionSabrina) ? Resources::HabitacionSabrinaOverlay : Resources::PasilloOverlay;
		getBackgroundSprite()->setSubTexture(id);
	}

}
void StoryManager::changeScene(Resources::SceneID newScene)
{
	PlayerKBCtrl* kbCtrl = player_->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl);
	kbCtrl->resetTarget();
	PlayerMovement* playerMove = player_->getComponent<PlayerMovement>(ecs::PlayerMovement);
	Animator<int>* anim = backgroundViewer_->getComponent<Animator<int>>(ecs::Animator);
	anim->setEnabled(true);
	anim->changeAnim(Resources::FadeInAnim);
	anim->setFinishFunc([anim](int a) 
	{
		anim->changeAnim(Resources::FadeOutAnim);
		anim->setFinishFunc([anim](int a)
			{
				anim->setEnabled(false);
			}, 0);
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
		CheckSceneSpecial(false);
	}
	currentScene = scenes_[newScene];
	setBackground();
	if (getSceneCallback(newScene) != nullptr)
		getSceneCallback(newScene)();
	CheckSceneSpecial(true);
	if(prevScene == nullptr)		//Si vamos a hacer cambios a escenas con músicas diferentes hay que revisitar esto
		setMusic();
	vector<Entity*> vec;
	if (currentScene->ghWorld) {
		vec = currentScene->ghEntities;
	}
	else vec = currentScene->entities;
	setEntitiesActive(vec, true);

	Camera* cam = LoremIpsum_->getStateMachine()->playState_->getCamera();
	cam->setLimitX(currentScene->background->getWidth());
	cam->setLimitY(currentScene->background->getHeight());

	//ya se arreglará porque si lo descomento, no funciona nada


	int x = player_->getComponent<Transform>(ecs::Transform)->getPos().getX() - 200;
	if (x < 0) x = 0;
	else if (x + cam->getWidth() > cam->getLimitX())x=cam->getLimitX()-cam->getWidth();
	cam->setPos(x, 0);



	/*
	
	VAMOS A SEGUIR LLENANDO DE MIERDA EL STORY MANAGER YUUUUUJU

	*/
	setInvestigableActive(Resources::ClueID::Prin_PistolaSilenciador, false);
	setInvestigableActive(Resources::ClueID::Prin_PanueloRojo, false);
}
void StoryManager::changeSceneState() {
	if (currentScene != nullptr) {
		bool st = currentScene->ghWorld;
		if (st) {
			player_->getComponent<Animator<int*>>(ecs::Animator)->getData()[0] = SDLGame::instance()->getTime();
			player_->getComponent<Animator<int*>>(ecs::Animator)->changeAnim(Resources::AnimID::DieFalling);
		}
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
		/*Interactable* it = e->getComponent<Interactable>(ecs::Interactable);
		if (it != nullptr)
			it->setEnabled(b);*/
	}
}
/*


 -> -> ->  [] -> -> -> { ->|  |<- }


*/
void StoryManager::setBackground() {
	Texture* t = nullptr;
	if (currentScene->ghWorld)
	{
		this->backgroundViewer_->getComponent<Sprite>(ecs::Sprite)->setEnabled(true);
		this->backgroundViewer_->getComponent<Sprite>(ecs::Sprite)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BackgroundDeathWorld));
	}
	else
	{
		this->backgroundViewer_->getComponent<Sprite>(ecs::Sprite)->setEnabled(false);
	}
	t = currentScene->background;

	Resources::AnimID actualAnim;
	if (currentScene->ghWorld)
		actualAnim = Resources::SDLGhostAnim;
	else
		actualAnim = Resources::IdleSDLAnim;

	player_->getComponent<Animator<Transform*>>(ecs::Animator)->changeAnim(actualAnim);
	getBackgroundSprite()->setTexture(t);
	getBackgroundSprite()->getEntity()->getComponent<Transform>(ecs::Transform)->setWH(t->getWidth(), t->getHeight());
}
void StoryManager::setMusic() {
	auto am = LoremIpsum_->getGame()->getAudioMngr();
	am->haltMusic();
	if (currentScene->ghWorld) {
		am->playMusic(Resources::GhostDraft);
	}
	else am->playMusic(Resources::MTloo);
}
void StoryManager::addAvailableScene(Scene* scene)
{
	availableScenes_.push_back(scene);
	phone_->getComponent<Phone>(ecs::Phone)->notification(StateMachine::APPS::MapsApp);
}
void StoryManager::removeAvailableScene(Scene* scene)
{
	int i = 0;
	while (i < availableScenes_.size() && availableScenes_[i] != scene)
	{
		i++;
	}
	if (i < availableScenes_.size())
	{
		availableScenes_.erase(availableScenes_.begin() + i);
	}
}
vector<Entity*> StoryManager::createBars(EntityManager* EM) {
	vector<Entity*> bars;

	int pxSprite = 56;
	int pxPerY = (LoremIpsum_->getGame()->getWindowHeight() / 5) * 3 / pxSprite;

	int halfW = LoremIpsum_->getGame()->getWindowWidth()/2;
	int y = (LoremIpsum_->getGame()->getWindowHeight() / 5) * 4 - 2 * pxPerY - 1;
	int barwidth = 40;

	vector<BarInfo> barInfo = tunerDificultyLevels[actualTunerDificultyLevel];

	for (int i = 0; i < barInfo.size(); i++) {
		Entity* bar = EM->addEntity(3);
		bar->addComponent<Transform>(halfW + (((halfW / 2.0) / (barInfo.size() + 1.0)) * (i + 1.0) - barwidth / 2.0) - 40.0, (double)y, (double)barwidth, 0.0);
		bar->addComponent<Bar>(EM, barInfo[i].upSpeed, barInfo[i].downSpeed, barInfo[i].minWinPer, barInfo[i].maxWinPer);
		bar->addComponent<Rectangle>(SDL_Color{ COLOR(0x00d3ffCC) });
		bars.push_back(bar);
	}

	return bars;
}

void StoryManager::setPortrait(Resources::ActorID id)
{
	if (actors_[id]->getPortrait() != Resources::Blank)
	{
		dialogPortrait->getComponent<Sprite>(ecs::Sprite)->setEnabled(true);
		dialogPortrait->getComponent<Sprite>(ecs::Sprite)->setTexture(actors_[id]->getPortrait());
		dialogPortrait->getComponent<Animator<int>>(ecs::Animator)->setEnabled(false);
	}
	else if (actors_[id]->getPortraitAnim() != Resources::noAnim)
	{
		dialogPortrait->getComponent<Animator<int>>(ecs::Animator)->setEnabled(true);
		dialogPortrait->getComponent<Animator<int>>(ecs::Animator)->changeAnim(actors_[id]->getPortraitAnim());
		dialogPortrait->getComponent<Sprite>(ecs::Sprite)->setEnabled(false);
	}
}

void StoryManager::createTimeLine()
{
	/*
	currentScene_ = sm->getScene(info.startScene_);
	sprite_ = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);

	entity_ = sm->addEntity(0);
	Transform* tr = entity_->addComponent<Transform>(info.x_, info.y_, info.w_, info.h_);
	Interactable* in = entity_->addComponent<Interactable>();
	in->setIcon(Resources::TextureID::ClueInteraction);
	sm->interactables_.push_back(in);
	entity_->setActive(false);
	id_ = info.unlockable_;
	Resources::InvestigableInfo i = info;
	in->setCallback([sm, i](Entity* player, Entity* other) { sm->thinkOutLoud({ i.thought_ }); sm->addPlayerClue(i.unlockable_);  });

	if (info.sprite_ != Resources::Blank)
	{
		Texture* t = SDLGame::instance()->getTextureMngr()->getTexture(info.sprite_);
		entity_->addComponent<Sprite>(t);
		tr->setWH((double)t->getWidth() * 8.0, (double)t->getHeight() * 8.0);
	}
	*/
	//Ricky please

	Entity* tl = addEntity(3);
	tl->addComponent<Transform>(620, 350, 30, 30);
	//Sprite* sp = tl->addComponent<Sprite>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureID::Bala));
	Interactable* inter = tl->addComponent<Interactable>();
	inter->setIcon(Resources::TextureID::ClueInteraction);
	interactables_.push_back(inter);

	tl->setActive(false);
	inter->setCallback([](Entity* e, Entity* e2) {
		cout << "TEST \n";
		LoremIpsum::instance()->getStateMachine()->PlayApp(StateMachine::APPS::TimelineApp);
		});

	scenes_[Resources::SceneID::Despacho]->entities.push_back(tl);
}

void StoryManager::activateApps(bool b) {
	for (size_t i = 0; i < StateMachine::APPS::lastIconApp; i++) {
		apps_[i]->setActive(b);
	}
}


void StoryManager::activateNotes() {
	activateApps(true);
	notes_->activate();
	InputHandler::instance()->lock();
}

void StoryManager::deactivateNotes() {
	activateApps(false);
	notes_->deactivate();
	InputHandler::instance()->unlock();
}

void StoryManager::fadeOutAndInAgain(vector<string>& lines)
{
	Animator<int>* anim = backgroundViewer_->getComponent<Animator<int>>(ecs::Animator);
	anim->setEnabled(true);
	anim->changeAnim(Resources::FadeInAnim);
	thinkOutLoud(lines, [anim](DialogComponent* dc) 
		{
			StoryManager::instance()->getBackgroundSprite()->getEntity()->getComponent<Animator<int>>(ecs::Animator)->changeAnim(Resources::FadeOutAnim);
		});
}




void StoryManager::setSceneCallback(std::function<void()>f, Resources::SceneID id)
{
		onPlaceEnteredFunc_[id] = f;
}

void StoryManager::resetTLClue(CentralClue* cc)
{
	LoremIpsum::instance()->getStateMachine()->ch_->resetWrongClue(cc);
}

//esto es una guarreria necesaria para el caso principal. ¿Se podría hacer mejor? Puede. ¿Yo? No
//deja tu respuesta en los comentarios
void StoryManager::setSceneCallbacks()
{
	onPlaceEnteredFunc_.resize(Resources::lastSceneID);
	for (int i = 0; i < onPlaceEnteredFunc_.size(); i++)
		onPlaceEnteredFunc_[i] = nullptr;

	std::function<void()>f([]() 
		{
			StoryManager* sm = StoryManager::instance();

			//para que no entres por el despacho más
			sm->removeAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo));

			sm->setGameCase(1); //perfe

			//empiezas a hablar con el capo en cuanto entras
			sm->getActors()[Resources::ActorID::Capo]->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->interact();

			//ponemos el spawnPoint para que salga delante del escritorio
			sm->getPlayer()->getComponent<Transform>(ecs::Transform)->setPos(400,288);

			//borrar esto, es para pruebas
			sm->addAvailableScene(sm->getScene(Resources::SceneID::Bosque));
			sm->setSceneCallback([]() {}, Resources::SceneID::DespachoPolo);
		});
	onPlaceEnteredFunc_[Resources::SceneID::DespachoPolo] = f;
	doors_[Resources::pDespachoSotano]->getEntity()->getComponent<Interactable>(ecs::Interactable)->setEnabled(false);
	//onPlaceEnteredFunc_[Resources::SceneID::Pasillo] = []() {
	//	cout << "PASILLO";
	//	 };
	//onPlaceEnteredFunc_[Resources::SceneID::DespachoPolo] = []() {
	//	cout << "DESPACHO";
	//	StoryManager::instance()->removeLayer(Vector2D(530, 320)); };
	//onPlaceEnteredFunc_[Resources::SceneID::HabitacionSabrina] = []() {
	//	cout << "HABITACIONSABRINA";
	//	StoryManager::instance()->removeLayer(Vector2D(550, 470)); };
}

Resources::AudioId StoryManager::selectFootstep() {
	Resources::AudioId fs;
	//Si la escena es una que tenga suelo de tierra, escoge un footstep de grass
	if (getCurrentScene()->scene == Resources::SceneID::Bosque || getCurrentScene()->scene == Resources::SceneID::JardinEntrada) {

		int rand = std::rand() % 8; //como hay 8 audios de pasos diferentes, escoge uno de los ocho aleatoriamente
		fs = Resources::AudioId(Resources::AudioId::FS_grass_0 + rand);
	}
	else {
		int rand = std::rand() % 7; //como hay 7 audios de pasos diferentes, escoge uno de los ocho aleatoriamente
		fs = Resources::AudioId(Resources::AudioId::FS_wood_0 + rand);
	}
	return fs;
}


Scene* StoryManager::moveActorTo(Resources::ActorID actor, Resources::SceneID to, int x, int y)
{
	Actor* a = actors_[actor];
	Scene* scene = actors_[actor]->getCurrentScene();
	Scene* newScene = scenes_[to];
	int i=0;
	vector<Entity*>& entities = (a->isDead()) ? scene->ghEntities : scene->entities;
	vector<Entity*>& newEntities = (a->isDead()) ? newScene->ghEntities : newScene->entities;
	for (i=0;i<entities.size();i++)
	{
		if (entities[i] == a->getEntity())
			break;
	}
	entities.erase(entities.begin() + i);
	newEntities.push_back(a->getEntity());
	if (x != -1)
		a->getEntity()->getComponent<Transform>(ecs::Transform)->setPosX(x);
	if (y != -1)
		a->getEntity()->getComponent<Transform>(ecs::Transform)->setPosX(y);
	return newScene;
}

bool StoryManager::checkVictory() {
	Timeline* tl = LoremIpsum_->getStateMachine()->tl_;
	return(tl->getCorrectEvents() && tl->getCorrectOrder());
}

void StoryManager::presentCase() {
	//aquí tiene que teletransportar a SDL y a la gente para el momento Sherlock Holmes.
	//En el momento Sherlock Holmes, suelta un thinking out loud con el texto de los eventos, y hace las comprobaciones de getOrder y getEvents de la timeline.
	//Si está mal, hace resetTimeline, y si está bien, se continúa
	Timeline* tl = LoremIpsum_->getStateMachine()->tl_;

	LoremIpsum::instance()->getStateMachine()->PlayGame();
	getActor(Resources::ActorID::Capo)->Move(Resources::SceneID::Salon);
	getActor(Resources::ActorID::CarlosI)->Move(Resources::SceneID::Salon);
	getActor(Resources::ActorID::CarlosI)->getEntity()->getComponent<Transform>(ecs::Transform)->setPosX(250);
	getActor(Resources::ActorID::Capa)->Move(Resources::SceneID::Salon);

	changeScene(Resources::SceneID::Salon);
	vector<string> lines;
	lines.push_back("Hola, familia Polo. Ya tengo mi hipótesis final y voy a mostrársela a la policía.");
	lines.push_back("Primero: " + tl->getDownEvents()[0]->actualDescription_);
	lines.push_back("Segundo: " + tl->getDownEvents()[1]->actualDescription_);
	lines.push_back("Tercero: " + tl->getDownEvents()[2]->actualDescription_);
	lines.push_back("Y, para finalizar: " + tl->getDownEvents()[3]->actualDescription_);
	thinkOutLoud(lines, [tl](DialogComponent*)
		{
			StoryManager* sm = StoryManager::instance();
			DialogComponent* capo = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent);
			int* data = capo->getData();	//para cambiar el valor en función de si has ganado o perdido: -1 significa que pierdes y 1, que ganas
			if (!(tl->getCorrectEvents() && tl->getCorrectOrder()))
			{
				data[5] = -1;
				tl->resetTimeline();
				//sacar un popup que te diga que te has equivocado y tienes que replantear tu solución, y cuando le des a OK te devuelva a tu despacho
			}
			else
			{
				data[5] = 1;
				capo->interact();
			}
		});


	
}