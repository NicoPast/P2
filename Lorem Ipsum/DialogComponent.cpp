#include "DialogComponent.h"
#include "Phone.h"
#include "Entity.h"
#include "PlayerKBCtrl.h"
#include "StoryManager.h"
void DialogComponent::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent() && conversing_)
	{
		if (ih->isKeyDown(SDLK_RETURN))
		{
			advanceDialog();
		}
		/* Las teclas 1, 2.. son para cambiar la opción. Esto ser hará con el ratón y las teclas de dirección cambiarán entre opciones*/
		else if (ih->isKeyDown(SDLK_1))
		{
			currentOption_ = 1;
			currentLine_ = 0;
			sendCurrentLine();
		}
		else if (ih->isKeyDown(SDLK_2))
		{
			currentOption_ = 2;
			currentLine_ = 0;
			sendCurrentLine();
		}
		else if (ih->isKeyDown(SDLK_3))
		{
			currentOption_ = 3;
			currentLine_ = 0;
			sendCurrentLine();
		}
		else if (ih->isKeyDown(SDLK_4))
		{
			currentOption_ = 4;
			currentLine_ = 0;
			sendCurrentLine();
		}
		/* ------------------------------------------------------------------------------------------------------------------------- */
		else if (ih->isKeyDown(SDLK_q))
		{
			stopDialog();
		}

	}
	if (!conversing_)
	{

	};
}

void DialogComponent::init()
{
	 rectComponent_ = sm_->getDialogBox()->getComponent<Rectangle>(ecs::Rectangle);
	 actorNameComponent_ = sm_->getDialogBoxActorName();
	 textComponent_ = sm_->getDialogBoxText();
}

void DialogComponent::interact()
{
	cout << "interacting\n";
	rectComponent_->setEnabled(true);
	GETCMP2(player_, PlayerKBCtrl)->setEnabled(false);
	player_->getComponent<Transform>(ecs::Transform)->setVelX(0);
	if (dialog_->options_.size() > 0)
	{
		conversing_ = true;
		if (dialog_->options_[0].startLine_ == "")
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
	//actorNameComponent_->setText("á");
	//textComponent_->setText("é");
}

void DialogComponent::sendDialogOtions()
{
	string options="";
	for (size_t i = 0; i < dialog_->options_.size(); i++)
	{
		if (dialog_->options_[i].startLine_ != "")
		{
			options += "-";
			options += dialog_->options_[i].startLine_;
			options += " \\n";
		}
	}
	if (options == "")
	{
		stopDialog();
	}
	else
	{
		//Quitamos el último salto de linea porque explota
		options.pop_back();
		options.pop_back();
		options.pop_back();
		textComponent_->setText(options);
	}
}
void DialogComponent::stopDialog()
{
	conversing_ = false;
	textComponent_->resetText();
	actorNameComponent_->resetText();
	rectComponent_->setEnabled(false);
	player_->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->setEnabled(true);
}
void DialogComponent::advanceDialog()
{
	if (!textComponent_->getEnded())
	{
		textComponent_->setTextDelay(20);
	}
	else if (dialog_->options_[currentOption_].lines_.size()  > currentLine_ + 1)
	{
		currentLine_++;
		sendCurrentLine();
	}
	else
	{
		//if (dialogs_.options_[currentOption_].callback_ != nullptr)
		//{
		//	//ejecuta callback añade pista
		//}
		sendDialogOtions();
	}
}

void DialogComponent::sendCurrentLine()
{
	textComponent_->setText(dialog_->options_[currentOption_].lines_[currentLine_].line_);
	actorNameComponent_->setText(sm_->getActorName((Resources::ActorID)dialog_->options_[currentOption_].lines_[currentLine_].actorID_));
};

