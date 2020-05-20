#include "State.h"
#include "LoremIpsum.h"
State::State(LoremIpsum* game)
{
	game_ = game;
	entityManager_ = new EntityManager(game_->getGame(), this);
	camera_ = new Camera();

	popUpMessage_ = entityManager_->addEntity(5);
	popUpMessage_->setUI(true);
	int x = SDLGame::instance()->getWindowWidth() / 2 - 200;
	int y = SDLGame::instance()->getWindowHeight() / 2 - 200;
	popUpMessage_->addComponent<Transform>(x, y, 400, 400);
	popUpMessage_->addComponent<Sprite>()->setTexture(Resources::MessageUIPanel);
	popUpMessage_->addComponent<Text>("TestText", Vector2D(x + 40, y + 40), 340, Resources::RobotoTest24, 0);
	auto but = popUpMessage_->addComponent<ButtonOneParametter<int>>([](int i) {LoremIpsum::instance()->getStateMachine()->actualState()->hidePopUpMessage(); }, 0);
	but->setOffsets(-26 * 4, -81 * 4, 26 * 8, 81 * 4);
	popUpMessage_->setActive(false);
}
void State::update()
{
	if (active_)
		entityManager_->update();
	else destroy();
}

void State::render()
{

	entityManager_->draw();
}

void State::showPopUpMessage(string text, std::function<void(int)> f)
{
	popUpMessage_->setActive(true);
	Text* t = GETCMP2(popUpMessage_, Text);
	auto but = popUpMessage_->getComponent<ButtonOneParametter<int>>(ecs::Button);
	t->setText(text);
	if (f != nullptr)
	{
		but->setCallback(f, 0);
	}

	int ochenta = t->getNumLines() * t->getCharH() + 40;
	int h = ochenta + ochenta / 2;
	if (h > 8 * SDLGame::instance()->getWindowHeight() / 10)
		h = 8 * SDLGame::instance()->getWindowHeight() / 10;
	if (h < 400)
		h = 400;

	Transform* tr = popUpMessage_->getComponent<Transform>(ecs::Transform);
	tr->setH(h);
	tr->setPosY((SDLGame::instance()->getWindowHeight() - h) / 2);
	t->setPos(tr->getPos() + Vector2D(40, 40));
	but->setOffsets(-26 * 4, -(81.0 * h / 100.0), 26 * 8, 86.0 * h / 100.0);
}

void State::hidePopUpMessage()
{
	popUpMessage_->setActive(false);
}

void State::destroy() 
{
	game_->getStateMachine()->destroyActual();
}
