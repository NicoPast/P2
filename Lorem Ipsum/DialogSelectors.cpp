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
					Afur = 3,
					AfurCorto = 4,
					ConversacionUrsula = 5,

			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();


			//la primera vez, versión larga. Luego, versión con opciones
			//
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
				if (d->getData()[1] >= 1)
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = !option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = option[Opciones][Jardinero];

					if (d->getData()[1] >= 2)
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = !option[Opciones][Afur];
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = option[Opciones][AfurCorto];

						if (d->getData()[1] >= 3)
						{
							d->dialogs_[Opciones]->options_[Afur].active_ = !option[Opciones][ConversacionUrsula];
						}
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;
					d->dialogs_[Opciones]->options_[Afur].active_ = false;
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;
					d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = false;
				}

			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };

				if (d->getData()[0] == 0)
				{
					d->setCallback([sm, d](DialogComponent* dc)
						{
							//contador para saber con cuántos miembros de la familia has hablado. 
							//sirve para desbloquear la caseta del jardín y el bosque

							d->getData()[0]++;

							if (d->getData()[0] >= 4)
							{
								string posvale = "(Si quiero encontrar algo que me sea de utilidad, no debería limitarme a buscar en la casa. Podría ver el bosque donde han enterrado a Sabrina)";
								d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
									{
										sm->thinkOutLoud({ posvale });
										sm->addAvailableScene(sm->getScene(Resources::SceneID::Bosque));
										sm->getDoor(Resources::DoorID::pEntradaBosque)->setLocked(false);
										sm->getDoor(Resources::DoorID::pEntradaCaseta)->setLocked(false);
										c->clearDialogFinishedCB();
									});
							}

							//todas las pistas
							sm->addPlayerClue(Resources::ClueID::Prin_ErnestoPolo);
							sm->addPlayerClue(Resources::ClueID::Prin_SabrinaPolo);
							sm->addPlayerClue(Resources::ClueID::Prin_Contrato);
							sm->addPlayerClue(Resources::ClueID::Prin_Cent_MuerteHija);

							d->clearCB();
						}, Saludo, 0, 4);
				}
				

			}
		}
	},
	{
		Resources::Capa, [](DialogComponent* d)
		{
			//la capa tiene dos diálogos. Uno para el principio (el del contrato) y uno corto, con todas las opciones de diálogo
			//puede que en el futuro cambie

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
				Opciones = 1,
					Jardinero = 1,
					JardinCorto = 2,
					Afur = 3,
					ConversacionUrsula = 4,
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();
			//la primera vez, versión larga. Luego, versión con opciones
			//faltan:
			//si se ha encontrado pista (Jardín descuidado), se activa la opción jardinero. Cuando utilizas esta opción, cambia a la versión corta
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
				int i = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];

				if (i >= 1)
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = !option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = option[Opciones][Jardinero];

					if (i >= 2)
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = !option[Opciones][Afur];

						if (i >= 3)
						{
							d->dialogs_[Opciones]->options_[Afur].active_ = !option[Opciones][ConversacionUrsula];
						}
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;
					d->dialogs_[Opciones]->options_[Afur].active_ = false;
					d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = false;
				}
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						//contador para saber con cuántos miembros de la familia has hablado. 
						//sirve para desbloquear la caseta del jardín y el bosque
						int i = ++sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[0];
						if (i>=4)
						{
							string posvale = "(Si quiero encontrar algo que me sea de utilidad, no debería limitarme a buscar en la casa. Podría ver el bosque donde han enterrado a Sabrina)";
							d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
								{
									sm->thinkOutLoud({ posvale });
									sm->addAvailableScene(sm->getScene(Resources::SceneID::Bosque));
									sm->getDoor(Resources::DoorID::pEntradaBosque)->setLocked(false);
									sm->getDoor(Resources::DoorID::pEntradaCaseta)->setLocked(false);
									c->clearDialogFinishedCB();
								});
						}

						//todas las pistas
						sm->addPlayerClue(Resources::ClueID::Prin_UrsulaPolo);
						d->clearCB();

					}, Saludo, 0, 5);



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
					Jardinero = 1,
					JardinCorto = 2,
					Afur = 3,
					AfurCorto = 4,
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();
			//la primera vez, versión larga. Luego, versión con opciones
			//faltan:
			//si se ha encontrado pista (Jardín descuidado), se activa la opción jardinero. Cuando utilizas esta opción, cambia a la versión corta
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };

				int i = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];

				if (i >= 1)
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = !option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = option[Opciones][Jardinero];
					if (i >= 2)
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = !option[Opciones][Afur];
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;
					d->dialogs_[Opciones]->options_[Afur].active_ = false;
				}
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						//contador para saber con cuántos miembros de la familia has hablado. 
						//sirve para desbloquear la caseta del jardín y el bosque
						int i = ++sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[0];
						if (i >= 4)
						{
							string posvale = "(Si quiero encontrar algo que me sea de utilidad, no debería limitarme a buscar en la casa. Podría ver el bosque donde han enterrado a Sabrina)";
							d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
								{
									sm->thinkOutLoud({ posvale });
									sm->addAvailableScene(sm->getScene(Resources::SceneID::Bosque));
									sm->getDoor(Resources::DoorID::pEntradaBosque)->setLocked(false);
									sm->getDoor(Resources::DoorID::pEntradaCaseta)->setLocked(false);
									c->clearDialogFinishedCB();

								});
						}

						//todas las pistas
						sm->addPlayerClue(Resources::ClueID::Prin_CarlosCastro);
						d->clearCB();
					}, Saludo, 0, 7);
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
					Jardinero = 1,
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();
			//la primera vez, versión larga. Luego, versión con opciones
			//faltan:
			//si se ha encontrado pista (Jardín descuidado), se activa la opción jardinero. Cuando utilizas esta opción, cambia a la versión corta
			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
				int i = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];

				if (i >= 1)
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = true;
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
				}
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						//contador para saber con cuántos miembros de la familia has hablado. 
						//sirve para desbloquear la caseta del jardín y el bosque
						int i = ++sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[0];
						if (i >= 4)
						{
							string posvale = "(Si quiero encontrar algo que me sea de utilidad, no debería limitarme a buscar en la casa. Podría ver el bosque donde han enterrado a Sabrina)";
							d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
								{
									sm->thinkOutLoud({ posvale });
									sm->addAvailableScene(sm->getScene(Resources::SceneID::Bosque));
									sm->getDoor(Resources::DoorID::pEntradaBosque)->setLocked(false);
									sm->getDoor(Resources::DoorID::pEntradaCaseta)->setLocked(false);
									c->clearDialogFinishedCB();

								});
						}

						//todas las pistas
						sm->addPlayerClue(Resources::ClueID::Prin_AfurPolo);
						sm->addPlayerClue(Resources::ClueID::Prin_ZapatosBarro);

						d->clearCB();
					}, Saludo, 0, 8);
			}

		}
	},
	{
		Resources::F_AntiguoTrabajador, [](DialogComponent* d)
		{

			//solo tiene un diálogo con opciones
			d->availableDialogs = {d->dialogs_[0] };

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Como = 0,
				PuntoMuerto = 1
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();
			
			if (option[0][PuntoMuerto])
			{
				StoryManager* sm = StoryManager::instance();

				sm->setInvestigableActive(Resources::ClueID::Prin_PanueloRojo, true);
				sm->setInvestigableActive(Resources::ClueID::Prin_PistolaSilenciador, true);
			}
			//ESPERA ES QUE PENSABA QUE ERAN DOS DIALOGOS
		}
	}

};