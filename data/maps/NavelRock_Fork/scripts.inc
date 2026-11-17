NavelRock_Fork_MapScripts::
	.byte 0

@ Dualocke: entrenador de ROCA OMBLIGO
NavelRock_Fork_EventScript_Lucas::
	trainerbattle_single TRAINER_LUCAS_2, NavelRock_Fork_Text_LucasIntro, NavelRock_Fork_Text_LucasDefeat
	msgbox NavelRock_Fork_Text_LucasPostBattle, MSGBOX_AUTOCLOSE
	end

NavelRock_Fork_Text_LucasIntro:
	.string "Un camino sube y el otro baja.\n"
	.string "¡Y los dos acaban en algo enorme!$"

NavelRock_Fork_Text_LucasDefeat:
	.string "¡Uf! Vuelvo a la superficie.$"

NavelRock_Fork_Text_LucasPostBattle:
	.string "Arriba, algo arde. Abajo, algo\n"
	.string "ruge en el agua. ¿Por dónde vas?$"
