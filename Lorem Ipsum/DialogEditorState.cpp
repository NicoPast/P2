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

	//int dialogOptionConfigH = 4 * (columnH/5.0);

	new UIPanel(entityManager_, 0, 0, windowW, windowH, SDL_Color{ COLOR(lighter) });
	dialogsPanel = new UIPanel(entityManager_, paddingPanels, paddingPanels, columnW, columnH, SDL_Color{ COLOR(base) });
	dialogsPanel->setHideenPos(-(columnW + paddingPanels), paddingPanels);
	std::function<void(DialogEditorState*)>cb = [columnW](DialogEditorState* s) {s->addDialog(columnW); };

	new UIButton<DialogEditorState*>(entityManager_, paddingPanels+5, (columnH+ paddingPanels) - 35, 30, 30,
		SDL_Color{ COLOR(dark) }, game_->getGame()->getTextureMngr()->getTexture(Resources::AddIcon),
		cb, this);
	cb = [columnW](DialogEditorState* s) {s->addDialogOption(columnW); };

	new UIButton<DialogEditorState*>(entityManager_, 3*columnW + paddingPanels + 5, (columnH + paddingPanels) - 35, 30, 30,
		SDL_Color{ COLOR(dark) }, game_->getGame()->getTextureMngr()->getTexture(Resources::AddIcon),
		cb, this);

	configurationPanel = new UIPanel(entityManager_, (3 * paddingPanels) + columnW, paddingPanels, columnW, columnH - statusPanelH, SDL_Color{ COLOR(base) });
	configurationPanel->setHideenPos((3 * paddingPanels) + columnW, (-columnH - paddingPanels));

	statusPanel = new UIPanel(entityManager_, (3 * paddingPanels) + columnW, 2*paddingPanels + (columnH - statusPanelH), columnW, statusPanelH-(paddingPanels), SDL_Color{ COLOR(base) });

	optionsPanel = new UIPanel(entityManager_, (5 * paddingPanels) + 2 * columnW, 15, columnW, columnH, SDL_Color{COLOR(base)});
	optionsPanel->setHideenPos(windowW + columnW , 15);

	new UIPanel(entityManager_, 15, columnH + (2 * paddingPanels), panelW, panelH, SDL_Color{ COLOR(base) });
	textBox_ = new UIPanel(entityManager_, 2*paddingPanels, columnH+(3*paddingPanels), panelW-30, panelH-30, SDL_Color{COLOR(light)});
	textBox_->addTitle(2 * paddingPanels, 5, panelW - 2 * paddingPanels, buttonFont, "nombre");
	textBox_->addText(3*paddingPanels,35,panelW-2*paddingPanels,buttonFont, "TextoDialogoTextoDialogoTextoDialogo TextoDialogoTextoDialogoTextoDialogoTextoDialogo TextoDialogoTextoDialogoTextoDialogoTextoDialogo");
	textBox_->disable();
	
	addDialogButtons(paddingPanels, paddingPanels, columnH, columnW);
	addOptionsButtons(columnW, columnH, (2 * columnW) + (5 * paddingPanels), paddingPanels);

	constexpr int littlebutSize = 32;
	constexpr int littlebutPadding = 6;
	SDL_Color darkerColor{ COLOR(darker) };

	nextLineB = new UIButton<DialogEditorState*>();
	string estoSeraUnaImg = ">";
	addBasicButton(estoSeraUnaImg, (panelW - paddingPanels), 0, windowH - (panelH+3*paddingPanels), littlebutSize, littlebutSize, *nextLineB);
	nextLineB->setCB([](DES* s) {s->nextLine(); }, this);
	UIButton<DialogEditorState*>* b = nextLineB;
	nextLineB->setMouseOutCB([darkerColor, b]() {b->setColor(darkerColor); });
	nextLineB->setColor(SDL_Color{ COLOR(darker) });
	nextLineB->disable();

	prevLineB = new UIButton<DialogEditorState*>();
	string estoSeraOtraImg = "<";
	addBasicButton(estoSeraOtraImg, (panelW - paddingPanels) - (littlebutSize), 0, windowH-(panelH+3*paddingPanels), littlebutSize, littlebutSize, *prevLineB);
	prevLineB->setCB([](DES* s) {s->prevLine(); }, this);
	prevLineB->setColor(SDL_Color{ COLOR(darker) });
	b = prevLineB;
	prevLineB->setMouseOutCB([darkerColor, b]() {b->setColor(darkerColor); });
	prevLineB->disable();

	std::function<void(DialogEditorState*)>f = [](DialogEditorState* s) {};
	editLineB = new UIButton<DialogEditorState*>(entityManager_, (panelW - paddingPanels) - (2*littlebutSize), windowH - (panelH + 3 * paddingPanels) + littlebutSize,
		littlebutSize, littlebutSize, SDL_Color{ COLOR(lighter) }, game_->getGame()->getTextureMngr()->getTexture(Resources::EditIcon), f, this);
	editLineB->setCB([](DES* s) {s->editDialogText(); }, this);
	editLineB->setColor(SDL_Color{ COLOR(lighter) });
	b = editLineB;
	SDL_Color lighterColor{ COLOR(lighter) };
	editLineB->setMouseOutCB([lighterColor, b]() {b->setColor(lighterColor); });

	SDL_Color darkColor{ COLOR(dark) };
	editLineB->setMouseOverCB([darkColor, b]() {b->setColor(darkColor); }); 
	editLineB->disable();


	string text = "Yeeeeeeeeeeeeeeeeeeeeeeeeeeeet";
	int padding = 4;
	statusB =new UIButton<DialogEditorState*>();
	addBasicButton(text, 10, 10, 10, 10, 100000, *statusB);
	statusB->setParent(statusPanel);
	statusB->setXY(padding, padding);
	statusB->setWH(columnW-(2* padding), statusPanelH - (paddingPanels) -(2* padding));
	statusB->setText("");
	clearMouseOverCBs(statusB);

}
void DialogEditorState::addDialogOption(int numeroMagico)
{
	int h = 30;
	int buttonPadding = 5;

	string text = "lloro";
	auto button = new UIButton<DialogEditorState*>();
	addBasicButton(text, 0, buttonPadding, (h * optionsContainer.size()+1), h, numeroMagico - 2 * buttonPadding, *button);
	button->disable();
	optionsContainer.push_back(button);
	button->setParent(optionsPanel);
	button->setX(buttonPadding);
	button->setIndex(optionsContainer.size() + 1);
	button->disable();
}



