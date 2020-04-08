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

};

void DialogEditorState::init()
{
	int windowW = game_->getGame()->getWindowWidth();
	int windowH = game_->getGame()->getWindowHeight();

	int panelH = 2*windowH / 7;
	int panelW = windowW;

	int columnW = windowW / 3;
	int columnH = windowH - panelH;

	int dialogOptionConfigH = 4 * (columnH/5.0);

	firstColumn  = entityManager_->addEntity(0);
	secondColumn = entityManager_->addEntity(0);
	thirdColumn  = entityManager_->addEntity(0);
	
	bottomPanel = entityManager_->addEntity(0);

	setRect(firstColumn, 0, 0, columnW, columnH, "Selecciona Diálogo:...........................................................................................................", 15, 15, SDL_Color{ COLOR(lighter) });
	setRect(secondColumn, columnW, 0, columnW, columnH, "Configuración de Diálogo:", 5, 15, SDL_Color{ COLOR(lighter) });
	setRect(thirdColumn, 2 * columnW, 0, columnW, columnH, "Seleciona Opción:", 15, 15, SDL_Color{ COLOR(lighter) });





#pragma region dialog
	//Mover a una función cuando no tenga pereza máxima
	setRect(bottomPanel, 0, columnH, panelW, panelH, "", 15, 15, SDL_Color{ COLOR(lighter) });

	Entity* dialogPanel = entityManager_->addEntity(0);
	setRect(dialogPanel, 5, columnH, panelW - 10, panelH - 5, "", 15, 15, SDL_Color{ COLOR(base) });

	nameDisplay = entityManager_->addEntity(0);
	setRect(nameDisplay, 15, columnH + 15, 150, 30, "Nombre: ", 5, -2, SDL_Color{ COLOR(dark) });

	Transform* tr = GETCMP2(bottomPanel, Transform);

	std::function<void(DialogEditorState*)>func;

	nextLineButton = entityManager_->addEntity(0);
	setRect(nextLineButton, (tr->getW() - 15) - 40, columnH + 50 - 30 - 5, 30, 30, ">", 8, -3, SDL_Color{ COLOR(dark) });
	nextLineButton->setActive(false);
	func = [](DialogEditorState* s) {s->nextLine(); };
	setButton<DialogEditorState*>(nextLineButton, func, this);

	prevtLineButton = entityManager_->addEntity(0);
	setRect(prevtLineButton, (tr->getW() - 15) - 75, columnH + 50 - 30 - 5, 30, 30, "<", 8, -3, SDL_Color{ COLOR(dark) });
	prevtLineButton->setActive(false);
	func = [](DialogEditorState* s) {s->prevLine(); };
	setButton<DialogEditorState*>(prevtLineButton, func, this);

	lineIndex = 0;
	linePanel_ = entityManager_->addEntityInQueue(0);
	tr = GETCMP2(bottomPanel, Transform);
	setRect(linePanel_, 15, tr->getPos().getY() + 30 + 15 + 5, tr->getW() - 40, tr->getH() - 60, "prueba", 5, -2, SDL_Color{ COLOR(dark) });

	dialogPreviewContainer.push_back(dialogPanel);
	dialogPreviewContainer.push_back(nameDisplay);
	dialogPreviewContainer.push_back(linePanel_);
	dialogPreviewContainer.push_back(nextLineButton);
	dialogPreviewContainer.push_back(prevtLineButton);

	for (Entity* entity : dialogPreviewContainer)
	{
		entity->setActive(false);
	}
#pragma endregion




	addDialogButtons(columnH, columnW);
	addDialogConfigurationOptions((columnH-dialogOptionConfigH),columnW,(48));
	addOptionConfigurationButtons(dialogOptionConfigH, columnW);
	addOptionsButtons(columnW, columnH, columnW * 2, 15);
}

