#include "LoremIpsum.h"
#include "DialogEditorState.h"
#include "DialogComponent.h"
#include "jute.h"

#include <iostream>
#include <fstream>
#include "SDL_Macros.h"

#include "DialogSystem.h"
#include "InputText.h"

#include "Sprite.h"

DialogEditorState::~DialogEditorState()
{ 
	cout << json.to_string() << endl;
	for (auto b: optionsContainer)
		delete b;
};

void DialogEditorState::init()
{
	int windowW = game_->getGame()->getWindowWidth();
	int windowH = game_->getGame()->getWindowHeight();


	int paddingPanels = 15;
	int panelH = (2*windowH / 7);
	int panelW = windowW - 2 * paddingPanels;

	int columnW = (windowW / 3) - (2*paddingPanels);
	int columnH = (windowH - panelH)- (3 * paddingPanels);

	int statusPanelH = columnH / 5;

	SDL_Color lighterColor{ COLOR(lighter) };
	SDL_Color lightColor{ COLOR(light) };
	SDL_Color darkColor{ COLOR(dark) };
	SDL_Color darkerColor{ COLOR(darker) };

	//Background
	new UIPanel(entityManager_, 0, 0, windowW, windowH, SDL_Color{ COLOR(lighter) });
	dialogsPanel = new UIPanel(entityManager_, paddingPanels, paddingPanels, columnW, columnH, SDL_Color{ COLOR(base) });
	dialogsPanel->setHideenPos(-(columnW + paddingPanels), paddingPanels);

	//Botón de añadir dialogo
	std::function<void(DialogEditorState*)>cb = [columnW](DialogEditorState* s) {s->addDialog(columnW); };
	addDialogButton_ = new UIButton<DialogEditorState*>(entityManager_, paddingPanels+5, (columnH+ paddingPanels) - 35, 30, 30,
		SDL_Color{ COLOR(dark) }, game_->getGame()->getTextureMngr()->getTexture(Resources::AddIcon),
		cb, this);
	auto but = addDialogButton_;
	cb = [columnW, lightColor, but](DialogEditorState* s) {s->addDialog(columnW); but->setColor(lightColor); };
	addDialogButton_->setCB(cb, this);
	addDialogButton_->setMouseOutCB([darkColor, but]() {but->setColor(darkColor); });
	addDialogButton_->setMouseOverCB([darkerColor, but]() {but->setColor(darkerColor); });
		
	//Botón para borrar dialogo
	deleteDialogButton_ = new UIButton<DialogEditorState*>(entityManager_, paddingPanels + 50, (columnH + paddingPanels) - 35, 30, 30,
		SDL_Color{ COLOR(dark) }, game_->getGame()->getTextureMngr()->getTexture(Resources::TrashIcon), cb, this);
	but = deleteDialogButton_;
	cb = [columnW, lightColor, but](DialogEditorState* s) {s->deleteDialog(s->getActualDialogId()); but->setColor(lightColor); };
	deleteDialogButton_->setCB(cb, this);
	deleteDialogButton_->setMouseOutCB([darkColor, but]() {but->setColor(darkColor); });
	deleteDialogButton_->setMouseOverCB([darkerColor, but]() {but->setColor(darkerColor); });

	//Botón de añadir opción
	cb = [columnW](DialogEditorState* s) {s->addDialogOption(columnW); };
	addOptionButton_ = new UIButton<DialogEditorState*>(entityManager_, windowW-paddingPanels-35, (columnH + paddingPanels) - 35, 30, 30,
		SDL_Color{ COLOR(dark) }, game_->getGame()->getTextureMngr()->getTexture(Resources::AddIcon),
		cb, this);
	but = addOptionButton_;
	cb = [columnW, lightColor, but](DialogEditorState* s) {s->addDialogOption(columnW); but->setColor(lightColor); };
	addOptionButton_->setCB(cb, this);
	addOptionButton_->setMouseOutCB([darkColor, but]() {but->setColor(darkColor); });
	addOptionButton_->setMouseOverCB([darkerColor, but]() {but->setColor(darkerColor); });

	//Botón para borrar opcion
	deleteOptionButton_ = new UIButton<DialogEditorState*>(entityManager_, windowW - paddingPanels - 85, (columnH + paddingPanels) - 35, 30, 30,
		SDL_Color{ COLOR(dark) }, game_->getGame()->getTextureMngr()->getTexture(Resources::TrashIcon), cb, this);
	but = deleteOptionButton_;
	cb = [columnW, lightColor, but](DialogEditorState* s) {s->deleteDialogOption(); but->setColor(lightColor); };
	deleteOptionButton_->setCB(cb, this);
	deleteOptionButton_->setMouseOutCB([darkColor, but]() {but->setColor(darkColor); });
	deleteOptionButton_->setMouseOverCB([darkerColor, but]() {but->setColor(darkerColor); });

	//Panel central
	configurationPanel = new UIPanel(entityManager_, (3 * paddingPanels) + columnW, paddingPanels, columnW, columnH - statusPanelH, SDL_Color{ COLOR(base) });
	configurationPanel->setHideenPos((3 * paddingPanels) + columnW, (-columnH - paddingPanels));

	//Panel de estado
	statusPanel = new UIPanel(entityManager_, (3 * paddingPanels) + columnW, 2*paddingPanels + (columnH - statusPanelH), columnW, statusPanelH-(paddingPanels), SDL_Color{ COLOR(base) });

	//Panel de opciones
	optionsPanel = new UIPanel(entityManager_, (5 * paddingPanels) + 2 * columnW, 15, columnW, columnH, SDL_Color{COLOR(base)});
	optionsPanel->setHideenPos(windowW + columnW , 15);

	//textbox y su background  
	new UIPanel(entityManager_, 15, columnH + (2 * paddingPanels), panelW, panelH, SDL_Color{ COLOR(base) });
	textBox_ = new UIPanel(entityManager_, 2*paddingPanels, columnH+(3*paddingPanels), panelW-30, panelH-30, SDL_Color{COLOR(light)});
	//textBox_->addTitle(2 * paddingPanels, 5, panelW - 2 * paddingPanels, buttonFont, "nombre");
	textBox_->addText(3*paddingPanels,35,panelW-2*paddingPanels,buttonFont, "TextoDialogoTextoDialogoTextoDialogo TextoDialogoTextoDialogoTextoDialogoTextoDialogo TextoDialogoTextoDialogoTextoDialogoTextoDialogo");
	textBox_->disable();
	
	//funciones no como el resto del init lmao
	addDialogButtons(paddingPanels, paddingPanels+5, columnH, columnW);
	addOptionsButtons(columnW, columnH, (2 * columnW) + (5 * paddingPanels), paddingPanels+5);


	constexpr int littlebutSize = 32;
	constexpr int littlebutPadding = 6;
	
	//Botón de avanzar linea
	nextLineB = new UIButton<DialogEditorState*>();
	string estoSeraUnaImg = ">";
	addBasicButton(estoSeraUnaImg, (panelW - paddingPanels), 0, windowH - (panelH+3*paddingPanels) + littlebutSize, littlebutSize, littlebutSize, *nextLineB);
	nextLineB->setCB([](DES* s) {s->nextLine(); }, this);
	UIButton<DialogEditorState*>* b = nextLineB;
	nextLineB->setMouseOutCB([darkerColor, b]() {b->setColor(darkerColor); });
	nextLineB->setColor(SDL_Color{ COLOR(darker) });
	nextLineB->disable();

	//Botón de retroceder línea
	prevLineB = new UIButton<DialogEditorState*>();
	string estoSeraOtraImg = "<";
	addBasicButton(estoSeraOtraImg, (panelW - paddingPanels) - (littlebutSize), 0, windowH-(panelH+3*paddingPanels) + littlebutSize, littlebutSize, littlebutSize, *prevLineB);
	prevLineB->setCB([](DES* s) {s->prevLine(); }, this);
	prevLineB->setColor(SDL_Color{ COLOR(darker) });
	b = prevLineB;
	prevLineB->setMouseOutCB([darkerColor, b]() {b->setColor(darkerColor); });
	prevLineB->disable();

	//Botón de editar línea
	std::function<void(DialogEditorState*)>f = [](DialogEditorState* s) {};
	editLineB = new UIButton<DialogEditorState*>(entityManager_, (panelW - paddingPanels) - (2*littlebutSize), windowH - (panelH + 3 * paddingPanels) + littlebutSize,
		littlebutSize, littlebutSize, SDL_Color{ COLOR(lighter) }, game_->getGame()->getTextureMngr()->getTexture(Resources::EditIcon), f, this);
	editLineB->setCB([](DES* s) {s->editDialogText(); }, this);
	editLineB->setColor(SDL_Color{ COLOR(lighter) });
	b = editLineB;
	editLineB->setMouseOutCB([lighterColor, b]() {b->setColor(lighterColor); });
	editLineB->setMouseOverCB([darkColor, b]() {b->setColor(darkColor); }); 
	editLineB->disable();

	newLineB= new UIButton<DialogEditorState*>(entityManager_, (panelW - paddingPanels) - (3 * littlebutSize), windowH - (panelH + 3 * paddingPanels) + littlebutSize,
		littlebutSize, littlebutSize, SDL_Color{ COLOR(lighter) }, game_->getGame()->getTextureMngr()->getTexture(Resources::AddIcon), f, this);
	newLineB->setCB([](DES* s) {s->addLine(); }, this);
	newLineB->setColor(SDL_Color{ COLOR(lighter) });
	setMouseOverCBs(newLineB);
	newLineB->disable();
	
	deleteLineButton_ = new UIButton<DialogEditorState*>(entityManager_, (panelW - paddingPanels) - (4 * littlebutSize), windowH - (panelH + 3 * paddingPanels) + littlebutSize,
		littlebutSize, littlebutSize, SDL_Color{ COLOR(lighter) }, game_->getGame()->getTextureMngr()->getTexture(Resources::TrashIcon), f, this);
	deleteLineButton_->setCB([](DES* s) {s->removeLine(); }, this);
	deleteLineButton_->setColor(SDL_Color{ COLOR(lighter) });
	setMouseOverCBs(deleteLineButton_);
	deleteLineButton_->disable();


	string text = "Yeeeeeeeeeeeeeeeeeeeeeeeeeeeet";
	int padding = 4;
	statusButton_ =new UIButton<DialogEditorState*>();
	addBasicButton(text, 10, 10, 10, 10, 100000, *statusButton_);
	statusButton_->setParent(statusPanel);
	statusButton_->setXY(padding, padding);
	statusButton_->setWH(columnW-(2* padding), statusPanelH - (paddingPanels) -(2* padding));
	statusButton_->setText("");
	clearMouseOverCBs(statusButton_);

	vector<string> names;
	for (int i = 0; i < Resources::actors_.size(); i++)
	{
		names.push_back(Resources::actors_[i].name_);
	}
	dialogActorDropDown = createDropdown(names, "Quien tiene el diálogo", columnW + paddingPanels * 3 + 5, paddingPanels + 10, columnW - 10, 30, false);
	for (int i = 1; i < dialogActorDropDown.size(); i++)
	{
		auto but = dialogActorDropDown[i];
		SDL_Color c{ COLOR(dark) };
		dialogActorDropDown[i]->setCB([c, i, but](DialogEditorState* s) {
			s->setDialogActor(Resources::actors_[i-1].id_);
			but->setColor(c);
			}, this);
	};
	lineActorDropDown = createDropdown(names, "Actor:", 2 * paddingPanels, columnH + (3 * paddingPanels),350, 30, false);
	for (int i = 1; i < Resources::actors_.size()+1; i++)
	{
		auto but = lineActorDropDown[i];
		auto butName = lineActorDropDown[0];
		auto prueba = Resources::actors_[i-1].name_;
		string name = but->getText();
		SDL_Color c{ COLOR(dark) };
		lineActorDropDown[i]->setCB([c, i, but,butName, prueba,name](DialogEditorState* s) {
			but->setColor(c);
			butName->setText(name);
			int index = i - 1;
			s->changeLineActor(index);
			cout <<index << " " << name << " " << prueba <<endl;
			}, this);
	}

}
void DialogEditorState::changeLineActor(size_t id)
{
	actualOption->lines_[lineIndex_].actorID_ = id;
 	cout << game_->getStoryManager()->getActorName((Resources::ActorID)id)<<endl;
	saveCurrentDialog();
}
void DialogEditorState::addDialogOption(int columnW)
{
	int h = 30;
	int buttonPadding = 5;
	int lastActive = 0;
	int acumH = 0;
	while (optionsContainer[lastActive]->isActive() && lastActive < optionsContainer.size())
	{
		acumH += optionsContainer[lastActive]->getH();
		lastActive++;
	}

	string text = "lloro";
	auto button = new UIButton<DialogEditorState*>();
	addBasicButton(text, buttonPadding, 0, optionsContainer[0]->getY()+acumH, h, optionsContainer[0]->getW(), *button);
	optionsContainer.push_back(button);
	button->setParent(optionsPanel);
	button->setX(buttonPadding);
	button->setIndex(optionsContainer.size() + 1);
	button->editText<DialogEditorState*>([button](DialogEditorState* s) {s->addDialogOptionForReal(button->getText()); }, this, false);
}

