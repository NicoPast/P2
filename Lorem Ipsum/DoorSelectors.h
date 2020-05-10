#pragma once
#include "Resources.h"
#include <functional>

class Door;

class DoorSelectors
{
public:

	static std::map<Resources::DoorID, std::function<bool(Door*)>> functions_;
};