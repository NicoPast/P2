#pragma once
#include "StoryManager.h"
#include "Resources.h"

class ClueCallbacks
{
public:
	static map<Resources::ClueID, std::function<void()>> clueCBs;

	//Estos callbacks se llamarán cuando cambie dicho evento en el chinchetario. El callback preguntará al story manager el estado de su evento y actuará acorde
	static map<Resources::ClueID, std::function<void()>> centralClueCBs;
};
