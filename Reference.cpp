/*
 * Reference.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "Reference.h"
#include <string>
#include "Guy.h"
#include "common.h"
#include <math.h>

const int WheelY = 5;

Reference::Reference() {
	TurnIT = -1;
	Weapons.Init(this);
	Weapons.AddWeapon("tropelet");
	Aim = 0;
	WheelRotate = 0;
	Dying = false;
	XAim = 0;
	SmokeTrace = 0;
	JumpLeft = 0;
	OnGround = false;
	CWheelY[0] = 0;
	CWheelY[1] = 0;

}

Reference::~Reference() {
}

void Reference::TimeTab(){
	long i;
	YSpeed = YSpeed + (10 - YSpeed) / 10;
	;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	;
	OnGround = 0;
	;
	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) > mWater) {
		if (YSpeed > 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed;
		}
	}
	if (FrmScreen.GetMapLine((XPos), (YPos) - 20, XSpeed, YSpeed) > mWater) {
		if (YSpeed < 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed;
		}
	}
	if (FrmScreen.GetMap((XPos), YPos - 15) > mWater) {
		if (YSpeed < 0) {
			YPos = YPos - YSpeed;
			YSpeed = -YSpeed;
		}
	}
	;
	if (FrmScreen.GetMap(XPos + 12, YPos) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 7; ++i){
				if (FrmScreen.GetMap(XPos + 12, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 12, YPos) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 7; ++i){
				if (FrmScreen.GetMap(XPos - 12, YPos - i) > mWater) {
					YPos = YPos - i;
					break;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos - 7, YPos - 2) > mWater && XSpeed < 0) {
		if (XSpeed < 0) {
			for(i = 0; i <= 20; ++i){
				if (FrmScreen.GetMap(XPos - 7 + i, YPos - 2) > mWater) {
					XPos = XPos + i;
					XSpeed = 0;
				}
			}
		}
	}
	if (FrmScreen.GetMap(XPos + 7, YPos - 2) > mWater && XSpeed > 0) {
		if (XSpeed > 0) {
			for(i = 0; i <= 20; ++i){
				if (FrmScreen.GetMap(XPos + 7 - i, YPos - 2) > mWater) {
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
		XSpeed = XSpeed / 1.1;
	}
	if (OnGround) { WheelCalculate (XSpeed);}
	if (XSpeed > 20) { XSpeed = 20;}
	if (XSpeed < -20) { XSpeed = -20;}

	if (MyNumber < 2) {
		auto c = FrmScreen.GetControll((MyNumber));
		if (OnGround) {
			XSpeed = XSpeed + (20. - XSpeed * c.MoveDirection) * c.MoveDirection / 5.;
		}
		else{
			XSpeed = XSpeed + c.MoveDirection * 0.5;
			WheelCalculate (c.MoveDirection * 2);
		}
		if (c.MoveDirection && c.Reload) {
			if (Items[2] > 9) {
				YSpeed = -1;
				XSpeed = 9 * TurnIT;
				SmokeTrace = 1;
				CalcItem(2, -9);
			}
		}
		JumpLeft = JumpLeft - 1;
		if (JumpLeft < 1) {
			JumpLeft = 0;
			if (c.Jump && Items[2] > 60) {
				YSpeed = -20;
				SmokeTrace = 20;
				CalcItem(2, -50);
				JumpLeft = 18;
			}
		}
		if (c.MoveDirection) { TurnIT = c.MoveDirection;}
		if (c.Fire) {
			if (c.Reload) {
				if (Items[2] > 399) {
					MakeWarp();
					Items[2] = 0;
				}
			}
			else{
				Weapons.GetCurrentWeapon()->Fire( (XPos), (YPos), XAim, Aim, (TurnIT), 1);
			}
		}
		else{
			Weapons.GetCurrentWeapon()->Fire( (XPos), (YPos), XAim, Aim, (TurnIT), 0);
		}
		if (c.AimDirection) {
			if (c.Reload) {
				if (Items[2] > 9) {
					YSpeed = -1 + 9 * c.AimDirection;
					XSpeed = 0;
					SmokeTrace = 1;
					CalcItem(2, -9);
				}
			}else if (!c.Change){
				Aim = Aim + c.AimDirection * 2;
				if (Aim > 30) { Aim = 30;}
				if (Aim < -50) { Aim = -50;}
				XAim = sqrt (2500 - Aim * Aim);
			}
		}
		if (CrossVar == 1) { CrossVar = 0 ;}else{ CrossVar = 1;}
		FrmScreen.SetScreenPos( (MyNumber), (XPos) + 50 * TurnIT, (YPos) + Aim);
		if (c.Change) {
			if (c.AimDirection == -1) {
				Weapons.SetNextWeapon();
			}else if (c.AimDirection == 1) {
				DropGuy();
			}
		}
		FrmScreen.SetStatus((MyNumber), 0,  Items[0] ,  ItemMax[0]);
	}
	else{
		if ( Items[0] < 20 && (int)(Rnd() * 100) == 1) {
			Die();
		}
		i = FrmScreen.isPlayer(XPos, YPos, 30, 30);
		if (i != 0) {
			if ( FrmScreen.getPlayer(i - 1)->isGuy()) {
				auto guy = (Guy*) FrmScreen.getPlayer(i - 1);
				guy->EW (this);
				UpDateItems();
			}
		}
	}
	CalcItem(1, 35);
	CalcItem(2, 5);
	if (SmokeTrace > 0) {
		SmokeTrace = SmokeTrace - 1;
		FrmScreen.MakeSmoke(XPos, YPos - 10, 0, 0, 1);
	}
}

void Reference::Render(){
	FrmScreen.DrawOnePlPic( MyNumber, ddCrossHair, XPos + XAim * TurnIT - 7.5, YPos + Aim - 7.5, 0);
	FrmScreen.DrawPlPic(ddChassi, XPos - 11, YPos - 22, 4.5 + (double)TurnIT / 2.);
	FrmScreen.DrawPlPic(ddWheel, XPos - 11, YPos + CWheelY[0] - 12, (WheelRotate));
	FrmScreen.DrawPlPic(ddWheel, XPos + 5, YPos + CWheelY[1] - 12, (WheelRotate));

	if (MyNumber == 0 || MyNumber == 2){
		if (FrmScreen.GetControll(MyNumber).Change){
			frmScreen.DrawText(XPos, YPos - 20, Weapons.GetCurrentWeapon()->name);
		}
	}
}

void Reference::Init(double X, double Y, double XSpeed2, double YSpeed2, int Number){
	long i;
	MyNumber = Number;
	XPos = X;
	YPos = Y;
	XSpeed = XSpeed2;
	XAim = 50;
	YSpeed = YSpeed2;
	Width = 22 / 2;
	Height = 22 / 2;
	Items[0] = 1 * GamePlay.Armor;
	ItemMax[0] = 1.25 * GamePlay.Armor;
	FrmScreen.SetStatus((MyNumber), 0, 1);
	for(i = 1; i <= 7; ++i){
		Items[i] = 4 * GamePlay.Ammo;
		ItemMax[i] = 4 * GamePlay.Ammo;
	}
	UpDateItems();
}

void Reference::WheelCalculate(float Val){
	WheelRotate = WheelRotate + Val;
	if (WheelRotate < -1000) WheelRotate = 0;
	if (WheelRotate > 1000) WheelRotate = 0;
	while (1){
		if (WheelRotate < 0) {
			WheelRotate = WheelRotate + 7;
		}else if (WheelRotate > 7) {
			WheelRotate = WheelRotate - 7;
		}else{
			return;
		}
	}
}

void Reference::Damage(long Val){
	if (Dying) { return;;}
	Items[0] =  Items[0] - Val;
	if ( Items[0] < 0) {
		Die();
		Items[0] = 0;
	}
	if ( Items[0] >  ItemMax[0]) {  Items[0] =  ItemMax[0];}
}

void Reference::Die(){
	Dying = 1;
	FrmScreen.RemoveObject(this);
	if (MyNumber < 2) { FrmScreen.MakePlayers (MyNumber);}
	FrmScreen.MakeSmoke(XPos, YPos, -3, 0, 1);
	FrmScreen.MakeSmoke(XPos, YPos, 3, 0, 1);
	FrmScreen.KilledPlayer(MyNumber);
}

void Reference::DropGuy(){
	auto guy = new Guy;
	guy->Init(XPos, YPos, XSpeed, YSpeed, MyNumber);
	FrmScreen.AddObject(guy);
	FrmScreen.SetPlayer(MyNumber, guy);
	MyNumber = 2;
}

void Reference::PickUp(std::string Item){
	Weapons.AddWeapon(Item);
}

void Reference::UpDateItems(){
	long i;
	for(i = 0; i <= 7; ++i){
		FrmScreen.SetStatus(MyNumber, i, Items[i] , ItemMax[i]);
	}
}

void Reference::MakeWarp(){
	long i; long X; long Y;
	long MapX; long MapY;
	MapX = frmScreen.GetMapWidth();
	MapY = frmScreen.GetMapHeight();
	FrmScreen.MakeSmoke(XPos, YPos, -3, 0, 1);
	FrmScreen.MakeSmoke(XPos, YPos, 3, 0, 1);
	for(i = 0; i <= 1000; ++i){
		X = (MapX - 20) * Rnd() + 10;
		Y = (MapY - 20) * Rnd() + 10;
		if (FrmScreen.GetMap(X, Y) == mAir) { break;}
	}
	XPos = X;
	YPos = Y;
	FrmScreen.MakeSmoke(XPos, YPos, -3, 0, 1);
	FrmScreen.MakeSmoke(XPos, YPos, 3, 0, 1);
	FrmScreen.MakeQuake(20);
}
