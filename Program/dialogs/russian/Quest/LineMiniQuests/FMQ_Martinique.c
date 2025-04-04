// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+", капитан. Позвольте представиться - "+GetFullName(npchar)+". Хотя мы с вами не так давно виделись, но вы вряд ли меня запомнили.";
			link.l1 = "Здравствуйте, месье. И где же я мог вас видеть?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "люггер 'Аделина'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "шлюп 'Чёрный пёс'";
			dialog.text = "На нашей верфи. Не так давно вы приобрели у нас корабль, "+sTemp+". Припоминаете? Я плотник с верфи Сен-Пьера.";
			link.l1 = "Да, я действительно приобрёл этот корабль. Так что вы хотели, месье "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "Наш мастер, месье "+GetFullName(sld)+", хочет с вами поговорить - у него какое-то предложение для вас. Он увидел ваше судно на рейде и отправил меня найти вас. Так что не откажите в милости - загляните к моему хозяину.";
			link.l1 = "Хорошо. Как сделаю все свои дела в городе, навещу вашего мастера.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("VOICE\Russian\soldier_arest_4.wav");
			dialog.text = "Так-так... Контрабандисты застигнуты на месте преступления!..";
			link.l1 = "Э...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "И не пытайтесь здесь отпираться! В подсобном помещении верфи стоит несколько десятков бочек с природной смолой. Вы, капитан, её привезли и сбыли своему сообщнику. Вы оба арестованы, а товар я конфискую, именем закона!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Не валяйте дурака, мастер! 'Какие бочки'! Вы отлично знаете, какие бочки стоят у вас в подсобке! Те, которые вы только что сгрузили с корабля этого моряка. Я упеку вас обоих за контрабанду в тюрьму! А ну...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("VOICE\Russian\soldier\soldier arest-02.wav");
			dialog.text = "Эта смола, дорогой 'мастер-корабел', является стратегическим товаром, и её оборот находится под строгим контролем губернатора! Но раз вы утверждаете, что это ваша смола - будь по-вашему. Вы арестованы, месье "+GetFullName(characterFromId("FortFrance_shipyarder"))+", и сейчас отправитесь за решётку, а завтра дадите объяснения, откуда у вас взялись эти бочки! И не беспокойтесь, мы во всём разберёмся! А вы, капитан, можете быть свободны. Сегодня вам повезло.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
			dialog.text = "Недаром это судно показалось мне подозрительным... Похоже, я недооценил вас, капитан.";
			link.l1 = "Точно, лейтенант. Не на дурака напали. Ваше 'сотрудничество' с мастером верфи не осталось для меня тайной.";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "Вижу. Поздравляю, вы проявили редкую проницательность и смекалку, раз сумели взять меня врасплох. Чего же вы желаете, капитан?";
			link.l1 = "А разве непонятно? Мне нужна моя смола, которую вы на пару с жуликом-корабелом реквизировали у меня.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "Хорошо. Я отдам вам вашу смолу. Но у меня её ровно половина от того количества, которое вы привезли в Сен-Пьер. Надеюсь, вас это удовлетворит, ибо большего предложить я не могу.";
			link.l1 = "Вы меня продолжаете держать за дурака? Нет второй половины - компенсируйте её стоимость деньгами, или теми товарами, что лежат в куче у меня за спиной.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Это исключено. По поводу второй половины обращайтесь к известному вам лицу.";
			link.l1 = "Вы издеваетесь? Вы серьёзно полагаете, что "+GetFullName(characterFromId("FortFrance_shipyarder"))+" отдаст мне мои бочки? Не смешите меня!";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Капитан, забирайте какую есть смолу и свою жизнь впридачу, и убирайтесь прочь. К этой сделке я добавляю своё обещание не чинить вам козней в Сен-Пьере. Большего вы не получите.";
			link.l1 = "Вы дарите мне мою жизнь? Ха-ха!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "Похоже, вы ещё не остыли после схватки, капитан. Разъясняю: вы уложили шайку салаг, но против моего отряда у вас шансов нет. Я мог бы вас спокойно прирезать в этой бухте, не предлагая никаких сделок, но мне дороги мои люди, которые могут случайно погибнуть или получить ранения, пока будут убивать вас. Так что или вы принимаете моё весьма щедрое предложение, или останетесь здесь навсегда. Выбирайте.";
			link.l1 = "Чёрт вас подери, лейтенант, но я вынужден согласиться. Похоже, что сила не на моей стороне.";
			link.l1.go = "officer_13";
			link.l2 = "Вы весьма самонадеянны, лейтенант. Пожалуй, стоит преподать вам и вашим наёмникам хороший урок, смолёный пёс!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "Вы разумный человек, капитан. Забирайте свои бочонки и отчаливайте. Предупреждаю сразу - доносить на меня губернатору смысла не имеет. Сегодня же мой схрон будет перенесён в другое место. Так что не тратьте своё время напрасно.";
			link.l1 = "Я и не думал на вас жаловаться - отлично понимаю, что это бесполезно.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Поторопитесь, у меня нет лишнего времени.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("VOICE\Russian\LE\Greguar\Greguar_02.wav");
			dialog.text = "О! Кого я вижу! Приветствую, монсеньор! Загулялись допоздна, да?";
			link.l1 = "Доброй ночи, уважаемый... а, это вы! Я вас вспомнил - мы с вами познакомились в мой первый день прибытия на Карибы. Месье Грегуар Валинье.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Рад, что вы меня не забыли. Как я вижу, вы теперь - капитан. Капитан "+GetFullName(pchar)+". Примите мои поздравления.";
			link.l1 = "Благодарю, месье...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "Да вы сам не свой, капитан. Что тут произошло? У вас неприятности?";
			link.l1 = "Да вроде того...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Монсеньор, давайте не будем стоять посреди улицы, а пойдём в таверну. Выпьем по кружечке. Там и поведаете, что у вас за беда. Ну же, идёмте!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Наливайте, капитан...";
			link.l1 = "Давайте...";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Угх... Ну а теперь рассказывайте - что у вас стряслось? У вас такой вид, будто вас собрались повесить.";
			link.l1 = "Да тут такое дело, месье Грегуар... Скажем, некоторые неприятности по роду работы...";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Капитан, мне вы можете рассказывать всё, что угодно. Я не побегу доносить на вас коменданту или губернатору, уж поверьте. Или вы сомневаетесь?";
			link.l1 = "Нет, монсеньор, не сомневаюсь.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "Тогда облегчите душу. Вдруг я смогу вам помочь.";
			link.l1 = "Корабел с местной верфи нуждался в особом товаре - смолах, и нанял меня 'пощипать' караван испанцев из Сан-Хосе. Обещал хорошо заплатить, по полтора десятка дублонов за бочку. Я отыскал этот конвой, отбил 'испанца' со смолами, привёз товар сюда. Судно моё поставили в доки на ремонт и попутно выгрузили бочонки на верфь. И только мы закончили - врывается этот офицер... И как он пронюхал?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "Короче, накрыли нас с поличным. Надо отдать должное корабелу - он взял всё на себя, сказал, что это его смолы, а я ни при чём. В итоге мастера арестовали, увели, а денежки мои плакали. Весь сыр-бор с испанским караваном был напрасен. Ладно, хоть тюрьмой дело не закончилось. Наливайте ещё, месье Грегуар.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "Так что - мастер-корабел арестован?";
			link.l1 = "Ну да. Его вёл тот самый офицер, они вышли из здания верфи передо мной. Вы должны были их видеть.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Да, я их видел, но мне даже и в голову не пришло, что лейтенант Фелисьен Грони мог арестовать своего старого друга.";
			link.l1 = "Что... Что вы сказали?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Вы не ослышались. Лейтенант Фелисьен Грони, который выходил с верфи перед вами, и хозяин верфи "+GetFullName(characterFromId("FortFrance_shipyarder"))+" - друзья. Вроде они как в Европе вместе служили. Грони остался в армии, а "+GetFullName(characterFromId("FortFrance_shipyarder"))+" сумел открыть собственное дело.";
			link.l1 = "Так они знакомы... Вот оно что...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "Похоже, мой дорогой "+pchar.name+", перед вами разыграли спектакль в расчёте на то, что вы тут человек новый. Бьюсь об заклад на сотню золотых дублонов, что не пройдёт и трёх дней, как месье "+GetFullName(characterFromId("FortFrance_shipyarder"))+" будет спокойно расхаживать по своей верфи.";
			link.l1 = "Похоже на то, что вы правы, монсеньор. Меня провели. Этот лейтенант никак не мог сам узнать про смолу. И появиться как раз вовремя.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "Это Карибы, месье "+pchar.name+". Привыкайте. Внешний вид ни о чём не говорит - самые отъявленные мерзавцы одеты в камзолы и кружева.";
			link.l1 = "Где-то я уже это слышал... Но что же мне сделать с этими жуликами? Пойти, доложить губернатору?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "Боюсь, что в этом случае месье "+GetFullName(characterFromId("FortFrance_shipyarder"))+" внезапно перестанет вас выгораживать, и пойдёте вы, как соучастник.";
			link.l1 = "Логично. Хорошо же! Раз по закону сделать ничего нельзя, буду делать не по закону, разрази меня гром! Я этого так не оставлю!";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "Не горячитесь, "+pchar.name+". Сейчас в вас говорит злость и ром. Остыньте. Выспитесь, отдохните, а завтра с утра хорошенько подумайте, что вам делать, и не лучше ли смириться с потерей и не искушать судьбу. Лейтенант Фелисьен Грони и "+GetFullName(characterFromId("FortFrance_shipyarder"))+" - люди влиятельные, и вам не по зубам. Не наделайте глупостей.";
			link.l1 = "Мы ещё посмотрим. Спасибо, что раскрыли мне глаза, монсеньор. Очень хорошо, что я вас встретил.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Будьте осторожны, месье. Помните, что я вам сказал.";
			link.l1 = "Я учту это. А теперь выпьем ещё по кружечке - и пора на боковую!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("VOICE\Russian\LE\Greguar\Greguar_03.wav");
			dialog.text = "Капитан "+GetFullName(pchar)+"!";
			link.l1 = "О, месье Грегуар! Снова вы!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Да, монсеньор. После нашего разговора в таверне я немного подумал, и... позволил себе немного навести справки о действиях лейтенанта Фелисьена Грони. Так вот, на следующий же день лейтенант подал ходатайство на десятидневный отпуск, которое было одобрено. Сегодня утром я увидел, что месье Фелисьен Грони сел в шлюпку и отправился к стоящей в порту тартане, которая вскоре подняла паруса, вышла в море и взяла курс на север, к Гваделупе\nЯ сразу же решил отыскать вас. Таким образом, я передаю вам эту информацию, а вы думайте, что делать дальше. Уверен, что лейтенант неспроста взял отпуск и отбыл с Мартиники на новенькой тартане под названием 'Топаз', едва сошедшей со стапелей нашей верфи.";
			link.l1 = "Я тоже в этом уверен, разрази меня гром! В трюме этой тартаны наверняка лежат мои смолы! Месье Грегуар - вы настоящий джентльмен. Как мне отблагодарить вас?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "О, полно, друг мой. Мы, дворяне, должны всегда помогать друг другу. Это наш долг. Думаю, на моём месте вы поступили бы точно так же. Не теряйте времени, выходите в море и ищите тартану Фелисьена Грони в северном направлении. Нападать не спешите - лучше проследите, куда он направляется и что задумал. Торопитесь, капитан!";
			link.l1 = "Ещё раз огромное спасибо, монсеньор!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "Ну, чего уставился? Что тебе тут надо?";
			link.l1 = "Приятель, я пришёл за своим добром. В бочках, стоящих у вон той кучи - моя смола, которую я добыл и за которую мне не заплатили.";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "Ты с пальмы рухнул, или просто нарываешься? Вали отсюда, пока цел!";
			link.l1 = "Я слишком много сил приложил для добычи этой смолы, чтобы кучка гнусного отребья смогла меня остановить.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Сейчас мы тебя угомоним, пижон!";
			link.l1 = "Сейчас на свете станет на несколько мерзавцев меньше!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
