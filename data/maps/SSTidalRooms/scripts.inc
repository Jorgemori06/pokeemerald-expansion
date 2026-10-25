SSTidalRooms_MapScripts::
	.byte 0

SSTidalRooms_EventScript_SnatchGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_SNATCH, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SNATCH
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch::
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed::
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Colton::
	trainerbattle_single TRAINER_COLTON, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah::
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas::
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret::
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi::
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_Text_TakeRestOnBed:
	.string "Hay una cama…\n"
	.string "Vamos a descansar.$"

SSTidalRooms_Text_ColtonIntro:
	.string "Voy mucho en barco a CIUDAD CALAGUA.\p"
	.string "Es que me encanta ir a los\n"
	.string "CONCURSOS.$"

SSTidalRooms_Text_ColtonDefeat:
	.string "¡Qué combate más agradable!$"

SSTidalRooms_Text_ColtonPostBattle:
	.string "Me emociona imaginar qué POKéMON\n"
	.string "veré en el próximo CONCURSO.\l"
	.string "¡La espera me encanta!$"

SSTidalRooms_Text_MicahIntro:
	.string "¿Tus amigos son fuertes?$"

SSTidalRooms_Text_MicahDefeat:
	.string "Tus amigos sí que son fuertes.$"

SSTidalRooms_Text_MicahPostBattle:
	.string "Los amigos no tienen por qué ser\n"
	.string "personas. ¡Para mí, los POKéMON son\l"
	.string "mis amigos más queridos!$"

SSTidalRooms_Text_ThomasIntro:
	.string "Criatura…\n"
	.string "¿Has llamado a la puerta?$"

SSTidalRooms_Text_ThomasDefeat:
	.string "Una derrota se acepta sin prisas\n"
	.string "ni nervios.$"

SSTidalRooms_Text_ThomasPostBattle:
	.string "No perder nunca la compostura es el\n"
	.string "código de conducta del CABALLERO.$"

SSTidalRooms_Text_JedIntro:
	.string "JED: Me da un poco de vergüenza,\n"
	.string "pero… ¡Verás nuestro poder amoroso!$"

SSTidalRooms_Text_JedDefeat:
	.string "JED: Suspiro…$"

SSTidalRooms_Text_JedPostBattle:
	.string "JED: ¡Es la primera vez que nuestro\n"
	.string "poder amoroso no basta!\l"
	.string "¡Qué bien entrenas!$"

SSTidalRooms_Text_JedNotEnoughMons:
	.string "JED: ¿Solo tienes un POKéMON?\n"
	.string "¿No es demasiado triste?$"

SSTidalRooms_Text_LeaIntro:
	.string "LEA: Me siento un poco tonta, pero…\n"
	.string "¡Verás nuestro poder amoroso!$"

SSTidalRooms_Text_LeaDefeat:
	.string "LEA: ¡Jo!$"

SSTidalRooms_Text_LeaPostBattle:
	.string "LEA: ¡No me lo puedo creer!\n"
	.string "Nuestro poder amoroso ha fallado…\l"
	.string "¡Qué bien entrenas!$"

SSTidalRooms_Text_LeaNotEnoughMons:
	.string "LEA: Quería combatir…\n"
	.string "Pero si ni siquiera tienes dos POKéMON…$"

SSTidalRooms_Text_GarretIntro:
	.string "Ah, llegas justo a tiempo.\p"
	.string "Es que me aburro.\n"
	.string "Puedes entretenerme.$"

SSTidalRooms_Text_GarretDefeat:
	.string "… Con eso basta.$"

SSTidalRooms_Text_GarretPostBattle:
	.string "Quizá le pida a Padre que me compre\n"
	.string "un yate.\l"
	.string "¡Un yate para mí y mis POKéMON!$"

SSTidalRooms_Text_NaomiIntro:
	.string "Oh, qué cosa más adorable.\n"
	.string "¿Te apetece un té?\l"
	.string "¿O prefieres combatir?$"

SSTidalRooms_Text_NaomiDefeat:
	.string "Ya veo.\n"
	.string "Te va la acción.$"

SSTidalRooms_Text_NaomiPostBattle:
	.string "Un crucero por el mundo en un barco\n"
	.string "de lujo tiene su encanto, sin duda…\p"
	.string "Pero reconozco que recorrer HOENN en\n"
	.string "ferry también tiene su gracia.$"

SSTidalRooms_Text_NotSuspiciousTakeThis:
	.string "Eh… ¡Hola! ¡No… no hago nada raro!\n"
	.string "Eh… ¡Toma esto! ¡Gratis!\p"
	.string "No… ¡De verdad que no se lo he\n"
	.string "ROBADO a nadie! ¡Yo nunca haría eso!\l"
	.string "¡Está limpio! ¡Puedes usarlo!$"

SSTidalRooms_Text_ExplainSnatch:
	.string "ROBO se queda con los efectos\n"
	.string "beneficiosos de ciertos movimientos\l"
	.string "antes de que los use otro.$"

