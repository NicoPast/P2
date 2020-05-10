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
class Pin;
class Sprite;
class Interactable;
class StoryManager;
class Phone;
class Clue
{
public:
	Clue(Resources::ClueInfo info);
	~Clue() {};
	std::string title_;
	std::string description_;
	std::string eventText_;
	Resources::ClueType type_;
	Resources::ClueIDs id_;
	//TextureId image_;
	bool placed_ = false;					//true = chinchetario
	Entity* entity_ = nullptr;
};
class CentralClue : public Clue
{
public:
	CentralClue(Resources::CentralClueInfo info) : Clue(info), links_(info.links_), eventDescription_(info.eventDescription_), timeline_(info.timeline_){};
	~CentralClue() {};
	vector<Resources::ClueIDs> links_;
	std::string eventDescription_;
	std::string actualDescription_ = "";
	bool event_ = false;
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
	Scene(Texture* t) { background = t; };										//Creo que hay que matarlo
	Scene(Texture* t, Texture* t2) { background = t; ghBackground = t2; };
	Scene(Texture* t, Resources::SceneID s) { background = t; scene = s; };		//Creo que hay que matarlo
	Scene(Texture* t, Resources::SceneID s, Texture* t2) { background = t; scene = s; ghBackground = t2; };
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
	Resources::SceneID scene = Resources::SceneID::lastSceneID; //Lo inicializo a LastSceneID pero en la constructora se van a�adiendo
};


class Actor
{
public:
	Actor(StoryManager* sm, Resources::ActorInfo info, Resources::SceneID currentScene) : Actor(sm, info, {1000,250 },20,20,currentScene) {}
	Actor(StoryManager* sm, Resources::ActorInfo info, Vector2D pos, int w, int h, Resources::SceneID currentScene);
	~Actor() {};
	inline std::string getName() { return name_; };
	inline Texture* getSprite() { return sprite_; };
	Resources::ActorID getId() { return id_; };
	Entity* getEntity() {return entity_;}
private:
	Resources::ActorID id_;
	string name_;
	Scene* currentScene_;
	Texture* sprite_;
	Resources::AnimID portrait_;
	Entity* entity_;
};

class StoryManager
{
public:
	StoryManager(LoremIpsum* li, EntityManager* entityManager) : LoremIpsum_(li), entityManager_(entityManager) { init(); };
	virtual ~StoryManager();
	void init();

	//============================================================================================================================

	inline const Scene* getCurrentScene() { return currentScene; };
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
	inline void addPlayerClue(Resources::ClueIDs id) { if (clues_[id] != nullptr) playerClues_.push_back(clues_[id]); }
	inline const vector<CentralClue*> getPlayerCentralClues() { return playerCentralClues_; };

	//============================================================================================================================

	Entity* addEntity(int layer = 0);
	Entity* getPlayer() { return player_; };
	Entity* getDialogBox() { return dialogBox_; };
	Sprite* getBackgroundSprite() { return bgSprite_; };

	//============================================================================================================================

	Dialog* getDialog(size_t id) { return dialogs_[id]; };
	Text* getDialogBoxText() { return dialogBoxText_; };
	Text* getDialogBoxActorName() { return dialogBoxActorName_; };

	vector<Scene*> getAvailableScenes() { return availableScenes_; }

	list<Interactable*> interactables_;

	vector<Entity*> createBars(EntityManager* EM);
	string getActorName(Resources::ActorID id) { string lazaro("Lazaro"); return (id == -1) ? lazaro : actors_[id]->getName(); }
private:
	Scene* currentScene=nullptr;
	Scene* prevSceneGh = nullptr;	//estado escena anterior (para no cortar la musica)
	LoremIpsum* LoremIpsum_;
	EntityManager* entityManager_;
	Entity* dialogBox_= nullptr;
	Text* dialogBoxActorName_ = nullptr;
	Text* dialogBoxText_ = nullptr;
	Entity* backgroundViewer_ = nullptr;
	Entity* player_ = nullptr;
	Entity* phone_=nullptr;

	Sprite* bgSprite_=nullptr;


	map<std::size_t, Actor*> actors_;
	map<std::size_t, Clue*> clues_;
	map<std::size_t, CentralClue*> centralClues_;

	//Este vector guarda las escenes a las que el jugador puede acceder
	map<std::size_t, Scene*> scenes_;
	vector<Clue*> playerClues_;
	vector<CentralClue*> playerCentralClues_;

	map<std::size_t, Dialog*> dialogs_;
	//Este vector guarda las escenas a las que el jugador puede acceder
	vector<Scene*> availableScenes_;

	//Este vector guarda las pistas centrales que el jugador ha ido encontrando
	//vector<CentralClue*> centralClues_;



	/*Creaci�n de entidades de manera chupiguay*/
	Entity* createInteractable(EntityManager* EM, list<Interactable*>&interactables, int layer, Vector2D pos, int textSize, string name, const SDL_Color& color, Resources::FontId font, int w, int h);
	Entity* createPhone(EntityManager* EM, LoremIpsum* loremIpsum);
	Entity* createPlayer(EntityManager* EM, Phone* p);

	friend class DialogEditorState;

	int level = 0; //nivel para las barras de los fantasmas
	vector<Entity*> bars_;
};