// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Co sądzisz o naszej fortecy? Wygląda dobrze, prawda? A garnizon wcale nie gorszy, ha...","Życie żołnierza fortu jest dość nudne... Strażowanie i patrolowanie, spanie i odpoczynek, a potem znowu to samo. Ale w mieście jest inaczej... Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Nękanie żołnierza głupimi pytaniami nie jest mile widziane, "+GetAddress_Form(NPChar)+"...","To już trzeci raz, kiedy próbujesz mnie dziś zapytać...","Niełatwo jest być żołnierzem, a jednak znowu tu jesteś"+GetSexPhrase(", chamie,  "," ")+" próbując mnie wkurzyć. Uważaj, bo wylądujesz w piwnicy fortu...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie, przepraszam za kłopot.","Nie mam nic do powiedzenia, przepraszam."),"Masz rację, przepraszam.","Masz rację, to już trzeci raz. Wybacz mi.","Przykro mi, to nic takiego.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
