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
			{Background, "../assets/images/background.png"},//
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
			{CorkBG, "../assets/images/corkBG.jpg"}
};


vector<Resources::AnimInfo> Resources::anims_{
	{CoinAnim, Pajarito, 3,3,0,5,100, true},
	{CoinAnim2, Pajarito, 3,3,5,9,100, true}
};



vector<Resources::ClueInfo> Resources::clues_ {

	{"Arma Homicida",
	 "Un cuchillo ensangrentado con un adorno en la empuñadura",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Arma_Homicida,
	 Resources::TextureId::Blank},

	{"Arma Homicida2",
	 "Un cuchillo ensangrentado con un adorno en la empuñadura",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Arma_Homicida2,
	 Resources::TextureId::Blank},

	{"Arma Homicida3",
	 "Un cuchillo ensangrentado con un adorno en la empuñadura",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Arma_Homicida3 ,
	 Resources::TextureId::Blank},

	{"Arma Homicida4",
	 "Un cuchillo ensangrentado con un adorno en la empuñadura",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Arma_Homicida4 ,
	 Resources::TextureId::Blank},

	{"Alfombra Rota",
	 "Una pieza de tela que formaba parte de una alfombra en la cocina del profesor.",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Alfombra_Rota ,
	 Resources::TextureId::Blank},

	{"Cuadro de Van Damme",
	 "Un cuadro de Van Damme con una firma. MB",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Cuadro_De_Van_Damme ,
	 Resources::TextureId::Blank},

	{"Retrato de Dovahkiin",
	 "El mejor rpg de la historia",
	 Resources::ClueType::Object,
	 Resources::ClueIDs::Retratrato_De_Dovahkiin,
	 Resources::TextureId::Blank}
};


vector<Resources::ActorInfo> Resources::actors_{
	{Resources::ActorID::Profesor, Resources::SceneID::calleProfesor, "Profesor Leon", Resources::TextureId::Blank},
	{Resources::ActorID::Barman, Resources::SceneID::Casa_Del_Profesor, "Barman", Resources::TextureId::Blank},
	{Resources::ActorID::PoliceOfficer, Resources::SceneID::Casa_Del_Profesor, "PoliceOfficer", Resources::TextureId::Blank}
};


/*----------------------------------------------------*/
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
		{ Boooo, "../assets/sound/boooo.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Wall_Hit, "../assets/sound/wall_hit.wav" }, //
		{ Paddle_Hit, "../assets/sound/paddle_hit.wav" }, //
		{ Bip, "../assets/sound/bip.wav" } //
};

