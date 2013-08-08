/*
 * Guy.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Guy.h"
#include "common.h"
#include <math.h>
#include "WeaponCollection.h"
#include "Blood.h"

Guy::Guy() {
	TurnIT = -1;
	Weapons.Init(this);
	Weapons.AddWeapon("Klachnikow");
	Weapons.AddWeapon("blaster");

}

Guy::~Guy() {
	// TODO Auto-generated destructor stub
}

void Guy::TimeTab(){
	long i;
	YSpeed = YSpeed + (10 - YSpeed) / 10;
	;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	;
	OnGround = 0;
	;
	if (FrmScreen.GetMapLine((XPos), YPos + 5, XSpeed, YSpeed) > mWater) {
		if (YSpeed > 0) {
			YSpeed = 0;
			for (int i = -10; i <= 3; ++i){
				if (FrmScreen.GetMap(XPos, YPos + 5 + i) > mWater) {
					YPos = YPos + i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap((XPos), YPos + 6) > mWater) {
		OnGround = 1;
	}
	if (FrmScreen.GetMap((XPos), YPos - 15) > mWater) {
		if (YSpeed < 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed;
		}
	}
	;
	if (FrmScreen.GetMap(XPos + 3, YPos) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 5; ++i){
				if (FrmScreen.GetMap(XPos + 3, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 3, YPos) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 5; ++i){
				if (FrmScreen.GetMap(XPos + 3, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 2, YPos - 2) > mWater && XSpeed < 0) {
		if (XSpeed < 0) {
			XPos = XPos - XSpeed;
			XSpeed = -XSpeed;
		}
	}
	if (FrmScreen.GetMap(XPos + 2, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			XPos = XPos - XSpeed;
			XSpeed = -XSpeed;
		}
	}
	if (MyNumber < 2) {
		FrmScreen.SetScreenPos( (MyNumber), (XPos), (YPos));
		auto c = FrmScreen.GetControll((MyNumber));
		WheelY = 5 + int(c.Jump) * 10;
		if (OnGround) {
			XSpeed = 3 * c.MoveDirection;
		}else{
			XSpeed = XSpeed + c.MoveDirection * 0.5;
		}
		if (! OnGround) {
			GuyStep = 2;
			XSpeed = XSpeed / 1.1;
		}
		else if (XSpeed) {
			if (GuyStep < 0) { GuyStep = 4;}
			GuyStep = GuyStep - 1;
		}
		if (c.MoveDirection) { TurnIT = c.MoveDirection;}
		Weapons.GetCurrentWeapon()->Fire( (XPos), (YPos), XAim, Aim, (TurnIT), c.Fire);
		Aim = Aim + c.AimDirection * 4;
		if (c.AimDirection) {
			if (Aim > 30) { Aim = 30;}
			if (Aim < -50) { Aim = -50;}
			XAim = pow((2500 - Aim * Aim) , 0.5);
		}
		CrossVar = ! CrossVar;
		if (c.Change) {
			if (c.AimDirection == -1) {
				Weapons.SetNextWeapon();
			}else{if (c.AimDirection == 1) { Weapons.SetNextWeapon();}
			}
		}
		if (c.Jump && OnGround) { YSpeed = -10;}
		;
		frmScreen.SetStatus((MyNumber), 0, Items[0] , ItemMax[0]);
	}
	else{
		WheelY = 5;
	}
	;
	;
	;
	CalcItem(1, 20);


}

void Guy::Render(){

	FrmScreen.DrawOnePlPic (MyNumber, ddCrossHair, XPos + XAim * TurnIT - 7.5, YPos + Aim - 7.5, 2);
	FrmScreen.DrawPlPic(ddGuy, XPos - 5, YPos - 7.5, 4.5 + TurnIT * (GuyStep + 1.5) + 10 * PictureNumber);


	if (MyNumber == 0 || MyNumber == 1){
		if (FrmScreen.GetControll(MyNumber).Change){
			frmScreen.DrawText(XPos, YPos - 20, Weapons.GetCurrentWeapon()->name);
		}
	}
}

void Guy::Init(double X, double Y,  double XSpeed2,  double YSpeed2, int Number){
	long i;
	MyNumber = Number;
	PictureNumber = GamePlay.SoldierType[MyNumber];
	XPos = X;
	YPos = Y;
	XSpeed = XSpeed2;
	YSpeed = YSpeed2;
	Dying = false;
	Width = 10 / 2;
	Height = 22 / 2;
	Items[0] = 0.4 * GamePlay.Armor + 1;
	ItemMax[0] = 0.4 * GamePlay.Armor + 1;
	FrmScreen.SetStatus((MyNumber), 0, 1);
	FrmScreen.SetPlayer(MyNumber, this);
	for(i = 1; i <= 7; ++i){
		Items[i] = 2 * GamePlay.Ammo;
		ItemMax[i] = 4 * GamePlay.Ammo;
	}
	XAim = 50;
	UpDateItems();
}

void Guy::Damage(long Val){
	if (Dying) { return;;}
	long i;
	for(i = 0; i <= 9  * GamePlay.Blood / 100; ++i){
		FrmScreen.MakeSmoke(XPos, YPos, Rnd() * 8 - 4, Rnd() * 8 - 4, 2);
	}
	Items[0] = Items[0] - Val;
	if (Items[0] < 0) {
		Die();
		Items[0] = 0;
	}
	else{
		PlaySound(dsOusch);
	}
	if (Items[0] > ItemMax[0]) { Items[0] = ItemMax[0];}
}

void Guy::Die(){
	Dying = 1;
	long i;
	for(i = 0; i <= 2  * GamePlay.Blood / 10 ; ++i){
		FrmScreen.MakeSmoke(XPos, YPos, Rnd() * 4 - 2, Rnd() * 4 - 2, 2);
	}
	;
	auto nBlood = new Blood();
	nBlood->Init((XPos), (YPos), 40 + 4 * GamePlay.Blood / 10);
	FrmScreen.AddObject(nBlood);

	FrmScreen.RemoveObject(this);
	FrmScreen.MakePlayers (MyNumber);
	PlaySound(dsDie);
	FrmScreen.KilledPlayer(MyNumber);
}

long  Guy::getItem(long Index){
	return Items[Index];
}

void Guy::setItem(int Index, long Val){
	Items[Index] = Val;
	if (Items[Index] < 0) { Items[Index] = 0;}
	if (Items[Index] > ItemMax[Index]) { Items[Index] = ItemMax[Index];}
	if (MyNumber < 2) {
		FrmScreen.SetStatus((MyNumber), Index, Items[Index] / ItemMax[Index]);
	}
}

void Guy::CalcItem(int Index, double Val){
	Items[Index] = Items[Index] + Val;
	if (Items[Index] < 0) { Items[Index] = 0;}
	if (Items[Index] > ItemMax[Index]) { Items[Index] = ItemMax[Index];}
	if (MyNumber < 2) {
		FrmScreen.SetStatus((MyNumber), Index, Items[Index] / ItemMax[Index]);
	}
}

bool Guy::EW(Player *p){
	auto c = FrmScreen.GetControll((MyNumber));
	if (c.Change && c.Jump) {
		FrmScreen.RemoveObject(this);
		p->MyNumber = MyNumber;
		FrmScreen.SetPlayer(MyNumber, p);
		PlaySound(dsOpen);
		return 1;
	}
	return 0;
}

void Guy::PickUp(std::string Item){
	Weapons.AddWeapon(Item);
}

void Guy::UpDateItems(){
	long i;
	for(i = 0; i <= 7; ++i){
		FrmScreen.SetStatus(MyNumber, i, Items[i] , ItemMax[i]);
	}
}
