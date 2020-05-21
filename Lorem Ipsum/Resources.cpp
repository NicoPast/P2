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
		'R', "\u00c9"
	},
	{
		'i', "\u00ed"
	},
	{
		'i', "\u00cd"
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
			{ NotificationIcon, "../assets/images/notificationIcon.png"},
			{OptionBars,"../assets/images/optionsBars.png"},
			{PhoneOn, "../assets/images/Phone On.png"},
			{PhoneOff, "../assets/images/Phone Off.png"},
			{MacarenaIdle, "../assets/images/MacarenaCatIdle.png"},
			{femur, "../assets/images/femur.png"},
			{clueEvent, "../assets/images/PolaroidEvento.png"},
			{DialogBox, "../assets/images/DialogBox.png"},
			{CatIdle, "../assets/images/IdleCat.png"},
			{VerticalUIPanel, "../assets/images/VerticalUIPanel.png"},
			{VerticalUIPanel2, "../assets/images/VerticalUIPanel2.png"},
			{HorizontalUIPanel, "../assets/images/HorizontalUIPanel.png"},
			{HorizontalUIPanel2, "../assets/images/HorizontalUIPanel2.png"},
			{MessageUIPanel, "../assets/images/messageUIPanel.png"},
			{LazaroPortrait, "../assets/images/PortraitLazaro.png"},
			{MacarenaPortrait, "../assets/images/PortraitMacarena.png"},
			{CatPortrait, "../assets/images/PortraitGato.png"},
			{BGEntradaOficinaSDL, "../assets/images/OficinaEntradaSDL.png"},
			{BGJardin, "../assets/images/jardinBG1.png"},
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
			{Escritorio, "../assets/images/Escritorio.png"},
			{VentanaOficina3, "../assets/images/VentanaOficina3.png"},
			{VentanaOficina2, "../assets/images/VentanaOficina2.png"},
			{VentanaOficina1, "../assets/images/VentanaOficina1.png"},
			{VentanaOficina0, "../assets/images/VentanaOficina.png"},
			{officeFan, "../assets/images/officeFan.png"},
			{MaridoCapaSpriteSheet, "../assets/images/MaridoCapaSpriteSheet.png"},
			{BackgroundDeathWorld, "../assets/images/backgroundGhostWorld.png"},
			{GhostSDL, "../assets/images/SDLGhost.png"},
			{MainMenuSpriteSheet, "../assets/images/MenuBGAnim.png"},
			{DespachoCapo, "../assets/images/DespachoCapo.png"},
			{AfurPortrait, "../assets/images/PortraitAfur.png"},
			{Afur, "../assets/images/Afur.png"},
			{UrsulaIdle, "../assets/images/UrsulaIdle.png"},
			{CarlosPortrait, "../assets/images/PortraitCarlos.png"},
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
	{Humo1Anim, Humo1SpriteSheet, 5,5,0,21,1000,true},
	{OfficeWindowAnim, VentanaOficina0, 4,4, 0,15, 1200, true},
	{officeFanAnim, officeFan, 3,4, 0,11, 120, true},
	{MaridoCapaKnifeAnim, MaridoCapaSpriteSheet, 2, 21, 0, 25, 84, true},
	{MaridoCapaRelaxAnim, MaridoCapaSpriteSheet, 2, 21, 26, 37, 200, true},
	{CatPortraitAnim, Resources::TextureID::CatPortrait, 5,4, 0, 19, 200, true},
	{MacarenaPortraitAnim, Resources::TextureID::MacarenaPortrait, 5, 5, 0, 21, 200, true},
	{SDLPortraitAnim, Resources::TextureID::LazaroPortrait, 2, 1, 0, 1, 1200, false},
	{SDLGhostAnim, Resources::TextureID::GhostSDL, 2, 4, 0, 5, 175, true},
	{CapaIdleAnim, Resources::TextureID::UrsulaIdle, 3, 7, 0, 20, 125, true}


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
	 Resources::TextureID::SillaDespachoInteractable},

	{"Papeles desordenados",
	 "No es que yo sea la persona m\u00e1s limpia, pero esto no ha sido fruto de mi desorden. Adem\u00e1s, parece un desorden intencionado, como si alguien estuviese buscando algo entre mis cosas.",
	 "una persona salvaje",
	 Resources::ClueType::Person,
	 Resources::ClueID::Tut_PapelesDesordenados,
	 Resources::TextureID::femur},

	 //-----------------------------------------
	 //------------ Caso Principal -------------
	 //-----------------------------------------

	 //--------------- Objetos -----------------

	 {"Contrato de confidencialidad",
	 "Contrato est" + tildes_['a'] + "ndar que te hace firmar la familia Polo cuando trabajas con ellos. El hecho de tener que firmar algo as" + tildes_['i'] + " habla por s" + tildes_['i'] + " solo, pero la verdad es que pagan bien, as" + tildes_['i'] + " que es un buen precio por mi silencio.",
	 "el contrato de confidencialidad",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_Contrato,
	 Resources::TextureID::femur},

	 {"Navaja de Carlos Castro",
	 "Navaja mariposa muy bonita, pertenece a Carlos. De todos los objetos puntiagudos de los que habla, este parece ser el m" + tildes_['a'] + "s preciado de todos. Y tambi" + tildes_['e'] + "n el m" + tildes_['a'] + "s peligroso.",
	 "la navaja de Carlos",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_NavajaCarlos,
	 Resources::TextureID::femur}, 
	
	 {"Piedra con musgo del bosque",
	 "Piedra con una forma un tanto afilada que tiene pinta de ser del bosque. No es especialmente bonita. Estaba en la habitaci"+ tildes_['o']+"n de Carlos y "+ tildes_['U']+"rsula.",
	 "la piedra del bosque",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PiedraMusgo,
	 Resources::TextureID::femur},
	
	 {"Zapatos con barro",
	 "Unos pares de zapatos pertenecientes a Afur. Tiene pequeños restos de barro, lo cual me resulta extraño debido a lo inmaculada que es esta familia en cuanto a la est" + tildes_['e'] + "tica.",
	 "los zapatos de Afur",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_ZapatosBarro,
	 Resources::TextureID::femur},

	 {"Bala y casquillo",
	 "Una bala y un casquillo de bala que estaba en el bosque. La bala no tiene sangre. Tiene pinta de que pertenecen al mismo disparo. Que est" + tildes_['e'] + " en el lugar donde encontraron a Sabrina enterrada da que pensar, aunque por aqu" + tildes_['i'] + " pasan cazadores.",
	 "la bala y el casquillo",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_BalaCasquillo,
	 Resources::TextureID::femur},

	 {"Herramientas de la caseta",
	 "Palas, tijeras de podar, rastrillos… Cualquiera de estos elementos podr" + tildes_['i'] + "a ser un arma homicida perfecta.",
	 "las herramientas de jardiner" + tildes_['i'] + "a",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_HerramientasCaseta,
	 Resources::TextureID::femur},

	 {"Pa" + tildes_['ñ'] + "uelo rojo",
	 "Es un pa" + tildes_['ñ'] + "uelo rojo de una tela muy resistente y que tiene bordado el nombre de Carlos Castro. Estaba rodeando la empu" + tildes_['ñ'] + "adura de la pistola. ",
	 "la bala y el casquillo",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PanueloRojo,
	 Resources::TextureID::femur},

	 {"Pistola con silenciador",
	 "Es una pistola bastante pesada pero manejable. Se encontraba en el sal" + tildes_['o'] + "n de la casa, y la bala y el casquillo parecen encajar con este modelo de pistola.",
	 "la bala y el casquillo",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PistolaSilenciador,
	 Resources::TextureID::femur},

	 {"Papeles de la herencia familiar",
	 "Estos papeles escritos por Marcelina Polo evidencian que quien debe tener el poder en los negocios es Ernesto, aunque quien mejor lo llevar" + tildes_['i'] + "a ser" + tildes_['i'] + "a " + tildes_['U'] + "rsula. Se lee la frase “Esto es lo mejor para ti, hija. No quer" + tildes_['i'] + "a que llevaras una vida como la m" + tildes_['i'] + "a”. Parece claro qui" + tildes_['e'] + "n era la favorita.",
	 "los papeles de la herencia familiar",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_PapelesHerencia,
	 Resources::TextureID::femur},

	 {"Contrato de confidencialidad de Gus",
	 "Es un contrato exactamente igual que el m" + tildes_['i'] + "o, pero con el nombre de “Mario L" + tildes_['a'] + "zaro”, pero su rol ser" + tildes_['a'] + " de cuidador . Hay una foto de Gus en " + tildes_['e'] + "l. Siempre fue muy fotog" + tildes_['e'] + "nico.",
	 "el contrato de Gus",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_ContratoGus,
	 Resources::TextureID::femur},

	 {"Llave",
	 "Llave de una habitaci" + tildes_['o'] + "n que estaba entre las cosas de Ernesto. Hay algunas habitaciones cerradas por la casa, as" + tildes_['i'] + " que estar" + tildes_['i'] + "a bien probar qu" + tildes_['e'] + " es lo que abre. Me hace gracia lo clich" + tildes_['e'] + " que es esto de encontrar una llave.",
	 "la llave",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_Llave,
	 Resources::TextureID::femur},

	 { "Fotograf" + tildes_['i'] + "a",
	 "A m" + tildes_['a'] + "s se relaciona este caso con Gus, m" + tildes_['a'] + "s nervioso estoy. En esta foto se ven a Gus, Ernesto y Sabrina en la puerta de la casa. Se les ve muy...felices.",
	 "la fotograf" + tildes_['i'] + "a",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_Foto,
	 Resources::TextureID::femur },

	 { "Orden de asesinato",
	 "Es el trozo de papel m" + tildes_['a'] + "s fr" + tildes_['i'] + "volo que he le" + tildes_['i'] + "do en mi vida. Se me para el coraz" + tildes_['o'] + "n cada vez que lo miro. “" + tildes_['O'] + "rdenes de madre, acaba con el cuidador”." + tildes_['¿'] + "Por qu" + tildes_['e'] + " tuviste que estar metido en todo esto, Gus ? ",
	 "la orden de asesinato",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_OrdenAsesinato,
	 Resources::TextureID::femur },

	 { "Llave de Ernesto",
	 " La jardinera me ha dicho d" + tildes_['o'] + "nde estaba " + tildes_['e'] + "sta llave, y pese a que ya todo me da igual, no puedo dejar esto a medias. Necesito saber qu" + tildes_['e'] + " me depara detr" + tildes_['a'] + "s de la puerta que abra. Ernesto lo sabr" + tildes_['a'] + ".",
	 "la llave de Ernesto",
	 Resources::ClueType::Object,
	 Resources::ClueID::Prin_LlaveErnesto,
	 Resources::TextureID::femur },

	 //------------- Personajes ----------------

	 {"Ernesto Polo",
	 "Es el cabecilla de la familia Polo, todos le conocen. Es el que tiene m"+tildes_['a']+"s poder, aunque no tiene mucha mano con los negocios. Parece un tanto ingenuo. Es muy tosco y amenazante, pero debe verse muy afectado por la muerte de su hija como para pedirme ayuda. ",
	 "Ernesto Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_ErnestoPolo,
	 Resources::TextureID::femur},

	 {"Sabrina  Polo",
	 "Era la hija de Ernesto. Seg" + tildes_['u'] + "n se dice por ah" + tildes_['i'] + ", era jovial y simp" + tildes_['a'] + "tica, seguramente la m" + tildes_['a'] + "s honrada todos, lejos del car" + tildes_['a'] + "cter serio y mezquino de la mayor" + tildes_['i'] + "a de la familia Polo. Tras su muerte, el ambiente familiar es incluso m" + tildes_['a'] + "s tenso y con cierta hostilidad.",
	 "Sabrina  Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_SabrinaPolo,
	 Resources::TextureID::femur},

	 { "" + tildes_['U'] + "rsula Polo",
	 "Es la hermana de Ernesto. Tiene pinta de ser la que maneja el cotarro de verdad, pese a que su hermano sea quien firma los papeles. Rezuma poder, o ansias del mismo.",
	 "" + tildes_['U'] + "rsula Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_UrsulaPolo,
	 Resources::TextureID::femur },

	 { "Carlos Castro",
	 "Es el marido de " + tildes_['U'] + "rsula. Se trata de un hombre bastante extravagante, me desconcierta su forma de ser. No sab" + tildes_['i'] + "a que una persona podr" + tildes_['i'] + "a estar tant" + tildes_['i'] + "simo tiempo hablando sobre objetos puntiagudos.",
	 "Carlos Castro",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_CarlosCastro,
	 Resources::TextureID::femur },

	 { "Afur Polo",
	 "Es el hijo de " + tildes_['U'] + "rsula y Carlos. Tiene un nombre muy peculiar, siendo esto de la poca informaci" + tildes_['o'] + "n que tengo sobre " + tildes_['e'] + "l, aparte de que no es muy hablador y parece tener un car" + tildes_['a'] + "cter d" + tildes_['e'] + "bil. Los padres son pijos hasta para el nombre del niño.",
	 "Afur Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_AfurPolo,
	 Resources::TextureID::femur },

	 { "Jardinera",
	 "Es el fantasma de una jardinera que debi" + tildes_['o'] + " trabajar aqu" + tildes_['i'] + " hace tiempo. Es muy misteriosa, lo cual me desconcierta. M" + tildes_['a'] + "s de lo que te puede desconcertar un fantasma como concepto, me refiero.",
	 "la jardinera",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_Jardinera,
	 Resources::TextureID::femur },

	 { "Marcelina Polo",
	 "Madre de Ernesto y " + tildes_['U'] + "rsula. Era quien mandaba antes de Ernesto, y le pas" + tildes_['o'] + " el testigo cuando lleg" + tildes_['o'] + " a la vejez. Pese a haber fallecido, sigue teniendo mucha presencia en toda la casa. Parece una mujer muy dura, pero seguramente fuese una coraza generada por el cargo tan estresante que ten" + tildes_['i'] + "a en la familia.",
	 "Marcelina Polo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_MarcelinaPolo,
	 Resources::TextureID::femur },

	 { "Mario L" + tildes_['a'] + "zaro (Gustavo)",
	 "No.. No me lo puedo creer. No pens" + tildes_['e'] + " que fuera a volver a ver a Gustavo m" + tildes_['a'] + "s que en mis fotos y mis pensamientos m" + tildes_['a'] + "s dolorosos. Era el mejor polic" + tildes_['i'] + "a de todos, hac" + tildes_['i'] + "a de m" + tildes_['i'] + " la persona que siempre quise ser, y que sin " + tildes_['e'] + "l, se ha desvanecido. No s" + tildes_['e'] + " como acab" + tildes_['o'] + " aqu" + tildes_['i'] + ", pero parece ser que cuidaba de alguien de la familia.",
	 "Gustavo",
	 Resources::ClueType::Person,
	 Resources::ClueID::Prin_Gustavo,
	 Resources::TextureID::femur },

	 //--------------- Lugares -----------------

	 { "Jard" + tildes_['i'] + "n de la entrada a la mansi" + tildes_['o'] + "n",
	  "Para ser la entrada a una mansi" + tildes_['o'] + "n, me parece que est" + tildes_['a'] + " bastante descuidada desde hace mucho",
	  "el jard" + tildes_['i'] + "n",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_Jardin,
	  Resources::TextureID::femur }, 
	 
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
	  "Esta habitaci" + tildes_['o'] + "n es menos personal, parece m" + tildes_['a'] + "s algo heredado que el resto de habitaciones de la casa. El enorme cuadro parece ser que es de la madre de Ernesto y " + tildes_['U'] + "rsula. Puede que es porque la quisiera mucho, o bien porque da miedo incluso estando muerta. Me da la sensaci" + tildes_['o'] + "n que es lo segundo.",
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
	  "Es una habitaci" + tildes_['o'] + "n normal y corriente, lo cual es llamativo sabiendo d" + tildes_['o'] + "nde vive y qui" + tildes_['e'] + "nes son su familia.Parece ser que Ernesto ha puesto muchos esfuerzos en que nadie est" + tildes_['e'] + " dentro de estas cuatro paredes.O bien est" + tildes_['a'] + " dolido, o bien, no quiere que vea algo.",
	  "la habitaci" + tildes_['o'] + "n de Sabrina",
	  Resources::ClueType::Place,
	  Resources::ClueID::Prin_HabSabrina,
	  Resources::TextureID::femur }


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
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "C" + tildes_['o'] + "mo muri" + tildes_['o'] + " la hija del capo?",
			"La muerte de Sabrina es un misterio en el que creo que puede caber cualquier perfil de esta familia. Necesito descubrir qui" + tildes_['e'] + "n la mat" + tildes_['o'] + ", c" + tildes_['o'] + "mo lo hizo y d" + tildes_['o'] + "nde fue para poder acusar con fundamento. No es que me importe mucho, pero me paga bastante bien.",
			Resources::ClueType::Person,
			Resources::ClueID::Prin_Cent_MuerteHija,
			Resources::TextureID::femur,
			{
				Resources::ClueID::Prin_UrsulaPolo,
				Resources::ClueID::Prin_PanueloRojo,
				Resources::ClueID::Prin_HabSabrina
			},
			"A Sabrina la asesinó @ usando ~ en $ .",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "C" + tildes_['o'] + "mo muri" + tildes_['o'] + " la jardinera?",
			"No se si esta mujer tiene algo que ver con todo esto, pero est" + tildes_['a'] + " claro que su fantasma va a estar en esta caseta porque le encante este sitio. Me desconcierta su presencia, o, m" + tildes_['a'] + "s bien, su no presencia.",
			Resources::ClueType::Person,
			Resources::ClueID::Prin_Cent_MuerteJardinera,
			Resources::TextureID::femur,
			{
				Resources::ClueID::Prin_ErnestoPolo,
				Resources::ClueID::Prin_NavajaCarlos,
				Resources::ClueID::Prin_CasetaJardin
			},
			"A la jardinera la asesinó @ usando ~ en $ .",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "Por qu" + tildes_['e'] + " discutieron Afur y Sabrina?",
			"Parece ser que en alg" + tildes_['u'] + "n momento antes de morir, Afur y Sabrina tuvieron una importante discusi" + tildes_['o'] + "n que le atormentaba. Debo descubrir el motivo si quiero saber qu" + tildes_['e'] + " pas" + tildes_['o'] + " con Sabrina.",
			Resources::ClueType::Object,
			Resources::ClueID::Prin_Cent_Discusion,
			Resources::TextureID::femur,
			{
				Resources::ClueID::Prin_OrdenAsesinato
			},
			"Afur y Sabrina discutieron por ~ .",
			true),

		Resources::CentralClueInfo(
			"" + tildes_['¿'] + "Qui" + tildes_['e'] + "n mat"+ tildes_['o']+" a Gus?",
			"No pens" + tildes_['e'] + " que todas estas muertes acabar" + tildes_['i'] + "an desembocando en la " + tildes_['u'] + "nica muerte que me importa de verdad, m" + tildes_['a'] + "s que la m" + tildes_['i'] + "a propia. Cari" + tildes_['ñ'] + "o...no s" + tildes_['e'] + " qu" + tildes_['e'] + " motivos ten" + tildes_['i'] + "as para meterte aqu" + tildes_['i'] + " dentro, pero lo que necesito saber qui" + tildes_['e'] + "n te hizo esto y resolver lo que no me deja dormir por las noches. ",
			Resources::ClueType::Person,
			Resources::ClueID::Prin_Cent_MuerteGus,
			Resources::TextureID::femur,
			{
				Resources::ClueID::Prin_Jardinera
			},
			"A Gustavo lo asesinó @ .",
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
	ActorInfo(Resources::ActorID::SDL, "L" + tildes_['a'] + "zaro", -1,				Resources::SceneID::EntradaDespacho,	Resources::AnimID::SDLPortraitAnim,				Resources::noAnim,						-1000,-250,30,30),
	ActorInfo(Resources::ActorID::MacarenaMartinez, "Macarena Mart\u00EDnez", -1,	Resources::SceneID::EntradaDespacho,	Resources::AnimID::MacarenaPortraitAnim,		Resources::MacarenaCatIdleAnim,			720, 340, 80, 264),
	ActorInfo(Resources::ActorID::Pelusa, "Black Cat", -1,							Resources::SceneID::EntradaDespacho,	Resources::AnimID::CatPortraitAnim,				Resources::CatIdleAnim,					110,680, 28,28),
	ActorInfo(Resources::ActorID::Barman, "Fernando el Barman", -1,					Resources::SceneID::Casa_Del_Profesor,	Resources::TextureID::Blank,					Resources::noAnim,						110,30, 30,30),
	ActorInfo(Resources::ActorID::CarlosI, "Carlos Castro", -1,						Resources::SceneID::HabitacionCarlos,	Resources::TextureID::CarlosPortrait,			Resources::AnimID::MaridoCapaKnifeAnim, 360, 300, 184, 344),
	ActorInfo(Resources::ActorID::Capo, "Ernesto Polo", -1,							Resources::SceneID::DespachoPolo,		Resources::TextureID::MacarenaPortrait,			Resources::AnimID::MacarenaCatIdleAnim,	720,360,80,264),
	ActorInfo(Resources::ActorID::Capa, ""+ tildes_['U'] +"rsula Polo", -1,			Resources::SceneID::HabitacionCarlos,	Resources::TextureID::MacarenaPortrait,			Resources::CapaIdleAnim,				120,340,80,264),
	ActorInfo(Resources::ActorID::CarlosII, "Afur Polo", -1,						Resources::SceneID::DespachoPolo,		Resources::TextureID::AfurPortrait,				Resources::MacarenaCatIdleAnim,			200,340,80,264),
	ActorInfo(Resources::ActorID::F_Hija, "Sabrina Polo", -1,						Resources::SceneID::DespachoPolo,		Resources::TextureID::MacarenaPortrait,			Resources::MacarenaCatIdleAnim,			280,340,80,264, true),
	ActorInfo(Resources::ActorID::F_MamaCapo, "Marcelina Polo", -1,					Resources::SceneID::DespachoPolo,		Resources::TextureID::MacarenaPortrait,			Resources::MacarenaCatIdleAnim,			544,340,80,264, true),
	ActorInfo(Resources::ActorID::F_Novio, "Gus", -1,								Resources::SceneID::DespachoPolo,		Resources::TextureID::MacarenaPortrait,			Resources::MacarenaCatIdleAnim,			624,340,80,264, true),
	ActorInfo(Resources::ActorID::F_Afur, "Fantasma de Afur Polo", -1,				Resources::SceneID::DespachoPolo,		Resources::TextureID::MacarenaPortrait,			Resources::MacarenaCatIdleAnim,			750,340,80,264, true),
	ActorInfo(Resources::ActorID::F_AntiguoTrabajador, "Jardinera sin nombre", -1,	Resources::SceneID::DespachoPolo,		Resources::TextureID::MacarenaPortrait,			Resources::MacarenaCatIdleAnim,			704,340,80,264, true),

	ActorInfo(Resources::ActorID::PhoneCall, "...", -1,								Resources::SceneID::Casa_Del_Profesor,	Resources::TextureID::MacarenaPortrait,			Resources::noAnim,						0,0,0,0)
};

