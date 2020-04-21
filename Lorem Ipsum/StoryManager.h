#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include "Entity.h"
#include "Texture.h"
#include "Bar.h"
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
//class CentralClue
//{
//	inline void addClue(size_t pos, Clue* clue) { clues[pos] = clue; };
//	const vector<Clue*>& getClues() { return clues; };
//private:
//	size_t numOfClues;
//	vector<Clue*> clues;
//	vector<Clue*> correctClues;
//};


//Una escena es una zona jugable. Ya sea una habitación o un conjunto de ellas, una casa entera...
struct Scene
{
	Scene() { background = nullptr; };
	Scene(Texture* t) { background = t; };
	~Scene() {};
	//Este vector guardará todos los objetos, personajes, puertas, pistas...
	std::vector<Entity*> entities;
	//Cada escena tiene un fondo
	Texture* background=nullptr;
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
	void changeScene(Resources::SceneID newScene);


	inline void addPlayerClue(Resources::ClueIDs id) { if (clues_[id] != nullptr) playerClues_.push_back(clues_[id]); }

	inline const vector<Clue*> getPlayerClues() { return playerClues_; };

	Scene* getScene(Resources::SceneID id) { return scenes_[id]; };

	Entity* addEntity(int layer = 0);

	Sprite* getBackgroundSprite() { return bgSprite_; };

	list<Interactable*> interactables_;

	vector<Entity*> createBars();

private:
	Scene* currentScene=nullptr;
	LoremIpsum* LoremIpsum_;
	EntityManager* entityManager_;
	Entity* backgroundViewer_ = nullptr;
	Entity* player_ = nullptr;
	Entity* phone_=nullptr;

	Sprite* bgSprite_=nullptr;


	map<std::size_t, Actor*> actors_;
	//Todas las pistas disponibles en el juego.
	//Este vector se inicializa en el método "init()" y tiene toda la información de las pistas.
	map<std::size_t, Clue*> clues_;

	//Este vector guarda las escenes a las que el jugador puede acceder
	map<std::size_t, Scene*> scenes_;

	//Este vector guarda las pistas que el jugador a recolectado
	vector<Clue*> playerClues_;

	//Este vector guarda las pistas centrales que el jugador ha ido encontrando
	//vector<CentralClue*> centralClues_;



	/*Creación de entidades de manera chupiguay*/
	Entity* createInteractable(EntityManager* EM, list<Interactable*>&interactables, int layer, Vector2D pos, int textSize, string name, const SDL_Color& color, Resources::FontId font, int w, int h);
	Entity* createPhone(EntityManager* EM, LoremIpsum* loremIpsum);
	Entity* createPlayer(EntityManager* EM, Phone* p);

	int level = 0; //nivel para las barras de los fantasmas
	vector<Entity*> bars_;
};