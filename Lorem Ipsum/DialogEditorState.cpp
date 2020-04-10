#include "LoremIpsum.h"
#include "DialogEditorState.h"
#include "DialogComponent.h"
#include "jute.h"

#include <iostream>
#include <fstream>
#include "SDL_Macros.h"

#include "DialogSystem.h"
#include "InputText.h"
DialogEditorState::~DialogEditorState()
{ 
	cout << file.to_string() << endl;
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

	//int dialogOptionConfigH = 4 * (columnH/5.0);

	new UIPanel(entityManager_, 0, 0, windowW, windowH, SDL_Color{ COLOR(light) });
	dialogsPanel=new UIPanel(entityManager_, paddingPanels, paddingPanels, columnW, columnH, SDL_Color{ COLOR(base) });
	dialogsPanel->setHideenPos(-(columnW + paddingPanels), paddingPanels);

	configurationPanel = new UIPanel(entityManager_, (3 * paddingPanels) + columnW, paddingPanels, columnW, columnH, SDL_Color{ COLOR(base) });
	configurationPanel->setHideenPos((3 * paddingPanels) + columnW, (-columnH - paddingPanels));

	optionsPanel = new UIPanel(entityManager_, (5 * paddingPanels) + 2 * columnW, 15, columnW, columnH, SDL_Color{COLOR(base)});
	optionsPanel->setHideenPos(windowW + columnW , 15);

	new UIPanel(entityManager_, 15, columnH + (2 * paddingPanels), panelW, panelH, SDL_Color{ COLOR(base) });
	textBox_ = new UIPanel(entityManager_, 2*paddingPanels, columnH+(3*paddingPanels), panelW-30, panelH-30, SDL_Color{COLOR(light)});
	textBox_->addTitle(2 * paddingPanels, 5, panelW - 2 * paddingPanels, buttonFont, "nombre");
	textBox_->addText(3*paddingPanels,35,panelW-2*paddingPanels,buttonFont, "TextoDialogoTextoDialogoTextoDialogoTextoDialogoTextoDialogoTextoDialogoTextoDialogoTextoDialogoTextoDialogoTextoDialogoTextoDialogo");
	//textBox_->disable();
	
	addDialogButtons(paddingPanels, paddingPanels, columnH, columnW);
	addOptionsButtons(columnW, columnH, (2 * columnW) + (5 * paddingPanels), paddingPanels);

	constexpr int littlebutSize = 30;
	constexpr int littlebutPadding = 6;
	SDL_Color darkerColor{ COLOR(darker) };

	nextLineB = new UIButton<DialogEditorState*>();
	string estoSeraUnaImg = ">";
	addBasicButton(estoSeraUnaImg, (panelW - paddingPanels) - (littlebutPadding), 0, windowH - (panelH+2*paddingPanels), littlebutSize, littlebutSize, *nextLineB);
	nextLineB->setCB([](DES* s) {s->nextLine(); }, this);
	UIButton<DialogEditorState*>* b = nextLineB;
	nextLineB->setMouseOutCB([darkerColor, b]() {b->setColor(darkerColor); });
	nextLineB->setColor(SDL_Color{ COLOR(darker) });
	nextLineB->disable();

	prevLineB = new UIButton<DialogEditorState*>();
	string estoSeraOtraImg = "<";
	addBasicButton(estoSeraOtraImg, (panelW - paddingPanels) - (littlebutSize+littlebutPadding), 0, windowH-(panelH+2*paddingPanels), littlebutSize, littlebutSize, *prevLineB);
	prevLineB->setCB([](DES* s) {s->prevLine(); }, this);
	prevLineB->setColor(SDL_Color{ COLOR(darker) });
	b = prevLineB;
	prevLineB->setMouseOutCB([darkerColor, b]() {b->setColor(darkerColor); });
	prevLineB->disable();


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
		string text = dialg.first;
		auto b = new UIButton<DialogEditorState*>();
		addBasicButton(text, 10+buttonPadding, buttonPadding, (h * i), h, columnW - 2 * buttonPadding, *b);
		b->setCB([text](DialogEditorState* s) {s->selectDialog(text); }, this);
		i++;
		b->setParent(dialogsPanel);
	}
}
void DialogEditorState::addBasicButton(std::string& text, int x, int buttonPadding, int y, int h, int w, UIButton<DialogEditorState*>& but)
{
	std::function<void()>a = []() {};
	std::function<void(DialogEditorState*)>b = [text](DialogEditorState* s) { };
	auto button = new UIButton<DialogEditorState*>(entityManager_, x + buttonPadding, y + buttonPadding + h, w, h,SDL_Color{ COLOR(light) }, text, 2, -2, buttonFont, b, this);
	SDL_Color overColor = SDL_Color{ COLOR(lighter) };
	SDL_Color baseColor = SDL_Color{ COLOR(light) };

	a = [button, overColor]() {button->setColor(overColor); };
	button->setMouseOverCB(a);
	a = [button, baseColor]() {button->setColor(baseColor); };
	button->setMouseOutCB(a);
	but = *button;
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
		addBasicButton(text, 0 , buttonPadding, (h * i), h, columnW-2*buttonPadding, *button);
		button->disable();
		optionsContainer.push_back(button);
		button->setParent(optionsPanel);
		button->setX(buttonPadding);
		button->disable();
	}

}

void DialogEditorState::selectDialog(string name)
{
	file = parser::parse_file(FILEDIR + name + ".dialog");
	actualDialog = &game_->getStoryManager()->dialogs_[name];
	showOptions();
}

void DialogEditorState::showOptions()
{
	int i = 0;
	int acumH = 0;
	for (auto& option : actualDialog->options_)
	{
		auto button = optionsContainer[i];
		string text = option.startLine_;
		if (text == "")text = "Primera conversación(saludo)";
		DialogOption* d = &option;
		SDL_Color clicked{ COLOR(dark) };
		SDL_Color baseC{ COLOR(light) };
		std::function<void(DialogEditorState*)>b = [text, i, button, clicked, baseC](DialogEditorState* s) {
			s->setDialogOption(i); button->setColor(clicked);
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

int DialogEditorState::getXOffsetToCenterHorizontallyInContainer(int& charW, int& charH, int containerW, int textPadding, std::string& text)
{
	auto font = game_->getGame()->getFontMngr()->getFont(buttonFont);
	TTF_SizeText(font->getTTF_Font(), "a", &charW, &charH);
	int xoff = ((containerW - (int)2 * textPadding) - text.size() * charW) / 2; //centers de text in button
	return xoff;
}

void DialogEditorState::setDialogOption(int index)
{
	int i = 0;
	for (auto& b : optionsContainer)
	{
		if (i != index)
		{
			SDL_Color baseC{ COLOR(light) };
			SDL_Color overC{ COLOR(lighter) };
			b->setColor(baseC);
			b->setMouseOverCB([overC, b]() {b->setColor(overC); });
			b->setMouseOutCB([baseC, b]() {b->setColor(baseC); });
		}
		else if (i == index)
		{
			b->setMouseOutCB([]() {});
			b->setMouseOverCB([]() {});
		}
		i++;
	}
	actualOption = &actualDialog->options_[index];

	lineIndex_ = 0;
	updateDialogText();
	nextLineB->enable();
	prevLineB->enable();
	textBox_->enable();
}
void DialogEditorState::updateDialogText()
{
	textBox_->setText(actualOption->lines_[lineIndex_].line_);
}

