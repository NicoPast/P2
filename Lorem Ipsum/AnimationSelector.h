#pragma once
#include "StoryManager.h"
#include "Resources.h"
#include "DialogSystem.h"
#include "DialogComponent.h"
#include "Animator.h"

class AnimationSelector
{
public:
	/*
	Estas funciones se encargaran de trabajar con el status del dialog component (Un bitset que muestra si has o no leido un dialogo)
	y su lista de dialogos, para mostrar unos u otros en el vector de dialogos disponibles.

	Por lo general usaremos cuales has leido, y cuales tienes desbloqueados para elegir unos u otros. Si quieres elegir uno en función de una pista
	puedes hacer que la pista en su callback active el dialogo y aquí definir en qué momento mostrar ese diálogo.

	*/
	static std::map<Resources::ActorID, std::function<void(Animator<int*>*)>> functions;
};