// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Cómo puedo ayudarte?","¿Qué puedo hacer por ti?"),"Dime, ¿qué te aflige, "+GetAddress_Form(NPChar)+"?","Por tercera vez, "+GetAddress_Form(NPChar)+", ¿qué necesitas?","Ya tuve suficiente de ti. ¡Fuera!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión, mis disculpas.","No es nada, discúlpame."),"Perdóname, no es nada.","Tienes razón, ya es la tercera vez. Perdóname...","Mis disculpas.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
