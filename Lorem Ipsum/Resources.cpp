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
			{ KeyBoardIcon, "../assets/images/keyboard.png" }, //
			{ MouseIcon, "../assets/images/mouse.png" }, //
			{ AIIcon, "../assets/images/ai.png" }, //
			{ SpaceShips, "../assets/images/spaceships.png" }, //
			{ Airplanes, "../assets/images/airplanes.png" }, //
			{ Star, "../assets/images/star.png" }, //
			{ BlackHole, "../assets/images/black-hole.png" }, //
			{ MainMenuBG, "../assets/images/MainMenuBG.jpg" }, //
			{ Pajarito, "../assets/images/badges.png" }, //
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
			{PhoneOn, "../assets/images/Phone On.png"},
			{PhoneOff, "../assets/images/Phone Off.png"},
			{clueTemplate, "../assets/images/clueTemplate.png"},
			{femur, "../assets/images/femur.png"},
			{CatIdle, "../assets/images/IdleCat.png"}
};


vector<Resources::AnimInfo> Resources::anims_{
	{CoinAnim, Pajarito, 3,3,0,5,100, true},
	{CoinAnim2, Pajarito, 3,3,5,9,100, true},
	{IdleSDLAnim, IdleSDL, 4,9,0,31,84, true},
	{WalkingSDLAnim, WalkingSDL, 1,8,0,7,84, true},
	{AppPressedAnim, AppPressed, 1,7,0,6,84, false},
	{CatIdleAnim, CatIdle, 1,8,0,7,84, true}
};


/*----------------------------------------------------*/
vector<Resources::ClueInfo> Resources::clues_ {

	/*
	{"Ana Mart\u00edn",
	 "Una chica bajita",
	 Resources::ClueType::Person,
	 Resources::ClueIDs::Arma_Homicida,
	 Resources::TextureId::femur},

	{"Arma Homicida2",
	 "Un cuchillo ensangrentado con un adorno en la empu�adura",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Arma_Homicida2,
	 Resources::TextureId::femur},

	{"Arma Homicida3",
	 "Un cuchillo ensangrentado con un adorno en la empu�adura",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Arma_Homicida3 ,
	 Resources::TextureId::femur},

	{"Arma Homicida4",
	 "Un cuchillo ensangrentado con un adorno en la empu�adura",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Arma_Homicida4 ,
	 Resources::TextureId::femur},

	{"Alfombra Rota",
	 "Una pieza de tela que formaba parte de una alfombra en la cocina del profesor.",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Alfombra_Rota ,
	 Resources::TextureId::femur},

	{"Centro comercial",
	 "La guarida de Harley Queen",
	 Resources::ClueType::Place,
	 Resources::ClueIDs::Cuadro_De_Van_Damme ,
	 Resources::TextureId::femur},

	{"Retrato de Dovahkiin",
	 "El mejor rpg de la historia",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Retratrato_De_Dovahkiin,
	 Resources::TextureId::femur},
	 */

	 //-----------------------------------------
	 //------------ Caso Tutorial --------------
	 //-----------------------------------------

	{"Migajas de comida por el suelo",
	 "Restos de comida china en mi despacho. No recuerdo haberme comido esto...",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Tut_MigajasComida,
	 Resources::TextureId::femur},

	{"Arañazos en la silla",
	 "Alguien ha hecho de mi silla un verdadero estropicio. Esta gente no tiene ni un poco de verg\u00FCenza",
	 Resources::ClueType::Place,
	 Resources::ClueIDs::Tut_SillaRota,
	 Resources::TextureId::femur},

	{"Papeles desordenados",
	 "",
	 Resources::ClueType::Place,
	 Resources::ClueIDs::Tut_MotivoEntrada,
	 Resources::TextureId::femur}

};
vector<Resources::CentralClueInfo> Resources::centralClues_(
	{
	/*
	Resources::CentralClueInfo(
		"Pista Central 1",
		"aaaaaaaasuputuamandre",
		Resources::ClueType::Object, 
		Resources::ClueIDs::Central_Clue_1 ,
		Resources::TextureId::femur,
		{
			Resources::ClueIDs::Alfombra_Rota,
			Resources::ClueIDs::Arma_Homicida,
			Resources::ClueIDs::Cuadro_De_Van_Damme
		},
		"@ compr\u00f3 ~ en $.",
		true),
	 
	Resources::CentralClueInfo(
		"Pista Central 2",
		"filho da puta",
		Resources::ClueType::Person,
		Resources::ClueIDs::Central_Clue_2,
		Resources::TextureId::femur,
		{
			 Resources::ClueIDs::Arma_Homicida2
		},
		"Tremendo ~.",
		false),
	Resources::CentralClueInfo(
		"Pista Central 3",
		"agora si entemdo",
		Resources::ClueType::Place,
		Resources::ClueIDs::Central_Clue_3,
		Resources::TextureId::femur,
		{
			 Resources::ClueIDs::Arma_Homicida3
		},
		"Tremendísimo ~, tron.",
		false)	
	*/
	Resources::CentralClueInfo(
		"La habitaci\u00F3n esta desordenada", 
		"", 
		Resources::ClueType::Place, 
		Resources::ClueIDs::Tut_DesordenHabitacion,
		Resources::TextureId::femur,
		{
			Resources::ClueIDs::Tut_SillaRota
		},
		"",
		false)
	}
);
	
