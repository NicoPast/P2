#pragma once
#include "Button.h"
#include <functional>

template <typename T>
class ButtonOneParametter : public Button
{
public:
	ButtonOneParametter(std::function<void(T)> f, T param) : Button(), f_(f), param_(param){};
	virtual ~ButtonOneParametter() {};

	void setCallback(std::function<void(T)> f, T param) { f_ = f; param_ = param; };
	void setMouseOverCallback(std::function<void()>f) { mouseOverF_ = f; hasMouseOverFunc_ = true; };
	void setMouseOutCallback(std::function<void()>f) { mouseOutF_ = f;};

	virtual void update()
	{
		InputHandler* ih = InputHandler::instance();
		if (hasMouseOverFunc_ && ih->mouseMotionEvent() && !ih->mouseButtonEvent())
		{
			int mouseX = (int)ih->getMousePos().getX();
			int mouseY = (int)ih->getMousePos().getY();
			int x = (int)(GETCMP1_(Transform)->getPos().getX()) - xOffset_;
			int y = (int)(GETCMP1_(Transform)->getPos().getY()) - yOffset_;
			int w = (int)(GETCMP1_(Transform)->getW()) - wOffset_;
			int h = (int)(GETCMP1_(Transform)->getH()) - hOffset_;
			const SDL_Point p{ mouseX,mouseY };
			const SDL_Rect r{ x, y, w, h };
			if (SDL_PointInRect(&p, &r) && !mouseOver_)
			{
				mouseOverF_();
				mouseOver_ = true;
			}
			else if (!SDL_PointInRect(&p, &r) && mouseOver_)
			{
				mouseOutF_();
				mouseOver_ = false;
			}
		}
		Button::update();
	};
	void simulateClick()
	{
		callback();
	}
protected:
	void callback() override
	{
		f_(param_);
	};
	bool mouseOver_ = false;
	bool hasMouseOverFunc_ = false;
	std::function<void(T)> f_;
	std::function<void()> mouseOverF_;
	std::function<void()> mouseOutF_;
	T param_;
};