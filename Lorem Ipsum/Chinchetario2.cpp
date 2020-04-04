#include "Chinchetario2.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "ButtonClue.h"
Chinchetario2::Chinchetario2(LoremIpsum* game): State(game) 
{
    bottomPanel_ = entityManager_->addEntity(Layers::CharacterLayer);
    rightPanel_ = entityManager_->addEntity(Layers::LastLayer);
    double rightPanelW = game_->getGame()->getWindowWidth() / 6;
    double rightPanelH = game_->getGame()->getWindowHeight();
    Transform* rpTr = rightPanel_->addComponent<Transform>(game_->getGame()->getWindowWidth() - rightPanelW, 0.0, rightPanelW, rightPanelH);
    rightPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x00FFFFFF) });
    
    auto textTitle_ = rightPanel_->addComponent<Text>("", rpTr->getPos(), -1, game_->getGame()->getFontMngr()->getFont(Resources::RobotoTest24), 0);
    textTitle_->setSoundActive(false);
    auto textDescription_ = rightPanel_->addComponent<Text>("", rpTr->getPos() + Vector2D(0, 116), rpTr->getW(), game_->getGame()->getFontMngr()->getFont(Resources::RobotoTest24), 0);
    textDescription_->setSoundActive(false);

    double bottomPanelW = game_->getGame()->getWindowWidth() - rightPanelW;
    double bottomPanelH = game_->getGame()->getWindowHeight() / 5;
    bottomPanel_->addComponent<Transform>(0, game_->getGame()->getWindowHeight() - bottomPanelH, bottomPanelW, bottomPanelH);
    bottomPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x00FF00FF) });

    vector<Clue*> clues = game_->getStoryManager()->getPlayerClues();
    for (int i = 0; i < clues.size(); i++)
    {
        Clue* c = clues[i];
        Entity* entity = (c->entity_ = entityManager_->addEntity(Layers::DragDropLayer));
        double clueSize = 80;
        entity->addComponent<Transform>(clueSize + (2 * clueSize) * i, game_->getGame()->getWindowHeight() - (bottomPanelH / 2 + clueSize / 2), clueSize, clueSize);
        entity->addComponent<Rectangle>(SDL_Color{ COLOR(0xff00ffff) });
        entity->addComponent<DragDrop>(this, [](Chinchetario2* ch, Entity* e) {ch->clueDropped(e); });
        entity->addComponent<ButtonClue>([](Text* title, Text* description, string newT, string newD)
            {title->setText(newT); description->setText(newD); }, textTitle_, textDescription_, clues[i]->title_, clues[i]->description_);
        clueEntities_.push_back(entity);
    }
};
void Chinchetario2::update()
{

    State::update();
}

void Chinchetario2::render()
{

    State::render();
}

bool Chinchetario2::compareDragLayerIndex(int index, int layer) {
    bool bigger = (index > dragLayerIndex);
    if (bigger) {
        if (dragLayerIndex >= 0) {
            auto actualLayer = entityManager_->getLayer(layer);
            actualLayer[dragLayerIndex].get()->getComponent<DragDrop>(ecs::DragDrop)->deactivateDrag();
        }
        dragLayerIndex = index;
    }
    return bigger;
}

void Chinchetario2::clueDropped(Entity* e)
{
    vector<Clue*> clues = game_->getStoryManager()->getPlayerClues();
    size_t i = 0;
    while (e != clues[i]->entity_)
    {
        i++;
    }
    clues[i]->placed_ = !checkClueInBottomPanel(e);
    relocateClues();
}

void Chinchetario2::relocateClues()
{
    vector<Clue*> clues = game_->getStoryManager()->getPlayerClues();
    size_t size = clues.size();
    int numPlaced = 0;
    for (int i = 0; i < size; i++)
    {
        //(clueSize + (2 * clueSize) * i, game_->getGame()->getWindowHeight() - (bottomPanelH / 2 + clueSize / 2));
        if (clues[i]->placed_)
        {
            numPlaced++;
        }
        else
        {
            Transform* t = clues[i]->entity_->getComponent<Transform>(ecs::Transform);
            t->setPos(t->getW() + (2 * t->getW()) * (i - numPlaced), game_->getGame()->getWindowHeight() - (GETCMP2(bottomPanel_, Transform)->getH() / 2 + t->getH() / 2));
        }
        //GETCMP2()
    }
}

bool Chinchetario2::checkClueInBottomPanel(Entity * e)
{
    //Entity* e = clueEntities_[i];
    Transform* clueTr = GETCMP2(e, Transform);
    Transform* pannelTr = GETCMP2(bottomPanel_, Transform);

    SDL_Rect r{ pannelTr->getPos().getX(), pannelTr->getPos().getY(), pannelTr->getW() + clueTr->getW(),  pannelTr->getH() + clueTr->getH() };
    SDL_Point p{ clueTr->getPos().getX() + clueTr->getW(), clueTr->getPos().getY() + clueTr->getH() };

    return ((SDL_PointInRect(&p, &r)));
}

