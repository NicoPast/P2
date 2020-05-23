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
	},
	{
		Resources::ClueID::Prin_BalaCasquillo, []()
		{
			//	StoryManager* sm = StoryManager::instance();
			//	auto clues = sm->getClues();
			//	if (sm->hasClue(clues[Resources::ClueID::Prin_BalaSinSangre]))
			//	{
			//		string palCallback = "Parece que este lugar está bastante relacionado con la muerte. Es el momento de probar esa nueva aplicación que me hizo el profesor León en mi marcapasos.";
			//		DialogComponent* dcComics = sm->dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent);
			//		//dcComics->setCallback([palCallback](DialogComponent* dc) {StoryManager::instance()->thinkOutLoud({ palCallback }); }, 0, 0, 0);
			//		dcComics->getDialog(0)->options_[0].lines_.push_back(DialogLine(0, palCallback));
			//	}
		}

	},
	{
		Resources::ClueID::Prin_PanueloRojo, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_PistolaSilenciador]))
			{
				string parte1 = "(¿¿Y esos gritos??)";
				DialogComponent* dcComics = sm->dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent);
				dcComics->getDialog(0)->options_[0].lines_.push_back(DialogLine(0, parte1));
				parte1 = "(¿Qué coño habrá pasado?)";
				dcComics->getDialog(0)->options_[0].lines_.push_back(DialogLine(0, parte1));
				//aqui hay un animatic precioson seguido de más ThinkOutLoud
				//Ricky
			}
		}

	},
	{
		Resources::ClueID::Prin_PistolaSilenciador, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_PanueloRojo]))
			{
				string parte1 = "(¿¿Y esos gritos??)";
				DialogComponent* dcComics = sm->dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent);
				dcComics->getDialog(0)->options_[0].lines_.push_back(DialogLine(0, parte1));
				parte1 = "(¿Qué coño habrá pasado?)";
				dcComics->getDialog(0)->options_[0].lines_.push_back(DialogLine(0, parte1));
				//aqui hay un animatic precioson seguido de más ThinkOutLoud
				//Ricky
				
				//para que pueda hablar del incidente de anoche
				sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 1;
			}
		}

	},
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
			LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("¡Gracias por jugar a la demo!");
		}
	}
};