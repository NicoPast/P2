#include "DialogSelectors.h"
#include "DialogComponent.h"
#include "Chinchetario.h"
#include "LoremIpsum.h"
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
		
		if (sm->getGameCase() > 0)//ahora hay que poner que el caso con el que empiezas el juego es el -1, y aparcao
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
				d->setCallback([sm](DialogComponent*d) {
					sm->addAvailableScene(sm->getScene(Resources::SceneID::DespachoPolo)); 
					sm->removeTutorialClues();
					d->clearCB();
				}, EventoComida, 0, 22);
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
				sm->getActors()[Resources::MacarenaMartinez]->setInPhone(true);

			}
		
		}
	}
	},
	//bitset del capo:
		/*
		0: para saber si has saludado a todos en la casa; desbloquea el bosque y la caseta del jard�n
		1: eventos de la historia; 
			1 cuando encuentras el jard�n descuidado; 
			2 cuando muere Afur; 
			3 cuando encuentras el m�vil de la capa;
			4 cuando encuentras las pistas escondidas en el despacho; 
			5 cuando desbloqueas la habitaci�n de Sabrina;
			6 cuando descubres la orden de asesinato y la foto
			7 cuando desbloqueas la timeline en el despacho
		2, 3, 4: para saber si has hablado con todos sobre Afur; desbloquea la aplicaci�n del marcapasos? o Afur fantasma? Por lo menos hay thinkOutLoud
			2 -> Capo
			3 -> Capa
			4 -> Carlos

		5: cuando se tiene la timeline hecha 
		*/

		/* 
			Como el layerRemover es uno solo (gracias Ricky), 
			y hay que compartirlo para todos los objetos que tienen falsos fondos (gracias Ricky)
			guardamos booleanos para que no se active varias veces el mismo, con los bitset (gracias Ricky)

			Jardinera[0] = 1 -> el del cuadro 
			Abuela[0] = 1 -> el de la mesa del despacho
			Sabrina[0] = 1 -> el de Sabrina
			Capo[7] = 1 -> el de la puerta al s�tano
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
				FinalMalo = 2,
				FinalBueno = 3
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();

			int& data1 = d->getData()[1];
			int dataFinal = d->getData()[5];
			
			//esto cuando desaparezca la alfombra
			//if (data1 >= 7);
			//{/*
			//	sm->removeLayer(Vector2D(800, 480), Resources::SceneID::DespachoPolo);
			//	std::function<void(Entity*, Entity*)> func = sm->getLayerRemover()->getComponent<Interactable>(ecs::Interactable)->getCallback();
			//	sm->getLayerRemover()->getComponent<Interactable>(ecs::Interactable)->setCallback([func, sm](Entity* e, Entity* e2)
			//		{
			//			func(e, e2);
			//		});*/
			//			//sm->getDoor(Resources::pDespachoSotano)->getEntity()->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
			//};
			if (dataFinal == -1)
			{
				d->availableDialogs = { d->dialogs_[FinalMalo] };
			}

			else if (dataFinal == 1)
			{
				d->availableDialogs = { d->dialogs_[FinalBueno] };
			}

			else if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };

				d->dialogs_[Opciones]->options_[Jardinero].active_ = data1 >= 1 && !option[Opciones][Jardinero];
				d->dialogs_[Opciones]->options_[JardinCorto].active_ = data1 >= 1 && option[Opciones][Jardinero];

				d->dialogs_[Opciones]->options_[Afur].active_ = data1 >= 2 && !option[Opciones][Afur];
				d->dialogs_[Opciones]->options_[AfurCorto].active_ = data1 >= 2 && option[Opciones][Afur];

				d->dialogs_[Opciones]->options_[ConversacionUrsula].active_ = data1 >= 3 && !option[Opciones][ConversacionUrsula] && sm->getActor(Resources::Capa)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getDialog(1)->options_[3].read_;
				d->dialogs_[Opciones]->options_[ConversacionUrsulaCorto].active_ = data1 >= 3 && option[Opciones][ConversacionUrsula] && sm->getActor(Resources::Capa)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getDialog(1)->options_[3].read_;;

				d->dialogs_[Opciones]->options_[Fotografia].active_ = data1 >= 6 && !option[Opciones][Fotografia];
				d->dialogs_[Opciones]->options_[FotografiaCorto].active_ = data1 >= 6 && option[Opciones][Fotografia];

				if (data1 >= 2 && option[Opciones][Afur] && d->getData()[2] == 0)
				{
					d->getData()[2] = 1;
					MuerteAfur(d);
				}

				if (data1 >= 3 && option[Opciones][ConversacionUrsula])
				{
					Entity* yaya = sm->getActor(Resources::ActorID::F_MamaCapo)->getEntity();
					yaya->getComponent<Animator<int*>>(ecs::Animator)->setEnabled(true);
					yaya->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
				}
				
				if (d->getData()[5]!=0 && d->getData()[7] != 1)
				{
					//sm->removeLayer(Vector2D(800, 480), Resources::SceneID::Pasillo);
					//std::function<void(Entity*, Entity*)> func = sm->getLayerRemover()->getComponent<Interactable>(ecs::Interactable)->getCallback();
					//sm->getLayerRemover()->getComponent<Interactable>(ecs::Interactable)->setCallback([func, sm](Entity* e, Entity* e2)
					//	{
					//		func(e, e2);
					//		sm->getDoor(Resources::pDespachoSotano)->getEntity()->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
					//	});
				};
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				sm->getActors()[Resources::Capo]->setInPhone(true);


				if (d->getData()[0] == 0)
				{
					d->setCallback([sm, d](DialogComponent* dc)
						{
							d->getData()[0]++;
							BosqueCaseta(d);

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
					DiscusionMovil = 4,
					DiscusionMovilCorto = 5,
			};
			auto status = d->getDialogStatus();
			auto option = d->getOptionsStatus();

			int* capo = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData();
			int data1 = capo[1];

			int dataFinal = capo[5];

			if (dataFinal != 0)
			{
				d->availableDialogs = {};
			}
			else if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };

				d->dialogs_[Opciones]->options_[Jardinero].active_ = data1 >= 1 && !option[Opciones][Jardinero];
				d->dialogs_[Opciones]->options_[JardinCorto].active_ = data1 >= 1 && option[Opciones][Jardinero];

				d->dialogs_[Opciones]->options_[Afur].active_ = data1 >= 2;

				d->dialogs_[Opciones]->options_[DiscusionMovil].active_ = data1 >= 3 && !option[Opciones][DiscusionMovil];
				d->dialogs_[Opciones]->options_[DiscusionMovilCorto].active_ = data1 >= 3 && option[Opciones][DiscusionMovil];

				int& j = capo[3];
				if (data1 >= 2 && option[Opciones][Afur] && j == 0)
				{
					j = 1;
					MuerteAfur(d);
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
						BosqueCaseta(d);

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
			
			int* capo = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData();
			int data1 = capo[1];
			int dataFinal = capo[5];

			if (dataFinal != 0)
			{
				d->availableDialogs = {};
			}

			else if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };

				d->dialogs_[Opciones]->options_[Jardinero].active_ = data1 >= 1 && !option[Opciones][Jardinero];
				d->dialogs_[Opciones]->options_[JardinCorto].active_ = data1 >= 1 && option[Opciones][Jardinero];

				d->dialogs_[Opciones]->options_[Afur].active_ = data1 >= 2 && !option[Opciones][Afur];
				d->dialogs_[Opciones]->options_[AfurCorto].active_ = data1 >= 2 && option[Opciones][Afur];

				if (data1 >= 1)
				{
					if (data1 >= 2 && option[Opciones][Afur] && capo[4] == 0)
					{
						capo[4] = 1;
						MuerteAfur(d);
					}
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
						BosqueCaseta(d);

						//todas las pistas
						sm->addPlayerClue(Resources::ClueID::Prin_CarlosCastro);
						auto clues = sm->getClues();
						clues[Resources::Prin_NavajaCarlos]->description_  = 
							"Navaja mariposa muy bonita, pertenece a Carlos. De todos los objetos puntiagudos de los que habla, este parece ser el m\u00e1s preciado de todos. Y sin duda el m\u00e1s peligroso.";
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

			int data1 = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];

			if (status[Saludo])
			{
				d->availableDialogs = { d->dialogs_[Opciones] };

				d->dialogs_[Opciones]->options_[Jardinero].active_ = data1 >= 1;

			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				d->setCallback([sm, d](DialogComponent* dc)
					{
						//contador para saber con cu�ntos miembros de la familia has hablado. 
						//sirve para desbloquear la caseta del jard�n y el bosque
						int i = ++sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[0];
						BosqueCaseta(d);

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
			
			int data1 = sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];
			
			sm->addPlayerClue(Resources::Prin_Cent_MuerteJardinera);
			if (option[0][PuntoMuerto] && d->getData()[0] != 1);
			{
				Entity* hider = sm->getScene(Resources::SceneID::Pasillo)->hider;
				hider->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
				std::function<void(Entity*, Entity*)> func = hider->getComponent<Interactable>(ecs::Interactable)->getCallback();
				hider->getComponent<Transform>(ecs::Transform)->setPos(530, 320);
				hider->getComponent<Interactable>(ecs::Interactable)->setCallback([func, sm](Entity* e, Entity* e2)
					{
						func(e, e2);
						sm->setInvestigableActive(Resources::ClueID::Prin_PanueloRojo, true);
						sm->setInvestigableActive(Resources::ClueID::Prin_PistolaSilenciador, true);
					});
				d->getData()[0] = 1;
			};

			d->dialogs_[Saludo]->options_[Gus].active_ = data1 >= 6 && !option[Saludo][Gus];
			d->dialogs_[Saludo]->options_[GusCorto].active_ = data1 >= 6 && option[Saludo][Gus];
			if (data1 >= 6)
			{
				sm->addPlayerClue(Resources::ClueID::Prin_LlaveErnesto);
				sm->createTimeLine();

				Entity* hider = sm->getScene(Resources::SceneID::DespachoPolo)->hider;
				hider->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
				std::function<void(Entity*, Entity*)> func = hider->getComponent<Interactable>(ecs::Interactable)->getCallback();
				hider->getComponent<Transform>(ecs::Transform)->setPos(530, 320);
				hider->getComponent<Interactable>(ecs::Interactable)->setCallback([func, sm](Entity* e, Entity* e2)
					{
						func(e, e2);
						sm->getDoor(Resources::pDespachoSotano)->getEntity()->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
						sm->getBackgroundSprite()->setTexture(Resources::TextureID::DespachoCapoNoCarpet);

					});
				d->getData()[7] = 1;
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
				sm->addPlayerClue(Resources::Prin_Cent_Discusion);
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

				int& data1 = sm->getActor(Resources::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData()[1];

				d->dialogs_[Cuidador]->options_[Cuidador].active_ = data1 >= 4 && !option[Opciones][Cuidador];
				d->dialogs_[Cuidador]->options_[CuidadorCorto].active_ = data1 >= 4 && option[Opciones][Cuidador];

				d->dialogs_[Opciones]->options_[Gus].active_ = data1 >= 6 && !option[Opciones][Gus];
				d->dialogs_[Opciones]->options_[GusCorto].active_ = data1 >= 6 && option[Opciones][Gus];

				if (option[Opciones][Cuidador] && data1 <= 5)
				{
					data1 = 5;
				}
			}
			else
			{
				d->availableDialogs = { d->dialogs_[Saludo] };
				if (d->getData()[0] != 1)
				{
					Entity* hider = sm->getScene(Resources::SceneID::DespachoPolo)->hider;
					hider->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
					std::function<void(Entity*, Entity*)> func = hider->getComponent<Interactable>(ecs::Interactable)->getCallback();
					hider->getComponent<Transform>(ecs::Transform)->setPos(530, 320);
					hider->getComponent<Interactable>(ecs::Interactable)->setCallback([func, sm](Entity* e, Entity* e2)
						{
							func(e, e2);
							StoryManager::instance()->setInvestigableActive(Resources::ClueID::Prin_ContratoGus, true);
							StoryManager::instance()->setInvestigableActive(Resources::ClueID::Prin_Llave, true);
							StoryManager::instance()->setInvestigableActive(Resources::ClueID::Prin_PapelesHerencia, true);
						});

					d->getData()[0] = 1;
				};
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

			if ((option[Saludo][Afur]) && d->getData()[0] != 1)
			{
				//sm->removeLayer(Vector2D(530, 320), Resources::SceneID::Pasillo);
				//std::function<void(Entity*, Entity*)> func = sm->getLayerRemover()->getComponent<Interactable>(ecs::Interactable)->getCallback();
				//sm->getLayerRemover()->getComponent<Interactable>(ecs::Interactable)->setCallback([func, sm](Entity* e, Entity* e2)
				//	{
				//		func(e, e2);

				//	});
					Entity* hider = sm->getScene(Resources::SceneID::HabitacionSabrina)->hider;
					hider->getComponent<Interactable>(ecs::Interactable)->setEnabled(true);
					std::function<void(Entity*, Entity*)> func = hider->getComponent<Interactable>(ecs::Interactable)->getCallback();
					
					hider->getComponent<Interactable>(ecs::Interactable)->setCallback([func,sm](Entity* e, Entity* e2)
						{
							func(e, e2);
							sm->setInvestigableActive(Resources::ClueID::Prin_Foto, true);
							sm->setInvestigableActive(Resources::ClueID::Prin_OrdenAsesinato, true);
						});

				d->getData()[0] = 1;
			};
		}
	},
	{
			Resources::F_Novio, [](DialogComponent* d)
		{

			StoryManager* sm = StoryManager::instance();
			auto status = d->getDialogStatus();
			d->availableDialogs = { d->dialogs_[0] };
			SDLGame::instance()->getAudioMngr()->playMusic(Resources::GhostLove);
			d->ignoreQ = true;
			//hacer fadeOut
			//sacar los créditos
			d->setDialogFinishedCallback([](DialogComponent* dc)
				{
					LoremIpsum::instance()->getStateMachine()->PlayCredits();
				});
		}
	}
			

};

void DialogSelectors::BosqueCaseta(DialogComponent* d)
{
	StoryManager* sm = StoryManager::instance();
	int* data = sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData();

	if (data[0] >= 4)
	{
		string thoughts = "(Si quiero encontrar algo que me sea de utilidad, no debería limitarme a buscar en la casa. Podría ver el bosque donde han enterrado a Sabrina.)";
		d->setDialogFinishedCallback([sm, thoughts](DialogComponent* c)
			{
				sm->thinkOutLoud({ thoughts });
				sm->getDoor(Resources::DoorID::pEntradaBosque)->setLocked(false);
				sm->getDoor(Resources::DoorID::pEntradaCaseta)->setLocked(false);
				c->clearDialogFinishedCB();
			});
	}
}

void DialogSelectors::MuerteAfur(DialogComponent* d)
{
	StoryManager* sm = StoryManager::instance();
	int* data = sm->getActor(Resources::ActorID::Capo)->getEntity()->getComponent<DialogComponent>(ecs::DialogComponent)->getData();

	if (data[2] == 1 && data[3] == 1 && data[4] == 1)
	{
		string thoughts = "(Creo que la mejor manera de descubrir qué ha pasado es hablar con el chico.)";
		d->setDialogFinishedCallback([sm, thoughts](DialogComponent* c)
			{
				sm->thinkOutLoud({ thoughts });

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
