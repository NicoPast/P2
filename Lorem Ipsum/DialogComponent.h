#pragma once
#include "Component.h"
//#include "StoryManager.h"
#include <array>
#include <string>
#include "Text.h"
#include "Rectangle.h"
#include <functional>
//#include "DialogEditorState.h"
class StoryManager;
class Text;
class Actor;
class DialogComponent : public Component
{
public:
	DialogComponent(Entity* player, Actor* actor, StoryManager* sm, size_t dialogs =1) : Component(ecs::DialogComponent), numOfDialogs_(dialogs),
		player_(player), currentLine_(0), currentOption_(0)
	{
		actor_ = actor;
		textComponent_ = nullptr;
		actorNameComponent_ = nullptr;
		selectedDialog_ = nullptr;
		rectComponent_ = nullptr;
		sm_ = sm;
	}

	virtual ~DialogComponent() {};

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	Actor* actor_;


	virtual void update() override;
	virtual void init() override;

	void interact();
	
	void addDialog(Dialog* d, bool active) { dialogs_.push_back({ active, d }); };
	void setFunc(std::function<void()> func) { func_ = func; };
private:
	//Cada personaje tiene un número de dialogos definido
	size_t numOfDialogs_;

	size_t currentOption_;
	size_t currentLine_;
	
	bool conversing_ = false;
	
	Dialog* selectedDialog_;
	list<pair<bool, Dialog*>> dialogs_;
	vector<Dialog*> availableDialogs;

	Entity* player_;
	Text* actorNameComponent_;
	Text* textComponent_;
	Rectangle* rectComponent_;
private:
	//Manda al componente de texto asignado las opciones de dialogo
	void startDialog();
	void showDialogList(vector<Dialog*> v);
	void sendDialogOtions();
	void stopDialog();
	void advanceDialog();
	void sendCurrentLine();
	StoryManager* sm_;
	bool showingOptions_ = false; //Para encargarse de colorear las opciones y/o seleccionar la que toca
	std::function<void()> func_=nullptr;
};