void DialogEditorState::addDialogOptionForReal(string startingLine)
{
	vector<DialogLine>lines;
	DialogLine l((Resources::ActorID)1, "Escribe algo ahí");
	lines.push_back(l);
	actualDialog->options_.push_back(DialogOption(startingLine, lines));
	showOptions();
}

void DialogEditorState::addDialog(int columnW)
{
	int i = dialogsContainer.size();
	int h = 30;
	int buttonPadding = 0;
	int id = game_->getStoryManager()->dialogs_.size();

	string text = "WAPISIMO";
	auto b = new UIButton<DialogEditorState*>();
	//addBasicButton(text, 10 + buttonPadding, buttonPadding + h * dialogsContainer.size() + 1, (h * i), h, numeroMagico - 2 * buttonPadding, *b);
	addBasicButton(text, dialogsContainer[0]->getX(), buttonPadding, dialogsContainer[0]->getY() + (h * i), h, dialogsContainer[0]->getW(), *b);
	SDL_Color clicked{ COLOR(dark) };
	b->setCB([id, b, clicked](DialogEditorState* s) {
		s->selectDialog(id); b->setColor(clicked);
		b->setMouseOutCB([]() {});
		b->setMouseOverCB([]() {});
		}, this);
	b->setIndex(i);
	b->setParent(dialogsPanel);
	dialogsContainer.push_back(b);
	b->editText<DialogEditorState*>([b](DialogEditorState* s) {s->addDialogForReal(b->getText()); }, this, true);
}

