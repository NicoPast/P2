#include "StoryManager.h"

void StoryManager::init()
{
	//Creación de pistas
	clues.reserve(ClueIDs::lastClueID);
	clues[ClueIDs::Arma_Homicida] = 
	{ "Arma Homicida",
	"Un cuchillo ensangrentado con un adorno en la empuñadura", 
	LoremIpsum_->getGame()->getTextureManager()->getTexture(Resources::Blank)};

	clues[ClueIDs::Alfombra_Rota] =
	{ "Alfombra Rota",
	"Una pieza de tela que formaba parte de una alfombra en la cocina del profesor.",
	LoremIpsum_->getGame()->getTextureManager()->getTexture(Resources::Blank) };

	clues[ClueIDs::Cuadro_De_Van_Damme] = {
	"Cuadro de Van Damme",
	"Un cuadro de Van Damme con una firma. MB",
	LoremIpsum_->getGame()->getTextureManager()->getTexture(Resources::Blank) };

	clues[ClueIDs::Retratrato_De_Dovahkiin] = {
	"Retrato de Dovahkiin",
	"El mejor juego de la historia",
	LoremIpsum_->getGame()->getTextureManager()->getTexture(Resources::Blank) };


	//Creación de escenas
	scenes.reserve(lastSceneID);
	Entity* profesor = LoremIpsum_->getGame()->getCurrentState()->getEntityManager()->addEntity();
	//profesor->addComponent<>()
	Scene casaDelProfesor =
	{
		//entities.
	};
	scenes[Casa_Del_Profesor] = casaDelProfesor;

}