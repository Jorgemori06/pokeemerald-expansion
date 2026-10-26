LilycoveCity_CoveLilyMotel_1F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_1F_EventScript_MotelOwner::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_BlockingTV::
	lockall
	playse SE_PIN
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn
	waitmovement 0
	release
	end

LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer:
	walk_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn:
	face_down
	walk_down
	face_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot:
	.string "Mm, ¿así que doblaron los clientes\n"
	.string "usando POKéMON como atracción?\p"
	.string "Mm, a lo mejor debería poner un\n"
	.string "POKéMON mono de mascota del motel.\p"
	.string "¿Vendrán así más clientes?$"

LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua:
	.string "¡Ay, perdona, perdona!\n"
	.string "¡Estaba muy metido viendo la tele!\p"
	.string "Desde que llegó el EQUIPO AQUA a la\n"
	.string "ciudad, los turistas no vienen.$"

LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV:
	.string "¡Eh, quita de en medio!\n"
	.string "¡Que no veo la tele!$"

LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem:
	.string "¡Increíble! ¿Me dices que un POKéMON\n"
	.string "encontró un objeto perdido?\p"
	.string "Eso sí que es algo. Si tuviéramos un\n"
	.string "POKéMON tan listo…\p"
	.string "Podríamos encontrar todo lo que\n"
	.string "perdieran los clientes…$"

LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted:
	.string "¡Ay, perdona, perdona!\n"
	.string "¡Estaba muy metido viendo la tele!\p"
	.string "He oído que alguien ha desmantelado\n"
	.string "la GUARIDA del EQUIPO AQUA.\p"
	.string "Gracias a eso, acaba de reservar un\n"
	.string "grupo grande.\p"
	.string "Era una empresa que se llama… Eh…\n"
	.string "GAME no sé qué…$"

LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar:
	.string "¡Increíble! ¿Un POKéMON que cuidaba la\n"
	.string "casa atrapó a un ladrón?\p"
	.string "Eso sí que es algo. Si tuviéramos un\n"
	.string "POKéMON fuerte de guardia…\p"
	.string "Podríamos dar más seguridad a los\n"
	.string "clientes.$"

LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner:
	.string "¡Ay, perdona, perdona!\n"
	.string "¡Estaba muy metido viendo la tele!\p"
	.string "Ah, sí. Hace un rato llegó un grupo\n"
	.string "grande de clientes.\p"
	.string "Se registraron como GAME FREAK, así\n"
	.string "que supongo que hacen juegos.\p"
	.string "¡Ay, tengo que ponerme con su cena!$"

