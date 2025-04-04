// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Приветствую вас, "+pchar.name+". Проходите, мне уже обо всём доложили.";
				link.l1 = "Доложили? Возможно, это какая-то ошибка, Ваша Светлость. Я пришёл, чтобы отчитаться об успешном завершении вашего задания, но вижу, что вы пребываете не в лучшем расположении духа.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Рад вас видеть, "+pchar.name+". Наслышан, наслышан про ваши подвиги. И, что самое важное - вы выполнили задачу, возложенную на вас, и выполнили её с блеском! Вы проявили себя с лучшей стороны, и я рад, что не ошибся в вас.";
				link.l1 = "Теперь я могу получить от вас письменный приказ, согласно которому мой брат будет освобождён из-под ареста?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Рад вас видеть, "+pchar.name+". Наслышан, наслышан про ваши подвиги. И, что самое важное - вы выполнили задачу, возложенную на вас! Хотя, если честно, я ожидал более хитрого хода, нежели лобовой штурм. Жаль погибших французских солдат\nНо на войне - как на войне, без потерь не бывает. Вы исполнили свой долг, и я рад, что не ошибся в вас.";
				link.l1 = "Теперь я могу получить от вас письменный приказ, согласно которому мой брат будет освобождён из-под ареста?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Рад вас видеть, Шарль. Прежде всего позвольте вас поздравить с успешно выполненным сложнейшим заданием по защите колонии Сен-Пьер от испанских захватчиков. Вы блестяще справились, мой друг!";
					link.l1 = "Спасибо за лестные слова, шевалье. Рад, что смог помочь моей стране.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Рад вас видеть, Шарль. Прежде всего позвольте вас поздравить с успешно выполненным сложнейшим заданием по защите колонии Сен-Пьер от испанских захватчиков. Вы блестяще справились, мой друг! И поэтому я даю вам ещё одну возможность поступить на службу в военно-морской флот. Такие офицеры нужны Франции. Надеюсь, в этот раз вы будете более благоразумным... Возьмите патент, капитан Шарль де Мор!";
					link.l1 = "Спасибо, шевалье. Рад, что смог помочь моей стране, и буду рад служить ей!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Шарль, вы меня огорчили. В результате ваших необдуманных поступков вы лишились патента и звания в королевском флоте. О дальнейшей работе не может быть и речи. Можете быть свободны.";
					link.l1 = "Гм...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Итак, с прибытием, Шарль. Докладывайте!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Задание выполнено, выкуп с колонии Сан-Хосе получен. Но есть плохая новость: в бою с фортом затонул 'Эклятон'. Я предупреждал капитана не лезть на рожон, но он меня не послушал, и...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "Задание выполнено, выкуп с колонии Сан-Хосе получен.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Монсеньор, извольте являться ко мне на приём в подобающем виде, в мундире! И сегодня, и впредь!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Барон, капитан! Рад вас видеть в добром здравии!";
					link.l1 = "Поставленная задача выполнена, шевалье.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", капитан. Какие новости вы привезли?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Испанцы действительно планировали нападение на Порт-о-Пренс. У западной оконечности Эспаньолы нами была обнаружена мощная эскадра противника. В бою она была полностью уничтожена. Однако в тяжёлом неравном бою 'Эклятон' был потоплен.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "Испанцы действительно планировали нападение на Порт-о-Пренс. У западной оконечности Эспаньолы нами была обнаружена мощная эскадра противника. В бою она была полностью уничтожена.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Шарль. Как обстоят дела у минхера Стайвесанта?";
					link.l1 = "Всё отлично, шевалье. Флейт доставлен по месту назначения, а вот ответ на ваше письмо.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Шарль, барон... Вы уже вернулись?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Не нравится мне ваш хмурый вид, Шарль. Что сказал Стайвесант, докладывайте!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Докладываю дословно: 'передайте шевалье, что он больше не в деле на Синт-Маартене. Хватит с него. А касательно инспекции из метрополии - пусть придумает что-нибудь'. Озвучив это послание, минхер директор меня выставил из резиденции. На этом переговоры окончились.";
					else link.l1 = "Передаю высказывание Стайвесанта дословно: 'ваш шеф чрезмерно зажрался на Синт-Маартене, поэтому настало время умерить его ненасытные аппетиты.' После чего меня попытались арестовать. Пришлось клинком прокладывать дорогу к кораблю. Вот так выглядит голландская дипломатия.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Капитан, мы ждём вас. Я ввёл уважаемого барона в курс дела, и он полностью поддержал моё решение. Голландцы ответят за свою наглость.";
					link.l1 = "Итак, война?..";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Так, мой друг, вижу, у вас есть трофейный ост-индец с товаром. Отлично!";
						link.l1 = "Передаю корабль вам, отдайте распоряжение портовым чиновникам, шевалье.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "У вас ко мне какие-то вопросы, Шарль?";
						link.l1 = "Пока нет, монсеньор. Я уже ухожу...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Капитан, наконец-то вы прибыли! Чрезвычайная ситуация на Сент-Кристофере!";
					link.l1 = "Вражеская эскадра?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = "Вы готовы принять в эскадру наш курьерский люггер?";
					link.l1 = "Да.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Капитан де Мор, сэр д'Ойли! Рад вас видеть! Весь город наблюдал за тем, как вы преподали урок испано-голландским негодяям, посягнувшим на нашу колонию!";
					link.l1 = "Я просто выполнял свой долг, шевалье.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Шарль. Итак, приступим к делу?";
					link.l1 = "Конечно, шевалье. Для этого я и здесь.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Я рад приветствовать в моём кабинете вице-адмирала королевского флота Франции! Да-да, мой друг, вы не ошиблись: я лично подписал приказ о вашем назначении. Формально его ещё должны будут утвердить во Франции, но вы даже не сомневайтесь в том, что это произойдёт. Поздравляю!";
					link.l1 = "Служу Отечеству!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "скоро будет готова"; // в зависимости от времени сколько добирался
					else sTemp = "уже готова";
					dialog.text = "Как успехи, мой друг? Полковник д'Ойли остался доволен?";
					link.l1 = "Всё прошло отлично, шевалье. Караван Стайвесанта захвачен, рабы доставлены на Ямайку, эскадра полковника "+sTemp+" к походу на Кюрасао.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Слава победителям! Поздравляю, поздравляю, мой друг! Вы, как всегда - на высоте.";
					link.l1 = "Спасибо, шевалье. Стайвесант наказан и готов выплатить контрибуцию, мир восстановлен, Синт-Маартен окончательно возвращён Франции.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Итак, друг мой, я рад вас видеть снова. Вы хорошо отдохнули?";
					link.l1 = "Да, шевалье. Отдых удался как никогда лучше. Вы говорили о каком-то деликатном деле?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Мой друг, вы просто волшебник! Вы сотворили чудо! Наш барон больше не желает даже пытаться создавать тут торговую компанию.";
					link.l1 = "Думаю, больше всего он сейчас хочет оказаться в Париже.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Шарль, вы слышали о бароне? Его захватили пираты...";
					link.l1 = "Да, шевалье. И увы, наш барон мёртв. Я знаю это достоверно.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Шарль, как ваши успехи? Мне докладывали, что барон поднялся к вам на борт...";
					link.l1 = "Да, шевалье. Он был на борту, я обрабатывал его, но... он умер. Лихорадка.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Шарль, как ваши успехи? Мне докладывали, что барон поднялся к вам на борт...";
					link.l1 = "Да, шевалье. Он был на борту, я обрабатывал его, но... его убили в случайном бою.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Мой друг, вы просто волшебник! Вы сотворили чудо! Наш барон больше не желает даже пытаться создавать тут торговую компанию.";
					link.l1 = "Наверное, сейчас он уже собирается домой, в Париж?.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "У вас ко мне какие-то вопросы, Шарль?";
				link.l1 = "Пока нет, монсеньор. Я уже ухожу...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Что вам угодно, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Ничего серьёзного, просто визит вежливости. Я уже ухожу...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Добрый день, Шарль. Позвольте представиться - Филипп де Пуанси, и я...";
			link.l1 = "Какого черта меня задержали и посадили в тюрьму? Это форменное безобразие! Я французский дворянин, и...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Добрый... день? Хорошая шутка, месье. Откуда вам известно кто я?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Молодой человек, я попрошу вас не перебивать меня! Вы разговариваете с генерал-губернатором французских колоний Карибского архипелага! Я прощаю ваш дерзкий тон лишь потому, что вы не могли знать, кто стоит перед вами. Но я рекомендовал бы вам впредь быть более сдержанным.";
			link.l1 = "Хм... Простите, Ваша Светлость.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Молодой человек, я попрошу вас не перебивать меня! Вы разговариваете с генерал-губернатором французских колоний Карибского архипелага! Я прощаю ваш дерзкий тон лишь потому, что вы не могли знать, кто стоит перед вами. Но я рекомендовал бы вам впредь быть более сдержанным.";
			link.l1 = "Хм... Простите, Ваша Светлость.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Так-то лучше. Что касается вашего вопроса - то вас по ошибке приняли за испанского шпиона и поместили под арест до выяснения. В последнее время проклятые кастильцы активизировали свою деятельность в французских поселениях, поэтому я лично издал приказ задерживать всех подозрительных людей\nНо сейчас во всём разобрались - вы действительно Шарль де Мор, брат Мишеля де Монпе, и я лично, подчеркиваю - лично явился в эти казематы, чтобы выпустить вас на свободу. А вы кричите и ведёте себя, словно мальчишка!";
			link.l1 = "Ещё раз приношу извинения, Ваша Светлость. Так я свободен?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Да, вы свободны. Но прежде чем сержант отопрёт двери вашей камеры, мы с вами поговорим по душам. Вы, вероятно, в курсе, что ваш брат, один из достойнейших воинов Ордена Мальтийских рыцарей, арестован и помещён под стражу?";
			link.l1 = "Я знаю лишь то, что мой брат попал в беду и ему нужна помощь. Я для этого и прибыл сюда из Парижа.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Что же, я очень и очень рад этому. Я хочу сообщить вам, что у месье де Монпе серьёзные неприятности. У меня есть все основания подозревать его в злоупотреблении служебным положением в личных целях, присвоении не принадлежащего ему имущества и клятвопреступлении. Однако вы действительно можете помочь вашему брату.";
			link.l1 = "Месье, вы не могли бы объяснить подробнее? Я что-то совсем не понимаю: Мишель был гордостью Ордена, и...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Я тоже так считал. Мы все так считали! Но его недавние поступки заставили нас... усомниться в его преданности делам Ордена. Настолько усомниться, что он был помещён под стражу. Подробности вам расскажет сам Мишель. Он же и объяснит, каким образом вы можете помочь снять с него обвинения и избежать позора.";
			link.l1 = "Где же мой брат сейчас? Вы сказали - он в тюрьме. Но я не видел его здесь...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Юноша, разве я сказал - посажен в тюрьму? Вы меня внимательно слушаете? Я сказал - взят под стражу! А это не одно и то же. Мишель де Монпе содержится под арестом в подземной базе Сен-Пьера, принадлежащей Мальтийскому Ордену\nЯ разрешаю вам неограниченное число раз посещать базу и беседовать с вашим братом столько, сколько вы сами сочтёте нужным. Офицеры и солдаты Ордена ознакомлены с моим распоряжением и не будут чинить вам препятствий.";
			link.l1 = "Где же находится эта подземная база?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "В Сен-Пьере, конечно. Найдите собор и войдите в дверь, на которую нанесена символика Ордена. Затем спуститесь по ступеням вниз, на второй подземный ярус к казематам. Там и отыщете месье де Монпе в одной из камер. Впрочем, не беспокойтесь: на выходе из тюрьмы вас встретят и проводят к вашему брату - я распорядился... На этом всё. Надеюсь, мы ещё с вами встретимся, Шарль. Сержант!";
			link.l1 = "Постойте, Ваша Светлость! А... мои вещи? Шпага, и прочее?..";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Ваши вещи конфискованы в счёт уплаты долгов вашего брата. Всего доброго, месье де Мор.";
			link.l1 = "Но...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "А-а, вот и сам Шарль де Мор собственной персоной! Очень, очень рад вас видеть. Вы, вероятно, явились обсудить со мной судьбу вашего брата?";
			link.l1 = "Я готов оплатить долг Мишеля де Монпе перед Орденом и лично вами. Надеюсь, эта сумма с лихвой покроет все издержки.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Гм... Но где же деньги? Молодой человек, у вас своеобразное чувство юмора, которое я не понимаю.";
			link.l1 = "Простите, шевалье. Я, видимо, забыл деньги в корабельном рундуке. Сейчас вернусь и принесу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "Вы принесли деньги, Шарль?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Конечно! Надеюсь, эта сумма с лихвой покроет все издержки.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Пока ещё нет...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Замечательно! Я принимаю у вас эти деньги. Вы показали себя с наилучшей стороны, Шарль!";
			link.l1 = "Когда я смогу получить приказ об освобождении Мишеля де Монпе?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Не торопитесь, юноша. Похвально, что вы возвращаете долги и печётесь о чести семьи, рискуя собственной жизнью. Нечасто встретишь подобное благородство... Но деньги в этой печальной истории не самое главное. Одним из условий передачи вашему брату столь крупной суммы было решение им одной весьма деликатной задачи\nМишель де Монпе, как благоверный католик, поклялся на Библии, что найдёт способ наказать одного зарвавшегося еретика и восстановить попранную им справедливость во славу Ордена и Святой Церкви...";
			link.l1 = "Но сидя под арестом на Мартинике он не сможет сдержать обещание!";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Видите ли, мой друг, ваш брат дал мне серьёзный повод усомниться в его порядочности. Кто даст мне гарантии, что, выйдя на свободу, он не исчезнет, нарушив данное мне слово? Так что, если хотите окончательно снять с брата все обвинения, исполните его клятву сами. Подробности, как и в прошлый раз, можете узнать у месье де Монпе.";
			link.l1 = "Гм... Не ожидал. Но вы не оставляете мне выбора, шевалье. Что же, я приму решение после встречи с моим несчастным братом.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Вы всё больше нравитесь мне, Шарль. Возможно, однажды мы станем друзьями. Во всяком случае, это моё последнее условие освобождения вашего брата. В случае успешного разрешения проблемы даю слово, что репутация вашей семьи не пострадает, а вы сможете рассчитывать на моё дальнейшее расположение.";
			link.l1 = "Я вас понял. Разрешите откланяться!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "Не беспокойтесь, "+pchar.name+", я держу слово. Ваш брат получит свободу, и все обвинения с него будут сняты. Более ничего не угрожает доброму имени вашей семьи. Без прикрас могу добавить - это ваша, и только ваша заслуга. Ваш отец может гордиться, что вырастил такого сына.";
			link.l1 = "Благодарю за тёплые слова, шевалье. Значит, я могу смело отправляться на Мартинику?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Погодите, друг мой. Надеюсь, я могу называть вас так? Я хочу выразить вам благодарность от себя лично... Я внимательно наблюдал за вами с самого вашего прибытия на архипелаг, и в курсе большинства ваших дел. Вы успели заработать себе весьма громкую славу на Карибах и, без преувеличения - приобрели известность и немалый вес в определённых кругах. Такие люди нужны Франции\nКапитан "+GetFullName(pchar)+"! Властью, данной мне Его Величеством, королём Франции, я имею честь предложить вам патент капитана королевского флота и взять под своё командование корабль военно-морских сил Франции, малый фрегат 'Гриффондор'!\nЕго бывший капитан шевалье де Фонтене вашими стараниями будет осваиваться в новой должности губернатора Тортуги, а место капитана лучшего малого фрегата на Карибах не должно пустовать. Вы согласны?";
			link.l1 = "Очень интересно. Но что вы потребуете взамен?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Самую малость. Десятую долю добычи и время от времени выполнение деликатных поручений. Итак, я жду вашего ответа.";
			link.l1 = "От таких предложений не отказываются, Ваша Светлость! Почту за честь служить родной стране!";
			link.l1.go = "serve_3";
			link.l2 = "Боюсь показаться нескромным, но я вынужден пока отклонить ваше щедрое предложение. Возможно, что дела семьи потребуют моего немедленного отплытия на родину.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Очень жаль. Я так надеялся... И, тем не менее, я вынужден просить вас ещё об одном одолжении, тем более, что это и в ваших интересах. На Мартинику высажен испанский десант. В порту и в городе идут жаркие бои\nК сожалению, мне некого послать на помощь осаждённому гарнизону, кроме вас. Прошу вас, как патриота своего Отечества, сделать всё, чтобы отразить атаку. Надеюсь, у вас для этого найдётся достаточно сил и средств\nТем более, что этим вы можете спасти жизнь своему брату, который до сих пор пребывает на базе Ордена.";
			link.l1 = "Мой брат в опасности? Я немедленно отправляюсь в путь!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Вот это достойные слова! Слова истинного солдата и верного сына Отечества! Поздравляю вас, месье "+GetFullName(pchar)+". Вам присвоено звание коммандера военно-морского флота Франции. Позвольте вручить вам этот мундир. Носите его с гордостью и будьте достойны его!";
			link.l1 = "Служу Отечеству!";
			link.l1.go = "serve_4";
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";
		break;
		
		case "serve_4":
			dialog.text = "В ваше распоряжение поступает малый фрегат 'Гриффондор'. Отныне этот великолепный корабль - ваш. Используйте его выдающиеся качества во славу Его Величества и для укрепления влияния Франции на Карибском архипелаге!";
			link.l1 = "Будет исполнено!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Однако на данный момент ваша эскадра слишком велика, чтобы принять ещё один корабль. Избавьтесь от лишнего корабля - и тогда принимайте командование 'Гриффондором'.";
				link.l1 = "Хорошо. Так и поступлю.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Вместе с 'Гриффондором' в ваше полное распоряжение поступает вся его команда и вахтённый офицер. Если сочтёте нужным - можете оставить его у себя на службе, если нет - спишете на берег, мы переведём его на другое место службы.";
				link.l1 = "Принял к сведению!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Но вслед за приятными новостями, капитан, у меня есть для вас и тревожные известия. Я только что узнал, что на Мартинику высажен испанский десант. В порту и в городе идут жаркие бои. К сожалению, мне некого послать на помощь осаждённому гарнизону, кроме вас. Вот вам первое неотложное поручение\nЗащитите Сен-Пьер! Тем более, что этим вы можете спасти жизнь своему брату, который до сих пор пребывает на базе Ордена.";
			link.l1 = "Мой брат в опасности? Я немедленно отправляюсь в путь!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "Вы готовы принять под своё командование 'Гриффондор'?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Пока ещё нет, я размещаю корабли своей эскадры...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Да, готов.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Отлично! Вместе с 'Гриффондором' в ваше полное распоряжение поступает вся его команда и вахтённый офицер. Если сочтёте нужным - можете оставить его у себя на службе, если нет - спишете на берег, мы переведём его на другое место службы.";
			link.l1 = "Принял к сведению!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			DelCharleePrince("");
			dialog.text = "И это только начало, монсеньор! Я уверен, что вы пойдёте далеко, с такими-то военными талантами! И у меня уже имеется для отличного морского офицера очередное поручение, с которым, я уверен, вы справитесь так же великолепно. Тем более, что оно напрямую связано с вашей предыдущей миссией.";
			link.l1 = "Я весь внимание, месье.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Но позвольте сначала представить вам человека, вошедшего в мой кабинет. Знакомьтесь - барон Ноэль Форже, почётный член Французской Вест-Индской торговой Компании. Прибыл на архипелаг с целью инспекции наших колоний на предмет расширения организации плантаций сахарного тростника и прочих культур, а также изучения возможности развития торговых связей в нашем регионе. Из Парижа предписано оказывать ему всяческую поддержку и содействие в этих вопросах, что мы, несомненно, и сделаем. Барон, представляю вам месье Шарля де Мора, одного из талантливейших капитанов на службе Франции...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "Итак, Шарль, пока мы с бароном займёмся инспекцией Сент-Кристофера, я ставлю перед вами следующую задачу. Никто не может безнаказанно нападать на французские поселения, и испанцы, хотя уже и понесли от вас урок за агрессию на Мартинике, должны ответить за содеянное звонкой монетой и компенсировать нанесённый колонии ущерб\nВместе с бароном из Франции прибыла эскадра, в составе которой - мощный линейный 66-пушечный корабль 'Эклятон'. Капитан корабля - опытный моряк, но на Карибах он впервые, поэтому он поступает под ваше командование. Вместе с 'Эклятоном' вы отправитесь к берегам испанского острова Тринидад, и потребуете от испанцев денежной компенсации в триста тысяч песо за нападение на Сен-Пьер.";
			link.l1 = "Шевалье, вы считаете, что испанцы согласятся заплатить?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Уверен, что да - после того, как 'Эклятон' и ваша эскадра разнесут форт Сан-Хосе в щепки. Высаживать десант и захватывать город, теряя солдат, думаю, не понадобится. Нападаете без предупреждения, уничтожаете форт, а затем сигнализируете коменданту, что желаете выставить условия. В такой ситуации испанцам будет некуда деваться, и они предпочтут заплатить. А вы бы как поступили на месте губернатора города, оставшегося без защиты?";
			link.l1 = "Хм... Резонно, шевалье.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ну что же, задание вам ясно?";
			link.l1 = "Так точно, Ваша Светлость.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = "Тогда приступайте. Держите письмо для капитана 'Эклятона' с подтверждением ваших полномочий. Этот отличный корабль с великолепно обученной командой поступает под ваше командование. Шарль, и не забывайте, что вы теперь на службе Франции, и для общения с официальными лицами, включая меня, в первую очередь, необходимо быть в мундире. К тому же, он вам очень к лицу. Удачи, капитан де Мор!";
			}
			else
			{
				dialog.text = "Тогда приступайте. Держите письмо для капитана 'Эклятона' с подтверждением ваших полномочий. Этот отличный корабль с великолепно обученной командой поступает под ваше командование. И ещё, Шарль: я приказываю - наденьте ваш капитанский мундир! Во-первых, негоже офицеру французского королевского флота ходить без знаков отличия от торговых капитанов и каперов, а во-вторых, мундир вам очень к лицу. Выполняйте, капитан де Мор!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'Эклятон' затонул? Шарль, это же катастрофа! Что теперь скажет министр? Ох, как же вы меня подвели! Я был уверен в вашей опытности, а вы... Увы, но ответственность за это ляжет на вас. Я напишу рапорт, а вам лучше всего исчезнуть на время. Ни о какой дальнейшей службе, как вы понимаете, не может быть и речи.";
			link.l1 = "Кхм... Очень жаль, месье. Вижу, что мне и в самом деле лучше залечь на дно на месяц-другой, пока гнев министра утихнет. До свидания, поверьте, мне очень жаль, что так нелепо получилось.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Замечательно!";
				link.l1 = "Вот, примите, пожалуйста, триста тысяч.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Замечательно, Шарль, но где же деньги?";
				link.l1 = "Хех, в сундуке на корабле, сейчас доставлю!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Итак, Шарль, вы принесли полученный выкуп с Тринидада?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Да, так точно. Вот он.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Уже несу!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Я вами доволен, Шарль, впрочем, как и всегда. Задание было непростым, и вам из суммы выкупа причитается премия - 50 000 песо. Возьмите, это ваше.";
			link.l1 = "Благодарю, шевалье.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "И для вас уже имеется новое поручение. Месье Форже закончил инспекцию на Сент-Кристофере и теперь желает посетить наши северные колонии. Я прошу вас отвезти барона на Тортугу и Эспаньолу, всячески содействовать в его делах и выполнять его просьбы. Мы договорились, Шарль?";
			link.l1 = "Конечно, шевалье.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Барон ограничен во времени, поэтому прошу вас не отвлекаться на посторонние дела и не затягивать путешествие дольше, чем на два месяца.";
			link.l1 = "Конечно, монсеньор. Переход между островами не займёт столько времени, разве что - дела месье Форже в колониях.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Отлично. Тогда барон отправляется на ваш корабль. Выделите ему самую лучшую каюту.";
			link.l1 = "Так точно, шевалье!";
			if (IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "И ещё, Шарль: вы снова без вашего офицерского мундира! Делаю вам замечание. И впредь прошу являться ко мне только в форме, в противном случае я просто не буду вас выслушивать. Вы на службе, и дисциплина должна быть во всём, в первую очередь - во внешнем виде морского офицера!";
			link.l1 = "Прошу прощения, шевалье, этого больше не повторится.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "Я ни минуты не сомневался в том, что ваше путешествие завершится благополучно. Есть какие-нибудь новости с Тортуги или из Порт-о-Пренса?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Да, шевалье, есть новости и не очень приятные. Во-первых, губернатор Порт-о-Пренса уверен, что испанцы готовят атаку на колонию и для этого собирают военную эскадру на... эм-м-м, как его... в Сантьяго, вот. И это не похоже на простые сплетни. Я считаю, что мы не можем оставить это без внимания, тем более, что плантации Порт-о-Пренса - лучшие из тех, что я видел до этого момента.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Испанцы готовятся атаковать Порт-о-Пренс? Хм... Хорошо. Мы поручим разобраться с этим капитану Шарлю де Мору. 'Эклятон' как раз починен, снаряжён и готов к выходу в море...";
			link.l1 = "И ещё, монсеньор: в Париже остров Синт-Маартен, что лежит на север отсюда, считается французской колонией, а капитан Шарль де Мор сказал мне, что там заправляют голландцы. Это так, шевалье?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "М-м-м... Это так, и в то же время не совсем так. Синт-Маартен является французской колонией. Однако, барон, этот остров с экономической точки зрения абсолютно бесполезен - площадь маленькая, почвы там скудные, неурожайные, и повсеместно - нехватка пресной воды, а та, что есть в колодцах - мутная и горьковатая. Мне даже говорили, что там для питья собирают дождевую воду\nПоэтому Синт-Маартен был передан в долгосрочную аренду Голландской Вест-Индской торговой Компании, которая использует его как северный перевалочный пункт на пути следования кораблей Компании из региона в метрополию. Голландцы расширили имевшееся там поселение Филипсбург, построили форт и порт, и для тех, кто прибыл на архипелаг относительно недавно, как капитан Шарль де Мор, Синт-Маартен действительно кажется голландской колонией.";
			link.l1 = "Однако де-юре остров принадлежит нам?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Конечно. Но как я уже сказал - выгоднее получать деньги за сдачу в аренду, чем использовать его скудные ресурсы.";
			link.l1 = "Мне кажется, что этот остров очень пригодится Французской Вест-Индской торговой Компании, когда она появится на Карибах. Значение его вы только что озвучили - северный форпост на пути в Европу. Мне нужно посетить эту колонию, и, весьма вероятно, что аренда острова голландцам будет прекращена.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Сначала надо направить запрос в Виллемстад, директору Голландской Вест-Индской торговой Компании, минхеру Питеру Стайвесанту. Он должен дать свою санкцию на инспекцию острова - ведь всё-таки они там ведут деятельность, и причём давно.";
			link.l1 = "Тогда нужно отправить курьера в Виллемстад.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "Проблема в том, что минхера Стайвесанта непросто застать в Виллемстаде, он постоянно в разъездах по делам Компании на своём галеоне...";
			link.l1 = "Но когда-то же он там бывает, я полагаю? Так или иначе, но обеспечить осмотр острова его законным владельцам голландцы обязаны. Почему бы не направить письмо губернатору Филипсбурга?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Минхер Мартин Томас, при всём уважении к нему - простой служащий, реальное управление осуществляет Компания. Барон, я решу эту проблему, не беспокойтесь, просто потребуется немного времени.";
			link.l1 = "Хорошо, время у меня есть. Ведь надо ещё посетить южные колонии, Гваделупу и Мартинику. Жаль, что капитан Шарль де Мор не будет сопровождать меня на этот раз - ему снова отправляться к берегам Эспаньолы...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Да-да, мы задерживаем нашего дорогого капитана своими скучными беседами! Шарль, принимайте в эскадру 'Эклятон', выдвигайтесь к Эспаньоле и выясните, действительно ли имеется реальная угроза Порт-о-Пренсу со стороны испанцев. Если имеется - устраните её. Впрочем, не мне вас учить, вы лучше меня всё знаете. Если же ничего не отыщете - не тратьте время понапрасну, вы нужны мне здесь. Жду вас с отчётом не позднее, чем через месяц. Удачи, мой друг!";
			link.l1 = "Спасибо, шевалье. Немедленно выхожу в море.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "Да, ещё, Шарль: я слышал, у вас проблемы с голландскими властями? Пожалуйста, уладьте этот вопрос как можно скорее, в недалёком будущем вам предстоит посещение голландских колоний. Как вы понимаете, под огнём фортов это будет невозможно.";
			link.l1 = "Хорошо, месье, я понял. Всё будет сделано.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "Да, ещё, Шарль: я заранее вас предупреждаю на всякий случай - избегайте конфликтов с голландцами. В скором будущем вам предстоит посещение голландских колоний. Как вы понимаете, под огнём фортов это будет невозможно.";
			link.l1 = "Хорошо, месье, я понял. Никаких ссор с голландцами.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Эклятон' затонул? Шарль, это же катастрофа! Что теперь скажет министр? Ох, как же вы меня подвели! Я был уверен в вашей опытности, а вы... Увы, но ответственность за это ляжет на вас. Я напишу рапорт, а вам лучше всего исчезнуть на время. Ни о какой дальнейшей службе, как вы понимаете, не может быть и речи.";
			link.l1 = "Кхм... Очень жаль, месье. Вижу, что мне и в самом деле лучше залечь на дно на месяц-другой, пока гнев министра утихнет. До свидания, поверьте, мне очень жаль, что так нелепо получилось.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Отлично! Пока у нас во флоте служат такие капитаны, как вы, нам нечего бояться козней кастильцев. Я завтра отправляю курьера в Порт-о-Пренс с депешей и почтой из Франции, и заодно намекну в личном письме монсеньору Жереми Дешамп дю Мюссаку, что неплохо было бы отблагодарить вас за службу, так что смею вас заверить, Шарль, что без заслуженной награды вы не останетесь\nА сейчас давайте перейдём к вашему следующему заданию. Да-да, мой друг, у меня для вас новое поручение, пусть на этот раз и не боевое, но весьма деликатное, и мне хотелось бы, чтобы его выполнили именно вы.";
			link.l1 = "Я весь внимание, шевалье.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Вы же помните мой разговор с месье Форже о Синт-Маартене? Надо обеспечить барону возможность инспекции этой колонии, и вы отправитесь на Кюрасао, в Виллемстад, к директору Компании Питеру Стайвесанту. Он сейчас там, и будет на месте ещё три недели. Также вам надо сопроводить флейт с товарами для Компании до Кюрасао и передать минхеру Стайвесанту письмо от меня.";
			link.l1 = "Это вся задача?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Да, капитан. С ответом от минхера Стайвесанта возвращайтесь ко мне. Месье Форже как раз должен будет вернуться из своей поездки на Мартинику и Гваделупу, и сможет наконец посетить Синт-Маартен, чего он так сильно желает.";
			link.l1 = "Хорошо. Я могу идти?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Ступайте, Шарль. С возвращением не затягивайте, барон не любит долго ждать. И обязательно на приём к Питеру Стайвесанту явитесь при параде, в форменном мундире! Всё должно выглядеть официально, вы понимаете меня?";
			link.l1 = "Конечно, шевалье. До свидания!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Благодарю, капитан, давайте его сюда... (читает)... Ну что же, великолепно! Питер Стайвесант сообщает, что барон Форже может посетить Синт-Маартен для инспекции и что губернатор Филипсбурга будет об этом извещён и окажет содействие. Думаю, что после визита барон примет правильное решение - оставить остров в аренде у голландцев\nА теперь самое приятное, капитан! У меня для вас две хорошие новости. Первая: с учётом боевых заслуг вы повышены в звании до чина 'коммодор'. Примите мои поздравления, монсеньор!";
			link.l1 = "Служу Отечеству!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "И вторая: губернатор Порт-о-Пренса прислал торговое судно с трюмом, полным товара, предназначенного вам: 500 больших мешков кофе и 500 ящиков какао. Это всё плоды наших плантаций на Эспаньоле, которые вы защитили от набега испанцев. Кроме того, для вас также предназначен особо ценный груз - 50 единиц бакаута. Что это такое, объяснять, думаю, не нужно. Ваш товар лежит на складе в магазине Капстервиля, и вы в любое удобное для вас время можете пойти к купцу и забрать его.";
			link.l1 = "Благодарю, шевалье! Прекрасные новости!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "И теперь по вашему очередному заданию: со дня на день на Сент-Кристофер вернётся барон Форже. Вы отвезёте его на Синт-Маартен и обеспечите ему охрану. Ну и, так сказать, присмотритесь к тому, что будет происходить в Филипсбурге, а затем доложите мне. Не покидайте город, капитан, как только барон прибудет сюда - мой вестовой разыщет вас и доложит.";
			link.l1 = "Всё ясно. Разрешите идти?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Идите. Пара дней отдыха на суше пойдёт вам на пользу.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "Да, шевалье, уже вернулись! Ваши голландские друзья у Синт-Маартена встретили нас огнём из пушек форта и атаковали эскадрой из трёх кораблей. Только благодаря мастерству капитана Шарля де Мора и его команды нам удалось уйти! Похоже, минхер Питер Стайвесант не очень желает видеть представителя короля Франции в Филипсбурге, шевалье?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "Как?!! Вот письмо Стайвесанта за его личной подписью, где он гарантирует...";
			link.l1 = "А комендант форта Филипсбурга, очевидно, получил другое послание от Стайвесанта, предписывавшее ему открыть огонь на поражение! И эскадра в засаде! Это случайность, шевалье? Нет! Нас там явно готовились встречать! Ядрами и картечью!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Барон, я прошу вас... Я во всём разберусь. Мы немедленно отправим нашего дорогого капитана Шарля де Мора снова на Кюрасао к Стайвесанту. У капитана большой опыт ведения деликатных дел... А сейчас я попрошу слуг приготовить для вас ванну и плотный обед.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Шарль, мой друг, вам нужно поспешить в Виллемстад. Возможно, Стайвесант ещё там. Если же нет - выясните, где он, и отыщите. При встрече расскажите об инциденте и затребуйте объяснений. Я полагаюсь на ваш опыт и ваш авторитет и поручаю провести все переговоры вам. Затем, не медля ни минуты, возвращайтесь и доложите мне о результатах встречи.";
			link.l1 = "Задача ясна, шевалье. Готовлю корабль и отправляюсь в путь.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "Не могу поверить...";
			link.l1 = "Кроме того, на обратном пути на меня вероломно напала голландская военная эскадра. Объясните мне, пожалуйста, шевалье, что тут происходит?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Друг мой, мне известно, насколько вы проницательны, поэтому скрывать от вас что-либо в данной ситуации я не стану. Единственное, о чём я вас попрошу - то, что вы услышите, не должно покинуть стен этого кабинета. Вы обещаете?";
			link.l1 = "Конечно, шевалье.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Хорошо. Я уверен, вас ждёт блестящая карьера во французском флоте. При моей поддержке, конечно, вы сможете получить чин вице-адмирала! Это к слову... Ну а теперь что касается голландцев и Синт-Маартена\nЕщё задолго до вашего прибытия на Синт-Маартене были обнаружены залежи соли. Сначала этим никто не интересовался, но потом на неё возник большой спрос у испанцев на Кубе и Эспаньоле - солить туши быков. Как вы сами понимаете, торговать с Испанией напрямую мы не можем, поэтому...";
			link.l1 = "... была создана 'прокладка' в виде голландской Вест-Индской торговой Компании...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Вы быстро, а главное - точно соображаете, Шарль! Именно так. Теперь же, узнав про инспекцию из Парижа, Стайвесант, очевидно, решил нагло прикарманить соляной бизнес полностью, в расчёте на то, что мы не рискнём афишировать наши торговые дела с испанцами. Но тут он просчитался. Никто не смеет безнаказанно запускать лапу в карман французского генерал-губернатора! И мы ему это покажем.";
			link.l1 = "Как я понимаю, барон Форже не должен быть в курсе...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Мой друг, вы совершенно правы, барону не нужно знать подробности. Достаточно того, что уже произошло: покушение на жизнь представителя французской короны, атака корабля дипломатической миссии, то есть - вас, а самое главное: де-факто аннексия острова Синт-Маартен! Этого достаточно, чтобы начать военные действия против Голландии.";
			link.l1 = "Война?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Именно! Мой друг, чин вице-адмирала у вас уже не за горами, вы понимаете?.. Представьте себя в адмиральском мундире на приёме в Лувре, и сам Людовик с почётом принимает такого высокопоставленного гостя... Мы должны поставить зарвавшихся голландцев на место! Стайвесант пожалеет о содеянном. Вы согласны?";
			link.l1 = "Согласен, шевалье. Голландцы должны ответить за свои бесчинства и подлость.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Отлично. Я сообщу барону принятое решение и отправлю курьеров во французские колонии, немедленно! А вы, мой друг, отдохните после дороги и зайдите ко мне завтра после девяти утра. Я подготовлю для вас боевое задание.";
			link.l1 = "Хорошо, монсеньор. Позвольте откланяться.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Я бы назвал это не войной, а принуждением к миру. И если Стайвесант одумается, мы будем только рады. Поэтому сейчас нам надо показать ему, что пытаясь присвоить остров Синт-Маартен, он теряет гораздо больше, чем приобретает. На это и будет ориентировано ваше задание, Шарль.";
			link.l1 = "Слушаю внимательно.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Синт-Маартен является перевалочной базой для голландских кораблей, следующих в Европу. Корабли Компании регулярно отдают якоря в гавани Филипсбурга. До сего момента эти воды для них были вполне безопасными. До сего момента, капитан!.. Вы отправитесь к берегам Синт-Маартена и будете караулить и захватывать торговые суда Компании\nДля перевозки дорогих грузов Компания использует ост-индцы - крепкие, хорошо вооружённые корабли с большим трюмом. Это и есть ваша цель. Захватите пять таких кораблей со всем товаром и приведите призами в гавань Капстервиля. После этого мы продолжим переговоры со Стайвесантом, и тогда, посчитав убытки, он, возможно, изменит своё решение.";
			link.l1 = "Задача ясна. Разрешите идти?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Монсеньор, я вынужден попросить вас принять посильное участие в финансировании этой операции. Это же месяцы плавания, постоянный ремонт и потери...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Боюсь, наши резервы истощены, Шарль. Содержание 'Эклятона' и боевые действия уже обошлись нам в полугодовой бюджет французских колоний. Вот, это всё, что я могу дать вам сейчас. Думайте о будущих наградах, Шарль! Вас ждёт большое будущее!";
			link.l1 = "Так точно!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Ступайте, и пусть удача сопутствует вам, мой друг.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "Вы выполнили задание полностью, капитан. Благодарю за отличную службу! И вам полагается часть прибыли от продажи трофеев - двести тысяч песо.";
				link.l1 = "Рад это слышать, месье!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Итак, вам осталось привести в наш порт ещё "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" голландских ост-индцев.";
				link.l1 = "Так точно, шевалье!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "И это ещё не всё. Я на днях немного поразмыслил... Шарль, вы действительно очень многое сделали для Франции. Устранение, прямо скажем, изменника Левассера, защита Сен-Пьера от коварного нападения Испании, успешный разгром форта колонии Сан-Хосе и получение с испанцев контрибуции в наказание за их дерзкую выходку... А после этого вы лично сопровождали представителя французской короны, прибывшего из Европы, и даже спасли ему жизнь, вырвавшись из засады голландцев в водах Филипсбурга!";
			link.l1 = "Месье, право, вы меня смущаете... Я просто выполняю свой долг.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Вы как всегда скромны, друг мой. И сейчас, во время выполнения очередной задачи по принуждению Голландии к миру, вы меня опять не подвели. Вы, не побоюсь этого слова - герой нации! Как генерал-губернатор французских колоний на архипелаге я имею при себе несколько экземпляров высшей награды Франции и... А, впрочем, прошу вас, прочитайте этот документ.";
			link.l1 = "За выдающиеся заслуги перед Францией... именем Его Величества короля Франции... наградить морского офицера на службе Франции капитана Шарля де Мора, сына Анри де Монпе... Шевалье, вы не шутите?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Ни капельки, мой друг. Я имею честь наградить вас по достоинству, вручив вам высшую награду Франции - Орден Святого Людовика! Каждый гражданин нашей страны должен знать своего героя! А Сен-Пьер вам вообще обязан жизнью! Вы заслужили этот Орден, Шарль.";
			link.l1 = "Право, не знаю, что и сказать... Благодарю вас, господин генерал-губернатор! Клянусь и дальше с гордостью служить Франции и не отступать перед лицом врага!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("Получен Орден Святого Людовика! Вы - герой нации!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Слова истинного офицера! Я искренне горжусь вами, Шарль. А теперь отдохните немного. Вы заслужили это. А я пока озабочусь переговорами со Стайвесантом - возможно, он уже осознал, что враждовать с нами ему гораздо убыточнее, нежели дружить. Не покидайте город, дня через два вы мне будете нужны.";
			link.l1 = "Хорошо, месье. Буду ждать ваших дальнейших распоряжений.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Да. Похоже, Стайвесант начал против нас ответные действия в альянсе с Испанией. Совместная испано-голландская эскадра берёт в кольцо Сент-Кристофер. Дозорные форта докладывают мне каждый час об их перемещениях.";
			link.l1 = "Осада?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Очевидно. На прямой штурм сразу не пошли, и это сыграет нам на руку. Нужно действовать срочно, капитан, пока враг не успел заблокировать весь остров.";
			link.l1 = "Что надо сделать?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "В Сент-Джонсе, что на Антигуа, сейчас находится английская военная эскадра полковника д'Ойли - он сейчас с визитом у сэра Джонатана Фокса. Вы должны пройти мимо вражеских кораблей и добраться до Антигуа. Там встретитесь с полковником, передадите ему моё письмо и попросите помощи.";
			link.l1 = "Вы думаете, полковник согласится нам помочь?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "Надеюсь, что да. Письмо должно убедить его в том, что награда за помощь будет весьма существенной... Кроме того, Шарль, нам нужно отправить весть капитану 'Эклятона', который сейчас находится у берегов Гваделупы, чтобы он поспешил к Сент-Кристоферу. Огневая мощь 'Эклятона' существенно поможет в предстоящем бою. Поскольку вы не можете разорваться на две части, к вам в эскадру войдёт наш военный курьерский люггер - вы должны вывести его в целости за кольцо врагов, и он отправится к Гваделупе, пока 'Эклятон' не ушёл на юг...";
			link.l1 = "Задача ясна. Пройти через осаду самому, провести курьерский люггер и поспешить в Сент-Джонс к полковнику д'Ойли с вашим письмом.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Всё верно. Вы готовы принять в эскадру ещё один корабль?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Выведу из состава одно судно и вернусь к вам.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Да.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Отлично. Держите письмо, люггер уже готов и ожидает ваших распоряжений.";
			link.l1 = "Не будем терять времени, шевалье!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Да-да, мой друг, ваша скромность мне давно известна. Вы настоящий офицер! И награда вас не минует, уверяю вас! Полагаю, после тяжёлой битвы вам необходим отдых? У вас есть целая неделя. Зайдите ко мне в кабинет на приём через семь дней - город как раз подготовит награду своему герою.";
			link.l1 = "Так точно, месье. Разрешите идти?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Идите и хорошенько отдохните. Потому что дальше нам предстоят серьёзные дела - как вы сами видите, мир с голландцами уже невозможен. А мы с уважаемым полковником пока что обсудим важные вопросы.";
			link.l1 = "Тогда до встречи через неделю, шевалье.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "Мы провели с полковником д'Ойли переговоры и я заручился его поддержкой. Англия окажет нам помощь в войне против голландцев. Ну а нам с вами сейчас необходимо нанести врагу ответный удар и восстановить справедливость - остров Синт-Маартен должен быть возвращён Франции. Эта задача поручается лучшему боевому капитану - вам, Шарль де Мор! Пока враг ещё не оправился после разгрома своей эскадры, мы атакуем Филипсбург и захватим его\nБой будет непростым. Сначала нужно уничтожить форт, затем сломить сопротивление гарнизона... (шёпотом) Вам также потребуется совершить марш-бросок в джунгли к соляному руднику, о котором я вам рассказывал, и выбить засевших там врагов...";
			link.l1 = "Задача действительно непростая, шевалье...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Я вас прекрасно понимаю, мой друг. Ваша эскадра будет усилена. Губернаторы Бас-Тера и Сен-Пьера должны были уже к этому моменту снарядить по одному военному кораблю - фрегату. Вам остаётся только посетить Гваделупу и Мартинику и принять под своё командование эти фрегаты. Если конечно вы сами пожелаете этого - в выборе методов и средств я вас никоим образом не ограничиваю. Также я выдаю вам денежную субсидию в размере 20 000 песо на закупку провизии и боеприпасов для вашего флагмана. Вот, получите...";
			link.l1 = "Хорошо, месье.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Также, как обычно, в вашем распоряжении линейный корабль 'Эклятон'. Он отремонтирован и снаряжён, стоит на рейде, и поговорив с капитаном, вы можете взять его под своё командование в любой удобный для вас момент.";
			link.l1 = "Отлично!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "И нельзя терять время, капитан. По сообщению моих лазутчиков, голландцы понимают, что грозит Синт-Маартену, и намерены многократно усилить его защиту. Однако двумя месяцами вы располагаете. Вы должны успеть за этот срок!";
			link.l1 = "Успеем... (шёпотом) Где находится рудник на Синт-Маартене? Ни на одной карте острова он не отмечен...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(шёпотом) Когда возьмёте штурмом город, прижмите к стенке наместника Филипсбурга, минхера Мартина Томаса, он расскажет. Этот голландец труслив и не осмелится упорствовать, я гарантирую.";
			link.l1 = "Хорошо, я понял. Тогда я отправляюсь?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Погодите, Шарль. Вы ещё не получили свою награду за спасение Сент-Кристофера. Примите от жителей города эти сундуки с золотом, а также огромную благодарность, которую нельзя оценить ни в каких деньгах!";
			link.l1 = "Очень приятно, месье!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			//Log_Info("Вы получили 10 сундуков с дублонами");
			PlaySound("interface\important_item.wav");
			dialog.text = "Теперь можете идти. Желаю удачи, капитан! Жду вас с победой!";
			link.l1 = "До встречи, шевалье.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "Также в моём распоряжении будет  и линейный корабль 'Эклятон'.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Кто бы мог предположить ещё какой-то год назад, что вы получите чин вице-адмирала, да, мой друг? Могу себе представить, как будет гордиться вами ваш отец, когда известие об этом достигнет Франции!";
			link.l1 = "Мой дорогой батюшка будет просто счастлив.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Вы заслужили своё положение во флоте! Синт-Маартен возвращён Франции, Стайвесант получил горький урок. Это большая победа! Но мы не должны останавливаться, нельзя дать голландцам передышки ни на день. Они должны почувствовать на себе всю тяжесть последствий своего предательства бывшего союзника! Полковник д'Ойли в Порт-Ройяле сейчас готовит военную эскадру: мы собираемся сломать врагу хребет, нанеся удар по Кюрасао. Но это немного позже, а пока нам надо одним выстрелом убить двух куропаток, Шарль\nСвои несметные богатства Компания нажила не только торговлей. Основной источник прибыли голландцев в регионе - работа рабов на плантациях. Если вы не в курсе, Шарль: Голландия - крупнейший рабовладелец и работорговец. Ост-индцы с грузом 'чёрной слоновой кости' регулярно прибывают на Кюрасао из западной Африки. И мне кое-что известно об этом, на горе Стайвесанту\nКак раз сейчас из Гвинеи на Карибы идут два голландцских ост-индца. В трюмах их полно чернокожих невольников. Где-то через десять дней караван будет проходить у берегов острова Тринидад в сторону Кюрасао. Ваша задача: найти этот караван и захватить оба ост-индца с грузом. Корабли сопровождения уничтожаете, рабов доставляете нашему союзнику полковнику д'Ойли на Ямайку. Это очень важно, Шарль, таким образом мы получим его расположение... ну, вы поняли меня\nМне жаль, что я совсем не оставляю вам времени на отдых, но дело действительно важное и деликатное, и поручить его я могу только вам.";
			link.l1 = "Служба не сахар, шевалье, мне ли это не знать? Готовлю судно и отчаливаю как можно скорее.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Желаю вам попутного ветра, вице-адмирал. А по возвращении на Сент-Кристофер, наш общий знакомый, месье Ноэль Форже, уже проведёт инспекцию в Филипсбурге, и я позабочусь о том, чтобы часть трофеев, доставшихся нам от голландцев, поступила лично вам.";
			link.l1 = "Буду премного благодарен, шевалье. Позвольте откланяться?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Ступайте. Удачи, мой друг!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Превосходно! Для вас не существует слова 'невозможно', Шарль. Когда-то я думал, что ваш брат - лучший военный офицер на Карибах, однако ему до вас очень далеко, уж простите меня за такое бесцеремонное сравнение. Я думаю, вы уже догадались, кого я отправляю к нашему дорогому полковнику для участия в штурме Виллемстада.";
			link.l1 = "Никак нет, монсеньор! Не могу знать!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ах, ваше знаменитое чувство юмора, мой дорогой друг! Ха-ха! Конечно же я отправляю вас, вице-адмирал. Достойнейшего из достойных. Вы готовы?";
			link.l1 = "Так точно, шевалье. Небольшой ремонт, пополнение припасов - и снова в путь.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "Не забудьте принять командование над 'Эклятоном'. Он отремонтирован и снаряжён, стоит на рейде. Маркиз Юбер Дассен уже весь в нетерпении и жаждет снова отправиться с вами в бой.";
			link.l1 = "Превосходно. Мощный корабль с дальнобойными кулевринами - то, что нужно для бомбёжки форта.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Задержитесь на минутку, Шарль. Наш друг, барон Форже, привёз для вас новости с Синт-Маартена.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "У меня для вас новости из Парижа. Ваше назначение на чин вице-адмирала подписано королём. Соответствующую бумагу вы получите. Так что ещё раз поздравляю вас!";
			link.l1 = "Благодарю, месье! Рад служить королю и Франции!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "И я, как всегда, очень рад слышать от вас эти слова. Шарль, может быть вы соизволите выпить со мной немного вина? Привезено прямиком из Парижа, здесь такого днём с огнём не найдёте!";
			link.l1 = "Спасибо, шевалье, но я, пожалуй, откажусь. Мне потом на корабль возвращаться, а негоже вице-адмиралу Франции стоять пьяным на квартердеке.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Что ж, почему бы и нет? Не каждый день и не каждому человеку выпадает возможность распивать вино с самим генерал-губернатором!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Да вы могли бы и отдохнуть, необязательно сразу на корабль возвращаться. Но желание ваше, и я его уважаю. Что же, тогда перейдём сразу к делу.";
			link.l1 = "Внимательно слушаю вас.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "И не каждому генерал-губернатору так везёт, чтобы вице-адмирал, лучший морской офицер, был ещё и его другом и мог бы сидеть с ним за одним столом и пить вино, привезённое с далёкой родины!";
			link.l1 = "За Францию!";
			link.l1.go = "patria_coat_03";
			link.l2 = "Ваше здоровье, шевалье!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "И за короля!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "И ваше, Шарль!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "Хм, прекрасное вино! Вы не находите?";
			link.l1 = "Да, вы оказались правы. Похоже на родное с моей далёкой Гаскони...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Вы немного ошиблись, мой друг: это Бордо. Впрочем, уверен, что гасконское ничуть не хуже!";
			link.l1 = "Иногда я уже начинаю забывать его вкус... Сколько времени прошло с тех пор, как я покинул Францию? Год? Два?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Эх, Шарль, казалось бы, только недавно мы с вами впервые встретились... кхм, при не самых лучших обстоятельствах. Простите, что вспоминаю это, но если бы кто-нибудь сказал мне тогда, что в тюремной камере передо мной стоит будущий первый человек после меня во французских колониях - я бы, наверное, рассмеялся.";
			link.l1 = "Inscrutabiles sunt viae Domini.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Простите, что вы сейчас сказали?";
			link.l1 = "Это латынь, шевалье. Пути господни неисповедимы. Никто не знает, что ему уготовила жизнь.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Вы не перестаёте меня удивлять, Шарль. И то верно: я вот, например, до сих пор не знал, что вы ещё и на латыни разговариваете. Но с другой стороны, в какой-то мере мы и сами куём свою судьбу - разве нет?";
			link.l1 = "Я думаю, что верно и то, и другое. Одному Господу известно, что с нами будет дальше. Но упорных он вознаграждает.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Не могу не согласиться. Я ведь помню, как выдал вам патент морского офицера и вручил этот мундир. А теперь передо мной стоит сам вице-адмирал!";
			link.l1 = "Время быстро летит, шевалье.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Да уж... И даже на вашем мундире я вижу следы от сабель: какие-то порезы уже зашиты, а какие-то явно свежие. Это нужно исправить.";
			link.l1 = "Что вы имеете ввиду, господин генерал-губернатор?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "Помимо того, что вы теперь официально стали вице-адмиралом французского флота на Карибском архипелаге, у меня есть для вас ещё один подарок.";
			link.l1 = "Вы меня смущаете, шевалье. Что же это за подарок?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Я договорился со своим личным портным - лучшим во французских колониях! - чтобы он пошил для вас соответствующий вашему чину мундир. Об оплате не беспокойтесь: я уже всё уладил.";
			link.l1 = "Премного благодарен! Обязательно навещу вашего портного. Где мне его искать?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Он должен сейчас находиться в портовом управлении: из метрополии прибыл новый курьерский корабль вместе с мелкими посылками. Наш портной всегда заказывает себе некоторые материалы, которые здесь найти сложно.";
			link.l1 = "Значит, схожу в портовое управление. Ещё раз спасибо вам, монсеньор!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "А сейчас, я уверен, вам надо хорошо отдохнуть. Я предоставляю вам месячный отпуск, и постарайтесь провести его как можно лучше. Никаких дел, никаких забот. Поручите всё вашим офицерам и хорошенько отдохните. Можете воспользоваться комнатами в моей резиденции. Слуги сделают ваш отдых максимально комфортным. А через месяц мы с вами вновь встретимся - у меня будет к вам очень деликатный разговор.";
			link.l1 = "Хорошо, шевалье. До встречи!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Да, Шарль. Я думал, что смогу справиться сам, но... увы, я опять вынужден просить вас позволить мне воспользоваться вашими талантами. Но для начала я хочу передать вам вот это: триста тысяч песо и пять сундуков с дублонами. Это львиная доля контрибуции, уплаченная мне Стайвесантом по договору. Я считаю, что вы заслужили именно такую часть, ибо фактически сделали всю работу. Примите. Вы довольны, друг мой?";
			link.l1 = "Деньги никогда и никому не мешали, монсеньор, я прочно усвоил этот урок.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ах, вице-адмирал, надеюсь, вы на меня не в обиде за прошлое?.. Вы теперь герой нации, вы в курсе? Как вы чувствуете себя в новом чине? Помните, что много достойнейших офицеров десятилетиями поднимаются по карьерной лестнице, но без опытной руки... так и остаются в чине коммандера. Однако у вас, мой дорогой, уникальная способность постоянно совершать невозможное! И высокопоставленный покровитель, который, в то же время, ваш друг.";
			link.l1 = "Благодарю вас за тёплые слова, Ваше Превосходительство. У меня ощущение, что я достиг практически всего в этом регионе. С вашей помощью, разумеется. Полагаю, я теперь могу спокойно заниматься своими делами? Пора позаботиться о семье.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Хотите жениться, Шарль? А-ха-ха! Ткните пальцем в любую парижскую красотку - и она отдастся вам немедленно! Но, к сожалению, с этим придётся немного повременить. Вы мне нужны здесь, мой друг, по крайней мере - ещё немного.";
			link.l1 = "Мне кажется, Франция сильна на Архипелаге, как никогда. Союз с англичанами, мирный договор с Компанией. Нет больше проблемных... левассеров. Так?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Государствам, как и людям, всегда будет мало того, что у них уже есть... И у нас появился новый проблемный 'левассер', вице-адмирал...";
			link.l1 = "Вот как? И кто же это?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "Это наш с вами общий знакомый, барон Ноэль Форже. Вы помните, для чего он сюда пожаловал?";
			link.l1 = "Кхм... Вы что-то говорили о Французской Вест-Индской торговой Компании. В Париже решили создать такую же контору, как у голландцев?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Именно. Аналог голландской Компании. Но сделать это с нуля очень сложно, ведь за конторой Стайвесанта стоят десятилетия торговли с разными континентами, развитая сеть агентов и мощный флот торговых кораблей. У Франции этого нет, и, если вы не в курсе, Шарль, король сейчас испытывает серьёзную нехватку денег. Они думают поправить финансовое положение метрополии за счёт торговли здесь, но не понимают, с чем придётся столкнуться\nКонкуренция в лице англичан и голландцев, территориальные амбиции испанцев, цветущее буйным цветом пиратство. Каждый торговый флейт нуждается в сопровождении военного судна, иначе рискует не добраться до места назначения. А мощного флота из ост-индцев, как у голландцев, или из галеонов, как у испанцев, у нас нет.";
			link.l1 = "Но вы же объясняли всё это барону? Про тех же пиратов?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Конечно. И про то, что после изгнания пиратов с Тортуги в результате вашей операции по смещению Левассера, они имеют на Францию зуб. Я организовывал за обедами встречи с разными людьми, которые подтверждали мои слова, но увы - барона это не убедило. Его сюда послали министры, и он должен... Вот так.";
			link.l1 = "Гм...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "Ну и не буду скрывать, ибо вы и сами это понимаете - торговая контора на Архипелаге, с прямым управлением из Парижа мне... нам с вами, вице-адмирал... тут ни к чему.";
			link.l1 = "Понимаю.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Видите, друг мой, я с вами предельно честен... Итак, я до последнего надеялся, что месье Форже разочаруется в идее создания торговой Компании, но... этого не случилось. Я исчерпал все средства воздействия на барона, теперь в игру должны вступить вы.";
			link.l1 = "Кхм... Что, как с Левассером?..";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "Ох, ну что вы, за кого вы меня принимаете! Барон - влиятельное лицо в Париже, друг министра финансов! К тому же, физическое устранение ничего не даст: из Парижа просто пришлют нового чиновника. Надо убить саму идею о возможности организации торговой компании тут, понимаете, Шарль? Чтобы барон, вернувшись во Францию, доложил, что это финансово рискованно, неоправданно...";
			link.l1 = "У вас есть предложения, монсеньор?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Увы, уже нет, Шарль. Я перепробовал всё. Пугал недостатком кораблей и денежных средств, голландцами, пиратами... Всё без толку.";
			link.l1 = "Видимо, нужно что-то более серьёзное, нежели просто слова. Гм... Пиратами, говорите?..";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Я вижу, у вас появилась идея, мой друг? Я не сомневался. У вас великолепный ум. Убедите нашего барона... А я позабочусь о том, чтобы ваш отец получил сумму денег, достаточную для того, чтобы ваше родовое поместье засияло роскошью, достойной Лувра. Обещаю вам, Шарль.";
			link.l1 = "Хорошо, шевалье. Задание мне ясно.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Клянусь вам, Шарль, что в случае успеха вы не пожалеете. Можете быть уверены в этом. Я хоть раз обманул вас, мой друг?";
			link.l1 = "Никак нет, монсеньор. Где мне найти барона?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Он сейчас в Порт-о-Пренсе. Очень понравились ему бескрайние поля и долины Эспаньолы, как он сказал...";
			link.l1 = "Хорошо. А теперь разрешите идти.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Именно так. Барон мне всё рассказал. После того, что ему пришлось пережить... Однако, вы умеете объяснять доходчиво, вице-адмирал! Мне стоит этому у вас поучиться!";
			link.l1 = "Я многому научился у вас, шевалье.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Мой друг, я в долгу перед вами. Смею обещать вам, что ваш дорогой батюшка больше не будет нуждаться ни в чём, а ваше родовое поместье будет лучшим во всей провинции... и одно из лучших во всей Франции. Кроме того, я выплачиваю вам 100 000 песо - надеюсь, это покроет ваши издержки с пиратами...";
			link.l1 = "Как приятно это слышать, монсеньор!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "Также я приготовил для вас особенный подарок. Уверен, вы оцените значимость этой вещи и поймёте глубину моей благодарности за вашу преданную службу! Итак, вице-адмирал Шарль де Мор, я вручаю вам свой личный церемониальный меч мальтийского ордена! Это великолепное оружие как раз подойдёт к вашему мундиру! Если вы решите вернуться в Париж, барон Ноэль Форже пообещал представить вас королю - вы должны быть на приёме при полном параде: в мундире и с этим наградным оружием! И вас ждёт дальнейшая славная карьера в военно-морском флоте!";
			link.l1 = "Просто изумительный по красоте меч! Спасибо, монсеньор, я, право, не заслужил подобной чести...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			//Log_Info("Вы получили Мальтийский меч");
			PlaySound("interface\important_item.wav");
			dialog.text = "Заслужили!.. А пока вы остаётесь здесь, вас ждут небольшие перемены. Приятные, конечно. Вице-адмирал Шарль де Мор, я назначаю вас губернатором Синт-Маартена!";
			link.l1 = "Кхах! Я не ослышался?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Нет, мой друг. Теперь вы губернатор освобождённого вами Синт-Маартена.";
			link.l1 = "Шевалье, позвольте мне отказаться. Я не желаю быть прикованным к одному унылому островку! И всякие хозяйственные дела... Это не моё!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Отказа не принимаю. Друг мой, не беспокойтесь: вы будете жить, как раньше. Все скучные дела возьмёт на себя нынешний временный управляющий. А вы будете фактический губернатор. Шарль, вы разве не понимаете, почему на Синт-Маартен назначены именно вы? Сейчас самый удобный момент для этого, и ни у кого не возникнет вопросов. А мне на Синт-Маартене губернатором нужен МОЙ человек, вы понимаете, о чём я?";
			link.l1 = "Соляной рудник?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Конечно! И вторая приятная новость: с этого дня, каждый месяц, 15 числа, вы будете получать часть прибыли рудника и прибыли от торговых операций с д'Ойли. Ваш пассивный доход составит 100 000 песо ежемесячно.";
			link.l1 = "Хех! Очень рад! Спасибо, шевалье. Ну, если я не буду ничем не ограничен, то я согласен стать губернатором. А если я решу отплыть во Францию?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Когда решите - тогда и отплывёте, а я, хоть и очень расстроюсь, отыщу вам замену. Но это ещё не всё: у меня письмо из Франции от вашего отца. Возьмите.";
			link.l1 = "От моего батюшки? Как я рад!.. Хорошо, монсеньор, договорились. Теперь я могу идти? Хочу прочесть письмо... Новых дел пока не намечается?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Пока нет, губернатор, но если появятся, я знаю, где вас искать. Удачи, Шарль!";
			link.l1 = "Взаимно, шевалье!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "Чёрт возьми, какая беда! Боюсь, мы теперь не оберёмся хлопот. Это вы приложили к этому руку, Шарль? Скажите честно. Это не случайность?";
			link.l1 = "Просто всё пошло немного не так...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "Чёрт возьми, какая беда! Боюсь, мы теперь не оберёмся хлопот. Не самое лучшее место барон выбрал для своей кончины! Вы точно не помогали ему перейти в мир иной?";
			link.l1 = "Вы что, шевалье! Конечно нет!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Чёрт возьми, какая беда! Боюсь, мы теперь не оберёмся хлопот. Это точно не вы помогли ему перейти в мир иной?";
			link.l1 = "Вы что, шевалье! Конечно нет!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Ясно. Ладно, друг мой, возможно, всё не так и страшно. Лихорадка - есть лихорадка, ведь так? А до прибытия нового инспектора из министерства мы тут немного приберёмся и будем встречать гостей во всеоружии... И нам нужно теперь, Шарль, свести к минимуму все наши контакты. Вы, надеюсь, понимаете, почему?";
			link.l1 = "Конечно.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Ясно. Ладно, друг мой, возможно, всё не так и страшно. Стычки на Карибах - обычное дело, ведь так? А до прибытия нового инспектора из министерства мы тут немного приберёмся и будем встречать гостей во всеоружии... И нам нужно теперь, Шарль, свести к минимуму все наши контакты. Вы, надеюсь, понимаете, почему?";
			link.l1 = "Конечно.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Ясно. Ладно, друг мой, возможно, всё не так и страшно. Пираты - есть пираты, ведь так? А до прибытия нового инспектора из министерства мы тут немного приберёмся и будем встречать гостей во всеоружии... И нам нужно теперь, Шарль, свести к минимуму все наши контакты. Вы, надеюсь, понимаете, почему?";
			link.l1 = "Конечно.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "В любом случае, мой друг, вы сделали всё, что могли. И это лучше, чем совсем ничего. Я рад, что судьба свела меня с вами. Ваш чин остаётся при вас, и я уверен, вас ждёт блестящая карьера во Франции. И я думаю, что вам уже пора возвращаться в Париж. Вот, у меня письмо от вашего отца. Держите.";
			link.l1 = "От моего батюшки? Как я рад!.. Хорошо, монсеньор, договорились. Никаких контактов, полная конспирация, и по возможности - в Париж. Теперь я могу идти? Хочу прочесть письмо...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Ступайте, Шарль. Удачи вам!";
			link.l1 = "Взаимно, шевалье!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Именно так. Однако, вы умеете объяснять доходчиво, вице-адмирал! Мне стоит этому у вас поучиться!";
			link.l1 = "Я многому научился у вас, шевалье.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Мой друг, я в долгу перед вами. Смею обещать вам, что ваш дорогой батюшка больше не будет нуждаться ни в чём, а ваше родовое поместье будет лучшим во всей провинции... и одно из лучших во всей Франции. Кроме того, я выплачиваю вам 100 000 песо - надеюсь, это покроет ваши дорожные издержки, и ещё немного останется вам на хороший отдых.";
			link.l1 = "Как приятно это слышать, монсеньор!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "Как ты мог, Шарль! Как ты мог так... поступить со мной!";
			link.l1 = "Кхм...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "Я знаю, что это ты. Не пытайся отрицать. Без твоего участия барон Форже никогда бы не смог получить ни показаний управляющего рудника Синт-Маартена, ни узнать, где находится рудник, ни, тем более, завладеть документами Питера Стайвесанта. Твоё имя нигде не прозвучало, но я знаю: это был ты. Почему, Шарль?.. Просто ответь: почему? Мишель? Миллион песо? Левассер? Или пост генерал-гебернатора?";
			// belamour legendary edition -->
			link.l1 = "Нашу первую встречу помните, шевалье? Как вы ставили меня на место? Как вымогали миллион? Я просто хотел, чтобы однажды мы поменялись местами. Больше мне вам нечего сказать.";
			link.l1.go = "patria_prison_2";
			link.l2 = "За Левассера. Долг в миллион я ещё могу понять. Я трудился, убивал, зарабатывал, грабил, но возместил вам весь ущерб. А вам было этого мало. Вы, шевалье, отправили меня на самоубийственное задание против короны, дабы я ещё больше укрепил вашу личную власть! Ваше вероломство требовало ответа. И вы его получили!";
			link.l2.go = "patria_prison_2";
			link.l3 = "Амбиции, шевалье. В этом странном новом мире я уже достиг почти всего, что мог. Пост генерал-губернатора показался мне достойной внимания целью. Я многому научился у вас. Прощайте!";
			link.l3.go = "patria_prison_2";
			link.l4 = "Сам не знаю, если честно. Может, потому, что мне импонирует барон и его верная служба нашей стране? В любом случае, у вас сейчас будет достаточно времени подумать над этим вопросом за меня. Прощайте!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Рад вас видеть, Шарль. Наслышан о ваших подвигах. Блестящая работа!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Это ещё не всё, Ваша Светлость.";
					link.l1.go = "PZ2";
				}
				else
				{
					link.l1 = "Теперь я могу получить от вас письменный приказ, согласно которому мой брат будет освобождён из-под ареста?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Приветствую вас, Шарль. Проходите, мне уже обо всём доложили.";
				link.l1 = "Доложили? Возможно, это какая-то ошибка, Ваша Светлость. Я пришёл, чтобы отчитаться об успешном завершении вашего задания, но вижу, что вы пребываете не в лучшем расположении духа.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ2":
			dialog.text = "Вот как? Что вы имеете в виду, капитан?";
			link.l1 = "Вместе со своими людьми мне удалось схватить Левассера живым и доставить его вам. Как только мы закончим, я прикажу привести его.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Это правда? Я и подумать не мог о чём-то подобном! Воистину, блестящая работа, Шарль! Сомневаюсь, что даже ваш прославленный брат смог бы лучше. Ваш отец может гордиться вами, друг мой.";
			link.l1 = "Благодарю за тёплые слова, шевалье.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ5":
			dialog.text = "Очень хорошо, Шарль. Я доволен вами.";
			link.l1 = "Теперь я могу получить от вас письменный приказ, согласно которому мой брат будет освобождён из-под ареста?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Видимо, мне всё же стоило иметь ввиду, что вы - не ваш брат, не военный и не тайный агент, что у вас ещё не было опыта в подобного рода операциях. Не стоило устраивать драку с солдатами прямо на улицах Тортуги. Возникнут вопросы, в том числе и ко мне. И у людей отнюдь не мелкого калибра, как вы понимаете.";
			link.l1 = "Прошу прощения, шевалье. Как вы понимаете, Левассер бы не согласился уйти со своего поста без сопротивления.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Я это понимаю, однако... Впрочем, неважно. Для первой операции - вполне неплохо. Напишу в рапорте, что он напал на ревизора и его эскорт во время официального визита с проверкой.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Ваша Светлость, если это как-то исправит положение, то я могу привести к вам Левассера. Нам с моими людьми посчастливилось пленить его в укромном месте, а на улице нам уже преградили путь прочие его... приспешники.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Теперь я могу получить от вас письменный приказ, согласно которому мой брат будет освобождён из-под ареста?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "Что вы сказали, Шарль? Повторите.";
			link.l1 = "Франсуа Левассер прямо сейчас находится в моём трюме и готов к передаче в ваши надёжные руки, месье.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Забудьте всё, что я до этого сказал. Я определённо погорячился. Блестящая работа. Это определённо, как вы сказали, 'исправит положение'. С лихвой. Даже не знаю, удалось ли бы нечто подобное вашему прославленному брату.";
			link.l1 = "Благодарю, шевалье.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Вы подаёте большие надежды, друг мой! Ваши бы таланты да на благо Родине! Но постарайтесь впредь действовать более... незаметно. Зачастую наши действия не терпят огласки. Ах да, и кое-что ещё...";
			link.l1 = "Да, Ваша Светлость?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}