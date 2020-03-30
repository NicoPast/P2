#pragma once
#include "Component.h"
#include "StoryManager.h"

#include <array>
#include <string>
#include "Text.h"

class Dialog : public Component
{
public:
	Dialog(ActorID name, Text* textComponent, size_t dialogs =1) : Component(ecs::Dialog), numOfDialogs_(dialogs)
	{
		dialogs_.reserve(numOfDialogs_);
		actorName_ = name;
		textComponent_ = textComponent;
	}

	virtual ~Dialog() {};

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	struct dialogLine
	{
		//El name es el nombre de la persona que dice la linea
		ActorID name_;

		//Esto puede ser un p�rrafo o una linea. Es lo que dice el actor
		string line_;
	};
	struct dialogOption
	{
		dialogOption() { conversation_.resize(1);}
		//callback m�gico que no sabemos hacer
		void* callback_ = nullptr;

		//n�mero de "dialogLines", m�nimo 1 
		size_t lines_ = 1;

		//Esta es la conversaci�n de la opci�n. un vector(de tama�o lines) de lineas que el jugador podr� leer
		vector<dialogLine> conversation_;

		//Cada conversaci�n tendr� una l�nea de inicio. Estas lineas son las opciones que salen para el jugador hablar o interrogar y empezar la opci�n de dialogo.
		//Si el dialogo empieza con una de estas startLine puede estar vac�o ("").
		string startLine_ = "";

		//Hay opciones que se desbloquearan en cierto punto de la historia. Esas deben tener 
		bool blocked_ = false;
	};
	//Cada componente de Dialogo tendr� asociado un Actor al cual hace referencia
	//Por ejemplo el Barman ser� el Actors::Barman
	ActorID actorName_;


	virtual void update() override;
	void interact();
	size_t getNumOfDialogs() { return numOfDialogs_; }
	inline vector<dialogOption>& getOptions() { return dialogs_; };
private:
	//Cada personaje tiene un n�mero de dialogos definido
	size_t numOfDialogs_;

	size_t currentOption_;
	size_t currentLine_;
	
	bool conversing = false;
	//este vector de tama�o numOfDialogs guarda todo el dialogo que tiene el personaje
	vector<dialogOption> dialogs_;

	Text* textComponent_;
	//Manda al componente de texto asignado las opciones de dialogo
	void sendDialogOtions();
	void advanceDialog();
	inline void sendCurrentLine() { textComponent_->setNextText(dialogs_[currentOption_].conversation_[currentLine_].line_); };
};

//R: Hola Ana
//A: Hola Ricardo, qu� tal?
//R: Bien y t�?
//A: Bien.
//R: �Ya hiciste la camara?
//R: �Qu� tal la familia? -> Desbloquea pista (Llama a un callback)