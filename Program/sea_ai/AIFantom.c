
#define INVALID_SHIP_TYPE			-1

int seaFantomsNum; // mitrokosta перенес из глобалов
int seaFantoms[MAX_SHIPS_ON_SEA];

ref CreateSeaFantom() {
	int index = FindFirstEmptyCharacter();
	seaFantoms[seaFantomsNum] = index;
	seaFantomsNum++;
	return GetCharacter(index);
}

void ClearSeaFantoms() {
	for (int i = 0; i < seaFantomsNum; i++) {
		int index = seaFantoms[i];
		InitCharacter(GetCharacter(index), index);
		FreeCharacter(index);
	}

	seaFantomsNum = 0;
}

int Fantom_SetEncounterShips(ref rEnc, string sGroupName)
{
	int iShipSum = 0;

	aref arShipTypes, arShipModes;
	makearef(arShipTypes, rEnc.ShipTypes);
	makearef(arShipModes, rEnc.ShipModes);

	int iShipType, i, q = GetAttributesNum(arShipTypes);
	string sFantomType;

	for (i = 0; i < q; i++)
	{
		ref rFantom = CreateSeaFantom();

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		iShipType   = GetAttributeValue(GetAttributeN(arShipTypes, i));
		sFantomType = GetAttributeValue(GetAttributeN(arShipModes, i));

		rFantom.Ship.Type = GenerateShipExt(iShipType, 0, rFantom);
		rFantom.Ship.Mode = sFantomType;
		rFantom.SeaAI.Group.Name = sGroupName;
		rFantom.Charge.Type = GOOD_BALLS;

		iShipSum++;
	}

    DeleteAttribute(rEnc, "FixedTypes");
	return iShipSum;
}

