#include "DialogSelectors.h"
#include "DialogComponent.h"
/*
Los enums de más abajo no hacen falta, solo hacen el código más claro. Si tienes dudas sobre en qué orden se están guardando en el vector los dialogos del 
componente hay una carpeta en Assets/Dialogs/ que se llama Actors que tiene archivos de texto con este enum es copiar y pegar, fácil y para toda la familia.
Si no aparece el archivo de tu actor puedes:
	-Revisar en el editor de dialogos que el dialogo está asociado a un actor.
	-Ejecutar el juego y cerrarlo.
	-Poner breakpoints e intentar verlo tu xD
	-Llamar a un fellow programmer para ver que coño pasa
	-Llorar en una esquina.
En ese orden de importancia son de más a menos eficaz. El último aunque no eficaz para el problema en cuestión, hace falta de vez en cuando. Ánimo campeón :D
*/

std::map<Resources::ActorID, std::function<void(DialogComponent*)>> DialogSelectors::functions =

{
		{Resources::MacarenaMartinez, [](DialogComponent* d) 
	{
		StoryManager* sm = StoryManager::instance();
		enum dialogNames
		{
			Saludo = 0,
			NoEvento = 1,
			EventoMalHecho = 2,
			EventoBienHecho = 3,
			EventoComida = 4,
			EventoComidaCorto = 5,
			CasoNuevo = 6
		};
		auto status = d->getDialogStatus();

		if (sm->getGameCase() != 0)
		{
			d->availableDialogs = { d->dialogs_[CasoNuevo] };
		}
		else 
		{

			//Si ya has terminado el caso y has hablado con Maca, diálogo corto
			if (d->dialogs_[EventoComida]->active_ && status[EventoComida])
			{
				d->availableDialogs = { d->dialogs_[EventoComidaCorto] };
			}
		
			//Si solo has desbloqueado el evento de comida, activa ese directamente
			else if (d->dialogs_[EventoComida]->active_)
			{
				d->availableDialogs = { d->dialogs_[EventoComida] };
				d->setCallback([sm](DialogComponent*) {sm->addAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo)); }, EventoComida, 0, 22);
			}
		
			//Si has creado el evento bien activa este diálogo directamente
			else if (d->dialogs_[EventoBienHecho]->active_)
			{
				d->availableDialogs = { d->dialogs_[EventoBienHecho] };
				d->setCallback([sm](DialogComponent*) {sm->addPlayerClue(Resources::Tut_Cent_MotivoEntrada); },EventoBienHecho,0,4);
			}

			//Si has creado el evento mal activa este diálogo directamente
			else if (d->dialogs_[EventoMalHecho]->active_)
			{
				d->availableDialogs = { d->dialogs_[EventoMalHecho] };
				d->setCallback([sm](DialogComponent*) {sm->addPlayerClue(Resources::Tut_Cent_MotivoEntrada); }, EventoMalHecho, 0, 4);
			}


			//Si no has hablado con ella todavía se ve primero la principal. Si vuelve a entrar aquí y ya has hablado con ella se ve "no evento"
			else if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[NoEvento] };
			}
			else 
			{
				d->availableDialogs = { d->dialogs_[Saludo] };

				//todo esto se quita para la release
				sm->addAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::HabitacionCarlos));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::HabitacionAfur));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::HabitacionSabrina));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::HabitacionErnesto));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::Salon));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::CasetaJardin));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::Sotano));
				sm->addAvailableScene(sm->getScene(Resources::SceneID::Bosque));
			}
		
		}
	}
	},
	{
		Resources::Capo, [](DialogComponent* d){
			//el capo tiene dos diálogos. Uno para el principio (el del contrato) y uno corto, con todas las opciones de diálogo
			//puede que en el futuro cambie

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
				Opciones = 1,
					Jardinero = 1,
					JardinCorto = 2,
					Afur=3,
					AfurCorto=4,

			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();


			//la primera vez, versión larga. Luego, versión con opciones
			//faltan:
			//si se ha encontrado pista (Jardín descuidado), se activa la opción jardinero. Cuando utilizas esta opción, cambia a la versión corta
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
					d->dialogs_[Opciones]->options_[Jardinero].active_ = !option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[Afur].active_ = !option[Opciones][Afur];
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = option[Opciones][AfurCorto];
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };


				//aqui por ejemplo quiero que al terminar este diálogo y el de la capa el del jardinero version corta, por ejemplo
				//no se como lo quiero guardar aja
				d->setCallback([d](DialogComponent* dc)
					{
						//data 0 contador de los diálogos estamos trakeando
						d->getData()[0]++; 
						if (d->getData()[0] == 1)
						{
							string posvale = "posvale";
							d->setDialogFinishedCallback([posvale](DialogComponent* c)
								{
									StoryManager::instance()->thinkOutLoud({ posvale }); 
								});
						}
					}, Saludo, 0, 4);

				//todas las pistas

				sm->addPlayerClue(Resources::ClueID::Prin_ErnestoPolo);
				sm->addPlayerClue(Resources::ClueID::Prin_SabrinaPolo);
				sm->addPlayerClue(Resources::ClueID::Prin_Contrato);
				sm->addPlayerClue(Resources::ClueID::Prin_Cent_MuerteHija);

			}
		}
	},
	{
		Resources::Capa, [](DialogComponent* d)
		{
			//la tiene dos diálogos. Uno para el principio (el del contrato) y uno corto, con todas las opciones de diálogo
			//puede que en el futuro cambie

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
				Opciones = 1,
				Jardinero = 2,
				JardinCorto = 3
			};
			auto status = d->getDialogStatus();

			//la primera vez, versión larga. Luego, versión con opciones
			//faltan:
			//si se ha encontrado pista (Jardín descuidado), se activa la opción jardinero. Cuando utilizas esta opción, cambia a la versión corta
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				sm->addPlayerClue(Resources::ClueID::Prin_UrsulaPolo);
			}

		}
	},
	{
		Resources::CarlosI, [](DialogComponent* d)
		{
			//la tiene dos diálogos. Uno para el principio (el del contrato) y uno corto, con todas las opciones de diálogo
			//puede que en el futuro cambie

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
				Opciones = 1,
				Jardinero = 2,
				JardinCorto = 3
			};
			auto status = d->getDialogStatus();

			//la primera vez, versión larga. Luego, versión con opciones
			//faltan:
			//si se ha encontrado pista (Jardín descuidado), se activa la opción jardinero. Cuando utilizas esta opción, cambia a la versión corta
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				sm->addPlayerClue(Resources::ClueID::Prin_CarlosCastro);
			}

		}
	},
	{
		Resources::CarlosII, [](DialogComponent* d)
		{
			//la tiene dos diálogos. Uno para el principio (el del contrato) y uno corto, con todas las opciones de diálogo
			//puede que en el futuro cambie

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
				Opciones = 1,
				Jardinero = 2,
				JardinCorto = 3
			};
			auto status = d->getDialogStatus();

			//la primera vez, versión larga. Luego, versión con opciones
			//faltan:
			//si se ha encontrado pista (Jardín descuidado), se activa la opción jardinero. Cuando utilizas esta opción, cambia a la versión corta
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				sm->addPlayerClue(Resources::ClueID::Prin_AfurPolo);
				sm->addPlayerClue(Resources::ClueID::Prin_ZapatosBarro);
			}

		}
	}
};