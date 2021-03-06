#include "Phone.h"
#include "Entity.h"

Phone::Phone(StoryManager* sm) : Component(ecs::Phone), tr_(nullptr), sm_(sm) {

}
void Phone::init(){
	tr_ = GETCMP1_(Transform);
	top_ = game_->getWindowHeight() - tr_->getH();
	bottom_ = game_->getWindowHeight();

	/*
	//metemos todos los nombres disponibles en el dropdown
	//por ahora. En un futuro deber�an ir a�adi�ndose seg�n se hayan reproducido o desbloqueado las conersaciones
	for (int i = 1; i < sm_->getActors().size(); i++) {
		actors_.push_back(sm_->getActors()[i]);
	}

	dropdown_ = createDropdown(actors_, "mirame", tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), 30, false);
	hideContacts();
	/**/
}

void Phone::update() {
#ifdef _DEBUG
	if (InputHandler::instance()->keyDownEvent())
	{
		if (InputHandler::instance()->isKeyDown(SDLK_k))
			notification();
	}
#endif // _DEBUG
	if (newNotification && vibrationAnimCount <30)
	{
		int sing;
		sing = (vibrationAnimCount % 2 == 0) ? -1 : 1;
		tr_->setRot(2 * sing);
		vibrationAnimCount++;
	}
	else if (newNotification)
	{
		tr_->setRot(0);
		newNotification = false;
	}
}

void Phone::move(bool up)
{
	setDir({ 0, ((up)? -speed_ : speed_)});
	inUse_ = up;
	moving_ = true;
	hideContacts();
}

void Phone::showContacts()
{

	if (dropdown_.empty())
	{
		for (auto& actor : sm_->getActors()) {
			//if(actor.second->getId() != Resources::SDL)
				actors_.push_back(actor.second);
		}
		dropdown_ = createDropdown(actors_, "mirame", (int)tr_->getPos().getX() + 5, (int)tr_->getPos().getY() + 30, (int)tr_->getW() - 10, 30, false);
	}
	else
	{
		for (int i = 1; i < sm_->getActors().size(); i++) {
		
			if (actors_[i]->imInPhone()) {
				dropdown_[i]->enable();
				dropdown_[i]->setText(actors_[i]->getContactsName());
				auto id = actors_[i]->getId();
				dropdown_[i]->setCB([id](Phone* p) {StoryManager::instance()->call(id); }, this);
			}
		}
		dropdown_[0]->enable();
	}
	//disableIcons();
	hideIcons();
	InputHandler::instance()->lock();
	//creamos un desplegable con todas las opciones de di�logo que se han desbloqueado

	/*messages_ = true;
	
/**/
}

void Phone::setDir(Vector2D dir)
{
	tr_->setVel(dir);
	for (int i = 0; i < icons_.size(); i++)
	{
		icons_[i]->setVel(dir);
	}
}

void Phone::stop()
{
	setDir({ 0,0 });
	moving_ = false;
}

vector<Phone::UIButton<Phone*>*> Phone::createDropdown(vector<Actor*>& actors, string text, int x, int y, int w, int h, bool up)
{
	vector<UIButton<Phone*>*> buttons;
	
	Phone::UIButton<Phone*>* b = new Phone::UIButton<Phone*>(entity_->getEntityMangr(), x, y, w, h, SDL_Color{ COLOR(0x5797BAff) }, "Salir", 0, 0, Resources::FontId::RobotoTest24, [](Phone* p) {}, this);
	int index = 1;
	int dir = (up) ? -1 : 1;
	vector<Transform*>transforms;
	/*b->disable();*/
	b->getEntity()->getComponent<ButtonOneParametter<Phone*>>(ecs::Button)->setSpecial();
	buttons.push_back(b);

	if (!actors.empty()) {
		for (auto actor : actors)
		{
			UIButton<Phone*>* but = new UIButton<Phone*>(entity_->getEntityMangr(), x, y + h * index * dir, w, h, SDL_Color{ COLOR(0x5797BAFF) }, actor->getContactsName(), 0, 0, Resources::FontId::RobotoTest24, [actor](Phone* p) { p->getStoryManager()->call(actor->getId()); }, this);
			buttons.push_back(but);
			transforms.push_back(but->getTransform());
			index++;
			but->disable();
		}

		SDL_Rect rect{ x,y + h,w, (int)(tr_->getH() - 2.5 * h) };
		auto scroll = b->createScroll(rect, transforms, 0, SDL_Color{ COLOR(0x880088ff) }, SDL_Color{ COLOR(0xCC) });
		b->setCB([buttons, scroll](Phone* state)
			{		
				state->showIcons();
				InputHandler::instance()->unlock();
				for (int i = 1; i < buttons.size(); i++)
				{
					auto& but = buttons[i];
					state->hideContacts();
					cout << i - 1;
				}
			}, entity_->getComponent<Phone>(ecs::Phone));
		scroll->show();
	}	
	
	return buttons;
}

void Phone::destroyMessagesMenu()
{
	for (size_t i = 0; i < dropdown_.size(); i++)
	{
		delete dropdown_[i];
		dropdown_[i] = nullptr;
	};
}

void Phone::hideContacts() {
	
	for (size_t i = 0; i < dropdown_.size(); i++)
	{
		dropdown_[i]->disable();
	};
}
/**/