// ~!~ TO_DO: DEL
int Fantom_GenerateEncounterExt(string sGroupName, int iEType, int iNumWarShips, int iNumMerchantShips, int iNation) 
{
	aref aWar, aMerchant;
	ref  rEnc;
	int  i;
	int  iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Merchant);

	if(iEType == ENCOUNTER_TYPE_BARREL || iEType == ENCOUNTER_TYPE_BOAT)
	{
		ref rFantom = CreateSeaFantom();

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.SeaAI.Group.Name = sGroupName;
		return 0;
	}

    // Далее не используется
	int iRank = sti(PChar.Rank);
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);

	int iShipType;

	for (i=0; i<iNumMerchantShips; i++)
	{
		if(iNumShips + i >= MAX_SHIPS_ON_SEA) return i;
		iShipType = Fantom_GetShipTypeExt(iMerchantClassMin, iMerchantClassMax, "Merchant", sGroupName, "Trade", iEType, iNation);
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	for (i=0; i<iNumWarShips; i++)
	{
		if(iNumShips + iNumMerchantShips + i >= MAX_SHIPS_ON_SEA) return iNumMerchantShips + i; 
		iShipType = Fantom_GetShipTypeExt(iWarClassMin, iWarClassMax, "War", sGroupName, "War", iEType, iNation);
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	return iNumWarShips + iNumMerchantShips;
}

int Fantom_GetShipTypeExt(int iClassMin, int iClassMax, string sShipType, string sGroupName, string sFantomType, int iEncounterType, int iNation)
{
	int iShips[60];
	int i, iShipsNum;
	iShipsNum = 0;
	aref aNation;
	string sAttr;
	bool bOk;

	for (i = SHIP_TARTANE; i <= SHIP_LSHIP_ENG; i++)  //энкаунтеры только до линкора, квестовые корабли отдельно
	{
		object rShip = GetShipByType(i);
		if (!CheckAttribute(rship, "class"))
		{
			trace ("bad ship is: " + rship.name);
		}
		int iClass = MakeInt(rShip.Class);
		
		if (iClass > iClassMin) continue;
		if (iClass < iClassMax) continue;
		if (sti(rShip.CanEncounter) != true) continue;
		if (sti(rShip.Type.(sShipType)) != true) continue;

		bOk = false;
		if(CheckAttribute(rShip, "nation"))
		{
			makearef(aNation, rShip.nation);
			int q = GetAttributesNum(aNation);
			for(int j = 0; j < q; j++)
			{
				sAttr = GetAttributeName(GetAttributeN(aNation, j)); 
				if(GetNationTypeByName(sAttr) == iNation && rShip.nation.(sAttr) == true ) {
                    bOk = true;
                    break;
                }
			}
		}	
		if(!bOk) continue;
		iShips[iShipsNum] = i;
		iShipsNum++;
	}
	if (iShipsNum == 0 ) 
	{
		Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	int iBaseShipType = iShips[rand(iShipsNum - 1)];

	ref rFantom = CreateSeaFantom();

	DeleteAttribute(rFantom, "relation");
	DeleteAttribute(rFantom, "abordage_twice");
	DeleteAttribute(rFantom, "QuestDate");
	DeleteAttribute(rFantom, "ransom");

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Mode = sFantomType;
	rFantom.Charge.Type = GOOD_BALLS;

	int iRealShipType = GenerateShipExt( iBaseShipType, 0, rFantom );

	rFantom.Ship.Type = iRealShipType;

	return iRealShipType;
	
}

// на деле этот метод бесполезен, тк золото в сундуке генерится в др месте, а в к3 тут были распределения опыта и команды вообще - позорище
void Fantom_SetRandomMoney(ref rFantom, string sFantomType)
{
	// clear money from character
	rFantom.Money = 0;

	//GenerateBootyItems(rFantom); // to_do del
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
	
    int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// clear money from character
	rFantom.Money = 0;

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	// add money
// boal 20.01.2004 -->
	switch (sFantomType)
	{
		case "trade":
			rFantom.Money = (10 - iSClass) * 100 + rand((10 - iSClass) * 800);
			return;
		break;
		case "war":
			rFantom.Money = (10 - iSClass) * 40 + rand((10 - iSClass) * 350);
			return;
		break;
		case "pirate":
		    rFantom.Money = (10 - iSClass) * 80 + rand((10 - iSClass) * 500);
			return;
		break;
	}
// boal 20.01.2004 <--
	//Trace("Fantom index = " + rFantom.index + ", group id = " + rFantom.SeaAI.Group.Name + ", have invalid encounter type = " + sFantomType);
}

// boal перенес из ВМЛ
int Fantom_CalcSkill(ref rMainCharacter, string sSkill, int iShipClass, int iSkillMin, int iSkillMax, int iSClass7, int iSClass6, int iSClass5, int iSClass4, int iSClass3, int iSClass2, int iSClass1)
// Stone-D : It was all backwards!
{
	int iSkill = GetSummonSkillFromName(rMainCharacter, sSkill);
    // boal 15.03.04 -->
    int minSkillLevel = 0;
	iSkill = iSkill + iSkillMin + rand(iSkillMax - iSkillMin);
	switch (iShipClass)
	{
		case 1: minSkillLevel =  iSClass1; break;
		case 2: minSkillLevel =  iSClass2; break;
		case 3: minSkillLevel =  iSClass3; break;
		case 4: minSkillLevel =  iSClass4; break;
		case 5: minSkillLevel =  iSClass5; break;
		case 6: minSkillLevel =  iSClass6; break;
		case 7: minSkillLevel =  iSClass7; break;
	}
	minSkillLevel = minSkillLevel*10; // приведение скила к 1-100
	
    if (iSkill < minSkillLevel)	iSkill = minSkillLevel;
    // boal 15.03.04 <--
	if (iSkill < 1)		    	iSkill = 1;
	if (iSkill > SKILL_MAX)     iSkill = SKILL_MAX;
	return iSkill;
}

void Fantom_SetCannons(ref rFantom, string sFantomType)
{
	int iSClass = GetCharacterShipClass(rFantom);
	ref rShip = GetRealShip(GetCharacterShipType(rFantom));

 	int iCannonsType = sti(rShip.Cannon);
	string sCannonType = "cannon";
	int iCaliber = sti(rShip.MaxCaliber);
    // boal 03.02.2004 -->
    switch(iCaliber)
	{
		case 3:
            iCaliber = 0;
		break;				
		case 6:
			iCaliber = 1;
		break;				
		case 8:
			iCaliber = 2;
		break;				
		case 12:
			iCaliber = 3;
		break;				
		case 16:
			iCaliber = 4;
		break;
		case 18:
			iCaliber = 5;
		break;
		case 20:
			iCaliber = 6;
		break;				
		case 24:
			iCaliber = 7;
		break;
		case 32:
			iCaliber = 8;
		break;
		case 36:
			iCaliber = 9;
		break;
		case 42:
			iCaliber = 10;
		break;	
	}
	if (iCaliber > 0)
	{
	   iCaliber = iCaliber - rand(1);
	}
	else
	{
		iCaliber = 0;
	}
	switch(iCaliber)
	{
		case 0:
			iCaliber = 3;
		break;
		case 1:
			iCaliber = 6;
		break;
		case 2:
			iCaliber = 8;
		break;
		case 3:
			iCaliber = 12;
		break;
		case 4:
			iCaliber = 16;
		break;
		case 5:
			iCaliber = 18;
		break;
		case 6:
			iCaliber = 20;
		break;
		case 7:
			iCaliber = 24;
		break;
		case 8:
			iCaliber = 32;
		break;
		case 9:
			iCaliber = 36;
		break;
		case 10:
			iCaliber = 42;
		break;	
	}
	if (iCaliber < 3)
	{
	   iCaliber = 3;
	}
    // boal 03.02.2004 <--
	if (iCaliber > sti(rShip.MaxCaliber)) { iCaliber=sti(rShip.MaxCaliber); }

	switch (sFantomType)
	{
        case "trade":
            // boal 20.01.2004 -->
		    if (rand(1000) < 700)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		break;

		case "war":
			if (rand(1000) < 200)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		    break;

		case "pirate":
			if (rand(1000) < 400)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		    break;
		    // boal 20.01.2004 <--
	}

	if (sti(rShip.Cannon) == CANNON_TYPE_NONECANNON)
	{
		rFantom.Ship.Cannons.Type = CANNON_TYPE_NONECANNON;
		return;
	}
	if (iCaliber == 42)
	{
	    sCannonType = "cannon";
	}
	rFantom.Ship.Cannons.Type = GetCannonByTypeAndCaliber(sCannonType, iCaliber);
}

void Fantom_SetSails(ref rFantom, string sFantomType)
{
	rFantom.Ship.Sails.Gerald = false;
	if (sFantomType == "war") rFantom.Ship.Sails.Gerald = true;
}

void Fantom_SetBalls(ref rFantom, string sFantomType)
{
	float fKBalls = 7 - GetCharacterShipClass(rFantom);

	if (fKBalls <= 0) fKBalls = 0.7; // баркас
	switch (sFantomType)
	{
		case "war":
			fKBalls = fKBalls * 1.7;
		break;
		case "trade":
			fKBalls = fKBalls * 0.8;
		break;
		case "pirate":
			fKBalls = fKBalls * 1.0;
		break;
	}
	if (GetCharacterShipClass(rFantom) == 1) fKBalls = fKBalls * 2.2; 
	if (GetCharacterShipClass(rFantom) == 2) fKBalls = fKBalls * 1.8; 
    // boal 20.01.2004 -->
	Fantom_SetCharacterGoods(rFantom, GOOD_BALLS,    	MakeInt(195 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_BOMBS,    	MakeInt(10  * fKBalls + rand(MakeInt(2  * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_KNIPPELS, 	MakeInt(90  * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_GRAPES,   	MakeInt(70  * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_POWDER,   	MakeInt(350 * fKBalls + rand(MakeInt(30 * fKBalls))), 0);

	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, 	MakeInt(4 	* fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, 		MakeInt(3 	* fKBalls + rand(MakeInt(20 * fKBalls))), 0);

    Fantom_SetCharacterGoods(rFantom, GOOD_FOOD, 		MakeInt(20 	* fKBalls + rand(MakeInt(26 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_WEAPON, 		MakeInt(8  	* fKBalls + rand(MakeInt(13 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_RUM, 		MakeInt(4  	* fKBalls + rand(MakeInt(10 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_MEDICAMENT, 	MakeInt(4  	* fKBalls + rand(MakeInt(13 * fKBalls))), 0);
    // boal 20.01.2004 <--
}

void Fantom_SetGoods(ref rFantom, string sFantomType)
{
	int 	iShipClass = 7 - GetCharacterShipClass(rFantom);  // для баркаса = 0
	int 	i, iGoods, iRandGoods, iGoodName, iGoodQuantity;

	int 	iMultiply 		= 10;
	int 	iRandMultiply 	= 1;

	int 	iStart 	= GOOD_BALLS;
	int 	iFinish = GOOD_POWDER - iStart - 1;

	bool 	isLock; 
	bool 	bOk = false;

	float 	fModifikator = 0.0;

	int 	Nation = sti(rFantom.nation);

	if(CheckAttribute(rFantom, "situation")) bOk = true;

	switch (sFantomType)
	{
		case "war":
			iStart 	= GOOD_BALLS;
            iFinish = GOOD_BRICK - iStart - 1;
            iMultiply = (rand(5)+5) * (rand(iShipClass) + 1);
			iRandMultiply = 1 + rand(iShipClass);		
			iRandGoods = rand(5)+3; 
			for (i = 0; i < iRandGoods; i++)
			{
				if(rand(4) == 1) isLock = 1; 
				else			 isLock = 0; 	
				isLock = isLock || bOk; 
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * rand(iRandMultiply * 3), isLock);
			}

			iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
			if (iMultiply != -1)
			{
				iRandMultiply = rand(6) - 2;  // 0..4 пушки
				if (iRandMultiply > 0)
				{
					Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);	
				}
			}			
		break;

		case "trade":
			iRandMultiply = 2 + rand(iShipClass);

			if (CheckAttribute(rFantom, "RealEncounterType"))
			{
				switch (sti(rFantom.RealEncounterType))
				{
					case ENCOUNTER_TYPE_MERCHANT_SMALL:
						iGoods = rand(2) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_FOOD;
						iFinish = GOOD_LEATHER - iStart - 1;						
					break;

					case ENCOUNTER_TYPE_MERCHANT_MEDIUM:
						iGoods = rand(4) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_FOOD;
						iFinish = GOOD_POWDER - iStart - 1;					
					break;

					case ENCOUNTER_TYPE_MERCHANT_LARGE:
						iGoods = rand(6) + 4; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_COFFEE;
						iFinish = GOOD_SHIPSILK - iStart - 1;					
					break;

					case ENCOUNTER_TYPE_MERCHANT_CROWN:
						iGoods = rand(3) + 3; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_POWDER;
						iFinish = GOOD_SLAVES - iStart - 1;
					break;

					case ENCOUNTER_TYPE_MERCHANT_EXPEDITION:
						iGoods = rand(2) + 2; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_SHIPSILK;
						iFinish = GOOD_CANNON_3 - iStart - 1;
					break;

                    case ENCOUNTER_TYPE_MERCHANT_SLAVES:
                        // TO_DO
                    break;
				}

				for (i = 0; i < iGoods; i++)
				{
					iGoodName = iStart + rand(iFinish);
					iGoodQuantity = makeint(20 + fModifikator * iMultiply * (2 + rand(iRandMultiply * 3)));

					// уникальные и коронные товары
					if(iGoodName >= GOOD_SHIPSILK && iGoodName <= GOOD_SILVER)
					{
						iGoodQuantity = makeint(rand(25) + rand(15) +  1.5 * (10 - MOD_SKILL_ENEMY_RATE) + 15 * (8 - iShipClass) );
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; 
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);			
					}
					else
					{
						if(rand(4) == 1) isLock = 1; 
						else			 isLock = 0; 	
						isLock = isLock || bOk; 
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}	
				}
			}
		break;

		case "pirate": 
			fModifikator = 1.2;
			iMultiply = (rand(10)+3) * (rand(iShipClass) + 1);
			iRandMultiply = 2 + rand(iShipClass);
			iRandGoods = rand(3) + 1;

			if (CheckAttribute(rFantom, "RealEncounterType"))
			{
				switch (sti(rFantom.RealEncounterType))
				{
					case ENCOUNTER_TYPE_PIRATE:
						iRandGoods = rand(3) + 1;
						iStart 	= GOOD_BALLS;
						iFinish = GOOD_COFFEE - iStart - 1;
					break;
					
					case ENCOUNTER_TYPE_SMUGGLERS:
						// TO_DO
					break;
				}
			}

			for (i = 0; i < iRandGoods; i++)
			{
				iGoodName = iStart + rand(iFinish);
				iGoodQuantity = makeint(20 + fModifikator * iMultiply * (1+rand(iRandMultiply * 3)));

				if(rand(4) == 1) isLock = 1; 
				else			 isLock = 0; 	
				isLock = isLock || bOk; 
				Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
			}			

			iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
			if (iMultiply != -1)
			{
				iRandMultiply = rand(6) - 2;  // 0..4 пушки
				if (iRandMultiply > 0)
				{
					Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);	
				}
			}			
		break;
	}

	RecalculateCargoLoad(rFantom);
}

// доработал метод, теперь возвращает сколько взял
int Fantom_SetCharacterGoods(ref rFantom, int iGoods, int iQuantity, bool isLock)
{
	if(iQuantity == 0) return 0;
	if(iGoods > GOODS_QUANTITY - 1 || iGoods < 0) //fix
	{ 
		trace("rChar " + rFantom.id +"     goods :" + iGoods + " out of order" );
        return 0; 
	}

	string sGood = Goods[iGoods].name;
	int iFreeQuantity = GetGoodQuantityByWeight(iGoods, GetCargoFreeSpace(rFantom));
	if (iFreeQuantity < 0) iFreeQuantity = 0;

	if (iQuantity > iFreeQuantity) iQuantity = iFreeQuantity;
	
	if (CheckAttribute(rFantom,"Ship.Cargo.Goods." + sGood))
	{
		rFantom.Ship.Cargo.Goods.(sGood) = sti(rFantom.Ship.Cargo.Goods.(sGood)) + iQuantity;
	}
    else
	{	
		rFantom.Ship.Cargo.Goods.(sGood) = iQuantity;
	}
	
	if(isLock) rFantom.Ship.Cargo.Goods.(sGood).Lock = true;
	RecalculateCargoLoad(rFantom);
	return iQuantity;
}

// опыт матросов
void Fantom_SetRandomCrewExp(ref rFantom, string sFantomType)
{
    if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	switch (sFantomType)
	{
		case "trade":
			rFantom.Ship.Crew.Exp.Sailors   = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Cannoners = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Soldiers  = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
		break;
		case "war":
			rFantom.Ship.Crew.Exp.Sailors   = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Cannoners = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Soldiers  = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
		break;
		case "pirate":
		    rFantom.Ship.Crew.Exp.Sailors   = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Cannoners = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Soldiers  = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
		break;
	}
}

void Fantom_SetQuestSitiation(ref rFantom, string sFantomType)
{
	string sSituation;
	bool CanGenerateSituation = false;
	if (!CheckAttribute(rFantom, "ship.type")) return; 
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; 
	
	switch (sFantomType)
	{
		case "pirate": // пираты или ДУ
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "hunter": // ОЗГ
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "war": // военные корабли
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "trade": // торговцы
			if(rand(120) < 3) 
			{
				sSituation = "Epidemy";
				CanGenerateSituation = true;
			}	
		break;		
	}
	if(CanGenerateSituation)
	{
		rFantom.situation = sSituation;
		rFantom.situation.type = sFantomType;
		rFantom.DontRansackCaptain = true; // Врагу не сдаётся наш гордый Варяг !!
	}
}

void Fantom_SetDamage(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	switch (sFantomType)
	{
		case "pirate":
			if(rand(100) < 5)
			{
				GenerateShipDamageParameters(rFantom);
			}	
		break;
		case "hunter":
			if(rand(100) < 5)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
		case "trade" :
			if(rand(100) < 10)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
		case "war"	 :
			if(rand(100) < 3)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
	}
}

void GenerateShipDamageParameters(ref rFantom)
{
	int i = rand(100);
	int j = rand(2);
	
	if(i < 33) 
	{
		if( j == 0 ) Fantom_SetDamageHull(rFantom);
		if( j == 1 ) Fantom_SetDamageCrew(rFantom);
		if( j == 2 ) Fantom_SetDamageCannons(rFantom);
		return;
	}	
	if((i >= 33) && (i < 66))
	{
		if( j == 0 )
		{
			Fantom_SetDamageHull(rFantom);
			Fantom_SetDamageCrew(rFantom);
		}
		if( j == 1 )
		{
			Fantom_SetDamageHull(rFantom);
			Fantom_SetDamageCannons(rFantom);
		}
		if( j == 2 )
		{
			Fantom_SetDamageCrew(rFantom);
			Fantom_SetDamageCannons(rFantom);
		}
		return;
	}
	if((i >= 66))
	{
		Fantom_SetDamageHull(rFantom);
		Fantom_SetDamageCrew(rFantom);
		Fantom_SetDamageCannons(rFantom);
		return;	
	}
}

void Fantom_SetDamageHull(ref rFantom)
{
	int nMaxDamageProcent = rand(20) + 20;
	int nHP = GetCurrentShipHP( rFantom );
	nHP -= nHP * nMaxDamageProcent / 100;
	rFantom.ship.hp = nHP; 
}

void Fantom_SetDamageCrew(ref rFantom)
{
	int nMaxDamageProcent = rand(10) + 15;
	int nCrew = GetCrewQuantity( rFantom );
	nCrew -= nCrew * nMaxDamageProcent / 100;
	SetCrewQuantity(rFantom, nCrew);
}

void Fantom_SetDamageCannons(ref rFantom)
{
	aref 	refShip;
	string 	sAttr, sBort;
	int 	i;
	
	makearef(refShip, rFantom.Ship);
	ref rRealShip = GetRealShip(GetCharacterShipType(rFantom));
	
	int iCannonDiff = 0;	
	int rCannonQty = GetBortIntactCannonsNum(rFantom, "cannonr", sti(rRealShip.rcannon));
	int lCannonQty = GetBortIntactCannonsNum(rFantom, "cannonl", sti(rRealShip.lcannon));

	if(rCannonQty > 4)
	{
		iCannonDiff = rand(1) + 1;
		sBort		= "cannonr";
		if(iCannonDiff > 0)
		{
			for (i = 0; i < iCannonDiff; i++)
			{
				sAttr = "c" + i;	
				if (CheckAttribute(rFantom, "Ship.Cannons.Borts." + sBort + ".damages"))
				{
					rFantom.Ship.Cannons.Borts.(sBort).damages.(sAttr) 		= 1.0; 			
				}	
			}
		}	
	}
	if(lCannonQty > 4)
	{
		iCannonDiff = rand(1) + 1;		
		sBort		= "cannonl";
		if(iCannonDiff > 0)
		{
			for (i = 0; i < iCannonDiff; i++)
			{
				sAttr = "c" + i;
				if (CheckAttribute(rFantom, "Ship.Cannons.Borts." + sBort + ".damages"))
				{	
					rFantom.Ship.Cannons.Borts.(sBort).damages.(sAttr) 		= 1.0; 
				}	
			}
		}	
	}			
}

// ugeen 03.06.09 - вероятность корабликов быть проапгрейженными на 1, 2 ...  все параметры
void Fantom_SetUpgrade(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// ship class
	int iSClass = GetCharacterShipClass(rFantom);
	int i = rand(100);
	
	switch (sFantomType)
	{
		case "pirate":   // апгрейдим параметр(ы)  шипа пиратских случаек
			if(i < (6 - iSClass)*4)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
		case "hunter":   // апгрейдим параметр(ы) шипа ДУ или ОЗГов
			if(i < ((6 - iSClass)*4 +10)) 
			{
				GenerateShipUpgradeParameters(rFantom);
			}			
		break;
		case "war":   // апгрейдим параметр(ы)  военных кораблей
			if(i < (6 - iSClass)*4)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
		case "trade":   // апгрейдим параметр(ы)  торгашей
			if(i < (6 - iSClass)*4 +10)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
	}
}

int GetPossibilityCannonsUpgrade(ref rFantom, bool isUpgrade)
{
	ref 	shTo;
	
	shTo = &RealShips[sti(rFantom.Ship.Type)];

	int  cannonQ       = sti(shTo.CannonsQuantity);		
	int	 cannonMaxQ;	
	int	 cannonMinQ    = sti(shTo.CannonsQuantityMin); 
	
	if(CheckAttribute(shTo,"CannonsQuantityMax")) 	cannonMaxQ = sti(shTo.CannonsQuantityMax); 
	else
	{		
		cannonMaxQ = sti(shTo.CannonsQuantity); 
		shTo.CannonsQuantityMax = sti(shTo.CannonsQuantity);
	}	
	
	//trace("cannonQ :" + cannonQ + " cannonMaxQ :" + cannonMaxQ + " cannonMinQ :" + cannonMinQ);
	
	if(isUpgrade) 
	{
		if( (cannonMaxQ - cannonQ) == 0) return 0;		// максимум орудий - апгрейд невозможен
	}	
	else	
	{
		if( (cannonQ - cannonMinQ) == 0) return 0;		// минимум орудий - даунгрейд невозможен
	}		
	return 1;
}

void GenerateShipUpgradeParameters(ref rFantom)
{
	int iNation = sti(rFantom.nation);
	
	switch (iNation)
	{
		case ENGLAND: // SW: SpeedRate&fWindAgainstSpeed
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "SpeedRate");
			}	
			else
			{
				UpgradeShipParameter(rFantom, "WindAgainstSpeed");
			}
		break;
		
		case FRANCE: // TM: TurnRate&MinCrew
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "TurnRate");
			}
			else
			{
				UpgradeShipParameter(rFantom, "MinCrew");
			}
		break;
		
		case SPAIN: // CC: Cannons&Capacity
			if(rand(1) == 0) 
			{
				if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
				{
					UpgradeShipParameter(rFantom, "Cannons");
				}	
			}
			else
			{
				if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
				{
					UpgradeShipParameter(rFantom, "Capacity");
				}	
			}
		break;
		
		case HOLLAND: // HP&MMaxCrew
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "HP");
			}
			else
			{
				UpgradeShipParameter(rFantom, "MaxCrew");
			}
		break;
		
		case PIRATE:
			switch(rand(3))
			{
				case 0: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "SpeedRate");
					}	
					else
					{
						UpgradeShipParameter(rFantom, "WindAgainstSpeed");
					}				
				break;
				case 1: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "TurnRate");
					}
					else
					{
						UpgradeShipParameter(rFantom, "MinCrew");
					}					
				break;
				case 2: 
					if(rand(1) == 0) 
					{
						if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
						{
							UpgradeShipParameter(rFantom, "Cannons");
						}	
					}
					else
					{
						if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
						{
							UpgradeShipParameter(rFantom, "Capacity");
						}	
					}				
				break;
				case 3: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "HP");
					}
					else
					{
						UpgradeShipParameter(rFantom, "MaxCrew");
					}				
				break;
			}
		break;
	}
}

void DegradeShipParameter(ref _chr, string _param)
{
	ref 	shTo;
	aref 	refShip;
	int		iCannonDiff;
	int		i;
	string  attr; 

	shTo = &RealShips[sti(_chr.Ship.Type)];
	makearef(refShip, _chr.Ship);

	switch(_param)
	{
		case "SpeedRate":
			shTo.SpeedRate = (stf(shTo.SpeedRate) - stf(shTo.SpeedRate)* 0.15);
			shTo.DontTuning.SpeedRate = true;		
		break;

		case "TurnRate":
			shTo.TurnRate = (stf(shTo.TurnRate) - stf(shTo.TurnRate) * 0.15);
			shTo.DontTuning.TurnRate = true;
		break;

		case "HP":
			shTo.HP = sti(shTo.HP) - makeint(sti(shTo.HP) * 0.15);
			shTo.DontTuning.HP = true;
		break;

		case "WindAgainstSpeed":
			shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) - 0.15 * stf(shTo.WindAgainstSpeed), 2);
			shTo.DontTuning.WindAgainst = true;
		break;

		case "Capacity":
			shTo.Capacity = sti(shTo.Capacity) - makeint(sti(shTo.Capacity) * 0.15);
			shTo.DontTuning.Capacity = true;
		break;
		
		case "MaxCrew":
			shTo.MaxCrew = sti(shTo.MaxCrew) - makeint(sti(shTo.MaxCrew) * 0.15);
			shTo.DontTuning.MaxCrew = true;	
		break;

		case "MinCrew":
			shTo.MinCrew = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.15);
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
			shTo.DontTuning.MinCrew = true;	
		break;

		case "Cannons":		
			if(GetPossibilityCannonsUpgrade(_chr, false) > 0 && CheckAttribute(refShip,"CannonDiff"))
			{
				iCannonDiff = sti(refShip.CannonDiff);
				iCannonDiff += 1;
								
				for (i = 0; i < sti(shTo.cannonr); i++)
				{
					attr = "c" + i;					
					if(i >= sti(shTo.cannonr) - iCannonDiff)	
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 2.0; 
					}
				}	
				for (i = 0; i < sti(shTo.cannonl); i++)
				{
					attr = "c" + i;
					if(i >= sti(shTo.cannonl) - iCannonDiff)	
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 2.0; 
					}
				}	
				shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
				shTo.CannonsQuantity = sti(shTo.Cannons);

				refShip.Cannons = sti(shTo.Cannons);
				refShip.CannonDiff = iCannonDiff;

				shTo.DontTuning.Cannon = true;		
			}							
		break;
	}
}

