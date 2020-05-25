#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include "Entity.h"
#include "Texture.h"
#include "DialogComponent.h"
#include "DialogSystem.h"
#include "Bar.h"
#include "Singleton.h"
#include "DoorSelectors.h"
#include "Animator.h"
#include "Notes.h"
#include "ClueCallbacks.h"
#include "Interactable.h"

class Pin;
class Sprite;
class Interactable;
class StoryManager;
class Phone;
const size_t SIZE_TMAXVALUE = 65535;

class Clue
{
public:
	Clue(Resources::ClueInfo info);
	~Clue() {};
	std::string title_ = "";
	std::string description_ = "";
	std::string eventText_ = "";
	Resources::ClueType type_;
	Resources::ClueID id_;
	Resources::TextureID spriteId_;

	//Esta funcion se llama cuando el jugador consigue una pista
	//DialogId desbloqueara ese dialogo, sceneId desbloqueara esa escena y clueid lo mismo con <<otra>> pista
	//El valor MAXVALUE se utiliza para poner por defecto a los parametros y saber que no hay que desbloquearlo
	std::function<void(size_t dialogID, Resources::SceneID sceneID, Resources::ClueID clueID)> gotClueCallback_;
	
	bool placed_ = false;					//true = chinchetario
	Entity* entity_ = nullptr;
};
class CentralClue : public Clue
{
public:
	CentralClue(Resources::CentralClueInfo info) : Clue(info), links_(info.links_), eventDescription_(info.eventDescription_), timeline_(info.timeline_){};
	~CentralClue() {};
	vector<Resources::ClueID> links_;
	std::string eventDescription_ = "";
	std::string actualDescription_ = "";
	bool isEvent_ = false;
	bool isCorrect_ = false;
	bool timeline_; //indica si será un acontecimiento (contará para la timeline) o un suceso (no contará para la timeline)
	vector<Entity*> pins_;
};
struct BarInfo {
	// valores locos para el debugeo
	double upSpeed = 10;
	double downSpeed = 100;
	double minWinPer = 0;
	double maxWinPer = 95;
};

//Una escena es una zona jugable. Ya sea una habitaci�n o un conjunto de ellas, una casa entera...
struct Scene
{
	Scene() { background = nullptr; };
	Scene(Texture* t, Texture* t2) { background = t; ghBackground = t2; };
	Scene(Texture* t, Resources::SceneID s, Texture* t2, std::vector<Vector2D> movementLine) { background = t; scene = s; ghBackground = t2; movementLine_ = movementLine;};
	Scene(Texture* t, Resources::SceneID s, std::vector<Vector2D> movementLine) { background = t; scene = s; movementLine_ = movementLine; };
	~Scene() {};
	//Este vector guardar� todos los objetos, personajes, puertas, pistas...
	std::vector<Entity*> entities;
	std::vector<Entity*> ghEntities;		//Este guarda las cosas fantasmicas
	bool ghWorld = false;
	//Cada escena tiene dos fondos (mundo vivo, mundo muerto)
	Texture* background = nullptr;
	Texture* ghBackground = nullptr;
	Texture* mapIcon = nullptr;
	Vector2D mapPos = { 0,0 }; //posici�n que ocupar� en el mapa. Esto habr� que modificarlo en archivos o en Tiled o algo para no ponerlo a pelo en el c�digo
	std::vector<Vector2D> movementLine_ = { {0,0} };
	Resources::SceneID scene = Resources::SceneID::lastSceneID; //Lo inicializo a LastSceneID pero en la constructora se van a�adiendo

};

class Investigable {
public:
	Investigable(StoryManager* sm, Resources::InvestigableInfo info);
	inline Texture* getSprite() { return sprite_; };
	Resources::ClueID getId() { return id_; };
	Entity* getEntity() { return entity_; }
private:
	Resources::ClueID id_;
	Scene* currentScene_ = nullptr;
	Texture* sprite_ = nullptr;
	Entity* entity_ = nullptr;
};

