#include "AnimationSelector.h"
#include "SimpleMoveBehavior.h"

std::map<Resources::ActorID, std::function<void(Animator<int*>*)>> AnimationSelector::functions =
{
	{Resources::MacarenaMartinez, [](Animator<int*>* c)
		{
		/*
			Voy a guardar en el data[0] el AnimId de la animación de idle que toca. Porque estoy loco.
			En el data[1] hay un 1 si ha cambiado el animID del idle. Para actualizar
		*/
		//esto es un array
		int* data = c->getData();
		Entity* e = c->getEntity();
		if (data[0] == 0)
		{
			data[0] = Resources::MacarenaIdleAnim;
			data[1] = 1;
		}
		if (data[1] == 1)
		{
			c->changeAnim((Resources::AnimID)data[0]);
			data[1] = 0;
		}

		DialogComponent* d = e->getComponent<DialogComponent>(ecs::DialogComponent);
		if (d->getActualDialogIndex() == -1)return;
		if (d->getActualDialogIndex() == 4 && (d->getActualLineIndex() == 3 && data[3] == 0))
		{
			data[3] = 1;
			Entity* pelusa = StoryManager::instance()->getActors()[Resources::Pelusa]->getEntity();
			pelusa->addComponent<SimpleMoveBehavior>();
			pelusa->getComponent<Transform>(ecs::Transform)->setVel(Vector2D(-1,-0.5));
			pelusa->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
			pelusa->getComponent<Animator<int*>>(ecs::Animator)->getData()[0] = 1;
			pelusa->getComponent<Animator<int*>>(ecs::Animator)->changeAnim(Resources::CatWalkingAnim);
			pelusa->getComponent<Transform>(ecs::Transform)->setWH(12 * 8, 9 * 8);


		};
		//Facepalm cada vez que SDL la llama por un nombre incorrecto
		if ((d->getActualDialogIndex() == 4 && (d->getActualLineIndex() == 5 && data[5 + 4] == 0 || d->getActualLineIndex() == 8 && data[8 + 4] == 0))
			|| (d->getActualDialogIndex() == 3 && d->getActualLineIndex() == 4 && data[4 + 3] == 0)
			|| (d->getActualDialogIndex() == 2 && d->getActualLineIndex() == 4 && data[4 + 2] == 0))
		{
			int index = d->getActualLineIndex();
			int lIndex = d->getActualDialogIndex();
			data[index + lIndex] = 1;
			c->changeAnim(Resources::MacarenaFacepalmAnim);
			c->setFinishFunc([data,c](int* e)
				{
					c->changeAnim((Resources::AnimID)data[0]);
					c->setFinishFunc([](int*) {}, nullptr);
				}, nullptr);
		}
	}
},
{Resources::Pelusa,[](Animator<int*>* c)
	{
		int* data = c->getData();
		Entity* e = c->getEntity();
		Transform* tr = GETCMP2(e, Transform);
		Sprite* s = GETCMP2(e, Sprite);
		DialogComponent* d = e->getComponent<DialogComponent>(ecs::DialogComponent);
		if (tr->getPos().getX() <= 760)
		{
			tr->setVelX(0);
			c->setEnabled(false);
			Entity* maca = StoryManager::instance()->getActors()[Resources::MacarenaMartinez]->getEntity();
			maca->getComponent<Animator<int*>>(ecs::Animator)->getData()[1] = 1;
			maca->getComponent<Animator<int*>>(ecs::Animator)->getData()[0] = Resources::MacarenaCatIdleAnim;
		}
		else if (!e->hasComponent(ecs::SimpleMoveBehavior) && data[0] == 0)
		{
			c->setEnabled(false);
		}
		if (tr->getPos().getY() <= 505)
		{
			tr->setVelY(0);
		};
	}},
	{Resources::Capa, [](Animator<int*>* c)
		{
			if (c->getEntity()->hasComponent(ecs::SimpleMoveBehavior) && c->getEntity()->getComponent<Transform>(ecs::Transform)->getPos().getX() <= 300)
			{
				c->getEntity()->getComponent<Transform>(ecs::Transform)->setVel(Vector2D(0, 0));
				c->setSelectorFunction([](Animator<int*>* c) {});

				StoryManager::instance()->getActor(Resources::Capa)->Move(Resources::SceneID::Salon);
				Transform* tr = c->getEntity()->getComponent<Transform>(ecs::Transform);
				tr->setPos(Vector2D(930,410));
			}
			else if(!c->getEntity()->hasComponent(ecs::SimpleMoveBehavior))
			{
				DialogComponent* dc = c->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent);
				if (dc->getActualDialogIndex() == 1 && dc->getActualOptionIndex()==4 && dc->getActualLineIndex()==2)
				{
					c->getEntity()->addComponent<SimpleMoveBehavior>();
					SimpleMoveBehavior* move = c->getEntity()->getComponent<SimpleMoveBehavior>(ecs::SimpleMoveBehavior);
					Transform* tr = c->getEntity()->getComponent<Transform>(ecs::Transform);
					if (tr->getVel().getX() == 0)
					{
						Vector2D pos(-300, tr->getPos().getY());
						tr->setVel((pos - tr->getPos()).normalize());
					}
				}
			}

		}
	}
};
