/*
 * Eagle.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "Eagle.h"
#include "Guy.h"
#include "aux.h"
#include "Spark.h"

Eagle::Eagle() {
	TurnIT = -1;
	Weapon1.MyPlayer = this;
	Weapon2.MyPlayer = this;
	WheelRotate = 0;
}

Eagle::~Eagle() {
}



void Eagle::TimeTab(){
	int i;
	if (XSpeed < -1) {
		YSpeed = (YSpeed + 2.1 / -(XSpeed - 2) - 0.1) / 1.1;
		XSpeed = XSpeed / 1.05;
	}else{if (XSpeed > 1) {
		YSpeed = (YSpeed + 2.1 / (XSpeed + 2) - 0.1) / 1.1;
		XSpeed = XSpeed / 1.05;
	}else{
		YSpeed = YSpeed + 0.6;
		XSpeed = XSpeed / 1.05;
	}
	;
	;
	OnGround = 0;
	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) > mWater) {
		if (YSpeed > 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 2;
		}
	}
	if (FrmScreen.GetMap((XPos), YPos - 15) > mWater) {
		if (YSpeed < 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 2;
		}
	}

	if (FrmScreen.GetMap(XPos + 6, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 4; ++i){
				if (FrmScreen.GetMap(XPos + 6, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 6, YPos - 2) > mWater) {
		if (XSpeed > 0) {
			for(i = 0; i <= 4; ++i){
				if (FrmScreen.GetMap(XPos - 6, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	;
	if (FrmScreen.GetMap(XPos - 6, YPos - 2) > mWater) {
		if (XSpeed < 0) {
			XPos = XPos - XSpeed;
			XSpeed = -XSpeed;
		}
	}
	if (FrmScreen.GetMap(XPos + 6, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			XPos = XPos - XSpeed;
			XSpeed = -XSpeed;
		}
	}
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;

	for(i = 0; i <= WheelY; ++i){
		if (FrmScreen.GetMap((XPos), YPos + i) > mWater) {
			YSpeed = YSpeed - 0.9 * (WheelY - i);
			break;
		}
	}
	CWheelY = i;
	if (i < WheelY) {
		OnGround = 1;
		XSpeed = XSpeed / 1.1;
	}

	if (OnGround) { WheelCalculate (XSpeed);}

	if (MyNumber < 2) {
		FrmScreen.SetScreenPos ((MyNumber), (XPos), (YPos));
		auto c = FrmScreen.GetControll(MyNumber);
		if (c.Change) {
			if (c.AimDirection == 1) {
				DropGuy();
			}else{
				if (c.AimDirection == -1) {
					Die();
				}
			}
		}
		if (Dying) {
			c.AimDirection = 0;
			c.Change = 0;
			c.Jump = 0;
			c.Fire = 0;
			c.MoveDirection = 0;
		}
		WheelY = 5 + (int)(c.Jump) * 10;
		if (OnGround) {
			XSpeed = XSpeed + (30 - XSpeed * c.MoveDirection) * c.MoveDirection / 20;
		}
		else{
			XSpeed = XSpeed + c.MoveDirection * 0.5;
		}
		if (!OnGround) {
			WheelCalculate( c.MoveDirection * 2);
			if (c.MoveDirection) { FrmScreen.MakeSmoke((XPos), YPos - 3, XSpeed - c.MoveDirection * 3 + Rnd() - 0.5, YSpeed + Rnd() - 0.5);}
			YSpeed = YSpeed + c.AimDirection * 0.5;
		}
		if (c.MoveDirection) {
			TurnIT = c.MoveDirection;
		}
		if (c.Fire) {
			if (c.Reload) {
				Weapon2.Fire ((XPos), YPos + 20, 20, 4, (TurnIT), 1);
			}else{
				Weapon1.Fire ((XPos), YPos + 20, 1, 0, (TurnIT), 1);
			}
		}
	}
	else{
		if (Items[0] < 20 && (int)(Rnd() * 100) == 1) { Die();}
		WheelY = 5;
		i = FrmScreen.isPlayer(XPos, YPos, 30, 30);
		if (i != 0) {
			if (FrmScreen.getPlayer(i - 1)->isGuy()) {
				Guy* guy = (Guy*)FrmScreen.getPlayer(i - 1);
				guy->EW (this);
				UpDateItems();
			}
		}
	}

	CalcItem(1, 50);
	CalcItem(2, 25);

	if (Dying) {
		FrmScreen.MakeSmoke(XPos, YPos, Rnd() * 4 - 2, Rnd() * 4 - 2);
		if (Rnd() * 5 > 4) {
			FrmScreen.Explosion(XPos + Rnd() * 10 - 5, YPos + Rnd() * 10 - 5, 1, 20, 0);
		}
		if (OnGround) {
			Terminate();
		}
	}
}
}

void Eagle::Render(){
	FrmScreen.DrawPlPic(ddWheel, XPos - 6, YPos + CWheelY - 12, (WheelRotate));
	FrmScreen.DrawPlPic(ddEagle, XPos - 15, YPos - 12, 0.5 + TurnIT / 2);
}

void Eagle::Init(double X, double Y, double XSpeed2, double YSpeed2, int Number){
	long i;
	MyNumber = Number;
	XPos = X;
	YPos = Y;
	XSpeed = XSpeed2;
	YSpeed = YSpeed2;
	Width = 22 / 2;
	Height = 12 / 2;
	Items[0] = GamePlay.Armor;
	ItemMax[0] = GamePlay.Armor;
	FrmScreen.SetStatus((MyNumber), 0, 1);
	for(i = 1; i <= 7; ++i){
		Items[i] = 1.5 * GamePlay.Ammo;
		ItemMax[i] = 2 * GamePlay.Ammo;
		if (MyNumber < 2) { FrmScreen.SetStatus((MyNumber), i, 1.5 / 2);}
	}
	UpDateItems();
}

void Eagle::WheelCalculate(float Val){
	WheelRotate = WheelRotate + Val;
	if (WheelRotate > 1000 || WheelRotate < -1000) WheelRotate = 0;
	do{
		if (WheelRotate < 0) {
			WheelRotate = WheelRotate + 7;
		}else{if (WheelRotate > 7) {
			WheelRotate = WheelRotate - 7;
		}else{
			return;
		}
		}
	}while(1);
}

void Eagle::Damage(long Val){
	if (Dying) { return;;}
	Items[0] = Items[0] - Val;
	if (Items[0] < 0) {
		Die();
		Items[0] = 0;
	}
	if (MyNumber < 2) { FrmScreen.SetStatus((MyNumber), 0, (double)Items[0] / (double)ItemMax[0]);}
	if (Items[0] > ItemMax[0]) { Items[0] = ItemMax[0];}
}

void Eagle::Die(){
	Dying = 1;
	FrmScreen.HugeExplosion(XPos, YPos, 60, 0);
	FrmScreen.MakeQuake(50);
}

void Eagle::Terminate(){
	FrmScreen.RemoveObject(this);
	FrmScreen.KilledPlayer(MyNumber);
	long i;
	for(i = 0; i <= 10; ++i){
		auto nSpark = new Spark;
		nSpark->Init((XPos), (YPos), 6 * Rnd() - 3, 6 * Rnd() - 3);
		FrmScreen.AddObject(nSpark);
	}
	FrmScreen.HugeExplosion(XPos, YPos, 90, 50);
	if (MyNumber < 2) { FrmScreen.MakePlayers (MyNumber);}
	PlaySound(dsExplosion);
	FrmScreen.MakeQuake(50);
}

void Eagle::DropGuy(){
	auto guy = new Guy;
	guy->Init(XPos, YPos, XSpeed, YSpeed, MyNumber);
	FrmScreen.AddObject(guy);
	FrmScreen.SetPlayer(MyNumber, guy);
	MyNumber = 2;
}

void Eagle::PickUp(std::string Item){
	//	'Weapons.AddWeapon(Item);
}

void Eagle::UpDateItems(){
	long i;
	for(i = 0; i <= 7; ++i){
		FrmScreen.SetStatus(MyNumber, i, (double)Items[i] / (double)ItemMax[i]);
	}
}