vector<Resources::DoorInfo> Resources::doors_={
	DoorInfo(Resources::DoorID::pRecepcionDespacho, Resources::SceneID::Despacho, Resources::SceneID::EntradaDespacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 860, 228, 41*4, 79*4,  10,333),
	DoorInfo(Resources::DoorID::pDespachoRecpecion, Resources::SceneID::EntradaDespacho, Resources::SceneID::Despacho, Resources::TextureID::Blank, Resources::AnimID::noAnim, 16 * 4,72 * 4 ,  44 * 2,200 * 2 , 840, 120),
	DoorInfo(Resources::DoorID::pDespachoPasillo, Resources::SceneID::Pasillo, Resources::SceneID::DespachoPolo, Resources::TextureID::Blank, Resources::AnimID::noAnim,1312,72*3 , 172,128 , 75, 280),
};

vector<Resources::InvestigableInfo> Resources::investigables_{
	InvestigableInfo(Resources::ClueID::Tut_MigajasComida, "No recuerdo haberme comido esto.",Resources::SceneID::Despacho, Resources::TextureID::ChineseFoodInteractable, Resources::AnimID::noAnim, 245, 675, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_PapelesDesordenados, "No parece que les interesara el dinero que hab\u00eda por aqu\u00ed. *Sigh* Tampoco habr\u00edan encontrado mucho",Resources::SceneID::Despacho, Resources::TextureID::PapelesDesordenadosInteractable, Resources::AnimID::noAnim, 350, 465, 30, 30),
	InvestigableInfo(Resources::ClueID::Tut_SillaRota, ""+tildes_['¿']+"Por qu\u00e9 habr\u00e1n ara"+tildes_['ñ']+"ado mis muebles? No son muy civilizados...",Resources::SceneID::Despacho, Resources::TextureID::SillaDespachoInteractable, Resources::AnimID::noAnim, 960, 420, 30, 30),
};

