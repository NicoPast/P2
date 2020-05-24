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
			//Si ya has terminado el caso y has hablado con Maca, di�logo corto
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
		
			//Si has creado el evento bien activa este di�logo directamente
			else if (d->dialogs_[EventoBienHecho]->active_)
			{
				d->availableDialogs = { d->dialogs_[EventoBienHecho] };
				d->setCallback([sm](DialogComponent*) {sm->addPlayerClue(Resources::Tut_Cent_MotivoEntrada); },EventoBienHecho,0,4);
			}

			//Si has creado el evento mal activa este di�logo directamente
			else if (d->dialogs_[EventoMalHecho]->active_)
			{
				d->availableDialogs = { d->dialogs_[EventoMalHecho] };
				d->setCallback([sm](DialogComponent*) {sm->addPlayerClue(Resources::Tut_Cent_MotivoEntrada); }, EventoMalHecho, 0, 4);
			}


			//Si no has hablado con ella todav�a se ve primero la principal. Si vuelve a entrar aqu� y ya has hablado con ella se ve "no evento"
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
	//bitset del capo:
		/*
		0: para saber si has saludado a todos en la casa; desbloquea el bosque y la caseta del jard�n
		1: eventos de la historia; 1 cuando encuentras el jard�n descuidado; 2 cuando muere Afur; 3 cuando encuentras el m�vil de la capa; 
		2, 3, 4: para saber si has hablado con todos sobre Afur; desbloquea la aplicaci�n del marcapasos? o Afur fantasma? Por lo menos hay thinkOutLoud
			2 -> Capo
			3 -> Capa
			4 -> Carlos
		*/

	{
		Resources::Capo, [](DialogComponent* d){

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


			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
				if (d->getData()[1] >= 1)
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = !option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = option[Opciones][Jardinero];

					if (d->getData()[1] >= 2)
					{
						bool read = option[Opciones][Afur];
						d->dialogs_[Opciones]->options_[Afur].active_ = !read;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = read; 
						
						if (read && d->getData()[2] == 0);
						{
							d->getData()[2] = 1;
							if (d->getData()[2] == 1 && d->getData()[3] == 1 && d->getData()[4] == 1)
							{
								string posvale = "(Creo que la mejor manera de descubrir qu� ha pasado es hablar con el chico. Parece un buen momento para utilizar la aplicaci�n del Profesor Le�n.)";
								d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
									{
										sm->thinkOutLoud({ posvale });
										sm->getActor(Resources::F_Afur)->getEntity()->setActive(true);
										c->clearDialogFinishedCB();
									});
								for (int i = 2; i < 5; i++)
								{
									d->getData()[i] = 2;
								}
							}

						}

					}
					else
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = false;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Afur].active_ = false;
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;
				}

				d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = d->getData()[1] >= 3;


			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };

				if (d->getData()[0] == 0)
				{
					d->setCallback([sm, d](DialogComponent* dc)
						{

							d->getData()[0]++;

							if (d->getData()[0] >= 4)
							{
								string posvale = "(Si quiero encontrar algo que me sea de utilidad, no deber�a limitarme a buscar en la casa. Podr�a ver el bosque donde han enterrado a Sabrina.)";
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
						bool read = option[Opciones][Afur];
						d->dialogs_[Opciones]->options_[Afur].active_ = !read;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = read;

						int j = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[3];
						if (read && j == 0);
						{
							j = 1;
							if (d->getData()[2] == 1 && d->getData()[4] == 1)
							{
								string posvale = "(Creo que la mejor manera de descubrir qu� ha pasado es hablar con el chico. Parece un buen momento para utilizar la aplicaci�n del Profesor Le�n.)";
								d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
									{
										sm->thinkOutLoud({ posvale });
										sm->getActor(Resources::F_Afur)->getEntity()->setActive(true);
										c->clearDialogFinishedCB();
									});
								for (int i = 2; i < 5; i++)
								{
									sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[i] = 2;
								}
							}

						}
						sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 3;
					}
					else
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = false;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Afur].active_ = false;
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;
				}

				d->dialogs_[Opciones]->options_[Afur].active_ = i >= 2;
				d->dialogs_[Opciones]->options_[AfurCorto].active_ = i >= 3;

			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						//contador para saber con cu�ntos miembros de la familia has hablado. 
						//sirve para desbloquear la caseta del jard�n y el bosque
						int i = ++sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[0];
						if (i>=4)
						{
							string posvale = "(Si quiero encontrar algo que me sea de utilidad, no deber�a limitarme a buscar en la casa. Podr�a ver el bosque donde han enterrado a Sabrina)";
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
			//la tiene dos di�logos. Uno para el principio (el del contrato) y uno corto, con todas las opciones de di�logo
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
			//la primera vez, versi�n larga. Luego, versi�n con opciones
			//faltan:
			//si se ha encontrado pista (Jard�n descuidado), se activa la opci�n jardinero. Cuando utilizas esta opci�n, cambia a la versi�n corta
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
						bool read = option[Opciones][Afur];
						d->dialogs_[Opciones]->options_[Afur].active_ = !read;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = read;

						int j = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[4];
						if (read && j == 0);
						{
							j = 1;
							if (d->getData()[2] == 1 && d->getData()[3] == 1)
							{
								string posvale = "(Creo que la mejor manera de descubrir qu� ha pasado es hablar con el chico. Parece un buen momento para utilizar la aplicaci�n del Profesor Le�n.)";
								d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
									{
										sm->thinkOutLoud({ posvale });
										sm->getActor(Resources::F_Afur)->getEntity()->setActive(true);
										c->clearDialogFinishedCB();
									});
								for (int i = 2; i < 5; i++)
								{
									sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[i] = 2;
								}
							}

						}
					}
					else
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = false;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Afur].active_ = false;
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;
				}
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						//contador para saber con cu�ntos miembros de la familia has hablado. 
						//sirve para desbloquear la caseta del jard�n y el bosque
						int i = ++sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[0];
						if (i >= 4)
						{
							string posvale = "(Si quiero encontrar algo que me sea de utilidad, no deber�a limitarme a buscar en la casa. Podr�a ver el bosque donde han enterrado a Sabrina)";
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
			//la tiene dos di�logos. Uno para el principio (el del contrato) y uno corto, con todas las opciones de di�logo
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

			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };
				int i = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];
				
				d->dialogs_[Opciones]->options_[Jardinero].active_ = i >= 1;

			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						//contador para saber con cu�ntos miembros de la familia has hablado. 
						//sirve para desbloquear la caseta del jard�n y el bosque
						int i = ++sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[0];
						if (i >= 4)
						{
							string posvale = "(Si quiero encontrar algo que me sea de utilidad, no deber�a limitarme a buscar en la casa. Podr�a ver el bosque donde han enterrado a Sabrina)";
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

			//solo tiene un di�logo con opciones
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