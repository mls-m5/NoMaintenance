/*
 * Phykoser.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Phykoser.h"
#include "aux.h"
#include "Guy.h"
#include "IBomb.h"
#include "Spark.h"
#include <math.h>

Phykoser::Phykoser() {
	Weapons.Init(this);
	Weapons.AddWeapon("flashbang");

}

Phykoser::~Phykoser() {
	// TODO Auto-generated destructor stub
}


void Phykoser::TimeTab(){
	long i;
	YSpeed = YSpeed + (10 - YSpeed) / 10;
	;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	;
	OnGround = 0;
	;
	if (FrmScreen.GetMapLine((XPos), (YPos) + 1, XSpeed, YSpeed) > mWater) {
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
				if (FrmScreen.GetMap(XPos - 12, YPos - i)) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 11, YPos - 2) > mWater && XSpeed < 0) {
		if (XSpeed < 0) {
			for(i = 0; i <= 10; ++i){
				if (FrmScreen.GetMap(XPos - 11 + i, YPos - 2)) {
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
		OnGround = 1;
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
		OnGround = 1;
		if (JetsOn) { XSpeed = 0; }else{ XSpeed = XSpeed / 1.1;}
	}
	if (OnGround) { WheelCalculate (XSpeed);}
	;
	if (MyNumber < 2) {
		auto c = FrmScreen.GetControll((MyNumber));
		if (SwitchDelay > 0) {
			SwitchDelay = SwitchDelay - 1;
		}else if (SwitchJet) {
			JetsOn = !JetsOn;
			SwitchJet = 0;
		}
		JetRotation = c.MoveDirection;
		if (c.Reload) {
			if (c.Jump) {
				SwitchJet = 1;
				SwitchDelay = 3;
			}
		}else if (JetsOn) {
			if (c.Jump && Items[2] > 20) {
				YSpeed = YSpeed - 2;
				FrmScreen.MakeSmoke(XPos + 11, YPos + 4, -JetRotation * 3 + XSpeed, 5 + YSpeed, 3);
				FrmScreen.MakeSmoke(XPos - 11, YPos + 4, -JetRotation * 3 + XSpeed, 5 + YSpeed, 3);
				CalcItem(2, -20);
			}
			WheelY = 5;
		}else{
			WheelY = 5 + (int)(c.Jump) * 10;
		}
		if (OnGround && !JetsOn) {
			XSpeed = XSpeed + (15 - XSpeed * c.MoveDirection) * c.MoveDirection / 5;
		}
		else{
			XSpeed = XSpeed + c.MoveDirection * 0.5;
		}
		if (!OnGround) { WheelCalculate( c.MoveDirection * 2);}
		if (c.MoveDirection) { TurnIT = c.MoveDirection;}
		Weapons.GetCurrentWeapon()->Fire( (XPos), (YPos), XAim, Aim, (TurnIT), c.Fire);
		Aim = Aim + c.AimDirection * 2;
		if (c.AimDirection) {
			if (Aim > 30) { Aim = 30;}
			if (Aim < -50) { Aim = -50;}
			XAim = sqrt(2500 - Aim * Aim);
		}
		if (CrossVar == 1) { CrossVar = 0; }else{ CrossVar = 1;}
		FrmScreen.SetScreenPos( (MyNumber), (XPos) + 50 * TurnIT, (YPos) + Aim);
		if (c.Change) {
			if (c.AimDirection == -1) {
				Weapons.SetNextWeapon();
			}else if (c.AimDirection == 1) {
				DropGuy();
			}
		}
		if (ItemMax[0]) {
			FrmScreen.SetStatus((MyNumber), 0, Items[0] , ItemMax[0]);
		}
	}else{
		if (Items[0] < 20 && (int)(Rnd() * 100) == 1) { Die();}
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
	CalcItem(0, 1);
	CalcItem(1, 35);
	CalcItem(2, 5);
}

void Phykoser::Render(){
	FrmScreen.DrawOnePlPic( MyNumber, ddCrossHair, XPos + XAim * TurnIT - 7.5, YPos + Aim - 7.5, 4);

	FrmScreen.DrawPlPic(ddChassi, XPos - 11, YPos - 22, 8.5 + (double)TurnIT / 2);
	if (SwitchJet) {
		FrmScreen.DrawPlPic(ddJetWheel, XPos - 11, YPos + CWheelY[0] - 12, 0);
		FrmScreen.DrawPlPic(ddJetWheel, XPos + 5, YPos + CWheelY[1] - 12, 0);
	}else if (JetsOn) {
		FrmScreen.DrawPlPic(ddJetWheel, XPos - 11, YPos + CWheelY[0] - 12, 2 + JetRotation);
		FrmScreen.DrawPlPic(ddJetWheel, XPos + 5, YPos + CWheelY[1] - 12, 2 + JetRotation);
	}else{
		FrmScreen.DrawPlPic(ddWheel, XPos - 11, YPos + CWheelY[0] - 12, (WheelRotate));
		FrmScreen.DrawPlPic(ddWheel, XPos + 5, YPos + CWheelY[1] - 12, (WheelRotate));
	}

	if (MyNumber == 0 || MyNumber == 2){
		if (FrmScreen.GetControll(MyNumber).Change){
			frmScreen.DrawText(XPos, YPos - 20, Weapons.GetCurrentWeapon()->name);
		}
	}
}

void Phykoser::Init(double X, double Y, double XSpeed2, double YSpeed2, int Number){
	Dying = false;
	JetsOn = false;
	SwitchDelay = 0;
	JetRotation = 0;
	WheelY = 0;
	CWheelY[0] = CWheelY[1] = 0;
	WheelRotate = 0;
	OnGround = false;
	TurnIT = 1;
	Aim = 0;
	XAim = 30;

	long i;
	MyNumber = Number;
	XPos = X;
	YPos = Y;
	XSpeed = XSpeed2;
	XAim = 50;
	YSpeed = YSpeed2;
	Width = 22 / 2;
	Height = 22 / 2;
	Items[0] = 0.5 * GamePlay.Armor;
	ItemMax[0] = 0.5 * GamePlay.Armor;
	FrmScreen.SetStatus((MyNumber), 0, 1);
	for(i = 1; i <= 7; ++i){
		Items[i] = 2.5 * GamePlay.Ammo;
		ItemMax[i] = 4 * GamePlay.Ammo;
	}
	UpDateItems();
}

void Phykoser::WheelCalculate(double Val){
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

void Phykoser::Damage(long Val){
	if (Dying) { return;;}
	Items[0] = Items[0] - Val * 2;
	if (Items[0] < 0) {
		Die();
		Items[0] = 0;
	}
	if (Items[0] > ItemMax[0]) { Items[0] = ItemMax[0];}
}

void Phykoser::Die(){
	Dying = 1;
	long i;
	for(i = 0; i <= 20; ++i){
		auto nSpark = new Spark;
		nSpark->Init((XPos), (YPos), 6 * Rnd() - 3, 6 * Rnd() - 3);
		FrmScreen.AddObject(nSpark);
	}
	FrmScreen.RemoveObject(this);
	FrmScreen.Explosion((XPos - 7), (YPos), 1, 30, 10);
	FrmScreen.Explosion((XPos + 7), (YPos), 1, 30, 10);
	auto nBomb = new IBomb;
	nBomb->Init((XPos), (YPos), 0);
	FrmScreen.AddObject(nBomb);
	if (MyNumber < 2) { FrmScreen.MakePlayers (MyNumber);}
	PlaySound(dsExplosion);
	FrmScreen.MakeQuake(20);
	FrmScreen.KilledPlayer(MyNumber);
}


void Phykoser::DropGuy(){
	auto guy = new Guy();
	guy->Init(XPos, YPos, XSpeed, YSpeed, MyNumber);
	FrmScreen.AddObject(guy);
	FrmScreen.SetPlayer(MyNumber, guy);
	MyNumber = 2;
}

void Phykoser::PickUp(std::string Item){
	Weapons.AddWeapon(Item);
}
