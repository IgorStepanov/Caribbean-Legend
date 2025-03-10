// колдун ривадос - Чимисет
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Стой! Остановись... Прошу, выслушай меня, прежде чем совершишь непоправимое.";
			link.l1 = "Уже стою... Надеюсь то, что ты скажешь, будет действительно весомым поводом, чтобы...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "Чтобы не убивать меня, верно? Я слышал ваш разговор с Чадом наверху, и не виню тебя - на твоём месте так поступил бы, наверное, каждый. Но ты ошибаешься, если думаешь, что Чад оставит тебя в живых, после того как ты расправишься со мной.";
			link.l1 = "Хм... Интересно, и почему? Пока что я достоверно знаю одно: если я не прикончу тебя, то меня ждёт очень печальное будущее.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "У тебя вообще не станет будущего, если ты меня убьёшь. Послушай: нарвалы и Чад хотят избавиться от меня, но страх перед моими способностями удерживает их от желания проделать это собственноручно - проклятие падёт на род убийцы до двенадцатого колена. Вот они и решили сделать это твоими руками\nЧад прекрасно знал, что ты не ривадос - он взял тебя 'на пушку'. Как только ты меня убьёшь - они немедленно расправятся с тобой и преподнесут произошедшее здесь Акуле в выгодном для них свете.";
			link.l1 = "Акула? Стив Додсон? Так он здесь? И объясни наконец, кто такие эти ривадос?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Хех, похоже, ты и впрямь не отсюда... Но сейчас не время для историй. Надо спасать свои шкуры. Я могу подсказать тебе, как это сделать.";
			link.l1 = "Знаешь что, колдун, я только что проделал путь через таинственный портал, еле-еле выжил, так что твои проклятия меня не пугают. Довольно я тебя слушал - пора умирать!";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "Хорошо, я верю тебе. Что ты задумал?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "Вон там, в углу, стоит сундук. В нём лежит приличное оружие и прочая амуниция. Сундук заперт, но замок там старый и расхлябаный, его можно открыть даже кочергой. Кочерги, правда, тут нет, но есть кое-что получше: у пыточных колодок лежит небольшой металлический ломик\nВо-он там, видишь? Возьми его, вставь острие в замок, нащупай пластину и сильно нажми вниз. Замок сломается, но крышку держать уже не будет. Забери из сундука всё, что тебе нужно, и встань у лестницы. Эти негодяи почуют неладное и направятся сюда, но больше чем поодиночке пройти не смогут - лестница слишком узка\nНу и, надеюсь, ты хорошо владеешь шпагой? Потому что я в этом деле тебе не помощник - стар я уже, да и кроме копья никакого оружия в руках и не держал. Если тебе удастся прикончить мерзавцев, я гарантирую тебе защиту ривадос, нашей семьи...";
			link.l1 = "Хорошо. Помолись за меня своим богам - драка предстоит нешуточная. Эти парни наверху выглядели более чем серьёзно.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Не теряй времени! Скорее взламывай сундук...";
			link.l1 = "Да-да, уже иду.";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Отличная работа! Ты и впрямь мастерски владеешь клинком. Я в долгу перед тобой, незнакомец. Скажи, как твоё имя?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+" меня зовут. А ты?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Моё имя - Чимисет, я шаман ривадос и советник нашего вождя - Чёрного Эдди. Он будет рад узнать о том, что ты вытащил меня из-за решетки и спас жизнь. Теперь ты друг Чимисета, Чёрного Эдди и всех ривадос. Ты всегда желанный гость у нас на 'Протекторе'...";
			link.l1 = "Постой... Чимисет, если ты ещё не понял, то я только несколько часов назад попал в это чертово место. Ты можешь мне доходчиво объяснить, где я, кто такие ривадос, и где мне найти Акулу Додсона?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Это место называется Остров Справедливости, хотя название скорее издевка. Справедливостью здесь и не пахнет. Остров, состоящий из большого количества погибших кораблей. Центральная часть приспособлена для жизни. Внутри кораблей живут люди, которых судьба забросила сюда после кораблекрушений\nРивадос - это клан, группа людей, уже долгие годы живущая вместе. Кроме ривадос на острове есть ещё один клан - нарвалы, с которыми у нас извечная вражда, а также пираты Акулы Додсона. Ну, и просто обычные жители. Акула - сейчас он является главой острова, и величает себя адмиралом\nОн прибыл на остров относительно недавно и жёсткой рукой установил свою власть. Акула захватил 'Сан-Августин', в трюме которого складируются основные запасы продовольствия на острове, и мы вынуждены его покупать по ценам, которые он сам устанавливает. На этот-то склад, похоже, ты и вломился\nЧад Каппер - это боцман Акулы, а ныне помощник и начальник тюрьмы. Лейтон Декстер - бывший старпом Акулы, тоже не последнее лицо на острове. Эти трое, вместе со своей командой пиратов, имеют серьёзное влияние на острове, по сути враждуя с кланами нарвалов и ривадос.";
			link.l1 = "Почему этот Чад Каппер приказал мне убить тебя?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Чад связался с кланом нарвал, нашими врагами. С их помощью он рассчитывал убить Акулу, своего бывшего капитана, и занять его место. У нарвалов зуб на адмирала, за смерть их предводителя Алана. Они думают, что его убил Акула, хотя это не так. Я знаю, кто его убил. Это Чад. Я единственный свидетель этого злодеяния\nПоэтому Чад не мог выпустить меня отсюда живым, а прикончить лично боялся, так как пираты храбры в схватках, но перед магией колдунов Африки они теряют свою смелость. Вот он и решил сделать это твоими руками. Чад и нарвалы хотели уничтожить Акулу, а вину возложить на ривадос.";
			link.l1 = "Вот как? Скажи, а почему...";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", друг мой, давай пока оставим эти разговоры и поспешим убраться отсюда. В любой момент сюда могут заявиться пираты Акулы, и тогда нам обоим несдобровать. Обыщи тело Чада и найди ключи - они отпирают двери наружу. Но прежде обыщи сундук рядом со столом Чада. Он постоянно складывал туда какие-то бумаги - уверен, что там можно найти что-то касательно планов убийства Акулы\nЗатем немедленно отправляйся к Акуле Додсону. Ты найдёшь его на корабле 'Сан-Августин', он стоит в стороне от прочих и к нему от корабля по имени 'Плуто' ведёт висячий мост. Расскажи ему, что Чад замышлял предательство, и скажи, что за всем этим стоят нарвалы, а мы, ривадос, тут не при чём\nА более подробно об этом острове, о нашем клане и других кланах я с удовольствием тебе расскажу, когда ты прибудешь в нашу резиденцию. Как я уже говорил, она находится на корабле 'Протектор'. А теперь давай поспешим уйти отсюда!";
			link.l1 = "Хорошо, Чимисет. Я обязательно найду тебя позже на этом... 'Протекторе'. Уходим!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "И ещё. На наши корабли, в том числе и 'Протектор', доступ посторонним запрещён. Для прохода нужно или быть ривадос, или знать пароль. Я бы сказал тебе пароль, но мы их меняем еженедельно, а поскольку я провёл в заключении достаточно долго, то текущего пароля я не знаю\nПоэтому сейчас отправляйся на 'Сан-Августин', побеседуй с Акулой, а я тем временем доберусь до своих и расскажу подробно о тебе. После этого ты сможешь проходить на нашу территорию свободно, как и сами ривадос. Но не спеши туда прямо сейчас, иначе быть беде: тебя примут за врага.";
			link.l1 = "Понятно. Отправляюсь на 'Сан-Августин'. До встречи!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("Ха, говорят, что вы подружились с кланом ривадос. Презанятно, скажу я вам. Поздравляю...", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("Ходят слухи, что вы вытащили из 'Тартаруса' колдуна ривадос Чимисета. Теперь вы у них на кораблях желанный гость.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("Так это вы вытащили Чимисета из-за решётки! Очень интересно... Теперь вы друг ривадос, но враг нарвалам. Не знаю, поздравить вас, или посочувствовать...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Что ты хочешь от меня, незнакомец?";
			link.l1 = "Тебя ведь зовут Чимисет, так?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Да, это я. Ты явился по какому-то делу, или просто для праздной болтовни?";
			link.l1 = "По делу. Я пришёл от адмирала, Акулы Додсона. Я принёс его приказ о твоём освобождении, но при одном условии: ты должен будешь ответить на мои несложные вопросы.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Додсон решил выпустить меня? Очень рад это слышать. Задавай свои вопросы. Надеюсь, они без подвоха, ибо в противном случае моя радость была преждевременной.";
			link.l1 = "Никакого подвоха, мне просто нужна твоя помощь. Скажи, Чимисет: есть ли на острове странный каменный истукан размером с рост человека? В полночь он из каменного превращается в золотой. Только ты не подумай, что я сошёл с ума...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "У тебя есть ещё какие-то вопросы?";
			link.l1 = "Да. Ты не знаешь такого человека - Белый Мальчик? Это имя, или прозвище...";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Белый Мальчик? Конечно, знаю. Так называли в детстве Оле Кристиансена, нашего забавного дурачка, за его белые волосы. Оле уже вырос, и совсем не мальчик, хотя... по уму - совсем ребёнок.";
			link.l1 = "Вот как? Скажи, а где я могу найти его?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Да где угодно в городе. Он часто бывает в магазине, таверне и просто на улицах. Поищи - ты сразу узнаешь его по белым волосам.";
			link.l1 = "Отлично! И ещё вопрос: ты не встречал здесь человека по имени Натаниэль Хоук? Он должен был появиться недавно, и возможно сильно болен.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Здесь я ничем тебе помочь не смогу, незнакомец. Человек с таким именем мне незнаком. Могу с уверенностью сказать, что на кораблях ривадос и в нейтральной зоне его нет. А вот что касается территории нарвалов - то кто его знает... Мы, ривадос, там не бываем.";
			link.l1 = "Ну что же, спасибо и на этом... Ты мне очень помог, Чимисет!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "И это всё? Теперь Акула меня выпустит?";
			link.l1 = "Да. Больше мне спрашивать нечего. Чад Каппер освободит тебя. Ну, а мне пора...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Стой! Погоди... Вернись назад.";
			link.l1 = "Ты что-то вспомнил?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Не совсем так...(понижая голос) Я вижу, ты не из людей Каппера... Не доверяй Чаду! Это гнусный мерзавец. Не так давно он хладнокровно зарубил палашом безоружного Алана Милроу, главу клана нарвал, который сидел в соседней клетке. Убил без всякой видимой на то причины - просто пришёл и расправился\nИ ещё: сидя здесь, я слышал обрывки разговоров, из которых у меня сложилась ясная картина: адмирала собираются убить, причём люди из его ближайшего окружения. Передай это Акуле. Также скажи, что подробнее я расскажу только при личной встрече.";
			link.l1 = "Хм. Хорошо, я обязательно поведаю об этом Додсону. Пока!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Ступай поскорее к Акуле и сообщи ему всё, что я сказал. Эх, быстрее бы открыли дверь этой клетки...";
			link.l1 = "Да-да, уже иду.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "Вот и снова ты, мой дорогой друг. Я ещё раз благодарю тебя за помощь, и за то, что ты поверил мне, а не этому подлецу Капперу. И чтобы мои слова обрели ещё больший вес, я дарю тебе эти амулеты. Я уверен, что они тебе понадобятся.";
			link.l1 = "Спасибо! Не ожидал...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "А теперь я готов выслушать тебя. Ты ведь хочешь задать мне вопросы, я прав?";
			link.l1 = "Ты прав, Чимисет. Мне нужна твоя помощь. Но буду последователен. Меня более всего волнует следующее: есть ли на острове странный каменный истукан размером с рост человека? В полночь он из каменного превращается в золотой. Только ты не подумай, что я сошёл с ума...";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "Я понял, о чём ты говоришь, мой друг. Я сам видел эту статую бога индейцев. Только золотой она становится не в полночь, а под лучами утреннего солнца... Мы не раз приносили в жертву нечестивцев из клана нарвал, и бог пожирал их. Однако её уже нет на острове.";
			link.l1 = "Как нет?! То есть - была-была, и внезапно не стало?!";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Не совсем так. Эта статуя была на одном из кораблей под названием 'Сан-Херонимо'. Несколько лет назад этот корабль затонул вместе со статуей.";
			link.l1 = "Вот невезение! Получается, что теперь с острова не выбраться... А хоть где этот корабль был-то?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Недалеко от владений нарвалов, у обломка корабля под названием 'Феникс'. Если проплыть там на лодке в ясную солнечную погоду, то можно увидеть этот корабль, покоящийся на дне.";
			link.l1 = "Ха! Так он лежит на мелководье? Тогда до него можно попробовать добраться вплавь...";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "Вплавь до него не добраться, друг мой. Во-первых, он лежит достаточно глубоко, а во-вторых, там полно гигантских крабов. Они растерзают тебя своими клешнями, прежде чем ты приблизишься к 'Сан-Херонимо'.";
			link.l1 = "Хм. Ладно. Я подумаю над этим. Главное - что истукан существует, и я знаю, где его искать.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Вижу, у тебя ещё есть вопросы. Задавай, друг мой, не стестняйся.";
			link.l1 = "Акула Додсон дал мне задание: разыскать пособников Чада, готовящих на него покушение. В письме, которое я нашёл в сундуке Каппера, говорилось про какого-то снайпера и какой-то ствол. Очевидно, Акулу собираются подстрелить с дальней дистанции. Ты можешь высказать на этот счёт хоть какие-то соображения?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "Хм. Адмирала собираются застрелить? Надо подумать... Дело в том, что адмирал практически не покидает свою резиденцию на 'Сан-Августине', а если и выходит, то только в сопровождении полудюжины пиратов. Но у него есть одна особенность: поздними вечерами он любит прогуляться по кормовой галерее своего корабля\nЕго резиденция, и эта кормовая галерея, лучше всего видны с двух мест: с носовой части корабля 'Санта-Флорентина', и с нашего корабля 'Фурия', если забраться на уцелевшую марсовую площадку на мачте. Однако даже если стрелок займёт любую из этих позиций, он не сможет убить адмирала, во всяком случае, шанс попадания невелик: слишком большое расстояние\nВ данном случае кроме крепкой руки и зоркого глаза нужно какое-то очень точное и дальнобойное оружие. И раз покушение готовится именно таким способом, то тебе, пожалуй, следует поискать на острове человека, у которого подобное оружие есть.";
			link.l1 = "Хех, похоже, мы на верном пути: в письме говорилось про какой-то ствол... А ты не видел ни у кого подобного оружия?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "Нет. Всё, что я видел до сих пор, на эту роль не годится. Поспрашивай, может, кто-то и подскажет.";
			link.l1 = "Хорошо... В любом случае, твоя информация очень ценна, спасибо! Ну и, наверное, последний вопрос, хотя я не надеюсь, что ты на него ответишь... Ты не знаешь такого человека - Белый Мальчик?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Белый Мальчик? Конечно, знаю. Так называли в детстве Оле Кристиансена, нашего забавного дурачка, за его белые волосы. Оле уже вырос, и совсем не мальчик, хотя... по уму - совсем ребёнок.";
			link.l1 = "Вот как? Скажи, а где я могу найти его?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Да где угодно в городе. Он часто бывает в магазине, таверне и просто на улицах. Поищи - ты сразу узнаешь его по белым волосам.";
			link.l1 = "Отлично! Спасибо, Чимисет, ты мне очень помог!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Всегда рад! Если у тебя появятся ещё какие-то вопросы - приходи, помогу, чем смогу.";
			link.l1 = "Обязательно! А сейчас мне пора. Ещё увидимся!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "А, вот и мой дорогой друг, которому я обязан свободой, и, возможно, жизнью. Благодарю тебя за то, что помог моим братьям вытащить меня из лап гнусного Каппера. И чтобы мои слова обрели ещё больший вес, я дарю тебе эти амулеты. Я уверен, что они тебе понадобятся.";
			link.l1 = "Спасибо! Не ожидал...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "Ты ещё что-то хочешь спросить, белый друг?";
			link.l1 = "Скажи ещё, Чимисет: не знаешь ли ты на Острове человека по прозвищу Белый Мальчик?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "О! Мой белый друг "+pchar.name+"! Так ты не утонул? Тебя спасли духи, я знаю...";
				link.l1 = "Как видишь - я жив и здоров, Чимисет. Духи? Наверное, да - ведь всё это произошло благодаря Кукулькану...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Что привело тебя ко мне вновь, мой добрый друг?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Расскажи, как погиб лидер нарвалов? Ты единственный, кто видел это.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "Ты говорил о крабах на дне у затонувшего 'Сан-Херонимо'. Можешь подробнее описать этих монстров?";
				link.l2.go = "crab";
			}
			link.l9 = "Ничего такого особенного, Чимисет. Просто зашёл проведать тебя.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Здесь будет написана история гибели Алана Милроу.";
			link.l1 = "ОК!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "Откуда они взялись, и почему достигли таких гигантских размеров - никто не знает. Но факт есть факт - эти твари существуют, и их видели многие жители острова. Основное их скопище на мелководье среди обломков утонувших кораблей - ползают по дну и собирают всякие отбросы, которые наши люди выбрасывают за борт, ну и, конечно, охотятся на рыб\nДля человека представляют реальную угрозу - могут нанести очень сильные повреждения своими клешнями, кроме того, в их челюстях содержится достаточно опасный яд, схожий с ядом морских рыб - при попадании в организм человека, без должного лечения, может привести к фатальным последствиям. Слава Богу, токсин нейтрализуется противоядием из местных трав\nКак-то раньше у нас жил один человек, занимавшийся охотой на этих крабов. Тогда он частенько приносил их мясо, которое на удивление вкусное, но самое важное: он добывал клешни этих монстров и челюсти с ядом - я их использовал как ингридиенты для некоторых зелий. Жаль, правда, давно мне уже их никто не приносил...";
			link.l1 = "А где же он сейчас, этот охотник?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "А ты не догадываешься? Когда охотишься на таких бестий, надо быть готовым к тому, что однажды из охотника превратишься в добычу. Так и вышло в один день - он не вернулся из похода. Поэтому я и предупредил тебя - будь внимателен и осторожен с этими существами.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}