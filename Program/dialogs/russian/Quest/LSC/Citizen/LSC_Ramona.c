// Рамона Лоцано - горячая испанская сеньорита
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Привет-привет! Новичок? Или прятался где-то по трюмам, что я тебя в первый раз вижу?";
				link.l1 = TimeGreeting()+". По трюмам прятаться - это как-то не в моих правилах. Я предпочитаю капитанский мостик... Да, я недавно здесь.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+pchar.name+"! "+TimeGreeting()+"! Рада тебя видеть! Что скажешь?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у тебя дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ну тогда давай знакомиться... капитан. Я - Рамона Лоцано, но не вздумай называть меня 'сеньорита Лоцано', я этого терпеть не могу. А тебя как зовут?";
			link.l1 = ""+GetFullName(pchar)+". Рад знакомству, Рамона.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Ты действительно рад, или просто вежливый, "+GetFullName(pchar)+"? Скажи, а ты и правда капитан, или так, шутил?";
			link.l1 = "Ого, сколько вопросов сразу! Можно по порядку? Во-первых, я действительно рад - не каждый день удаётся знакомиться с красивыми девушками, а во-вторых - я правда капитан. Однако мой корабль сейчас у берегов Западного Мэйна...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Вот забавно! И как же это так вышло, а, капитан? Ты тут, а корабль твой у берегов Мэйна. Не боишься, что команда разбежится, или лоханку твою уведут?";
			link.l1 = "Я отправился на баркасе в... разведку, однако сие мероприятие пошло не так, как задумывалось, и я очутился у берегов вашего Острова. Потом мы в темноте наскочили на какой-то обломок, перевернулись, и - вуаля, я здесь. А корабль мой будет дожидаться столько, сколько надо - Данни Хоук сумеет присмотреть за командой.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Данни Хоук?! Сама Даниэль Хоук? Ты что, хочешь сказать, что плаваешь с ней?";
			link.l1 = "Плавают известные продукты жизнедеятельности, а Данни служит у меня офицером. Сейчас она осталась за старшую, пока меня нет... А ты откуда её знаешь?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ха! Кто же в испанских колониях не знает пиратов Даниэль Хоук и её мужа, Натаниэля! Да ты, сеньор "+GetFullName(pchar)+", похоже, крутой парень... Ты тоже пират? Не переживай, я к вашей братии отношусь нормально. Мне нравятся крутые парни.";
			link.l1 = "Ну, не то что пират... Просто сейчас работаю вместе с Яном Свенсоном, и разыскиваю мужа Данни, Натаниэля.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "И после этого ты будешь мне рассказывать, что ты не пират? Работаешь на Лесного Дьявола, старпом - Данни Хоук, ищешь Натана Хоука... а на Остров ты наверняка явился к адмиралу. Так?";
			link.l1 = "Рамона, если тебе нравится считать меня пиратом - пожалуйста, я не возражаю. Хоть якорем назови, только в воду не бросай...";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Похоже, ты и впрямь из серьёзных ребят, "+pchar.name+". Ладно, мне пора идти. Ещё увидимся! Мне почему-то кажется, что мы с тобой можем подружиться... близко подружиться.";
			link.l1 = "Всё может быть. Удачи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Да что ты такое говоришь! Ну, спрашивай, если смогу - отвечу...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "А как ты-то попала сюда?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Ты, конечно, никогда не пыталась отсюда выбраться назад...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Как тебе здесь живётся?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "А чем ты занимаешься на Острове? Ведь, как я понимаю, еда тут не бесплатная...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извини...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Это долгая история... Во всём виноват мой отчим. Ещё каких-то четыре года назад я жила в Гаване и даже представить себе не могла, что жизнь так лихо закрутится. Всё началось после того, как умерла моя матушка. Мы были не то что богатые, но... деньги водились, причём значительная часть состояния досталась по закону мне. Отчиму это не понравилось, и он задумал устранить меня\nКонечно, я узнала об этом только потом, когда на меня напали за городскими воротами два проходимца. Эти глупцы сами и сказали мне, и кто их нанял, и почему они собираются меня прикончить. На моё счастье, они не были профессиональными убийцами - иначе лежать бы мне в зарослях с перерезанным горлом - а просто тупоголовыми мерзавцами, и захотели сначала позабавиться\nОднако судьба решила иначе - по тропе в город направлялся незнакомец, как оказалось - капитан, вроде тебя. Он увидел всё это, выхватил саблю и порешил негодяев на месте. Те даже ойкнуть не успели. Ну, а потом я рассказала капитану свою историю, поплакалась... Понимая, что деваться мне некуда, он пожалел меня и взял к себе на корабль, сначала на время, а потом\nНу, наверное, я бы так с ним и осталась, если бы спустя два месяца он не ввязался в бой с патрулём, не потерял мачту на своём шлюпе, не попал в шторм и не нашёл вечный покой где-то на дне у внешнего кольца. А я, назло всем несчастьям, выжила, и пополнила ряды горожан Острова.";
			link.l1 = "Да, ну что тут скажешь...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Нет, конечно. Потому что это невозможно. Я сама видела того, кто пытался уплыть отсюда на лодке... он вернулся, спустя два дня. Привязанный линем к обломку мачты, в надежде не утонуть, синий и совсем-совсем мёртвый. Мне как-то не очень хочется последовать по его стопам\nДа и скажи, "+pchar.name+": вот выберусь я отсюда, и что буду делать? В Гаване мне появляться нельзя - отчим меня быстро сживёт со свету. Дома у меня нет, денег тоже. Куда мне идти? В бордель?";
			link.l1 = "Но ты всё-таки хотела бы вернуться на архипелаг?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "А сам как думаешь? Конечно, хотела бы. Но это невозможно - я же только что тебе рассказала. Эх, вот если бы кто смог урезонить моего отчима... острой сталью или свинцом, тогда был бы шанс возврата к нормальной жизни. Только кто на это отважится, если отчим - лучший друг алькальда Гаваны? Да и к чему этот разговор - отсюда не уплыть...";
			link.l1 = "Ну, это мы ещё посмотрим. Придёт время...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Ну, живётся как-то. Выбора-то нет. Дружу я больше с мужчинами, поскольку две наши красотки на выдание - Джиллиан и Таннеке, меня не любят из-за моего характера, да и мне от их показной благопристойности тошно. Наталия была нормальной девахой, пока не стала слишком много общаться с этими дурочками, а глупость - штука заразная.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Работаю, как и другие девушки. Наша основная задача - помогать мужчинам. На Острове масса женской работы, так что без дела не сижу. Ну, подарки иногда дарят, но это у нас в порядке вещей. Ты не подумай, я не какая-нибудь оторва, я нормальная девушка, и воспитывалась в приличной семье. Просто я не строю из себя святошу, как некоторые.";
			link.l1 = "Да я ничего такого и не думал...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдёт!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьёзному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Осторожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}