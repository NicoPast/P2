#include "StoryManager.h"
#include "Dialog.h"
#include "LoremIpsum.h"
#include "SDLGame.h"

void StoryManager::init()
{
	//Creación de pistas
	clues.resize(ClueIDs::lastClueID);

	clues[ClueIDs::Arma_Homicida] = 
		new Clue(string("Arma Homicida"), 
			string("Un cuchillo ensangrentado con un adorno en la empuñadura"),
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	clues[ClueIDs::Alfombra_Rota] =
		new Clue("Alfombra Rota",
			"Una pieza de tela que formaba parte de una alfombra en la cocina del profesor.",
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	clues[ClueIDs::Cuadro_De_Van_Damme] =
		new Clue("Cuadro de Van Damme",
			"Un cuadro de Van Damme con una firma. MB",
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	clues[ClueIDs::Retratrato_De_Dovahkiin] =
		new Clue("Retrato de Dovahkiin",
			"El mejor juego de la historia",
			LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::Blank));

	
	//Creación de escenas
	scenes.resize(lastSceneID);
	Entity* profesor = entityManager_->addEntity(4);
	
	Vector2D p = { 200, 0 };
	Text* texto = profesor->addComponent<Text>("ESTOY AQUI", p, 600, LoremIpsum_->getGame()->getFontMngr()->getFont(Resources::ARIAL16), 0);
	texto->addSoundFX(Resources::Bip);
	texto->addSoundFX(Resources::Paddle_Hit);
	Dialog* profesorDialog = profesor->addComponent<Dialog>(ActorID::Profesor, texto,1);

	Dialog::dialogOption profesorOption1;
	Dialog::dialogLine line;
	line.line_ = "Wow, esto es mucho código";
	line.name_ = ActorID::Profesor;
	profesorOption1.conversation_[0]=line;

	profesorDialog->getOptions().push_back(profesorOption1);
	
	Scene* casaDelProfesor = new Scene();
	casaDelProfesor->background = LoremIpsum_->getGame()->getTextureMngr()->getTexture(Resources::BlackHole);
	casaDelProfesor->entities.push_back(profesor);
	scenes[Casa_Del_Profesor] = casaDelProfesor;

	profesor->setActive(false);

	setCurrentScene(casaDelProfesor);
	//profesorDialog->interact();
}

void StoryManager::setCurrentScene(Scene* newScene)
{
	if (currentScene!=nullptr)
	{
		for (Entity* e : currentScene->entities)
		{
			e->setActive(false);
		}
	}
	currentScene = newScene;
	for (Entity* e : currentScene->entities)
	{
		e->setActive(true);
	}
}