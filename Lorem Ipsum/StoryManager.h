#pragma once
#include <string>
#include <vector>
#include <map>
#include "Entity.h"
#include "Texture.h"
//Este enum se utilizará para acceder a la pista con su identificador en el vector clues del Story Manager
enum ClueIDs
{
	Arma_Homicida, 
	Alfombra_Rota,
	Cuadro_De_Van_Damme,
	Retratrato_De_Dovahkiin,
	lastClueID
};

struct Clue
{
	std::string title;
	std::string description;
	Texture* image;
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
	Casa_Del_Profesor=0,
	lastSceneID
};

//Una escena es una zona jugable. Ya sea una habitación o un conjunto de ellas, una casa entera...
struct Scene
{
	//este método creará una escena a partir de un archivo. Todas las entidades y el background.
	Scene(iostream file)
	{

	}
	~Scene()
	{

	}
	//Este vector guardará todos los objetos, personajes, puertas, pistas...
	std::vector<Entity*> entities;

	//Cada escena tiene un fondo
	Texture* background;
};

enum Actors {
	Profesor,
	PoliceOfficer,
	Barman,
	lastActorID
}

class StoryManager
{
public:
	StoryManager(LoremIpsum* li) : LoremIpsum_(li) { init(); };
	~StoryManager() {};
	void init();


	inline void changeScene(string id) { currentScene = scenes[id]; }
	inline void addClue(int id, Clue* clue) { if (clues[id] == nullptr)clues[id] = clue; };


private:
	Scene* currentScene;
	LoremIpsum* LoremIpsum_;


	//Todas las vistas disponibles en el juego.
	//Este vector se inicializa en el método "init()" y tiene toda la información de las pistas.
	vector<Clue> clues;

	//Este vector guarda las pistas que el jugador a recolectado
	vector<Clue*> playerClues;

	//Este vector guarda las escenes a las que el jugador puede acceder
	vector<Scene*> scenes;

	//Este vector guarda las pistas centrales que el jugador ha ido encontrando
	vector<CentralClue*> centralClues;
};