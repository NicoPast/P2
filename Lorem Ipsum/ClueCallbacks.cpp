#include "ClueCallbacks.h"
#include "LoremIpsum.h"

map<Resources::ClueID, std::function<void()>> ClueCallbacks::clueCBs =
{
	{
		Resources::ClueID::Tut_SillaRota, []()
		{
			StoryManager* sm =  StoryManager::instance();
			//LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("DAMN, short message");

		}
	},
	{
		Resources::ClueID::Tut_PapelesDesordenados, []()
		{
			StoryManager* sm =  StoryManager::instance();
			//LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("Has completado una pista. Esto es un texto muy largo para ver como se comporta en el texto para el pop up. Por ahroa solo funciona en un estado, y eso me ahce sad. Pero podemos, en teoría hacer que distinga entre estados y que pueda usar uno similar en el mapa, chinchetario... :D");
		}
	}
};


map<Resources::ClueID, std::function<void()>> ClueCallbacks::centralClueCBs =
{
	//si hay dudas sobre el orden en el que se guardan los dialogos revise la carpeta Assets/Dialogs/Actors
	//si hay más dudas vea el comentario de dialogSelector.cpp
	{	Resources::ClueID::Tut_Cent_DesordenHabitacion, []()
		{
			Resources::ClueID id = Resources::ClueID::Tut_Cent_DesordenHabitacion;
			StoryManager* sm = StoryManager::instance();
			Entity* macarena = sm->getActors()[Resources::ActorID::MacarenaMartinez]->getEntity();
			DialogComponent* macarenaDialg = GETCMP2(macarena, DialogComponent);

			if (sm->getCentralClues()[id]->isEvent_)
			{
				if (sm->getCentralClues()[id]->isCorrect_)
				{

					macarenaDialg->setDialogActive(3, true);
					macarenaDialg->setDialogActive(2, false);
				}
				else if (!sm->getCentralClues()[id]->isCorrect_)
				{
					macarenaDialg->setDialogActive(3, false);
					macarenaDialg->setDialogActive(2, true);
				}
			}
			else
			{
				macarenaDialg->setDialogActive(3, false);
				macarenaDialg->setDialogActive(2, false);
			}

		}},
	{
		Resources::ClueID::Tut_Cent_MotivoEntrada, []() 
		{
			StoryManager* sm = StoryManager::instance();
			Entity* macarena = sm->getActors()[Resources::ActorID::MacarenaMartinez]->getEntity();
			DialogComponent* macarenaDialg = GETCMP2(macarena, DialogComponent);
			//Este evento si se forma siempre está bien, no hace falta comprobar con el storymanager nada
			macarenaDialg->setDialogActive(4, sm->getCentralClues()[Resources::ClueID::Tut_Cent_MotivoEntrada]->isEvent_);
			sm->addAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo));
			LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("¡Gracias por jugar a la demo!");
		}
	}
};