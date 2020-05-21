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
		MainMenuBG,
		MainMenuBG1,
		MainMenuBG2,
		MainMenuBG3,
		MainMenuBut,
		LazaroPortrait,
		MacarenaPortrait,
		CatPortrait,
		Chinchetas,
		GoBackButton,
		HideShowButton,
		ChineseFoodPhoto,
		ChineseFoodInteractable,
		PapelesDesordenadosInteractable,
		SillaDespachoInteractable,
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
		OptionsAppIcon,
		PhoneAppIcon,
		NotesAppIcon,
		NotificationIcon,
		PhoneOn,
		PhoneOff,
		AppPressed,
		TimelineBG,
		Manometer,
		ManometerNeedle,
		TunerBG,
		Bars,
		OptionBars, 
		Lock,
		ResetStress,
		clueTemplate,
		femur,
		clueEvent,
		VerticalUIPanel,
		VerticalUIPanel2,
		HorizontalUIPanel,
		HorizontalUIPanel2,
		MessageUIPanel,
		MacarenaIdle,
		DialogBox,
		BGEntradaOficinaSDL,
		BGJardin,
		FadeSpriteSheet,
		MainMenuSpriteSheet,
		Humo1SpriteSheet,
		Escritorio,
		VentanaOficina3,
		VentanaOficina2,
		VentanaOficina1,
		VentanaOficina0,
		officeFan,
		CatIdle,
		BackgroundDeathWorld,
		GhostSDL,
		MaridoCapaSpriteSheet,
		DespachoCapo,
		AfurPortrait,
		Afur,
		UrsulaIdle,
		CarlosPortrait,
		BackgroundCasetaJardin,
	};
	enum AudioId : std::size_t {
		// music
		MTint,
		MTloo,
		GhostDraft,
		// sound effects
		Wall_Hit,
		Paddle_Hit,
		Buzz,
		Bip
	};
	enum FontId : std::size_t {
		RobotoTest24
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
		MainMenuAnim,
		Humo1Anim,
		OfficeWindowAnim,
		officeFanAnim,
		MaridoCapaKnifeAnim,
		MaridoCapaRelaxAnim,
		CatPortraitAnim,
		MacarenaPortraitAnim,
		SDLPortraitAnim,
		SDLGhostAnim,
		CapaIdleAnim,
		//ESTOS DEJARLOS AL FINAL
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
		//------------ Caso Principal -------------
		//-----------------------------------------

		//--------------- Objetos -----------------

		Prin_Contrato,
		Prin_NavajaCarlos,
		Prin_PiedraMusgo,
		Prin_ZapatosBarro,
		Prin_BalaCasquillo,
		Prin_HerramientasCaseta,
		Prin_PanueloRojo,
		Prin_PistolaSilenciador,

		Prin_PapelesHerencia,
		Prin_ContratoGus,
		Prin_Llave,

		Prin_Foto,
		Prin_OrdenAsesinato,
		Prin_LlaveErnesto,

		//------------- Personajes ----------------

		Prin_ErnestoPolo,
		Prin_SabrinaPolo,
		Prin_UrsulaPolo,
		Prin_CarlosCastro,
		Prin_AfurPolo,
		Prin_Jardinera,

		Prin_MarcelinaPolo,
		Prin_Gustavo,

		//--------------- Lugares -----------------

		Prin_Jardin,
		Prin_Salon,
		Prin_DespachoErnesto,
		Prin_HabUrsulaCarlos,
		Prin_HabAfur,
		Prin_HabErnesto,
		Prin_CasetaJardin,

		Prin_HabSabrina,

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
		//------------ Caso Principal -------------
		//-----------------------------------------

		Prin_Cent_MuerteHija,
		Prin_Cent_MuerteJardinera,

		Prin_Cent_Discusion,

		Prin_Cent_MuerteGus,

		//-----------------------------------------
		//-----------------------------------------
		//-----------------------------------------

		lastCentralClueID
	};
	enum DoorID : size_t {
		pRecepcionDespacho = 0,
		pDespachoRecpecion,
		
		
		pDespachoPasillo,
		pPasilloDespacho,
		pEntradaBosque,
		pBosqueEntrada,
		pEntradaCaseta,
		pCasetaEntrada,
		pEntradaSalon,
		pSalonEntrada,
		lastDoorID
	};

	//Al crear un actorID y un actorInfo, mantener el orden del enum en el vector.
	enum ActorID :size_t{
		SDL = 0, //No mover a SDL, tiene que ser el 0

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
		CarlosI,
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
		F_Afur,
		F_AntiguoTrabajador,

		//-----------------------------------------
		//-----------------------------------------
		//-----------------------------------------
		PhoneCall,
		lastActorID
	};
	enum SceneID : size_t
	{
		EntradaDespacho = 0,
		Despacho,

		Casa_Del_Profesor,
		calleProfesor,
		
		DespachoPolo,
		HabitacionCarlos,
		HabitacionErnesto,
		HabitacionAfur,
		HabitacionSabrina,
		JardinEntrada,
		CasetaJardin,
		Salon,
		Pasillo,
		Bosque,


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
		InvestigableInfo(ClueID clue,string thought, SceneID scene, TextureID texture, AnimID anim, int x, int y, int w, int h) :
			ObjectInfo(scene, texture, anim, x, y, w, h),
			unlockable_(clue), thought_(thought)
		{};
		ClueID unlockable_;
		string thought_;
	};
	struct ActorInfo : ObjectInfo
	{
		ActorInfo(ActorID actor, string name, int dialogId, SceneID scene, TextureID texture, AnimID anim, int x, int y, int w, int h, bool gh = false) :
			ObjectInfo(scene, texture, anim, x, y, w, h),
			id_(actor),
			name_(name),
			dialogId_(dialogId),
            ghWorld_(gh)
		{};
		ActorInfo(ActorID actor, string name, int dialogId, SceneID scene, AnimID portraitAnim, AnimID anim, int x, int y, int w, int h, bool gh = false) :
			ObjectInfo(scene, Resources::Blank, anim, x, y, w, h),
			id_(actor),
			name_(name),
			dialogId_(dialogId),
			ghWorld_(gh),
			portraitAnim_(portraitAnim)
		{};
		ActorID id_;
		string name_;
        bool ghWorld_ = false;			//true = mundo de fantasmas
		int dialogId_ = -1;
		AnimID portraitAnim_=Resources::AnimID::noAnim;
	};

	enum ClueType
	{
		Object,
		Person,
		Place
	};
	struct ClueInfo
	{
		ClueInfo(std::string t, std::string d, std::string eT, ClueType ty, ClueID id, TextureID i) : title_(t), description_(d), eventText_(eT), type_(ty), id_(id), image_(i){};
		std::string title_;
		std::string description_;
		std::string eventText_;
		ClueType type_;
		ClueID id_;
		TextureID image_;
	};
	struct CentralClueInfo : ClueInfo
	{
		CentralClueInfo(std::string t, std::string d, ClueType ty, ClueID id, TextureID i, vector<ClueID> l, std::string ed, bool tl) : ClueInfo(t, d, "" ,ty, id, i), links_(l), eventDescription_(ed), timeline_(tl) {};
		vector<ClueID> links_;
		std::string eventDescription_;
		bool timeline_;
	};
	struct TimelineInfo
	{
		TimelineInfo(vector<ClueID> o) : order_(o) {};
		vector<ClueID> order_;
	};
	struct SceneInfo
	{
		SceneInfo(SceneID id, TextureID backgroundId, TextureID ghBackgroundId, TextureID mapIcon, Vector2D mapPos, std::vector<Vector2D>line) :
			id_(id),
			backgroundId_(backgroundId),
			ghBackgroundId_(ghBackgroundId),
			mapIcon_(mapIcon),
			mapPos_(mapPos),
			moveLine_(line)
		{}
		SceneID id_;
		TextureID backgroundId_;
		TextureID ghBackgroundId_;
		TextureID mapIcon_;
		Vector2D mapPos_;
		std::vector<Vector2D> moveLine_;
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
	static vector<TimelineInfo> timelineSolutions_;

};
