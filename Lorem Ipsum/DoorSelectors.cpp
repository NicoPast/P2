#pragma once
#include "DoorSelectors.h"
#include "StoryManager.h"
#include "Parallax.h"

std::map<Resources::DoorID, std::function<bool(Door*)>> DoorSelectors::functions_ =
{
	{
		//Solo un ejemplo para ver c�mo a�adir callbacks. 
		
		Resources::DoorID::pRecepcionDespacho, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			//sm->getBackgroundSprite()->getEntity()->getComponent<Parallax>(ecs::Parallax)->setPlayer(sm->getPlayer()->getComponent<Transform>(ecs::Transform));
			sm->addPlayerClue(Resources::Tut_Cent_DesordenHabitacion);
			sm->thinkOutLoud({ "OH! �Qu� este desastre!?, voy a buscar pistas", "Con la tecla E puedo interactuar con ellas." });
			return false;
		}
	},

	{
		Resources::DoorID::pDespachoRecpecion, [](Door* d)
		{


			return false;
		}
	},

	{
		Resources::DoorID::pEntradaBosque, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();

			sm->thinkOutLoud({ "Deber�a hablar con la familia antes de investigar en otros sitios." });
			return false;
		}
	},

	{
		Resources::DoorID::pEntradaCaseta, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();

			sm->thinkOutLoud({ "Deber�a hablar con la familia antes de investigar en otros sitios." });
			return 	sm->getDoor(Resources::DoorID::pEntradaCaseta)->isLocked();
		}
	},

	{
		Resources::DoorID::pBosqueEntrada, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();

			sm->getDoor(Resources::DoorID::pEntradaCaseta)->setLocked(false);
			return false;
		}
	},


	{
		Resources::DoorID::pSalonEntrada, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();

			sm->thinkOutLoud({ "Es una casa preciosa, pero el jard�n est� hecho una mierda. Me pregunto por qu� no contratan a alguien que lo cuide." });
			sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 1;
			return false;
		}
	},

};