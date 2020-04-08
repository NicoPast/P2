#pragma once
#include "Component.h"
#include "Text.h"
#include <functional>
#include "SDL_macros.h"
template<typename T>
class InputText : public Component
{
public:
	InputText(Text* t, std::function<void(T)>f, T arg) : Component(ecs::InputText), t_(t), func_(f), arg_(arg) {  };
	virtual ~InputText() {};

protected:
	Text* t_;
	string inputString_;
	bool finished_ = false;
	size_t cursorPosition_=0;
	size_t lastBlink;
	size_t blinkDuration=500;
	bool blinking_ = false;
	void executeCallback(T margs)
	{
		func_(margs);
	}
	std::function<void(T)> func_;
	T arg_;
public:

	void update()
	{
		InputHandler* ih = InputHandler::instance();

		if (ih->keyDownEvent() != finished_)
		{
			if (ih->isKeyDown(SDLK_BACKSPACE) && inputString_.length() > 0)
			{
				inputString_.replace(cursorPosition_-1, 1, "");
				cursorPosition_--;
			}
			else if (ih->isKeyDown(SDLK_LEFT) && cursorPosition_ > 0)
				cursorPosition_--;
			else if (ih->isKeyDown(SDLK_RIGHT) && cursorPosition_ < inputString_.size()-1)
				cursorPosition_++;
			else if (ih->isKeyDown(SDLK_RETURN))
			{
				this->setEnabled(false);
				executeCallback(arg_);
			}
			else
			{
				string s = ih->getTextInput();
				//inputString_.reserve(inputString_.size() + s.size());
				inputString_.insert(cursorPosition_, s);
				cursorPosition_ += s.size();
			}
			t_->setText(inputString_);
		}
	}
	void draw() override
	{
		int charW = t_->getCharW();
		int charH = t_->getCharH();

		int w = t_->getCharW();
		int h = t_->getCharH();


		int numLines = t_->getNumLines();
		vector<string> lines = t_->getLines();
		int maxW = t_->getMaxW();

		int x = (t_->getPos().getX())+(cursorPosition_ * w) % maxW;
		int y = (t_->getPos().getY())+(lines.size() - 1) * h;


		if (game_->getTime() - lastBlink > blinkDuration)
		{
			lastBlink = game_->getTime();
			blinking_ = !blinking_;
		}
		if (blinking_)
		{
			SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0xffffffff));
			if (isEnabled())
			{
				SDL_RenderDrawLine(game_->getRenderer(), x, y, x, y + charH);
				SDL_RenderDrawLine(game_->getRenderer(), x + 1, y, x + 1, y + charH);
				SDL_RenderDrawLine(game_->getRenderer(), x + 2, y, x + 2, y + charH);
			}
		}

	}
};