void DialogEditorState::deleteDialogOption()
{
	actualDialog->options_.erase(actualDialog->options_.begin() + actualOptionIndex);	
	actualOption = nullptr;
	showOptions();
}

void DialogEditorState::deleteDialog(int index)
{
	string pathToDelete = "../assets/dialogs/" + game_->getStoryManager()->dialogs_[index]->dialogName_ + ".dialog";
	int removed = remove(pathToDelete.c_str());

	string dir = "../assets/dialogs/dialogList.conf";
	string name = game_->getStoryManager()->dialogs_[index]->dialogName_;
	game_->getStoryManager()->dialogs_.erase(index);
	ifstream reader(dir);
	int numOfDialogs;
	reader >> numOfDialogs;
	auto buffer = reader.rdbuf();
	bool skiped = false;
	string totalText="";
	for (int i = 0; i < numOfDialogs; i++)
	{
		string actualName;
		int actualNumber;
		reader >> actualName;
		reader >> actualNumber;
		if (!skiped && actualName == name)
		{
			skiped = true;
			//Re-escribimos con el siguiente, porque estamos saltando uno
			if (i < numOfDialogs - 1)
			{
				reader >> actualName;
				reader >> actualNumber;
			}
			else actualName = "";
		}
		if (skiped)
			actualNumber--;
		totalText += actualName;
		totalText += " ";
		totalText += (actualName=="") ? "" : to_string(actualNumber);
		totalText += "\n";
	}
	reader.close();
	ofstream writer(dir);
	writer << numOfDialogs-1 << endl << totalText;
	for (auto& but : dialogsContainer)
		but->disable();
	int i = 0;
	for (auto& dialg : game_->getStoryManager()->dialogs_)
	{
		auto b = dialogsContainer[i];
		SDL_Color clicked{ COLOR(dark) };
		b->setCB([b, clicked, dialg](DialogEditorState* s) {
			s->selectDialog(dialg.second->id_);
			b->setColor(clicked);
			b->setMouseOutCB([]() {});
			b->setMouseOverCB([]() {});
			}, this);
		b->setText(dialg.second->dialogName_);
		b->enable();
		i++;
	}
}
void DialogEditorState::addDialogForReal(string name)
{

	ifstream f("../assets/dialogs/" + name + ".dialog");
	if( f.good() ) throw exception("Ya hay uno que se llama igual paleto");

	int id = game_->getStoryManager()->dialogs_.size();
	ofstream file("../assets/dialogs/" + name + ".dialog");
	file << id;
	file.close();
	game_->getStoryManager()->dialogs_[id] = new Dialog();
	game_->getStoryManager()->dialogs_[id]->dialogName_ = name;
	string dir = "../assets/dialogs/dialogList.conf";
	ifstream reader(dir);
	int numOfDialogs;
	reader >> numOfDialogs;//nos saltamos el número de dialogos
	auto data = reader.rdbuf();
	file.open(dir);
	file << numOfDialogs + 1;
	file << data;
	file << endl;
	file << name << " ";
	file << numOfDialogs;
	actualDialog = game_->getStoryManager()->dialogs_[id];
	actualDialog->id_ = id;
	dialogId_ = id;
	
	selectDialog(id);

}

