SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_PARTS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	removeobject LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "¿Sí? Si buscas a BABOR, ese\n"
	.string "soy yo.\p"
	.string "¡Ah! Esas deben de ser las piezas\n"
	.string "que le pedí al SR. PEÑA de DEVON.\p"
	.string "¡Gracias! ¡Estupendo! Ya podemos\n"
	.string "prepararnos para la expedición.$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "¡Jejeje, alto ahí!\n"
	.string "¡Esas piezas nos las llevamos!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "CAPITÁN BABOR: ¿Q-qué?\n"
	.string "¿Quiénes sois vosotros?$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "¡Somos el EQUIPO AQUA!\p"
	.string "¡Nuestro JEFE quiere esas piezas!\n"
	.string "¡Cierra el pico y suéltalas!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "¡Aaaaah!\n"
	.string "¡Me ha ganado un renacuajo!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "Ay, madre, qué desastre…\n"
	.string "El JEFE se va a poner furioso…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "¡Bah, llorica!\n"
	.string "¡Deja que me encargue yo!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "¡¿Qué?!\n"
	.string "¡Yo también he perdido!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "¿Y ahora qué? ¡Si no conseguimos las\n"
	.string "piezas, nos la vamos a cargar!\p"
	.string "¡Arrg, no contaba con que un\n"
	.string "renacuajo se metiera en medio!$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "Vengo a ver por qué tardáis tanto\n"
	.string "en robar unas piezas, ¿y resulta que\l"
	.string "no podéis con una simple criatura?$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "¡Somos el EQUIPO AQUA\n"
	.string "y amamos el mar!\p"
	.string "¡Y yo soy el líder del EQUIPO AQUA,\n"
	.string "AQUILES!\p"
	.string "¿Por qué te metes en nuestros\n"
	.string "asuntos?\p"
	.string "… ¡No! ¡No puede ser!\n"
	.string "¿Eres del EQUIPO MAGMA?\p"
	.string "Espera, no puede ser.\n"
	.string "No llevas la ropa adecuada.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "POKéMON, personas… Toda la vida\n"
	.string "depende del mar.\p"
	.string "Por eso, el EQUIPO AQUA se dedica\n"
	.string "a expandir el mar.\p"
	.string "¿No estás de acuerdo? Lo que hacemos\n"
	.string "es una empresa magnífica.\p"
	.string "Ah, bueno…\n"
	.string "Aún eres demasiado joven para\l"
	.string "entender nuestro noble objetivo.\p"
	.string "Pero te lo advierto: ni se te ocurra\n"
	.string "volver a meterte en nuestros planes.\p"
	.string "¡Lo pagarás muy caro!\p"
	.string "¡Que no se te olvide!$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "CAPITÁN BABOR: Tú eres…\n"
	.string "Ah, vale, eres {PLAYER}{KUN}…\p"
	.string "¡En fin, qué momento más tenso!\n"
	.string "¡Gracias por salvarnos!\p"
	.string "¡Ah, sí! ¡Casi se me olvida que\n"
	.string "me has traído las piezas de DEVON!$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "CAPITÁN BABOR: ¡Huy!\n"
	.string "¡No hay tiempo que perder!\p"
	.string "Tenemos que salir muy pronto en\n"
	.string "nuestra expedición al fondo del mar.\p"
	.string "Gracias otra vez, ¡pero ahora\n"
	.string "tengo que irme!\p"
	.string "Puedes dar una vuelta y ver\n"
	.string "nuestras instalaciones, si quieres.$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "He visto aquí la maqueta de un barco.\p"
	.string "Me ha recordado al BARCO ABANDONADO\n"
	.string "que hay cerca de PUEBLO AZULIZA…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "¡Ni se te ocurra correr dentro\n"
	.string "del MUSEO!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "¡Hala, el submarino es genial!\n"
	.string "¡Quiero dar una vuelta en él!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "“MUESTRA DE AGUA 1”, dice\n"
	.string "la etiqueta.\p"
	.string "Todo el mar está conectado, pero el\n"
	.string "agua parece distinta en cada zona.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "“MUESTRA DE AGUA 2”, dice\n"
	.string "la etiqueta.\p"
	.string "¿También cambia lo salada que es el\n"
	.string "agua según la zona?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "Una pelota de goma se hincha\n"
	.string "y se encoge.\p"
	.string "“En el mar, el propio peso del agua\n"
	.string "ejerce presión.\p"
	.string "”En aguas poco profundas, la presión\n"
	.string "no es muy alta.\p"
	.string "”Pero a grandes profundidades puede\n"
	.string "llegar a decenas de miles de\l"
	.string "toneladas sobre una zona pequeña”.$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "“MAQUETA DE LA REGIÓN DE HOENN”\p"
	.string "Es un diorama en miniatura de la\n"
	.string "región de HOENN.\p"
	.string "¿Dónde estará VILLA RAÍZ?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "Una exposición sobre las corrientes.\p"
	.string "“Cerca del fondo, el agua se mueve\n"
	.string "por diferencias de factores como\l"
	.string "la temperatura o la salinidad”.$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "Una exposición sobre las corrientes.\p"
	.string "“Cerca de la superficie, el viento\n"
	.string "mueve el agua y forma corrientes”.$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "“EL FERRY M.S. MAREA\p"
	.string "”Maqueta a escala del barco que se\n"
	.string "construye en el ASTILLERO DE BABOR”.$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "“SUBMARINO EXPLORADOR 1\p"
	.string "”Réplica del submarino de alto\n"
	.string "rendimiento para explorar el fondo”.$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "“CÁPSULA SUMERGIBLE\p"
	.string "”Réplica de una cápsula compacta y\n"
	.string "sin tripulación para explorar el fondo”.$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "“S.S. ANNE\p"
	.string "”Réplica del lujoso transatlántico\n"
	.string "que da la vuelta al mundo”.$"
