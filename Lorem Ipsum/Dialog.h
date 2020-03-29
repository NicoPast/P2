#pragma once
#include "Component.h"
#include "StoryManager.h"

#include <array>
#include <pair>
#include <string>

class Dialog : public Component
{
	Dialog() : Component(ecs::Dialog) {}
	virtual ~Dialog() {};

	//Cada componente de Dialogo tendrá asociado un Actor al cual hace referencia
	//Por ejemplo el Barman será el Actors::Barman
	Actors actorName;

	//Cada personaje tiene un número de dialogos definido
	size_t numOfDialogs;
	

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	struct dialogLine
	{
		//El name es el nombre de la persona que dice la linea
		Actors name;

		//Esto puede ser un párrafo o una linea. Es lo que dice el actor
		string line;
	};



	struct dialogOption
	{
		//callback mágico que no sabemos hacer
		void* callback = nullptr;

		//número de "dialogLines", mínimo 1 
		size_t lines = 1;

		//Esta es la conversación de la opción. un array de lineas que el jugador podrá leer
		array<dialogLine, lines> conversation;

		//Cada conversación tendrá una línea de inicio. Estas lineas son las opciones que salen para el jugador hablar o interrogar y empezar la opción de dialogo.
		//Si el dialogo empieza con una de estas startLine puede estar vacío ("").
		string startLine = "";

		//Hay opciones que se desbloquearan en cierto punto de la historia. Esas deben tener 
		bool blocked = false;
	};


	//R: Hola Ana
	//A: Hola Ricardo, qué tal?
	//R: Bien y tú?
	//A: Bien.
	//R: ¿Ya hiciste la camara?
	//R: ¿Qué tal la familia? -> Desbloquea pista (Llama a un callback)
	//R: ¿Pa cuando vienes pa las Cañadas del Teide?
	array<dialogOption, numOfDialogs> Dialogs;


};