#pragma once
#include "DoorSelectors.h"
#include "StoryManager.h"

std::map<Resources::DoorID, std::function<bool(Door*)>> DoorSelectors::functions_ =
{
	//{
	//	//Solo un ejemplo para ver cómo añadir callbacks. 
	//	
	//	Resources::DoorID::pRecepcionDespacho, [](Door* d)
	//	{
	//		StoryManager* sm = StoryManager::instance();

	//		Transform* tr = sm->getPlayer()->getComponent<Transform>(ecs::Transform);
	//		tr->setW(2*tr->getW());
	//		tr->setH(2 * tr->getH());


	//		return false;
	//	}
	//},

	//{
	//	Resources::DoorID::pDespachoRecpecion, [](Door* d)
	//	{

	//		StoryManager* sm = StoryManager::instance();
	//		Transform* tr = sm->getPlayer()->getComponent<Transform>(ecs::Transform);
	//		tr->setW(tr->getW()/2);
	//		tr->setH(tr->getH()/2);

	//		return false;
	//	}
	//}
};