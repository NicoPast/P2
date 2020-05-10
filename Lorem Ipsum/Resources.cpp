#include "Resources.h"
#include "SDL_macros.h"
static map<char, string>tildes_{
	{
		'o', "\u00f3"
	},
	{
		'a', "\u00e1"
	},
	{
		'i', "\u00ed"
	},
	{
		'u', "\u00fa"
	},
	{
		'e', "\u00e9"
	},
	{
		'ñ', "\u00F1"
	},
	{ '¿', "\u00BF"}
};

vector<Resources::FontInfo> Resources::fonts_{
	//
			{ RobotoTest24, "../assets/fonts/RobotoMono-Bold.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_{
	//
			{ Blank, "../assets/images/blank.png" }, //
			{ Background, "../assets/images/background.png"},//
			{ FadeSpriteSheet, "../assets/images/FadeAnimations.png" }, //
			{ MainMenuBG, "../assets/images/MenuBG.png" }, //
			{ MainMenuBG1, "../assets/images/MenuBG1.png" }, //
			{ MainMenuBG2, "../assets/images/MenuBG2.png" }, //
			{ MainMenuBG3, "../assets/images/MenuBG3.png" }, //
			{ MainMenuBut, "../assets/images/MainMenuBut.png" }, //
			{ Pixel, "../assets/images/whiterect.png" }, //
			{ CorkBG, "../assets/images/corkBG.jpg"},
			{ MapsBG, "../assets/images/mapBg.png" }, //
			{ AddIcon, "../assets/images/addIcon.png" }, //
			{ EditIcon, "../assets/images/editIcon.png" },//
		    { Manometer, "../assets/images/manometer.png" }, //
		    { ManometerNeedle, "../assets/images/needle.png" }, //
		    { TunerBG, "../assets/images/tunerBG.png" }, //
		    { Bars, "../assets/images/radioBars.png" }, //
		    { Lock, "../assets/images/lockBars.png" }, //
		    { ResetStress, "../assets/images/resetStress.png" }, //
			{ IdleSDL, "../assets/images/Idle.png"},
			{ WalkingSDL, "../assets/images/WalkingSDL.png"},
			{ ChatInteraction, "../assets/images/conversationIcon.png"},
			{ ClueInteraction, "../assets/images/clueIcon.png"},
			{ DoorInteraction, "../assets/images/doorIcon.png"},
			{ GhostInteraction, "../assets/images/heart.png"},
			{TrashIcon, "../assets/images/trashIcon.png"},
			{AppPressed, "../assets/images/App Pressed.png"},
			{DeathAppIcon, "../assets/images/Death App Icon.png"},
			{MapAppIcon, "../assets/images/MapAppIcon.png"},
			{ChinchetarioAppIcon, "../assets/images/ChinchetarioAppIcon.png"},
			{OptionsAppIcon, "../assets/images/OptionsAppIcon.png"},
			{PhoneAppIcon, "../assets/images/PhoneAppIcon.png"},
			{ NotesAppIcon, "../assets/images/NotesAppIcon.png"},
			{OptionBars,"../assets/images/optionsBars.png"},
			{PhoneOn, "../assets/images/Phone On.png"},
			{PhoneOff, "../assets/images/Phone Off.png"},
			{MacarenaIdle, "../assets/images/MacarenaCatIdle.png"},
			{femur, "../assets/images/femur.png"},
			{DialogBox, "../assets/images/DialogBox.png"},
			{CatIdle, "../assets/images/IdleCat.png"},
			{VerticalUIPanel, "../assets/images/VerticalUIPanel.png"},
			{HorizontalUIPanel, "../assets/images/HorizontalUIPanel.png"},
			{LazaroPortrait, "../assets/images/PortraitLazaro.png"},
			{MacarenaPortrait, "../assets/images/PortraitMacarena.png"},
			{CatPortrait, "../assets/images/PortraitGato.png"},
			{BGEntradaOficinaSDL, "../assets/images/OficinaEntradaSDL.png"},
			{clueTemplate, "../assets/images/Polaroid.png"},
			{TimelineBG, "../assets/images/timelineBG.png"},
			{Humo1SpriteSheet, "../assets/images/bgHumo1.png"},
			{Chinchetas, "../assets/images/Chinchetas.png"},
			{GoBackButton, "../assets/images/GoBackButton.png"},
			{HideShowButton, "../assets/images/HideShowButton.png"},
			{ChineseFoodPhoto, "../assets/images/ChineseFoodPhoto.png"},
			{ChineseFoodInteractable, "../assets/images/ChineseFoodInteractable.png"},
			{PapelesDesordenadosInteractable, "../assets/images/PapelesDesordenadosInteractable.png"},
			{SillaDespachoInteractable, "../assets/images/SillaDespachoInteractable.png"},

			{MainMenuSpriteSheet, "../assets/images/MenuBGAnim.png"}
};


vector<Resources::AnimInfo> Resources::anims_{
	{IdleSDLAnim, IdleSDL, 4,9,0,31,143, true},
	{WalkingSDLAnim, WalkingSDL, 1,8,0,7,143, true},
	{AppPressedAnim, AppPressed, 1,7,0,6,84, false},
	{CatIdleAnim, CatIdle, 1,8,0,7,84, true},
	{MacarenaCatIdleAnim, MacarenaIdle, 2,7,0,12,84,true},
	{FadeInAnim, FadeSpriteSheet, 3,4,0,11,14,false},
	{FadeOutAnim, FadeSpriteSheet, 3,3,3,6,14,false},
	{MainMenuAnim, MainMenuSpriteSheet, 3,4, 0,10, 84,false},
	{Humo1Anim, Humo1SpriteSheet, 5,5,0,21,1000,true}
};

/*----------------------------------------------------*/
vector<Resources::ClueInfo> Resources::clues_ {

	 //-----------------------------------------
	 //------------ Caso Tutorial --------------
	 //-----------------------------------------

	{"Comida china",
	 "No recuerdo haber pedido esto, ni siquiera me gusta la comida china. Seguro que es de la secretaria. Aunque ella nunca entra en mi despacho... Seguro que es m\u00eda",
	 "mi comida china",
	 Resources::ClueType::Object,
	 Resources::ClueID::Tut_MigajasComida,
	 Resources::TextureID::ChineseFoodPhoto},

	{"Ara"+tildes_['ñ']+"azos de un animal",
	 "Me han dejado la silla hecha un asco. Tiene pinta de ser de un animal",
	 "un animal",
	 Resources::ClueType::Person,
	 Resources::ClueID::Tut_SillaRota,
	 Resources::TextureID::femur},

	{"Papeles desordenados",
	 "No es que yo sea la persona m\u00e1s limpia, pero esto no ha sido fruto de mi desorden. Adem\u00e1s, parece un desorden intencionado, como si alguien estuviese buscando algo entre mis cosas.",
	 "una persona salvaje",
	 Resources::ClueType::Person,
	 Resources::ClueID::Tut_PapelesDesordenados,
	 Resources::TextureID::femur}

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
			Resources::TextureID::femur,
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
			Resources::TextureID::femur,
			{
				Resources::ClueID::Tut_MigajasComida
			},
			"Vino en busca de ~",
			true)
	}
);

