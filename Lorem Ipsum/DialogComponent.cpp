#include "DialogComponent.h"
#include "Phone.h"
#include "Entity.h"
#include "PlayerKBCtrl.h"
#include "StoryManager.h"
#include "DialogSelectors.h"

DialogComponent::~DialogComponent()
{
	if (file_!="FAKEACTOR")
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
		else
		{
			for (auto d : dialogs_)
			{
				delete d;
			}
		}
	}

	delete []data;
};

void DialogComponent::update()
{
	InputHandler* ih = InputHandler::instance();

	if (conversing_ || showingDialogs || showingOptions_)
	{
		ih->unlock();
	}
	if (callback_ != nullptr)
		if(dialogCallbackIndex_ == selectedDialog_->listPosition_ && optionCallbackIndex_ == currentOption_ && lineCallbackIndex_ == currentLine_)
			callback_(this);
	if (ih->keyDownEvent() && conversing_)
	{
		if (ih->isKeyDown(SDLK_RETURN))
		{
			advanceDialog();
		}
		else if (!ignoreQ && ih->isKeyDown(SDLK_q))
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
			tinted = textComponent_->clickOnText(ih->getMousePos(), charIndex, line);
			if (tinted)
			{
				textComponent_->setColor(255, 0, 255, line);
				line++;//Ignoramos la primera linea porque, las dialogLines empiezan en 0, y auí estamos viendo las lineas de inicio en un componente texto
				currentOption_ = line;
			}
			else
			{
				checkOptionsColor();
			}
		}
		if(ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::LEFT) && currentOption_!=0)
		{
			int line = 0;
			int charIndex = 0;
			if (textComponent_->clickOnText(ih->getMousePos(), charIndex, line))
			{
				currentLine_ = 0;
				currentOption_ = optionsPairs[line].second/*line+1*/;
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
	if (conversing_ || showingDialogs || showingOptions_)
	{
		ih->lock();
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

	 data = new int[MAXDATA];

	 for (int i = 0; i < MAXDATA; i++)
	 { 
		 data[i] = 0;
	 }
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
	optionsPairs.resize(selectedDialog_->options_.size());
	bool allRead = true;
	int textIndex = 0;

	for (size_t i = 0; i < selectedDialog_->options_.size(); i++)
	{
		if (allRead) {
			allRead = selectedDialog_->options_[i].read_;
		}
		optionsStatus_[selectedDialog_->listPosition_][i] = selectedDialog_->options_[i].read_;
	}
	if (allRead)
		this->dialogsStatus_[selectedDialog_->listPosition_] = 1;
	if (hasFunc)
	{
		dialogSelectorFunc_(this);
	}

	for (size_t i = 0; i < selectedDialog_->options_.size(); i++)
	{
		if (selectedDialog_->options_[i].startLine_ != "" && selectedDialog_->options_[i].active_)
		{
			options += "-"+selectedDialog_->options_[i].startLine_+ " \\n";
			optionsPairs[textIndex] = {textIndex,i};
			textIndex++;
		}
		//Si alguna lo hace false, queda false. De lo contrario el jugador ha leído todas las opciones. Y podemos marcar el diálogo como leído en el bitset
	}

	//Marcamos el dialogo seleccionado como leído en el bitset si todas las opciones han sido leídas hasta el final

	if (options == "")
		stopDialog();
	
	else
	{
		showingOptions_ = true;
		options.pop_back();
		options.pop_back();
		options.pop_back();
		textComponent_->setText(options);
		checkOptionsColor();
	}
}

void DialogComponent::stopDialog()
{
	InputHandler::instance()->unlock();
	conversing_ = false;
	showingDialogs = false;
	showingOptions_ = false;
	textComponent_->resetText();
	actorNameComponent_->resetText();
	tweenComponent_->GoToA();
	player_->getComponent<PlayerKBCtrl>(ecs::PlayerKBCtrl)->setEnabled(true);
	while (!availableDialogs.empty())
		availableDialogs.pop_back();
	if (dialogFinishedCB_ != nullptr)
		dialogFinishedCB_(this);
}

void DialogComponent::advanceDialog()
{
	if (!textComponent_->getEnded())
	{
		if (textComponent_->getTextDelay() > 30)textComponent_->setTextDelay(30);
		else textComponent_->setTextDelay(15);
	}
	else if (selectedDialog_->options_[currentOption_].lines_.size()  > currentLine_ + 1)
	{
		currentLine_++;
		sendCurrentLine();
		textComponent_->setTextDelay(100);
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
}
void DialogComponent::checkOptionsColor()
{
	int line = 0;
	while (line < this->selectedDialog_->options_.size())
	{
		if (!optionsStatus_[selectedDialog_->listPosition_][optionsPairs[line].second])
			textComponent_->setColor(255, 255, 255, line);
		else if (optionsStatus_[selectedDialog_->listPosition_][optionsPairs[line].second])
			textComponent_->setColor(200, 200, 200, line);
		line++;
	}
};
