#pragma once
#include "State.h"
#include "SDL_macros.h"
#include "ButtonOneParametter.h"
#include "jute.h"
#include "DialogEditorState.h"
#include "DialogComponent.h"
#include "Text.h"
#include "InputText.h"
#include "Tween.h"
class Rectangle;
class LoremIpsum;

using color = unsigned long;
using editorCallback = std::function<void(DialogEditorState*)>;
class DialogEditorState :
	public State
{
	using DES = DialogEditorState;
public:
	const string FILEDIR = "../assets/dialogs/";
	enum firstOptionState : size_t {none=0, on, off};

	DialogEditorState(LoremIpsum* li) : State(li) { init(); };
	virtual ~DialogEditorState();


	void addDialog(int numeroMagico);
	void addDialogOption(int numeroMagico);
	void selectDialog(size_t id);
	void showOptions();
	void newDialogNameSet();
	void addOptionsButtons(int columnW, int columnH, int x, int h);
	void setDialogOption(int index);
	void nextLine() { if (lineIndex_ < actualOption->lines_.size() - 1) { lineIndex_++; updateDialogText(); } };
	void prevLine() { if (lineIndex_ > 0) { lineIndex_--; updateDialogText(); } };
	void editDialogText();
	void saveCurrentDialog();
	void endTextEdit();

	
	void setFirstOption(firstOptionState state);
	firstOptionState option1State;
private:
	//Clases de UI para que no se me vaya la cabeza
	class UIPanel
	{
	public:
		UIPanel(EntityManager* em, int x, int y, int w, int h, SDL_Color c) {
			em_ = em; e_ = em->addEntity(0); e_->addComponent<Transform>(x, y, w, h);
			e_->addComponent<Rectangle>(c);
		};
		~UIPanel() {};
		void addTitle(int xOffset, int yOffset, int w, Resources::FontId f, string t)
		{
			Transform* tr = GETCMP2(e_, Transform);
			e_->addComponent<Text>(t, Vector2D(xOffset, yOffset) + tr->getPos(), w, f, 0);
		};
		void setTitle(string t) { GETCMP2(e_, Text)->setText(t); }
		//xOffset e yOffset son los pixeles que se va a mover el texto relativo al panel.
		void addText(int xOffset, int yOffset, int w, Resources::FontId f, string t)
		{
			eText_ = em_->addEntity(1);
			Transform* tr = GETCMP2(e_, Transform);
			eText_->addComponent<Transform>(0,0,100,100);
			eText_->addComponent<Text>(t, Vector2D(xOffset, yOffset) + tr->getPos(), w, f, 0);
		}
		void setChildren(Transform* t, Text* text = nullptr) { t->setParent(GETCMP2(e_, Transform)); if (text != nullptr)textChildren.push_back(text); };
		void setText(string t) { GETCMP2(eText_, Text)->setText(t); }
		void setColor(SDL_Color c) { GETCMP2(e_, Rectangle)->setColor(c); };

		void enable() { e_->setActive(true); if (eText_!=nullptr)eText_->setActive(true); };
		void disable() { e_->setActive(false); if (eText_ != nullptr)eText_->setActive(false); };

		void setHideenPos(double x, double y){ e_->addComponent<Tween>(x,y,15.0); }
		void hide() { if (!e_->hasComponent(ecs::Tween)) { e_->addComponent<Tween>(); } else  GETCMP2(e_, Tween)->play();};
		void show() { GETCMP2(e_, Tween)->play(); for (auto t : textChildren) t->setPos(GETCMP2(e_, Tween)->getInitalPos()); };

		void edit(DialogEditorState* des);
		string getText() { return GETCMP2(eText_, Text)->getText(); }
		string getFullText()
		{
			auto vec = GETCMP2(eText_, Text)->getLines();
			string ret;
			for (string& s : vec)
				ret += s;
			return ret;
		}
		private:
		EntityManager* em_ = nullptr;
		Entity* e_ = nullptr;
		string title_;
		
		vector<Text*>textChildren;

		Entity* eText_ = nullptr;
		string text_;
	};

	template <typename T>
	class UIButton
	{
		using CB = std::function<void(T)>;
		using emptyCB = std::function<void()>;
	public:
		UIButton() {};
		//Con sprite, en general serán pequeños
		UIButton(EntityManager* em, int x, int y, int w, int h, 
			SDL_Color rectColor, Texture* texture, CB click, T param) :x_(x), y_(y), w_(w), h_(h)
		{
			e_ = em->addEntity(1);
			e_->addComponent<Transform>(x, y, w, h);
			e_->addComponent<Rectangle>(rectColor);
			e_->addComponent<Sprite>(texture);
			e_->addComponent<ButtonOneParametter<T>>(click, param);

		};
		//Con texto, serán los más grandes
		UIButton(EntityManager* em, int x, int y, int w, int h, SDL_Color rectColor, string text,
			int textPaddingLeft, int textPaddingTop, Resources::FontId font, CB click, T param) : x_(x), y_(y), w_(w), h_(h),
			textLeftPadding_(textPaddingLeft), textTopPadding_(textPaddingTop)
		{
			e_ = em->addEntity(1);
			e_->addComponent<Transform>(x, y, w, h);
			e_->addComponent<Rectangle>(rectColor);
			e_->addComponent<Text>(text, Vector2D(x + textPaddingLeft, y + textPaddingTop), w - (2 * textPaddingLeft), font, 0);
			e_->addComponent<ButtonOneParametter<T>>(click, param);
		};
		~UIButton() {};

		void enable() { e_->setActive(true); };
		void disable() { e_->setActive(false); };

		void setParent(UIPanel* p) 
		{
			Transform* tr(GETCMP2(e_, Transform));
			Text* te = GETCMP2(e_, Text);
			Vector2D prevP(tr->getPos() - te->getPos());
			p->setChildren(tr);
			te->setPos(tr->getPos()+prevP);
		}

		int getX() { return x_; }
		int getY() { return y_; }
		int getW() { return w_; }
		int getH() { return h_; };
		string getText()
		{
			if (e_!=nullptr && e_->hasComponent(ecs::Text))
			{
				return GETCMP2(e_, Text)->getText();
			}
			return "";
		};

		void setX(int n) { x_ = n; resize(); }
		void setY(int n) { y_ = n; resize(); }
		void setXY(int x, int y) { x_ = x; y_ = y; resize(); }

		void setIndex(int i) { index_ = i; };
		int getIndex() { return index_; };
		int getID() { return id_; }
		int setID(int id) { id_ = id; }


		void setW(int n) { w_ = n; resize(); }
		void setH(int n) { h_ = n; resize(); }
		void setWH(int w, int h) { w_ = w; h_ = h; resize(); }

		void setXYWH(int x, int y, int w, int h) { x_ = x; y_ = y; w_ = w; h_ = h; resize(); }

		void adjustHeightBasedOnText()
		{
			setH(GETCMP2(e_, Text)->getCharH() * GETCMP2(e_, Text)->getNumLines());
		}
		void setColor(SDL_Color c) { GETCMP2(e_, Rectangle)->setColor(c); };
		void setCB(CB newClick, T param) { static_cast<ButtonOneParametter<T>*>(GETCMP2(e_, Button))->setCallback(newClick, param); }

		void disableClick() { GETCMP2(e_, Button)->setEnabled(false); };
		void enableClick() { GETCMP2(e_, Button)->setEnabled(true); };
		void setMouseOverCB(emptyCB mouseOver) { static_cast<ButtonOneParametter<T>*>(GETCMP2(e_, Button))->setMouseOverCallback(mouseOver); }
		void setMouseOutCB(emptyCB mouseOut) { static_cast<ButtonOneParametter<T>*>(GETCMP2(e_, Button))->setMouseOutCallback(mouseOut); }
		void setText(string t) { GETCMP2(e_, Text)->setText(t); }
	private:
		void resize() {
			Transform* tr= GETCMP2(e_, Transform);
			tr->setPos(x_, y_);
			tr->setWH(w_, h_); 
			if (e_->hasComponent(ecs::Text))
			{
				GETCMP2(e_, Text)->setPos(tr->getPos() + Vector2D(textLeftPadding_, textTopPadding_));
			}
		};

		int id_;
		int x_;
		int y_;
		int w_;
		int h_;

		int textLeftPadding_ = 0;
		int textTopPadding_ = 0;

		int index_ = -1;

		Entity* e_;
		emptyCB mouseOverFunc_;
		CB mouserOverFunc_;
	};

	jValue json;
	Dialog* actualDialog = nullptr;
	int dialogId_ = -1;
	//string dialogName_ = "";

	DialogOption* actualOption = nullptr;
	int actualOptionIndex=-1;
	int lineIndex_ = 0;
	UIPanel* textBox_ = nullptr;
	UIPanel* optionsPanel = nullptr;
	UIPanel* statusPanel = nullptr;
	UIButton<DialogEditorState*>* statusB;

	UIPanel* configurationPanel = nullptr;
	UIPanel* dialogsPanel = nullptr;
	virtual void init();
	void updateDialogText();
	void addDialogButtons(int x, int w, int columnH, int columnW);
	void addBasicButton(std::string& text, int x, int buttonPadding, int y, int h, int columnW, UIButton<DialogEditorState*>& button );
	void addDialogConfigurationOptions(int columnH, int columnW, int y);
	void addOptionConfigurationButtons(int columnH, int columnW);

	void setRect(Entity* e, int x, int y, int w, int h, 
				 string text, int textXOffset, int textYOffset,
			     SDL_Color color = {COLOR(0xffffffff)},
				 Resources::FontId fontID = Resources::RobotoTest24,
				 int textSpeed=0);
	

	void updateOptions();
	void desableOptions();

	//void addDialog();
	void setMouseOverCBs(DialogEditorState::UIButton<DialogEditorState*>*& b)
	{
		SDL_Color baseC{ COLOR(light) };
		SDL_Color overC{ COLOR(lighter) };
		b->setColor(baseC);
		b->setMouseOverCB([overC, b]() {b->setColor(overC); });
		b->setMouseOutCB([baseC, b]() {b->setColor(baseC); });
	};
	void clearMouseOverCBs(DialogEditorState::UIButton<DialogEditorState*>*& b)
	{
		b->setMouseOutCB([]() {});
		b->setMouseOverCB([]() {});
	};






	template<typename T>
	void setButton(Entity* e, std::function<void(T)>callback, T param);


	vector<Entity*> dialogConfigurationContainer;
	vector<Entity*> optionConfigurationContainer;


	vector<UIButton<DialogEditorState*>*> optionsContainer;
	vector<UIButton<DialogEditorState*>*> dialogsContainer;
	vector<Entity*> dialogPreviewContainer;

	UIButton<DialogEditorState*>* nextLineB;
	UIButton<DialogEditorState*>* prevLineB;
	UIButton<DialogEditorState*>* editLineB;

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
