#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "../assets/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "../assets/fonts/ARIAL.ttf", 24 }, //
		{ RobotoTest24, "../assets/fonts/RobotoMono-Bold.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Blank, "../assets/images/blank.png" }, //
		{ TennisBall, "../assets/images/tennis_ball.png" }, //
		{ KeyBoardIcon, "../assets/images/keyboard.png" }, //
		{ MouseIcon, "../assets/images/mouse.png" }, //
		{ AIIcon, "../assets/images/ai.png" }, //
		{ SpaceShips, "../assets/images/spaceships.png" }, //
		{ Airplanes, "../assets/images/airplanes.png" }, //
		{ Star, "../assets/images/star.png" }, //
		{ BlackHole, "../assets/images/black-hole.png" }, //
		{ MainMenuBG, "../assets/images/MainMenuBG.jpg" }, //
		{ Pajarito, "../assets/images/badges.png" } //
};


vector<Resources::AnimInfo> Resources::anims_{
	{CoinAnim, Pajarito, 3,3,0,5,100, true},
	{CoinAnim2, Pajarito, 3,3,5,9,100, true},
};






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

