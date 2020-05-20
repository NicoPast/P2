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
		for (auto& icon : icons_)
			icon->getEntity()->setActive(false);
	};

	void showContacts();
	void hide() 
	{ 
		entity_->getComponent<Tween>(ecs::Tween)->GoToA(); 
		hideContacts();
		auto but = entity_->getComponent<ButtonOneParametter<int>>(ecs::Button);
		Transform* mobTr = tr_;
		but->setMouseOverCallback([mobTr]() {mobTr->setPosY(mobTr->getPos().getY() - 5); });
		but->setMouseOutCallback([mobTr]() {mobTr->setPosY(mobTr->getPos().getY() + 5); });
		entity_->getComponent<Sprite>(ecs::Sprite)->setTexture(game_->getTextureMngr()->getTexture(Resources::PhoneOff));
		hideIcons();
	};
	void show() { entity_->getComponent<Tween>(ecs::Tween)->GoToB();  enableIcons();
	auto but = entity_->getComponent<ButtonOneParametter<int>>(ecs::Button);
	but->setMouseOverCallback([]() {});
	but->setMouseOutCallback([]() {});
	};
	StoryManager* getStoryManager() { return sm_; };
	void hideContacts();
	void notication() { newNotification = true; vibrationAnimCount = 0; SDLGame::instance()->getAudioMngr()->playChannel(Resources::Buzz,1,0); }
private:
	//void addBasicButton(string text, int x, 0, int y, int h, int w, *b);
	void setDir(Vector2D dir);
	void stop();

	bool newNotification = false;
	int vibrationAnimCount = 0;
	bool inUse_ = false;
	bool moving_ = false;
	double top_ = 200;
	double bottom_ = 480;
	double speed_ = 9;
	Transform* tr_ = nullptr;
	vector<Transform*> icons_;
	bool messages_ = false;
	Transform* contactsTr_ = nullptr;
	vector<Actor*> actors_;
	StoryManager* sm_ = nullptr;
	void disableIcons() { for (auto i : icons_) { i->getEntity()->getComponent<ButtonOneParametter<LoremIpsum*>>(ecs::Button)->setEnabled(false); } };
	void enableIcons() { for (auto i : icons_) { i->getEntity()->getComponent<ButtonOneParametter<LoremIpsum*>>(ecs::Button)->setEnabled(true); } };


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
			e_ = em->addEntityInQueue(4);
			e_->addComponent<Transform>(x, y, w, h);
			e_->addComponent<Rectangle>(rectColor);
			e_->addComponent<Sprite>(texture);
			e_->addComponent<ButtonOneParametter<T>>(click, param);

		};
		//Con texto, serán los más grandes
		UIButton(EntityManager* em, int x, int y, int w, int h, SDL_Color rectColor, string text,
			int textPaddingLeft, int textPaddingTop, Resources::FontId font, CB click, T param, int layer = 4) : x_(x), y_(y), w_(w), h_(h),
			textLeftPadding_(textPaddingLeft), textTopPadding_(textPaddingTop)
		{
			e_ = em->addEntityInQueue(layer);
			e_->addComponent<Transform>(x, y, w, h);
			e_->addComponent<Rectangle>(rectColor)->setBorder(SDL_Color{COLOR(0x000000ff)});
			e_->addComponent<Text>(text, Vector2D(x + textPaddingLeft, y + textPaddingTop), w - (2 * textPaddingLeft), font, 0);
			e_->addComponent<ButtonOneParametter<T>>(click, param);
		};
		~UIButton() {};

		void enable() { e_->setActive(true); };
		void disable() { e_->setActive(false); };
		bool isActive() { return e_->getActive(); }

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
		int id_ = 0;
		int x_ = 0;
		int y_ = 0;
		int w_ = 0;
		int h_ = 0;

		int textLeftPadding_ = 0;
		int textTopPadding_ = 0;

		int index_ = -1;

		Entity* e_= nullptr;
		emptyCB mouseOverFunc_;
		CB mouserOverFunc_;
	};/**/

	vector<Phone::UIButton<Phone*>*> createDropdown(vector<Actor*>& actors, string text, int x, int y, int w, int h, bool up);
	void destroyMessagesMenu();

	vector<Phone::UIButton<Phone*>*> dropdown_;
};