void DialogEditorState::addOptionsButtons(int columnW, int columnH, int x, int y)
{
	int i = 0;
	int h = 30;
	int buttonPadding = 5;
	for (int i = 0; i < 10; i++)
	{
		string text = "option"+i;
		auto button = new UIButton<DialogEditorState*>();
		addBasicButton(text, 0, buttonPadding, y, h, columnW - 2 * buttonPadding, *button);
		optionsContainer.push_back(button);
		button->setParent(optionsPanel);
		button->setX(buttonPadding);
		button->setIndex(i);
		button->disable();
	}

}
void DialogEditorState::addDialogButtons(int x, int y, int columnH, int columnW)
{
	int i = 0;
	int h = 30;
	int buttonPadding = 5;
	for (auto& dialg : game_->getStoryManager()->dialogs_)
	{
		string text = dialg.second->dialogName_;
		int id = dialg.second->id_;

		auto b = new UIButton<DialogEditorState*>();
		addBasicButton(text, 10+buttonPadding, buttonPadding, y+(h*i), h, columnW - 2 * buttonPadding, *b);
		SDL_Color clicked{COLOR(dark)};
		b->setCB([id, b, clicked](DialogEditorState* s) {
			s->selectDialog(id); b->setColor(clicked); 
			b->setMouseOutCB([]() {});
			b->setMouseOverCB([]() {});
			}, this);
		i++;
		b->setIndex(i);
		b->setParent(dialogsPanel);
		dialogsContainer.push_back(b);
	}
}
void DialogEditorState::addBasicButton(std::string& text, int x, int buttonPadding, int y, int h, int w, UIButton<DialogEditorState*>& but, int layer)
{
	std::function<void()>a = []() {};
	std::function<void(DialogEditorState*)>b = [](DialogEditorState* s) { };
	auto button = new UIButton<DialogEditorState*>(entityManager_, x + buttonPadding, y + buttonPadding, w, h,SDL_Color{ COLOR(light) }, text, 2, -2, buttonFont, b, this,layer);
	SDL_Color overColor = SDL_Color{ COLOR(lighter) };
	SDL_Color baseColor = SDL_Color{ COLOR(light) };

	a = [button, overColor]() {button->setColor(overColor); };
	button->setMouseOverCB(a);
	a = [button, baseColor]() {button->setColor(baseColor); };
	button->setMouseOutCB(a);
	button->setBorder(SDL_Color{ COLOR(darker) });
	but = *button;
}