void DialogEditorState::addOptionConfigurationButtons(int h, int w)
{
	Transform* tr = GETCMP2(secondColumn, Transform);


	Entity* secOptionTitle = entityManager_->addEntity(1);
	secOptionTitle->addComponent<Text>("Configuración de opción:", Vector2D(tr->getW()+5, 60 + tr->getH() - h), w-10, buttonFont, 0);
	optionConfigurationContainer.push_back(secOptionTitle);

	configurationBackgroundPanel = entityManager_->addEntity(0);
	setRect(configurationBackgroundPanel, tr->getW(), 55+tr->getH()-h, w, h-65, "", 0, 0, SDL_Color{ COLOR(base) });
	optionConfigurationContainer.push_back(configurationBackgroundPanel);

	for (Entity* entity : optionConfigurationContainer)
	{
		entity->setActive(false);
	}
}

void DialogEditorState::addDialogButtons(int columnH, int columnW)
{
	int i = 0;
	int numOfEntries = game_->getStoryManager()->dialogs_.size();
	int h = 30;
	if ((columnH / numOfEntries) < 30)
		throw "Hay que implementar un scroll vertical pa que no se salgan los botones de la lista de diálogos";
	string text;
	int charW, charH;
	int containerW = columnW - 30;
	int textPadding = 15;
	int xoff = 1;
	std::function<void(DialogEditorState*)>func;

	for (auto& dialg : game_->getStoryManager()->dialogs_)
	{
		Entity* entry = entityManager_->addEntity(1);
		text = dialg.first;
		xoff = getXOffsetToCenterHorizontallyInContainer(charW, charH, containerW, textPadding, text);
		setRect(entry, 15, 55 + 5 * i + h * i, columnW - 30, h, text, xoff, -2, SDL_Color{ COLOR(dark) });
		func = [text](DialogEditorState* s) {s->selectDialog(text); };
		setButton<DialogEditorState*>(entry, func, this);
		i++;
	}
	addDialogButton_ = entityManager_->addEntity(1);
	text = "Añade un diálogo";
	xoff = getXOffsetToCenterHorizontallyInContainer(charW, charH, containerW, textPadding, text);
	setRect(addDialogButton_, 15, 55 + 5 * i + h * i, containerW, h, text, xoff, -2, SDL_Color{ COLOR(light) });


	func = [](DialogEditorState* s) {s->addDialog();};
	setButton<DialogEditorState*>(addDialogButton_,func, this);

	Entity* backgroundPanel = entityManager_->addEntity(0);
	setRect(backgroundPanel, 10, 48, columnW - 20, columnH - 58, "", 0, 0, SDL_Color{ COLOR(base)});

}
void DialogEditorState::addDialogConfigurationOptions(int cH, int cW, int y)
{
	int x = cW;
	std::function<void(DialogEditorState*)> func;

	Entity* e = entityManager_->addEntity(1);
	setRect(e, x, y, cW, cH, "", 0, 0, SDL_Color{ COLOR(base) }, buttonFont);
	dialogConfigurationContainer.push_back(e);


	Entity* firstOptionTitle = entityManager_->addEntity(1);
	setRect(firstOptionTitle, x+5, y+5, cW - 10, cH-10, "Comenzar con conversación", 5, 5, SDL_Color{ COLOR(dark) }, buttonFont);
	dialogConfigurationContainer.push_back(firstOptionTitle);

	firstOptionOnRect = entityManager_->addEntity(1);
	setRect(firstOptionOnRect, (2 * cW - (135)), y + 55, 15, 15, "", 60, 0, SDL_Color{ COLOR(darker) });
	auto onRect = GETCMP2(firstOptionOnRect, Transform);
	firstOptionOnRect->addComponent<Text>("Sí", onRect->getPos()+Vector2D(30,-10), 2 * cW, buttonFont, 0);
	func = [](DialogEditorState* s) { s->setFirstOption(on); };
	setButton<DialogEditorState*>(firstOptionOnRect, func, this);
	dialogConfigurationContainer.push_back(firstOptionOnRect);

	firstOptionOffRect = entityManager_->addEntity(1);
	setRect(firstOptionOffRect, (2 * cW - (135)), y + 25, 15, 15, "", 0, 0, SDL_Color{ COLOR(darker) });
	auto offRect = GETCMP2(firstOptionOffRect, Transform);
	firstOptionOffRect->addComponent<Text>("No", offRect->getPos() + Vector2D(30, -10), 2 * cW, buttonFont, 0);
	func = [](DialogEditorState* s) { s->setFirstOption(off); };
	setButton<DialogEditorState*>(firstOptionOffRect, func, this);
	dialogConfigurationContainer.push_back(firstOptionOffRect);

	for (Entity* entity : dialogConfigurationContainer)
	{
		entity->setActive(false);
	}
}

