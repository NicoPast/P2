#pragma once
#include "StoryManager.h"
#include "Resources.h"
#include "DialogSystem.h"
#include "DialogComponent.h"

class DialogSelectors
{
public:
	/*
	Estas funciones se encargaran de trabajar con el status del dialog component (Un bitset que muestra si has o no leido un dialogo)
	y su lista de dialogos, para mostrar unos u otros en el vector de dialogos disponibles.

	Por lo general usaremos cuales has leido, y cuales tienes desbloqueados para elegir unos u otros. Si quieres elegir uno en funci�n de una pista
	puedes hacer que la pista en su callback active el dialogo y aqu� definir en qu� momento mostrar ese di�logo.

	*/
	static std::map<Resources::ActorID, std::function<void(DialogComponent*)>> functions;

	static void BosqueCaseta(DialogComponent* d);
	static void MuerteAfur(DialogComponent* d);
};