#pragma once
#include "Component.h"
//#include "StoryManager.h"
#include <array>
#include <string>
#include "Text.h"
#include "Rectangle.h"
#include <functional>
#include "Tween.h"
#include <bitset>
//#include "DialogEditorState.h"
class StoryManager;
class Text;
class Actor;
class DialogComponent : public Component
{
	static constexpr short int MAXDIALOGS = 32;
	static constexpr short int MAXOPTIONS = 32;
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
		optionsStatus_.resize(MAXDIALOGS);
	}

	virtual ~DialogComponent();


	//El array guarda booleanos para no mostrar los dialogos bloquados
	//Los dialogos son arrays de strings
	Actor* actor_ = nullptr;


	virtual void update() override;
	virtual void init() override;

	void interact();
	//CUIDADO CON ESTE METODO VA A BORRAR TODOS LOS DEMÁS DIALGOOS QUE TENGA GUARDADOS
	//POR AHORA SOLO SE USA AL PENSAR EN VOZ ALTA Y SI LO USAS EN OTRO LADO TE LA JUEGAS
	void setSingleDialog(Dialog* d)
	{
		while (!dialogs_.empty()) {
			delete dialogs_.back();
			dialogs_.pop_back();
		}
			
		dialogs_.push_back(d); d->listPosition_ = dialogs_.size() - 1; refresh();
		hasFunc = false;
	};

	void deleteSingleDialog() {
		delete dialogs_.back();
		dialogs_.pop_back();
	}

	void addDialog(Dialog* d);
	void setFunc(std::function<void(DialogComponent*)> func) { dialogSelectorFunc_ = func; hasFunc = true; };

	void setDialogActive(int id, bool active)
	{
		getDialog(id)->active_ = active;
		refresh();
	}

	Dialog* getDialog(int dialog) {
		if (dialog >= dialogs_.size()) return nullptr;

		for (auto d : dialogs_)
			if (d->id_ == dialog) return d;
	};
	void refresh()
	{
		while (!availableDialogs.empty())
			availableDialogs.pop_back();
	}

	const std::bitset<MAXDIALOGS>& getDialogStatus() { return dialogsStatus_; };
	const std::vector<std::bitset<MAXOPTIONS>>& getOptionsStatus() { return optionsStatus_; };
private:
	//Cada personaje tiene un número de dialogos definido
	size_t numOfDialogs_ = 0;

	size_t currentOption_ = 0;
	size_t currentLine_ = 0;
	
	bool conversing_ = false;
	bool showingDialogs = false;
	
	Dialog* selectedDialog_ = nullptr;
	vector<Dialog*> dialogs_;
	vector<Dialog*> availableDialogs;

	Entity* player_ = nullptr;
	Entity* phone_ = nullptr;
	Text* actorNameComponent_ = nullptr;
	Text* textComponent_ = nullptr;
	Tween* tweenComponent_ = nullptr;
	string file_="";
private:
	//Manda al componente de texto asignado las opciones de dialogo
	void startDialog();
	void showDialogList(vector<Dialog*>& v);
	void sendDialogOtions();
	void stopDialog();
	void advanceDialog();
	void sendCurrentLine();
	void checkOptionsColor();

	StoryManager* sm_ = nullptr;
	bool showingOptions_ = false; //Para encargarse de colorear las opciones y/o seleccionar la que toca
	std::vector<std::pair<int, int>> optionsPairs;
	//Esta funcion se encarga de manejar que dialogos de los que están activos mostramos, cuales no, cuales tienen mas importancia etc.
	//Se llama en interact y se guarda en setFunc()
	std::function<void(DialogComponent*)> dialogSelectorFunc_ =	nullptr;
	bool hasFunc = false;
	std::vector<std::bitset<MAXOPTIONS>> optionsStatus_;
	std::bitset<MAXDIALOGS> dialogsStatus_;
	friend class DialogSelectors;
};
