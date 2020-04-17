#include "Maps.h"
#include "LoremIpsum.h"

Maps::Maps(LoremIpsum* game) : State(game) {
    sm_ = game_->getStoryManager();
    availableScenes_ = sm_->getAvailableScenes();
    background_ = entityManager_->addEntity(0);
    background_->addComponent<Transform>(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
    background_->addComponent<Sprite>(game->getGame()->getTextureMngr()->getTexture(Resources::TextureId::MapsBG));
    
    //añadimos los botones
    for (int i = 0; i < availableScenes_.size(); i++) {
        Vector2D mapPos = availableScenes_[i]->mapPos;
        scene_ = availableScenes_[i]->scene;
        Entity* icon = entityManager_->addEntity(3);
        icon->addComponent<Transform>(mapPos.getX(), mapPos.getY(), 30, 30);
        icon->addComponent<Rectangle>(SDL_Color{ COLOR(0xC0C0C0C0) });
        icon->addComponent<ButtonOneParametter<Maps*>>(std::function<void(Maps*)>([](Maps* m) { m->changeScene(); }), this);
        buttons_.push_back(icon);
    }
}

void Maps::update()
{

    State::update();
}

void Maps::render()
{

    State::render();
}

void Maps::changeScene()
{
    game_->getStateMachine()->PlayGame();
    game_->changeScene(scene_);
}