#include "ClueCallbacks.h"
#include "LoremIpsum.h"

map<Resources::ClueID, std::function<void()>> ClueCallbacks::clueCBs =
{

	{
		Resources::ClueID::Tut_SillaRota, []()
		{
			StoryManager* sm =  StoryManager::instance();
			sm->addPlayerClue(Resources::Prin_Cent_Discusion);
			sm->addPlayerClue(Resources::Prin_Cent_MuerteGus);
			sm->addPlayerClue(Resources::Prin_Cent_MuerteHija);
			sm->addPlayerClue(Resources::Prin_Cent_MuerteJardinera);
			sm->addPlayerClue(Resources::Prin_OrdenAsesinato);
			sm->addPlayerClue(Resources::Prin_PanueloRojo);
			sm->addPlayerClue(Resources::Prin_HabSabrina);
			sm->addPlayerClue(Resources::Prin_UrsulaPolo);
			sm->addPlayerClue(Resources::Prin_Jardinera);
			sm->addPlayerClue(Resources::Prin_ErnestoPolo);
			//LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("DAMN, short message");
		}
	},
	{
		Resources::ClueID::Tut_PapelesDesordenados, []()
		{
			StoryManager* sm =  StoryManager::instance();
			//LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("Has completado una pista. Esto es un texto muy largo para ver como se comporta en el texto para el pop up. Por ahroa solo funciona en un estado, y eso me ahce sad. Pero podemos, en teoría hacer que distinga entre estados y que pueda usar uno similar en el mapa, chinchetario... :D");
		}
	},
	{
		Resources::ClueID::Prin_BalaCasquillo, []()
		{
			//	StoryManager* sm = StoryManager::instance();
			//	auto clues = sm->getClues();
			//	if (sm->hasClue(clues[Resources::ClueID::Prin_BalaSinSangre]))
			//	{
			//		string palCallback = "Parece que este lugar está bastante relacionado con la muerte. Es el momento de probar esa nueva aplicación que me hizo el profesor León en mi marcapasos.";
			//		DialogComponent* dcComics = sm->dialogPortrait->getComponent<DialogComponent>(ecs::DialogComponent);
			//		//dcComics->setCallback([palCallback](DialogComponent* dc) {StoryManager::instance()->thinkOutLoud({ palCallback }); }, 0, 0, 0);
			//		dcComics->getDialog(0)->options_[0].lines_.push_back(DialogLine(0, palCallback));
			//	}
		}

	},
	{
		Resources::ClueID::Prin_PanueloRojo, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_PistolaSilenciador]))
			{

				vector<string>lines = { "(¿¿Y esos gritos??)", "(¿Qué coño habrá pasado?)" };
				vector<string>lines2 = { "Qué tragedia. El caso no hace más que complicarse.", "Supongo que toca dar el pésame." };


				sm->thinkOutLoud(lines,
					[sm](DialogComponent* dc)
					{
						Animator<int>* anim = sm->backgroundViewer_->getComponent<Animator<int>>(ecs::Animator);
						anim->setEnabled(true);
						anim->changeAnim(Resources::FadeInAnim);
						//anim->setFinishFunc([anim](int a)
						//	{}, 0);
					});
				sm->thinkOutLoud(lines2, [](DialogComponent* dc)
				{
					Animator<int>* anim = StoryManager::instance()->backgroundViewer_->getComponent<Animator<int>>(ecs::Animator);
					anim->changeAnim(Resources::FadeOutAnim);
					anim->setFinishFunc([anim](int a)
						{
							anim->setEnabled(false);
						}, 0);
				});

				sm->getActor(Resources::Capo)->Move(Resources::SceneID::Salon);
				sm->getActor(Resources::Capo)->getEntity()->getComponent<Transform>(ecs::Transform)->setPosX(450.0);
				sm->getActor(Resources::CarlosI)->Move(Resources::SceneID::HabitacionCarlos);
				sm->getActor(Resources::CarlosI)->getEntity()->getComponent<Transform>(ecs::Transform)->setPos(Vector2D(763, 340));
				sm->getActor(Resources::Capa)->getEntity()->getComponent<Transform>(ecs::Transform)->setPos(Vector2D(960,340));
				Entity* carlitos = sm->getActor(Resources::CarlosII)->getEntity();
				carlitos->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(false);
				carlitos->getComponent<Interactable>(ecs::Interactable)->setEnabled(false);

				sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 2;

			}
		}

	},
	{
		Resources::ClueID::Prin_PistolaSilenciador, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_PanueloRojo]))
			{
				vector<string>lines = { "(¿¿Y esos gritos??)", "(¿Qué coño habrá pasado?)" };
				vector<string>lines2 = { "Qué tragedia. El caso no hace más que complicarse", "Supongo que toca dar el pésame." };
				sm->thinkOutLoud(lines,
					[sm](DialogComponent* dc)
					{
						Animator<int>* anim = sm->backgroundViewer_->getComponent<Animator<int>>(ecs::Animator);
						anim->setEnabled(true);
						anim->changeAnim(Resources::FadeInAnim);
						anim->setFinishFunc([anim](int a)
							{
								//Aqui es oscuro, cambiar de escena, que el player no se mueva ni interactue i think
							}, 0);
					});
				sm->thinkOutLoud(lines2, [](DialogComponent* dc)
					{
						Animator<int>* anim = StoryManager::instance()->backgroundViewer_->getComponent<Animator<int>>(ecs::Animator);
						anim->changeAnim(Resources::FadeOutAnim);
						anim->setFinishFunc([anim](int a)
							{
								anim->setEnabled(false);
							}, 0);
					});
				sm->getActor(Resources::Capo)->Move(Resources::SceneID::Salon);
				sm->getActor(Resources::Capo)->getEntity()->getComponent<Transform>(ecs::Transform)->setPosX(450.0);
				sm->getActor(Resources::CarlosI)->Move(Resources::SceneID::HabitacionCarlos);
				sm->getActor(Resources::CarlosI)->getEntity()->getComponent<Transform>(ecs::Transform)->setPos(Vector2D(763, 340));
				sm->getActor(Resources::Capa)->getEntity()->getComponent<Transform>(ecs::Transform)->setPos(Vector2D(960, 340));
				Entity* carlitos = sm->getActor(Resources::CarlosII)->getEntity();
				carlitos->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(false);
				carlitos->getComponent<Interactable>(ecs::Interactable)->setEnabled(false);

				sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 2;

			}
		}

	},
	{
		Resources::ClueID::Prin_ContratoGus, []()
		{
			StoryManager* sm = StoryManager::instance();

			sm->addPlayerClue(Resources::Prin_Cent_MuerteGus);
			
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_PapelesHerencia]) && sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] < 5)
			{
				sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 4;
			}
		}

	},
	{
		Resources::ClueID::Prin_Llave, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 5;
		}

	}, 
	{
		Resources::ClueID::Prin_PapelesHerencia, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_ContratoGus]) && sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] < 5)
			{
				sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 4;
			}
			sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 6;
		}
	},
	{
		Resources::ClueID::Prin_Foto, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_OrdenAsesinato]))
			{
				sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 6;
			}
		}
	},
	{
		Resources::ClueID::Prin_OrdenAsesinato, []()
		{
			StoryManager* sm = StoryManager::instance();
			auto clues = sm->getClues();
			if (sm->hasClue(clues[Resources::ClueID::Prin_Foto]))
			{
				sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 6;
			}
		}
	},
};