void DialogEditorState::selectDialog(size_t id)
{
	actualDialog = game_->getStoryManager()->dialogs_[id];
	dialogId_ = actualDialog->id_;
	int i = 0;
	for (auto& but : dialogActorDropDown)
	{
		but->setColor(SDL_Color{ COLOR(light) });
		setMouseOverCBs(but);
	}
	for (auto but : dialogActorDropDown)
	{
		if (i == actualDialog->actorID_+1)
		{
			but->setColor(SDL_Color{ COLOR(dark) });
			clearMouseOverCBs(but);
		}
		i++;
	}
	showOptions();
	i = 0;
	for (auto& b : dialogsContainer)
	{
		if (i != b->getIndex())
		{
			setMouseOverCBs(b);
		}
		else if (i == b->getIndex())
		{
			clearMouseOverCBs(b);
		}
		i++;
	}
}

void DialogEditorState::showOptions()
{
	int i = 0;
	int acumH = 0;
	for (auto& but : optionsContainer)
	{
		but->disable();
		but->setY(optionsContainer[0]->getY());
	}
	for (auto& option : actualDialog->options_)
	{
		auto button = optionsContainer[i];
		string text = option.startLine_;
		if (text == "")text = "Primera conversación(saludo)";
		DialogOption* d = &option;
		SDL_Color clicked{ COLOR(dark) };
		SDL_Color baseC{ COLOR(light) };
		std::function<void(DialogEditorState*)>b = [text, i, button, clicked, baseC](DialogEditorState* s) {
			s->setDialogOption(i); 
			button->setColor(clicked);
			button->setMouseOutCB([button, baseC]() {});
			button->setMouseOverCB([]() {});
		};
		button->enable();
		button->setCB(b, this);
		button->setText(text);

		if (acumH > 0)button->setY(button->getY() + acumH);

		button->adjustHeightBasedOnText();
		acumH += button->getH();

		i++;
	}
}


