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
			sm->thinkOutLoud({ "OH! ¿Qué este desastre!?, voy a buscar pistas", "Con la tecla E puedo interactuar con ellas" });
			return false;
		}
	},

	{
		Resources::DoorID::pDespachoRecpecion, [](Door* d)
		{


			return false;
		}
	}
};