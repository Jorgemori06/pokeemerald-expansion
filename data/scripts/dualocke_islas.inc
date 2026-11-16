@ Dualocke: las islas del ferry de CALAGUA (ZONAS.md; Miguel, 16/11/2026).
@ - Se abren una por medalla: ISLA SUR con la 6.ª, ISLA LEJANA con la 7.ª, e ISLA ORIGEN y ROCA OMBLIGO
@   con la 8.ª. El encargado del puerto de CALAGUA da el billete de cada una
@   (Dualocke_EventScript_BilletesIslas) y el ferry ya no espera a la Liga.
@ - En vez de los legendarios, cada isla tiene un Pokémon fuerte (pseudolegendario o con mega) que se
@   puede capturar. Con semilla sale otro de ese tipo (tools/dualocke/aleatorio/estaticos.py, islas()).
@   Al vencerlo o capturarlo deja un premio: un objeto fijo y su megapiedra si tiene mega.
@ - Cada isla hace: setvar VAR_TEMP_8 (especie del setwildbattle), setvar VAR_TEMP_9 (premio fijo),
@   call Dualocke_EventScript_AvisoIsla, setwildbattle, dowildbattle, call Dualocke_EventScript_ResultadoIsla
@   y, si se ha ido, su flag y call Dualocke_EventScript_PremioIsla.

@ Lo llama el encargado del puerto de CALAGUA antes de mirar los billetes.
Dualocke_EventScript_BilletesIslas::
	goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
	call_if_unset FLAG_ENABLE_SHIP_SOUTHERN_ISLAND, Dualocke_EventScript_BilleteSur
	goto_if_unset FLAG_BADGE07_GET, Common_EventScript_NopReturn
	call_if_unset FLAG_ENABLE_SHIP_FARAWAY_ISLAND, Dualocke_EventScript_BilleteLejana
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	call_if_unset FLAG_ENABLE_SHIP_BIRTH_ISLAND, Dualocke_EventScript_BilleteOrigen
	call_if_unset FLAG_ENABLE_SHIP_NAVEL_ROCK, Dualocke_EventScript_BilleteOmbligo
	return

@ Al darlo ya cuenta como enseñado: así sale en la lista de destinos y no se va directo a la isla
Dualocke_EventScript_BilleteSur::
	msgbox Dualocke_Text_BilleteSur, MSGBOX_DEFAULT
	giveitem ITEM_EON_TICKET
	setflag FLAG_ENABLE_SHIP_SOUTHERN_ISLAND
	setflag FLAG_SHOWN_EON_TICKET
	return

Dualocke_EventScript_BilleteLejana::
	msgbox Dualocke_Text_BilleteLejana, MSGBOX_DEFAULT
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_SHOWN_OLD_SEA_MAP
	return

Dualocke_EventScript_BilleteOrigen::
	msgbox Dualocke_Text_BilleteOrigen, MSGBOX_DEFAULT
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_SHOWN_AURORA_TICKET
	return

Dualocke_EventScript_BilleteOmbligo::
	msgbox Dualocke_Text_BilleteOmbligo, MSGBOX_DEFAULT
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_SHOWN_MYSTIC_TICKET
	return

@ Antes del combate: el nombre del Pokémon que sale con la semilla y el aviso
Dualocke_EventScript_AvisoIsla::
	copyvar VAR_0x8004, VAR_TEMP_8
	special Dualocke_GraficoPokemonIsla
	msgbox Dualocke_Text_PokemonIsla, MSGBOX_DEFAULT
	closemessage
	return

@ Después del combate: VAR_RESULT = TRUE si se ha vencido o capturado (y entonces se va), FALSE si no
Dualocke_EventScript_ResultadoIsla::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Dualocke_EventScript_ResultadoIslaSeVa
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Dualocke_EventScript_ResultadoIslaSeVa
	setvar VAR_RESULT, FALSE
	return

Dualocke_EventScript_ResultadoIslaSeVa::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_RESULT, TRUE
	return

@ El premio: el objeto de VAR_TEMP_9 y la megapiedra del Pokémon, si tiene
Dualocke_EventScript_PremioIsla::
	msgbox Dualocke_Text_PremioIsla, MSGBOX_DEFAULT
	giveitem VAR_TEMP_9
	copyvar VAR_0x8004, VAR_TEMP_8
	special Dualocke_MegapiedraPokemonIsla
	goto_if_eq VAR_RESULT, ITEM_NONE, Common_EventScript_NopReturn
	copyvar VAR_TEMP_9, VAR_RESULT
	giveitem VAR_TEMP_9
	return

Dualocke_Text_BilleteSur:
	.string "¡Buenas noticias! Ahora el ferry\n"
	.string "también va a algunas islas lejanas.\p"
	.string "Con tus medallas ya puedes ir a\n"
	.string "ISLA SUR. Toma, tu billete.$"

Dualocke_Text_BilleteLejana:
	.string "¡Otra medalla! Ya puedes ir a\n"
	.string "ISLA LEJANA.\p"
	.string "Para llegar hace falta este mapa\n"
	.string "viejo. ¡Quédatelo!$"

Dualocke_Text_BilleteOrigen:
	.string "¡Ocho medallas! Ya puedes ir a\n"
	.string "ISLA ORIGEN. Aquí tienes el billete.$"

Dualocke_Text_BilleteOmbligo:
	.string "Y este es para ROCA OMBLIGO.\n"
	.string "Dicen que dentro hay algo enorme…$"

Dualocke_Text_PokemonIsla:
	.string "¡Un {STR_VAR_1} enorme vigila\n"
	.string "este lugar!\p"
	.string "¡Se lanza al ataque!$"

Dualocke_Text_PremioIsla:
	.string "¡Donde estaba el POKéMON hay algo\n"
	.string "brillando!$"
