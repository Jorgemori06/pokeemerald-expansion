@ Dualocke: el INVESTIGADOR de DEVON (FÉRRICA) revive también los fósiles de otras generaciones, que reparte el
@ randomizer de objetos del suelo. Antes solo sabía revivir el Fósil Raíz y el Fósil Garra (lo vio Miguel,
@ 18/11/2026). Los dos de Esmeralda siguen con su script original; este se usa para el resto.
@ - La tabla de fósiles y su POKéMON está en src/data/dualocke_fosiles.h. Con semilla sale otro al azar
@   (como los demás regalos: lo cambia givemon, y si es repetido o legendario va a VETADOS).
@ - VAR_WHICH_FOSSIL_REVIVED guarda el objeto del fósil (en el original solo era 1 o 2).

@ Desde RustboroCity_DevonCorp_2F_EventScript_FossilScientist, si no lleva ni el Fósil Raíz ni el Garra
Dualocke_EventScript_FosilOtro::
	special Dualocke_BuscarFosil
	goto_if_eq VAR_RESULT, ITEM_NONE, Dualocke_EventScript_FosilNada
	copyvar VAR_0x8006, VAR_RESULT
	closemessage
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	bufferitemname STR_VAR_1, VAR_0x8006
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem VAR_0x8006
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	copyvar VAR_WHICH_FOSSIL_REVIVED, VAR_0x8006
	release
	end

Dualocke_EventScript_FosilNada::
	release
	end

@ Desde RustboroCity_DevonCorp_2F_EventScript_FossilMonReady, si el fósil no era el Raíz ni el Garra
Dualocke_EventScript_FosilListo::
	special Dualocke_EspecieFosil
	goto_if_eq VAR_0x8004, SPECIES_NONE, Dualocke_EventScript_FosilNada
	@ Los nombres se guardan antes de givemon, que puede usar estas variables
	bufferspeciesname STR_VAR_1, VAR_0x8005
	bufferspeciesname STR_VAR_2, VAR_0x8005
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_0x8005
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	givemon VAR_0x8004, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Dualocke_EventScript_FosilEquipo
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Dualocke_EventScript_FosilPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Dualocke_EventScript_FosilEquipo::
	call Dualocke_EventScript_FosilFanfarria
	msgbox gText_NicknameThisPokemon, MSGBOX_DEFAULT
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Dualocke_EventScript_FosilFin
	end

Dualocke_EventScript_FosilPC::
	call Dualocke_EventScript_FosilFanfarria
	msgbox gText_NicknameThisPokemon, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedBoxMon
	call Common_EventScript_TransferredToPC
	goto Dualocke_EventScript_FosilFin
	end

Dualocke_EventScript_FosilFanfarria::
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	return

Dualocke_EventScript_FosilFin::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end
