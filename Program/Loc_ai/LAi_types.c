
//Подключённые типы для интелекта

//Игрок
#include "Loc_ai\types\LAi_player.c"
//Офицер
#include "Loc_ai\types\LAi_officer.c"
//Горожанин
#include "Loc_ai\types\LAi_citizen.c"
//Охраник
#include "Loc_ai\types\LAi_guardian.c"
//Патруль
#include "Loc_ai\types\LAi_patrol.c"
//Воин
#include "Loc_ai\types\LAi_warrior.c"
//Торговец
#include "Loc_ai\types\LAi_merchant.c"
//Стоячий человек
#include "Loc_ai\types\LAi_stay.c"
//Сидячий человек
#include "Loc_ai\types\LAi_sit.c"
//Бармен
#include "Loc_ai\types\LAi_barman.c"
//Официантка
#include "Loc_ai\types\LAi_waitress.c"
//Нищий
#include "Loc_ai\types\LAi_poor.c"
//Губернатор, сидячий на месте
#include "Loc_ai\types\LAi_huber.c"
//Губернатор, ходячий по помещению
#include "Loc_ai\types\LAi_huberstay.c"
//Священик
#include "Loc_ai\types\LAi_priest.c"
//Актёр
#include "Loc_ai\types\LAi_actor.c"
//Хозяин дома
#include "Loc_ai\types\LAi_owner.c"
//Носильщик
#include "Loc_ai\types\LAi_carrier.c"
//Жители ГПК, не внутрянка
#include "Loc_ai\types\LAi_LSCout.c"
//Сидящий не земле
#include "Loc_ai\types\LAi_groundSit.c"
//Обезьяна-монстр
#include "Loc_ai\types\LAi_monkey.c"
//Спящий
#include "Loc_ai\types\LAi_lay.c"
// Оглушенные
#include "Loc_ai\types\LAi_stunned.c"
// Рыбаки на пирсе
#include "Loc_ai\types\LAi_fisher.c"
// Сидящие на лавочках
#include "Loc_ai\types\LAi_benchsit.c"
// Кузнецы
#include "Loc_ai\types\LAi_blacksmith.c"
// Музыканты
#include "Loc_ai\types\LAi_musician.c"
// Шлюхи
#include "Loc_ai\types\LAi_horse.c"
// Пьяницы
#include "Loc_ai\types\LAi_drinker.c"


//------------------------------------------------------------------------------------------
//Player
//------------------------------------------------------------------------------------------

//Установить персонажу тип игрока
void LAi_SetPlayerType(aref chr)
{
	//Тип персонажа по умолчанию
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	//Шаблон специальный
	LAi_type_player_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
	SendMessage(&locCamera, "ll", MSG_CAMERA_SPECIALMODE, false);
}

//------------------------------------------------------------------------------------------
//Officer
//------------------------------------------------------------------------------------------

//Установить персонажу тип офицера
void LAi_SetOfficerType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_officer_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
	//LAi_DelAdjustFencingSkill(chr);
}

//Установить персонажу тип офицера
void LAi_SetFollowerType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_follower_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
	//LAi_DelAdjustFencingSkill(chr);
}

//------------------------------------------------------------------------------------------
//Citizen
//------------------------------------------------------------------------------------------

//Установить персонажу тип горожанина
void LAi_SetCitizenType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_citizen_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип горожанина, без перемещения в группу
void LAi_SetCitizenTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_citizen_Init(chr);
}

//------------------------------------------------------------------------------------------
//Guardian
//------------------------------------------------------------------------------------------

//Установить персонажу тип стражника
void LAi_SetGuardianType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_guardian_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
// boal	if (!IsOfficer(chr))
	//{
	//	LAi_SetAdjustFencingSkill(chr, -4.0, 2.0);
	//}
}

//Установить персонажу тип стражника, без перемещения в группу
void LAi_SetGuardianTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_guardian_Init(chr);
}

//------------------------------------------------------------------------------------------
//Patrol
//------------------------------------------------------------------------------------------

//Установить персонажу тип патруля
void LAi_SetPatrolType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_SetPatrolTypeNoGroup(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
// boal	if (!IsOfficer(chr))
//	{
//		LAi_SetAdjustFencingSkill(chr, -4.0, 2.0);
//	}
}

//Установить персонажу тип патруля, без перемещения в группу
void LAi_SetPatrolTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_patrol_Init(chr);
}

//------------------------------------------------------------------------------------------
//Warrior
//------------------------------------------------------------------------------------------

//Установить персонажу тип война
void LAi_SetWarriorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_warrior_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
//	if (!IsOfficer(chr))
//	{
//		LAi_SetAdjustFencingSkill(chr, -4.0, 2.0);
//	}
}

//Установить персонажу тип война, без перемещения в группу
void LAi_SetWarriorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_warrior_Init(chr);
}


//------------------------------------------------------------------------------------------
//Merchant
//------------------------------------------------------------------------------------------

