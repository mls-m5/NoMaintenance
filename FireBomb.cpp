/*
 * FireBomb.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "FireBomb.h"
#include "common.h"
#include "Fire.h"

FireBomb::FireBomb() {
	// TODO Auto-generated constructor stub

}

FireBomb::~FireBomb() {
	// TODO Auto-generated destructor stub
}


void FireBomb::Init(double X, double Y, double Xs, double Ys, long Ammo){
    XPos = X;
    YPos = Y;
    XSpeed = Xs;
    YSpeed = Ys;
    Power = Ammo;
    Action = 0;
}

void FireBomb::TimeTab(){
    bool isHit;
    YSpeed = YSpeed + 0.5;
    XPos = XPos + XSpeed;
    YPos = YPos + YSpeed;
    if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed)) {
        isHit = 1;
    }
    if (FrmScreen.isPlayer((XPos), (YPos))) {
        isHit = 1;
    }
    if (!Action == 0) {
    	auto Flame = new class Fire;
        Flame->Init((XPos), (YPos), 0, 4);
        FrmScreen.AddObject(Flame);
        Action = Action - 1;
        if (Action == 1) {
            FrmScreen.RemoveObject(this);
        }
    }
    if (!isHit) { return;;}
    FrmScreen.Explosion(XPos - XSpeed, YPos - YSpeed, 1, 15, 50);
    YPos = YPos + 5;
    PlaySound(dsExplosion);
    if (Action == 0) {
        Action = Power * 1.5 + 5;
        YPos = YPos - YSpeed * 2;
        XPos = XPos - XSpeed * 2;
        XSpeed = 0;
        YSpeed = -Power / 1.5;
    }else{
        FrmScreen.RemoveObject(this);
    }
}

void FireBomb::Render() {
    FrmScreen.DrawPlPic(ddShell, XPos - 5, YPos - 5, GetRot(XSpeed, YSpeed, 15));
}

