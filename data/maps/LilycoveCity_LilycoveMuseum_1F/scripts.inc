LilycoveCity_LilycoveMuseum_1F_MapScripts::
	.byte 0

LilycoveCity_LilycoveMuseum_1F_EventScript_Greeter::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Curator::
	lockall
	applymovement LOCALID_MUSEUM_1F_CURATOR, Common_Movement_FacePlayer
	message LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings
	waitmessage
	multichoice 20, 8, MULTI_VIEWED_PAINTINGS, TRUE
	goto_if_eq VAR_RESULT, 0, LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings
	goto_if_eq VAR_RESULT, 1, LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested
	goto_if_eq VAR_RESULT, YES, LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat, MSGBOX_SIGN
	releaseall
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe, MSGBOX_SIGN
	applymovement LOCALID_MUSEUM_1F_CURATOR, LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs
	waitmovement 0
	removeobject LOCALID_MUSEUM_1F_CURATOR
	switch VAR_FACING
	case DIR_NORTH, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth
	case DIR_WEST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest
	case DIR_EAST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth::
	lockall
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest::
	lockall
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast::
	lockall
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs:
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest:
	walk_left
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast:
	walk_right
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth:
	walk_up
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_EventScript_OldPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FantasyPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_WomanPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_LegendaryPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_GrassPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_BerryPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_EventScript_BirdSculpture::
	msgbox LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PokeBallSculpture::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_StoneTablet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SchoolKidM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NinjaBoy::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman2::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PsychicM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist2::
	lock
	faceplayer
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MUSEUM_1F_ARTIST_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FatMan::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum:
	.string "Te damos la bienvenida al MUSEO DE\n"
	.string "CALAGUA.\p"
	.string "Tómate tu tiempo para disfrutar de\n"
	.string "nuestra colección de obras de arte\l"
	.string "con POKéMON.$"

LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings:
	.string "Soy el CONSERVADOR de este MUSEO de\n"
	.string "bellas artes.\p"
	.string "Da gusto ver a alguien tan joven\n"
	.string "en nuestro MUSEO.\p"
	.string "¿Has visto ya nuestra colección\n"
	.string "de cuadros?$"

LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime:
	.string "Ah, entonces no te molesto.\n"
	.string "Tómate tu tiempo, por favor.$"

LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings:
	.string "¿Oh? Me da la impresión de que\n"
	.string "entrenas POKéMON.\p"
	.string "¿También te interesan los cuadros?$"

LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat:
	.string "Ya veo…\p"
	.string "Es un honor que nos visites aun así.$"

LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe:
	.string "¡Ah, excelente!\n"
	.string "¡Te gustan los cuadros!\p"
	.string "Entonces, ¿me acompañas, por favor?$"

LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting:
	.string "Es un cuadro muy antiguo.\n"
	.string "La pintura se cae a trozos.$"

LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery:
	.string "Es un paisaje raro, con escenas\n"
	.string "extrañas y fantásticas.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman:
	.string "Es el retrato de una mujer guapa y\n"
	.string "sonriente con un POKéMON en el regazo.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon:
	.string "Es un cuadro de un POKéMON legendario\n"
	.string "de hace mucho tiempo.\p"
	.string "El artista lo pintó de memoria,\n"
	.string "imaginándoselo.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon:
	.string "Es un cuadro de POKéMON de tipo\n"
	.string "PLANTA meciéndose con la brisa.\p"
	.string "Parece que disfrutan de la suave\n"
	.string "caricia del viento.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries:
	.string "Es un cuadro de BAYAS con muy\n"
	.string "buena pinta.\p"
	.string "¡Te puede abrir el apetito!$"

LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica:
	.string "Es una réplica de una escultura famosa.\p"
	.string "Representa a un POKéMON PÁJARO\n"
	.string "antiguo.$"

LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone:
	.string "Es una POKé BALL enorme tallada en\n"
	.string "piedra negra.\p"
	.string "Parece que se usaba en las fiestas\n"
	.string "de antaño.$"

LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText:
	.string "Es una gran tabla de piedra con\n"
	.string "POKéMON grabados y un texto denso\l"
	.string "de letras diminutas en una lengua\l"
	.string "antigua e ilegible.$"

LilycoveCity_LilycoveMuseum_1F_Text_WorksOfMagnificence:
	.string "Mmm…\n"
	.string "Qué obras tan magníficas…$"

LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts:
	.string "Combatir con POKéMON es divertido,\n"
	.string "eso te lo reconozco.\p"
	.string "Pero no hay que olvidar el amor por\n"
	.string "las bellas artes.$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration:
	.string "Este MUSEO DE ARTE… Se pueden ver\n"
	.string "muchos cuadros fantásticos.\p"
	.string "Y el CONSERVADOR es una persona\n"
	.string "maravillosa.\p"
	.string "Para los artistas como yo, este MUSEO\n"
	.string "es una inspiración.$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty:
	.string "¡Qué guapa es esta señora!\n"
	.string "¡Se parece a mamá!$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable:
	.string "¡Este POKéMON es adorable!\n"
	.string "¡Como nuestro pequeño!$"

LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings:
	.string "Me dijeron que a este MUSEO DE ARTE\n"
	.string "habían llegado cuadros nuevos.\p"
	.string "Así que, claro, he venido corriendo.\p"
	.string "¿Los cuadros nuevos están en la\n"
	.string "segunda planta?$"

LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful:
	.string "Últimamente el CONSERVADOR está\n"
	.string "más contento que de costumbre.\p"
	.string "Seguro que le ha pasado algo bueno.\n"
	.string "Seguro.$"

LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings:
	.string "Quiero ver aquí muchos cuadros\n"
	.string "geniales y aprender de ellos.\p"
	.string "Sueño con que algún día expongan\n"
	.string "aquí una obra mía.$"

LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination:
	.string "El MUSEO DE ARTE se ha convertido en\n"
	.string "un destino turístico de primera.\p"
	.string "¡Es genial para CALAGUA…!\n"
	.string "¡No, para toda la región de HOENN!\p"
	.string "He oído que todos los cuadros de\n"
	.string "arriba los consiguió una sola persona.$"

