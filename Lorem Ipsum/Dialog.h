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

	//Cada componente de Dialogo tendr� asociado un Actor al cual hace referencia
	//Por ejemplo el Barman ser� el Actors::Barman
	Actors actorName;

	//Cada personaje tiene un n�mero de dialogos definido
	size_t numOfDialogs;
	

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	struct dialogLine
	{
		//El name es el nombre de la persona que dice la linea
		Actors name;

		//Esto puede ser un p�rrafo o una linea. Es lo que dice el actor
		string line;
	};



	struct dialogOption
	{
		//callback m�gico que no sabemos hacer
		void* callback = nullptr;

		//n�mero de "dialogLines", m�nimo 1 
		size_t lines = 1;

		//Esta es la conversaci�n de la opci�n. un array de lineas que el jugador podr� leer
		array<dialogLine, lines> conversation;

		//Cada conversaci�n tendr� una l�nea de inicio. Estas lineas son las opciones que salen para el jugador hablar o interrogar y empezar la opci�n de dialogo.
		//Si el dialogo empieza con una de estas startLine puede estar vac�o ("").
		string startLine = "";

		//Hay opciones que se desbloquearan en cierto punto de la historia. Esas deben tener 
		bool blocked = false;
	};


	//R: Hola Ana
	//A: Hola Ricardo, qu� tal?
	//R: Bien y t�?
	//A: Bien.
	//R: �Ya hiciste la camara?
	//R: �Qu� tal la familia? -> Desbloquea pista (Llama a un callback)
	//R: �Pa cuando vienes pa las Ca�adas del Teide?
	array<dialogOption, numOfDialogs> Dialogs;


};