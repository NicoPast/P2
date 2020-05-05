#include "Phone.h"
#include "Entity.h"

Phone::Phone(StoryManager* sm) : Component(ecs::Phone), tr_(nullptr), sm_(sm) {

}
void Phone::init(){
	tr_ = GETCMP1_(Transform);
	top_ = game_->getWindowHeight() - tr_->getH();
	bottom_ = game_->getWindowHeight();
}

void Phone::update() {
}

void Phone::move(bool up)
{
	setDir({ 0, ((up)? -speed_ : speed_)});
	inUse_ = up;
	moving_ = true;

	if (panel_ != nullptr) destroyMessagesMenu();
}

void Phone::showContacts()
{
	messages_ = true;
	hideIcons();

	//creamos un desplegable con todas las opciones de diálogo que se han desbloqueado
	panel_ = new UIPanel(entity_->getEntityMangr(), tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH(), SDL_Color{ COLOR(0xff00ffff) });
	panel_->addTitle(0, 0, tr_->getW(), Resources::RobotoTest24, "Agenda");

	//metemos todos los nombres disponibles en el dropdown
	//por ahora. En un futuro deberían ir añadiéndose según se hayan reproducido o desbloqueado las conersaciones
	for (auto actor : sm_->getActors())
		names_.push_back(actor.second->getName());

	dropdown_ = createDropdown(names_, "mirame", tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), 30, false );


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

vector<Phone::UIButton<Phone*>*> Phone::createDropdown(vector<string>names, string text, int x, int y, int w, int h, bool up)
{
	Phone::UIButton<Phone*>* b = new Phone::UIButton<Phone*>(entity_->getEntityMangr(), x, y, w, h, SDL_Color{ COLOR(0x0ff00CCff) }, "hello", 0, 0, Resources::FontId::RobotoTest24, [](Phone* p) {}, this);
	int index = 1;
	int dir = (up) ? -1 : 1;
	vector<Transform*>transforms;
	vector<UIButton<Phone*>*> buttons;
	buttons.push_back(b);
	for (string buttName : names)
	{
		UIButton<Phone*>* but = new UIButton<Phone*>(entity_->getEntityMangr(), x, y + h * index * dir, w, h, SDL_Color{ COLOR(0x0CC00CCff) }, buttName, 0, 0, Resources::FontId::RobotoTest24, [](Phone* p) {}, this);
		buttons.push_back(but);
		transforms.push_back(but->getTransform());
		index++;
	}

	SDL_Rect rect{ x,y + h,w, tr_->getH() - h };
	auto scroll = b->createScroll(rect, transforms, 0, SDL_Color{ COLOR(0x880088ff) }, SDL_Color{ COLOR(0xCC) });
	b->setCB([buttons, scroll](Phone* state)
		{
			for (int i = 1; i < buttons.size(); i++)
			{
				auto& but = buttons[i];
				(but->isActive()) ? scroll->hide() : scroll->show();
				(but->isActive()) ? but->disable() : but->enable();
				cout << i - 1;
			}
		}, entity_->getComponent<Phone>(ecs::Phone));
	scroll->show();
	return buttons;
}
void Phone::destroyMessagesMenu()
{
	delete panel_;
	panel_ = nullptr;


	for (size_t i = 0; i < dropdown_.size(); i++)
	{
		delete dropdown_[i];
	};

}
/**/
