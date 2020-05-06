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
		else if (ih->isKeyDown(SDLK_q))
		{
			stopDialog();
		}
	}
	if ((conversing_ && showingOptions_))
	{
		bool tinted = false;
		InputHandler* ih = InputHandler::instance();
		if (ih->mouseMotionEvent())
		{
			int line=0;
			int charIndex=0;
			tinted = textComponent_->clickOnText(ih->getMousePos(), line, line);
			if (tinted)
			{
				textComponent_->setColor(255, 0, 255, line);
				line++;//Ignoramos la primera linea porque, las dialogLines empiezan en 0, y auí estamos viendo las lineas de inicio en un componente texto
				currentOption_ = line;
			}
			if(!tinted)
				textComponent_->setColor(255, 0, 255, -1);
		}
		if(ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::LEFT) && currentOption_!=0)
		{
			int line = 0;
			int charIndex = 0;
			if (textComponent_->clickOnText(ih->getMousePos(), line, line))
			{
				currentLine_ = 0;
				sendCurrentLine();
				textComponent_->setColor(255, 0, 255, -1);
			}
			else
			{
				stopDialog();
			}
		}
	};
	if (conversing_ && !showingOptions_ && ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::LEFT))
	{
		SDL_Point mouseP{ ih->getMousePos().getX(), ih->getMousePos().getY() };
		Transform* t = textComponent_->getEntity()->getComponent<Transform>(ecs::Transform);
		SDL_Rect lineBox = {t->getPos().getX(),t->getPos().getY(), t->getW(),t->getH() };
		if (SDL_PointInRect(&mouseP, &lineBox))
		{
			advanceDialog();
		}
		else
		{
			stopDialog();
		}
	}
	if (!conversing_ && showingDialogs)
	{
		int line = 0;
		int charIndex = 0;
		if (ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::LEFT) && textComponent_->clickOnText(ih->getMousePos(), line, line))
		{
			selectedDialog_ = availableDialogs[line];
			startDialog();
		}
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_q))
			stopDialog();
	}
}

void DialogComponent::init()
{
	 tweenComponent_ = sm_->getDialogBox()->getComponent<Tween>(ecs::Tween);
	 actorNameComponent_ = sm_->getDialogBoxActorName();
	 actorNameComponent_->setColor(255, 255, 255);
	 textComponent_ = sm_->getDialogBoxText();
	 textComponent_->setColor(255, 255, 255);
	 phone_ = sm_->getPhone();
	 player_ = sm_->getPlayer();
}

void DialogComponent::interact()
{
	if (dialogs_.empty())return;
	if (showingOptions_ || conversing_)return;
	showingOptions_ = false;
	showingDialogs = false;
	textComponent_->setEnabled(false);
	actorNameComponent_->setEnabled(false);
	player_->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->setEnabled(false);
	player_->getComponent<Transform>(ecs::Transform)->setVelX(0);
	phone_->getComponent<Tween>(ecs::Tween)->GoToA();
 	tweenComponent_->GoToB();
	int availableScenes = 0;
	for (auto dial : dialogs_)
	{
		if (dial.first)
			availableDialogs.push_back(dial.second);
	}
	if (availableDialogs.size() == 1)
	{
		selectedDialog_ = availableDialogs[0];
		startDialog();
	}
	else if (availableDialogs.size() > 1)
	{
		showDialogList(availableDialogs);
	}
	else
		stopDialog();
}

void DialogComponent::showDialogList(vector<Dialog*>& v)
{
	string options = "";
	for (auto& d : v)
	{
			options += "-" + d->dialogName_ + " \\n";
	}
	options.pop_back();
	options.pop_back();
	options.pop_back();
	textComponent_->setText(options);
	showingDialogs = true;
}

void DialogComponent::startDialog()
{
	if (selectedDialog_->options_.size() > 0)
	{
		conversing_ = true;
		if (selectedDialog_->options_[0].startLine_ == "")
		{
			currentOption_ = 0;
			currentLine_ = 0;
			sendCurrentLine();
		}
		else
			sendDialogOtions();
	}
}

void DialogComponent::sendDialogOtions()
{
	string options="";
	for (size_t i = 0; i < selectedDialog_->options_.size()-1; i++)
	{
		if (selectedDialog_->options_[i].startLine_ != "")
		{
			options += "-"+selectedDialog_->options_[i].startLine_+ " \\n";
		}
	}
	if (options == "")
	{
		stopDialog();
	}
	else
	{
		showingOptions_ = true;
		options += "-"+selectedDialog_->options_.back().startLine_;
		textComponent_->setText(options);
	}
}

void DialogComponent::stopDialog()
{
	conversing_ = false;
	showingDialogs = false;
	showingOptions_ = false;
	textComponent_->resetText();
	actorNameComponent_->resetText();
	tweenComponent_->GoToA();
	player_->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->setEnabled(true);
	while (!availableDialogs.empty())
		availableDialogs.pop_back();
}

void DialogComponent::advanceDialog()
{
	if (!textComponent_->getEnded())
	{
		textComponent_->setTextDelay(20);
	}
	else if (selectedDialog_->options_[currentOption_].lines_.size()  > currentLine_ + 1)
	{
		currentLine_++;
		sendCurrentLine();
	}
	else
	{
		currentOption_ = 0;
		sendDialogOtions();
	}
}

void DialogComponent::sendCurrentLine()
{
	showingOptions_ = false;
	textComponent_->setText(selectedDialog_->options_[currentOption_].lines_[currentLine_].line_);
	actorNameComponent_->setText(sm_->getActorName((Resources::ActorID)selectedDialog_->options_[currentOption_].lines_[currentLine_].actorID_));
	sm_->setPortrait((Resources::ActorID)selectedDialog_->options_[currentOption_].lines_[currentLine_].actorID_);
};