vector<Resources::TimelineInfo> Resources::timelineSolutions_(
	{
		//Poner cada elemento en el orden en el que aparecerán en el juego.
		//Los ID que hay que indicar también deben estar en orden. Deben ser de pistas principales (debido a que los eventos y su información lo forman las pistas principales)

		//Primera Timeline (esta es una de prueba, en el tutorial no habrá)
		Resources::TimelineInfo(
			{
				Resources::ClueID::Tut_Cent_DesordenHabitacion,
				Resources::ClueID::Tut_Cent_MotivoEntrada
			})
		//Etc
	}
);


//seguir el mismo orden que el enum, si no, van a asignarse mal los diálogos				---		Meter true al final pa matarlos
vector<Resources::ActorInfo> Resources::actors_{
	ActorInfo(Resources::ActorID::SDL, "L"+tildes_['a']+"zaro", -1, Resources::SceneID::EntradaDespacho, Resources::TextureID::LazaroPortrait, Resources::noAnim, -1000,-250,30,30),
	ActorInfo(Resources::ActorID::Barman, "Fernando el Barman", -1, Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Blank, Resources::noAnim,110,30, 30,30),
	ActorInfo(Resources::ActorID::MacarenaMartinez, "Macarena Mart\u00EDnez", -1, Resources::SceneID::EntradaDespacho, Resources::TextureID::MacarenaPortrait, Resources::MacarenaCatIdleAnim,200, 545, 40, 132),
	ActorInfo(Resources::ActorID::Pelusa, "Black Cat", -1, Resources::SceneID::EntradaDespacho, Resources::TextureID::CatPortrait, Resources::CatIdleAnim,110,680, 28,28)
};

