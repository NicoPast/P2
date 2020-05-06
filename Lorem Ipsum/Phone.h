#pragma once
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"
#include "ButtonOneParametter.h"
#include "Rectangle.h"
#include "Tween.h"
#include "LimitedVerticalScroll.h"
#include "StoryManager.h"
#include "checkML.h"

class Phone :
	public Component
{
public:
	Phone(StoryManager* sm);
	virtual ~Phone() { 
		destroyMessagesMenu();
	};

	void init();
	void initIcons(vector<Transform*> icons) { icons_ = icons; };
	void update();
	void move(bool up);
	bool inUse() { return inUse_; };
	void hideIcons() {
		for (auto& icon : icons_)icon->getEntity()->setActive(false);
	};

	void showContacts();
	StoryManager* getStoryManager() { return sm_; };

private:
	//void addBasicButton(string text, int x, 0, int y, int h, int w, *b);
	void setDir(Vector2D dir);
	void stop();

	bool inUse_ = false;
	bool moving_ = false;
	double top_ = 200;
	double bottom_ = 480;
	double speed_ = 9;
	Transform* tr_;
	vector<Transform*> icons_;
	bool messages_ = false;
	Transform* contactsTr_;
	vector<Actor*> actors_;
	StoryManager* sm_;

	//Clases de UI para que no se me vaya la cabeza
	class UIPanel
	{
	public:
		UIPanel(EntityManager* em, int x, int y, int w, int h, SDL_Color c) {
			em_ = em; e_ = em->addEntityInQueue(3); e_->addComponent<Transform>(x, y, w, h);
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
			eText_ = em_->addEntityInQueue(1);
			Transform* tr = GETCMP2(e_, Transform);
			eText_->addComponent<Transform>(tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH());
			eText_->addComponent<Text>(t, Vector2D(xOffset, yOffset) + tr->getPos(), w, f, 0);
		}
		void setChildren(Transform* t, Text* text = nullptr) { t->setParent(GETCMP2(e_, Transform)); if (text != nullptr)textChildren.push_back(text); };
		void setText(string t) { GETCMP2(eText_, Text)->setText(t); }
		void setColor(SDL_Color c) { GETCMP2(e_, Rectangle)->setColor(c); };

 		void enable() { e_->setActive(true); if (eText_ != nullptr)eText_->setActive(true); };
		void disable() { e_->setActive(false); if (eText_ != nullptr)eText_->setActive(false); };

		void setHideenPos(double x, double y) { e_->addComponent<Tween>(x, y, 15.0); }
		void hide() { if (!e_->hasComponent(ecs::Tween)) { e_->addComponent<Tween>(); } else  GETCMP2(e_, Tween)->play(); };
		void show() { GETCMP2(e_, Tween)->play(); for (auto t : textChildren) t->setPos(GETCMP2(e_, Tween)->getInitalPos()); };

		void edit(Phone* des);
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
			int textPaddingLeft, int textPaddingTop, Resources::FontId font, CB click, T param, int layer = 3) : x_(x), y_(y), w_(w), h_(h),
			textLeftPadding_(textPaddingLeft), textTopPadding_(textPaddingTop)
		{
			e_ = em->addEntity(layer);
			e_->addComponent<Transform>(x, y, w, h);
			e_->addComponent<Rectangle>(rectColor)->setBorder(SDL_Color{COLOR(0x000000ff)});
			e_->addComponent<Text>(text, Vector2D(x + textPaddingLeft, y + textPaddingTop), w - (2 * textPaddingLeft), font, 0);
			e_->addComponent<ButtonOneParametter<T>>(click, param);
		};
		~UIButton() {};

		void enable() { e_->setActive(true); };
		void disable() { e_->setActive(false); };
		bool isActive() { return e_->getActive(); }
		void setParent(UIPanel* p)
		{
			Transform* tr(GETCMP2(e_, Transform));
			Text* te = GETCMP2(e_, Text);
			Vector2D prevP(tr->getPos() - te->getPos());
			p->setChildren(tr);
			tr->setPos(tr->getPos());
			te->setPos(tr->getPos() + prevP);
		}

		int getX() { return x_; }
		int getY() { return y_; }
		int getW() { return w_; }
		int getH() { return h_; };
		string getText()
		{
			if (e_ != nullptr && e_->hasComponent(ecs::Text))
			{
				return GETCMP2(e_, Text)->getText();
			}
			return "";
		};
		Transform* getTransform() { return GETCMP2(e_, Transform); }
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
		void setBorder(SDL_Color c) { GETCMP2(e_, Rectangle)->setBorder(c); };

		void setCB(CB newClick, T param) { static_cast<ButtonOneParametter<T>*>(GETCMP2(e_, Button))->setCallback(newClick, param); };
		LimitedVerticalScroll* createScroll(SDL_Rect limit, vector<Transform*> elements, double tolerance, SDL_Color barColor, SDL_Color indicatorColor)
		{
			return e_->addComponent<LimitedVerticalScroll>(limit, elements, tolerance, barColor, indicatorColor);
		}
		void disableClick() { GETCMP2(e_, Button)->setEnabled(false); };
		void enableClick() { GETCMP2(e_, Button)->setEnabled(true); };
		void setMouseOverCB(emptyCB mouseOver) { static_cast<ButtonOneParametter<T>*>(GETCMP2(e_, Button))->setMouseOverCallback(mouseOver); }
		void setMouseOutCB(emptyCB mouseOut) { static_cast<ButtonOneParametter<T>*>(GETCMP2(e_, Button))->setMouseOutCallback(mouseOut); }
		void setText(string t) { GETCMP2(e_, Text)->setText(t); }
		
	private:


		void resize() {
			Transform* tr = GETCMP2(e_, Transform);
			tr->setPos(x_, y_);
			tr->setWH(w_, h_);
			if (e_->hasComponent(ecs::Text))
			{
				GETCMP2(e_, Text)->setPos(tr->getPos() + Vector2D(textLeftPadding_, textTopPadding_));
			}
		};
		/**/
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
	};/**/

	vector<Phone::UIButton<Phone*>*> createDropdown(vector<Actor*>& actors, string text, int x, int y, int w, int h, bool up);
	void destroyMessagesMenu();
	void hideContacts();


	UIPanel* panel_ = nullptr;
	vector<Phone::UIButton<Phone*>*> dropdown_;
};

