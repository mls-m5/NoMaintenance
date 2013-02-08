/*
 * Musquash.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Musquash.h"
#include "common.h"
#include "IBomb.h"
#include "Guy.h"
#include <math.h>
#include "SmokeSpark.h"

Musquash::~Musquash() {
}


void Musquash::TimeTab(){
	int i;
	YSpeed = YSpeed + (15 - YSpeed) / 10;
	;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	;
	OnGround = false;
	;
	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) > mWater) {
		if (YSpeed > 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 4;
		}
	}
	if (FrmScreen.GetMap((XPos), YPos - 15) > mWater) {
		if (YSpeed < 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 4;
		}
	}
	;
	if (FrmScreen.GetMap(XPos + 12, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 4; ++i){
				if (FrmScreen.GetMap(XPos + 12, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 12, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 4; ++i){
				if (FrmScreen.GetMap(XPos - 12, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 11, YPos - 2) > mWater && XSpeed < 0) {
		if (XSpeed < 0) {
			for(i = 0; i <= 10; ++i){
				if (FrmScreen.GetMap(XPos - 11 + i, YPos - 2) > mWater) {
					XPos = XPos + i;
					XSpeed = 0;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos + 11, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 10; ++i){
				if (FrmScreen.GetMap(XPos + 11 - i, YPos - 2) > mWater) {
					XPos = XPos - i;
					XSpeed = 0;
				}
			}
		}
	}
	for(i = 0; i <= WheelY; ++i){
		if (FrmScreen.GetMap(XPos - 11, YPos + i) > mWater) {
			YSpeed = YSpeed - 0.9 * (WheelY - i);
			XSpeed = XSpeed + 0.2;
			break;
		}
	}
	CWheelY[0] = i;
	if (i < WheelY) {
		OnGround = true;
		XSpeed = XSpeed / 1.1;
	}
	for(i = 0; i <= WheelY; ++i){
		if (FrmScreen.GetMap(XPos + 11, YPos + i) > mWater) {
			YSpeed = YSpeed - 0.9 * (WheelY - i);
			XSpeed = XSpeed - 0.2;
			break;
		}
	}
	CWheelY[1] = i;
	if (i < WheelY) {
		OnGround = true;
		XSpeed = XSpeed / 1.1;
	}
	if (OnGround) { WheelCalculate (XSpeed);}
	;
	if (MyNumber < 2) {
		auto c = FrmScreen.GetControll(MyNumber);
		if (SpecialLeft > 0) { SpecialLeft = SpecialLeft - 1;}
		WheelY = 5 + c.Jump * 10;
		if (OnGround) { XSpeed = XSpeed + (12 - XSpeed * c.MoveDirection) * c.MoveDirection / 5; }else{ XSpeed = XSpeed + c.MoveDirection * .5;}
		if (! OnGround) { WheelCalculate( c.MoveDirection * 2);}
		if (c.MoveDirection != 0 && c.Reload == 0) {
			TurnIT = c.MoveDirection;
		}
		if (c.Fire != 0) {
			if (c.Reload  != 0) {
				if (Items[3] > 300 && SpecialLeft == 0) {
					PlaySound(dsLaunch);
					NinjaOut = true;
					NinjaMode = inAir;
					NinjaPosX = XPos;
					NinjaPosY = YPos - 10;
					NinjaLength = 1;
					SpecialLeft = 5;
					nXS = XAim * TurnIT / 3;
					nYS = Aim / 3;
					TheEnemy = 0;
				}
			}else{
				Weapons.GetCurrentWeapon()->Fire( (XPos), (YPos) - 7, XAim, Aim, (TurnIT), true);
			}
		}else{
			Weapons.GetCurrentWeapon()->Fire( (XPos), (YPos) - 7, XAim, Aim, (TurnIT), false);
		}
		if (c.Reload != 0 && c.Jump != 0) { NinjaOut = false;}
		if (c.Reload != 0) {
			if (c.AimDirection == -1) {
				if (NinjaLength > .2) { NinjaLength = NinjaLength - 0.1;}
			}else if (c.AimDirection == 1) {
				if (NinjaLength < 10) { NinjaLength = NinjaLength + .1;}
			}
		}
		if (NinjaOut) { DoNinjarope();}
		if (!c.Change){
			CAim = CAim + (double)c.AimDirection / 10;
			if (c.AimDirection != 0) {
				if (CAim > 0.7) { CAim = 0.7;}
				if (CAim < -1.8) { CAim = -1.8;}
				XAim = cos(CAim) * 50;
				Aim = sin(CAim) * 50;
			}
		}
		if (CrossVar == true) { CrossVar = false; }else{ CrossVar = true;}
		FrmScreen.SetScreenPos ((MyNumber), (XPos) + (XAim + 20) * TurnIT, (YPos) + Aim * 2);
		if (c.Change != 0) {
			if (c.AimDirection == -1) {
				Weapons.SetNextWeapon();
			}else if (c.AimDirection == 1) {
				DropGuy();
			}else if (c.Reload != 0) {
				Weapons.SetWeapon( 0);
			}
		}
		FrmScreen.SetStatus((MyNumber), 0, Items[0] , ItemMax[0]);
		if (MyNumber == 1) { Target = 0; }else{ Target = 1;}
	}else{
		if (Items[0] < 20) { Damage (1);}
		if (NinjaOut) { DoNinjarope();}
		WheelY = 5;
		i = FrmScreen.isPlayer(XPos, YPos, 30, 30);
		if (i != 0) {
			if ( FrmScreen.getPlayer(i - 1)->isGuy()) {
				auto guy = (Guy*) FrmScreen.getPlayer(i - 1);
				guy->EW (this);
				UpDateItems();
			}
		}
	}
	;
	if (Items[0] < 40 && Rnd() * 40 > Items[0]) {
		FrmScreen.MakeSmoke(XPos, YPos - 5, Rnd() - 0.5, -1.5d, 0);
	}
	CalcItem(1, 35);
	CalcItem(2, 1);
	CalcItem(3, 25);
}

void Musquash::Init(double X, double Y, double XSpeed2, double YSpeed2, int Number){
	int i;

	MyNumber = Number;
	if (Number == 1){
		Target = 0;
	}
	else{
		Target = 1;
	}
	XAim = 50;
	CAim = 0;
	Aim = 0;
	XPos = X;
	YPos = Y;
	XSpeed = XSpeed2;
	YSpeed = YSpeed2;
	WheelY = 5;
	WheelRotate = 0;
	TurnIT = 1;
	Width = 22 / 2;
	Height = 22 / 2;
	Items[0] = 2 * GamePlay.Armor;
	ItemMax[0] = 2 * GamePlay.Armor;
	NinjaOut = 0;
	FrmScreen.SetStatus((MyNumber), 0, 1);
	for(i = 1; i <= 7; ++i){
		Items[i] = 6 * GamePlay.Ammo;
		ItemMax[i] = 6 * GamePlay.Ammo;
	}
	UpDateItems();
	if (MyNumber == 1) { Target = 0; }else{ Target = 1;}
	Weapons.Init(this);
}

void Musquash::WheelCalculate(double Val){
	WheelRotate = WheelRotate + Val;
	if (WheelRotate < -1000) WheelRotate = 0; //To avoid an infinite loop
	if (WheelRotate > 1000) WheelRotate = 0;
	do{
		if (WheelRotate < 0) {
			WheelRotate = WheelRotate + 7;
		}else if (WheelRotate > 7) {
			WheelRotate = WheelRotate - 7;
		}else{
			return;
		}
	}while(true);
}

Musquash::Musquash() {
	TurnIT = -1;
	Dying = false;
	Weapons.Init(this);
	Weapons.AddWeapon("kanonare");
	Weapons.AddWeapon("Klachnikow");
}

void Musquash::Damage(long Val){
	if (Dying) { return;}
	Items[0] = Items[0] - Val;
	if (Items[0] < 0) {
		Die();
		Items[0] = 0;
	}
	if (Items[0] > ItemMax[0]) { Items[0] = ItemMax[0];}
}

void Musquash::Die(){
	Dying = true;
	long i;
	for(i = 0; i <= 20; ++i){
		auto nSpark = new SmokeSpark();
		nSpark->Init((XPos), (YPos), 6 * Rnd() - 3, 6 * Rnd() - 3, 1);
		FrmScreen.AddObject(nSpark);
	}
	FrmScreen.RemoveObject(this);
	if (MyNumber < 2) { FrmScreen.MakePlayers (MyNumber);}
	FrmScreen.Explosion((XPos - 7), (YPos), 1, 30, 10);
	FrmScreen.Explosion((XPos + 7), (YPos), 1, 30, 10);
	auto nBomb = new IBomb();
	nBomb->Init((XPos), (YPos), 0);
	FrmScreen.AddObject(nBomb);
	PlaySound(dsExplosion);
	FrmScreen.MakeQuake(20);
	FrmScreen.KilledPlayer( MyNumber);
}

void Musquash::DropGuy(){
	auto guy = new Guy();
	guy->Init(XPos, YPos, XSpeed, YSpeed, MyNumber);
	FrmScreen.AddObject(guy);
	FrmScreen.SetPlayer(MyNumber, guy);
	MyNumber = 2;
}

void Musquash::PickUp(std::string Item){
	Weapons.AddWeapon(Item);
}


void Musquash::DoNinjarope(){
	long Total; double ToX; double ToY; int i;
	ToX = NinjaPosX - XPos;
	ToY = NinjaPosY - YPos - 5;
	Total = (long) sqrt(ToX * ToX + ToY * ToY);
	;
	switch (NinjaMode){
	case inAir:
		nXS = nXS - ToX / 400 / NinjaLength;
		nYS = nYS - ToY / 400 / NinjaLength + 0.3;
		if (NinjaPic != 0) {
			NinjaPic = 0;
		}
		else{
			NinjaPic = 1;
		}
		break;
	case inDirt:
		nXS = 0;
		nYS = 0;
		XSpeed = XSpeed + ToX / 10000 * Total / NinjaLength;
		YSpeed = YSpeed + ToY / 10000 * Total / NinjaLength;
		if (ToX > 200) { FrmScreen.DrawCircleToMap(NinjaPosY, NinjaPosY, 5, mAir);}
		if (ToY > 200) { FrmScreen.DrawCircleToMap(NinjaPosX, NinjaPosX, 5, mAir);}
		break;
	case inRock:
		nXS = 0;
		nYS = 0;
		XSpeed = XSpeed + ToX / 10000 * Total / NinjaLength;
		YSpeed = YSpeed + ToY / 10000 * Total / NinjaLength;
		break;
	case inEnemy:
		nXS = 0;
		nYS = 0;
		;
		TheEnemy->Force(- ToX / 15000 * Total / NinjaLength,- ToY / 15000 * Total / NinjaLength);
		XSpeed = XSpeed + ToX / 10000 * Total / NinjaLength;
		YSpeed = YSpeed + ToY / 10000 * Total / NinjaLength;
		NinjaPosX = TheEnemy->getXPos();
		NinjaPosY = TheEnemy->getYPos();
		break;
	}
	;
	if (MyNumber < 2) {
		if (NinjaMode != inEnemy) {
			if (FrmScreen.isThisPlayer(Target, NinjaPosX, NinjaPosY)) { NinjaMode = inEnemy;}
			if (NinjaMode == inEnemy) { TheEnemy = FrmScreen.getPlayer(Target);}
		}
	}else{
		if (NinjaMode != inEnemy) {
			for(i = 0; i <= 1; ++i){
				if (FrmScreen.isThisPlayer(i, NinjaPosX, NinjaPosY)) { NinjaMode = inEnemy;}
				if (NinjaMode == inEnemy) {  TheEnemy = FrmScreen.getPlayer(i);}
			}
		}
	}
	if (NinjaMode != inEnemy) {
		switch (FrmScreen.GetMapLine(NinjaPosX, NinjaPosY, nXS, nYS)){
		case mDirt: NinjaMode = inDirt;
		break;
		case mRock: NinjaMode = inRock;
		break;
		default: NinjaMode = inAir;
		break;
		}
	}


	NinjaPosX = NinjaPosX + nXS;
	NinjaPosY = NinjaPosY + nYS;

}


void Musquash::Render(){
	FrmScreen.DrawOnePlPic (ddCrossHair, XPos + XAim * TurnIT - 7.5, YPos + Aim - 7.5, 3);

	FrmScreen.DrawPlLine (XPos, YPos - 7, XPos + XAim / 4 * TurnIT, YPos + Aim / 4 - 7, 6, Color(.5,.5,.5));

	FrmScreen.DrawPlPic(ddWheel, XPos - 13, YPos + CWheelY[0] - 12, (long) (WheelRotate));
	FrmScreen.DrawPlPic(ddWheel, XPos + 1, YPos + CWheelY[1] - 12, (long) (WheelRotate));


	if (NinjaOut){
		double ToX; double ToY;
		ToX = NinjaPosX - XPos;
		ToY = NinjaPosY - YPos - 5;
		double Total = sqrt(ToX * ToX + ToY * ToY);
		double OffX = 0; double OffY = 0;
		if (Total != 0) { OffX = ToX / Total;}
		if (Total != 0) { OffY = ToY / Total;}
		for(int i = 1; i <= Total / 10 - 1; ++i){
			FrmScreen.DrawPlPic(ddNinjaRope, NinjaPosX - i * OffX * 10 - 6, NinjaPosY - i * OffY * 10 - 6, 0);
		}
		;
		;
		if (NinjaPic != 0) {
			FrmScreen.DrawPlPic(ddNinjaRope, NinjaPosX - 6, NinjaPosY - 6, 2 );
		}
		else{
			FrmScreen.DrawPlPic(ddNinjaRope, NinjaPosX - 6, NinjaPosY - 6, 1);
		}
	}
	if (Aim > -27) {
		FrmScreen.DrawPlPic(ddChassi, XPos - 14, YPos - 22, 1 + TurnIT);
	}
	else{
		FrmScreen.DrawPlPic(ddChassi, XPos - 14, YPos - 22, 2 + TurnIT);
	}

	if (MyNumber == 0 || MyNumber == 2){
		if (FrmScreen.GetControll(MyNumber).Change){
			frmScreen.DrawText(XPos, YPos - 20, Weapons.GetCurrentWeapon()->name);
		}
	}
}
