#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include "Entity.h"
#include "Texture.h"
#include "DialogComponent.h"
#include "DialogSystem.h"

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
	Resources::ClueType type_;
	Resources::ClueIDs id_;
	//TextureId image_;
	bool placed_ = false;
	Entity* entity_ = nullptr;
};


//Una escena es una zona jugable. Ya sea una habitación o un conjunto de ellas, una casa entera...
struct Scene
{
	Scene() { background = nullptr; };
	Scene(Texture* t) { background = t; };
	Scene(Texture* t, Resources::SceneID s) { background = t; scene = s; };
	~Scene() {};
	//Este vector guardará todos los objetos, personajes, puertas, pistas...
	std::vector<Entity*> entities;
	//Cada escena tiene un fondo
	Texture* background=nullptr;
	Texture* mapIcon = nullptr;
	Vector2D mapPos = { 0,0 }; //posición que ocupará en el mapa. Esto habrá que modificarlo en archivos o en Tiled o algo para no ponerlo a pelo en el código
	Resources::SceneID scene = Resources::SceneID::lastSceneID; //Lo inicializo a LastSceneID pero en la constructora se van añadiendo
};


class Actor
{
public:
	Actor(StoryManager* sm, Resources::ActorInfo info, Resources::SceneID currentScene) : Actor(sm, info, {1000,250 },20,20,currentScene) {}
	Actor(StoryManager* sm, Resources::ActorInfo info, Vector2D pos, int w, int h, Resources::SceneID currentScene);
	~Actor() {};

	inline std::string getName() { return name_; };
	inline Texture* getPortrait() { return portrait_; };
	inline Texture* getSprite() { return sprite_; };
	Resources::ActorID getId() { return id_; };
	Entity* getEntity() {return entity_;}
private:
	Resources::ActorID id_;
	string name_;
	Scene* currentScene_;
	Texture* sprite_;
	Texture* portrait_;
	Entity* entity_;
};

class StoryManager
{
public:
	StoryManager(LoremIpsum* li, EntityManager* entityManager) : LoremIpsum_(li), entityManager_(entityManager) { init(); };
	virtual ~StoryManager();
	void init();

	inline const Scene* getCurrentScene() { return currentScene; };
	Scene* getScene(Resources::SceneID id) { return scenes_[id]; };
	void changeScene(Resources::SceneID newScene);

	inline const vector<Clue*> getPlayerClues() { return playerClues_; };
	inline void addPlayerClue(Resources::ClueIDs id) { if (clues_[id] != nullptr) playerClues_.push_back(clues_[id]); }

	Entity* addEntity(int layer = 0);
	Entity* getPlayer() { return player_; };
	Entity* getDialogBox() { return dialogBox_; };
	Sprite* getBackgroundSprite() { return bgSprite_; };

	Dialog* getDialog(string n) { return &dialogs_[n]; };
	Text* getDialogBoxText() { return dialogBoxText_; };
	Text* getDialogBoxActorName() { return dialogBoxActorName_; };

	vector<Scene*> getAvailableScenes() { return availableScenes_; }

	list<Interactable*> interactables_;
private:
	Scene* currentScene=nullptr;
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
	map<std::size_t, Scene*> scenes_;
	vector<Clue*> playerClues_;

	map<string, Dialog> dialogs_;
	//Este vector guarda las escenas a las que el jugador puede acceder
	vector<Scene*> availableScenes_;

	//Este vector guarda las pistas centrales que el jugador ha ido encontrando
	//vector<CentralClue*> centralClues_;



	/*Creación de entidades de manera chupiguay*/
	Entity* createInteractable(EntityManager* EM, list<Interactable*>&interactables, int layer, Vector2D pos, int textSize, string name, const SDL_Color& color, Resources::FontId font, int w, int h);
	Entity* createPhone(EntityManager* EM, LoremIpsum* loremIpsum);
	Entity* createPlayer(EntityManager* EM, Phone* p);

	friend class DialogEditorState;
};