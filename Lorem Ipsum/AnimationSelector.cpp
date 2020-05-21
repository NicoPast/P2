#include "AnimationSelector.h"
std::map<Resources::ActorID, std::function<void(Animator<int*>*)>> AnimationSelector::functions =
{
	{Resources::MacarenaMartinez, [](Animator<int*>* c)
		{
			int* data = c->getData();
			Entity* e = c->getEntity();
			/*
			Comida = 6, 9
			*/
			DialogComponent* d = e->getComponent<DialogComponent>(ecs::DialogComponent);
			if (d->getActualDialogIndex() == -1)return;
			if (d->getActualDialogIndex() == 4 && (d->getActualLineIndex() == 6 || d->getActualLineIndex() == 9))
			{

				c->changeAnim(Resources::MacarenaFacepalmAnim);
				c->setFinishFunc([c](int* e) 
					{
						c->changeAnim(Resources::MacarenaCatIdleAnim); 
						c->setFinishFunc([](int*) {}, nullptr);
					}, nullptr);
			}

		}
	}
};