void DialogEditorState::setDialogOption(int index)
{
	int i = 0;
	for (auto& b : optionsContainer)
	{
		if (i != index)
		{
			setMouseOverCBs(b);
		}
		else if (i == index)
		{
			clearMouseOverCBs(b);
		}
		i++;
	}
	actualOption = &actualDialog->options_[index];
	actualOptionIndex = index;
	lineIndex_ = 0;
	updateDialogText();
	nextLineB->enable();
	prevLineB->enable();
	editLineB->enable();
	newLineB->enable();
	deleteLineButton_->enable();
	textBox_->enable();
}

void DialogEditorState::updateDialogText()
{
	textBox_->setText(actualOption->lines_[lineIndex_].line_);
	lineActorDropDown[0]->setText(game_->getStoryManager()->getActorName((Resources::ActorID)actualOption->lines_[lineIndex_].actorID_));
}

void DialogEditorState::editDialogText()
{
	textBox_->edit(this);
	statusButton_->setText("Editing...");
	for (auto& b : dialogsContainer)
	{
		if (b->getID() != dialogId_)
		{
			clearMouseOverCBs(b);
			b->disableClick();
		}
	}
	for (auto& b : optionsContainer)
	{
		clearMouseOverCBs(b);
		b->disableClick();
	}
}
void DialogEditorState::endTextEdit()
{
	string quieroMorir = textBox_->getFullText();
	actualOption->lines_[lineIndex_].line_ = quieroMorir;
	int i = 0;
	json = actualDialog->toJSON();

	for (auto& b : dialogsContainer)
	{
		if (b->getID() != dialogId_)
		{
			b->enableClick();
		}
	}
	for (auto& b : optionsContainer)
	{
		b->enableClick();
		if (b->getIndex() == actualOptionIndex)
		{
			b->setColor(SDL_Color{ COLOR(darker) });
		}
		else
		{
			setMouseOverCBs(b);
		}
	}
	SDL_Color darkc = { COLOR(0x66dd66ff) };
	auto but = statusButton_;
	statusButton_->setText("Save changes");
	statusButton_->setCB([darkc, but](DialogEditorState* s) { s->saveCurrentDialog(); but->setColor(darkc); }, this);
	statusButton_->enableClick();
	SDL_Color base = { COLOR(0x77dd77ff) };
	SDL_Color highlighted = { COLOR(0x88ee88ff) };
	auto b = statusButton_;
	statusButton_->setMouseOutCB([base, b]() {b->setColor(base); });
	statusButton_->setMouseOverCB([highlighted, b]() {b->setColor(highlighted); });
	statusButton_->setColor(base);
}
void DialogEditorState::saveCurrentDialog()
{
	if (actualDialog != nullptr)
	{
		json = actualDialog->toJSON();
		ofstream file;
		file.open(FILEDIR + actualDialog->dialogName_ + ".dialog");
		file << json.to_string();
		file.close();
	}
}

