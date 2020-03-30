#pragma once
#include <string>
#include <vector>
#include <list>
#include "Entity.h"
#include "Texture.h"

class Interactable;
//Este enum se utilizar� para acceder a la pista con su identificador en el vector clues del Story Manager
enum ClueIDs
{
	Arma_Homicida, 
	Alfombra_Rota,
	Cuadro_De_Van_Damme,
	Retratrato_De_Dovahkiin,
	lastClueID
};

enum ClueType
{
	Object,
	Person,
	Place
};

struct Clue
{
	Clue(string title, string description, Texture* image, ClueType type = ClueType::Object) : title_(title), description_(description), image_(image), type_(type)
	{

	}
	std::string title_;
	std::string description_;
	ClueType type_;
	Texture* image_;
};

class CentralClue
{
	inline void addClue(size_t pos, Clue* clue) { clues[pos] = clue; };
	const vector<Clue*>& getClues() { return clues; };
private:
	size_t numOfClues;
	vector<Clue*> clues;
	vector<Clue*> correctClues;
};

enum SceneIDs
{
	Casa_Del_Profesor = 0,
	calleProfesor,
	lastSceneID
};

//Una escena es una zona jugable. Ya sea una habitaci�n o un conjunto de ellas, una casa entera...
struct Scene
{
	//este m�todo crear� una escena a partir de un archivo. Todas las entidades y el background.
	Scene(iostream file)
	{

	}
	~Scene()
	{

	}
	Scene() { entities.reserve(1), background = nullptr; };

	//Este vector guardar� todos los objetos, personajes, puertas, pistas...
	std::vector<Entity*> entities;

	//Cada escena tiene un fondo
	Texture* background=nullptr;
};

enum ActorID {
	Profesor,
	PoliceOfficer,
	Barman,
	lastActorID
};

class StoryManager
{
public:
	StoryManager(LoremIpsum* li, EntityManager* entityManager) : LoremIpsum_(li), entityManager_(entityManager) { init(); };
	~StoryManager() {};
	void init();

	inline const Scene* getCurrentScene() { return currentScene; };
	void changeScene(SceneIDs newScene);
	inline void addClue(SceneIDs id, Clue* clue) { if (clues[id] == nullptr) clues[id] = clue; };

	void setCurrentScene(Scene* newScene);
private:
	Scene* currentScene=nullptr;
	LoremIpsum* LoremIpsum_;
	EntityManager* entityManager_;
	Entity* BackgroundViewer_=nullptr;

	Entity* addEntity(int layer=0);

	//Todas las vistas disponibles en el juego.
	//Este vector se inicializa en el m�todo "init()" y tiene toda la informaci�n de las pistas.
	vector<Clue*> clues;

	//Este vector guarda las pistas que el jugador a recolectado
	vector<Clue*> playerClues;

	//Este vector guarda las escenes a las que el jugador puede acceder
	vector<Scene*> scenes;

	//Este vector guarda las pistas centrales que el jugador ha ido encontrando
	vector<CentralClue*> centralClues;



	/*Creaci�n de entidades de manera chupiguay*/
	Entity* createInteractable(EntityManager* EM, list<Interactable*>&interactables, int layer, Vector2D pos, int textSize, string name, const SDL_Color& color, Font* font, int w, int h);
	Entity* createPhone(EntityManager* EM, LoremIpsum* loremIpsum);
	Entity* createPlayer(EntityManager* EM);
};