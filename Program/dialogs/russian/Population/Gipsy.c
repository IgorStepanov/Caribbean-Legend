//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

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
			dialog.text = "А-а, это опять ты, мил"+GetSexPhrase("ок","ая")+"? Что ты хотел"+GetSexPhrase("","а")+"?";
			link.l1 = "Да нет, пожалуй, ничего.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Мил"+GetSexPhrase("ок","ая")+", позолоти ручку. Всю правду тебе расскажу.","Эй, моряч"+GetSexPhrase("ок","ка")+", не спеши! Хочешь узнать всю правду?","Угости табачком, "+GetSexPhrase("соколик","голубушка")+", и парой серебряных монет, а я загляну в твоё будущее.");
				link.l1 = "Извини, мне пора идти.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Послушай, любезная, я знаю, что вы - знатоки различных зелий. Мне тут шепнули на ушко, что вас здорово интересует вот эта травка. Посмотри.";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Чернобровая, у меня для тебя кое-что есть... Это мангароса. Будешь покупать?";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Ты можешь мне погадать?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Послушай, чернобровая, говорят, ты исцеляешь людей - даже от тяжких болезней. Это правда?";
				link.l6.go = "dwh_gypsy_1";
			}
			// <-- Тёмные воды исцеления
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "А что, чернобровая, не найдётся ли у тебя отравы какой для крыс? Совсем от них житья не стало!";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Конечно, мил"+GetSexPhrase("ок","ая")+". Дай несколько монет и покажи свою правую ладонь - поведаю о том, что ждёт тебя впереди, без обману!";
			link.l1 = "Пожалуй, я передумал"+GetSexPhrase("","а")+". Неохота что-то...";
			link.l1.go = "exit";
			link.l2 = "Сколько денег ты просишь?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "А, мил"+GetSexPhrase("ок","ая")+", это сколько позволит тебе твой кошель и твоё желание.";
			link.l1 = "100 песо.";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 песо.";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 песо.";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 песо.";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ай, спасибо за эти несколько монет, "+GetSexPhrase("соколик","голубушка")+"! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьёзно? Ну что же, запомню...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждёт тебя. Горе, горе насмешнику! Сгустятся чёрные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ай, спасибо, "+GetSexPhrase("соколик","голубушка")+"! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьёзно? Ну что же, запомню...");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждёт тебя. Горе, горе насмешнику! Сгустятся чёрные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ай, спасибо за серебро, "+GetSexPhrase("соколик","голубушка")+"! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьёзно? Ну что же, запомню...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждёт тебя. Горе, горе насмешнику! Сгустятся чёрные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Ай, спасибо за твою щедрость, "+GetSexPhrase("соколик","голубушка")+"! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьёзно? Ну что же, запомню...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждёт тебя. Горе, горе насмешнику! Сгустятся чёрные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Ой не знаю, красав"+GetSexPhrase("ец","ица")+"! Давеча один вот тоже просил крыс примучить, а потом кто-то солдат в форте потравил. Нас две недели на допрос таскали. Чуть из города не погнали, пока не нашли того душегуба. Лазутчиком вражеским оказался.",
				                             "А откуда мне знать, кого ты травить собрал"+GetSexPhrase("ся","ась")+"? Может знатного соперника, с которым боишься на клинках сойтись в честном поединке? ",
											 "Сказывали мне, что в прошлом месяце кто-то отравил в таверне заезжего купца и обобрал до нитки. А купец тот ещё долго мучился пока представился, весь пеной изошёл и синий стал, как баклажан. Не твоих ли рук дело, яхонтов"+GetSexPhrase("ый","ая")+" мо"+GetSexPhrase("й","я")+"?");
				link.l1 = "Вот значит, как ты обо мне подумала! Не волнуйся, людей травить не в моих привычках. Для людей у меня другие средства имеются, а вот против крыс ничего не помогает.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) notification("Вызывающий доверие", "Trustworthy");
			}
			else
			{
				dialog.text = "Ишь, чего удумал"+GetSexPhrase("","а")+"! Нет у меня никакой отравы! Травы есть, отвары есть, а отравы нет.";
				link.l1 = "Ну да ладно..";
				link.l1.go = "exit";
				notification("Не открыта способность", "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Ну ладно, выручу я тебя. Только не говори никому, что это я тебе отраву продала. С тебя "+sti(npchar.quest.poison_price)+" дублонов.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Дороговато, конечно... Ну да ладно, лишь бы помогло.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Да ты что! В прошлый раз за пять золотых брал"+GetSexPhrase("","а")+"! Да за такие деньги я этих крыс сам руками переловлю!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Вот и лови, а ко мне больше не лезь со всякими глупостями. В следующий раз позову солдат.";
			link.l1 = "Не нужно солдат, пойду я.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Показывай, "+GetSexPhrase("соколик","голубушка")+", что там у тебя за травка... Хм... пожалуй, я куплю её у тебя. Три сотни песо тебя устроит?","Покажи мне её, "+GetSexPhrase("дружок","подруга")+"... Хе... ну, две с половиной сотни я тебе за неё, пожалуй, заплачу.","Давай посмотрим... О! Интересный экземпляр! Две сотни серебряных монет! По рукам?")"";
			link.l1 = LinkRandPhrase("Начинается... Чернобровая, я не "+GetSexPhrase("какой-нибудь деревенский простачок","какая-нибудь деревенская простачка")+". Я знаю, что это за травка. Это - мангароса...","Да что ты такое говоришь! Это же мангароса, причём отличный экземпляр. Не пытайся водить меня за нос.","Ага, вот прямо сейчас взял"+GetSexPhrase("","а")+" и отдал"+GetSexPhrase("","а")+" тебе мангаросу за эти гроши...");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Хорошо-хорошо, красав"+GetSexPhrase("чик","ица")+". Вижу, что тебе известно кое-что об этом растении. Пятьдесят дублонов. Давай её сюда.";
			link.l1 = "Ох, да погоди ты! Я хочу узнать, где она применяется, что из неё можно приготовить. Ты можешь поведать мне это? Ведь недаром же вы готовы отваливать золото горстями за этот зелёный куст!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Хм... Ну, пожалуй, никакого страху не будет, если я тебе расскажу немного о ней. Всё равно без специальных знаний у тебя ничего путного не выйдет.";
				link.l1 = "Я в"+GetSexPhrase("есь","ся")+" внимание!";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Золото, может, и готовы отваливать, а вот раскрывать свои тайны - не намерены. ","Золото - золотом, а секреты - секретами, "+GetSexPhrase("соколик","голубушка")+"... ","Платить мы, конечно, готовы, а вот трепать языком почём зря - не станем.")+"Ты будешь продавать мне свою мангаросу? Пятьдесят дублонов - это наша такса за неё, больше тебе никто не даст.";
				link.l1 = "Ох, ладно... Да, буду. Пятьдесят дублонов меня устраивает. Держи.";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Пойми, я не хочу продавать её. Я хочу узнать, почему она вам так нужна. Поделись знаниями, а я отдам тебе этот стебель бесплатно.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Получи свои монеты, "+GetSexPhrase("соколик","голубушка")+". Если найдёшь ещё мангаросы - приноси нам. Правда, покупаем мы только по одному стеблю - большие суммы в дублонах с собой не носим. Уж больно любит к нам цепляться городская стража.";
			link.l1 = "Хорошо. Если встречу ещё - обязательно принесу.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Ишь, чего захотел"+GetSexPhrase("","а")+"! Не хочешь продавать - и не надо, а рассказывать тебе я ничего не буду.","Я не стану выдавать наши секреты посторонним. Не будешь продавать - и чёрт с тобой.",""+GetSexPhrase("Дружок","Подруга")+", это не для твоих ушей. Не хочешь продавать за полсотни дублонов - иди, продай лоточнице за пару сотен песо.");
			link.l1 = LinkRandPhrase("Ну и напрасно! Расскажет кто-нибудь другой из ваших. Он и получит мангаросу в подарок. Бывай!","Что за упрямство? Не расскажешь ты - расскажет другая. Ей я и подарю мангаросу. Прощай.","Что ты так ерепенишься? Я ведь всё равно своего добьюсь. Кто-нибудь из ваших окажется сговорчивей и получит эту мангаросу бесплатно. Пока!");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "Спрашиваешь, "+GetSexPhrase("соколик","голубушка")+"! Конечно! Давай её мне.";
			link.l1 = "Давай пятьдесят дублонов.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Ой! Кажется, я её или потерял"+GetSexPhrase("","а")+", или забыл"+GetSexPhrase("","а")+" на корабле. Какая досада! Извини...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Не бойся, не обману. Получай свои монеты.";
			link.l1 = "Забирай свою мангаросу. Найду ещё - принесу!";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Мы измельчаем это растение особым способом, потом высушиваем, соблюдая определённые условия, а затем смешиваем с табаком в некотором соотношении, набиваем свои трубки и курим. Получаем от этого... незабываемый эффект. Одного стебля хватает на два десятка трубок.";
			link.l1 = "Вот как! А ты можешь научить меня этому? Я хорошо заплачу...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = ""+GetSexPhrase("Соколик","Голубушка")+", поверь - не стоит оно того. Не ввязывайся в это дело, сгубит оно тебя. Даже и не проси. Однако... смотрю я на тебя - "+GetSexPhrase("бравый парень","статная девка")+", с саблей, моря"+GetSexPhrase("к","чка")+"... может, даже капитан?";
			link.l1 = "Ты не ошиблась.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Тогда слушай сюда. Мангаросу можно использовать и для других целей, куда более благородных, и это может очень тебе пригодиться. Секреты этого растения досконально изучила одна наша знахарка. Вот она-то тебе и нужна\nЕсли ты отдашь мне свою мангаросу - я скажу тебе, как её зовут и где искать. А там уже уговаривай её сам"+GetSexPhrase("","а")+", чтобы она с тобой поделилась рецептами своих зелий.";
			link.l1 = "Хорошо. Бери растение и рассказывай, как найти твою знахарку.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Зовут её Амелия. Живет она уединённо, в домике в дюнах недалеко от моря, где-то на юго-западе Мэйна, как говорят учёные люди.";
			link.l1 = "Хм. А поточнее не можешь сказать, где её дом?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Ну ты же моря"+GetSexPhrase("к","чка")+", "+GetSexPhrase("соколик","голубушка")+", а я нет. Поищи хорошенько там, где я сказала. Её дом совсем близко от берега. Там ещё рядом есть какая-то бухта - моряки должны её знать.";
			link.l1 = "Ладно, найду как-нибудь...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Когда отправишься к ней - обязательно имей при себе мангаросу, иначе она даже не станет с тобой разговаривать, да и дублонов прихвати побольше - не думаешь же ты, что она будет учить тебя бесплатно!";
			link.l1 = "Я учту это. Спасибо за рассказ!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Амелия";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_gypsy_1":
			dialog.text = "Правда, "+GetSexPhrase("милок","красавица")+". Ко всякой хвори у меня свой подход. И простолюдинов, и богатеев, и купцов на ноги ставила. Да что там - сам губернатор к моим зельям прибегал, когда никто другой помочь не мог. Болезни, они золота не стращаются, а вот зелий моих - не выдерживают.";
			link.l1 = "Тогда почему ты отказываешься лечить тяжело больную девочку - дочку Томаса Моррисона?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "Кто ж тебе такую небылицу наплёл, "+GetSexPhrase("соколик","голубушка")+"? Помочь-то я не против, только вот отец её сам из дома меня прогнал. Мы уж договорились, что я возьмусь за лечение, а он вдруг как переменился. Выставил меня за порог - будто врага лютого.";
			link.l1 = "Вот как? Значит, он собственноручно обрёк свою дочь на мучения?";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "Что ты, он заботливый отец - сложно представить, почему он мог так поступить.";
			link.l1 = "Ты пыталась снова с ним поговорить?";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "Да он меня и близко к дому не подпускает. Слушай, "+GetSexPhrase("милок","красавица")+", раз уж тебе не безразлична судьба бедной девчушки, может, попробуешь узнать, в чём дело? Поговори с Томасом - помоги мне спасти дитё от страданий.";
			link.l1 = "Разумеется, я помогу. Где мне найти Томаса?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "Нет, чернобровая. Как бы там ни было, я думаю, что у её отца есть веские причины отвергать твою помощь. Я не стану в это ввязываться. Пускай он сам решает - это ведь его дочь.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "Их дом находится у стены, в северной части города, рядом с роскошным особняком с колоннами. Ступай, "+GetSexPhrase("соколик","голубушка")+", поговори с ним и возвращайся ко мне.";
			link.l1 = "Скоро вернусь.";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			
			AddQuestRecord("DWH", "2");
			
			sld = GetCharacter(CreateCharacterClone(npchar, -1));
			sld.id = "DWH_gypsy";
			npchar.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_Tomas", "citiz_13", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Томас";
			sld.lastname = "Моррисон";
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas";
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "goto", "goto1");
			sld.City = "SentJons";
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "повезёт тебе, "+GetSexPhrase("соколик","голубушка")+", завтра непременно в карты повезёт!" break;
		case 1: sText = "в загаданном деле тебя ожидает удача, капитан!" break;
		case 2: sText = "в открытом море неудача таится, именно тебя ждёт, подожди три дня!" break;
		case 3: sText = "вижу, необходимо тебе искать помощи близких людей, од"+GetSexPhrase("ин","на")+" в следующем бою не выживешь!" break;
		case 4: sText = "сходи, поставь свечку в церкви, проклял тебя недруг. Без божьей помощи не справишься!" break;
		case 5: sText = "потеряешь вскоре многое, но всё-таки отчаиваться не надо - надейся на собственные силы, ищи помощи друзей..." break;
		case 6: sText = "потеря тебя ожидает, в море, но вижу я - сумеете, капитан, если и не добиться желаемого, то возместить потраченные силы и средства при других обстоятельствах." break;
		case 7: sText = "ты вступил"+GetSexPhrase("","а")+" в полосу неудач, капитан! "+GetSexPhrase("Сходи в бордель, развейся","Развейся")+"." break;
		case 8: sText = "твоё желание хоть и будет исполнено, однако же ничего хорошего ждать от этого не придётся: то, чего ты так страстно хотел"+GetSexPhrase("","а")+", кэп, принесёт одни неприятности, и лучше отказаться от задуманного." break;
		case 9: sText = "вижу на челе твоём отблеск абсолютной удачи: сбудется даже больше того, на что рассчитывал"+GetSexPhrase("","а")+", "+GetSexPhrase("соколик","голубушка")+"!" break;
		case 10: sText = "тебе необходимо заново оценить своё желание и решить, необходимо ли его исполнение: судьба даёт шанс подумать." break;
		case 11: sText = "это редкое везение - не так часто у нас есть шанс передумать. Просто отдохни денёк, ясноглаз"+GetSexPhrase("ый","ая")+", подумай о бренном. Не спеши на смерть!" break;
		case 12: sText = "хотя все затраченные вами усилия и не принесут ожидаемого результата, отчаиваться не стоит - в самый неожиданный момент тебя ждёт удача, не пропусти её!" break;
		case 13: sText = "твой конкретный вопрос не будет решён положительно, но ты упрям"+GetSexPhrase("","а")+", всё равно получишь своё, но, может быть, вовсе не оттуда, откуда ожидал"+GetSexPhrase("","а")+"." break;
		case 14: sText = "лучше забудь о том деле, которым занят"+GetSexPhrase("","а")+" - удачи тебе в нём никогда не будет, а если продолжишь настаивать, то, возможно, пострадают или даже погибнут твои спутники." break;
		case 15: sText = "впереди тебя ожидает событие, капитан, которое настолько круто переменит твою жизнь, что всё сейчас происходящее не будет иметь никакого значения!" break;
		case 16: sText = "на пути к исполнению твоего желания тебя подстерегает опасность, и тебе очень повезёт, если сумеешь добиться того, чего хотел"+GetSexPhrase("","а")+", ничего не потеряв, капитан. Лучше, пока не поздно, свернуть с пути и забыть мечту недостижимую. Хотя, если прямо сейчас в кости или карты проиграть, то судьбу можно обмануть..." break;
		case 17: sText = "вижу силу в тебе могучую, как скала, и свет яркий, как звёзды, что людей за собой поведёт. Хороший знак и добрая весть тебя ждут." break;
		case 18: sText = "знак недобрый на твоём пути встанет, опасайся дурного глаза, и держи поближе верных людей." break;
		case 19: sText = "счастливый случай дожидается тебя чуть не за спиной. Ищи то, что само идёт в руки, и не гонись за несбыточным." break;
	}
	return sText;
}
