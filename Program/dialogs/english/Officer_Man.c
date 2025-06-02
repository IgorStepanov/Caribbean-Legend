void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			npchar.CanTakeMushket = true;
			DeleteAttribute(npchar, "DualAnimations");
			//npchar.DualAnimations = true;
			dialog.text = "Да-а-а, капитан?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Ну что, Румба, на чьих костях сегодня спляшем?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Да, Элли?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Слушаю тебя, капитан.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = npchar.name+", я бы хотел тебя попросить кое о чём очень серьёзном. Есть один... каменный истукан краснокожих. И мне понадобится помощь. Я могу попросить о ней только самых близких друзей, вроде тебя. Новички или те, кому я ещё не слишком доверяю, не подойдут.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = npchar.name+", хорош чаек считать. Весь груз описал? Дай полный отчёт с прогнозом.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = npchar.name+", мне нужно, чтобы ты, начиная с этого дня, закупал определённые товары в портах.";
				Link.l12.go = "TransferGoodsEnable";
				
				if (startHeroType == 4)
				{
					Link.l11 = npchar.name+", отчитайся, пожалуйста, обо всём на корабле?";
					Link.l12 = npchar.name+", я очень устаю, ты не мог бы пополнять запасы определённых товаров в каждом порту?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Приготовь мне отчёт о состоянии корабля и всего, что на нём есть, "+npchar.name+".";
					Link.l12 = "Ты не мог бы закупать определённые товары во время наших заходов в порт?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Пересчитай мне всё, что есть на корабле, и доложи об его состоянии в целом.";
					Link.l12 = "Мне нужно, чтобы ты докупал вот эти товары во время наших заходов в каждый порт.";
				}
				
				if(CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l12 = "Знаешь, закупать товары в колониях не нужно.";
				    Link.l12.go = "TransferGoodsDisable";
			    }
			}
			//////
			Link.l1 = "Внимательно слушай мой приказ!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Непременно на чьих-нибудь. А пока что слушай мой приказ.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Слушай мой приказ... "+npchar.name+".";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Это хорошо, потому что у меня для тебя новый приказ, "+npchar.name+".";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Слушай мой приказ, "+npchar.name+".";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Ничего, "+npchar.name+", вольно.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Посмотрим, "+npchar.name+", как пойдёт.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Нет, "+npchar.name+", ничего.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Да нет, ничего.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Ничего, всё в порядке.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Капитан, но у нас ведь нет корабля!";
				Link.l1 = "Спасибо, напомнил...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Irons_officer";
				break;
			}
			
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Максимальная активность крыс в рейсе " +
			FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
			"%% от количества груза. На "+GetCrewQuantity(PChar) + " матросов нужно " + makeint((GetCrewQuantity(PChar)+6) / 10) + " провианта в день. Это без учёта перевозимых рабов.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;

		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Капитан, какие товары?! Нужно сначала корабль где-нибудь раздобыть!";
				Link.l1 = "Да, ты прав.";
				Link.l1.go = "Exit";
				NextDiag.TempNode = "Irons_officer";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Будет исполнено, капитан!";
			Link.l1 = "Вольно.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			NextDiag.TempNode = "Irons_officer";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Будет исполнено, капитан.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Ой, приказ прямо-таки. Тебе так нравится муштра и все эти штучки? Лучше бы сразу сказал, что нужно сделать.","Ну ты прямо-таки, как сержант какой-то. Не идёт это тебе, ты слишком прекрасна для этого. Да и в армии бы не выжила и дня. Но я тебя слушаю.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Видимо, ты и правда большой любитель формы, муштры и прочего. Но ладно, продолжай.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "И какой же?";
			}
			
            Link.l1 = ""+GetSexPhrase("Никуда не иди и ничего не делай, просто наблюдай, понял меня? А то знаю я тебя.","Вот и стой в таком случае на месте, понял меня?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Просто стой здесь, никуда не отходи и ничего не трогай.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Стой здесь и никого не пропускай.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Следуй за мной и ни на что не отвлекайся - жёнушек чьих-нибудь или внезапно возникших сослуживцев.","Держись рядом, хорошо? В предстоящей заварушке мне бы хотелось, чтобы моя спина была прикрыта.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Следуй за мной. А то смотрю, ты задумался о чём-то.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Иди за мной, а то встал чего-то.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Мне нужно, чтобы ты стрелял из пистолета другими снарядами.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Мне нужно, чтобы в предстоящей схватке ты стрелял другими снарядами.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "В следующем бою будешь пользоваться другими снарядами.";
					}
				}	
			}
			
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Мне нужно, чтобы ты стрелял из мушкета другими снарядами.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Нужно изменить тип твоего приоритетного оружия для боя.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Мне бы хотелось, чтобы ты держал определённую дистанцию между собой и врагами.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Я бы хотел, чтобы ты держался на определённом расстоянии от врагов, "+npchar.name+".";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Соблюдай определённую дистанцию между собой и врагами, "+npchar.name+".";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Это какими? Надеюсь, ты тщательно отобрал каждый снаряд? А то кто знает, куда он полетит, хе-хе.","Для тебя - что угодно. Неважно, какие они будут, но никогда - не холостые, хе-хе.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Чую, намечается кое-что интересное! Хорошо, и какими же?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Опять пристреливаться... Ладно, какими?";
			}
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
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
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Даже если тебя будут избивать, хе-хе? Понял, будем наблюдать за этим.","Караульного из меня решила сделать? А если тебя будут избивать или ещё что?")+"";
            Link.l1 = ""+GetSexPhrase("Но-но! Разберёмся в случае чего.","Ну ты же не будешь просто смотреть на это, верно? Если ты и правда считаешь своего капитана таким прекрасным, как говоришь, то сделаешь что-нибудь.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Даже по нужде? Ладно-ладно, не смотри так, я тебя понял.";
				Link.l1 = "Уж надеюсь на это.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Понял тебя. Не боись, никто не пройдёт.";
				Link.l1 = "Если ты никого не проворонишь, конечно. Но хорошо.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Очень смешно. Но я тебя понял.","О, не волнуйся, твой тыл всегда под моим пристальным присмотром, хе-хе.")+"";
            Link.l1 = ""+GetSexPhrase("Вот и хорошо.","Боже, ты неисправим, "+npchar.name+".")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Да вот пытаюсь вспомнить нечто очень важное. А потом понимаю, что даже не знаю, что именно, так как память-то потерял тогда, так что ничего не выйдет. Ладно, пойдём.";
				Link.l1 = "Остроумно, ничего не скажешь.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Ну так я стою, потому что ты сам мне ранее это приказал. Иду, иду.";
				Link.l1 = "Кхм, ладно-ладно.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Какую? Имей ввиду, что в поле больше, чем на двадцать метров, я не смогу вести прицельный огонь. Если, конечно, тебе нужно, чтобы я непременно попадал, хе-хе.","Как будто я сам горю желанием подходить вплотную к вонючим мужикам после твоего общества. Так какую? Но знай, что больше, чем на двадцать метров, я не смогу вести прицельный огонь. Никто не смог бы.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Хорошо, каком же? Но напоминаю, что больше, чем на двадцать метров, я в пылу сражения вести прицельный неспешный огонь не смогу.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Хорошо. Какую? Помни, что дальше, чем... впрочем, не маленькие мы уже с тобой оба, и так знаешь.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Тебе не стоит заниматься юмором.","Тебе ещё у меня учиться и учиться искусству шутки, девочка моя. Но ты определённо делаешь успехи!")+"";
				link.l1 = ""+GetSexPhrase("Странно, мне всегда говорили обратное.","Очень смешно, "+npchar.name+".")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Не самая твоя плохая шутка. Может, однажды ты даже перестанешь быть занудой, хе-хе.";
					Link.l1 = "Ну-ну.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ха-ха-ха, хорошая шутка.";
					Link.l1 = "Вообще-то я просто... ладно.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Что ж, тогда я буду просто стоять на месте и держать оборону. Если будешь биться с ними слишком далеко - сам"+GetSexPhrase("","а")+" виноват"+GetSexPhrase("","а")+", хе-хе.";
				link.l1 = "Не ёрничай, всё верно, именно этого я от тебя и хочу сейчас.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Хех, мог бы просто сказать, чтобы я держал оборону, а не говорить про расстояние там, цифры.";
					Link.l1 = "Ну, главное, что ты меня понял.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Понял, буду держать оборону здесь. Подводи их тогда ко мне поближе, чтоб отстреливать мог.";
					Link.l1 = "Непременно.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Слушай, я понимаю, конечно, что тебе бы хотелось, чтобы каждый мой выстрел был как тогда на маяке, но не выйдет. Там точка хорошая была. И спокойствие. В пылу боя так не получится.";
				link.l1 = "Хм, ну ладно. Тогда держись на расстоянии в двадцать ярдов.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Я знаю, что ты бы этого хотел, да все ребята бы этого хотели, но как тогда, на маяке - больше не получится. Мне понадобятся хорошая точка, ну и чтобы никто не мог до меня добраться, а то нервы сдадут.";
					Link.l1 = "Хм, ну ладно.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Я, конечно, отточил свои навыки с тех пор, но невозможное так и останется невозможным - в разгаре боя тот выстрел с маяка мне никак не повторить. Даже с колесным штуцером.";
					Link.l1 = "И невозможное возможно, "+npchar.name+". Но ладно, нет - так нет.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Очень хорошо. Буду поддерживать именно такое расстояние, а если будем в таверне или пещере - выйду, чтобы его соблюдать, ха-ха.", "Постараюсь запомнить. Но имей ввиду, что палубы и замкнутые пространства продиктуют свои условия.");
			link.l1 = ""+GetSexPhrase("Несмешно, "+npchar.name+". Действуй по обстоятельствам, но без шуточек и подстав.","Я знаю это, "+npchar.name+", не тупая.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Постараюсь запомнить.";
				Link.l1 = "Хорошо, рассчитываю на тебя.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Есть, капитан.";
				Link.l1 = "Непременно.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Помощь в чём, украсть его? Только зачем? Я, конечно, польщён, но ты уже давно мог бы сказать всё. Давай, сплюнь.";
			link.l1 = "Следи за языком, а? Впрочем, чёрт с ним - мне на самом деле всё равно, как ты выражаешься, пока ты на моей стороне. Так вот, тот истукан. Через него можно... магическим образом попадать в другое место. Не смотри на меня так - я понимаю, как это звучит. Но я уже проходил через это и видел всё своими глазами. Это... безопасно, если выпить один эликсир.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Смотрю, ты уже выпил несколько. Хотя нет, вроде трезвый. А ещё про меня говорят, что я всё время несу околесицу...";
			link.l1 = "Ты пойдёшь со мной, или нет? Истукан должен перенести нас в древний город индейцев майя, и кто знает, что нас там ждёт? Ты один из тех, на кого, как я считаю, я могу положиться в трудную минуту. И сейчас такая минута как раз пришла.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Дурное у меня предчувствие насчёт всего этого. Не будь ты моим капитаном, сказал бы, что тебе место в лечебнице для душевнобольных. Ты ещё скажи, что Бог существует.";
			link.l1 = "Существует, "+npchar.name+". И, как я к собственному удивлению обнаружил на этом Архипелаге, не только наш. Ты сам мог видеть, как тут творилась всякая чертовщина. И наверняка заметил влияние благословлённых или проклятых побрякушек.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Чертовщина есть и дома. И ей всегда было нормальное объяснение. Извини, капитан, но плясать вокруг каменных идолов я с тобой не стану. Перестрелять врагов - пожалуйста. Я, может, и потерял память, но вот рассудок - нет. По крайней мере, я так думаю.";
			link.l1 = "Ну, заставить я тебя не могу. Так что... как хочешь, "+npchar.name+".";
			link.l1.go = "tieyasal_5";
			link.l2 = "Да уже сомневаюсь, хватит ли тебе духу перестрелять их, храбрец ты наш, раз боишься к камню подойти.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ну-ну, губы-то не надувай. Ладно, если вернёшься после танцев вокруг этого своего... истукана, то я подумаю в следующий раз.";
			link.l1 = "Следующего раза уже может и не быть. Возвращайся на корабль, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Я не боюсь, не подумай. Но своё чутьё привык слушать, оно за долгие годы меня не подводило. И сейчас оно говорит, что ничего хорошего из этого не выйдет. Но и бросать тебя одного на такое дело не хочется. Говори, что надо сделать.";
		
			link.l1 = "Расскажу, когда придет время.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
			NextDiag.CurrentNode = "Irons_officer";
		break;
	}
} 