map<Resources::ClueID, std::function<void()>> ClueCallbacks::centralClueCBs =
{
	//si hay dudas sobre el orden en el que se guardan los dialogos revise la carpeta Assets/Dialogs/Actors
	//si hay más dudas vea el comentario de dialogSelector.cpp
	{	Resources::ClueID::Tut_Cent_DesordenHabitacion, []()
		{
			Resources::ClueID id = Resources::ClueID::Tut_Cent_DesordenHabitacion;
			StoryManager* sm = StoryManager::instance();
			Entity* macarena = sm->getActors()[Resources::ActorID::MacarenaMartinez]->getEntity();
			DialogComponent* macarenaDialg = GETCMP2(macarena, DialogComponent);

			if (sm->getCentralClues()[id]->isEvent_)
			{
				if (sm->getCentralClues()[id]->isCorrect_)
				{

					macarenaDialg->setDialogActive(3, true);
					macarenaDialg->setDialogActive(2, false);
				}
				else if (!sm->getCentralClues()[id]->isCorrect_)
				{
					macarenaDialg->setDialogActive(3, false);
					macarenaDialg->setDialogActive(2, true);
				}
			}
			else
			{
				macarenaDialg->setDialogActive(3, false);
				macarenaDialg->setDialogActive(2, false);
			}

		}},
	{
		Resources::ClueID::Tut_Cent_MotivoEntrada, []() 
		{
			StoryManager* sm = StoryManager::instance();
			Entity* macarena = sm->getActors()[Resources::ActorID::MacarenaMartinez]->getEntity();
			DialogComponent* macarenaDialg = GETCMP2(macarena, DialogComponent);
			//Este evento si se forma siempre está bien, no hace falta comprobar con el storymanager nada
			macarenaDialg->setDialogActive(4, sm->getCentralClues()[Resources::ClueID::Tut_Cent_MotivoEntrada]->isEvent_);
			LoremIpsum::instance()->getStateMachine()->actualState()->showPopUpMessage("¡Gracias por jugar a la demo!");
		}
	}
};