void DialogEditorState::addDialog(int numeroMagico)
{
	//int i = 0;
	//int h = 30;
	//int buttonPadding = 5;
	//string text = "WAPISIMO";
	//auto b = new UIButton<DialogEditorState*>();
	//addBasicButton(text, 10 + buttonPadding, buttonPadding + h*dialgosContainer.size()+1, (h * i), h, numeroMagico - 2 * buttonPadding, *b);
	//SDL_Color clicked{ COLOR(dark) };
	//b->setCB([text, b, clicked](DialogEditorState* s) {
	//	s->selectDialog(text); b->setColor(clicked);
	//	b->setMouseOutCB([]() {});
	//	b->setMouseOverCB([]() {});
	//	}, this);
	//i++;
	//b->setIndex(i);
	//b->setParent(dialogsPanel);
	//dialgosContainer.push_back(b);
}

void DialogEditorState::addOptionsButtons(int columnW, int columnH, int x, int y)
{
	int i = 0;
	int h = 30;
	int buttonPadding = 5;

	for (int i = 0; i < 10; i++)
	{
		string text = "lloro";
		auto button = new UIButton<DialogEditorState*>();
		addBasicButton(text, 0, buttonPadding, (h * i), h, columnW - 2 * buttonPadding, *button);
		button->disable();
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
	//		auto button=new UIButton<DialogEditorState*>(entityManager_, x+ buttonPadding, y + buttonPadding + (h+buttonPadding) * i, columnW - 2 * buttonPadding, h,
	//SDL_Color{ COLOR(light) }, text, 2, -2, buttonFont, b, this);
	for (auto& dialg : game_->getStoryManager()->dialogs_)
	{
		string text = dialg.second->dialogName_;
		int id = dialg.second->id_;

		auto b = new UIButton<DialogEditorState*>();
		addBasicButton(text, 10+buttonPadding, buttonPadding, (h * i), h, columnW - 2 * buttonPadding, *b);
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
void DialogEditorState::addBasicButton(std::string& text, int x, int buttonPadding, int y, int h, int w, UIButton<DialogEditorState*>& but)
{
	std::function<void()>a = []() {};
	std::function<void(DialogEditorState*)>b = [](DialogEditorState* s) { };
	auto button = new UIButton<DialogEditorState*>(entityManager_, x + buttonPadding, y + buttonPadding + h, w, h,SDL_Color{ COLOR(light) }, text, 2, -2, buttonFont, b, this);
	SDL_Color overColor = SDL_Color{ COLOR(lighter) };
	SDL_Color baseColor = SDL_Color{ COLOR(light) };

	a = [button, overColor]() {button->setColor(overColor); };
	button->setMouseOverCB(a);
	a = [button, baseColor]() {button->setColor(baseColor); };
	button->setMouseOutCB(a);
	but = *button;
}


void DialogEditorState::selectDialog(size_t id)
{
	actualDialog = game_->getStoryManager()->dialogs_[id];
	dialogId_ = actualDialog->id_;
	showOptions();
	int i = 0;
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
		but->disable();
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

		acumH -= button->getH();
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
	textBox_->enable();
}

void DialogEditorState::updateDialogText()
{
	textBox_->setText(actualOption->lines_[lineIndex_].line_);
	textBox_->setTitle(actualOption->lines_[lineIndex_].actorName_);
}

void DialogEditorState::editDialogText()
{
	textBox_->edit(this);
	statusB->setText("Editing...");
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
	statusB->setText("Save changes");
	statusB->setCB([](DialogEditorState* s) { s->saveCurrentDialog(); }, this);
	statusB->enableClick();
	SDL_Color base = { COLOR(0x77dd77ff) };
	SDL_Color highlighted = { COLOR(0x88ee88ff) };
	auto b = statusB;
	statusB->setMouseOutCB([base, b]() {b->setColor(base); });
	statusB->setMouseOverCB([highlighted, b]() {b->setColor(highlighted); });
	statusB->setColor(base);
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
	eText_->addComponent<InputText<DialogEditorState*>>(GETCMP2(eText_, Text), [](DialogEditorState* des) {des->endTextEdit(); }, s);
};