vector<Resources::SceneInfo> Resources::scenes_
{
	SceneInfo(Resources::SceneID::EntradaDespacho, Resources::TextureID::BGEntradaOficinaSDL,Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::Blank, {30,30}, {{136,350}, {700,350},{840,250}}),
	SceneInfo(Resources::SceneID::Despacho, Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::Blank, {0, 0 }, {{0,0}}),
	SceneInfo(Resources::SceneID::calleProfesor, Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::Blank,{30,30 }, {{0,0}}),
	SceneInfo(Resources::SceneID::Casa_Del_Profesor, Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::Blank, {100,180}, {{0,0}}),
	SceneInfo(Resources::SceneID::DespachoPolo,Resources::TextureID::DespachoCapo, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,100},{{0,0}}),
	SceneInfo(Resources::SceneID::HabitacionCarlos,Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{200,100},{{0,0}}),
	SceneInfo(Resources::SceneID::HabitacionErnesto,Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{300,100},{{0,0}}),
	SceneInfo(Resources::SceneID::HabitacionAfur,Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{400,100},{{0,0}}),
	SceneInfo(Resources::SceneID::HabitacionSabrina,Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{500,100},{{0,0}}),
	SceneInfo(Resources::SceneID::JardinEntrada,Resources::TextureID::BGJardin, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,200},{{0,0}}),
	SceneInfo(Resources::SceneID::CasetaJardin,Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,300},{{0,0}}),
	SceneInfo(Resources::SceneID::Salon,Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,400},{{0,0}}),
	SceneInfo(Resources::SceneID::Pasillo,Resources::TextureID::Background, Resources::TextureID::BackgroundDeathWorld, Resources::TextureID::AddIcon,{150,400},{{0,0}}),

};


/*----------------------------------------------------*/


vector<Resources::MusicInfo> Resources::musics_ {
//
		{ MTint, "../assets/sound/MainThemeIntro.wav" } ,//
		{ MTloo, "../assets/sound/MainThemeLoop.wav" }, //
		{ GhostDraft, "../assets/sound/GhostTheme3NoDrums.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Wall_Hit, "../assets/sound/wall_hit.wav" }, //
		{ Paddle_Hit, "../assets/sound/paddle_hit.wav" }, //
		{ Buzz, "../assets/sound/buzzCut.wav" }, //
		{ Bip, "../assets/sound/bip.wav" } //
};