//Установить персонажу тип торговца
void LAi_SetMerchantType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_merchant_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип торговца, без перемещения в группу
void LAi_SetMerchantTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_merchant_Init(chr);
}

//------------------------------------------------------------------------------------------
//Stay
//------------------------------------------------------------------------------------------

//Установить персонажу тип стоячего
void LAi_SetStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_stay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип стоячего, без перемещения в группу
void LAi_SetStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_stay_Init(chr);
}

//------------------------------------------------------------------------------------------
//Sit
//------------------------------------------------------------------------------------------

//Установить персонажу тип сидячего
void LAi_SetSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_sit_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип сидячего, без перемещения в группу
void LAi_SetSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_sit_Init(chr);
}


//------------------------------------------------------------------------------------------
//Barmen
//------------------------------------------------------------------------------------------

//Установить персонажу тип бармена (only man)
void LAi_SetBarmanType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_barman_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип официантки, без перемещения в группу (only man)
void LAi_SetBarmanTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_barman_Init(chr);
}

//------------------------------------------------------------------------------------------
//Waitress
//------------------------------------------------------------------------------------------

//Установить персонажу тип официантки (only woman)
void LAi_SetWaitressType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_waitress_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип официантки, без перемещения в группу (only woman)
void LAi_SetWaitressTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_waitress_Init(chr);
}


//------------------------------------------------------------------------------------------
//Poor
//------------------------------------------------------------------------------------------

//Установить персонажу тип бедника
void LAi_SetPoorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_poor_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип бедника, без перемещения в группу
void LAi_SetPoorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_poor_Init(chr);
}

//------------------------------------------------------------------------------------------
//Huber
//------------------------------------------------------------------------------------------

//Установить персонажу тип губернатора
void LAi_SetHuberType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huber_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_HUBER);
}

//Установить персонажу тип губернатора, без перемещения в группу
void LAi_SetHuberTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huber_Init(chr);
}

//------------------------------------------------------------------------------------------
//HuberStay
//------------------------------------------------------------------------------------------

//Установить персонажу тип губернатора, ходячего по комнате
void LAi_SetHuberStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_HUBER);
}

//Установить персонажу тип губернатора, ходячего по комнате, без перемещения в группу
void LAi_SetHuberStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
}

//------------------------------------------------------------------------------------------
//Priest
//------------------------------------------------------------------------------------------

//Установить персонажу тип священика
void LAi_SetPriestType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_priest_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип священика, без перемещения в группу
void LAi_SetPriestTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_priest_Init(chr);
}


//------------------------------------------------------------------------------------------
//Actor
//------------------------------------------------------------------------------------------

//Установить персонажу тип актёра
void LAi_SetActorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_actor_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
	if(IsMainCharacter(chr)) SendMessage(&locCamera, "ll", MSG_CAMERA_SPECIALMODE, true);
}

//Установить персонажу тип актёра, без перемещения в группу
void LAi_SetActorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_actor_Init(chr);
    if(IsMainCharacter(chr)) SendMessage(&locCamera, "ll", MSG_CAMERA_SPECIALMODE, true);
}

//------------------------------------------------------------------------------------------
//Owner
//------------------------------------------------------------------------------------------

//Установить персонажу тип хозяина дома/комнаты
void LAi_SetOwnerType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_owner_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//Установить персонажу тип хозятна комнаты без перемещения в группу
void LAi_SetOwnerTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_owner_Init(chr);
}

//------------------------------------------------------------------------------------------
//Carrier
//------------------------------------------------------------------------------------------

//Установить персонажу тип хозяина дома/комнаты
void LAi_SetCarrierType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_carrier_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//Установить персонажу тип хозятна комнаты без перемещения в группу
void LAi_SetCarrierTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_carrier_Init(chr);
}

//------------------------------------------------------------------------------------------
//LSCout
//------------------------------------------------------------------------------------------

//Установить персонажу тип гражданина ГПК
void LAi_SetLSCoutType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_LSCout_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//Установить персонажу тип гражданина ГПК без перемещения в группу
void LAi_SetLSCoutTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_LSCout_Init(chr);
}

//------------------------------------------------------------------------------------------
//GroundSit
//------------------------------------------------------------------------------------------

//Установить персонажу тип сидящего на земле
void LAi_SetGroundSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_GroundSit_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//Установить персонажу тип сидящего на земле без перемещения в группу
void LAi_SetGroundSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_GroundSit_Init(chr);
}

//------------------------------------------------------------------------------------------
//Monkey
//------------------------------------------------------------------------------------------

//Установить персонажу тип обезьяны-монстра
void LAi_SetMonkeyType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_monkey_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_MONSTERS);
}

//Установить персонажу тип обезьяны-монстра, без перемещения в группу
void LAi_SetMonkeyTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_monkey_Init(chr);
}

//------------------------------------------------------------------------------------------
//Lay 
//------------------------------------------------------------------------------------------

