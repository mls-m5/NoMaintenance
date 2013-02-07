/*
 * Plasma.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Plasma.h"
#include "aux.h"

Plasma::Plasma() {
	// TODO Auto-generated constructor stub

}

Plasma::~Plasma() {
	// TODO Auto-generated destructor stub
}


void Plasma::Init(double X, double Y, double Xs, double Ys){
    XPos = X;
    YPos = Y;
    XSpeed = Xs;
    YSpeed = Ys;
}

void Plasma::TimeTab(){
    FrmScreen.MakeSmoke(XPos, YPos, Rnd() * 0.5 - 0.25, Rnd() * 0.5 - 0.25, 1);
    YSpeed = YSpeed * 1.1;
    XSpeed = XSpeed * 1.1;
    XPos = XPos + XSpeed;
    YPos = YPos + YSpeed;
    if (FrmScreen.GetMapLine(XPos, YPos, XSpeed, YSpeed) || FrmScreen.isPlayer(XPos, YPos, 5, 5)) {
        FrmScreen.Explosion(XPos, YPos, 1, 20, 20);
        FrmScreen.RemoveObject(this);
        PlaySound(dsExplosion);
        FrmScreen.MakeQuake(10);
    }
}

void Plasma::Render(){
    FrmScreen.DrawPlPic(ddDisk, XPos - 5, YPos - 5, 1 + Rnd());
}