class Door {
public:
	Door(StoryManager* sm, Resources::DoorInfo info);
	~Door() {};
	inline Texture* getSprite() { return sprite_; };
	Resources::DoorID getId() { return id_; };
	Entity* getEntity() { return entity_; }
	bool inline isLocked() { return locked_; };
	void inline setLocked(bool l) { locked_ = l; };
	std::function<bool(Door*)> getFunc() { return func_; };
	void setFunc(std::function<bool(Door*)> f) { func_ = f; };


private:
	Resources::DoorID id_;
	Scene* currentScene_ = nullptr;
	Texture* sprite_ = nullptr;
	Entity* entity_ = nullptr;
	bool locked_ = false;
	std::function<bool(Door*)> func_ = nullptr;

};

class Actor
{
public:
	Actor(StoryManager* sm, Resources::ActorInfo info) : Actor(sm, info, {1000,250 },20,20) {}
	Actor(StoryManager* sm, Resources::ActorInfo info, Vector2D pos, int w, int h);
	~Actor() {};
	inline std::string getName() { return name_; };
	inline Texture* getSprite() { return sprite_; };
	void addDialog(Dialog* d);
	Resources::ActorID getId() { return id_; };
	Entity* getEntity() { return entity_; };
	Resources::TextureID getPortrait() { return portrait_; }
	Resources::AnimID getPortraitAnim() { return portraitAnim_; }
	Scene* getCurrentScene() { return currentScene_; }
	void Move(Resources::SceneID newScene);
	Dialog* getDialog(int id);
	bool isDead() { return dead; }
private:

	Resources::ActorID id_;
	string name_ = "";
	Scene* currentScene_ = nullptr;
	Texture* sprite_ = nullptr;
	Resources::TextureID portrait_;
	Resources::AnimID portraitAnim_=Resources::noAnim;
	Entity* entity_ = nullptr;
	bool dead = false;
	
};

class StoryManager : public Singleton<StoryManager>
{
public:
	friend class Singleton<StoryManager>;
	StoryManager(LoremIpsum* li, EntityManager* entityManager) : Singleton(), LoremIpsum_(li), entityManager_(entityManager) { init(); };
	virtual ~StoryManager();
	void init();

	//============================================================================================================================

	inline Scene* getCurrentScene() { return currentScene; };
	Scene* getScene(Resources::SceneID id) { return scenes_[id]; };
	void changeScene(Resources::SceneID newScene);
	//Cambia el estado de la escena(activa/desactiva las entidades de los vectores y otros ajustes)
	void changeSceneState();
	//Recorre el vector y activa/desactiva(interactable incluido)
	void setEntitiesActive(vector<Entity*> vec, bool b);
	void setBackground();
	void setMusic();

	//============================================================================================================================

	const map<std::size_t, Clue*> getClues() { return clues_; }
	inline const vector<Clue*> getPlayerClues() { return playerClues_; };
	inline void addPlayerClue(Resources::ClueID id);
	void removeTutorialClues();

	bool hasClue(Clue* clue)
	{
		int i = 0;
		while (i < playerClues_.size() && playerClues_[i] != clue) i++;

		return i < playerClues_.size();
	}

	inline const vector<CentralClue*> getPlayerCentralClues() { return playerCentralClues_; };

	//============================================================================================================================

	Entity* addEntity(int layer = 0);
	Entity* getPlayer() { return player_; };
	Entity* getDialogBox() { return dialogBox_; };
	Sprite* getBackgroundSprite() { return bgSprite_; };
	Entity* getPhone() { return phone_; }

	//============================================================================================================================

	Dialog* getDialog(size_t id) { return dialogs_[id]; };
	Text* getDialogBoxText() { return dialogBoxText_; };
	Text* getDialogBoxActorName() { return dialogBoxActorName_; };

