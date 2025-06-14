// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Что вам нужно?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Добрый день. Полагаю, вы - "+GetFullName(pchar)+". Я не ошибся?";
			link.l1 = "Всё верно, месье Лекруа. Капитан "+GetFullName(pchar)+" к вашим услугам. Меня рекомендовал вам Фадей Московит...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Да-да, дорогой Фадей очень точно описал вас - я с порога понял, что это именно вы. Скажите, капитан, что у вас за корабль?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Эм-м... У меня на данный нет корабля, месье... Это временно.";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "У меня "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+", называется - '"+pchar.ship.name+"'.";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ха! Ну так какой же вы капитан, если у вас нет даже корабля? Извините, месье, но в таком случае никакой работы у меня для вас нет. Всего доброго, передавайте привет Фадею!";
			link.l1 = "Гм...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "в данный момент я был без корабля";
		break;
		
		case "lecrua_badship":
			dialog.text = "Ну, это совсем несерьёзно. Какой же это корабль? Это просто большая лодка! Увы, месье, но вы мне не подходите. Всего доброго, передавайте привет Фадею!";
			link.l1 = "Гм...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "мой корабль не устроил этого хлыща";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "Мы ведь уже всё с вами обсудили, месье, разве не так?";
			link.l1 = "Да-да, месье Лекруа... Я уже иду.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Превосходно. В таком случае вы мне подходите. Вы готовы отправиться в путь немедленно?";
			link.l1 = "Да, месье, готов. Что я должен сделать?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Вы должны доставить небольшую партию пороха и бомб в форт Порт-о-Пренса, это на французской Эспаньоле. Комендант уже заждался этот груз, так что вам не следует терять времени - у вас в распоряжении не более десяти дней\nУважаемый "+GetFullName(sld)+" позаботится о погрузке указанного груза на борт вашего судна. Оплату за фрахт получите у коменданта форта - пять тысяч песо.";
			link.l1 = "И это вся работа?..";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Нет, конечно, месье. Основную задачу вам объяснит комендант, которому вы повезёте порох и бомбы, по прибытии. Этот фрахт - всего лишь малая часть работы, которая вам предстоит. Так что не расстраивайтесь: если проявите старание - сможете хорошо заработать.";
			link.l1 = "Отлично! Я очень рад открывшейся перспективе. Моё судно готово принять груз на борт.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Тогда не будем терять времени, капитан! Отправляйтесь на свой корабль и готовьтесь к выходу в море.";
			link.l1 = "Уже иду!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Режим исследования: таймер отключён.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "Что вам угодно, сударь?";
			link.l1 = "Добрый день, капитан. Как я понимаю, вы - Флориан Шоке?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Вы не ошиблись. А, я, кажется, понимаю: вы - курьер из Порт-о-Пренса, так?";
			link.l1 = "Именно! Я доставил вам пятнадцать орудий. Летел как на крыльях, еле успел...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Хм. Странные у вас шутки, сударь! Что-то я не вижу на вашем корыте достаточного количества орудий для моего корабля.";
				link.l1 = "Чёрт побери! Мы получили пробоину и часть груза выбросили за борт...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Рад вас видеть, капитан?..";
				link.l1 = ""+GetFullName(pchar)+". Капитан "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Приятно познакомиться. Не будем терять времени и приступим к перегрузке орудий на мой корабль - чёрт возьми, это будет очень непросто!";
			link.l1 = "Как нибудь справимся. Главное - задействовать побольше людей...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "И как только подобное дело доверили такому недотёпе? Отправляйтесь на свой корабль, капитан, и займитесь чем-нибудь, что больше вам подходит: пассажиров возите, или товары по магазинам. И то, сомневаюсь, что это у вас получится. Всего доброго!";
			link.l1 = "Но...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Ну вот, закончили... Благодарю за службу, капитан! Примите вашу награду - двести дублонов.";
			link.l1 = "Спасибо!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			//Log_Info("Вы получили 200 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Но это ещё не всё, капитан. Хотите заработать ещё двести пятьдесят монет?";
			link.l1 = "Ха! А кто же не хочет пополнить карман! Но смотря что вы попросите за это сделать...";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Задача довольно опасная, не скрою. Как вы наверняка знаете, я тут подстерегаю испанский тяжёлый галеон с ценным грузом. Этот корабль был поставлен в доки на починку. По моим сведениям, он должен был встать на рейд и готовиться к выходу в море ещё вчера, однако этого не произошло\nКроме того, мой агент в Порто Белло так и не пришёл для передачи собранных сведений в условленную бухту. Я подозреваю, что испанцы его схватили. Вам следует пробраться в Порто Белло и попытаться разузнать две вещи: почему галеон до сих пор находится в доках и что случилось с моим агентом. Вы готовы?";
			link.l1 = "Боюсь, у меня нет должной подготовки для дела такого рода. Я и сам попадусь, и вам помочь не смогу. Увы, но - нет.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Опасность велика, но всё же я рискну. Каково имя вашего человека и как называется галеон?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Что же, это ваше право. Я вас понимаю. Тогда до свидания, капитан, и ещё раз спасибо за помощь!";
			link.l1 = "Всего доброго, месье Шоке.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "Отлично! Агента зовут Сильвен Лафоре, но в Порто Белло он представился как Хайме Силисио, торговец. Галеон носит имя 'Алькантара'. Советую пробираться в город ночью, через джунгли - стража в Порто Белло сейчас очень подозрительна, да и исчезновение Сильвена тоже наводит на неприятные мысли. Времени на операцию у вас не более двух суток. Удачи, месье! И возьмите этот амулет - говорят, что он отводит глаза городской страже.";
			link.l1 = "Скоро увидимся, месье Шоке...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Режим исследования: таймер отключён.");
			// <-- legendary edition
			//Log_Info("Получен амулет 'Веер цыганки'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Старайтесь двигаться шагом. Тогда стражники будут менее подозрительны!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "Мы ведь уже всё обсудили, капитан, разве не так?";
			link.l1 = "Да-да, я уже иду...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Как успехи, капитан? Что удалось узнать?";
			link.l1 = "Успехи мои весьма посредственны, месье Шоке. Всё-таки шпион из меня неважный - раскрыли меня очень быстро. Пришлось вырываться из города с боем. Единственное, что мне удалось узнать - что ваш человек, Сильвен Лафоре, арестован и находится в тюрьме.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Чёрт возьми! Это плохие новости... Про галеон ничего не узнали?";
			link.l1 = "Ничего.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Жаль. Мне очень нужна информация о нём. Ладно, попробую послать ещё одного лазутчика... Капитан, я предлагаю вам пока не уходить отсюда. Возможно, мне потребуется ваша помощь. Подождёте денек-другой, пока я выведаю что-нибудь об 'Алькантаре'?";
			link.l1 = "Хм. Конечно, подожду! Я буду очень не прочь реабилитироваться за провал.";
			link.l1.go = "florian_9";
			link.l2 = "Нет, пожалуй. Видимо, подобные игры не для меня. Я отправляюсь восвояси.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Что же, это ваше право. Всего доброго, капитан.";
			link.l1 = "Прощайте, месье Шоке.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Как успехи, капитан? Что удалось узнать?";
			link.l1 = "Успехи мои весьма посредственны, месье Шоке. Всё-таки шпион из меня неважный. Единственное, что мне удалось узнать - что ваш человек, Сильвен Лафоре, арестован и находится в тюрьме.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Тогда отправляйтесь на ваш корабль, а завтра, примерно в это же время, или немного позже, поднимитесь ко мне на борт. Может, к тому времени я что-нибудь разузнаю. На берег не суйтесь, ждите у себя на судне!";
			link.l1 = "Хорошо. Так и поступим.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "И, капитан: возьмите этот кошель. Ведь всё-таки ваши труды не были напрасны - по крайней мере, мы знаем, что случилось с беднягой Сильвеном...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			//Log_Info("Вы получили кошель с дублонами");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Капитан, пока никаких новостей у меня нет. Ждём...";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Как успехи, капитан? Что удалось узнать?";
			link.l1 = "Мой поход оказался успешным - мне удалось узнать много интересного. Ваш человек, Сильвен Лафоре, арестован и находится в тюрьме. Его раскусили.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Чёрт возьми! Это очень плохо... Про галеон что-нибудь удалось узнать?";
			link.l1 = "Да. Он уже давно готов к выходу в море, но губернатор Порто Белло намеренно держит его в доках. Сейчас он ждёт прибытия из Картахены баркентины 'Пуэбла' с грузом пороха для 'Алькантары'. Судя по словам матроса с галеона, у них нехватка пороха.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Очень интересно!";
			link.l1 = "Но если 'Пуэбла' не придёт за ближайшие три дня - то 'Алькантара' не будет её ждать и отправится в путь.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Великолепная работа, капитан! Я очень доволен вами. Вот, возьмите ваше вознаграждение. Вы его честно заработали!";
			link.l1 = "Благодарю! У вас есть ещё задания для меня?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			//Log_Info("Вы получили 250 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Вы читаете мои мысли, капитан! Да, есть, чёрт возьми! Раз на 'Алькантаре' недостаточно пороха, то я могу её отпустить подальше в море и затем принудить вести затяжной морской бой, в котором они израсходуют свои запасы раньше нас. Это весьма облегчит мою задачу\nВам нужно сделать так, чтобы эта баркентина, 'Пуэбла', не дошла до Порто Белло. Я не могу расхаживать на фрегате вдоль побережья - береговая охрана легко заметит мой корабль, и тогда я вообще могу не дождаться 'Алькантары'\nА вы вполне справитесь с этой баркентиной. Отыщите её и уничтожьте: потопите, абордируйте - мне всё равно. Лишь бы это корыто не добралось до Порто Белло!\nЕсли вы успешно выполните эту задачу - отправляйтесь на Гваделупу и идите к Жерару Лекруа - ведь вы знаете его, так? Он выдаст вам заслуженный гонорар.";
			link.l1 = "Договорились! Отправляюсь на перехват 'Пуэблы'!";
			link.l1.go = "florian_19";
			link.l2 = "Подождите немного, месье Шоке. Дело в том, что я пока... Скажем так, не особо привычен к морским боям. А вы - капитан фрегата, у вас за плечами явно не одно морское сражение. Если вам не сложно, вы могли бы... Как бы это правильно сказать...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Очень хорошо, что вы пришли, капитан. Я как раз получил важные сведения от своего лазутчика и у меня есть для вас ответственное поручение.";
			link.l1 = "Слушаю вас внимательно.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "'Алькантара' готова к выходу в море, однако капитан галеона ждёт прибытия баркентины 'Пуэбла' из Картахены с грузом боеприпасов. Дело в том, что на 'Алькантаре' недостаточно пороха, и испанец не решается отправиться в путь. Однако терпение его не безгранично, и если 'Пуэбла' не прибудет через три дня, галеон покинет Порто Белло\nНа нём будет нехватка пороха, и я смогу навязать ему затяжной морской бой, в котором буду иметь преимущество. Ваша задача - перехватить 'Пуэблу' и уничтожить её. Потопите, абордируйте - мне всё равно. Лишь бы это корыто не добралось до Порто Белло!\nЕсли вы успешно выполните эту работу - отправляйтесь на Гваделупу и идите к Жерару Лекруа - ведь вы знаете его, так? Он выдаст вам заслуженный гонорар.";
			link.l1 = "Договорились! Отправляюсь на перехват 'Пуэблы'!";
			link.l1.go = "florian_19";
			link.l2 = "Подождите немного, месье Шоке. Дело в том, что я пока... Скажем так, не особо привычен к морским боям. А вы - капитан фрегата, у вас за плечами явно не одно морское сражение. Если вам не сложно, вы могли бы... Как бы это правильно сказать...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "Провести вам небольшой ликбез по тактике морского боя? С радостью, капитан! Тем более, что это в моих же интересах: я хочу быть уверенным в том, что вы успешно выполните задачу по перехвату 'Пуэблы'.";
			link.l1 = "Нет, я не это имел в виду. Ладно, забудьте: уверен, что проблем с перехватом какой-то баркентины у меня не возникнет.";
			link.l1.go = "florian_19";
			link.l2 = "Да, именно это я и имел в виду. Уверен, что новые знания мне не повредят.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Итак, первое, что вам необходимо запомнить: половина сражения выигрывается или проигрывается ещё до его начала. Очень много зависит от того, насколько вы и ваш корабль к нему готовы.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Для начала позаботьтесь о том, чтобы ваш корабль был отремонтирован. Если у вас пробоины в корпусе, то противнику, как вы понимаете, не составит труда отправить вас на дно. А если у вас вместо парусов висят лохмотья, то это очень существенно ограничивает вашу мобильность. Противник с лёгкостью сможет уйти от вас, если соотношение сил будет не в его пользу, или, наоборот, догнать вас и навязать невыгодный вам бой - или вообще сразу взять на абордаж. Кроме того, с порванными парусами особо не выберешь позицию, не повернёшься нужным бортом.";
			link.l1 = "Понимаю. Что ещё?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Следите за тем, чтобы у вас было достаточно команды. Даже самый мощный корабль с 42-фунтовыми орудиями становится бесполезным, если на три пушки у вас приходится по одному канониру, а парусами попросту некому управлять. Я бы вообще просто сразу взял такое судно на абордаж.";
			link.l1 = "Понял. Буду следить за количеством матросов на корабле.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Кроме того, следите за своими орудиями: они не служат вечно. Со временем они портятся, и если ваши пушки начнут в разгар сражения взрываться, это может очень плохо для вас кончиться. А мне вообще не повезло: партия орудий оказалась с браком отливки. Если бы вы не успели вовремя привезти замену, мне бы пришлось просто отказаться от операции, поскольку 'Воинственный' сильно уступал бы 'Алькантаре' в огневой мощи. Орудия нужно вовремя менять.";
			link.l1 = "Теперь понимаю, почему это было так важно!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "Помимо орудий следите также за количеством боеприпасов. 'Алькантара' именно на этом и попадётся: если у неё мало пороха, она не сможет вести долгое сражение - ей нужно сразу переходить в ближний бой. И на этом я сыграю: мой фрегат быстрее, тяжёлый галеон от него уйти не сможет. Но и близко подходить мне тоже нет нужды: я навяжу длительную артиллерийскую дуэль на дальней дистанции, а потом, когда порох на 'Алькантаре' кончится, я просто пойду на абордаж. Будет сопротивляться - 'промою' предварительно палубы картечью.";
			link.l1 = "Безвыходная ситуация...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Именно. Поэтому следите за количеством пороха и боеприпасов. Кончатся ядра - и потопить вражеское судно вы уже, скорее всего, не сможете. Кончится картечь - можете не надеяться на абордаж, если команды у вас меньше. Не будет книппелей - не сможете догнать противника или уйти от него, если он быстрее. Все боеприпасы важны.";
			link.l1 = "Поучительно, спасибо.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "Ну, и последнее: в зависимости от типа и размера вашего корабля и судна противника применяйте соответствующую тактику сражения. На большом и медлительном судне нет смысла гоняться за бригом или корветом для последующего абордажа - без предварительной обработки книппелями всё равно не догоните. В таких случаях иногда лучше просто открыть огонь на потопление. Если всё-таки необходимо взять такое судно на абордаж - предпочтительно использовать для этого быстрый и манёвренный корабль.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "Старайтесь не соваться под бортовую батарею мощных кораблей на хлипком судне. Используйте преимущество в скорости и манёвренности, обстреливайте книппелями и картечью, если всё-таки нужно брать на абордаж. Если нужно потопить... Ну, это будет задача не из лёгких. Вообще, в таких случаях не будет позорным бегство. Хороший капитан сбережёт корабль и команду от верной смерти вместо излишнего героизма.";
			link.l1 = "Всё усвоил. Большое спасибо, месье Шоке!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Рад помочь, капитан. Надеюсь, эти знания помогут вам в будущем.";
			link.l1 = "Уверен, что помогут. Отправляюсь на перехват 'Пуэблы'!";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение
		
		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "Так, кто это тут у нас? Очередной французский шпик? Очень интересно! Ты хотел видеть Хайме Силисио? Ну что же, я предоставлю тебе такую возможность в нашей тюрьме. Взять его!";
			link.l1 = "А-аргх! Ну, попробуйте!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}