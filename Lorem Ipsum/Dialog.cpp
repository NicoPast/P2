#include "Dialog.h"

void Dialog::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent() && conversing_)
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
			conversing_ = false;
		}

	}
	if (!conversing_)
	{
		if (ih->isKeyDown(SDLK_c))
		{
			interact();
		}
	};
}

void Dialog::init()
{
	 Vector2D p2 = { 0.0,game_->getWindowHeight() - 200.0 };
	 rectComponent_ = entity_->addComponent<Rectangle>(SDL_Color{COLOR(0x666666FF)});
	 rectComponent_->setEnabled(false);
	 textComponent_ = entity_->addComponent<Text>("", p2, 600, game_->getFontMngr()->getFont(Resources::ARIAL16), 0);
	 textComponent_->addSoundFX(Resources::Bip);
	 textComponent_->addSoundFX(Resources::Paddle_Hit);

}

void Dialog::interact()
{
	cout << "interacting\n";
	rectComponent_->setEnabled(true);
	if (dialogs_.size() > 0)
	{
		conversing_ = true;
		if (dialogs_[0].startLine_ == "")
		{
			currentOption_ = 0;
			currentLine_ = 0;
			textComponent_->setText(dialogs_[currentOption_].conversation_[currentLine_].line_);
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
		conversing_ = false;
	else
		textComponent_->setNextText(options);
}
void Dialog::advanceDialog()
{
	if (dialogs_[currentOption_].lines_  > currentLine_ + 1)
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