//Установить персонажу тип лежачего
void LAi_SetLayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_lay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип лежачего, без перемещения в группу
void LAi_SetLayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_lay_Init(chr);
}

//------------------------------------------------------------------------------------------
// Stunned 
//------------------------------------------------------------------------------------------

//Установить персонажу тип оглушенного
void LAi_SetStunnedType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Stunned_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//Установить персонажу тип оглушенного, без перемещения в группу
void LAi_SetStunnedTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Stunned_Init(chr);
}

//Установить персонажу тип стоящего рыбака
void LAi_SetFisherStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_fisher_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип стоящего рыбака, без перемещения в группу
void LAi_SetFisherStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_fisher_Init(chr);
}

//Установить персонажу тип сидящего рыбака
void LAi_SetFisherSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.fishersit = true;
	LAi_type_fisher_Init(chr);
	//Установим сидячую анимацию персонажу
	LAi_SetFisherSitAnimation(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип сидящего рыбака, без перемещения в группу
void LAi_SetFisherSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.fishersit = true;
	LAi_type_fisher_Init(chr);
	//Установим сидячую анимацию персонажу
	LAi_SetFisherSitAnimation(chr);
}

//Установить персонажу тип сидящего на лавочке
void LAi_SetBenchSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_BenchSit_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
	//Установим сидячую анимацию персонажу
	//LAi_SetBenchSitAnimation(chr);
}

//Установить персонажу тип сидящего на лавочке, без перемещения в группу
void LAi_SetBenchSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_BenchSit_Init(chr);
	//Установим сидячую анимацию персонажу
	//LAi_SetBenchSitAnimation(chr);
}

//Установить персонажу тип кузнеца
void LAi_SetBlacksmithType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Blacksmith_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип кузнеца, без перемещения в группу
void LAi_SetBlacksmithTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Blacksmith_Init(chr);
}

//Установить персонажу тип стоячего скрипача
void LAi_SetViolinistStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.musician = "ViolinistStay";
	LAi_type_Musician_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип стоячего скрипача, без перемещения в группу
void LAi_SetViolinistStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.musician = "ViolinistStay";
	LAi_type_Musician_Init(chr);
}

//Установить персонажу тип стоячего флейтиста
void LAi_SetFlutistStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.musician = "FlutistStay";
	LAi_type_Musician_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип стоячего флейтиста, без перемещения в группу
void LAi_SetFlutistStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.musician = "FlutistStay";
	LAi_type_Musician_Init(chr);
}

//Установить персонажу тип сидящего флейтиста
void LAi_SetFlutistSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.musician = "FlutistSit";
	LAi_type_Musician_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип сидящего флейтиста, без перемещения в группу
void LAi_SetFlutistSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.musician = "FlutistSit";
	LAi_type_Musician_Init(chr);
}

//Установить персонажу тип стоячей проститутки
void LAi_SetHorseStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.horse = "HorseStay";
	LAi_type_Horse_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип стоячей проститутки, без перемещения в группу
void LAi_SetHorseStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.horse = "HorseStay";
	LAi_type_Horse_Init(chr);
}

//Установить персонажу тип сидящей проститутки
void LAi_SetHorseSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.horse = "HorseSit";
	LAi_type_Horse_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип сидящей проститутки, без перемещения в группу
void LAi_SetHorseSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.horse = "HorseSit";
	LAi_type_Horse_Init(chr);
}

//Установить персонажу тип сидящего пьяницы
void LAi_SetDrinkerSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.drinkersit = true;
	LAi_type_drinker_Init(chr);
	//Установим сидячую анимацию персонажу
	LAi_SetDrinkerSitAnimation(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип сидящего пьяницы, без перемещения в группу
void LAi_SetDrinkerSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.drinkersit = true;
	LAi_type_drinker_Init(chr);
	//Установим сидячую анимацию персонажу
	LAi_SetDrinkerSitAnimation(chr);
}

//Установить персонажу тип пьяницы
void LAi_SetDrinkerStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_drinker_Init(chr);
	//Установим сидячую анимацию персонажу
	//LAi_SetDrinkerSitAnimation(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип пьяницы, без перемещения в группу
void LAi_SetDrinkerStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_drinker_Init(chr);
	//Установим сидячую анимацию персонажу
	//LAi_SetDrinkerSitAnimation(chr);
}

//Установить персонажу тип пьяницы на лавке
void LAi_SetDrinkerSitBenchType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.drinkersitbench = true;
	LAi_type_drinker_Init(chr);
	//Установим сидячую анимацию персонажу
	//LAi_SetDrinkerSitAnimation(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_CITIZEN);
}

//Установить персонажу тип пьяницы на лавке, без перемещения в группу
void LAi_SetDrinkerSitBenchTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.drinkersitbench = true;
	LAi_type_drinker_Init(chr);
	//Установим сидячую анимацию персонажу
	//LAi_SetDrinkerSitAnimation(chr);
}
