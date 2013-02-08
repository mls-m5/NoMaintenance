/*
 * Grenade.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Grenade.h"
#include "common.h"

Grenade::Grenade() {
	// TODO Auto-generated constructor stub

}

Grenade::~Grenade() {
	// TODO Auto-generated destructor stub
}



void Grenade::Init(double X, double Y, double Xs, double Ys){
    XPos = X;
    YPos = Y;
    XSpeed = Xs;
    YSpeed = Ys;
    HLeft = 20 + Rnd() * 5;
    NextSmoke = 0;
}

void Grenade::TimeTab(){
    YSpeed = YSpeed + 0.3;
    XPos = XPos + XSpeed;
    YPos = YPos + YSpeed;
    HLeft = HLeft - 1;
    NextSmoke = NextSmoke - 1;
    if (NextSmoke < 0) {
        NextSmoke = 2;
        FrmScreen.MakeSmoke(XPos, YPos, -XSpeed / 2, -YSpeed / 2);
    }
    if (HLeft < 1) {
        long i;
        FrmScreen.RemoveObject(this);
        for(i = 0; i <= 3; ++i){
            FrmScreen.Explosion(XPos + Rnd() * 30 - 15, YPos + Rnd() * 30 - 15, 1, 15, 15);
        }
        PlaySound(dsExplosion);
    }
    if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed)) {
    	if (FrmScreen.GetMap(XPos + XSpeed, YPos - YSpeed / 2)) {
            XSpeed = -XSpeed / 1.2;
        }
        if (FrmScreen.GetMap(XPos + XSpeed, YPos + YSpeed)) {
            YSpeed = -YSpeed / 1.2 - 0.3;
        }
    }
    if (FrmScreen.isPlayer(XPos, YPos)) { HLeft = 0;}
}

void Grenade::Render(){
    FrmScreen.DrawPlPic(ddBomb, XPos - 3, YPos - 3, 0);
}
