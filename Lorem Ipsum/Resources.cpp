#include "Resources.h"
#include "SDL_macros.h"
static map<char, string>tildes_{
	
	{
		'a', "\u00e1"
	},
	{
		'A', "\u00c1"
	},
	{
		'e', "\u00e9"
	},
	{
		'E', "\u00c9"
	},
	{
		'i', "\u00ed"
	},
	{
		'I', "\u00cd"
	},
	{
		'o', "\u00f3"
	},
	{
		'O', "\u00d3"
	},
	{
		'u', "\u00fa"
	},
	{
		'U', "\u00da"
	},
	{
		'Ñ', "\u00D1"
	},
	{
		'ñ', "\u00F1"
	},
	{ '¿', "\u00BF"},
	{ '¡', "\u00A1"}
};

vector<Resources::FontInfo> Resources::fonts_{
	//
			{ RobotoTest24, "../assets/fonts/RobotoMono-Bold.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_{
	//
			{ Blank, "../assets/images/blank.png" }, //
			{ Background, "../assets/images/backgrounds//background.png"},//
			{ FadeSpriteSheet, "../assets/images/FadeAnimations.png" }, //
			{ MainMenuBG, "../assets/images/backgrounds/MenuBG.png" }, //
			{ MainMenuBG1, "../assets/images/backgrounds/MenuBG1.png" }, //
			{ MainMenuBG2, "../assets/images/backgrounds/MenuBG2.png" }, //
			{ MainMenuBG3, "../assets/images/backgrounds/MenuBG3.png" }, //
			{ MainMenuBut, "../assets/images/UI/MainMenuBut.png" }, //
			{ Pixel, "../assets/images/whiterect.png" }, //
			{ CorkBG, "../assets/images/backgrounds/corkBG.jpg"},
			{ MapsBG, "../assets/images/backgrounds/mapBg.png" }, //
			{ AddIcon, "../assets/images/UI/addIcon.png" }, //
			{ EditIcon, "../assets/images/UI/editIcon.png" },//
		    { Manometer, "../assets/images/UI/manometer.png" }, //
		    { ManometerNeedle, "../assets/images/UI/needle.png" }, //
		    { TunerBG, "../assets/images/backgrounds/tunerBG.png" }, //
		    { Bars, "../assets/images/UI/radioBars.png" }, //
		    { Lock, "../assets/images/UI/lockBars.png" }, //
		    { ResetStress, "../assets/images/UI/resetStress.png" }, //
			{ IdleSDL, "../assets/images/Lazaro/Idle.png"},
			{ WalkingSDL, "../assets/images/Lazaro/WalkingSDL.png"},
			{ ChatInteraction, "../assets/images/UI/conversationIcon.png"},
			{ ClueInteraction, "../assets/images/UI/clueIcon.png"},
			{ DoorInteraction, "../assets/images/UI/doorIcon.png"},
			{ GhostInteraction, "../assets/images/UI/doorIcon.png"},
			{TrashIcon, "../assets/images/UI//trashIcon.png"},
			{AppPressed, "../assets/images/Phone/App Pressed.png"},
			{DeathAppIcon, "../assets/images/Phone/Death App Icon.png"},
			{MapAppIcon, "../assets/images/Phone/MapAppIcon.png"},
			{ChinchetarioAppIcon, "../assets/images/Phone/ChinchetarioAppIcon.png"},
			{OptionsAppIcon, "../assets/images/Phone/OptionsAppIcon.png"},
			{PhoneAppIcon, "../assets/images/Phone/PhoneAppIcon.png"},
			{ NotesAppIcon, "../assets/images/Phone/NotesAppIcon.png"},
			{ NotificationIcon, "../assets/images/Phone/notificationIcon.png"},
			{OptionBars,"../assets/images/UI/optionsBars.png"},
			{PhoneOn, "../assets/images/Phone/Phone On.png"},
			{PhoneOff, "../assets/images/Phone/Phone Off.png"},
			{MacarenaCatIdle, "../assets/images/macarena/MacarenaCatIdle.png"},
			{MacarenaHeadShake, "../assets/images/macarena/MacarenaHeadShake.png"},
			{MacarenaFacepalm, "../assets/images/macarena/MacarenaFacepalm.png"},
			{femur, "../assets/images/Clues/femur.png"},
			{clueEvent, "../assets/images/Clues/PolaroidEvento.png"},
			{DialogBox, "../assets/images/UI/DialogBox.png"},
			{CatIdle, "../assets/images/pelusa/IdleCat.png"},
			{CatWalk, "../assets/images/pelusa/WalkingCat.png"},
			{CatRun, "../assets/images/pelusa/RunningCat.png"},
			{VerticalUIPanel, "../assets/images/UI/VerticalUIPanel.png"},
			{VerticalUIPanel2, "../assets/images/UI/VerticalUIPanel2.png"},
			{HorizontalUIPanel, "../assets/images/UI/HorizontalUIPanel.png"},
			{HorizontalUIPanel2, "../assets/images/UI/HorizontalUIPanel2.png"},
			{MessageUIPanel, "../assets/images/UI/messageUIPanel.png"},
			{LazaroPortrait, "../assets/images/Lazaro/PortraitLazaro.png"},
			{MacarenaPortrait, "../assets/images/Macarena/PortraitMacarena.png"},
			{CatPortrait, "../assets/images/pelusa/PortraitGato.png"},
			{BGEntradaOficinaSDL, "../assets/images/backgrounds/OficinaEntradaSDL.png"},
			{BGJardin, "../assets/images/backgrounds/jardinBG1.png"},
			{clueTemplate, "../assets/images/Clues/Polaroid.png"},
			{TimelineBG, "../assets/images/backgrounds/timelineBG.png"},
			{Humo1SpriteSheet, "../assets/images/backgrounds/bgHumo1.png"},
			{Chinchetas, "../assets/images/UI/Chinchetas.png"},
			{GoBackButton, "../assets/images/UI/GoBackButton.png"},
			{HideShowButton, "../assets/images/UI/HideShowButton.png"},
			{ChineseFoodPhoto, "../assets/images/Clues/objectClues/ChineseFoodPhoto.png"},
			{ChineseFoodInteractable, "../assets/images/Clues/WorldClues/ChineseFoodInteractable.png"},
			{PapelesDesordenadosInteractable, "../assets/images/Clues/WorldClues/PapelesDesordenadosInteractable.png"},
			{SillaDespachoInteractable, "../assets/images/Clues/WorldClues/SillaDespachoInteractable.png"},
			{Escritorio, "../assets/images/Escritorio.png"},
			//{VentanaOficina3, "../assets/images/VentanaOficina3.png"},
			//{VentanaOficina2, "../assets/images/VentanaOficina2.png"},
			//{VentanaOficina1, "../assets/images/VentanaOficina1.png"},
			{VentanaOficina0, "../assets/images/VentanaOficina.png"},
			{officeFan, "../assets/images/officeFan.png"},
			{MaridoCapaSpriteSheet, "../assets/images/familiaPolo/MaridoCapaSpriteSheet.png"},
			{BackgroundDeathWorld, "../assets/images/backgrounds/backgroundGhostWorld.png"},
			{GhostSDL, "../assets/images/Lazaro/SDLGhost.png"},
			{MainMenuSpriteSheet, "../assets/images/backgrounds/MenuBGAnim.png"},
			{DespachoCapo, "../assets/images/backgrounds//DespachoCapo.png"},
			{DespachoCapoOverlay, "../assets/images/backgrounds/DespachoCapo.png"},
			{AfurPortrait, "../assets/images/familiaPolo/PortraitAfur.png"},
			{Afur, "../assets/images/familiaPolo/Afur.png"},
			{AfurFantasma, "../assets/images/familiaPolo/AfurFantasma.png" },
			{AfurFantasmaPortrait, "../assets/images/familiaPolo/AfurPortraitFantasma.png" },
			{UrsulaIdle, "../assets/images/familiaPolo/UrsulaIdle.png"},
			{UrsulaWalking, "../assets/images/familiaPolo/UrsulaWalking.png"},
			{UrsulaPortrait, "../assets/images/familiaPolo/UrsulaPortrait.png"},
			{CarlosPortrait, "../assets/images/familiaPolo/PortraitCarlos.png"},
			{BackgroundCasetaJardin, "../assets/images/backgrounds/background2.png"},
			{UnkownPortrait, "../assets/images/portraitUnknown.png"},
			{ErnestoIdle, "../assets/images/familiaPolo/ErnestoSmoking.png"},
			{ErnestoPortrait, "../assets/images/familiaPolo/CapoPortrait.png"},
			{SabrinaIdle, "../assets/images/familiaPolo/SabrinaIdle.png"},
			{SabrinaPortrait, "../assets/images/familiaPolo/SabrinaPortraitFantasma.png"},
			{YayaIdle, "../assets/images/familiaPolo/YayaFantasma.png"},
			{LocationIcon, "../assets/images/UI/MapLocationIcon.png"},
			{YayaPortrait, "../assets/images/familiaPolo/YayaPortrait.png"},
			{Resources::TextureID::OptionsUIButton, "../assets/images/UI/FullScreenIcon.png"},
			{Resources::TextureID::OptionsUISlider, "../assets/images/UI/Slider.png"},
			{Resources::TextureID::OptionsUISoundIcon, "../assets/images/UI/SoundIcons.png"},
			{Resources::TextureID::OptionsUIBG, "../assets/images/UI/BG.png"},
			{HabitacionCapoBG, "../assets/images/backgrounds/CapoRoom.png"},
			{HabitacionCapaBG, "../assets/images/backgrounds/CapaRoom.png"},
			{HabitacionAfurBG, "../assets/images/backgrounds/AfurRoom.png"},
			{HabitacionSabrinaBG, "../assets/images/backgrounds/SabrinaRoom_Open.png"},
			{HabitacionSabrinaOverlay, "../assets/images/backgrounds/SabrinaRoom.png"},
			{ SotanoBG, "../assets/images/backgrounds/Sotano.png" },
			{ HallBG, "../assets/images/backgrounds/hallBG.png" },
			{ PasilloBG, "../assets/images/backgrounds/pasillo_open.png" },
			{ PasilloOverlay, "../assets/images/backgrounds/pasilloComplete.png" },
			{ BosqueBG, "../assets/images/backgrounds/forestBG.png" },
			{ BosqueOverlay, "../assets/images/backgrounds/forest_realforeground.png"},
			{ PolaroidPapelesDesordenados, "../assets/images/Clues/objectClues/papelesDesordenados.png"},
			{ AcursarButton, "../assets/images/UI/Acusar.png" },
			{ FlechaButton, "../assets/images/UI/FlechaTimeLine.png" },
			{ JardineraPortrait, "../assets/images/familiaPolo/JardineraPortraitFantasma.png" },
			{ JardineraIdle, "../assets/images/familiaPolo/JardineraFantasma.png" },
			{ GusPortrait, "../assets/images/familiaPolo/GusPortrait.png" },
			{ GusIdle, "../assets/images/familiaPolo/GusFantasma.png" },

			//pistas caso principal
			{ Bala,			"../assets/images/Clues/worldClues/bala_casquilloWorld.png"},
			{ Contrato,		"../assets/images/Clues/worldClues/contratoGus.png"},
			{ ContratoGus,	"../assets/images/Clues/worldClues/contratoGus.png"},
			{ Foto,			"../assets/images/Clues/worldClues/fotoOverworld.png" },
			{ Pistola,		"../assets/images/Clues/worldClues/gunWorld.png" },
			{ Herencia,		"../assets/images/Clues/worldClues/herencia.png" },
			{ Herramientas,	"../assets/images/Clues/worldClues/herencia.png" },
			{ LlaveSabrina,	"../assets/images/Clues/worldClues/llaveSabrina.png" },
			{ LlaveSotano,	"../assets/images/Clues/worldClues/llaveSotano.png" },
			{ Navaja,		"../assets/images/Clues/worldClues/navaja.png" },
			{ Orden,		"../assets/images/Clues/worldClues/ordenAsesinato.png" },
			{ Panuelo,		"../assets/images/Clues/worldClues/cloth.png"},
			{ Roca,			"../assets/images/Clues/worldClues/rock.png"},

			{ SillaDespachoPolaroid,		 "../assets/images/Clues/objectClues/silla.png" },

			//polaroids caso principal
			{PolaroidBala,		 "../assets/images/Clues/objectClues/bala_casquillo.png"},
			{Polaroidcontrato,	 "../assets/images/Clues/objectClues/contrato_Confidencialidad.png"},
			{PolaroidcontratoGus,"../assets/images/Clues/objectClues/contrato_Confidencialidad_Gus.png"},
			{Polaroidfoto,		  "../assets/images/Clues/objectClues/fotografia.png"},
			{Polaroidpistola,	  "../assets/images/Clues/objectClues/gun.png"},
			{Polaroidherencia,	  "../assets/images/Clues/objectClues/herencia.png"},
			{Polaroidherramientas,"../assets/images/Clues/objectClues/herramientas.png"},
			{PolaroidllaveSabrina,"../assets/images/Clues/objectClues/llave_Sabrina.png"},
			{PolaroidllaveSotano, "../assets/images/Clues/objectClues/llave_Sotano.png"},
			{Polaroidnavaja,	  "../assets/images/Clues/objectClues/navaja.png"},
			{Polaroidorden,		  "../assets/images/Clues/objectClues/orden_Asesinato.png"},
			{Polaroidpanuelo,	  "../assets/images/Clues/objectClues/pañuelo_rojo.png"},
			{Polaroidroca,		  "../assets/images/Clues/objectClues/rock.png"},
			{PolaroidAfur,		"../assets/images/Clues/personClues/AfurPolaroid.png"},
			{PolaroidCapa,		"../assets/images/Clues/personClues/CapaPolaroid.png"},
			{PolaroidCapo,		"../assets/images/Clues/personClues/CapoPolaroid.png"},
			{PolaroidCarlos,	"../assets/images/Clues/personClues/CarlosPolaroid.png"},
			{PolaroidJardinera,	"../assets/images/Clues/personClues/JardineraPolaroid.png"},
			{PolaroidSabrina,	"../assets/images/Clues/personClues/SabrinaPolaroid.png"},
			{PolaroidYaya,		"../assets/images/Clues/personClues/YayaPolaroid.png"},
			{PolaroidGus,		"../assets/images/Clues/personClues/GusPolaroid.png" },
			{PolaroidHabAfur,		"../assets/images/Clues/placeClues/afurRoomPolaroid.png" },
			{PolaroidHabSabrina,	"../assets/images/Clues/placeClues/sabrinaRoomPolaroid.png" },
			{PolaroidHabCapa,		"../assets/images/Clues/placeClues/ursulaRoomPolaroid.png" },
			{PolaroidHabCapo,		"../assets/images/Clues/placeClues/capoRoomPolaroid.png" },
			{PolaroidBosque,		"../assets/images/Clues/placeClues/bosquePolaroid.png" },
			{PolaroidCaseta,		"../assets/images/Clues/placeClues/casetaPolaroid.png" },
			{PolaroidDespacho,		"../assets/images/Clues/placeClues/despachoPolaroid.png" },
			{PolaroidHall,		"../assets/images/Clues/placeClues/hallPolaroid.png" },
			{PolaroidPasillo,		"../assets/images/Clues/placeClues/pasilloPolaroid.png" },
			{PolaroidEntrada,		"../assets/images/Clues/placeClues/entradaPolaroid.png" },

			//imagenes timeline
			{ TL1,				"../assets/images/Clues/TimeLineTut1.png" },
			{ TL2,				"../assets/images/Clues/TimeLineTut2.png" },
			{ TLAfur,			"../assets/images/Clues/TimeLineAfurPolaroid.png" },
			{ TLGus,			"../assets/images/Clues/TimeLineGusPolaroid.png" },
			{ TLJardinera,		"../assets/images/Clues/TimeLineJardineraPolaroid.png" },
			{ TLSabrina,		"../assets/images/Clues/TimeLineSabrinaPolaroid.png" },
			{ TimelinePlaceholders,			"../assets/images/UI/TLPlaceholders.png" }
};


vector<Resources::AnimInfo> Resources::anims_{
	{IdleSDLAnim, IdleSDL, 4,9,0,31,143, true},
	{WalkingSDLAnim, WalkingSDL, 1,8,0,7,143, true},
	{AppPressedAnim, AppPressed, 1,7,0,6,84, false},
	{CatIdleAnim, CatIdle, 1,8,0,7,84, true},
	{MacarenaCatIdleAnim, MacarenaCatIdle, 2,7,0,12,84,true},
	{FadeInAnim, FadeSpriteSheet, 3,4,0,5,14,false},
	{FadeOutAnim, FadeSpriteSheet, 3,4,5,11,14,false},
	{MainMenuAnim, MainMenuSpriteSheet, 5,5, 0,20, 84,false},
	{Humo1Anim, Humo1SpriteSheet, 5,5,0,21,1000,true},
	{OfficeWindowAnim, VentanaOficina0, 6,7, 0,38, 500, true},
	{officeFanAnim, officeFan, 3,4, 0,11, 120, true},
	{MaridoCapaKnifeAnim, MaridoCapaSpriteSheet, 2, 21, 0, 25, 84, true},
	{MaridoCapaRelaxAnim, MaridoCapaSpriteSheet, 2, 21, 26, 37, 200, true},
	{CatPortraitAnim, Resources::TextureID::CatPortrait, 5,4, 0, 19, 200, true},
	{MacarenaPortraitAnim, Resources::TextureID::MacarenaPortrait, 5, 5, 0, 21, 200, true},
	{SDLPortraitAnim, Resources::TextureID::LazaroPortrait, 2, 1, 0, 1, 1200, false},
	{SDLGhostAnim, Resources::TextureID::GhostSDL, 2, 4, 0, 5, 175, true},
	{UrsulaIdleHairAnim, Resources::TextureID::UrsulaIdle, 4, 9, 0, 11, 125, true},
	{UrsulaIdleGlassAnim, Resources::TextureID::UrsulaIdle, 4, 9, 12, 34, 125, true},
	{UrsulaWalkingAnim, Resources::TextureID::UrsulaWalking, 3, 3, 0, 11, 125, true},
	{MacarenaFacepalmAnim, Resources::TextureID::MacarenaFacepalm, 2, 9, 0, 17, 125, false},
	{MacarenaIdleAnim, Resources::TextureID::MacarenaHeadShake, 1, 4, 2, 2, 1250, true},
	{CatWalkingAnim, CatWalk,2,5,0,9,84, true},
	{CatRunningAnim, CatRun, 1,9,0,8,84, true},
	{CapoIdleAnim, ErnestoIdle, 3,4,0,11,250, true},
	{AfurAnim, Afur, 1,1,0,0,84,false},
	{AfurAnimFantasma, AfurFantasma, 2,4,0,5,84,true},
	{AfurPortraitFantasma, Afur, 2,1,0,1,84,true},
	{PortraitAfurAnim, AfurPortrait, 2,1,0,1,84,false},
	{YayaAnim, YayaIdle, 2,5,0,8,84,true},
	{SabrinaIdleAnim, SabrinaIdle, 2,3,0,5,84,true},
	{JardineraIdleAnim, JardineraIdle, 2,5,0,5,84,true},
	{GusIdleAnim, GusIdle, 2,4,0,5,84, true},



};

/*----------------------------------------------------*/
vector<Resources::ClueInfo> Resources::clues_ {

	 //-----------------------------------------
	 //------------ Caso Tutorial --------------
	 //-----------------------------------------

	{"Comida china",
	 "No recuerdo haber pedido esto, ni siquiera me gusta la comida china. Seguro que es de la secretaria. Aunque ella nunca entra en mi despacho... Seguro que es m\u00eda.",
	 "mi comida china.",
	 Resources::ClueType::Object,
	 Resources::ClueID::Tut_MigajasComida,
	 Resources::TextureID::ChineseFoodPhoto},

	{"Ara"+tildes_['ñ']+"azos de un animal",
	 "Me han dejado la silla hecha un asco. Tiene pinta de ser de un animal.",
	 "un animal.",
	 Resources::ClueType::Person,
	 Resources::ClueID::Tut_SillaRota,
	 Resources::TextureID::SillaDespachoPolaroid},

	{"Papeles desordenados",
	 "No es que yo sea la persona m\u00e1s limpia, pero esto no ha sido fruto de mi desorden. Adem\u00e1s, parece un desorden intencionado, como si alguien estuviese buscando algo entre mis cosas.",
	 "una persona salvaje.",
	 Resources::ClueType::Person,
	 Resources::ClueID::Tut_PapelesDesordenados,
	 Resources::TextureID::PolaroidPapelesDesordenados},

	 //-----------------------------------------
	 //------------ Caso Principal -------------
	 //-----------------------------------------

	 //--------------- Objetos -----------------

	 {"Contrato de confidencialidad",
	 "Contrato est" + tildes_['a'] + "ndar que te hace firmar la familia Polo cuando trabajas con ellos. Tener que firmar esto habla por s" + tildes_['i'] + " solo, pero la verdad es que pagan bien, y estoy corto de dinero... as" + tildes_['i'] + " que lo he firmado.",
	 "el contrato de confidencialidad",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_Contrato,
	 Resources::TextureID::Polaroidcontrato},

	 {"Navaja de Carlos Castro",
	 "Navaja mariposa muy bonita.",
	 "la navaja de Carlos",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_NavajaCarlos,
	 Resources::TextureID::Polaroidnavaja}, 
	
	 {"Piedra con musgo del bosque",
	 "Piedra con una forma un tanto afilada que tiene pinta de ser del bosque. No es especialmente bonita. Estaba en la habitaci"+ tildes_['o']+"n de Carlos y "+ tildes_['U']+"rsula.",
	 "la piedra del bosque",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PiedraMusgo,
	 Resources::TextureID::Polaroidroca},
	
	 {"Zapatos con barro",
	 "Unos pares de zapatos pertenecientes a Afur. Tiene pequeños restos de barro, lo cual me resulta extraño debido a lo inmaculada que es esta familia en cuanto a la est" + tildes_['e'] + "tica.",
	 "los zapatos de Afur",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_ZapatosBarro,
	 Resources::TextureID::femur},

	 {"Bala y casquillo",
	 "Una bala y un casquillo de bala que estaba en el bosque. La bala no tiene sangre. Tiene pinta de que pertenecen al mismo disparo. Que est" + tildes_['e'] + " en el lugar donde encontraron a Sabrina enterrada da qu"+tildes_['e']+" pensar, aunque por aqu" + tildes_['i'] + " pasan cazadores.",
	 "la bala y el casquillo",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_BalaCasquillo,
	 Resources::TextureID::PolaroidBala},

	 {"Herramientas de la caseta",
	 "Palas, tijeras de podar, rastrillos… Cualquiera de estos elementos podr" + tildes_['i'] + "a ser un arma homicida perfecta.",
	 "las herramientas de jardiner" + tildes_['i'] + "a",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_HerramientasCaseta,
	 Resources::TextureID::Polaroidherramientas},

	 {"Pa" + tildes_['ñ'] + "uelo rojo",
	 "Es un pa" + tildes_['ñ'] + "uelo rojo de una tela muy resistente que tiene bordado \"C.C.\". Estaba rodeando la empu" + tildes_['ñ'] + "adura de la pistola. ",
	 "el pa" +tildes_['ñ'] + "uelo rojo",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PanueloRojo,
	 Resources::TextureID::Polaroidpanuelo},

	 {"Pistola con silenciador",
	 "Es una pistola bastante pesada pero manejable. Se encontraba en el sal" + tildes_['o'] + "n de la casa. La bala y el casquillo parecen encajar con este modelo de pistola.",
	 "la pistola con silenciador",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PistolaSilenciador,
	 Resources::TextureID::Polaroidpistola},

	 {"Papeles de la herencia familiar",
	 "Estos papeles escritos por Marcelina Polo evidencian que quien tiene el poder en los negocios es Ernesto, aunque quien mejor lo llevar" + tildes_['i'] + "a ser" + tildes_['i'] + "a " + tildes_['U'] + "rsula. Se lee la frase: \"Esto es lo mejor para ti, hija. No quer" + tildes_['i'] + "a que llevaras una vida como la m" + tildes_['i'] + "a\". Parece claro qui" + tildes_['e'] + "n era la favorita.",
	 "los papeles de la herencia familiar",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PapelesHerencia,
	 Resources::TextureID::Polaroidherencia},

	 {"Contrato de confidencialidad de Gus",
	 "Es un contrato exactamente igual que el m" + tildes_['i'] + "o, pero con el nombre de “Mario L" + tildes_['a'] + "zaro”. Es de cuidador . Hay una foto de Gus en " + tildes_['e'] + "l. Siempre fue muy fotog" + tildes_['e'] + "nico.",
	 "el contrato de Gus",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_ContratoGus,
	 Resources::TextureID::PolaroidcontratoGus},

	 {"Llave",
	 "Llave de una habitaci" + tildes_['o'] + "n que estaba entre las cosas de Ernesto. Hay algunas habitaciones cerradas por la casa, as" + tildes_['i'] + " que estar" + tildes_['i'] + "a bien probar qu" + tildes_['e'] + " es lo que abre. Me hace gracia lo clich" + tildes_['e'] + " que es esto de encontrar una llave.",
	 "la llave",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_Llave,
	 Resources::TextureID::PolaroidllaveSabrina},

	 { "Fotograf" + tildes_['i'] + "a",
	 "Cuanto m" + tildes_['a'] + "s se relaciona este caso con Gus, m" + tildes_['a'] + "s nervioso estoy. En esta foto salen Gus, Ernesto y Sabrina en la puerta de la casa. Se les ve muy...felices.",
	 "la fotograf" + tildes_['i'] + "a",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_Foto,
	 Resources::TextureID::Polaroidfoto },

	 { "Orden de asesinato",
	 "Es el trozo de papel m" + tildes_['a'] + "s fr" + tildes_['i'] + "volo que he le" + tildes_['i'] + "do en mi vida. Se me para el coraz" + tildes_['o'] + "n cada vez que lo miro. “" + tildes_['O'] + "rdenes de Madre, acaba con el cuidador”." + tildes_['¿'] + "Por qu" + tildes_['e'] + " tuviste que estar metido en todo esto, Gus? ",
	 "la orden de asesinato",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_OrdenAsesinato,
	 Resources::TextureID::Polaroidorden },

	 { "Llave de Ernesto",
	 " La jardinera me ha dicho d" + tildes_['o'] + "nde estaba " + tildes_['e'] + "sta llave, y pese a que ya todo me da igual, no puedo dejar esto a medias. Necesito saber qu" + tildes_['e'] + " me depara detr" + tildes_['a'] + "s de la puerta que abra. Ernesto lo sabr" + tildes_['a'] + ".",
	 "la llave de Ernesto",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_LlaveErnesto,
	 Resources::TextureID::PolaroidllaveSotano },

	 //------------- Personajes ----------------

	 {"Ernesto Polo",
	 "Es el cabecilla de la familia Polo, todos le conocen. Es el que tiene m"+tildes_['a']+"s poder, aunque no tiene mucha mano con los negocios. Parece un tanto ingenuo. Es muy tosco y amenazante, pero está muy afectado por la muerte de su hija porque me ha pedido ayuda.",
	 "Ernesto Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_ErnestoPolo,
	 Resources::TextureID::PolaroidCapo },

	 {"Sabrina  Polo",
	 "Era la hija de Ernesto. Seg" + tildes_['u'] + "n se dice por ah" + tildes_['i'] + ", era jovial y simp" + tildes_['a'] + "tica, seguramente la m" + tildes_['a'] + "s honrada de todos, lejos del car" + tildes_['a'] + "cter serio y mezquino de la mayor" + tildes_['i'] + "a de la familia Polo. Tras su muerte, el ambiente familiar es incluso m" + tildes_['a'] + "s tenso y hay cierta hostilidad.",
	 "Sabrina  Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_SabrinaPolo,
	 Resources::TextureID::PolaroidSabrina },

	 { "" + tildes_['U'] + "rsula Polo",
	 "Es la hermana de Ernesto. Tiene pinta de ser la que maneja el cotarro de verdad, pese a que su hermano firme los papeles. Rezuma poder, o ansias del mismo.",
	 "" + tildes_['U'] + "rsula Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_UrsulaPolo,
	 Resources::TextureID::PolaroidCapa },

	 { "Carlos Castro",
	 "Es el marido de " + tildes_['U'] + "rsula. Se trata de un hombre bastante extravagante, me desconcierta su forma de ser. No sab" + tildes_['i'] + "a que una persona podr" + tildes_['i'] + "a estar tant" + tildes_['i'] + "simo tiempo hablando sobre objetos puntiagudos.",
	 "Carlos Castro",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_CarlosCastro,
	 Resources::TextureID::PolaroidCarlos },

	 { "Afur Polo",
	 "Es el hijo de " + tildes_['U'] + "rsula y Carlos. Tiene un nombre muy peculiar. No es muy hablador y parece tener un car" + tildes_['a'] + "cter d" + tildes_['e'] + "bil. Los padres son pijos hasta para el nombre del niño.",
	 "Afur Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_AfurPolo,
	 Resources::TextureID::PolaroidAfur },

	 { "Jardinera",
	 "Es el fantasma de una jardinera que debi" + tildes_['o'] + " trabajar aqu" + tildes_['i'] + " hace tiempo. Es muy misteriosa, lo cual me desconcierta. M" + tildes_['a'] + "s de lo que suelen desconcertar los fantasmas. Seg"+tildes_['u']+"n mi experiencia.",
	 "la jardinera",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_Jardinera,
	 Resources::TextureID::PolaroidJardinera },

	 { "Marcelina Polo",
	 "Madre de Ernesto y " + tildes_['U'] + "rsula. Era quien mandaba antes de Ernesto, y le pas" + tildes_['o'] + " el testigo cuando lleg" + tildes_['o'] + " a la vejez. Pese a haber fallecido, sigue teniendo mucha presencia en toda la casa. Parece una mujer muy dura, pero seguramente fuese una coraza generada por el cargo tan estresante que ten" + tildes_['i'] + "a en la familia.",
	 "Marcelina Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_MarcelinaPolo,
	 Resources::TextureID::PolaroidYaya },

	 { "Mario L" + tildes_['a'] + "zaro (Gustavo)",
	 "No.. No me lo puedo creer. No pens" + tildes_['e'] + " que fuera a volver a ver a Gustavo m" + tildes_['a'] + "s que en mis fotos y pensamientos m" + tildes_['a'] + "s dolorosos. Era el mejor polic" + tildes_['i'] + "a de todos, hac" + tildes_['i'] + "a de m" + tildes_['i'] + " la persona que siempre quise ser, y que sin " + tildes_['e'] + "l, se ha desvanecido. No s" + tildes_['e'] + " como acab" + tildes_['o'] + " aqu" + tildes_['i'] + ", pero parece ser que cuidaba de alguien de la familia.",
	 "Gustavo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_Gustavo,
	 Resources::TextureID::PolaroidGus },

	 //--------------- Lugares -----------------

	 { "Jard" + tildes_['i'] + "n de la entrada a la mansi" + tildes_['o'] + "n",
	  "Para ser la entrada a una mansi" + tildes_['o'] + "n, me parece que est" + tildes_['a'] + " bastante descuidada desde hace mucho.",
	  "el jard" + tildes_['i'] + "n",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_Jardin,
	  Resources::TextureID::femur}, 
	 
	 { "Sal" + tildes_['o'] + "n de la mansi" + tildes_['o'] + "n",
	  "Como era de esperar, es bastante lujoso y amplio, perfectamente apto para hacer una fiesta llena de pijos con dinero. No obstante, no parece que haya mucha vida por aqu" + tildes_['i'] + ". ",
	  "el sal" + tildes_['o'] + "n",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_Salon,
	  Resources::TextureID::femur },
	
	 { "Despacho de Ernesto",
	  "Despacho donde la familia hace sus negocios. Aqu" + tildes_['i'] + " reside quien mande, en este caso es Ernesto. Hay una puerta bloqueada al fondo de la habitaci" + tildes_['o'] + "n. Seguramente Ernesto se sienta muy inc" + tildes_['o'] + "modo teniendo a otras personas dentro de su despacho. Entiendo esa sensaci" + tildes_['o'] + "n.",
	  "el despacho de Ernesto",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_DespachoErnesto,
	  Resources::TextureID::femur }, 
	 
	 { "Habitaci" + tildes_['o'] + "n de " + tildes_['U'] + "rsula y Carlos",
	  "Una habitaci" + tildes_['o'] + "n lujosa para una gente lujosa. Hay muchos objetos de valor de Carlos, pero poco de " + tildes_['U'] + "rsula. Pens" + tildes_['e'] + " que ella ser" + tildes_['i'] + "a m" + tildes_['a'] + "s materialista.",
	  "la habitaci" + tildes_['o'] + "n de " + tildes_['U'] + "rsula y Carlos",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_HabUrsulaCarlos,
	  Resources::TextureID::femur },
	 
	 { "Habitaci" + tildes_['o'] + "n de Afur",
	  "Me parece una habitaci" + tildes_['o'] + "n bastante sosa, por lo que es acorde a la persona que duerme entre estas cuatro paredes.",
	  "la habitaci" + tildes_['o'] + "n de Afur",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_HabAfur,
	  Resources::TextureID::femur },
	
	 { "Habitaci" + tildes_['o'] + "n de Ernesto",
	  "Esta habitaci" + tildes_['o'] + "n es menos personal, parece m" + tildes_['a'] + "s algo heredado que el resto de habitaciones de la casa.",
	  "la habitaci" + tildes_['o'] + "n de Ernesto",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_HabErnesto,
	  Resources::TextureID::femur }, 
	 
	 { "Caseta del jard" + tildes_['i'] + "n",
	  "Es un espacio un tanto claustrof" + tildes_['o'] + "bico y desordenado. Veo que hasta en las familias m" + tildes_['a'] + "s ricas existe la cutrez de un trastero lleno de mierda, aunque en este caso bastante centrado en cosas de jardiner" + tildes_['i'] + "a muy oxidadas. Me transmite bastante m" + tildes_['a'] + "s fuerza del m" + tildes_['a'] + "s all" + tildes_['a'] + " que el resto de la casa.",
	  "la caseta del jard" + tildes_['i'] + "n",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_CasetaJardin,
	  Resources::TextureID::femur },

	 { "Habitaci" + tildes_['o'] + "n de Sabrina",
	  "Es una habitaci" + tildes_['o'] + "n normal y corriente, lo cual es llamativo sabiendo d" + tildes_['o'] + "nde vive y qui" + tildes_['e'] + "nes son su familia. Parece ser que Ernesto ha puesto muchos esfuerzos en que nadie est" + tildes_['e'] + " dentro de estas cuatro paredes. O bien est" + tildes_['a'] + " dolido, o bien, no quiere que vea algo.",
	  "la habitaci" + tildes_['o'] + "n de Sabrina",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_HabSabrina,
	  Resources::TextureID::femur },


};
vector<Resources::CentralClueInfo> Resources::centralClues_(
	{
		// @ persona
		// ~ Objeto
		// $ lugar
		Resources::CentralClueInfo(
			""+tildes_['¿']+"Qui"+tildes_['e']+"n ha entrado?",
			""+tildes_['¿']+"Qu"+tildes_['e']+" co" + tildes_['ñ'] + "o ha pasado aqu"+tildes_['i']+"? No me gusta que nadie m\u00e1s que yo entre a mi despacho porque pasa lo que pasa. Ahora toca descubrir qui\u00e9n o qu\u00e9 querr\u00eda venir aqu\u00ed.",
			Resources::ClueType::Person,
			Resources::ClueID::Tut_Cent_DesordenHabitacion,
			Resources::TextureID::TL1,
			{
				Resources::ClueID::Tut_SillaRota
			},
			"Ha entrado @",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "Qu"+tildes_['e']+" estaba buscando?",
			"Suponiendo que estoy en lo cierto con lo que sea que haya causado este desastre, ahora bien, "+tildes_['¿']+"por qu"+tildes_['e']+"?",
			Resources::ClueType::Object,
			Resources::ClueID::Tut_Cent_MotivoEntrada,
			Resources::TextureID::TL2,
			{
				Resources::ClueID::Tut_MigajasComida
			},
			"Vino en busca de ~",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "C" + tildes_['o'] + "mo muri" + tildes_['o'] + " la hija del capo?",
			"La muerte de Sabrina es un misterio en el que creo que puede caber cualquier perfil de esta familia. Necesito descubrir qui" + tildes_['e'] + "n la mat" + tildes_['o'] + ", c" + tildes_['o'] +
			"mo lo hizo y d" + tildes_['o'] + "nde fue para poder acusar con fundamento. No es que me importe mucho, pero me pagan bastante bien.",
			Resources::ClueType::Person,
			Resources::ClueID::Prin_Cent_MuerteHija,
			Resources::TextureID::TLSabrina,
			{
				Resources::ClueID::Prin_UrsulaPolo,
				Resources::ClueID::Prin_PanueloRojo,
				Resources::ClueID::Prin_HabSabrina
			},
			"A Sabrina la asesinó @ usando ~ en $ .",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "C" + tildes_['o'] + "mo muri" + tildes_['o'] + " la jardinera?",
			"No s"+tildes_['e']+" si esta mujer tiene algo que ver con todo esto, pero est" + tildes_['a'] 
			+ " claro que su fantasma va a estar en esta caseta porque le encante este sitio. Me desconcierta su presencia, o, m" + tildes_['a'] + "s bien, su no presencia.",
			Resources::ClueType::Person,
			Resources::ClueID::Prin_Cent_MuerteJardinera,
			Resources::TextureID::TLJardinera,
			{
				Resources::ClueID::Prin_ErnestoPolo,
			},
			"A la jardinera la asesinó @.",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "Por qu" + tildes_['e'] + " discutieron Afur y Sabrina?",
			"Parece ser que en alg" + tildes_['u'] + "n momento antes de morir, Afur y Sabrina tuvieron una importante discusi" + tildes_['o'] + "n que le atormentaba. Debo descubrir el motivo si quiero saber qu" + tildes_['e'] + " pas" + tildes_['o'] + " con Sabrina.",
			Resources::ClueType::Object,
			Resources::ClueID::Prin_Cent_Discusion,
			Resources::TextureID::TLAfur,
			{
				Resources::ClueID::Prin_OrdenAsesinato
			},
			"Afur y Sabrina discutieron por ~.",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "Qui" + tildes_['e'] + "n mat"+ tildes_['o']+" a Gus?",
			"No pens" + tildes_['e'] + " que todas estas muertes acabar" + tildes_['i'] + "an desembocando en la " + tildes_['u'] + "nica muerte que me importa de verdad, m" + tildes_['a'] + "s que la m" + tildes_['i'] + "a propia. Cari" + tildes_['ñ'] + "o...no s" + tildes_['e'] + " qu" + tildes_['e'] + " motivos ten" + tildes_['i'] + "as para meterte aqu" + tildes_['i'] + " dentro, pero lo que necesito saber es qui" + tildes_['e'] + "n te hizo esto y resolver lo que no me deja dormir por las noches. ",
			Resources::ClueType::Person,
			Resources::ClueID::Prin_Cent_MuerteGus,
			Resources::TextureID::TLGus,
			{
				Resources::ClueID::Prin_Jardinera
			},
			"A Gustavo lo asesinó @.",
			true)
	}
);

vector<Resources::TimelineInfo> Resources::timelineSolutions_(
	{
		//Poner cada elemento en el orden en el que aparecerán en el juego.
		//Los ID que hay que indicar también deben estar en orden. Deben ser de pistas principales (debido a que los eventos y su información lo forman las pistas principales)

//Primera Timeline (esta es una de prueba, en el tutorial no habrá)

//esta es la del caso principal pero no está montada
	Resources::TimelineInfo(
		{
			//vete al storymanager, abajo del todo
			//perfe
			//esto entonces lo lee el story manager, hay un int que se llama gameCase que te dice que timeline leer, ya que esta lo usamos y ponemios el 0
			//pues mejor quitar eso ahora, para no estar con una timeline creada que no se use, donde se cambia al caso 1? si recuerdas quitalo si puedes jaja
			Resources::ClueID::Prin_Cent_MuerteGus,
			Resources::ClueID::Prin_Cent_MuerteJardinera,
			Resources::ClueID::Prin_Cent_Discusion,
			Resources::ClueID::Prin_Cent_MuerteHija
		})
		//Etc
	}
);


//seguir el mismo orden que el enum, si no, van a asignarse mal los diálogos				---		Meter true al final pa matarlos
vector<Resources::ActorInfo> Resources::actors_{
	ActorInfo(Resources::ActorID::SDL, "L" + tildes_['a'] + "zaro", -1,				Resources::SceneID::EntradaDespacho,	Resources::AnimID::SDLPortraitAnim,				Resources::noAnim,						-1000,-250,30,30),
	ActorInfo(Resources::ActorID::MacarenaMartinez, "Macarena Mart\u00EDnez", -1,	Resources::SceneID::EntradaDespacho,	Resources::AnimID::MacarenaPortraitAnim,		Resources::MacarenaCatIdleAnim,			720, 340, 80, 264),
	ActorInfo(Resources::ActorID::Pelusa, "Black Cat", -1,							Resources::SceneID::EntradaDespacho,	Resources::AnimID::CatPortraitAnim,				Resources::CatIdleAnim,					980,580, 56,56),
	ActorInfo(Resources::ActorID::Barman, "Fernando el Barman", -1,					Resources::SceneID::Casa_Del_Profesor,	Resources::TextureID::Blank,					Resources::noAnim,						110,30, 30,30),
	ActorInfo(Resources::ActorID::CarlosI, "Carlos Castro", -1,						Resources::SceneID::JardinEntrada,		Resources::TextureID::CarlosPortrait,			Resources::AnimID::MaridoCapaKnifeAnim, 1350, 300, 184, 344),
	ActorInfo(Resources::ActorID::Capo, "Ernesto Polo", -1,							Resources::SceneID::DespachoPolo,		Resources::TextureID::ErnestoPortrait,			Resources::AnimID::CapoIdleAnim,		673,288,240,320),
	ActorInfo(Resources::ActorID::Capa, ""+ tildes_['U'] +"rsula Polo", -1,			Resources::SceneID::HabitacionCarlos,	Resources::TextureID::UrsulaPortrait,			Resources::UrsulaIdleHairAnim,				551,310,160,346),
	ActorInfo(Resources::ActorID::CarlosII, "Afur Polo", -1,						Resources::SceneID::HabitacionAfur,		Resources::TextureID::AfurPortrait,				Resources::AfurAnim,					544,350,80,264),
	ActorInfo(Resources::ActorID::F_Hija, "Sabrina Polo", -1,						Resources::SceneID::HabitacionSabrina,	Resources::TextureID::SabrinaPortrait,					Resources::SabrinaIdleAnim,				1246, 265,80,264, true),
	ActorInfo(Resources::ActorID::F_MamaCapo, "Marcelina Polo", -1,					Resources::SceneID::HabitacionErnesto,	Resources::TextureID::YayaPortrait,				Resources::YayaAnim,					544,340,80,264, true),
	ActorInfo(Resources::ActorID::F_Novio, "Gus", -1,								Resources::SceneID::Sotano,				Resources::TextureID::GusPortrait,			Resources::MacarenaCatIdleAnim,			624,340,80,264, true),
	ActorInfo(Resources::ActorID::F_Afur, "Fantasma de Afur Polo", -1,				Resources::SceneID::JardinEntrada,		Resources::AfurFantasmaPortrait,					Resources::AfurAnimFantasma,					750,340,80,264, true),
	ActorInfo(Resources::ActorID::F_AntiguoTrabajador, "Jardinera sin nombre", -1,	Resources::SceneID::CasetaJardin,		Resources::TextureID::JardineraPortrait,			Resources::JardineraIdleAnim,			704,340,80,264, true),

	ActorInfo(Resources::ActorID::PhoneCall, "...", -1,								Resources::SceneID::Casa_Del_Profesor,	Resources::TextureID::UnkownPortrait,			Resources::noAnim,						0,0,0,0)
};

//van por pares
//la que va a un sitio
//la que vuelve a ese sitio
vector<Resources::DoorInfo> Resources::doors_={

	//							nombrepuerta		dónde va								de dónde viene							sprite															x,y, w, h, spawnPoint	

	/*----------Despacho de SDL----------*/
	DoorInfo(Resources::DoorID::pRecepcionDespacho, Resources::SceneID::Despacho,			Resources::SceneID::EntradaDespacho,	Resources::TextureID::Blank,	Resources::AnimID::noAnim,		860, 228, 41*4, 79*4,  10,333),
	DoorInfo(Resources::DoorID::pDespachoRecpecion, Resources::SceneID::EntradaDespacho,	Resources::SceneID::Despacho,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		60 ,  280,44 * 2,200 * 2 , 840, 120),
	

	/*----------Mansión de los Polo----------*/
	DoorInfo(Resources::DoorID::pDespachoPasillo,	Resources::SceneID::Pasillo,			Resources::SceneID::DespachoPolo,		Resources::TextureID::Blank,	Resources::AnimID::noAnim,		1234,284 , 120,128 , 190, 250),//xy de sabrina : 240,580,960,230 arriba
	DoorInfo(Resources::DoorID::pPasilloDespacho,	Resources::SceneID::DespachoPolo,		Resources::SceneID::Pasillo,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		190,250 , 70,240  , 1234, 284),//

	DoorInfo(Resources::DoorID::pEntradaBosque,		Resources::SceneID::Bosque,				Resources::SceneID::JardinEntrada,		Resources::TextureID::Blank,	Resources::AnimID::noAnim,		570,550 , 120,128 , 2261,395),
	DoorInfo(Resources::DoorID::pBosqueEntrada,		Resources::SceneID::JardinEntrada,		Resources::SceneID::Bosque,				Resources::TextureID::Blank,	Resources::AnimID::noAnim,		2261,395 , 120,128 , 75, 280),

	DoorInfo(Resources::DoorID::pEntradaCaseta,		Resources::SceneID::CasetaJardin,		Resources::SceneID::JardinEntrada,		Resources::TextureID::Blank,	Resources::AnimID::noAnim,		1940,560 , 120,128 , 800, 450),
	DoorInfo(Resources::DoorID::pCasetaEntrada,		Resources::SceneID::JardinEntrada,		Resources::SceneID::CasetaJardin,		Resources::TextureID::Blank,	Resources::AnimID::noAnim,		900,450 , 120,128 , 1940, 280),

	DoorInfo(Resources::DoorID::pEntradaSalon,		Resources::SceneID::Salon,				Resources::SceneID::JardinEntrada,		Resources::TextureID::Blank,	Resources::AnimID::noAnim,		1195,80 , 120,360  , 694,623),
	DoorInfo(Resources::DoorID::pSalonEntrada,		Resources::SceneID::JardinEntrada,		Resources::SceneID::Salon,				Resources::TextureID::Blank,	Resources::AnimID::noAnim,		694,623 , 120,128 , 1195, 280),

	DoorInfo(Resources::DoorID::pPasilloEntrada,	Resources::SceneID::Salon,				Resources::SceneID::Pasillo,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		328,220 , 50,200, 90, 450),
	DoorInfo(Resources::DoorID::pEntradaPasillo,	Resources::SceneID::Pasillo,			Resources::SceneID::Salon,				Resources::TextureID::Blank,	Resources::AnimID::noAnim,		90,450 , 80,200 , 328, 220),

	DoorInfo(Resources::DoorID::pSabrinaPasillo,	Resources::SceneID::Pasillo,			Resources::SceneID::HabitacionSabrina,	Resources::TextureID::Blank,	Resources::AnimID::noAnim,		60,240, 130,430 , 948,202),
	DoorInfo(Resources::DoorID::pPasilloSabrina,	Resources::SceneID::HabitacionSabrina,	Resources::SceneID::Pasillo,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		948,202, 147,500  ,60,240),

	DoorInfo(Resources::DoorID::pCarlosPasillo,		Resources::SceneID::HabitacionCarlos,	Resources::SceneID::Pasillo,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		870,250 , 70,240  , 58, 335),
	DoorInfo(Resources::DoorID::pPasilloCarlos,		Resources::SceneID::Pasillo,			Resources::SceneID::HabitacionCarlos,	Resources::TextureID::Blank,	Resources::AnimID::noAnim,		53,314 , 120,128 , 870, 250),

	DoorInfo(Resources::DoorID::pAfurPasillo,		Resources::SceneID::Pasillo,			Resources::SceneID::HabitacionAfur,		Resources::TextureID::Blank,	Resources::AnimID::noAnim,		1152,190 , 100,500  , 80, 300),
	DoorInfo(Resources::DoorID::pPasilloAfur,		Resources::SceneID::HabitacionAfur,		Resources::SceneID::Pasillo,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		80,300 , 100,500 , 1152, 190),
	
	DoorInfo(Resources::DoorID::pCapoPasillo,		Resources::SceneID::Pasillo,			Resources::SceneID::HabitacionErnesto,		Resources::TextureID::Blank,	Resources::AnimID::noAnim,		162,525 , 130,430 , 1100, 187),
	DoorInfo(Resources::DoorID::pPasilloCapo,		Resources::SceneID::HabitacionErnesto,		Resources::SceneID::Pasillo,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		1100,187 , 147,500  , 162, 525),

	DoorInfo(Resources::DoorID::pDespachoSotano,	Resources::SceneID::Sotano,		Resources::SceneID::DespachoPolo,			Resources::TextureID::Blank,	Resources::AnimID::noAnim,		80*8,480 , 480,300  , 140, 350),

};

vector<Resources::InvestigableInfo> Resources::investigables_{
	InvestigableInfo(Resources::ClueID::Tut_MigajasComida, "No recuerdo haberme comido esto.",Resources::SceneID::Despacho, Resources::TextureID::ChineseFoodInteractable, Resources::AnimID::noAnim, 228, 673, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_PapelesDesordenados, "No parece que les interesara el dinero que hab\u00eda por aqu\u00ed. *Suspiro* Tampoco habr\u00edan encontrado mucho.",Resources::SceneID::Despacho, Resources::TextureID::PapelesDesordenadosInteractable, Resources::AnimID::noAnim, 419, 464, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_SillaRota, "" + tildes_['¿'] + "Por qu\u00e9 habr\u00e1n ara" + tildes_['ñ'] + "ado mis muebles? No son muy civilizados...",Resources::SceneID::Despacho, Resources::TextureID::SillaDespachoInteractable, Resources::AnimID::noAnim, 960, 420, 30, 30),
	
	
	InvestigableInfo(Resources::ClueID::Prin_NavajaCarlos, "Debe de ser su favorita. La tiene muy bien guardada.",Resources::SceneID::HabitacionCarlos, Resources::TextureID::Navaja, Resources::AnimID::noAnim, 472, 242, 30, 30),
	InvestigableInfo(Resources::ClueID::Prin_PiedraMusgo, "" + tildes_['¿'] + "Una piedra? " + tildes_['¿'] + "De d" + tildes_['o'] + "nde la habr" + tildes_['a'] + " sacado?",Resources::SceneID::HabitacionCarlos, Resources::TextureID::Roca, Resources::AnimID::noAnim, 260, 534, 30, 30),
	InvestigableInfo(Resources::ClueID::Prin_BalaCasquillo, "La bala no tiene sangre, y seguramente este sea su casquillo . Me pregunto si el disparo fallido iba dirigido a Sabrina.",Resources::SceneID::Bosque, Resources::TextureID::Bala, Resources::AnimID::noAnim, 898, 598, 30, 30),
	InvestigableInfo(Resources::ClueID::Prin_PanueloRojo, "" + tildes_['¿'] + "Por qu" + tildes_['e'] + " esconder" + tildes_['i'] + "an esto?",Resources::SceneID::Pasillo, Resources::TextureID::Panuelo, Resources::AnimID::noAnim, 529,336, 30, 30),
	InvestigableInfo(Resources::ClueID::Prin_PistolaSilenciador, "Interesante... Es del mismo calibre que la bala del bosque.",Resources::SceneID::Pasillo, Resources::TextureID::Pistola, Resources::AnimID::noAnim, 576, 352, 30, 30),
	InvestigableInfo(Resources::ClueID::Prin_HerramientasCaseta, "Palas, tijeras de podar, rastrillos... Cualquiera de estos elementos podr" + tildes_['i'] + "a ser un arma homicida perfecta.",Resources::SceneID::CasetaJardin, Resources::TextureID::Blank, Resources::AnimID::noAnim, 300, 420, 100, 30),
	InvestigableInfo(Resources::ClueID::Prin_Llave, "" + tildes_['¿'] + "Una llave? Qu" + tildes_['e'] + " peliculero.",Resources::SceneID::DespachoPolo, Resources::TextureID::LlaveSabrina, Resources::AnimID::noAnim, 906, 540, 100, 30),
	InvestigableInfo(Resources::ClueID::Prin_PapelesHerencia, "Aqu" + tildes_['i'] + " est" + tildes_['a'] + " la carta que escribi" + tildes_['o'] + " Martina. Efectivamente, es lo que ella dec" + tildes_['i'] + "a. Esconderla de esta manera es caer muy bajo.",Resources::SceneID::DespachoPolo, Resources::TextureID::Herencia, Resources::AnimID::noAnim, 782, 538, 100, 30),
	InvestigableInfo(Resources::ClueID::Prin_ContratoGus, "Otro contrato como el m" + tildes_['i'] + "o. Un momento... " + tildes_['¿'] + tildes_['¡'] + "GUS!? " + 
	tildes_['¿'] + tildes_['¡'] + "QU" + tildes_['E'] + " CO" + tildes_['Ñ'] + "O HACE ESTA FAMILIA CONTRATANDO A GUS!? No puede ser... Es de cuatro meses antes de que " + tildes_['e'] + "l se fuera. Un momento, " +
	tildes_['¿'] + "lo contrataron de cuidador? " + tildes_['¿'] + tildes_['¡'] + "En qu" +tildes_['e']+ "andas... andabas metido, Gus?",Resources::SceneID::DespachoPolo, Resources::TextureID::ContratoGus, Resources::AnimID::noAnim, 655,534, 100, 30),
	InvestigableInfo(Resources::ClueID::Prin_Foto, "Gus... " + tildes_['¿'] + "Por esto dejaste de hablarme?",Resources::SceneID::HabitacionSabrina, Resources::TextureID::Foto, Resources::AnimID::noAnim, 464, 540, 100, 30),
	InvestigableInfo(Resources::ClueID::Prin_OrdenAsesinato, "(" + tildes_['O'] + "rdenes de Madre, acaba con... " + tildes_['¿'] + tildes_['¡'] + "con Gus!? Lo que me tem" + tildes_['i'] + "a. Voy a ver a la puta vieja. YA.",Resources::SceneID::HabitacionSabrina, Resources::TextureID::Orden, Resources::AnimID::noAnim, 701, 546, 100, 30),
};

vector<Resources::SceneInfo> Resources::scenes_
{
	SceneInfo(Resources::SceneID::EntradaDespacho, Resources::TextureID::BGEntradaOficinaSDL,Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::LocationIcon, {50,510}, {{136,350}, {700,350},{840,250}}),
	SceneInfo(Resources::SceneID::Despacho, Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::Blank, {0, 0 }, {{87,322 },{351,347 },{625,379 },{1023,343 }}),
	SceneInfo(Resources::SceneID::calleProfesor, Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::Blank,{30,30 }, {{0,0}}),
	SceneInfo(Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::Blank, {100,180}, {{0,0}}),
	SceneInfo(Resources::SceneID::DespachoPolo,Resources::TextureID::DespachoCapo, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::LocationIcon,{1110,420},{{207,459 },{475,356 },{821,364 },{986,355 },{1106,349 },{1245,314 }}),
	SceneInfo(Resources::SceneID::HabitacionCarlos,Resources::TextureID::HabitacionCapaBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{200,100},{{{119,371 },{424,308 },{931,378 }}}),
	SceneInfo(Resources::SceneID::HabitacionErnesto,Resources::TextureID::HabitacionCapoBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{300,100},{{{201,494 },{285,319 },{990,365 },{1326,451 }}}),
	SceneInfo(Resources::SceneID::HabitacionAfur,Resources::TextureID::HabitacionAfurBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{400,100},{{{271,378 },{534,338 },{812,326 },{1100,361 }}}),
	SceneInfo(Resources::SceneID::HabitacionSabrina,Resources::TextureID::HabitacionSabrinaBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{500,100},{{0,0}}),
	SceneInfo(Resources::SceneID::JardinEntrada,Resources::TextureID::BGJardin, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::LocationIcon,{1100,430},{{449,370 },{868,334 },{1208,252 },{1516,369 },{1976,559 }}),
	SceneInfo(Resources::SceneID::CasetaJardin,Resources::TextureID::BackgroundCasetaJardin, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,300},{{214,315 },{798,316 },{991,655 }}),
	SceneInfo(Resources::SceneID::Salon,Resources::TextureID::HallBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,400},{{77,361 },{618,466 },{1090,356 }}),
	SceneInfo(Resources::SceneID::Pasillo,Resources::TextureID::PasilloBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,500},{{72,333 },{361,218 },{821,249 },{1080,364 }}),
	SceneInfo(Resources::SceneID::Bosque,Resources::TextureID::BosqueBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::LocationIcon,{980,330},{{0,0}}),
	SceneInfo(Resources::SceneID::Sotano,Resources::TextureID::SotanoBG, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,400},{{269,355 },{602,363 },{705,294 }})
};


