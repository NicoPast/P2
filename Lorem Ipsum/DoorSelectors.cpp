#pragma once
#include "DoorSelectors.h"
#include "StoryManager.h"
#include "Parallax.h"

std::map<Resources::DoorID, std::function<bool(Door*)>> DoorSelectors::functions_ =
{
	{
		//Solo un ejemplo para ver cómo añadir callbacks. 
		
		Resources::DoorID::pRecepcionDespacho, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			//sm->getBackgroundSprite()->getEntity()->getComponent<Parallax>(ecs::Parallax)->setPlayer(sm->getPlayer()->getComponent<Transform>(ecs::Transform));
			if (sm->getGameCase() == 0)
			{
				sm->addPlayerClue(Resources::Tut_Cent_DesordenHabitacion);
				sm->thinkOutLoud({"¡OH! ¿¡Qué es este desastre!? Voy a buscar pistas."});
			}
			return false;
		}
	},

	{
		Resources::DoorID::pEntradaBosque, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			
			if (sm->getDoor(Resources::DoorID::pEntradaBosque)->isLocked())
			{
				sm->thinkOutLoud({ "Debería hablar con la familia antes de investigar en otros sitios." });
				return true;
			}
			return 	false;
		}
	},

	{
		Resources::DoorID::pEntradaCaseta, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			if (sm->getDoor(Resources::DoorID::pEntradaCaseta)->isLocked())
			{
				sm->thinkOutLoud({ "Debería hablar con la familia antes de investigar en otros sitios." });
				return true;
			}
			sm->addPlayerClue(Resources::ClueID::Prin_CasetaJardin);
			return 	false;
		}
	},

	{
		Resources::DoorID::pSalonEntrada, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();

			int& data = sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];
			if (data < 1)
			{
				sm->thinkOutLoud({ "Es una casa preciosa, pero el jardín está hecho una mierda. Me pregunto por qué no contratan a alguien que lo cuide." });

				sm->addPlayerClue(Resources::ClueID::Prin_Jardin);

				//asi puedes moverte entre el despacho y la casa de los Polo
				sm->addAvailableScene(sm->getScene(Resources::SceneID::JardinEntrada));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::Despacho));
				sm->removeAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo));
				//esta línea debería activar este diálogo
				data = 1;

			}
			return false;
		}
	},
	{
		Resources::DoorID::pPasilloAfur, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			sm->addPlayerClue(Resources::ClueID::Prin_HabAfur);
			return false;
		}
	},
	{
	Resources::DoorID::pPasilloCapo, [](Door* d)
	{
		StoryManager* sm = StoryManager::instance();
		sm->addPlayerClue(Resources::ClueID::Prin_HabErnesto);
		return false;
	}
	},
		{
	Resources::DoorID::pPasilloEntrada, [](Door* d)
	{
		StoryManager* sm = StoryManager::instance();
		sm->addPlayerClue(Resources::ClueID::Prin_Salon);
		return false;
	}
	},
	{
	Resources::DoorID::pPasilloCarlos, [](Door* d)
	{
		StoryManager* sm = StoryManager::instance();
		sm->addPlayerClue(Resources::ClueID::Prin_HabUrsulaCarlos);
		return false;
	}
	},
	{
		Resources::DoorID::pPasilloSabrina, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			Clue* clue = clues[Resources::ClueID::Prin_Llave];
			sm->addPlayerClue(Resources::ClueID::Prin_HabSabrina);


			return !(sm->hasClue(clue) && sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] >= 5);
		}
	},

};