void DialogEditorState::UIPanel::edit(DialogEditorState* s)
{
	eText_->addComponent<InputText<DialogEditorState*>>(GETCMP2(eText_, Text), [](DialogEditorState* des) {des->endTextEdit(); }, s, false);
};

vector<DialogEditorState::UIButton<DialogEditorState*>*> DialogEditorState::createDropdown(vector<string>names,string text, int x, int y, int w, int h, bool up)
{
	UIButton<DialogEditorState*>* b = new UIButton<DialogEditorState*>();
	int index = 1;
	int dir = (up)? -1 : 1;
	addBasicButton(text, x, 0, y, h, w, *b);
	vector<Transform*>transforms;
	vector<UIButton<DialogEditorState*>*> buttons;
	buttons.push_back(b);
	for (string buttName : names)
	{
		UIButton<DialogEditorState*>* but = new UIButton<DialogEditorState*>();
		addBasicButton(buttName, x, 0, y+h*index*dir, h, w, *but,1);
		but->disable();
		buttons.push_back(but);
		transforms.push_back(but->getTransform());
		index++;
	}

	SDL_Rect rect{ x,y+h,w, h * 2 * dir };
	auto scroll = b->createScroll(rect, transforms, 0, SDL_Color{ COLOR(dark) }, SDL_Color{ COLOR(light) });
	b->setCB([buttons, scroll](DialogEditorState* state)
		{
			for (int i = 1; i<buttons.size();i++)
			{
				auto& but = buttons[i];
				(but->isActive()) ? scroll->hide() : scroll->show();
				(but->isActive()) ? but->disable() : but->enable();
				cout << i - 1;
			}
		}
	, this);
	return buttons;
}