/*----------------------------------------------------*/


vector<Resources::MusicInfo> Resources::musics_ {
//
		{ MTint, "../assets/sound/MainThemeIntro.wav" } ,//
		{ MTloo, "../assets/sound/MainThemeLoop.wav" }, //
		{ GhostDraft, "../assets/sound/GhostTheme3NoDrums.wav" }, //
		//{ GhostDraftDrums, "../assets/sound/GhostTheme3NoDrums.wav" }, //
		{ GhostLove, "../assets/sound/GhostLove.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Wall_Hit, "../assets/sound/wall_hit.wav" }, //
		{ Paddle_Hit, "../assets/sound/paddle_hit.wav" }, //
		{ Buzz, "../assets/sound/buzzCut.wav" }, //
		{ Bip, "../assets/sound/bip.wav" }, //
		{ Minigame_W, "../assets/sound/SFX/Minigame/w_bar.wav" }, //
		{ Door_open, "../assets/sound/SFX/overworld/Door_Opening.wav" }, //
		{ Levitating, "../assets/sound/SFX/overworld/Levitating.wav"  }, //
		{ Phone_Beep, "../assets/sound/SFX/overworld/Phone Beep.wav"  }, //
		{ FS_wood_0, "../assets/sound/SFX/overworld/wood/fs_wood_0.wav" }, //
		{ FS_wood_1, "../assets/sound/SFX/overworld/wood/fs_wood_1.wav"  }, //
		{ FS_wood_2, "../assets/sound/SFX/overworld/wood/fs_wood_2.wav" }, //
		{ FS_wood_3,"../assets/sound/SFX/overworld/wood/fs_wood_3.wav"  }, //
		{ FS_wood_4, "../assets/sound/SFX/overworld/wood/fs_wood_4.wav"  }, //
		{ FS_wood_5, "../assets/sound/SFX/overworld/wood/fs_wood_5.wav"  }, //
		{ FS_wood_6, "../assets/sound/SFX/overworld/wood/fs_wood_6.wav"  }, //
		{ FS_grass_0, "../assets/sound/SFX/overworld/grass/fs_grass_0.wav"  }, //
		{ FS_grass_1, "../assets/sound/SFX/overworld/grass/fs_grass_1.wav"  }, //
		{ FS_grass_2, "../assets/sound/SFX/overworld/grass/fs_grass_2.wav"  }, //
		{ FS_grass_3, "../assets/sound/SFX/overworld/grass/fs_grass_3.wav"  }, //
		{ FS_grass_4, "../assets/sound/SFX/overworld/grass/fs_grass_4.wav"  }, //
		{ FS_grass_5, "../assets/sound/SFX/overworld/grass/fs_grass_5.wav" }, //
		{ FS_grass_6,"../assets/sound/SFX/overworld/grass/fs_grass_6.wav" }, //
		{ FS_grass_7, "../assets/sound/SFX/overworld/grass/fs_grass_7.wav"  }, //
		{ ButtonClicked, "../assets/sound/SFX/ButtonClicked.wav" }, //
		{ ClueDropped, "../assets/sound/SFX/clueDropped.wav"  }, //
		{ PinDropped, "../assets/sound/SFX/PinDropped.wav" }, //
		{ CameraClick, "../assets/sound/SFX/overworld/camera.wav" }, //
		{ Event, "../assets/sound/SFX/event.wav" }, //
		{ Stress_Low, "../assets/sound/SFX/Minigame/stress_low.wav" }, //
		{ Stress_Medium, "../assets/sound/SFX/Minigame/stress_medium.wav" }, //
		{ Stress_High, "../assets/sound/SFX/Minigame/stress_high.wav" }, //
};

