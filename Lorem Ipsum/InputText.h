#pragma once
#include "Component.h"
#include "Text.h"
#include <functional>
#include "SDL_macros.h"
template<typename T>
class InputText : public Component
{
public:
	InputText(Text* t, std::function<void(T)>f, T arg, bool emptyStart=true) : Component(ecs::InputText), t_(t), func_(f), arg_(arg), emptyStart_(emptyStart) {  };
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
	bool tilde = false;
	bool dieresis = false;
	bool emptyStart_ = true;
public:
	void init()
	{
		if (emptyStart_)
			inputString_ = "";
		else
			inputString_ = t_->getText();
	}
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
			else if (ih->isKeyDown(SDLK_RIGHT) && cursorPosition_ < inputString_.size())
				cursorPosition_++;
			else if (ih->isKeyDown(SDLK_RETURN))
			{
				if (!ih->isKeyDown(SDL_SCANCODE_LSHIFT) &&!ih->isKeyDown(SDL_SCANCODE_RSHIFT))
				{
					executeCallback(arg_);
					this->setEnabled(false);
				}
				else
					inputString_ += "\\n";

			}
//apa�o pa las tildes y dem�s, el que quiera intentar hacerlo bonito, le deseo suerte y le dar� cr�dito en el 5� c�rculo del infierno.
#pragma region apa�o

			else if (ih->isKeyDown(SDL_SCANCODE_EQUALS))
			{
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
				{
					inputString_ += "�";
				}
				else inputString_ += "�";
				cursorPosition_++;
			}
			else if (ih->isKeyDown(SDL_SCANCODE_SEMICOLON))
			{
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					inputString_ += "�";
				else
					inputString_ += "�";
				cursorPosition_++;
			}
			else if (ih->isKeyDown(SDL_SCANCODE_APOSTROPHE))
			{
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					dieresis = true;
				else tilde = true;
			}
			else if (ih->isKeyDown(SDLK_a) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					inputString_ += "�";
				else 
					inputString_ += "�";
				cursorPosition_++;
			}
			else if (ih->isKeyDown(SDLK_e) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					inputString_ += "�";
				else
					inputString_ += "�";
				cursorPosition_++;
			}
			else if (ih->isKeyDown(SDLK_i) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					inputString_ += "�";
				else
					inputString_ += "�";
				cursorPosition_++;
			}
			else if (ih->isKeyDown(SDLK_o) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					inputString_ += "�";
				else
					inputString_ += "�";
				cursorPosition_++;
			}
			else if (ih->isKeyDown(SDLK_u) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					inputString_ += "�";
				else
					inputString_ += "�";
				cursorPosition_++;
			}
			else if (ih->isKeyDown(SDLK_u) && dieresis)
			{
				dieresis = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					inputString_ += "�";
				else
					inputString_ += "�";
				cursorPosition_++;
			}
//finde apa�o
#pragma endregion
			else
			{
				if (!(ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT)))
				{
					tilde = false;
					dieresis = false;
					//uint32_t si=0;
					//uint32_t no=0;
					//const SDL_MessageBoxButtonData buttons[] = {
					//	{ si        , 0, "Si" },
					//	{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No" }
					//};
					//const SDL_MessageBoxColorScheme colorScheme = {
					//{ /* .colors (.r, .g, .b) */
					//	{ 255,   0,   0 },
					//	{   0, 255,   0 },
					//	{ 255, 255,   0 },
					//	{   0,   0, 255 },
					//	{ 255,   0, 255 }
					//}
					//};
					//const SDL_MessageBoxData data2
					//{
					//	SDL_MESSAGEBOX_INFORMATION,
					//	game_->getWindow(),
					//	"�Seguro?",
					//	"Vas a cargar de archivo y descartar tus cambios",
					//	SDL_arraysize(buttons),
					//	buttons,
					//	&colorScheme
					//};
					//int buttonId;
					////SDL_ShowSimpleMessageBox(0, "titulo", "vas a modificar el archivo, puto loco", game_->getWindow());
					//SDL_ShowMessageBox(&data2, &buttonId);
					//if (si!=0) cout << "lol";
				}
				string s = ih->getTextInput();
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
				SDL_RenderDrawLine(game_->getRenderer(), x,		y, x,	  y + charH);
				SDL_RenderDrawLine(game_->getRenderer(), x + 1, y, x + 1, y + charH);
				SDL_RenderDrawLine(game_->getRenderer(), x + 2, y, x + 2, y + charH);
			}
		}

	}
};


