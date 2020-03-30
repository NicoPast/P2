#pragma once
#include "Component.h"
#include "StoryManager.h"

#include <array>
#include <pair>
#include <string>

class Dialog : public Component
{
public:
	Dialog(size_t dialogs) : Component(ecs::Dialog), numOfDialogs_(dialogs)
	{
		dialogs_.reserve(numOfDialogs_);
	}

	virtual ~Dialog() {};

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	struct dialogLine
	{
		//El name es el nombre de la persona que dice la linea
		ActorID name_;

		//Esto puede ser un párrafo o una linea. Es lo que dice el actor
		string line_;
	};
	struct dialogOption
	{
		//callback mágico que no sabemos hacer
		void* callback_ = nullptr;

		//número de "dialogLines", mínimo 1 
		size_t lines_ = 1;

		//Esta es la conversación de la opción. un vector(de tamaño lines) de lineas que el jugador podrá leer
		vector<dialogLine> conversation_;

		//Cada conversación tendrá una línea de inicio. Estas lineas son las opciones que salen para el jugador hablar o interrogar y empezar la opción de dialogo.
		//Si el dialogo empieza con una de estas startLine puede estar vacío ("").
		string startLine_ = "";

		//Hay opciones que se desbloquearan en cierto punto de la historia. Esas deben tener 
		bool blocked_ = false;
	};
	//Cada componente de Dialogo tendrá asociado un Actor al cual hace referencia
	//Por ejemplo el Barman será el Actors::Barman
	ActorID actorName_;


	size_t getNumOfDialogs() { return numOfDialogs_; }

	inline const vector<dialogOption>& getOptions() {return dialogs_};
private:
	//Cada personaje tiene un número de dialogos definido
	size_t numOfDialogs_;

	//este vector de tamaño numOfDialogs guarda todo el dialogo que tiene el personaje
	vector<dialogOption> dialogs_;

};

//R: Hola Ana
//A: Hola Ricardo, qué tal?
//R: Bien y tú?
//A: Bien.
//R: ¿Ya hiciste la camara?
//R: ¿Qué tal la familia? -> Desbloquea pista (Llama a un callback)