vector<Resources::DoorInfo> Resources::doors_={
	DoorInfo(Resources::DoorID::pRecepcionDespacho, Resources::SceneID::Despacho, Resources::SceneID::EntradaDespacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 850, 400, 120, 240,  10,0),
	DoorInfo(Resources::DoorID::pDespachoRecpecion, Resources::SceneID::EntradaDespacho, Resources::SceneID::Despacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 10, 400,   50, 100, 840, 120)
};

vector<Resources::InvestigableInfo> Resources::investigables_{
	InvestigableInfo(Resources::ClueID::Tut_MigajasComida, "No recuerdo haberme comido esto.",Resources::SceneID::Despacho, Resources::TextureID::ChineseFoodInteractable, Resources::AnimID::noAnim, 120, 530, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_PapelesDesordenados, "No parece que les interesara el dinero que hab\u00eda por aqu\u00ed. *Sigh* Tampoco habr\u00edan encontrado mucho",Resources::SceneID::Despacho, Resources::TextureID::PapelesDesordenadosInteractable, Resources::AnimID::noAnim, 170, 530, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_SillaRota, ""+tildes_['ñ']+"Por qu\u00e9 habr\u00e1n arañado mis muebles? No son muy civilizados...",Resources::SceneID::Despacho, Resources::TextureID::SillaDespachoInteractable, Resources::AnimID::noAnim, 220, 530, 30, 30),
};

vector<Resources::SceneInfo> Resources::scenes_
{
	SceneInfo(Resources::SceneID::EntradaDespacho, Resources::TextureID::BGEntradaOficinaSDL,Resources::TextureID::Background, Resources::TextureID::Blank, {150,150}, {{136,500}, {700,500},{840,410}}),
	SceneInfo(Resources::SceneID::Despacho, Resources::TextureID::Background, Resources::TextureID::BGEntradaOficinaSDL, Resources::TextureID::Blank, {0, 0 }, {{0,0}}),
	SceneInfo(Resources::SceneID::calleProfesor, Resources::TextureID::Background, Resources::TextureID::BGEntradaOficinaSDL, Resources::TextureID::Blank,{30,30 }, {{0,0}}),
	SceneInfo(Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Background, Resources::TextureID::BGEntradaOficinaSDL, Resources::TextureID::Blank, {100,180}, {{0,0}})
};


/*----------------------------------------------------*/


vector<Resources::MusicInfo> Resources::musics_ {
//
		{ MTint, "../assets/sound/MainThemeIntro.wav" } ,//
		{ MTloo, "../assets/sound/MainThemeLoop.wav" }, //
		{ GhostDraft, "../assets/sound/GhostDraft.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Wall_Hit, "../assets/sound/wall_hit.wav" }, //
		{ Paddle_Hit, "../assets/sound/paddle_hit.wav" }, //
		{ Bip, "../assets/sound/bip.wav" } //
};

