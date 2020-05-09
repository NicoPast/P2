#pragma once
#include "DoorSelectors.h"
#include "StoryManager.h"

std::map<Resources::DoorID, std::function<bool(Door*)>> DoorSelectors::functions_ =
{
	{
		//Solo un ejemplo para ver cómo añadir callbacks. 
		/*
		Resources::DoorID::pDespachoRecpecion, [](Door* d)
		{
			StoryManager* sm = StoryManager::instance();

			if (d->isLocked())
				sm->thinkOutLoud("Necesito una llave");
			else
				sm->thinkOutLoud("Pos tenía llave");

			return d->isLocked();
		}
		/**/
	}
};