void DialogEditorState::addOptionsButtons(int columnW, int columnH, int x, int y)
{
	int addedY = y+10;
	Entity* entity = entityManager_->addEntity(0);
	optionsContainer.push_back(entity);
	entity->setActive(false);
	setRect(entity, 10+ 2 * columnW , y+32, columnW-20, columnH-60, "", 0, 0, SDL_Color{ COLOR(base) });
	for (int i = 0; i < 10; i++)
	{
		Entity* e = entityManager_->addEntityInQueue(4);
		string name = "si este texto se ve, la liaste wey";
		setRect(e, x + 5, y, columnW - 30, 30, name, 15, -2, SDL_Color{ COLOR(dark) });
		e->setActive(false);
		optionsContainer.push_back(e);
	}
}
void DialogEditorState::setFirstOption(firstOptionState state)
{
	if (state == on)
	{
		GETCMP2(firstOptionOffRect, Rectangle)->setColor(SDL_Color{ COLOR(darker) });
		GETCMP2(firstOptionOnRect, Rectangle)->setColor(SDL_Color{ COLOR(light) });
	}
	else if (state == off)
	{
		if(actualDialog->options_[0].startLine_=="")
			
		GETCMP2(firstOptionOnRect, Rectangle)->setColor(SDL_Color{ COLOR(darker) });
		GETCMP2(firstOptionOffRect, Rectangle)->setColor(SDL_Color{ COLOR(light) });
	}
	else
	{
		GETCMP2(firstOptionOnRect, Rectangle)->setColor(SDL_Color{ COLOR(darker) });
		GETCMP2(firstOptionOffRect, Rectangle)->setColor(SDL_Color{ COLOR(darker) });
	}

}


void DialogEditorState::addDialog()
{
	Text* text = addDialogButton_->getComponent<Text>(ecs::Text);
	text->resetText();
	addDialogButton_->addComponent<InputText<DialogEditorState*>>(text, [](DialogEditorState* state) {state->newDialogNameSet(); }, this);
}