//seguir el mismo orden que el enum, si no, van a asignarse mal los diálogos
vector<Resources::ActorInfo> Resources::actors_{
	{Resources::ActorID::SDL, Resources::SceneID::calleProfesor, "L\u00E1zaro", Resources::TextureId::Blank, Resources::noAnim, -1,-1000,-250,30,30},
	{Resources::ActorID::Profesor, Resources::SceneID::calleProfesor, "Profesor Le\u00F3n", Resources::TextureId::Blank, Resources::noAnim, -1,10,250,30,30},
	{Resources::ActorID::PoliceOfficer, Resources::SceneID::Casa_Del_Profesor, "Oficial Luis", Resources::TextureId::Blank, Resources::noAnim, -1,250,250,30,30},
	{Resources::ActorID::PoliceOfficer2, Resources::SceneID::Casa_Del_Profesor, "Oficial Luis 2", Resources::TextureId::Blank, Resources::noAnim, -1,300,250,30,30},
	{Resources::ActorID::PoliceOfficer3, Resources::SceneID::Casa_Del_Profesor, "Oficial Luis 3", Resources::TextureId::Blank, Resources::noAnim, -1,350,250,30,30},
	{Resources::ActorID::Barman, Resources::SceneID::Casa_Del_Profesor, "Fernando el Barman", Resources::TextureId::Blank, Resources::noAnim,-1,110,250, 30,30},
	{Resources::ActorID::Pelusa, Resources::SceneID::calleProfesor, "Black Cat", Resources::TextureId::Blank, Resources::CatIdleAnim,-1,110,250, 28,28}

};

map<string, Resources::ActorID> Resources::actorNames_
{
	{"Profesor Leon", Resources::ActorID::Profesor},
	{"Fernando el Barman", Resources::ActorID::Barman},
	{"Oficial Luis", Resources::ActorID::PoliceOfficer}
};

vector<Resources::SceneInfo> Resources::scenes_
{
	{Resources::SceneID::calleProfesor, Resources::TextureId::BlackHole,Resources::TextureId::Blank,{30,30} },
	{Resources::SceneID::Casa_Del_Profesor, Resources::TextureId::Background,Resources::TextureId::Blank, {100,180} }
};


/*----------------------------------------------------*/


vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }, //
		{ PressAnyKey, "Press Any Key to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOver, "Game Over", { COLOR(0xffffbbff) }, ARIAL24 } //
};

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