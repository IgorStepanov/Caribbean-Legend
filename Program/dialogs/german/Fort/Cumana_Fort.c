// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was denken Sie über unsere Festung? Sieht gut aus, ja? Und die Garnison ist noch nicht schlechter, ha...","Das Leben eines Festungssoldaten ist ziemlich langweilig... Bewachen und patrouillieren, schlafen und ausruhen und dann wieder von vorne. Aber in der Stadt ist es anders... Was möchtest du, "+GetAddress_Form(NPChar)+"?"),"Es ist nicht willkommen, einen Soldaten mit dummen Fragen zu belästigen, "+GetAddress_Form(NPChar)+"...","Es ist das dritte Mal, dass du heute versuchst, mich zu fragen...","Es ist nicht einfach, ein Soldat zu sein und doch bist du wieder hier"+GetSexPhrase(", Tölpel,  "," ")+" versuchen, mich zu verärgern. Sei vorsichtig, sonst landest du im Keller der Festung...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt, Entschuldigung für die Störung.","Ich habe nichts zu sagen, Entschuldigung."),"Du hast recht, ich entschuldige mich.","Du hast recht, das ist schon das dritte Mal. Verzeih mir.","Entschuldigung, es ist nichts.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
