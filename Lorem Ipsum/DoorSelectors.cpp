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
			return 	sm->getDoor(Resources::DoorID::pEntradaCaseta)->isLocked(); //s�, lo he cerrado porque soy imbecil y no vamos a poder probarlo
		}
	},

	{
		Resources::DoorID::pBosqueEntrada, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();
			//esto es lo que quiero hacer
			//no. quiero que al ir desde el bosque a la entrada de la mansi�n, se desbloquee la puerta para ir a la caseta del jard�n
			//pEntradaCaseta->locked = false;
			sm->getDoor(Resources::DoorID::pEntradaCaseta)->setLocked(false);
			return false;
		}
	},

};