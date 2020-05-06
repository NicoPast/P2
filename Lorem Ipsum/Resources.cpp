#include "Resources.h"
#include "SDL_macros.h"
vector<Resources::FontInfo> Resources::fonts_{
	//
			{ ARIAL16, "../assets/fonts/ARIAL.ttf", 16 }, //
			{ ARIAL24, "../assets/fonts/ARIAL.ttf", 24 }, //
			{ RobotoTest24, "../assets/fonts/RobotoMono-Bold.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_{
	//
			{ Blank, "../assets/images/blank.png" }, //
			{ Background, "../assets/images/background.png"},//
			{ TennisBall, "../assets/images/tennis_ball.png" }, //
			{ FadeSpriteSheet, "../assets/images/FadeAnimations.png" }, //
			{ KeyBoardIcon, "../assets/images/keyboard.png" }, //
			{ MouseIcon, "../assets/images/mouse.png" }, //
			{ AIIcon, "../assets/images/ai.png" }, //
			{ SpaceShips, "../assets/images/spaceships.png" }, //
			{ Airplanes, "../assets/images/airplanes.png" }, //
			{ Star, "../assets/images/star.png" }, //
			{ BlackHole, "../assets/images/black-hole.png" }, //
			{ MainMenuBG, "../assets/images/MainMenuBG.png" }, //
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
			{BGEntradaOficinaSDL, "../assets/images/OficinaEntradaSDL.png"},
			{clueTemplate, "../assets/images/clueTemplate.png"}
};


vector<Resources::AnimInfo> Resources::anims_{
	{IdleSDLAnim, IdleSDL, 4,9,0,31,84, true},
	{WalkingSDLAnim, WalkingSDL, 1,8,0,7,84, true},
	{AppPressedAnim, AppPressed, 1,7,0,6,84, false},
	{CatIdleAnim, CatIdle, 1,8,0,7,84, true},
	{MacarenaCatIdleAnim, MacarenaIdle, 2,7,0,12,84,true},
	{FadeInAnim, FadeSpriteSheet, 3,4,0,11,14,false},
	{FadeOutAnim, FadeSpriteSheet, 3,3,3,6,14,false}
};


/*----------------------------------------------------*/
vector<Resources::ClueInfo> Resources::clues_ {

	 //-----------------------------------------
	 //------------ Caso Tutorial --------------
	 //-----------------------------------------

	{"Comida china",
	 "No recuerdo haber pedido esto, ni siquiera me gusta la comida china. Seguro que es de la secretaria. Aunque ella nunca entra en mi despacho... Seguro que es mía",
	 "mi comida china",
	 Resources::ClueType::Object,
	 Resources::ClueID::Tut_MigajasComida,
	 Resources::TextureID::femur},

	{"Arañazos de un animal",
	 "Me han dejado la silla hecha un asco. Tiene pinta de ser de un animal",
	 "un animal",
	 Resources::ClueType::Person,
	 Resources::ClueID::Tut_SillaRota,
	 Resources::TextureID::femur},

	{"Papeles desordenados",
	 "No es que yo sea la persona más limpia, pero esto no ha sido fruto de mi desorden. Además, parece un desorden intencionado, como si alguien estuviese buscando algo entre mis cosas.",
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
			"¿Quién ha entrado?",
			"¿Qué coño ha pasado aquí? No me gusta que nadie más que yo entre a mi despacho porque pasa lo que pasa. Ahora toca descubrir quién o qué querría venir aquí.",
			Resources::ClueType::Person,
			Resources::ClueID::Tut_Cent_DesordenHabitacion,
			Resources::TextureID::femur,
			{
				Resources::ClueID::Tut_SillaRota
			},
			"Ha entrado @",
			false),

		Resources::CentralClueInfo(
			"¿Qué estaba buscando?",
			"Suponiendo que estoy en lo cierto con lo que sea que haya causado este desastre, ahora bien, ¿por qué?",
			Resources::ClueType::Object,
			Resources::ClueID::Tut_Cent_MotivoEntrada,
			Resources::TextureID::femur,
			{
				Resources::ClueID::Tut_MigajasComida
			},
			"Vino en busca de ~",
			false)
	}
);
	