void UpgradeShipParameter(ref _chr, string _param)
{
	ref 	shTo;
	aref 	refShip;
	int 	iCaliber;
	int		iCannonDiff;
	int		i;
	string  attr; 
	
	shTo = &RealShips[sti(_chr.Ship.Type)];
	makearef(refShip, _chr.Ship);
	
	switch(_param)
	{
		case "SpeedRate":		
			if(!CheckAttribute(shTo, "Tuning.SpeedRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}		
				shTo.Tuning.SpeedRate = true;		
			}				
		break;		
		
		case "TurnRate":		
			if(!CheckAttribute(shTo, "Tuning.TurnRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_TurnRate"))
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
				}
				else
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
				}	
				shTo.Tuning.TurnRate = true;
			}				
		break;
		
		case "HP":		
			if(!CheckAttribute(shTo, "Tuning.HP"))
			{
				if(!CheckAttribute(shTo, "Bonus_HP"))
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
				else
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}	
				shTo.Tuning.HP = true;
				shTo.BaseHP = sti(shTo.HP);
				ProcessHullRepair(_chr, 100.0);
			}				
		break;
		
		case "WindAgainstSpeed":
			if(!CheckAttribute(shTo, "Tuning.WindAgainst"))
			{
				shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) +  0.20 * stf(shTo.WindAgainstSpeed), 2);
				shTo.Tuning.WindAgainst = true;
			}				
		break;
		
		case "Capacity":		
			if(!CheckAttribute(shTo, "Tuning.Capacity"))
			{
				if(!CheckAttribute(shTo, "Bonus_Capacity"))
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}					
				shTo.Tuning.Capacity = true;
			}				
		break;
		
		case "MaxCrew":		
			if(!CheckAttribute(shTo, "Tuning.MaxCrew"))
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
				shTo.Tuning.MaxCrew = true;				
			}				
		break;
		
		case "MinCrew":
			if(!CheckAttribute(shTo, "Tuning.MinCrew"))
			{
				shTo.MinCrew        = sti(shTo.MinCrew) * 2;
				shTo.Tuning.MinCrew = true;
			}	
		break;
		
		case "Cannons":					
			if(!CheckAttribute(shTo, "Tuning.Cannon") && GetPossibilityCannonsUpgrade(_chr, true) > 0)
			{
				iCannonDiff = sti(refShip.CannonDiff);
				iCannonDiff -= 1;
								
				for (i = 0; i < sti(shTo.cannonr); i++)
				{
					attr = "c" + i;										
					
					if(i < (sti(shTo.cannonr) - iCannonDiff) )	
					{
						if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
						{
							refShip.Cannons.Borts.cannonr.damages.(attr) = 0.0; 
						}	
					}					
				}	
				for (i = 0; i < sti(shTo.cannonl); i++)
				{
					attr = "c" + i;
					if(i < (sti(shTo.cannonl) - iCannonDiff) )	
					{
						if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
						{
							refShip.Cannons.Borts.cannonl.damages.(attr) = 0.0; 
						}	
					}										
				}	
				
				shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
				shTo.CannonsQuantity = sti(shTo.Cannons);
		
				refShip.Cannons = sti(shTo.Cannons);
				refShip.CannonDiff = iCannonDiff;
			
				shTo.Tuning.Cannon = true;		
			}
			else
			{
				if(!CheckAttribute(shTo, "Tuning.Cannon"))
				{
					shTo.Tuning.Cannon = true;
				}
			}
		break;
	}
}
// ugeen

