#include "DialogSelectors.h"
#include "DialogComponent.h"
#include "Chinchetario.h"
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
				d->setCallback([sm](DialogComponent*) {sm->addAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo)); sm->removeTutorialClues(); }, EventoComida, 0, 22);
				
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
	//bitset del capo:
		/*
		0: para saber si has saludado a todos en la casa; desbloquea el bosque y la caseta del jardín
		1: eventos de la historia; 
			1 cuando encuentras el jardín descuidado; 
			2 cuando muere Afur; 
			3 cuando encuentras el móvil de la capa;
			4 cuando encuentras las pistas escondidas en el despacho; 
			5 cuando desbloqueas la habitación de Sabrina;
			6 cuando descubres la orden de asesinato y la foto
		2, 3, 4: para saber si has hablado con todos sobre Afur; desbloquea la aplicación del marcapasos? o Afur fantasma? Por lo menos hay thinkOutLoud
			2 -> Capo
			3 -> Capa
			4 -> Carlos
		*/

	{
		Resources::Capo, [](DialogComponent* d) {

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
					ConversacionUrsulaCorto = 6,
					Fotografia = 7,
					FotografiaCorto = 8,

			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();


			int& data1 = d->getData()[1];
			bool read;

			if (status[Saludo])
			{
				if (data1 >= 6)
				{
					read = option[Opciones][Fotografia];
					d->dialogs_[Opciones]->options_[Fotografia].active_ = !read;
					d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = read;
				}
				else if (data1 >= 3)
				{
					read = option[Opciones][ConversacionUrsula];
					d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = !read;
					d->dialogs_[Opciones]->options_[ConversacionUrsulaCorto].active_ = read;
					if (read)
					{
						Entity* yaya = sm->getActor(Resources::ActorID::F_MamaCapo)->getEntity();
						yaya->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
						yaya->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
					}
				}
				else if (data1 >= 2)
				{
					read = option[Opciones][Afur];
					d->dialogs_[Opciones]->options_[Afur].active_ = !read;
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = read;

					if (read && d->getData()[2] == 0);
					{
						d->getData()[2] = 1;
						if (d->getData()[2] == 1 && d->getData()[3] == 1 && d->getData()[4] == 1)
						{
							string posvale = "(Creo que la mejor manera de descubrir qué ha pasado es hablar con el chico. Parece un buen momento para utilizar la aplicación del Profesor León.)";
							d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
								{
									sm->thinkOutLoud({ posvale });
									cout << "AQui pasan cosas \n";
									Entity* carlitos = sm->getActor(Resources::F_Afur)->getEntity();
									carlitos->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
									carlitos->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
									c->clearDialogFinishedCB();
								});
							for (int i = 2; i < 5; i++)
							{
								d->getData()[i] = 2;
							}
						}

					}
				}
				else if (data1 >= 1)
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = !option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = option[Opciones][Jardinero];
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Afur].active_ = false;
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;

					d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = false;
					d->dialogs_[Opciones]->options_[ConversacionUrsulaCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Fotografia].active_ = false;
					d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = false;
				}
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
								string posvale = "(Si quiero encontrar algo que me sea de utilidad, no debería limitarme a buscar en la casa. Podría ver el bosque donde han enterrado a Sabrina.)";
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

			/*

			if (status[Saludo])
			{

				d->availableDialogs = { d->dialogs_[Opciones] };
				if (data1 >= 1)
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = !option[Opciones][Jardinero];
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = option[Opciones][Jardinero];

					if (data1 >= 2)
					{
						bool read = option[Opciones][Afur];
						d->dialogs_[Opciones]->options_[Afur].active_ = !read;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = read;

						if (read && d->getData()[2] == 0);
						{
							d->getData()[2] = 1;
							if (d->getData()[2] == 1 && d->getData()[3] == 1 && d->getData()[4] == 1)
							{
								string posvale = "(Creo que la mejor manera de descubrir qué ha pasado es hablar con el chico. Parece un buen momento para utilizar la aplicación del Profesor León.)";
								d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
									{
										sm->thinkOutLoud({ posvale });
										cout << "AQui pasan cosas \n";
										Entity* carlitos = sm->getActor(Resources::F_Afur)->getEntity();
										carlitos->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
										carlitos->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
										c->clearDialogFinishedCB();
									});
								for (int i = 2; i < 5; i++)
								{
									d->getData()[i] = 2;
								}
							}

						}

						if (data1 >= 3)
						{
							read = option[Opciones][ConversacionUrsula];
							d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = !read;
							d->dialogs_[Opciones]->options_[ConversacionUrsulaCorto].active_ = read;
							if (read)
							{
								Entity* yaya = sm->getActor(Resources::ActorID::F_MamaCapo)->getEntity();
								yaya->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
								yaya->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
							}

							if (data1 >= 6)
							{
								read = option[Opciones][Fotografia];
								d->dialogs_[Opciones]->options_[Fotografia].active_ = !read;
								d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = read;
							}
							else
							{
								d->dialogs_[Opciones]->options_[Fotografia].active_ = false;
								d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = false;
							}
						}
						else
						{
							d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = false;
							d->dialogs_[Opciones]->options_[ConversacionUrsulaCorto].active_ = false;

							d->dialogs_[Opciones]->options_[Fotografia].active_ = false;
							d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = false;
						}

					}
					else
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = false;
						d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;

						d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = false;
						d->dialogs_[Opciones]->options_[ConversacionUrsulaCorto].active_ = false;

						d->dialogs_[Opciones]->options_[Fotografia].active_ = false;
						d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = false;
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Afur].active_ = false;
					d->dialogs_[Opciones]->options_[AfurCorto].active_ = false;

					d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = false;
					d->dialogs_[Opciones]->options_[ConversacionUrsulaCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Fotografia].active_ = false;
					d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = false;
				}

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
								string posvale = "(Si quiero encontrar algo que me sea de utilidad, no debería limitarme a buscar en la casa. Podría ver el bosque donde han enterrado a Sabrina.)";
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
		/**/
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
					DiscusionMovil = 4,
					DiscusionMovilCorto = 5,
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
						d->dialogs_[Opciones]->options_[Afur].active_ = true;

						int* capo = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData();
						int& j = capo[3];
						if (read && j == 0);
						{
							j = 1;
							if (capo[2] == 1 && capo[4] == 1)
							{
								string posvale = "(Creo que la mejor manera de descubrir qué ha pasado es hablar con el chico. Parece un buen momento para utilizar la aplicación del Profesor León.)";
								d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
									{
										sm->thinkOutLoud({ posvale });

										Entity* carlitos = sm->getActor(Resources::F_Afur)->getEntity();
										carlitos->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
										carlitos->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
										c->clearDialogFinishedCB();
									});
								for (int i = 2; i < 5; i++)
								{
									sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[i] = 2;
								}
							}

						}

						if (i >= 3)
						{
							d->dialogs_[Opciones]->options_[DiscusionMovil].active_ = !option[Opciones][DiscusionMovil];
							d->dialogs_[Opciones]->options_[DiscusionMovilCorto].active_ = option[Opciones][DiscusionMovil];
						}
						else
						{
							d->dialogs_[Opciones]->options_[DiscusionMovil].active_ = false;
							d->dialogs_[Opciones]->options_[DiscusionMovilCorto].active_ = false;
						}

					}
					else
					{
						d->dialogs_[Opciones]->options_[Afur].active_ = false;

						d->dialogs_[Opciones]->options_[DiscusionMovil].active_ = false;
						d->dialogs_[Opciones]->options_[DiscusionMovilCorto].active_ = false;
					}
				}
				else
				{
					d->dialogs_[Opciones]->options_[Jardinero].active_ = false;
					d->dialogs_[Opciones]->options_[JardinCorto].active_ = false;

					d->dialogs_[Opciones]->options_[Afur].active_ = false;

					d->dialogs_[Opciones]->options_[DiscusionMovil].active_ = false;
					d->dialogs_[Opciones]->options_[DiscusionMovilCorto].active_ = false;
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

						int* capo = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData();
						int& j = capo[4];
						if (read && j == 0);
						{
							j = 1;
							if (capo[2] == 1 && capo[3] == 1)
							{
								string posvale = "(Creo que la mejor manera de descubrir qué ha pasado es hablar con el chico. Parece un buen momento para utilizar la aplicación del Profesor León.)";
								d->setDialogFinishedCallback([sm, posvale](DialogComponent* c)
									{
										sm->thinkOutLoud({ posvale });
										Entity* carlitos = sm->getActor(Resources::F_Afur)->getEntity();
										carlitos->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
										carlitos->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
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
			d->availableDialogs = {d->dialogs_[0] };

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
					Como = 0,
					PuntoMuerto = 1,
					Gus = 2,
					GusCorto = 3,
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();
			
			if (option[0][PuntoMuerto])
			{
				sm->setInvestigableActive(Resources::ClueID::Prin_PanueloRojo, true);
				sm->setInvestigableActive(Resources::ClueID::Prin_PistolaSilenciador, true);
			}
			int& i = sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];
			
			if (i >= 6)
			{
				d->dialogs_[Saludo]->options_[Gus].active_ = !option[Saludo][Gus];
				d->dialogs_[Saludo]->options_[GusCorto].active_ = option[Saludo][Gus];
			}
			else
			{
				d->dialogs_[Saludo]->options_[Gus].active_ = false;
				d->dialogs_[Saludo]->options_[GusCorto].active_ = false;
			}
		}
	},
	{
		Resources::F_Afur, [](DialogComponent* d)
		{

			d->availableDialogs = { d->dialogs_[0] };

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Suicidio = 0,
				Discusion = 1
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();

			if (option[0][Discusion])
			{
				sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1] = 3;
			}

		}
	},
	{
		Resources::F_MamaCapo, [](DialogComponent* d)
		{

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
				Opciones = 1,
					Cuidador = 1,
					CuidadorCorto = 2,
					Gus = 3,
					GusCorto = 4
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();

			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };

				int& i = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];
				if (i >= 4)
				{
					d->dialogs_[Cuidador]->options_[Cuidador].active_ = !option[Opciones][Cuidador];
					d->dialogs_[Cuidador]->options_[CuidadorCorto].active_ = option[Opciones][Cuidador];
				}
				if (option[Opciones][Cuidador])
				{
					i = 5;
				}
				if (i >= 6)
				{
					d->dialogs_[Opciones]->options_[Gus].active_ = !option[Opciones][Gus];
					d->dialogs_[Opciones]->options_[GusCorto].active_ = option[Opciones][Gus];
				}
				else
				{
					d->dialogs_[Opciones]->options_[Gus].active_ = false;
					d->dialogs_[Opciones]->options_[GusCorto].active_ = false;
				}
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						sm->setInvestigableActive(Resources::ClueID::Prin_PapelesHerencia, true);
						sm->setInvestigableActive(Resources::ClueID::Prin_Llave, true);
						sm->setInvestigableActive(Resources::ClueID::Prin_ContratoGus, true);
						d->clearCB();
					}, Saludo, 0, 7);
			}

		}
	},
	{
		Resources::F_Hija, [](DialogComponent* d)
		{

			StoryManager* sm = StoryManager::instance();
			enum dialogNames
			{
				Saludo = 0,
					Cuidador = 1,
					Muerte = 2,
					Afur = 3,
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();

			d->availableDialogs = { d->dialogs_[Saludo] };

			if (option[Saludo][Afur])
			{
				sm->setInvestigableActive(Resources::ClueID::Prin_Foto, true);
				sm->setInvestigableActive(Resources::ClueID::Prin_OrdenAsesinato, true);

			}

		}
	}


};