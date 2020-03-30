#include "Dialog.h"

void Dialog::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent() && conversing)
	{
		if (ih->isKeyDown(SDLK_RETURN))
		{
			advanceDialog();
		}
		if (ih->isKeyDown(SDLK_0))
		{
			currentOption_ = 0;
			currentLine_ = 0;
			sendCurrentLine();
		}
		if (ih->isKeyDown(SDLK_q))
		{
			conversing = false;
		}

	}
	if (!conversing)
	{
		if (ih->isKeyDown(SDLK_c))
		{
			interact();
		}
	};
}


void Dialog::interact()
{
	if (dialogs_.size() > 0)
	{
		conversing = true;
		if (dialogs_[0].startLine_ == "")
		{
			currentOption_ = 0;
			currentLine_ = 0;
			sendCurrentLine();
		}
		else
		{
			sendDialogOtions();
		}
	}
}

void Dialog::sendDialogOtions()
{
	string options;
	//se salta el primero si startline == "" porque ya se habrá mandado
	for (int i = 0; i < dialogs_.size(); i++)
	{
		if (dialogs_[i].startLine_ != "")
		{
			options.append(dialogs_[i].startLine_ + "\n");
		}
	}
	if (options == "")
		conversing = false;
	else
		textComponent_->setNextText(options);
}
void Dialog::advanceDialog()
{
	if (dialogs_[currentOption_].lines_ < currentLine_)
	{
		currentLine_++;
		sendCurrentLine();
	}
	else
	{
		if (dialogs_[currentOption_].callback_ != nullptr)
		{
			//ejecuta callback añade pista
		}
		sendDialogOtions();
	}
}

/*

o/            \o
=================
JUAN:
	HOLA ME LLAMO JUAN
Lázaro:
	Ok.
=================
	-Saludar 
	-Interrogar
*/