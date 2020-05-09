#include "DialogSelectors.h"
#include "DialogComponent.h"
/*
Los enums de m�s abajo no hacen falta, solo hacen el c�digo m�s claro. Si tienes dudas sobre en qu� orden se est�n guardando en el vector los dialogos del 
componente hay una carpeta en Assets/Dialogs/ que se llama Actors que tiene archivos de texto con este enum es copiar y pegar, f�cil y para toda la familia.
Si no aparece el archivo de tu actor puedes:
	-Revisar en el editor de dialogos que el dialogo est� asociado a un actor.
	-Ejecutar el juego y cerrarlo.
	-Poner breakpoints e intentar verlo tu xD
	-Llamar a un fellow programmer para ver que co�o pasa
	-Llorar en una esquina.
En ese orden de importancia son de m�s a menos eficaz. El �ltimo aunque no eficaz para el problema en cuesti�n, hace falta de vez en cuando. �nimo campe�n :D
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
			EventoComida =4
		};
		auto status = d->getDialogStatus();
	
		//Si no has hablado con ella todav�a se ve primero la principal. Si vuelve a entrar aqu� y ya has hablado con ella se ve "no evento"
		if (status[Saludo])
			d->availableDialogs = { d->dialogs_[NoEvento] };
		else
			d->availableDialogs = { d->dialogs_[Saludo] };
		
		/* Casos excluyentes y prioritarios al anteririor*/
		if (d->dialogs_[EventoMalHecho]->active_)
		{
			//Si has creado el evento mal activa este di�logo directamente
			d->availableDialogs = { d->dialogs_[EventoMalHecho] };
		}
		else if (d->dialogs_[EventoBienHecho]->active_)
		{
			//Si has creado el evento bien activa este di�logo directamente
			d->availableDialogs = { d->dialogs_[EventoBienHecho] };
		}
		else if(d->dialogs_[EventoComida]->active_)
		{
			//Si solo has desbloqueado el vento de comida, activa ese directamente
			d->availableDialogs = { d->dialogs_[EventoComida] };
		}
		/*
		Para completar este callback y el di�logo con Macarena Ana ha comentado que estar�a bien a�adir otra versi�n de EventoBienHecho m�s corta que
		recuerde al jugador pedir un uber por tel�fono. Ser�a tan sencillo como a�adir !status[EventoBienHecho] y cuando sea true mostrar la versi�n corta.
		:D
		*/
	}}

};