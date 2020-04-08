#pragma once
#include "Component.h"
#include "StoryManager.h"

#include <array>
#include <string>
#include "Text.h"
#include "Rectangle.h"
//#include "DialogEditorState.h"

class DialogComponent : public Component
{
public:
	DialogComponent(Entity* player, Actor* actor, size_t dialogs =1) : Component(ecs::DialogComponent), numOfDialogs_(dialogs),
		player_(player), currentLine_(0), currentOption_(0)
	{
		//dialogs_.options_.resize(numOfDialogs_);
		actor_ = actor;
		textComponent_ = nullptr;
		actorNameComponent_ = nullptr;
	}

	virtual ~DialogComponent() {};

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	Actor* actor_;


	virtual void update() override;
	virtual void init() override;
	void interact();
	size_t getNumOfDialogs() { return numOfDialogs_; }
	//inline vector<dialogOption>& getOptions() { return dialogs_; };
	void setDialog(Dialog* d) { dialog_ = d; };
private:
	//Cada personaje tiene un n�mero de dialogos definido
	size_t numOfDialogs_;

	size_t currentOption_;
	size_t currentLine_;
	
	bool conversing_ = false;
	
	Dialog* dialog_;
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
		textComponent_->setText(dialog_->options_[currentOption_].lines_[currentLine_].line_);
		actorNameComponent_->setText(dialog_->options_[currentOption_].lines_[currentLine_].actorName_);
	};
};

//R: Hola Ana
//A: Hola Ricardo, qu� tal?
//R: Bien y t�?
//A: Bien.
//R: �Ya hiciste la camara?
//R: �Qu� tal la familia? -> Desbloquea pista (Llama a un callback)