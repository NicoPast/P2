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
	if (conversing_ && showingOptions_)
	{
		bool tinted = false;
		InputHandler* ih = InputHandler::instance();
		if (ih->mouseMotionEvent())
		{
			string line;
			long h = textComponent_->getCharH();
			long w = textComponent_->getCharW();
			vector<string> lines = textComponent_->getLines();
			Vector2D pos = textComponent_->getPos();

			for (long i = 0; i < lines.size(); i++)
			{
				line = lines[i];
				SDL_Point mouseP{ ih->getMousePos().getX(), ih->getMousePos().getY() };
				SDL_Rect lineBox{ pos.getX(), pos.getY()+h*i, w*line.size(),h };
				if (SDL_PointInRect(&mouseP, &lineBox))
				{
					textComponent_->setColor(255, 0, 255, i);
					tinted = true;
					currentOption_ = i+1;
				}
			}
			if(!tinted)
				textComponent_->setColor(255, 0, 255, -1);
		}
		if(ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::LEFT) && currentOption_!=0)
		{
			string line;
			long h = textComponent_->getCharH();
			long w = textComponent_->getCharW();
			vector<string> lines = textComponent_->getLines();
			Vector2D pos = textComponent_->getPos();
			int i = currentOption_-1;
			line = lines[i];
			SDL_Point mouseP{ ih->getMousePos().getX(), ih->getMousePos().getY() };
			SDL_Rect lineBox{ pos.getX(), pos.getY() + h * i, w * line.size(),h };
			if (SDL_PointInRect(&mouseP, &lineBox))
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
		long h = textComponent_->getCharH();
		long w = textComponent_->getCharW();
		vector<string> lines = textComponent_->getLines();
		Vector2D pos = textComponent_->getPos();
		SDL_Point mouseP{ ih->getMousePos().getX(), ih->getMousePos().getY() };
		Transform* t = rectComponent_->getEntity()->getComponent<Transform>(ecs::Transform);
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
	showingOptions_ = false;
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
	for (size_t i = 0; i < dialog_->options_.size()-1; i++)
	{
		if (dialog_->options_[i].startLine_ != "")
		{
			options += "-"+dialog_->options_[i].startLine_+ " \\n";
		}
	}
	if (options == "")
	{
		stopDialog();
	}
	else
	{
		showingOptions_ = true;
		options += "-"+dialog_->options_.back().startLine_;
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
		currentOption_ = 0;
		sendDialogOtions();
	}
}

void DialogComponent::sendCurrentLine()
{
	showingOptions_ = false;
	textComponent_->setText(dialog_->options_[currentOption_].lines_[currentLine_].line_);
	actorNameComponent_->setText(sm_->getActorName((Resources::ActorID)dialog_->options_[currentOption_].lines_[currentLine_].actorID_));
};

