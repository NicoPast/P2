#pragma once
#include "State.h"
#include "SDL_macros.h"
#include "ButtonOneParametter.h"
#include "jute.h"

class Rectangle;
class LoremIpsum;
using color = unsigned long;
using editorCallback = std::function<void(DialogEditorState*)>;
class DialogEditorState :
	public State
{
public:
	const string FILEDIR = "../assets/dialogs/";
	enum firstOptionState : size_t {none=0, on, off};

	DialogEditorState(LoremIpsum* li) : State(li) { init(); };
	virtual ~DialogEditorState();


	void addDialog();
	void selectDialog(string name);
	void newDialogNameSet();
	void addOptionsButtons(int columnW, int columnH, int x, int h);
	void setActualOption(DialogOption* op, Rectangle* r);
	void nextLine() { if (lineIndex < actualOption->lines_.size() - 1) { lineIndex++; updateDialogText(); } };
	void prevLine() { if (lineIndex > 0) { lineIndex--; updateDialogText(); } };
	
	
	void setFirstOption(firstOptionState state);
	firstOptionState option1State;
private:
	jValue file;
	Dialog* actualDialog = nullptr;
	string dialogName;
	DialogOption* actualOption = nullptr;
	int lineIndex = 0;

	void init();
	void updateDialogText();
	void addDialogButtons(int columnH, int columnW);
	void addDialogConfigurationOptions(int columnH, int columnW, int y);
	void addOptionConfigurationButtons(int columnH, int columnW);
	int getXOffsetToCenterHorizontallyInContainer(int& charW, int& charH, int containerW, int textPadding, std::string& text);

	void setRect(Entity* e, int x, int y, int w, int h, 
				 string text, int textXOffset, int textYOffset,
			     SDL_Color color = {COLOR(0xffffffff)},
				 Resources::FontId fontID = Resources::RobotoTest24,
				 int textSpeed=0);
	

	void updateOptions();
	//void addDialog();
	template<typename T>
	void setButton(Entity* e, std::function<void(T)>callback, T param);

	Entity* bottomPanel = nullptr;

	Entity* firstColumn = nullptr;
	Entity* secondColumn = nullptr;
	Entity* thirdColumn = nullptr;

	Entity* addDialogButton_ = nullptr;

	Entity* linePanel_ = nullptr;
	Entity* nameDisplay = nullptr;
	Entity* nextLineButton = nullptr;
	Entity* prevtLineButton = nullptr;

	Entity* firstOptionOnRect = nullptr; 
	Entity* firstOptionOffRect = nullptr;

	Entity* configurationBackgroundPanel = nullptr;


	vector<Entity*> dialogConfigurationContainer;
	vector<Entity*> optionConfigurationContainer;
	vector<Entity*> optionsContainer;
	vector<Entity*> dialogPreviewContainer;


	color lighter = 0xFFCDB2FF;
	color light = 0xFFB4A2FF;
	color base = 0xE5989BFF;
	color dark = 0xB5838DFF;
	color darker = 0x6D6875FF;
	Resources::FontId buttonFont = Resources::RobotoTest24;

};

template<typename T>
inline void DialogEditorState::setButton(Entity* e, std::function<void(T)>callback, T param)
{
	e->addComponent<ButtonOneParametter<T>>(callback, param);
}
