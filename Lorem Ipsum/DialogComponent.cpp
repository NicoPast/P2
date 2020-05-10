#include "DialogComponent.h"
#include "Phone.h"
#include "Entity.h"
#include "PlayerKBCtrl.h"
#include "StoryManager.h"
#include "DialogSelectors.h"

DialogComponent::~DialogComponent()
{
	
	if (file_ != "")
	{
		std::ofstream out(file_.c_str());
		out << "enum dialogNames =\n {\n";
		for (auto d : dialogs_)
		{
			out << d->dialogName_ << " = " << d->listPosition_ << endl;
			delete d;
		}
		out << endl << "}";
		out.close();
	}
};

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
		bool* gray  = new bool[selectedDialog_->options_.size()];
		for (int i = 0; i<selectedDialog_->options_.size();i++)
		{
			gray[i] = selectedDialog_->options_[i].read_;
			if(gray[i])textComponent_->setColor(200, 200, 200, i);
		}
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
			if(!tinted && !gray[line])
				textComponent_->setColor(255, 255, 255, line);
			else if (!tinted && gray[line])
				textComponent_->setColor(200, 200, 200, line);
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
		delete[] gray;
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
	phone_->getComponent<Phone>(ecs::Phone)->hide();
 	tweenComponent_->GoToB();
	int availableScenes = 0;

	if (hasFunc)
	{
		dialogSelectorFunc_(this);
	}
	else
	{
		for (auto dial : dialogs_)
		{
			if (dial->active_)
			{
				availableDialogs.push_back(dial);
			}
		}
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

void DialogComponent::addDialog(Dialog* d)
{
	if (file_ == "")
		file_ = "../assets/dialogs/actors/" + actor_->getName() + ".dialogList";
	dialogs_.push_back(d); d->listPosition_ = dialogs_.size() - 1; refresh();
};

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
	bool allRead = true;
	for (size_t i = 0; i < selectedDialog_->options_.size()-1; i++)
	{
		if (selectedDialog_->options_[i].startLine_ != "")
		{
			options += "-"+selectedDialog_->options_[i].startLine_+ " \\n";
		}
		//Si alguna lo hace false, queda false. De lo contrario el jugador ha leído todas las opciones. Y podemos marcar el diálogo como leído en el bitset
		if(allRead)
			allRead = selectedDialog_->options_[i].read_;
	}
	//Marcamos el dialogo seleccionado como leído en el bitset si todas las opciones han sido leídas hasta el final
	if (allRead)
		this->dialogsStatus_[selectedDialog_->listPosition_] = 1;
	if (options == "")
		stopDialog();
	
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
		selectedDialog_->options_[currentOption_].read_ = true; //El jugador ha leído esta opción y la marcamos como tal
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
