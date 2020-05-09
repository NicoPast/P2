#pragma once
#include "StoryManager.h"
#include "Resources.h"

class ClueCallbacks
{
public:
	static map<Resources::ClueID, std::function<void()>> clueCBs;

	//Estos callbacks se llamar�n cuando cambie dicho evento en el chinchetario. El callback preguntar� al story manager el estado de su evento y actuar� acorde
	static map<Resources::ClueID, std::function<void()>> centralClueCBs;
};
