// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}

	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		

		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Капитан "+pchar.name+"! Офицер Мэри Каспер готова приступить к своим обязанностям!";
				link.l1 = "Отлично, офицер! Приказываю немедленно прибыть на моё судно. Но первое задание нужно выполнить прямо сейчас: поцеловать своего капитана!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "Это было просто великолепно, милый... С добрым утром!";
				link.l1 = "С добрым утром, дорогая! Ты - прелесть!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", для меня нет большей радости, чем быть в твоих объятиях, да... Пойдём!",""+pchar.name+", если бы такое было возможно - я бы вообще не расставалась с тобой ни на минуту. Пойдём!");
			link.l1 = RandPhraseSimple("Ты - самая лучшая на свете, моя девочка...","Ты - просто прелесть, моя красавица...");
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Милый, ты как всегда - был великолепен!","Всё было просто замечательно, дорогой!");
			link.l1 = LinkRandPhrase("Я рад, что ты довольна, свет души моей...", "Я обожаю тебя, Мэри...", "Я люблю тебя, Мэри...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", для меня нет большей радости, чем быть в твоих объятиях, да... Но сейчас немного не время - нужно отловить этого прохвоста Тибо, пока он не смылся куда-нибудь.";
				link.l1 = "Ты как всегда права, моя девочка...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", для меня нет большей радости, чем быть в твоих объятиях, да... Пойдём!",""+pchar.name+", если бы такое было возможно - я бы вообще не расставалась с тобой ни на минуту. Пойдём!");
			link.l1 = RandPhraseSimple("Ты - самая лучшая на свете, моя девочка...","Ты - просто прелесть, моя красавица...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			Pchar.questTemp.SexPartner = Npchar.id;
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "GiveKissInRoom");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestCheckDelay("Mary_LoveSex", 2.5); // mitrokosta fix
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", мы так давно не были вместе... Ты совсем забыл про меня, да! Милый, я хочу расслабиться - давай снимем комнату и уединимся!",""+pchar.name+", ты совсем увлёкся делами, и я начинаю подозревать, что и вовсе забыл про меня! Дорогой, я очень хочу... остаться с тобой вдвоём. Давай снимем комнату, да!");
			link.l1 = "Мэри, милая, ну что ты такое говоришь - 'забыл про меня'? Глупости... Но я действительно закрутился со всеми этими проблемами, конца-края им нет. Прости меня, моя девочка. Конечно, пойдём наверх - и пусть весь мир подождёт!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Не сегодня, дорогая. Голова что-то болит.","Мэри, милая, как я могу забыть о тебе? Давай попозже - дел сейчас по горло..."),RandPhraseSimple("Ты всегда в моих мыслях, Мэри, но сейчас мы не можем себе позволить расслабиться.","Мэри "+npchar.lastname+", никаких глупостей на сегодня"));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "Эх... Что ещё бедной девушке остаётся... Так точно капитан!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			Log_Info("Для отказа Мэри станьте более известным");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Шарль...";
			link.l1 = "Мэри, милая, ну что ты такое говоришь - 'забыл про меня'? Глупости... Но я действительно закрутился со всеми этими проблемами, конца-края им нет. Прости меня, моя девочка. Конечно, пойдём наверх - и пусть весь мир подождёт!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Да, не так! Я тебе больше не нравлюсь, да? Скажи!";
			link.l1 = "Вот так номер! Мэри, что за вздор? С чего ты это взяла?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Тогда почему ты ходил к этим сучкам, этим бордельным девкам? Я это знаю, да, не отрицай! Я чем-то тебя не устраиваю, когда мы занимаемся любовью, да? (плачет) Скажи...";
			link.l1 = "Мэри, Мэри... успокойся, пожалуйста, девочка. Да, я был в борделе несколько раз, но исключительно по делам. Понимаешь - по делам, а не для развлечений!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "И в комнату со шлюхами ты тоже 'по делам' поднимался, да? (всхлипывает) Ты врёшь мне, "+pchar.name+"!";
			link.l1 = "Мэри, милая, да перестань же наконец... У меня действительно были дела, с хозяйкой борделя. И наверх я поднимался тоже... вот, в последний раз по личной просьбе губернатора - он просил найти там своё утерянное обручальное кольцо. Ну разве мог я отказать Его Светлости?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "А как я объясню маман, что мне нужно на второй этаж, чтобы пошарить по углам и под кроватью? Никак. Вот и пришлось покупать шлюху... Второй раз мне шепнули на ушко добрые люди в таверне, что один купчина в пьяном угаре после похода в бордель потерял документы на свой корабль и груз. Опять пришлось оплачивать девку, чтобы пройти в комнату, зато за бумаги мне заплатили десятикратную сумму...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "В третий раз я действовал по заданию коменданта: расспросить бордельных девок об одном офицере гарнизона, завсегдатае злачных мест. Этот офицер подозревался в шпионаже и связи с пиратами. В итоге мы отловили мерзавца, и я получил приличную награду...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "Видишь? Я же говорю тебе - это деловые визиты. Мэри, мне правда никто кроме тебя не нужен. Ты у меня лучшая, честное слово! Неужели ты думаешь, что я пойду к каким-то грязным портовым шлюхам, когда у меня есть ты? Как тебе такое вообще могло прийти в голову?";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+"... Это действительно так? Ты не обманываешь? Ты не был с ними?";
			link.l1 = "Мэри, милая, кроме тебя для меня никого не существует, правда. Подойди поближе, дорогая. Дай я тебя обниму... Вытри слёзы, и перестань, наконец, ревновать! Ну хочешь, я больше вообще в бордели заходить не буду!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Да, хочу!.. "+pchar.name+", я ревную, потому что люблю тебя... И не хочу тебя потерять, да! Слышишь? Я убью любую дрянь, которая только посмеет приблизиться к тебе!";
			link.l1 = "Тише, тише... моя собственница. Никого убивать не потребуется. И ты меня не потеряешь, обещаю. Всё, успокойся. Ты у меня единственная и самая лучшая на свете... Поверь, это так.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", что за странный вопрос? Ты что, думаешь, я отпущу тебя одного? И не рассчитывай! Я иду с тобой! Когда отправляемся?";
			link.l1 = "Действительно, милая, зная тебя, с моей стороны это - странный вопрос... А когда выдвигаться - я скажу немного позже. Пока нам нужно подготовиться.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Я готова в любой момент, мой капитан! С тобой - хоть на край света!";
			link.l1 = "Спасибо, любимая...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			npchar.CanTakeMushket = true;
			npchar.DualAnimations = true;
			
			npchar.CivilAnimation.model = "jessika2_civil";
			npchar.CivilAnimation.animation = "Mary";
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! Мне надо с тобой поговорить, да! Серьёзно поговорить!";
				Link.l1 = "Что случилось, Мэри? Что-то не так?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Я вся во внимании, мой дорогой капитан!","Да, "+pchar.name+", я тебя внимательно слушаю!","У тебя есть для меня задание, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Мэри, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдёшь со мной?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Мэри, дай мне полный отчёт о корабле.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Я хочу, чтобы во время стоянки в колонии ты закупала товары.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Мэри, я хочу с тобой посоветоваться.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Мэри, у меня для тебя есть распоряжение...";
            Link.l1.go = "stay_follow";
			
			
			bool readyToSex = isReadyToSex(npchar); //CheckAttribute(npchar, "quest.daily_sex")
			
			if (pchar.location == Get_My_Cabin() && readyToSex)
			{
				Link.l2 = RandPhraseSimple("Милая, я хочу остаться с тобой наедине, прямо сейчас. Ты не возражаешь?","Дорогая, как насчёт того, чтобы немного... побыть вдвоём?");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && readyToSex && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Милая, а давай снимем комнату и останемся вдвоём?","Дорогая, мне так хочется побыть с тобой наедине... может, снимем комнату и забудем обо всём на пару часов?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Пока ничего, Мэри.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Корабль прекрасный, Шарль, да! Пробоину ниже ватерлинии после последнего боя залатали, паруса просушены. А что ты хотел? Не смотри так на меня, я на казначея никогда не училась.";
			Link.l1 = "Прости, Мэри, я и правда как-то не подумал.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Шарль, так мне ничего и не надо закупать. Одежда у меня есть, клинок есть. Но спасибо за беспокойство, мне очень приятно, да!";
			link.l1 = "Так я же имел в виду... Ладно, дорогая, забудь, всё хорошо.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Какие будут приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			//sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Нужно изменить тип боеприпаса для твоего пистолета.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Нужно изменить тип боеприпаса для твоего мушкета.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Нужно изменить тип твоего приоритетного оружия для боя.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Я хочу, чтобы ты держалась на определённом расстоянии от цели.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			if(LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet))
			{
				rItem = ItemsFromID(sBullet);
				notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			}
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "В начале боя я буду доставать:";
			Link.l1 = "Холодное оружие";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Мушкет";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			NPChar.PriorityMode = 1;
			UpdateWithPriorityMode(NPChar);
			//SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			NPChar.PriorityMode = 2;
			UpdateWithPriorityMode(NPChar);
            //SetPriorityMode(NPChar, 2);
			DialogExit();
		break;	

		case "TargetDistance":
			dialog.text = "На какой именно, капитан? Но учти, дальше двадцати ярдов я не смогу попасть.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Мой капитан, я тебя не понимаю.";
				link.l1 = "Извини, ошибочка вышла...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Я буду стоять на месте, никуда не двигаться. Ты хочешь этого, капитан?";
				link.l1 = "Да, именно это от тебя и требуется.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Я не могу встать дальше двадцати ярдов от цели. Тогда я промахнусь.";
				link.l1 = "Хорошо, тогда держись на расстоянии в двадцать ярдов.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Я тебя поняла.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Есть, мой капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Есть, мой капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}