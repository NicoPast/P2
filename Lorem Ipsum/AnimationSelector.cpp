#include "AnimationSelector.h"
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
			if (d->getActualDialogIndex() == 4 && (d->getActualLineIndex() == 4 && data[4]==0 || d->getActualLineIndex() == 7 && data[7] == 0))
			{
				int index = d->getActualLineIndex();
				data[index] =1;
				c->changeAnim(Resources::MacarenaFacepalmAnim);
				c->setFinishFunc([data,c](int* e) 
					{
						c->changeAnim((Resources::AnimID)data[0]); 
						c->setFinishFunc([](int*) {}, nullptr);
					}, nullptr);
			}
		}
	}

};
