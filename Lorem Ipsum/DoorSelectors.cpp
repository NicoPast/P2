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
			sm->addPlayerClue(Resources::Tut_Cent_DesordenHabitacion);
			if (sm->getGameCase() == 0)
			{
				sm->thinkOutLoud({ "OH! ¿Qué este desastre!?, voy a buscar pistas", "Con la tecla E puedo interactuar con ellas." });
			}
			return false;
		}
	},

	{
		Resources::DoorID::pEntradaBosque, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			
			if (sm->getActor(Resources::Capo))
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
				return false;
			}
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


				//asi puedes moverte entre el despacho y la casa de los Polo
				sm->addAvailableScene(sm->getScene(Resources::SceneID::JardinEntrada));
				sm->removeAvailableScene(sm->getScene(Resources::SceneID::EntradaDespacho));

				//esta línea debería activar este diálogo
				data = 1;
			}
			return false;
		}
	},

	{
		Resources::DoorID::pPasilloSabrina, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			Clue* clue = clues[Resources::ClueID::Prin_Llave];


			return !(sm->hasClue(clue) && sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] >= 5);
		}
	},

};