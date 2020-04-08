#include "DialogComponent.h"
#include "Phone.h"
#include "Entity.h"
#include "PlayerKBCtrl.h"

void DialogComponent::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent() && conversing_)
	{
		if (ih->isKeyDown(SDLK_RETURN))
		{
			advanceDialog();
		}
		/* Las teclas 1, 2.. son para cambiar la opci�n. Esto ser har� con el rat�n y las teclas de direcci�n cambiar�n entre opciones*/
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
	 Vector2D p2 = { 0.0, game_->getWindowHeight() - 200.0 };
	 rectComponent_ = entity_->addComponent<Rectangle>(SDL_Color{COLOR(0x666666FF)});
	 rectComponent_->setEnabled(false);//600
	 actorNameComponent_ = entity_->addComponent<Text>("", p2, GETCMP1_(Transform)->getW(), Resources::RobotoTest24, 0);
	 //actorNameComponent_->setColor(240, 350, 420);

	 p2 = { 0.0, game_->getWindowHeight() - 160.0 };
	 textComponent_ = entity_->addComponent<Text>("", p2, game_->getWindowWidth(), Resources::RobotoTest24, 100);
	 textComponent_->addSoundFX(Resources::Bip);
	 textComponent_->addSoundFX(Resources::Paddle_Hit);
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
	//actorNameComponent_->setText("�");
	//textComponent_->setText("�");
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
		//Quitamos el �ltimo salto de linea porque explota
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
		//	//ejecuta callback a�ade pista
		//}
		sendDialogOtions();
	}
}

/*

o/            \o
=================
JUAN:
	HOLA ME LLAMO JUAN
L�zaro:
	Ok.
=================
	-Saludar 
	-Interrogar
*/