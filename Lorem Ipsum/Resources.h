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

	enum TextureID : std::size_t {
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
		MainMenuBut,
		LazaroPortrait,
		Pixel,
		CorkBG,
		MapsBG,
		IdleSDL,
		WalkingSDL,
		ChatInteraction,
		ClueInteraction,
		DoorInteraction,
		GhostInteraction,
		TrashIcon,
		DeathAppIcon,
		ChinchetarioAppIcon,
		MapAppIcon,
		PhoneOn,
		PhoneOff,
		AppPressed,
		Manometer,
		ManometerNeedle,
		TunerBG,
		Bars,
		Lock,
		ResetStress,
		clueTemplate,
		femur,
		VerticalUIPanel,
		HorizontalUIPanel,
		MacarenaIdle,
		DialogBox,
		BGEntradaOficinaSDL,
		FadeSpriteSheet,
		CatIdle
	};
	enum AudioId : std::size_t {
		// music
		Beat,
		Cheer,
		Boooo,
		MTint,
		MTloo,
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
		IdleSDLAnim, 
		WalkingSDLAnim,
		AppPressedAnim,
		CatIdleAnim,
		MacarenaCatIdleAnim,
		FadeInAnim,
		FadeOutAnim,
		LastAnimID,
		noAnim
	};
	enum ClueID
	{
		//-----------------------------------------
		//-------- Pistas no Principales ----------
		//-----------------------------------------

		//-----------------------------------------
		//------------ Caso Tutorial --------------
		//-----------------------------------------

		Tut_SillaRota,
		Tut_PapelesDesordenados,
		Tut_MigajasComida,

		//-----------------------------------------
		//-----------------------------------------
		//-----------------------------------------

		lastClueID,

		//-----------------------------------------
		//---------- Pistas Centrales -------------
		//-----------------------------------------

		//-----------------------------------------
		//------------ Caso Tutorial --------------
		//-----------------------------------------

		Tut_Cent_DesordenHabitacion,
		Tut_Cent_MotivoEntrada,

		//-----------------------------------------
		//-----------------------------------------
		//-----------------------------------------

		lastCentralClueID
	};
	enum DoorID : size_t {
		pRecepcionDespacho = 0,
		pDespachoRecpecion,
		lastDoorID
	};

	//Al crear un actorID y un actorInfo, mantener el orden del enum en el vector.
	enum ActorID :size_t{
		SDL = 0, //No mover a SDL, tiene que ser el 0
		Profesor,
		PoliceOfficer,
		PoliceOfficer2,
		PoliceOfficer3,
		PoliceOfficer4,

		//-----------------------------------------
		//------------ Caso Tutorial --------------
		//-----------------------------------------

		MacarenaMartinez,
		Pelusa,

		//-----------------------------------------
		//-----------------------------------------
		//-----------------------------------------

		//-----------------------------------------
		//------------- Caso del Bar --------------
		//-----------------------------------------

		Barman,
		Claudio,
		Lydia,
		Consuelo,
		Camarero,

		//------------ Fantasmas -------------
		F_Juanjo,
		F_ExtraCasaDeJuanjo,
		//-----------------------------------------
		//-----------------------------------------
		//-----------------------------------------

		//-----------------------------------------
		//------------ Caso Principal -------------
		//-----------------------------------------

		Capo,
		Hija,
		Anthony,
		Capa,
		Eduardo,
		Soprimo,
		CarlosII,
		DamaDeLaLimpieza,
		Brayan,
		YayaPolo,

		//------------ Fantasmas -------------

		F_Hija,
		F_Capo,
		F_MamaCapo,
		F_Novio,
		F_Soprimo,
		F_AntiguoTrabajador,

		//-----------------------------------------
		//-----------------------------------------
		//-----------------------------------------
		lastActorID
	};
	enum SceneID : size_t
	{
		EntradaDespacho = 0,
		Despacho,

		Casa_Del_Profesor,
		calleProfesor,
		
		lastSceneID
	};
	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};
	struct ImageInfo {
		TextureID id;
		string fileName;
	};
	struct TextMsgInfo {
		TextureID id;
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
		TextureID textureId_;
		int rows_;
		int cols_;
		int initialFrame_;
		int lastFrame_;
		size_t speed_;
		bool loop_=false;
	};

	//-----------------------------------------
	//-----------------------------------------
	//-----------------------------------------

	struct ObjectInfo 
	{
		ObjectInfo(SceneID scene, TextureID texture, AnimID anim, int x, int y, int w, int h) :
			startScene_(scene),
			sprite_(texture),
			anim_(anim),
			x_(x),
			y_(y),
			w_(w),
			h_(h)
		{};
		SceneID startScene_;
		TextureID sprite_;
		AnimID anim_;
		int x_;
		int y_;
		int w_;
		int h_;
	};
	struct DoorInfo : ObjectInfo
	{
		DoorInfo(DoorID door, SceneID goTo, SceneID scene, TextureID texture, AnimID anim, int x, int y, int w, int h, int spawnX, int spawnY) :
			ObjectInfo(scene, texture, anim, x, y, w, h),
			goTo_(goTo),
			id_(door),
			spawnPoint_(spawnX, spawnY)
		{}
		DoorID id_;
		SceneID goTo_;
		Vector2D spawnPoint_; //The point iwch the player will be translated to
	};
	struct InvestigableInfo : ObjectInfo
	{
		InvestigableInfo(ClueID clue, SceneID scene, TextureID texture, AnimID anim, int x, int y, int w, int h) :
			ObjectInfo(scene, texture, anim, x, y, w, h),
			unlockable_(clue)
		{};
		ClueID unlockable_;
	};
	struct ActorInfo : ObjectInfo
	{
		ActorInfo(ActorID actor, string name, int dialogId, SceneID scene, TextureID texture, AnimID anim, int x, int y, int w, int h) :
			ObjectInfo(scene, texture, anim, x, y, w, h),
			id_(actor),
			name_(name),
			dialogId_(dialogId)
		{};
		ActorID id_;
		string name_;
		int dialogId_ = -1;
	};

	enum ClueType
	{
		Object,
		Person,
		Place
	};
	struct ClueInfo
	{
		ClueInfo(std::string t, std::string d, ClueType ty, ClueID id, TextureID i) : title_(t), description_(d), type_(ty), id_(id), image_(i){};
		std::string title_;
		std::string description_;
		ClueType type_;
		ClueID id_;
		TextureID image_;
	};
	struct CentralClueInfo : ClueInfo
	{
		CentralClueInfo(std::string t, std::string d, ClueType ty, ClueID id, TextureID i, vector<ClueID> l, std::string ed, bool tl) : ClueInfo(t, d, ty, id, i), links_(l), eventDescription_(ed), timeline_(tl) {};
		vector<ClueID> links_;
		std::string eventDescription_;
		bool timeline_;
	};

	struct SceneInfo
	{
		SceneInfo(SceneID id, TextureID backgroundId, TextureID mapIcon, Vector2D mapPos) :
			id_(id),
			backgroundId_(backgroundId),
			mapIcon_(mapIcon),
			mapPos_(mapPos)
		{}
		SceneID id_;
		TextureID backgroundId_;
		TextureID mapIcon_;
		Vector2D mapPos_;
	};

	static vector<FontInfo> fonts_;   // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<AnimInfo> anims_;	  // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp

	/*En un mundo m�gico todo lo de abajo ser�an jotasones T-T*/
	static vector<SceneInfo> scenes_;
	static vector<ActorID> actorNames_;
	static vector<ActorInfo> actors_;
	static vector<DoorInfo> doors_;
	static vector<InvestigableInfo> investigables_;
	static vector<ClueInfo> clues_;
	static vector<CentralClueInfo> centralClues_;
	//static vector<InteractionInfo> interactableIcons_;


};
