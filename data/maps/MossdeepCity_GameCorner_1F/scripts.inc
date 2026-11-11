MossdeepCity_GameCorner_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.2byte 0

MossdeepCity_GameCorner_1F_OnFrame:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_InfoMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_OldMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


@ Everything below is leftover from RS
@ The house that was here in RS was moved to Sootopolis and replaced by the Game Corner
@ The text below is unused and duplicated in its replacement in Sootopolis City
@ And the BG Door event was moved inaccessibly into a wall

RS_MysteryEventsHouse_EventScript_Door::
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting:
	.string "When I was young, I traveled the world\n"
	.string "as a POKéMON TRAINER.\p"
	.string "Now that I've become an old buzzard,\n"
	.string "my only amusement is watching young\l"
	.string "TRAINERS battle.$"

RS_MysteryEventsHouse_Text_DoorIsLocked:
	.string "Parece que la puerta está cerrada.$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer:
	.string "Ha venido a mi casa un ENTRENADOR\n"
	.string "llamado {STR_VAR_1}.\p"
	.string "¿Quieres combatir contra\n"
	.string "{STR_VAR_1}?$"

RS_MysteryEventsHouse_Text_YouWontBattle:
	.string "¿No vas a combatir? Qué pena\n"
	.string "no poder verte en acción…$"

RS_MysteryEventsHouse_Text_KeepItToA3On3:
	.string "¡Bien, bien!\p"
	.string "Pero mi casa no es muy resistente.\p"
	.string "¿Podría pediros que sea un\n"
	.string "combate de tres contra tres?$"

RS_MysteryEventsHouse_Text_SaveYourProgress:
	.string "Antes del combate, deberías\n"
	.string "guardar la partida.$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch:
	.string "¡Espero ver un buen combate!$"

RS_MysteryEventsHouse_Text_BattleTie:
	.string "Vaya, ha quedado en tablas.\p"
	.string "¡Ha sido un combate genial en el\n"
	.string "que nadie ha cedido ni un paso!$"

RS_MysteryEventsHouse_Text_BattleWon:
	.string "¡Ha sido magnífico!\p"
	.string "¡Ha sido como volver a verme\n"
	.string "en mi juventud!$"

RS_MysteryEventsHouse_Text_BattleLost:
	.string "¡Ah, qué mala suerte!\p"
	.string "Pero ha sido un buen combate.\n"
	.string "Espero que la próxima vez ganes.$"
