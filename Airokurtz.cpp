/*
 * Airokurtz.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Airokurtz.h"
#include "aux.h"
#include "Guy.h"
#include "Spark.h"
#include <math.h>

Airokurtz::Airokurtz() {

	TurnIT = -1;
	Weapons.Init(this);
	Weapons.AddWeapon("carlgustaf");
	Dying = false;

}

Airokurtz::~Airokurtz() {
	// TODO Auto-generated destructor stub
}


void Airokurtz::TimeTab(){
	int i;
	long modXS; long modYS;
	YSpeed = YSpeed + 0.4;
	XSpeed = XSpeed / 1.05;
	if (YSpeed > 0) { YSpeed = YSpeed / 1.1;}
	;
	OnGround = 0;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	;
	if (FrmScreen.GetMap((XPos), YPos - 15) > mWater) {
		if (YSpeed < 0) {
			YPos = YPos - YSpeed + 1;
			YSpeed = -YSpeed / 2;
			modYS = 1;
		}
	}
	if (FrmScreen.GetMap((XPos), YPos) > mWater) {
		if (YSpeed > 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 2;
			modYS = 1;
		}
	}
	;
	if (FrmScreen.GetMap(XPos + 6, YPos - 2) > mWater) {
		if (XSpeed > 0) {
			for(i = 0; i <= 4; ++i){
				if (FrmScreen.GetMap(XPos + 6, YPos - i - 2) == mAir) {
					YPos = YPos - i - 2;
					YSpeed = 0;
					modYS = 1;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 6, YPos - 2) > mWater) {
		if (XSpeed < 0) {
			for(i = 0; i <= 4; ++i){
				if (FrmScreen.GetMap(XPos - 6, YPos - i - 2) == mAir) {
					YPos = YPos - i - 2;
					YSpeed = 0;
					modYS = 1;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos + 6, YPos - 3) > mWater) {
		if (XSpeed > 0) {
			XPos = XPos - XSpeed;
			XSpeed = -XSpeed;
			modXS = 1;
		}
	}
	if (FrmScreen.GetMap(XPos - 6, YPos - 3) > mWater) {
		if (XSpeed < 0) {
			XPos = XPos - XSpeed;
			XSpeed = -XSpeed;
			modXS = 1;
		}
	}
	if (FrmScreen.GetMapLine(XPos, YPos - 5, XSpeed, YSpeed) > mWater) {
		if (modYS == 0) {
			YPos = YPos - YSpeed - 0.3;
			YSpeed = -0.3;
		}
		if (modXS == 0) {
			XPos = XPos - YSpeed;
			XSpeed = 0;
		}
	}

	for(i = 0; i <= 10; ++i){
		if (FrmScreen.GetMap((XPos), YPos + i * 2) > mWater) {
			YSpeed = YSpeed - 1 - 0.1 * (10 - i);
			break;
		}
	}
	if (i < 20) {
		OnGround = 1;
	}

	if (MyNumber < 2) {
		FrmScreen.SetScreenPos( (MyNumber), (XPos), (YPos));
		auto c = FrmScreen.GetControll((MyNumber));
		if (OnGround) {
			XSpeed = XSpeed + (30 - XSpeed * c.MoveDirection) * c.MoveDirection / 20;
			if (c.AimDirection == 1 && c.Jump) {
				YSpeed = YSpeed + 3;
				CalcItem(2, 10);
			}
		}else{
			XSpeed = XSpeed + c.MoveDirection * 1.;
		}
		if (c.MoveDirection) { TurnIT = c.MoveDirection;}
		if (c.Change) {
			if (c.AimDirection == -1) {
				Weapons.SetNextWeapon();
			}else if (c.AimDirection == 1) {
				DropGuy();
			}
		}
		Weapons.GetCurrentWeapon()->Fire ((XPos), (YPos), XAim, Aim, (TurnIT), c.Fire);
		if (c.Jump) {
			if (Items[2] > 10) {
				CalcItem(2, -10);
				YSpeed = YSpeed - 1.5;
			}
		}
		Aim = Aim + c.AimDirection * 2;
		if (c.AimDirection) {
			if (Aim > 30) { Aim = 30;}
			if (Aim < -40) { Aim = -40;}
			XAim = sqrt(2500 - Aim * Aim);
		}
	}else{
		if (Items[0] < 20 && (int)(Rnd() * 100) == 1) { Die();}
		i = FrmScreen.isPlayer(XPos, YPos, 30, 30);
		if (i != 0) {
			if ( FrmScreen.getPlayer(i - 1)->isGuy()) {
				auto guy = (Guy*) FrmScreen.getPlayer(i - 1);
				guy->EW (this);
				UpDateItems();
			}
		}
	}

	CalcItem(1, 30);
	CalcItem(2, 3);
}

void Airokurtz::Render(){
	FrmScreen.DrawOnePlPic( MyNumber, ddCrossHair, XPos + XAim * TurnIT - 7.5, YPos + Aim - 7.5, 0);

	frmScreen.DrawPlPic(ddAirokurtz, XPos - 15, YPos - 12, 0.5 + (double)TurnIT / 2);
}

void Airokurtz::Init(double X, double Y, double XSpeed2, double YSpeed2, int Number){
	long i;
	XAim = 50;
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
	;
	Items[2] = 5 * GamePlay.Ammo;
	ItemMax[2] = 5 * GamePlay.Ammo;
	if (MyNumber < 2) { FrmScreen.SetStatus((MyNumber), 2, 1);}
	UpDateItems();
}

void Airokurtz::Damage(long Val){
	if (Dying) { return;;}
	Items[0] = Items[0] - Val;
	if (Items[0] < 0) {
		Die();
		Items[0] = 0;
	}
	if (MyNumber < 2) {
		FrmScreen.SetStatus((MyNumber), 0, Items[0] , ItemMax[0]);
	}

	if (Items[0] > ItemMax[0]) {
		Items[0] = ItemMax[0];
	}
	FrmScreen.DrawPlPic(ddAirokurtz, XPos - 15, YPos - 12, 2);
}

void Airokurtz::Die(){
	Dying = 1;
	FrmScreen.RemoveObject(this);
	long i;
	for(i = 0; i <= 10; ++i){
		auto nSpark = new Spark;
		nSpark->Init((XPos), (YPos), 6 * Rnd() - 3, 6 * Rnd() - 3);
		FrmScreen.AddObject(nSpark);
	}
	if (MyNumber < 2) { FrmScreen.MakePlayers (MyNumber);}
	PlaySound(dsExplosion);
	FrmScreen.KilledPlayer(MyNumber);
}

void Airokurtz::DropGuy(){
	auto guy = new Guy;
	guy->Init(XPos, YPos, XSpeed, YSpeed, MyNumber);
	FrmScreen.AddObject(guy);
	FrmScreen.SetPlayer(MyNumber, guy);
	MyNumber = 2;
}

void Airokurtz::PickUp(std::string Item){
	Weapons.AddWeapon(Item);
}

void Airokurtz::UpDateItems(){
	long i;
	for(i = 0; i <= 7; ++i){
		FrmScreen.SetStatus(MyNumber, i, Items[i] , ItemMax[i]);
	}
}
