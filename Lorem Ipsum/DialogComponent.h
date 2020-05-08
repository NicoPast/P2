#pragma once
#include "Component.h"
//#include "StoryManager.h"
#include <array>
#include <string>
#include "Text.h"
#include "Rectangle.h"
#include <functional>
#include "Tween.h"
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
		tweenComponent_ = nullptr;
		phone_ = nullptr;
		sm_ = sm;
	}

	virtual ~DialogComponent() {};

	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	Actor* actor_;


	virtual void update() override;
	virtual void init() override;

	void interact();
	//CUIDADO CON ESTE METODO VA A BORRAR TODOS LOS DEMÁS DIALGOOS QUE TENGA GUARDADOS
	void setSingleDialog(Dialog* d, bool active=true)
	{
		while (!dialogs_.empty())
			dialogs_.pop_back();
		dialogs_.push_back({ active,d });
	};

	void addDialog(Dialog* d, bool active) { dialogs_.push_back({ active, d }); refresh(); };
	void setFunc(std::function<void(DialogComponent*)> func) { func_ = func; };

	void setDialogActive(int id, bool active)
	{
		getDialog(id)->active_ = active;
		refresh();
	}

	Dialog* getDialog(int dialog) {
		if (dialog >= dialogs_.size()) return nullptr;

		for (auto d : dialogs_)
			if (d.second->id_ == dialog) return d.second;
	};
	void refresh()
	{
		while (!availableDialogs.empty())
			availableDialogs.pop_back();
		for (auto d : dialogs_)
			d = { d.second->active_,d.second };
	}
private:
	//Cada personaje tiene un número de dialogos definido
	size_t numOfDialogs_;

	size_t currentOption_;
	size_t currentLine_;
	
	bool conversing_ = false;
	bool showingDialogs = false;
	
	Dialog* selectedDialog_;
	list<pair<bool, Dialog*>> dialogs_;
	vector<Dialog*> availableDialogs;

	Entity* player_;
	Entity* phone_;
	Text* actorNameComponent_;
	Text* textComponent_;
	Tween* tweenComponent_;
private:
	//Manda al componente de texto asignado las opciones de dialogo
	void startDialog();
	void showDialogList(vector<Dialog*>& v);
	void sendDialogOtions();
	void stopDialog();
	void advanceDialog();
	void sendCurrentLine();

	StoryManager* sm_;
	bool showingOptions_ = false; //Para encargarse de colorear las opciones y/o seleccionar la que toca
	std::function<void(DialogComponent*)> func_ = nullptr;
};
