#pragma once
#include "Component.h"
#include "StoryManager.h"

#include <array>
#include <string>
#include "Text.h"
#include "Rectangle.h"

class Dialog : public Component
{
public:
	Dialog(Entity* player, Actor* actor, size_t dialogs =1) : Component(ecs::Dialog), numOfDialogs_(dialogs),
		player_(player), currentLine_(0), currentOption_(0)
	{
		dialogs_.resize(numOfDialogs_);
		actor_ = actor;
		textComponent_ = nullptr;
		actorNameComponent_ = nullptr;
	}

	virtual ~Dialog() {};

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	struct dialogLine
	{
		dialogLine():dialogLine("Empty text", Resources::ActorID::lastActorID){}
		dialogLine(string l, Resources::ActorID  id) : name_(id), line_(l) {};
		//El name es el nombre de la persona que dice la linea
		Resources::ActorID name_;

		//Esto puede ser un párrafo o una linea. Es lo que dice el actor
		string line_;
	};
	struct dialogOption
	{
		dialogOption(int numLines = 1) { lines_ = numLines; conversation_.resize(lines_); }
		//callback mágico que no sabemos hacer
		void* callback_ = nullptr;

		//número de "dialogLines", mínimo 1 
		size_t lines_;

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
	Actor* actor_;


	virtual void update() override;
	virtual void init() override;
	void interact();
	size_t getNumOfDialogs() { return numOfDialogs_; }
	inline vector<dialogOption>& getOptions() { return dialogs_; };
private:
	//Cada personaje tiene un número de dialogos definido
	size_t numOfDialogs_;

	size_t currentOption_;
	size_t currentLine_;
	
	bool conversing_ = false;
	
	//este vector de tamaño numOfDialogs guarda todo el dialogo que tiene el personaje
	vector<dialogOption> dialogs_;
	Entity* player_;
	Text* actorNameComponent_;
	Text* textComponent_;
	Rectangle* rectComponent_;
private:
	//Manda al componente de texto asignado las opciones de dialogo
	void sendDialogOtions();
	void stopDialog();
	void advanceDialog();
	inline void sendCurrentLine() {
		textComponent_->setText(dialogs_[currentOption_].conversation_[currentLine_].line_);
		actorNameComponent_->setText((dialogs_[currentOption_].conversation_[currentLine_].name_ == actor_->getId()) ? actor_->getName() : "SDL");
	};
};

//R: Hola Ana
//A: Hola Ricardo, qué tal?
//R: Bien y tú?
//A: Bien.
//R: ¿Ya hiciste la camara?
//R: ¿Qué tal la familia? -> Desbloquea pista (Llama a un callback)