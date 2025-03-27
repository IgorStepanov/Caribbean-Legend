// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué deseas, " + GetAddress_Form(NPChar) + "?"), "¿Preguntas de nuevo, " + GetAddress_Form(NPChar) + "... ", "Preguntas, preguntas... ¿Qué tal si comerciamos, " + GetAddress_Form(NPChar) + "¿eh?", "Escucha, ¿cuánto tiempo planeas hablar?", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sin preguntas por ahora...", "Lo siento, No tengo nada que decirte..."), "Una vez más, lo siento...", "Tal vez realmente sea hora de comerciar...", "Lo siento,   hagamos un trueque...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