	vector<Scene*> getAvailableScenes() { return availableScenes_; };
	void addAvailableScene(Scene* scene);
	void removeAvailableScene(Scene* scene);


	void call(Resources::ActorID to) {
		if (fakeActor_ == nullptr)
		{
			fakeActor_ = entityManager_->addEntity();
			fakeActor_->addComponent<DialogComponent>(nullptr, nullptr, this);
		}
		fakeActor_->setActive(true);
		auto other = actors_[to]->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent);
		auto dc = fakeActor_->getComponent<DialogComponent>(ecs::DialogComponent);
		dc->copyDialogComponent(other);
		dc->interact();
		//other->interact();
	};

	list<Interactable*> interactables_;

	vector<Entity*> createBars(EntityManager* EM);
	string getActorName(Resources::ActorID id) { string lazaro("Lazaro"); return (id == -1) ? lazaro : actors_[id]->getName(); }
	void setPortrait(Resources::ActorID id);
	
	std::vector <std::pair<Dialog*, std::function<void(DialogComponent*)>>>& getThougts() { return thoughts_; }
	void thinkOutLoud(vector<string> lines, std::function<void(DialogComponent*)>f=nullptr)
	{
		vector<string> l = lines;
		auto func = f;
		//unique_ptr<Dialog> d(new Dialog(options));
		
		vector<DialogLine> dialogLines;
		for (auto line : l)
			dialogLines.push_back(DialogLine(0, line));
		DialogOption p("", dialogLines);
		vector<DialogOption> options;
		options.push_back(p);
		Dialog* d =new Dialog(options);
		std::pair<Dialog*, std::function<void(DialogComponent*)>> pair(d, f);
		thoughts_.push_back(pair);
		if (thoughts_.size() == 1)
		{
			dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent)->setSingleDialog(thoughts_.front().first);
			dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent)->setDialogFinishedCallback([](DialogComponent* dc) {

				StoryManager::instance()->actualThougtCallback(dc);
				StoryManager::instance()->checkForThought(dc);
				});
			dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent)->interact();

		}
	}
	void checkForThought(DialogComponent* dc)
	{
		thoughts_.erase(thoughts_.begin()); //borra el primer elemento
		if (thoughts_.size() > 0)
		{
			dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent)->setSingleDialog(thoughts_.front().first);
			dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent)->setDialogFinishedCallback([](DialogComponent* dc) {

				StoryManager::instance()->actualThougtCallback(dc);
				StoryManager::instance()->checkForThought(dc);
				});
			dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent)->interact();
		}
	}
	void actualThougtCallback(DialogComponent* dc)
	{
		if(thoughts_.front().second != nullptr)
			thoughts_.front().second(dc);
	}
	//Make sure to call StoryManager::instance()->hidePopUpMessage() on the callback to hide the message on click of the button
	//thats the default behaviour of the button, would be nice if your callback also resets it to that, idk.

	void setInvestigableActive(Resources::ClueID clue, bool active)
	{
		int i = 0;
		while (i < investigables_.size() && investigables_[i]->getId() != clue)
		{
			i++;
		}
		
		if (i < investigables_.size())
		{
			investigables_[i]->getEntity()->getComponent<Interactable>(ecs::Interactable)->setEnabled(active);
			investigables_[i]->getEntity()->getComponent<Sprite>(ecs::Sprite)->setEnabled(active);
		}
	}
	void fadeOutAndInAgain(vector<string>& lines);
	map<std::size_t, Actor*> getActors() const { return actors_; };
	Actor* getActor(Resources::ActorID actor) { return actors_[actor]; };
	//Cosas para la timeline, chinchetario, pistas y los eventos
	int getGameCase() { return gameCase_; }
	void setGameCase(int c) { gameCase_ = c; }
	vector<Resources::ClueID> getTimeline() { return timelineSolutions_[gameCase_]; }
	bool getEventChanges() { return eventChanged; }

	map<size_t, CentralClue*> getCentralClues() { return centralClues_; };
	void setEventChanges(bool b) { eventChanged = b; }
	bool getInvestigableChanges() { return investigableChanged; }
	void setInvestigableChanges(bool b) { investigableChanged = b; }

	Door* getDoor(Resources::DoorID d) { return doors_[d]; };
	
	void deactivateNotes();
	void setSceneCallbacks();
	std::function<void()> getSceneCallback(size_t id) { return onPlaceEnteredFunc_[id]; }
	std::vector<std::function<void()>> onPlaceEnteredFunc_;

	Resources::AudioId selectFootstep();
	Scene* moveActorTo(Resources::ActorID actor, Resources::SceneID to, int x=-1, int y=-1);
	Entity* getUIDisplay() { return UiDisplay; };

	int getTunerDificultyLevel() { return actualTunerDificultyLevel; }
	void setTunerDificultyLevel(int newLevel) { actualTunerDificultyLevel = newLevel; };
