gText_PkmnTransferredSomeonesPC::
	.string "{STR_VAR_2} se ha enviado al\n"
	.string "PC de ALGUIEN.\p"
	.string "Se ha guardado en la\n"
	.string "CAJA “{STR_VAR_1}”.$"

gText_PkmnTransferredLanettesPC::
	.string "{STR_VAR_2} was transferred to\n"
#if IS_FRLG
	.string "BILL'S PC.\p"
#else
	.string "LANETTE'S PC.\p"
#endif
	.string "It was placed in \n"
	.string "BOX “{STR_VAR_1}.”$"

gText_PkmnTransferredSomeonesPCBoxFull::
	.string "La CAJA “{STR_VAR_3}” del PC\n"
	.string "de ALGUIEN estaba llena.\p"
	.string "{STR_VAR_2} se ha enviado a la\n"
	.string "CAJA “{STR_VAR_1}”.$"

gText_PkmnTransferredLanettesPCBoxFull::
	.string "BOX “{STR_VAR_3}” on\n"
#if IS_FRLG
	.string "BILL'S PC was full.\p"
#else
	.string "LANETTE'S PC was full.\p"
#endif
	.string "{STR_VAR_2} was transferred to\n"
	.string "BOX “{STR_VAR_1}.”$"

gText_PkmnSentToPCAfterCatch::
	.string "{STR_VAR_2} se ha enviado al\n"
	.string "PC de {B_PC_CREATOR_NAME}.\p"
	.string "Se ha guardado en la\n"
	.string "CAJA “{STR_VAR_1}”.$"

gText_PlayerObtainedTheMon::
	.string "¡{PLAYER} ha obtenido\n"
	.string "{STR_VAR_1}!$"

gText_NoMoreRoomForPokemon::
	.string "¡No queda sitio para más POKéMON!\p"
	.string "¡Las CAJAS POKéMON están llenas y\n"
	.string "no caben más!$"

gText_NicknameThisPokemon::
	.string "¿Quieres ponerle un mote\n"
	.string "a {STR_VAR_1}?$"
