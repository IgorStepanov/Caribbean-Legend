//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("I've got a question for you.", "I need information.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Hey, captain! Yes, you. Come here I've got a deal for you...";
					link.l1 = "And what's the deal?";
					link.l1.go = "passenger";
					link.l2 = "I am in a hurry, friend. Next time perhaps.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hey, captain, I am busy actually. What do you need?","What do you want, captain?","Cap'n, I am not in the mood to talk. What do you want?");
				link.l1 = "Greeting, "+GetAddress_FormToNPC(NPChar)+". Wait a minute, I want you to tell me something.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "It's nothing, I am on a way to the tavern...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. You are a captain of a ship but you don't look like a merchant. It looks like you have some coins in your pocket... How about to get some interesting information in exchange for a fistful of doubloons?";
				link.l1 = "First, prove that your information is worth a single piece of eight.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "It is, cap, it is. It costs much more than I ask. You give me the gold and I'll tell you when and on which ship a certain very important person will sail. You will be able to ransom this one for a very good price... I'll even tell you the name of the buyer. Deal?";
				link.l1 = "No way! I'm not a kidnapper. Shove off!";
				link.l1.go = "exit_quest";
				link.l2 = "And how can I know that you are telling the truth?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "It would be most unwise to cheat you, sea dog. I live in this town and I don't need the trouble. For just "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" doubloons I'll provide complete information. You will make much more.";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "You have a point. Take the gold and start talking.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "I don't have enough coins with me now.";
				link.l2.go = "passenger_3";
				link.l3 = "Are you kidding me? Paying real gold for empty promises? Get lost...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Don't you? Fine, cap. I can wait for a few days more and this information can too. Find me when you get your gold. It won't be difficult to find me... today, ha-ha-ha!";
				link.l1 = "Don't show your teeth like that. Fine, I'll bring you the gold... if I don't change my mind. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Did you bring my gold?";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Yes. Take it. Don't even try to lie now...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Not yet. Maybe later...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "Keep your powder dry, you'll need it soon, cap. Now listen, in "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" a ship will sail away from our colony, the ship is "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" named '"+pchar.GenQuest.Marginpassenger.ShipName+"' and it will be heading to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". There will be a passenger -  "+pchar.GenQuest.Marginpassenger.Text+", named "+pchar.GenQuest.Marginpassenger.q1Name+"\nThe captain "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Gen"))+" is a yellowbellied coward like all traders, ha-ha-ha! Perhaps, you will even avoid any fighting. Just put the fear of the devil into him and he should hand over the target himself, he-he\nAs you understand, "+pchar.GenQuest.Marginpassenger.Text1+", you'll probably get your coins, yes, but the local authorities will hunt you to death after that. You'd better bring your prey to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". You'll find there a man named "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" and you won't be even need to tell your name. It's your decision where to ransom your man, but don't bite off more then you can chew... But "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" doubloons you can ask for sure. Got it?";
				link.l1 = "Yes. I am going to get back on my ship and write it in the log.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Exactly! Right choice. Fine, cap, good luck in this easy task. Oh yes, I've almost forgotten: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" will sail not from the port but from one of bays nearby. So watch it. Good luck and thanks for the gold!";
				link.l1 = "You're welcome. Don't spend it all in one night.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen matey, calm down and sheathe your weapon.", "Listen mate, calm down and sheathe your weapon.");
			link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you wish.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Don't beat around the bush, cap. Speak what you want!","Oh, fine. What do you want?","Questions? Fine, sailor, I am listening.");
			link.l1 = LinkRandPhrase("Can you tell me the latest gossip?","Has anything interesting happened here recently?","What's going on in the Caribbean?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
