#include "Chinchetario.h"
#include "LoremIpsum.h"
#include "DragDrop.h"
#include "ButtonClue.h"
#include "ScrollerLimited.h"
#include "Rectangle.h"
#include "Line.h"


Chinchetario::Chinchetario(LoremIpsum* game): State(game) 
{
	mng_ = entityManager_->addEntity();
    bottomPanel_ = entityManager_->addEntity(Layers::CharacterLayer);
    rightPanel_ = entityManager_->addEntity(Layers::LastLayer);
    double rightPanelW = game_->getGame()->getWindowWidth() / 6;
    double rightPanelH = game_->getGame()->getWindowHeight();
    Transform* rpTr = rightPanel_->addComponent<Transform>(game_->getGame()->getWindowWidth() - rightPanelW, 0.0, rightPanelW, rightPanelH);
    rightPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x00FFFFFF) });
    
    auto textTitle_ = rightPanel_->addComponent<Text>("", rpTr->getPos(), -1, Resources::RobotoTest24, 0);
    textTitle_->setSoundActive(false);
    auto textDescription_ = rightPanel_->addComponent<Text>("", rpTr->getPos() + Vector2D(0, 116), rpTr->getW(), Resources::RobotoTest24, 0);
    textDescription_->setSoundActive(false);

    double bottomPanelW = game_->getGame()->getWindowWidth() - rightPanelW;
    double bottomPanelH = game_->getGame()->getWindowHeight() / 5;
    bottomPanel_->addComponent<Transform>(0, game_->getGame()->getWindowHeight() - bottomPanelH, bottomPanelW, bottomPanelH);
    bottomPanel_->addComponent<Rectangle>(SDL_Color{ COLOR(0x00FF00FF) });

	scroll_ = mng_->addComponent<ScrollerLimited>(0, bottomPanelW);

    auto hidePannelButton = entityManager_->addEntity(Layers::LastLayer);
    hidePannelButton->addComponent<Transform>(5, game_->getGame()->getWindowHeight()-10-bottomPanelH/2, 40, 20);
    hidePannelButton->addComponent<Rectangle>(SDL_Color{ COLOR(0xffccccff)});
    
    hidePannelButton->addComponent<ButtonOneParametter<Chinchetario*>>(std::function<void(Chinchetario*)>([](Chinchetario* ch) {ch->toggleBottomPanel(); }), this);



    vector<Clue*> playerClues = game_->getStoryManager()->getPlayerClues();
    vector<Clue*> playercentralClues = game_->getStoryManager()->getPlayerCentralClues();
    vector<CentralClue> centralClues =
    {
        {
            Resources::ClueIDs::Central_Clue_1,
            {
                Resources::ClueIDs::Alfombra_Rota,
                Resources::ClueIDs::Arma_Homicida,
            }
        },
        {
             Resources::ClueIDs::Central_Clue_2,
            {
                Resources::ClueIDs::Arma_Homicida2
            }
        },
        {
             Resources::ClueIDs::Central_Clue_3,
            {
                Resources::ClueIDs::Arma_Homicida3
            }
        }
    };

    for (int i = 0; i < playerClues.size(); i++)
    {
        Clue* c = playerClues[i];
        Entity* entity = (c->entity_ = entityManager_->addEntity(Layers::DragDropLayer));
        double clueSize = 80;
        scroll_->addItem(entity->addComponent<Transform>(clueSize + (2 * clueSize) * i, game_->getGame()->getWindowHeight() - (bottomPanelH / 2 + clueSize / 2), clueSize, clueSize), i);
        entity->addComponent<Rectangle>(SDL_Color{ COLOR(0xff00ffff) });
        entity->addComponent<DragDrop>(this, [](Chinchetario* ch, Entity* e) {ch->clueDropped(e); });
        entity->addComponent<ButtonClue>([](Text* title, Text* description, string newT, string newD)
            {title->setText(newT); description->setText(newD); }, textTitle_, textDescription_, playerClues[i]->title_, playerClues[i]->description_);
        //entity->addComponent<Line>(Vector2D{ 0,0 }, Vector2D{0,0}, 3);
        clueEntities_.push_back(entity);
    }

    for (int i = 0; i < centralClues.size(); i++) {
        //guardamos los datos de la pista actual
        Clue* actualClue = playercentralClues[centralClues[i].id_];
        Entity* actualClueEntity = actualClue->entity_;
        Transform* clueTR = GETCMP2(actualClueEntity, Transform);
        //Las pistas se dibujarán alrededor de la circunferencia definida por estos datos:
        double angle= 360 / (centralClues[i].links_.size());
        double rd = clueTR->getH() / 2;
        //Colocamos cada chincheta en su sitio (cada pista central tendrá x número de chinchetas)
        for (int j = 0; j < centralClues[i].links_.size(); j++) {
            double rad = M_PI / 180;
            double pinY = rd * cos(rad * (180+angle*j)); //posición en X y en Y LOCALES de la chincheta
            double pinX = rd * sin(rad * (180 + angle * j));
            Vector2D pinPos = Vector2D(pinX +rd, pinY+rd); //posición en X y en Y GLOBALES de la chincheta
            pinPos = pinPos + clueTR->getPos();
            //Creamos una entidad con la posición que acabamos de calcular
            Entity* pin = entityManager_->addEntity(Layers::LastLayer); //La layer la puse para testear porque es la que está más arriba
            int pinSize = 10; int pinOffset = pinSize / 2;
            pin->addComponent<Transform>(pinPos.getX() - pinOffset, pinPos.getY() - pinOffset, pinSize, pinSize)->setParent(clueTR);  
            
            switch (actualClue->type_) 
            {
                case Resources::ClueType::Object:
                    pin->addComponent<Rectangle>(SDL_Color{ COLOR(0xff000000) });
                    break;
                case Resources::ClueType::Person:
                    pin->addComponent<Rectangle>(SDL_Color{ COLOR(0x00ff0000) });
                    break;
                case Resources::ClueType::Place:
                    pin->addComponent<Rectangle>(SDL_Color{ COLOR(0x0000ffff) });
                    break;
            }
        }
       
    }
};
void Chinchetario::update()
{
    State::update();
}