void UpgradeShipFull(ref _chr)
{
	UpgradeShipParameter(_chr, "SpeedRate");
	UpgradeShipParameter(_chr, "TurnRate");
	UpgradeShipParameter(_chr, "WindAgainstSpeed");
	UpgradeShipParameter(_chr, "Capacity");
	UpgradeShipParameter(_chr, "HP");
	UpgradeShipParameter(_chr, "MaxCrew");
	UpgradeShipParameter(_chr, "MinCrew");
	UpgradeShipParameter(_chr, "Cannons");
	RealShips[sti(_chr.ship.type)].Tuning.All = true;
}

// eddy. подбор типа корабля для фантома от ранга и нац. принадлежности
void SetShipToFantom(ref _chr, string _type, bool _setgoods)
{
	int ShipType;
	int Nation = sti(_chr.nation);
	int Rank = sti(pchar.rank);
	int iClassFlag = FLAG_SHIP_CLASS_6;
	int iTypesFlag = FLAG_SHIP_TYPE_MERCHANT;
	int iNationsFlag = GetNationFlag(Nation);
	switch (_type)
	{
		case "trade":	
			iTypesFlag = FLAG_SHIP_TYPE_MERCHANT;
			if (Rank < 6)
			{
				iClassFlag = FLAG_SHIP_CLASS_6;
			}			
			if (Rank >= 6 && Rank < 12)
			{
				iClassFlag = FLAG_SHIP_CLASS_5;
			}
			if (Rank >= 12 && Rank <= 20)
			{
				iClassFlag = FLAG_SHIP_CLASS_4;
			}
            if (Rank > 21 && Rank <= 29)
            {
                iClassFlag = FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4;
            }
			if (Rank > 30)
			{
				iClassFlag = FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3;
			}
		break;
		case "pirate":
			iTypesFlag = FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT;
			if (Rank < 6)
			{
				iClassFlag = FLAG_SHIP_CLASS_6;
			}			
			if (Rank >= 6 && Rank < 12)
			{
				iClassFlag = FLAG_SHIP_CLASS_5;
			}
			if (Rank >= 12 && Rank <= 20)
			{
				iClassFlag = FLAG_SHIP_CLASS_4;
			}
            if (Rank > 21 && Rank <= 29)
            {
                iClassFlag = FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4;
            }
			if (Rank > 30)
			{
				iClassFlag = FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3;
			}
		break;

		case "war":
			iTypesFlag = FLAG_SHIP_TYPE_WAR;
			if (Rank < 6)
			{
				iClassFlag = FLAG_SHIP_CLASS_6;
			}			
			if (Rank >= 6 && Rank < 12)
			{
				iClassFlag = FLAG_SHIP_CLASS_5;
			}
			if (Rank >= 12 && Rank <= 20)
			{
				iClassFlag = FLAG_SHIP_CLASS_4;
			}
            if (Rank > 21 && Rank <= 29)
            {
                iClassFlag = FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4;
            }
			if (Rank > 30)
			{
				iClassFlag = FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3;
			}
		break;
	}
	
	ShipType = GetRandomShipType(iClassFlag, iTypesFlag, iNationsFlag);
	
	_chr.Ship.Type = GenerateShipExt(ShipType, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, _type);
    Fantom_SetBalls(_chr, _type);

	if(_type == "pirate")
	{
		Fantom_SetUpgrade(_chr, "pirate");
	}
	
    if (_setgoods)
    {
        Fantom_SetGoods(_chr, _type);
    }
}