void DialogEditorState::newDialogNameSet()
{
	auto tComponent = addDialogButton_->getComponent<Text>(ecs::Text);
	auto transform = addDialogButton_->getComponent<Transform>(ecs::Transform);
	string text = tComponent->getText();
	int charW, charH;
	int containerW = firstColumn->getComponent<Transform>(ecs::Transform)->getW();
	int textPadding = 15;
	int xoff = 1;
	xoff = getXOffsetToCenterHorizontallyInContainer(charW, charH, containerW, textPadding, text);
	tComponent->setPos(transform->getPos() + Vector2D(xoff, -2));

	actualDialog = &game_->getStoryManager()->dialogs_[text];
	Transform* tr = GETCMP2(thirdColumn, Transform);
	addOptionsButtons(tr->getW(), tr->getH(), tr->getPos().getX(), tr->getPos().getY()+50);
}
void DialogEditorState::selectDialog(string name)
{
	file = parser::parse_file(FILEDIR + name + ".dialog");
	actualDialog = &game_->getStoryManager()->dialogs_[name];
	updateOptions();
	if (actualDialog->options_[0].startLine_ != "")
		setFirstOption(off);
	else 
		setFirstOption(on);
	
	Transform* tr = GETCMP2(thirdColumn, Transform);
	//addOptionsButtons(tr->getW(), tr->getH(), tr->getPos().getX(), tr->getPos().getY() + 50);
	for (Entity* entity : dialogConfigurationContainer)
	{
		entity->setActive(true);
	}
}
void DialogEditorState::updateOptions()
{	
	optionsContainer[0]->setActive(true);
	int i = 1;//saltarse el bg

	int addedY = 52;
	int colW = GETCMP2(firstColumn, Transform)->getW();
	std::function<void(DialogEditorState*)>func;
	for (auto& option : actualDialog->options_)
	{
		Entity* e = optionsContainer[i];
		Text* textComp = e->getComponent<Text>(ecs::Text);
		textComp->setColor(256, 100, 100);
		string buttonText = option.startLine_;
		if (buttonText == "")buttonText = "Conversación inicial (saludo)";
		textComp->setText(buttonText);
		int newH = textComp->getNumLines() * textComp->getCharH();
		GETCMP2(e, Transform)->setH(newH);
		Rectangle* r = GETCMP2(e, Rectangle);
		func = [&option, r](DialogEditorState* s) {s->setActualOption(&option, r);};
		setButton<DialogEditorState*>(e, func, this);
		Vector2D newPos = Vector2D(2 * colW + 15, (addedY));
		GETCMP2(e, Transform)->setPos(newPos);
		textComp->setPos(newPos+Vector2D(15, -2));
		addedY += newH+5;
		e->setActive(true);
		i++;
	}
}
void DialogEditorState::setActualOption(DialogOption* option, Rectangle* r)
{
	if(!linePanel_)
	{	
		actualOption = option;
		lineIndex = 0;
		linePanel_ = entityManager_->addEntityInQueue(0);
		Transform* tr = GETCMP2(bottomPanel, Transform);
		setRect(linePanel_, 15, tr->getPos().getY() + 30 + 15 + 5, tr->getW() - 40, tr->getH() - 60, option->lines_[0].line_, 5, -2, SDL_Color{ COLOR(dark) });
		dialogPreviewContainer.push_back(linePanel_);
	}
	else
	{
		actualOption = option;
		lineIndex = 0;
	}
	GETCMP2(linePanel_, Text)->setText(option->lines_[0].line_);
	GETCMP2(nameDisplay, Text)->setText(actualOption->lines_[lineIndex].actorName_);
	for (Entity* e : optionConfigurationContainer)
		e->setActive(true);
	for (Entity* e : dialogPreviewContainer)
		e->setActive(true);
	for (Entity* e : optionsContainer)
		GETCMP2(e, Rectangle)->setColor(SDL_Color{COLOR(dark)});
	GETCMP2(optionsContainer[0], Rectangle)->setColor(SDL_Color{ COLOR(base) });
	r->setColor(SDL_Color{ COLOR(light) });
	
}
void DialogEditorState::updateDialogText()
{
	GETCMP2(linePanel_, Text)->setText(actualOption->lines_[lineIndex].line_);
	GETCMP2(nameDisplay, Text)->setText(actualOption->lines_[lineIndex].actorName_);

}

int DialogEditorState::getXOffsetToCenterHorizontallyInContainer(int& charW, int& charH, int containerW, int textPadding, std::string& text)
{
	auto font = game_->getGame()->getFontMngr()->getFont(buttonFont);
	TTF_SizeText(font->getTTF_Font(), "a", &charW, &charH);
	int xoff = ((containerW - (int)2 * textPadding) - text.size() * charW) / 2; //centers de text in button
	return xoff;
}

void DialogEditorState::setRect(Entity* e, int x, int y, int w, int h,string text, int textXOffset, int textYOffset, SDL_Color color, Resources::FontId fontID, int textSpeed)
{
	Transform* tr = e->addComponent<Transform>(x, y, w, h);
	e->addComponent<Rectangle>(color);
	if(text!="")e->addComponent<Text>(text, Vector2D(tr->getPos().getX()+textXOffset, tr->getPos().getY() + textYOffset), tr->getW() - (2 * textXOffset), fontID, textSpeed);
}

