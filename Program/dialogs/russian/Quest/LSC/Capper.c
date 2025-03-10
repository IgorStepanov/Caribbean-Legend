// Чад Каппер - боцман Акулы и тюремщик
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
		
		// вариант R
		case "Chimiset":
			dialog.text = "Так-так... Значит, это и есть наш таинственный воришка? Хм... А не похож на мелкого жулика.";
			link.l1 = "Послушайте, уважаемый, вы ошибаетесь. Я только с час назад вообще появился в этом месте. В трюме этого чёртового корабля, за дверью которого меня и схватили. Откуда же я мог знать, что у вас там запретная зона, чёрт побери?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Да? Неужели? Складно врёшь... И откуда же ты прибыл, скажи на милость?";
			link.l1 = "С Мэйна... Через эту каменную статую. Как точно - я и сам не понимаю.";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Через статую? Ха-ха! Да ты ещё и шутник, однако... Ладно, я сам тебе скажу: ты проплыл через пролом в корпусе корабля и намеревался проникнуть на наш склад. Но твоя рожа мне и впрямь незнакома, а я думал, что знаю всех ривадос в лицо...";
			link.l1 = "Каких ещё ривадос? Не знаю я никаких ривадос! И знать никогда не знал! Послушайте, я повторяю, я только час назад...";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Не ори, я всё понимаю с первого раза, не тупой. Да, я уже слышал твой вздор про то, что ты пришёл сюда через какую-то статую, и нахожу твою шутку очень забавной. Посмеёмся вместе? Ха-ха-ха!.. Ты чего не смеёшься, а? Твой розыгрыш удался... ривадос. Но шутки теперь окончены. Я сгною тебя в клетке, обещаю.";
			link.l1 = "Да никакой я не ривадос! Я вообще впервые слышу это слово!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Впервые слышишь? Хм... А может, ты и впрямь не из них? Так ты не из них, я тебя спрашиваю?!";
			link.l1 = "Если ты имеешь в виду этих пресловутых ривадос, о которых ты мне талдычишь уже в который раз, то - нет.";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Действительно? Хорошо... Тогда докажи это. Внизу, в помещении где мы держим заключённых, в клетке сидит один из ривадос. Он опасный колдун. Убей его, и я не только поверю, что ты не из них, но и прощу тебе твоё незаконное вторжение на наш склад\nНу, так что? Готов доказать? Не бойся, колдун не вооружён, у него нет даже иголки... ну, разве что испепелит тебя каким-нибудь заклинанием, вроде того, что перенесло тебя в трюм Сан-Августина...";
			link.l1 = "Если бы ты видел это заклинание в действии, то перестал бы зубоскалить. Если бы вообще в живых остался...";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Довольно разглагольствований! Ты идёшь, или нет? Если да, то бери вот это мачете и иди расправься с колдуном. Если нет - отправишься в клетку до конца дней своих. Что выбираешь?";
			link.l1 = "Из двух зол выбираю меньшее. Давай сюда мачете.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Молодец. Держи. А теперь ступай и завали этого черномазого. Его клетка отперта. И не вздумай дурить: попробуешь выкинуть какой-нибудь номер - прикончим на месте. Вперёд!";
			link.l1 = "О чём речь? Или ты боишься, что я этим куском железа уложу вас всех?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "Мне надоело слушать тебя. Марш в трюм и делай, что сказано!";
			link.l1 = "Хорошо-хорошо, не кипятись. Уже иду...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Ты испытываешь моё терпение, недоносок! И оно скоро иссякнет.";
			link.l1 = "Хорошо-хорошо, не кипятись.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Завалил этого негритянского колдуна? Молодец... Я очень и очень рад. Ты доказал, что ты не ривадос.";
			link.l1 = "Так ты наконец выпустишь меня из этой чёртовой лоханки? Мне срочно нужно встретиться с Акулой.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Встретишься, встретишься... Начнёшь с того, что проложишь ему дорожку... в ад!";
			link.l1 = "Что?!";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ха! Вот так номер! Что ты делаешь здесь, в моей тюрьме?";
			link.l1 = "Ты - Чад Каппер, тюремщик, как я понимаю? Меня зовут "+GetFullName(pchar)+", и я пришёл от Акулы Додсона. Он дал мне ключ от дверей.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "От адмирала? Хм, тогда понятно. Ты - его новый мальчик на побегушках?";
			link.l1 = "Повежливее, уважаемый. Я ни к кому в прислугу не нанимался, ни к Акуле, ни к тебе, и выслушивать в свой адрес подобные выпады не намерен.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ха-ха, ты мне нравишься, парень! Забудь о том, что я тебе сказал... Так по какому делу пожаловал?";
			link.l1 = "Акула отдал распоряжение об освобождении содержащегося здесь заключённого по имени Чимисет.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "Колдуна ривадос? Хм. Очень странно, я удивлён, право...";
			link.l1 = "Акула так и сказал - освободить Чимисета. Он хочет наладить отношения с ривадос.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "А-а, ну тогда понятно. Хорошо, я пошлю человека на пост к ривадос, чтобы они прислали сюда пару бойцов и забрали своего клоуна.";
			link.l1 = "А просто выпустить ты его не можешь?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Могу, конечно, но это будет опасно для него. Чимисет слишком известная фигура на Острове, и я не дам за его жизнь и ломаного гроша, когда он будет проходить через 'Эсмеральду' - территорию его лютых врагов нарвалов. А другого выхода с 'Тартаруса' нет - не отправлять же старикашку вплавь вокруг острова!\nA если его убьют ненароком, к кому ривадос потом предъявят претензии? Конечно - к нам, и лично ко мне! Как ты понимаешь, мне проблемы не нужны. Так что выпущу я колдуна отсюда только под конвоем бойцов его клана. Может, ты хочешь поговорить с Чимисетом? Занятный тип...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Я уже разговаривал с ним. Действительно, оригинал. Ладно, мне пора. До встречи, Чад!";
			else link.l1 = "Именно это я и собирался сделать. Пойду, поболтаю с ним.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Я сейчас пошлю гонца к ривадос, чтобы они забрали колдуна. Не переживай, парень, ступай спокойно.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "...он наверняка уже приложился к бочонку, я уверен. Это его любимый виски, чёртов ирландец. Ждать осталось недолго - мышьяка я насыпал столько, что табун лошадей передохнет...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "А? Чёрт возьми, что тебе здесь надо? Проваливай!";
			link.l1 = "Долго же я тебя искал... отравитель. Странно, что второго негодяя, Циклопа, тут нет. Значит, метишь на место Акулы?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ха-ха, Акула - уже труп! А ты сейчас отправишься вслед за ним, шпион!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "...хорошее получится пойло. Проклятый ирландец давно мечтал об этом виски, так что вылакает пинту сразу же. Так, где мышьяк? Насыпем побольше, чтобы наверняка... А потом наш друг Фацио отнесёт бочонок адмиралу, как подарок от нарвалов, ха-ха! Так, любезный Джузеппе? Ты же ещё хочешь жить?\nАргх! Смотри-ка, у нас гости! Тебе чего здесь надо, болван? Проваливай, пока цел!";
			link.l1 = "Твой план провалился, Каппер. Я шёл по твоим следам, и сразу понял, и где ты, и что ты задумал вместе с Циклопом. Брось мышьяк! Тебе не удастся отравить Акулу.";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "Ах ты, шпик! Ну, тогда ты проложишь дорожку в ад своему любимому адмиралу! Ребята, к бою!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}