//seguir el mismo orden que el enum, si no, van a asignarse mal los diálogos
vector<Resources::ActorInfo> Resources::actors_{
	ActorInfo(Resources::ActorID::SDL, "L\u00E1zaro", -1, Resources::SceneID::EntradaDespacho, Resources::TextureID::Blank, Resources::noAnim, -1000,-250,30,30),
	ActorInfo(Resources::ActorID::Profesor, "Profesor Le\u00F3n", -1, Resources::SceneID::Casa_Del_Profesor , Resources::TextureID::Blank, Resources::noAnim, 10,250,30,30),
	ActorInfo(Resources::ActorID::PoliceOfficer, "Oficial Luis", -1, Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Blank, Resources::noAnim,250,250,30,30),
	ActorInfo(Resources::ActorID::PoliceOfficer2, "Oficial Luis 2", -1, Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Blank, Resources::noAnim,300,250,30,30),
	ActorInfo(Resources::ActorID::PoliceOfficer3, "Oficial Luis 3", -1, Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Blank, Resources::noAnim,350,250,30,30),
	ActorInfo(Resources::ActorID::PoliceOfficer4, "Oficial Luis 4", -1, Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Blank, Resources::noAnim,400,250,30,30),
	ActorInfo(Resources::ActorID::MacarenaMartinez, "Macarena Mart\u00EDnez", -1, Resources::SceneID::EntradaDespacho, Resources::TextureID::Blank, Resources::MacarenaCatIdleAnim,200, 300, 40, 132),
	ActorInfo(Resources::ActorID::Pelusa, "Black Cat", -1, Resources::SceneID::EntradaDespacho, Resources::TextureID::Blank, Resources::CatIdleAnim,110,250, 28,28),
	ActorInfo(Resources::ActorID::Barman, "Fernando el Barman", -1, Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Blank, Resources::noAnim,110,250, 30,30),
	ActorInfo(Resources::ActorID::Claudio, "Claudio Polo", -1, Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Blank, Resources::AnimID::noAnim, 450, 250, 30, 30)
};

vector<Resources::DoorInfo> Resources::doors_={
	DoorInfo(Resources::DoorID::pRecepcionDespacho, Resources::SceneID::Despacho, Resources::SceneID::EntradaDespacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 500, 250, 50, 100,0,50),
	DoorInfo(Resources::DoorID::pDespachoRecpecion, Resources::SceneID::EntradaDespacho, Resources::SceneID::Despacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 0, 250, 50, 100,500,50)
};

vector<Resources::InvestigableInfo> Resources::investigables_{
	InvestigableInfo(Resources::ClueID::Tut_MigajasComida, Resources::SceneID::Despacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 120, 250, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_PapelesDesordenados, Resources::SceneID::Despacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 170, 250, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_SillaRota, Resources::SceneID::Despacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 220, 250, 30, 30),
};

/*
map<string, Resources::ActorID> Resources::actorNames_
{
	{"Profesor Leon", Resources::ActorID::Profesor},
	{"Fernando el Barman", Resources::ActorID::Barman},
	{"Oficial Luis", Resources::ActorID::PoliceOfficer}
};
*/

vector<Resources::SceneInfo> Resources::scenes_
{
	SceneInfo(Resources::SceneID::EntradaDespacho, Resources::TextureID::BGEntradaOficinaSDL, Resources::TextureID::Blank, {150,150}),
	SceneInfo(Resources::SceneID::Despacho, Resources::TextureID::Background, Resources::TextureID::Blank, {0, 0 }),
	SceneInfo(Resources::SceneID::calleProfesor, Resources::TextureID::BlackHole,Resources::TextureID::Blank,{30,30 }),
	SceneInfo(Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Background,Resources::TextureID::Blank, {100,180})
};


/*----------------------------------------------------*/


vector<Resources::MusicInfo> Resources::musics_ {
//
		{ Beat, "../assets/sound/beat.wav" }, //
		{ Cheer, "../assets/sound/cheer.wav" }, //
		{ Boooo, "../assets/sound/boooo.wav" }, //
		{ MTint, "../assets/sound/MainThemeIntro.mp3" } ,//
		{ MTloo, "../assets/sound/MainThemeLoop.mp3" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Wall_Hit, "../assets/sound/wall_hit.wav" }, //
		{ Paddle_Hit, "../assets/sound/paddle_hit.wav" }, //
		{ Bip, "../assets/sound/bip.wav" } //
};
/*
vector<Resources::InteractionInfo> Resources::interactableIcons_
{
	{ChatInteraction, "../assets/images/life.png"},
	{ ClueInteraction, "../assets/images/star.png"},
	{ DoorInteraction, "../assets/images/heart.png"},
	{ GhostInteraction, "../assets/images/addIcon.png"}
};
/**/
static map<char, char>tildes_{
	{
		'o', '\u00f3'
	},
	{
		'a', '\u00e1'
	},
	{
		'i', '\u00ed'
	},
	{
		'u', '\u00fa'
	},
	{
		'e', '\u00e9'
	}
};