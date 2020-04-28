#pragma once

#include <SDL.h>
#include "DialogSystem.h"
#include <string>
#include <vector>
#include <map>
#include "Vector2D.h"

using namespace std;
class Resources {
public:

	enum TextureId : std::size_t {
		// images
		Blank,
		Background,
		AddIcon,
		EditIcon,
		TennisBall,
		KeyBoardIcon,
		MouseIcon,
		AIIcon,
		SpaceShips,
		Airplanes,
		Star,
		BlackHole,
		MainMenuBG,
		Pajarito,
		Pixel,
		CorkBG,
		MapsBG,
		IdleSDL,
		WalkingSDL,
		ChatInteraction,
		ClueInteraction,
		DoorInteraction,
		GhostInteraction,
		// text
		HelloWorld,
		PressAnyKey,
		GameOver,
		Manometer,
		ManometerNeedle,
		TunerBG,
		Bars,
		Lock,
		ResetStress,
	};
	enum AudioId : std::size_t {
		// music
		Beat,
		Cheer,
		Boooo,

		// sound effects
		Wall_Hit,
		Paddle_Hit,
		Bip
	};
	enum FontId : std::size_t {
		ARIAL16, ARIAL24, RobotoTest24
	};
	enum AnimID : std::size_t
	{
		CoinAnim,
		CoinAnim2,
		IdleSDLAnim, 
		WalkingSDLAnim,
		LastAnimID
	};
	enum ClueIDs
	{
		Arma_Homicida,
		Arma_Homicida2,
		Arma_Homicida3,
		Arma_Homicida4,
		Alfombra_Rota,
		Cuadro_De_Van_Damme,
		Retratrato_De_Dovahkiin,
		lastClueID,
		Central_Clue_1,
		Central_Clue_2,
		Central_Clue_3,
		lastCentralClueID
	};
	enum ActorID {
		Profesor,
		PoliceOfficer,
		Barman,
		SDL,
		lastActorID
	};
	enum SceneID : size_t
	{
		Casa_Del_Profesor = 0,
		calleProfesor,
		lastSceneID
	};
	/*
	enum InteractionType : std::size_t
	{
		ChatInteraction,
		ClueInteraction,
		DoorInteraction,
		GhostInteraction,
		lastInteractionType
	};

	struct InteractionInfo
	{
		InteractionType id;
		string texture;
	};
	/**/
	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};
	struct ImageInfo {
		TextureId id;
		string fileName;
	};
	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};
	struct MusicInfo {
		AudioId id;
		string fileName;
	};
	struct SoundInfo {
		AudioId id;
		string fileName;

	};
	struct AnimInfo {
		AnimID id_;
		TextureId textureId_;
		int rows_;
		int cols_;
		int initialFrame_;
		int lastFrame_;
		size_t speed_;
		bool loop_=false;
	};
	struct ActorInfo
	{
		ActorID id_;
		SceneID startScene_;
		string name_;
		TextureId sprite_;
		TextureId portrait_;
		string dialog_="";
		int x_;
		int y_;
	};

	enum ClueType
	{
		Object,
		Person,
		Place
	};
	struct ClueInfo
	{
		ClueInfo(std::string t, std::string d, ClueType ty, ClueIDs id, TextureId i) : title_(t), description_(d), type_(ty), id_(id), image_(i){};
		std::string title_;
		std::string description_;
		ClueType type_;
		ClueIDs id_;
		TextureId image_;
	};
	struct CentralClueInfo : ClueInfo
	{
		CentralClueInfo(std::string t, std::string d, ClueType ty, ClueIDs id, TextureId i, vector<ClueIDs> l, std::string ed, bool tl) : ClueInfo(t, d, ty, id, i), links_(l), eventDescription_(ed), timeline_(tl) {};
		vector<ClueIDs> links_;
		std::string eventDescription_;
		bool timeline_;
	};

	struct SceneInfo
	{
		SceneID id_;
		TextureId backgroundId_;
		TextureId mapIcon_;
		Vector2D mapPos_;
	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<AnimInfo> anims_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp

	/*En un mundo m�gico todo lo de abajo ser�an jotasones T-T*/
	static vector<SceneInfo> scenes_;
	static map<string, ActorID> actorNames_;
	static vector<ActorInfo> actors_;
	static vector<ClueInfo> clues_;
	static vector<CentralClueInfo> centralClues_;
	//static vector<InteractionInfo> interactableIcons_;
	//Un coj�n de strings y numeros
	//static vector<Conversation> conversations_;

};
