// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать вопрос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня полно работы по управлению делами города, а ты всё вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "У меня к вам щекотливое дело. Недавно приходу Бас-Тера неким капером была подарена драгоценность - золотой крест с лазуритом. Беда в том, что этот крест был похищен из прихода Сантьяго, причём при похищении был убит церковный служка...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Я прибыл по приказу генерал-губернатора Филиппа де Пуанси чтобы принять командование над снаряжённым вами фрегатом.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Я готов принять в эскадру фрегат.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "Мне назначена у вас встреча с одним человеком...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Месье, я планирую заняться коммерческой деятельностью в городе. В частности, меня интересует торговля спиртным в крупных объемах, на постоянной основе.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Вы уже всё забрали. Что вам ещё нужно?", "Неужели осталось ещё что-то, что вы не прихватили?");
            link.l1 = RandPhraseSimple("Осматриваюсь напоследок...", "Проверяю, может забыл"+ GetSexPhrase("","а") +" что забрать...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Хм. Очень интересно. Но почему же вы считаете, что проблемы испанцев должны меня волновать?";
			link.l1 = "Дело не в испанцах, месье. Религия не делит людей по национальному признаку. В вашем приходе сейчас находится вещь, политая кровью невинного церковнослужителя, а в отношении прихода Сантьяго совершено святотатство...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "Я прошу вас проявить справедливость и приказать святому отцу вернуть крест тому приходу, которому он принадлежит.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "И с каких это пор вы стали таким ревностным и добропорядочным верующим, а, "+pchar.name+"? Испанцы нам не друзья, и я не считаю должным оказывать давление на святого отца в этом вопросе. Подарен крест - и ладно. Наш священник никакого отношения к грабежу и убийству не имеет, так что...";
			link.l1 = "Ничем не можете мне помочь?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Буду откровенным, "+pchar.name+": и не считаю должным. Я не испытываю любви к этим папистским фанатикам.";
			link.l1 = "Ясно. Простите за беспокойство, месье...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Корабль готов, но у вас нет места для него. Уменьшите вашу эскадру и возвращайтесь, и я сразу передам вам фрегат.";
				link.l1 = "Хорошо.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Да, конечно, корабль готов к выходу в море. Капитан осведомлён и будет выполнять все ваши распоряжения.";
				link.l1 = "Тогда мы отправляемся в путь. До свидания, Ваша Светлость.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Отлично. Принимайте. Капитан осведомлён и будет выполнять все ваши распоряжения.";
			link.l1 = "Тогда мы отправляемся в путь. До свидания, Ваша Светлость.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "А, месье Шарль де Мор, я чуть не позабыл! Да-да, мой старый друг очень желает с вами встретиться и просил оповестить, как только вы явитесь в город. Прошу вас, проходите в малую приёмную, а я немедля пошлю весточку Ангеррану. Кстати, а как вы познакомились?";
			link.l1 = "Играли в карты. Он проиграл, и у нас вышла небольшая ссора. Полагаю, месье де Шиво хочет всё уладить.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "Не сомневаюсь! Надеюсь - вы обо всём договоритесь и устраните то досадное недоразумение, что у вас возникло. Ангерран может и не самый приятный человек, но он умён и благороден, поверьте, такие люди сегодня наперечёт, как и вы.";
			link.l1 = "Вы льстите мне таким сравнением, Ваша Светлость. С вашего позволения, я пройду в гостиную.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "Конечно, располагайтесь, будьте как дома. Возможно, придётся немного подождать. Я прикажу подать напитки.";
			link.l1 = "Благодарю, Ваша Светлость, это излишне. Я просто подожду нашего общего... друга.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Капитан, вы правильно сделали, что обратились ко мне. Мы всеми силами боремся с незаконной торговлей на острове, и я искренне рад, когда ко мне приходят честные капитаны, чтобы всё организовать по закону.";
			link.l1 = "Итак, какие условия и шаги необходимы для начала торговли?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_guber_2":
			dialog.text = "Здесь всё просто. Для торговли спиртным вам нужно будет уплачивать налог в казну, который составляет сто дублонов в месяц, а также вести документацию и регулярно сдавать отчёты о своей деятельности. Как только вы внесёте деньги в казну, можете смело начинать торговлю.";
			link.l1 = "Отлично. Условия вполне приемлемы. От моего имени здесь дела будет вести местный житель - Кристиан Делюш. Надеюсь, с этим не возникнет проблем?";
			link.l1.go = "TPZ_guber_3";
		break;
		
		case "TPZ_guber_3":
			dialog.text = "Как пожелаете, капитан. Однако помните: вся ответственность за вашего протеже ложится на вас, и в случае его проступков вы разделите его участь.";
			link.l1 = "Разумеется. Благодарю за разъяснения, месье губернатор. Мы всё подготовим, и Кристиан уплатит налог.";
			link.l1.go = "TPZ_guber_4";
		break;
		
		case "TPZ_guber_4":
			dialog.text = "Превосходно. Рад видеть столь добросовестный подход. Удачи вам в вашем деле.";
			link.l1 = "Благодарю. Уверен, наше сотрудничество принесёт пользу городу. До свидания.";
			link.l1.go = "TPZ_guber_5";
		break;
		
		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");
			
			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

