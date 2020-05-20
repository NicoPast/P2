#pragma once
#include "Component.h"
#include "Text.h"
#include <functional>
#include "SDL_macros.h"
template<typename T>
class InputText : public Component
{
public:
	InputText(Text* t, std::function<void(T)>f, T arg, bool emptyStart) : Component(ecs::InputText), t_(t), func_(f), arg_(arg), emptyStart_(emptyStart) {  };
	virtual ~InputText() {};

protected:
	Text* t_;
	string inputString_;
	bool finished_ = false;
	size_t cursorPosition_ = 0;
	size_t lastBlink;
	size_t blinkDuration = 500;
	bool blinking_ = false;
	void executeCallback(T margs)
	{
		func_(margs);
	}
	std::function<void(T)> func_;
	T arg_;
	bool tilde = false;
	bool dieresis = false;
	bool emptyStart_;

	int cursorChar = 0;
	int cursorLine = 0;

	int prevChar = 0;
	int prevLine = 0;

	bool selecting_ = false;
public:
	void clear()
	{
		inputString_ = "";
		t_->setText(inputString_);
	};
	virtual void init() override
	{
		//Si el texto esta vacio inserta un espacio en blanco
		if (emptyStart_)
			inputString_ = "";
		else
			inputString_ = t_->getText();
		t_->setText(inputString_);

		//Coloca el cursor donde toca
		cursorPosition_ = inputString_.length();

		vector<string> lines = t_->getLines();
		int cursorP = cursorPosition_;
		int i = 0;
		while (i < lines.size() && (cursorP - (int)lines[i].size()) > 0)
		{
			cursorP -= lines[i].size();
			i++;
		}
		cursorLine = i;
		prevLine = i;
		cursorChar = cursorP;
		prevChar = cursorP;
	}
	void update()
	{
		InputHandler* ih = InputHandler::instance();
		if (ih->keyDownEvent() != finished_)
		{
			if (prevChar != cursorChar || prevLine != cursorLine)
			{
				vector<string> lines = t_->getLines();
				int dist = 0;
				int cChar = cursorChar;
				int pChar = prevChar;
				int cLine = cursorLine;
				int pLine = prevLine;
				if ((cursorChar < prevChar && cursorLine <= prevLine) || cursorLine < prevLine)
				{
					int little = cChar;
					cChar = pChar;
					pChar = little;
				}
				int prevPos = prevChar;

				if (cLine < pLine)
				{
					int little = cLine;
					cLine = pLine;
					pLine = little;
				}
				for (int i = 0; i < pLine; i++)
				{
					prevPos += lines[i].size();
				}
				for (int i = pLine; i < pLine - cLine; i++)
				{
					dist += lines[i].size();
				}
				if (cLine - pLine == 0)
				{
					dist += cChar - pChar;
				}
				else if (cLine - pLine == 1)
				{
					dist += lines[pLine].size() - pChar;
					dist += cChar;
				}
				else
				{
					dist += lines[pLine].size() - pChar;
					dist += cChar;
				}

				inputString_.replace(prevPos, dist, "");
				cursorPosition_ -= dist;
			}
			string s;
			if (ih->isKeyDown(SDLK_BACKSPACE) && inputString_.length() > 0)
			{
				inputString_.replace(cursorPosition_ - 1, 1, "");
				cursorPosition_--;
			}
			else if (ih->isKeyDown(SDLK_DELETE) && inputString_.length() > 0)
			{
				inputString_.replace(cursorPosition_ , 1, "");
				//cursorPosition_--;
			}
			else if (ih->isKeyDown(SDLK_LEFT) && cursorPosition_ > 0)
				cursorPosition_--;
			else if (ih->isKeyDown(SDLK_RIGHT) && cursorPosition_ < inputString_.size())
				cursorPosition_++;
			else if (ih->isKeyDown(SDLK_RETURN))
			{
				if (!ih->isKeyDown(SDL_SCANCODE_LSHIFT) && !ih->isKeyDown(SDL_SCANCODE_RSHIFT))
				{
					executeCallback(arg_);
					this->setEnabled(false);
				}
				else
					s += "\\n";
			}
			//apaño pa las tildes y demás, el que quiera intentar hacerlo bonito, le deseo suerte y le daré crédito en el 5º círculo del infierno.
#pragma region apaño

			else if (ih->isKeyDown(SDL_SCANCODE_EQUALS))
			{
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
				{
					s += "¿";
				}
				else s += "¡";
			}
			else if (ih->isKeyDown(SDL_SCANCODE_SEMICOLON))
			{
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					s += "Ñ";
				else
					s += "ñ";
			}
			else if (ih->isKeyDown(SDL_SCANCODE_APOSTROPHE))
			{
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					dieresis = true;
				else tilde = true;
			}
			else if (ih->isKeyDown(SDLK_v) && (ih->isKeyDown(SDLK_LCTRL) || ih->isKeyDown(SDLK_RCTRL)))
			{
				//RaiiClipboard clipboard;

				//HANDLE hData = GetClipboardData(CF_TEXT);
				//if (hData == nullptr)
				//	throw runtime_error("Can't get clipboard text.");

				//RaiiTextGlobalLock textGlobalLock(hData);
				//string text(textGlobalLock.Get());
				//s += text;
				char* text = SDL_GetClipboardText();
				if (text == NULL)
					throw "E";
				s += text;
			}
			else if (ih->isKeyDown(SDLK_a) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					s += "Á";
				else
					s += "á";
			}
			else if (ih->isKeyDown(SDLK_e) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					s += "É";
				else
					s += "é";
			}
			else if (ih->isKeyDown(SDLK_i) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					s += "Í";
				else
					s += "í";
			}
			else if (ih->isKeyDown(SDLK_o) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					s += "Ó";
				else
					s += "ó";
			}
			else if (ih->isKeyDown(SDLK_u) && tilde)
			{
				tilde = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					s += "Ú";
				else
					s += "ú";
			}
			else if (ih->isKeyDown(SDLK_u) && dieresis)
			{
				dieresis = false;
				if (ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT))
					s += "Ü";
				else
					s += "ü";
			}
			//finde apaño
#pragma endregion
			else
			{
				if (!(ih->isKeyDown(SDL_SCANCODE_LSHIFT) || ih->isKeyDown(SDL_SCANCODE_RSHIFT)))
				{
					tilde = false;
					dieresis = false;
				}
				s = ih->getTextInput();
			}
			inputString_.insert(cursorPosition_, s);
			cursorPosition_ += s.size();
			t_->setText(inputString_);
			int vCount = 0;//vertical count
			int i = 0;
			vector<string> lines = t_->getLines();
			int cursorP = cursorPosition_;
			while (i < lines.size() && (cursorP - (int)lines[i].size()) > 0)
			{
				cursorP -= lines[i].size();
				i++;
			}
			cursorLine = i;
			prevLine = i;
			//cout << i << endl;
			//if (prevChar == cursorChar)prevChar = vCount - cursorPosition_;
			cursorChar = cursorP;
			prevChar = cursorP;

		}
		if (ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::LEFT))
		{
			int lineIndex = 0;
			int charIndex = 0;
			Vector2D mousePos(ih->getMousePos());
			if (t_->clickOnText(mousePos, charIndex, lineIndex));
			{
				int vCount = 0;//vertical count
				vector<string> lines = t_->getLines();
				for (int i = 0; i < lineIndex; i++)
				{
					vCount += lines[i].size();
				}
				vCount += charIndex;
				cursorPosition_ = vCount;

				cursorChar = charIndex;
				cursorLine = lineIndex;
				prevChar = cursorChar;
				prevLine = cursorLine;

				selecting_ = true;
			}
		}
		else if (ih->mouseButtonEvent() && !ih->getMouseButtonState(InputHandler::LEFT))
		{
			if (selecting_)
			{
				selecting_ = false;
			}
		}
		else if (ih->mouseMotionEvent() && selecting_)
		{
			int lineIndex = 0;
			int charIndex = 0;
			Vector2D mousePos(ih->getMousePos());
			if (t_->clickOnText(mousePos, charIndex, lineIndex))
			{
				int vCount = 0;//vertical count
				vector<string> lines = t_->getLines();
				for (int i = 0; i < lineIndex; i++)
				{
					vCount += lines[i].size();
				}
				vCount += charIndex;
				cursorPosition_ = vCount;

				cursorChar = charIndex;
				cursorLine = lineIndex;

			}
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

		int x = (t_->getPos().getX());
		int y = (t_->getPos().getY());

		int line = 0;
		int charPos = cursorPosition_;
		bool selected = (cursorChar != prevChar || cursorLine != prevLine);

		if (selected)
		{
			int xS = x;
			int yS = y;
			int cChar = cursorChar;
			int pChar = prevChar;
			int cLine = cursorLine;
			int pLine = prevLine;
			bool leftToRight = (cursorChar > prevChar || cursorLine > prevLine);
			if ((cursorChar < prevChar && cursorLine <= prevLine) || cursorLine < prevLine)
			{
				int little = cChar;
				cChar = pChar;
				pChar = little;
			}
			if (cLine < pLine)
			{
				int little = cLine;
				cLine = pLine;
				pLine = little;
			}
			SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0xa0a0cc55));
			if (cLine - pLine == 0)
			{
				SDL_Rect r{ xS + pChar * w, yS + cLine * h, (cChar - pChar) * w, h };
				SDL_RenderFillRect(game_->getRenderer(), &r);
			}
			else if (cLine - pLine == 1)
			{

				SDL_Rect r1{ xS + pChar * w, yS + pLine * h, (lines[pLine].size() - pChar) * w, h };
				SDL_RenderFillRect(game_->getRenderer(), &r1);

				SDL_Rect r2{ xS, yS + cLine * h, cChar * w, h };
				SDL_RenderFillRect(game_->getRenderer(), &r2);
			}
			else
			{
				int maxW = t_->getMaxW();
				SDL_Rect r1{ xS + pChar * w, yS + pLine * h, (lines[pLine].size() - pChar) * w, h };
				SDL_RenderFillRect(game_->getRenderer(), &r1);

				SDL_Rect r2{ xS, yS + cLine * h, cChar * w, h };
				SDL_RenderFillRect(game_->getRenderer(), &r2);

				SDL_Rect r3{ xS, yS + (cLine)* h, maxW, ((pLine - cLine) + 1) * h };
				SDL_RenderFillRect(game_->getRenderer(), &r3);
			}

		}

		x += cursorChar * charW;
		y += cursorLine * charH;
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
