#include "Maps.h"
#include "LoremIpsum.h"
#include "StoryManager.h"
Maps::Maps(LoremIpsum* game) : State(game) {
    sm_ = game_->getStoryManager();
    availableScenes_ = sm_->getAvailableScenes();
    background_ = entityManager_->addEntity(0);
    background_->addComponent<Transform>(0, 0, game_->getGame()->getWindowWidth(), game_->getGame()->getWindowHeight());
    background_->addComponent<Sprite>(game->getGame()->getTextureMngr()->getTexture(Resources::TextureID::MapsBG));
    
    //añadimos los botones
    for (int i = 0; i < availableScenes_.size(); i++) {
        Vector2D mapPos = availableScenes_[i]->mapPos;
        Resources::SceneID scene = availableScenes_[i]->scene;
        Entity* icon = entityManager_->addEntity(3);
        icon->addComponent<Transform>(mapPos.getX(), mapPos.getY(), 30, 30);
        icon->addComponent<Sprite>(availableScenes_[i]->mapIcon);
        StoryManager* sm = StoryManager::instance();
        icon->addComponent<ButtonOneParametter<LoremIpsum*>>(std::function<void(LoremIpsum*)>([sm,scene](LoremIpsum* g)
            {
                if(sm->getSceneCallback(scene)!=nullptr)sm->getSceneCallback(scene)();
                g->getStateMachine()->PlayGame();
                g->getStoryManager()->changeScene(scene); 
            }), game_);
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
