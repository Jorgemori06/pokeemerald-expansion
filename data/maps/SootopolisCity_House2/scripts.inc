SootopolisCity_House2_MapScripts::
	.byte 0

SootopolisCity_House2_EventScript_ExpertF::
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SootopolisCity_House2_EventScript_KnowAboutOrbs
	call_if_eq VAR_RESULT, NO, SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs:
	.string "El MONTE PÍRICO…\p"
	.string "En su cima hay dos prismas, uno al\n"
	.string "lado del otro. ¿Lo sabías?$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide:
	.string "Sí, dos prismas uno al lado del otro…\p"
	.string "Verlos juntos…\n"
	.string "Tiene algo que tranquiliza…$"

SootopolisCity_House2_Text_OughtToVisitAndSee:
	.string "¿Ah, sí?\n"
	.string "Quizá deberías ir a verlos…$"

