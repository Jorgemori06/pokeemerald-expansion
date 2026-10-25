Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "Eres la primera persona que veo que\n"
	.string "maneja los POKéMON con tanta maestría.\p"
	.string "Pero te lo advierto: mi hijo es\n"
	.string "más fuerte que tú.\p"
	.string "Que sepas que hasta se ha atrevido\n"
	.string "con la LIGA POKéMON.$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "Usamos este BRAZAL FIRME para\n"
	.string "fortalecer mejor a nuestros POKéMON\l"
	.string "cuando entrenan.\p"
	.string "Como nos has ganado a todos, no sé\n"
	.string "si te hará falta, pero nos gustaría\l"
	.string "que te quedaras nuestro BRAZAL FIRME.$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "Con los combates POKéMON nos\n"
	.string "solemos poner muy apasionados.$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "Mamá es más fuerte que papá.\p"
	.string "Yo soy más fuerte que mamá.\p"
	.string "¡Y la abuela es más fuerte que yo!\p"
	.string "Pero mi hermano mayor es todavía\n"
	.string "más fuerte que la abuela.$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "No hay duda de que eres fuerte.\p"
	.string "Pero si combatieras con mi nieto,\n"
	.string "acabarías llorando de rabia.\p"
	.string "Es muchísimo más fuerte que cualquier\n"
	.string "ENTRENADOR que conozcamos.\p"
	.string "Seguro que ya está desafiando al\n"
	.string "CAMPEÓN de la LIGA POKéMON.\p"
	.string "¡Conociéndolo, puede que ya sea\n"
	.string "el CAMPEÓN!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "Seguro que mi nieto ya está\n"
	.string "desafiando al CAMPEÓN de la LIGA.\p"
	.string "¡Conociéndolo, puede que ya sea\n"
	.string "el CAMPEÓN!$"

