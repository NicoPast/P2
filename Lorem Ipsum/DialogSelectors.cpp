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
	{
		Resources::MacarenaMartinez, [](DialogComponent* d) 
	{
		StoryManager* sm = StoryManager::instance();
		enum dialogNames
		{
			Saludo = 0,
			NoEvento = 1,
			EventoMalHecho = 2,
			EventoBienHecho = 3,
			EventoComida = 4,
			EventoComidaCorto = 5
		};
		auto status = d->getDialogStatus();


		//Si ya has terminado el caso y has hablado con Maca, diálogo corto
		if (d->dialogs_[EventoComida]->active_ && status[EventoComida])
			d->availableDialogs = { d->dialogs_[EventoComidaCorto] };
		
		//Si solo has desbloqueado el evento de comida, activa ese directamente
		else if (d->dialogs_[EventoComida]->active_)
		{
			d->availableDialogs = { d->dialogs_[EventoComida] };
			sm->addAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo));
		}
		
		//Si has creado el evento bien activa este diálogo directamente
		else if (d->dialogs_[EventoBienHecho]->active_)
		{
			d->availableDialogs = { d->dialogs_[EventoBienHecho] };
		}

		//Si has creado el evento mal activa este diálogo directamente
		else if (d->dialogs_[EventoMalHecho]->active_)

			d->availableDialogs = { d->dialogs_[EventoMalHecho] };


		//Si no has hablado con ella todavía se ve primero la principal. Si vuelve a entrar aquí y ya has hablado con ella se ve "no evento"
		else if (status[Saludo])
		{
			d->availableDialogs = { d->dialogs_[NoEvento] };
		}
		else 
		{
			d->availableDialogs = { d->dialogs_[Saludo] };
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
		}

	}},
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
		}

	}
}
};