/*
 * Hao.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Hao.h"
#include "common.h"
#include "Spark.h"
#include <math.h>
#include "Guy.h"

Hao::Hao() {
	TurnIT = -1;
	Weapons.Init(this);
	Weapons.AddWeapon("jolt");
}

Hao::~Hao() {
	// TODO Auto-generated destructor stub
}


void Hao::TimeTab(){
	int i;
	long modXS; long modYS;
	if (XSpeed < -1) {
		YSpeed = (YSpeed + 2.1 / -(XSpeed - 2) - 0.1) / 1.1;
		XSpeed = XSpeed / 1.05;
	}else if (XSpeed > 1) {
		YSpeed = (YSpeed + 2.1 / (XSpeed + 2) - 0.1) / 1.1;
		XSpeed = XSpeed / 1.05;
	}else{
		YSpeed = YSpeed + 0.6;
		XSpeed = XSpeed / 1.05;
	}
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	;
	;
	OnGround = 0;
	if (FrmScreen.GetMap((XPos), YPos - 15) > mWater) {
		if (YSpeed < 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 2;
			modYS = 1;
		}
	}
	if (FrmScreen.GetMap((XPos), YPos) > mWater) {
		if (YSpeed > 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 2;
		}
		modYS = 1;
	}
	if (FrmScreen.GetMap(XPos + 6, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 4; ++i){
				if (FrmScreen.GetMap(XPos + 6, YPos - i) > mWater) {
					YPos = YPos - i;
					modYS = 1;
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
					modYS = 1;
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
			modXS = 1;
		}
	}
	if (FrmScreen.GetMap(XPos + 6, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			XPos = XPos - XSpeed;
			XSpeed = -XSpeed;
			modXS = 1;
		}
	}
	if (FrmScreen.GetMapLine((XPos), YPos - 2, XSpeed, YSpeed) > mWater) {
		if (modYS == 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed / 4;
		}
		if (modXS == 0) {
			XPos = XPos - XSpeed;
			XSpeed = 0;
		}
	}

	if (Dying && (int)(Rnd() * 50) == 1) { Terminate();}

	if (MyNumber < 2) {
		auto c = FrmScreen.GetControll((MyNumber));
		for(i = 0; i <= 10; ++i){
			if (FrmScreen.GetMap((XPos), YPos + i * 2)) {
				YSpeed = YSpeed - 1 - 0.1 * (10 - i);
				break;
			}
		}
		if (c.Change) {
			if (c.AimDirection == 1) {
				DropGuy();
			}else if (c.AimDirection == -1) {
				Weapons.SetNextWeapon();
			}
		}
		CAim = CAim - (double)c.AimDirection / 10.;
		if (c.AimDirection) {
			if (CAim > 2) { CAim = 2;}
			if (CAim < -2) { CAim = -2;}
			Aim = cos(CAim) * 50 ;
			XAim = sin(CAim) * 50;
		}
		FrmScreen.MakeSmoke((XPos), YPos - 3, Rnd() / 2 - 0.25, Rnd() / 2 - 0.25, 3);
		if (c.Jump) { YSpeed = YSpeed - 1;}
		if (c.Reload) { YSpeed = YSpeed + 0.7;}
		if (c.MoveDirection) { TurnIT = c.MoveDirection;}
		XSpeed = XSpeed + c.MoveDirection * 1 / 1.1;
		Weapons.GetCurrentWeapon()->Fire ((XPos), (YPos), XAim, Aim, (TurnIT), c.Fire);
		FrmScreen.SetScreenPos ((MyNumber), (XPos) + XAim * TurnIT, (YPos) + Aim);
	}else{
		if (Items[0] < 20 && (int)(Rnd() * 100) == 1) { Die();}
		i = FrmScreen.isPlayer(XPos, YPos, 30, 30);
		if (i != 0) {
			auto guy = dynamic_cast<Guy *> (FrmScreen.getPlayer(i - 1));
			if (guy) {
				guy->EW( this);
				UpDateItems();
			}
		}
	}

	CalcItem(1, 30);
	CalcItem(2, 25);

	if (Dying) {
		FrmScreen.MakeSmoke(XPos, YPos, Rnd() * 4 - 2, Rnd() * 4 - 2);
		if (Rnd() * 5 > 4) { FrmScreen.Explosion(XPos + Rnd() * 10 - 5, YPos + Rnd() * 10 - 5, 1, 20, 0);}
		if (OnGround) {
			Terminate();
		}
	}
}

void Hao::Render(){
	FrmScreen.DrawOnePlPic (MyNumber, ddCrossHair, XPos + XAim * (double)TurnIT - 7.5, YPos + Aim - 7.5, 1);
	FrmScreen.DrawPlPic(ddEagle, XPos - 15, YPos - 12, 0.5 + (double)TurnIT / 2 + 2);

	if (MyNumber == 0 || MyNumber == 2){
		if (FrmScreen.GetControll(MyNumber).Change){
			frmScreen.DrawText(XPos, YPos - 20, Weapons.GetCurrentWeapon()->name);
		}
	}
}

void Hao::Init(double X, double Y, double XSpeed2, double YSpeed2, int Number){
	long i;
	Aim = 50;
	MyNumber = Number;
	XPos = X;
	YPos = Y;
	XSpeed = XSpeed2;
	YSpeed = YSpeed2;
	Width = 22 / 2;
	Dying = false;
	Height = 12 / 2;
	CAim = 0;
	Aim = 0;
	XAim = 50;
	TurnIT = 1;
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

void Hao::Damage(long Val){
	if (Dying) { return;;}
	Items[0] = Items[0] - Val;
	if (Items[0] < 0) {
		Die();
		Items[0] = 0;
	}
	if (MyNumber < 2) { FrmScreen.SetStatus((MyNumber), 0, Items[0] / ItemMax[0]);}
	if (Items[0] > ItemMax[0]) { Items[0] = ItemMax[0];}
}

void Hao::Die(){
	Dying = 1;
	FrmScreen.HugeExplosion(XPos, YPos, 60, 0);
	FrmScreen.MakeQuake(50);
}

void Hao::Terminate(){
	FrmScreen.RemoveObject(this);
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
	FrmScreen.KilledPlayer(MyNumber);
}

void Hao::DropGuy(){
	auto guy = new Guy();
	guy->Init(XPos, YPos, XSpeed, YSpeed, MyNumber);
	FrmScreen.AddObject(guy);
	FrmScreen.SetPlayer(MyNumber, guy);
	MyNumber = 2;
}

void Hao::PickUp(std::string Item){
	Weapons.AddWeapon(Item);
}

void Hao::UpDateItems(){
	long i;
	for(i = 0; i <= 7; ++i){
		FrmScreen.SetStatus(MyNumber, i, Items[i] , ItemMax[i]);
	}
}