private:
	StoryManager() {};
	std::vector<std::vector<BarInfo>> tunerDificultyLevels;
	int actualTunerDificultyLevel = 0;
	Scene* currentScene=nullptr;
	Scene* prevScene = nullptr;	//estado escena anterior (para no cortar la musica)
	Entity* dialogPortrait=nullptr;
	Entity* dialogBox_= nullptr;
	LoremIpsum* LoremIpsum_ = nullptr;
	EntityManager* entityManager_ = nullptr;
	Text* dialogBoxActorName_ = nullptr;
	Text* dialogBoxText_ = nullptr;
	Entity* backgroundViewer_ = nullptr;
	Entity* player_ = nullptr;
	Entity* phone_=nullptr;
	Notes* notes_ = nullptr;
	Entity* apps_[8];
	Entity* fakeActor_=nullptr;
	Entity* UiDisplay= nullptr;
	//Esto deberia funcionar pero no lo hace
	//Entity* apps_[StateMachine::APPS::lastApps];

	Sprite* bgSprite_=nullptr;

	map<std::size_t, Actor*> actors_;
	vector<Door*> doors_;
	vector<Investigable*> investigables_;
	map<std::size_t, Clue*> clues_;
	map<std::size_t, CentralClue*> centralClues_;

	//Este vector guarda las escenes a las que el jugador puede acceder
	map<std::size_t, Scene*> scenes_;
	vector<Clue*> playerClues_;
	vector<CentralClue*> playerCentralClues_;

	map<std::size_t, Dialog*> dialogs_;
	//Este vector guarda las escenas a las que el jugador puede acceder
	vector<Scene*> availableScenes_;

	//Este vector guarda las timeline
	vector<vector<Resources::ClueID>> timelineSolutions_;

	vector <std::pair<Dialog*, std::function<void(DialogComponent*)>>> thoughts_;
	/*Creaci�n de entidades de manera chupiguay*/
	Entity* createPhone(EntityManager* EM, LoremIpsum* loremIpsum);
	Entity* createPlayer(EntityManager* EM, Phone* p);

	friend class DialogEditorState;
	friend class ClueCallbacks;		//puestos a hacer guarradas, por lo menos me hacen la vida mas facil

	int level = 0; //nivel para las barras de los fantasmas
	//COSAS PARA LA TIMELINE Y LOS EVENTOS
	int gameCase_ = 0;		//Este int indica en que caso del juego estamos, util para los escenarios y tal pero actualmente lo usamos solo para la TL.
	bool eventChanged = false; //bool para comunicarse entre el chinchetario y la timeline cuando un evento se ha modificado
	bool investigableChanged = false; //bool para comunicarse entre el chinchetario y los investigables cuando se recoge una pista
	void activateNotes();
public:
	const int LAZAROHEIGHT = 172;
	int PLAYABLEHIGHT=0;
#ifdef _DEBUG
	bool showingHitbox_ = false;
	bool chopMovement_ = false;
#endif // _DEBUG
};