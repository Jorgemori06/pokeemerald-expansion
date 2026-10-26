PacifidlogTown_House1_MapScripts::
	.byte 0

PacifidlogTown_House1_EventScript_Man::
	msgbox PacifidlogTown_House1_Text_RegiStory, MSGBOX_NPC
	end

PacifidlogTown_House1_EventScript_Woman::
	msgbox PacifidlogTown_House1_Text_SixDotsOpenThreeDoors, MSGBOX_NPC
	end

PacifidlogTown_House1_Text_RegiStory:
	.string "En la región de HOENN hay tres POKéMON\n"
	.string "que representan el poder de la roca,\l"
	.string "el hielo y el acero.\p"
	.string "Dicen que cada uno se esconde en lo\n"
	.string "más hondo de una cueva.\p"
	.string "Esa es la historia que me contaban\n"
	.string "cuando era pequeño.$"

PacifidlogTown_House1_Text_SixDotsOpenThreeDoors:
	.string "“Seis puntos abren tres puertas”.\p"
	.string "Eso decía el abuelo, pero no sé qué\n"
	.string "quería decir.$"

