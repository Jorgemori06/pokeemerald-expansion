RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	goto_if_eq VAR_0x8004, 1, RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase::
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda::
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard:
	.string "Ay, todos los días igual…\p"
	.string "¿El qué?\n"
	.string "¿Hace falta que lo preguntes?\p"
	.string "Pensar qué hacer de comer\n"
	.string "cada día.\p"
	.string "De verdad que no es fácil pensar\n"
	.string "un menú todos los días.$"

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase:
	.string "¡Ah, hola!\n"
	.string "Esta es la casa de los PEPPER.\p"
	.string "Tengo una pregunta para ti.\n"
	.string "¿Alguna vez has cuidado de un bebé?\p"
	.string "Verás, soy padre primerizo y criar\n"
	.string "a una niña es nuevo para mí.\p"
	.string "Y tengo un problema: mi hija\n"
	.string "WALDA no se ríe mucho.\p"
	.string "Creo que se reiría si le dijera\n"
	.string "algo gracioso.\p"
	.string "¿Sabes alguna palabra o frase\n"
	.string "graciosa que me puedas decir?$"

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase:
	.string "Últimamente le digo “{STR_VAR_1}”\n"
	.string "para hacerla reír.\p"
	.string "¿Sabes alguna palabra o frase\n"
	.string "mejor que pueda funcionar?$"

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
	.string "Oh, qué maravilla.\n"
	.string "A ver, dime tu idea.$"

RustboroCity_Flat1_2F_Text_OhIsThatRight:
	.string "Ah, ¿sí?\p"
	.string "Bueno, si se te ocurre algo bueno,\n"
	.string "soy todo oídos.$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
	.string "Ah, ya veo.\n"
	.string "Bueno, vamos a probar, ¿no?$"

RustboroCity_Flat1_2F_Text_OhShesLaughing:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "¡Oh, sí! ¡Se está riendo!\n"
	.string "¡Estoy tan contento como ella!$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
	.string "Ah, ya veo.\n"
	.string "Bueno, vamos a probar, ¿no?$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Mmm… No sonríe nada.\n"
	.string "A lo mejor WALDA es muy seria…$"

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
	.string "Ah, así que no sabes ninguna.\n"
	.string "Pues tendré que pensarla yo.\p"
	.string "Mmm…\n"
	.string "¿Qué tal “{STR_VAR_1}”?\l"
	.string "A ver si funciona.$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Mmm… No sonríe nada.\n"
	.string "A lo mejor WALDA es muy seria…$"

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
	.string "Ah, así que no sabes ninguna.\n"
	.string "Seguiré intentándolo con la frase\l"
	.string "de antes.\p"
	.string "En todo caso, si se te ocurre algo\n"
	.string "bueno, no dudes en decírmelo, ¿vale?$"

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper:
	.string "¡Gracias!\p"
	.string "¡Gracias a ti, mi querida WALDA\n"
	.string "se ha reído!\p"
	.string "Aunque no lo parezca, soy uno de\n"
	.string "los mejores investigadores de\l"
	.string "la CORPORACIÓN DEVON.\p"
	.string "Así que, ¿qué tal si te devuelvo\n"
	.string "el favor?\p"
	.string "Ya sé, añadiré fondos nuevos para\n"
	.string "las CAJAS del sistema de\l"
	.string "almacenamiento del PC.\p"
	.string "En el menú de fondos, elige\n"
	.string "“AMIGOS”.\p"
	.string "Así podrás usar los fondos\n"
	.string "nuevos.$"

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
	.string "¡Es un MUÑECO de peluche POKéMON!$"

