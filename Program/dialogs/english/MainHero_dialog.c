void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "If you're reading this line, it's a bug in the code";
			Link.l1 = "Exit";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
			{
				dialog.text = "Thrilling, damn it! A real naval battle!\nToo bad I won’t see the fight from here... Never mind. I think I’ve learned enough about seafaring to imagine how it goes\nProbably five pirates... One big ship, a couple of mediums, and some small fry. Just right for our pinnace. It'll make a great tale — Lulu will love it!";
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
				pchar.wind.speed = 18.0;
				fWeatherSpeed = stf(18.0);
				//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
				AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
			}
			//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "So, we have found this place on the map. I should mark it, and we're good to go searching.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "Alright, we're here. I should hide my ship in the Southern bay, then come back on foot through the jungle and arrange a nasty surprise for Fleetwood.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "Hm... Trusting this rascal is dangerous, although his story seems genuine. Perhaps, he's not lying this time. But, anyway, I should talk to his wife... Bosun! Bring me that captive woman!";
    			link.l1 = "Aye Aye, captain!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "This seems to be the place. It's the only sapless tree in the vicinity. I should dig here.";
    			link.l1 = "(dig the treasure out)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "What's going on? Where am I?! What kind of place is this?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "This is the door which leads to the inner premises of the ship. It's locked... Hawk must be here. What did Ole mention again? I should use a secret knock.";
    			link.l1 = "Knock twice.";
    			link.l1.go = "knock_2";
				link.l2 = "Knock three times.";
    			link.l2.go = "knock_3";
				link.l3 = "Knock once, pause, knock three times.";
    			link.l3.go = "knock_1_3";
				link.l4 = "Knock twice, pause, knock twice.";
    			link.l4.go = "knock_2_2";
				link.l5 = "Knock three times, pause, knock once.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "Wow! That thing is really heavy!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "No-no-no! No way! Three times were more than enough!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "It is done. Levasseur is dead. It turned out to be much easier than I expected... But something isn't right. Thibaut didn't even speak to Martene! It means that either Robert betrayed me or there's been an accident\nBut where could that bastard Thibaut run? He must be hunting down Catherine. I must act quickly if I want to take the girl alive from under his nose...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "Treasures, treasures... an Indian city... I don't believe in such coincidences... I bet that my brother had something to do with the disappearance of Dichoso's frigate. He probably made sure that Dichoso will never open his mouth again\nOr, maybe he was working with him, the Spanish must have had reasons to think that Dichoso is somewhere around here. This makes no sense. But I am confident that the Indian gold Michel was delivering to de Poincy, as well as Miguel Dichoso's gold is the same gold. The prisoner's story matches with what the officer told me about my brother's adventures\nFunny, Michel had failed to deliver the gold and so had Miguel! And where are the treasures now then? Perhaps, they were the reason why my brother is in a such rush\nErgo, finding the gold will mean killing two birds with one stone: I will look in my brother's insolent eyes again and... yes, the gold's always good. But how the hell do I find it? It seems, that it's time to become real close to the Spanish\nDon Ramona Mendoza is off the table, I doubt that I will be able to deal with him, but holy father Vincento, a baron's worst enemy... he will do. His kind is not scrupulous but loves money and foul means\nDichoso, Dichoso... I've heard this surname before... or haven't I? Whatever, to hell with it. I should go to the officer and claim the Spanish prisoner. Then I may head to Santiago at any time.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "Vanilla has been loaded on the carrack and her sails have long ago disappeared beyond the horizon - and this damned galleon has returned to the port instead of taking to the high seas. I must not show up with my ship in the port - it's best if they think that I had left Guadeloupe... I guess I'll walk to the town through the jungle and find out about my dear Marchais...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "There are only a few guards on the upper deck, all of them rather sleepy. I guess I can take them all out one by one, if I silently come from behind and hit them with a knuckle-duster in the back of the head... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "An unlocked empty house with a cozy room on the second floor, and in the vicinity of Calhoun's apartments... This is just an answer to a maiden's prayer... If I get out of the window and walk on the abat-jour of the roof, I'll sneak into Archie's room with ease. But this must be done at night so that I don't get caught...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "Finally! I have located the spot, indicated by the 'manifestation': it's an Indian idol. When near, the 'Arrow of the Way' stops oscillating and points in one direction. Well, it seems logical - Indian magic and an Indian idol. Now I should mark the location indicated by the 'Arrow of the Way' on the map, and then I will go to Dominica.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "Finally! I have located the spot, indicated by the 'manifestation': it's an Indian idol. When near, the 'Arrow of the Way' stops oscillating and points in one direction. Well, it seems logical - Indian magic and an Indian idol. Now I should mark the location indicated by the 'Arrow of the Way' on the map, and then I will go to Main.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "Both manifestations have been found! Now I must mark the second direction on the map. The intersection of these two directions will show me the location of the island of Ksocheatem.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "Alonso de Maldonado said that there is a path to Tayasal which starts North of Yucatan. It means that I should go deep into the selva of the area. But Gino said that teleport statues were originally supposed to move people to Tayasal\nAnd Miskito's shaman Snake Eye told me the idols were designed to send the 'eaten' to the place. But why then, are those portals are broken? Hm. Besides, the map of Two Manifestations shows an odd circle close to the Miskito's statue\nWhat the hell does it mean? Another magic place? Or it shows that the statue there has some additional functions? I suppose, I should pay a visit to the shaman. Or I can go to the North West of Main and search for the path there, at one of the local bays.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alonso de Maldonado said that there was another way to Tayasal from the northern part of the peninsula of Yucatan. That means I must look for a path into the depths of the selva. It is likely that the path I need begins at one of the coves in the north-western Main.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "It is done. The end of my long journey. I couldn't possibly imagine that saving my brother from prison meant preparing myself for the final fight against him! That I had almost doomed our world. Thank God, this is over\nNothing holds me in the Caribbean any longer. Time to return home, to France. But... Do I really want that?";
				link.l1 = "Yes, I am returning to Europe.";
				link.l1.go = "final_1";
				link.l2 = "No, I am staying here in the Caribbean.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "Have you heard the colonel? The rebels are hiding there! Search everything, turn the house upside down and seize everyone you find there! Get to it!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "This is the best place for an ambush. I should wait here for Pinette's arrival.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "Hm. This story doesn't feel right. I believe that lugger from St. Jones was never meant to exist. The lieutenant is dragging me into his military operation. Why would I need that? I am not at war with the Dutch... What should I do? Should I leave and let Brits have fun on their own? Or should I stay?";
				link.l1 = "Leave.";
				link.l1.go = "FMQN_1";
				link.l2 = "Stay.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "So, the chest is prepared. I could try to find all the required materiel myself, but I'd rather go and see Fadey. He strikes me as a man who can acquire anything.";
    			link.l1 = "*USE A THINKING OUT LOUD OPTION TO FINISH GATHERING MUNITIONS*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "So, we have to build six longboats. For this I need a carpenter, 20 planks and 10 leather packs";
    			link.l1 = "*USE A THINKING OUT LOUD OPTION TO START BUILDING LONGBOATS*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "So, I intend to simply blow this pile of old trees sky high. All I need for this is 300 units of gunpowder just to be sure.";
    			link.l1 = "*use a Thinking Out Loud option to order a gunpowder placement*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" The exit is sealed! It seems they blocked the door with something heavy! "+RandSwear()+"\nHush... What the hell?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "This is it... End of the line\n Looks like don Enrico was serious: there is no way out of these dungeons. I had a moment of hope when I found a second door at the water level but now... I have lost count of time - how long have I been lurking these dark tunnels? Half a day, the entire day? This place is as quiet and scary as a coffin\nThey had a church here once, right here. What a perfect place to say my prayers. I have sinned much, too much... I will pray and sleep here, my wounds and my exhaustion are killing me. If I am lucky I will never get up...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "I, Charles de Maure, French captain and nobleman, swear to myself and my conscience that I am done with my pirate past for good!";
    			link.l1.go = "Good_Choice";
				link.l2 = "Yeah! Yeah! Ah ha ha!! I did it, I survived! Eat it, Zorro! Go to hell, Marcus! Now I'm on my own! Charlie Prince may have died, but Charles de Maure no one shall ever kill!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "What should we do?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "... of course, Levasseur is no fool. Otherwise, why would they need to arrest us this very moment?\nAnd they didn't say a word!\n" + dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "Helen, why are you so quiet?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "Mary, why do you look so happy?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "Tichingitu? Say something appropriate for the situation.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "Hercule, can you hear me? What are we going to do?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "Nothing to be done. Guess I'll wear Michel's shoes for a while.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "Oh my God, they killed Hercule!";
				link.l1.go = "exit";
				link.l2 = "You bastards!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "What an evening! Why did I listen to her? Brother was right - the girls here are completely different. Maybe they add something to the rum?";
				link.l1 = "Time to sleep, and then - to Cartagena!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "Not a single thing was stolen, though everything is scattered around. Even the valuables are untouched. ";
				link.l1 = "They weren't trying to rob me - they were looking for something specific. But what? And more importantly, who...?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuest("PZ_OsmatrivaemSunduk_3");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "Let's wait until nightfall and attack!";
				link.l1 = "We'll start preparing the longboats in the meantime.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "Oh my God... No, no, no... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "Oh God, oh God, oh God... Why? Oh God, why... but I did all I could...";
				link.l1 = "It's all my fault, mine alone. I didn't get here in time. I am so sorry... Please, please forgive me.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("That was one hell of a fight... Now we can call those cowards that ran away...", "Ha! That was easy. And those landlubbers just scattered!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Hmm... So what should I do now?", "What to do now?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Call for a companion.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Rest until morning.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Rest until night.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Rest until next morning.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Enlist the slaves in the crew.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "Start capturing the nearest town.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "I should rest...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "I want to change the ammunition for the firearms.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "I want to change the ammunition for the musket.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "I want to choose a priority weapon for combat.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "I want to select a potion for constant use.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "Try to find the island by the coordinates on the map.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Summon Adam Rayner.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Arrest Adam Rayner.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "Tally up the chest's contents and decide to finish gathering munitions for Picard.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "Give an order to attack the Maracaibo plantation.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "Give an order to build longboats.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "Order to deliver the gunpowder to the dead abatis.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "Think about a wedding.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "Make a marriage proposal.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "Prepare the celebration.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			// -->Авторемонт			
			if(Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions()) 
			{
				Link.l14 = "Start repairing ships";
				Link.l14.go = "StartSelfRepair";
			}			
			// <--Авторемонт
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "Finish the business on the Caribbean and sail to Europe.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("Not now. There is no time.", "No time for that, too much to do.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		
		case "StartSelfRepair":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchRepair(pchar);
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Select ammunition type:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Select ammunition type:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "At the beginning of the fight I will use:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "Select potion:";
	    	Link.l1 = "Healing potion.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "Elixir.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "Mixture.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "Ginger root.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "Rum.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "Wine.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "I want to select potions automatically.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "Wait, I have changed my mind..";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("A healing essence will be used by default.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("An elixir will be used by default.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("A mixture will be used by default.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("A ginger root will be used by default.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum will be used by default.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wine will be used by default.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Potions will be selected automatically.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "We could start capturing the town, but the ship would not endure the salvos of the fort's cannons for long, and we won't be able to send a landing party.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "No, I am not that crazy yet..";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "There is no point in attacking this mine without first gathering information about the gold and silver mined there. Otherwise I'll be sending my men to die in vain.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Attack " + GetCityName(chr.City) + ".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "Quit messing around! Halt!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "Quit messing around! Halt!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "To arms!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Stop!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Heh! There aren't enough people in the crew; we need at least "+needCrew+" men.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Don't disperse! Continue with the attack!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "None of the slaves are willing to join the crew.";
	            Link.l1 = "Hell with them!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "There's no free space on the ship for new sailors.";
	                Link.l1 = "Heh! I'll need to transfer part of the crew to another ship.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "Your crew can be replenished with " + pchar.GenQuest.SlavesToCrew+ " slaves who want to serve under you. Would you like to accept?";
	                Link.l1 = "Yes";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "No";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
			if(!bOk)
			{
				// belamour legendary edition перк получил время работы, старый метод не подходит
				if (GetOfficersPerkUsing(pchar, "IronWill"))
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
				}
				else
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
				}
			}
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "This sweet ship is mine now, and I am the captain here! It's a pity that I had to kill the entire crew, though.";
			Link.l1 = "It's time to come ashore...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Which companion to summon?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Some other time.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "Pity that I don't have the necessary navigational instruments for determining the latitude and longitude. I'll have to search for the island some other time. ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "Bosun! Bring Adam Rayner to me immediately!";
			link.l1 = "Aye aye, captain!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "So, I knocked, now let's wait for the answer...";
			link.l1 = "(wait)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "So, I knocked, now let's wait for the answer...";
			link.l1 = "(wait)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "So, I knocked, now let's wait for the answer...";
			link.l1 = "(wait)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "So, I knocked, now let's wait for the answer...";
			link.l1 = "(wait)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "So, I knocked, now let's wait for the answer...";
			link.l1 = "(wait)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "He isn't opening the door... I guess I used the wrong secret knock. Alright, I'll come tomorrow and try again. Today, he will not open the door for sure.";
			link.l1 = "(leave)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "Wow! He answered and opened the door! I can enter now...";
			link.l1 = "(enter)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "Caramba! So that's the delayed backup for Levasseur... No way I can leave through the door... Fine, I'll follow in Thibaut's steps - through the window! After all, this rascal managed to slip away somehow!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "So, our mission is to repel an attack of the blasted Spanish and save Saint Pierre. The fort is captured, and a battle is being fought in the streets. There is a powerful squadron in Saint Pierre's bay and they have got a ship of the line as a flagship. Attacking it now is pointless, the fort and the city is under enemy control, so they won't let us land in port\nTherefore, I have decided to move through the jungles and strike them from behind through the city gates. Once the fort and the city are cleared from the Spanish, we shall deal with the squadron. It will become much more vulnerable without the fire support of the fort\nThis won't be easy, so I have given orders to pay extra hundred thousand pesos to be distributed among the crew in addition to the normal salary. Let's move!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "Hold on, where am I going? I can't leave the position of Governor-General without permission from Paris! Otherwise I will be most definitely arrested for the unauthorized abandonment of the entrusted colonies when I come back to France. Paris, I will miss you ...";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "Then let's waste no more time! I miss the fields of my dear Gascony so much! Set sail!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "I believe this is the right decision! What is left in good old Europe waiting for me, when I found myself here? Besides, I can get back to France whenever I choose, anyway!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "That's the best way. I should come on board and sail out of here.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "Nah, no way, I am staying. But hell, I won't stay here waiting for God knows what. I should sail to the port of Philipsburg and investigate the situation. I don't fancy the idea of being a tool in the hands of some blasted lying Englishman.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "Thirty pieces of cold steel are in the chest! Should I stop now, or should I gather more firearms, charges, and potions?";
				link.l1 = "This is enough!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "No, I should keep filling this chest.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "Fill with the contents of Fadey's chest, and take the excess."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "Thirty pieces of cold steel are not gathered yet! I should bring more.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Locking the chest and making a plan to sneak it to the plantation.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "Go, chaaarge! Huurah!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "All required materials are prepared, we should start building the long boats right away.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "I don't have an experinced carpenter capable of performing the job. I should assign an officer to this position.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Not enough materials, we need at least 20 packs of planks plus 10 bales of leather.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "Everything`s ready for a blast!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "I need at least 20 men to deliver the gunpowder.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Not enough gunpowder, at least 300 is needed.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "Was it a door?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "Right! We have visitors... Jan?..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "Me and "+sTemp+" have been together for a long time, and our bonds are stronger than any church vows, but I want both of us to remember this moment. Therefore, I need to decide where I am to propose to her:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Isla Tessoro - this island means a lot in our story. I suppose, there is no better place - Sabu Matila Bay is charming at sunset!";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "Tortuga - a symbol of freedom of our time, and the view from the lighthouse to the Tortu strait is worthy of the brush of any painter!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "Jamaica - there's so much to it! And admiring the dawn in Portland Cove is how I imagine Paradise on earth.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "But we cannot do this without the solemnity of the church - everything should be according to all the canons so that my father would be forced to accept my choice. So, I will need a priest, and I don't see anyone worthy of this position besides Abbot Benoit. He is an old friend of my father and from him began my adventures in the New World. I think he will agree to do me the honor.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "But we cannot do this without the solemnity of the church - everything should be according to all the canons so that my father would be forced to accept my choice. So, I will need a priest, and I don't see anyone worthy of this position besides Abbot Benoit. He is an old friend of my father and from him began my adventures in the New World. I think he will agree to do me the honor.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "But we cannot do this without the solemnity of the church - everything should be according to all the canons so that my father would be forced to accept my choice. So, I will need a priest, and I don't see anyone worthy of this position besides Abbot Benoit. He is an old friend of my father and from him began my adventures in the New World. I think he will agree to do me the honor.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Well, this can happen without mankind's solemnity. Though I would prefer to discuss this with "+sTemp+" a little later.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "Well, I'm ready!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "Everything is prepared!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "The necessary goods and coin haven't been collected yet!";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    DialogExit();
	locCameraSleep(false); //boal
}