void Chinchetario::render()
{

    State::render();
}

bool Chinchetario::compareDragLayerIndex(int index, int layer) {
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

void Chinchetario::clueDropped(Entity* e)
{
    vector<Clue*> clues = game_->getStoryManager()->getPlayerClues();
    size_t i = 0;
    while (e != clues[i]->entity_)
    {
        i++;
    }
	bool b = !checkClueInBottomPanel(e);
	if (b && !clues[i]->placed_) scroll_->removeItem(e->getComponent<Transform>(ecs::Transform), i);
	else if (!b && clues[i]->placed_)scroll_->addItem(e->getComponent<Transform>(ecs::Transform), i);
	clues[i]->placed_ = b;
    //if (!clues[i]->placed_)
    //    clues[i]->entity_->setLayer(Layers::LastLayer);
    relocateClues();
}

void Chinchetario::relocateClues()
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


    if (numPlaced == clues.size())
        hideBottomPanel();
}

bool Chinchetario::checkClueInBottomPanel(Entity * e)
{
    //Entity* e = clueEntities_[i];
    Transform* clueTr = GETCMP2(e, Transform);
    Transform* pannelTr = GETCMP2(bottomPanel_, Transform);

    SDL_Rect r{ pannelTr->getPos().getX(), pannelTr->getPos().getY(), pannelTr->getW() + clueTr->getW(),  pannelTr->getH() + clueTr->getH() };
    SDL_Point p{ clueTr->getPos().getX() + clueTr->getW(), clueTr->getPos().getY() + clueTr->getH() };

    return (bottomPanel_->getActive() && (SDL_PointInRect(&p, &r)));
}

void Chinchetario::setUnplacedClues(bool b)
{
    for (auto& c : game_->getStoryManager()->getPlayerClues())
    {
        if(!c->placed_)
            c->entity_->setActive(b);
    }
}