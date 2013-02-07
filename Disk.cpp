/*
 * Disk.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Disk.h"
#include "aux.h"

Disk::Disk() {

}

Disk::~Disk() {
}

void Disk::Init(double X, double Y, double Xs, double Ys){
    XPos = X;
    YPos = Y;
    XSpeed = Xs;
    YSpeed = Ys;
    HLeft = 50;
}

void Disk::TimeTab(){
    long i;
    XPos = XPos + XSpeed;
    YPos = YPos + YSpeed;
    HLeft = HLeft - 1;
    if (HLeft < 1) {
    	FrmScreen.RemoveObject(this);
    }
    i = FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed);
    if (i) {
        FrmScreen.Explosion((XPos), (YPos), 0, 2, 0);
        HLeft = HLeft - 16;
        if (i == mRock) { HLeft = 0;}
        XPos = XPos - XSpeed / 1.5;
        YPos = YPos - YSpeed / 1.5;
    }
    i = FrmScreen.isPlayer((XPos), (YPos));
    if (i) {
        FrmScreen.HitPlayer(i - 1, 2);
        FrmScreen.Explosion(XPos, YPos, 1, 0, 0);
    }
}

void Disk::Render() {
    FrmScreen.DrawPlPic(ddDisk, XPos - 5, YPos - 5, 0);
}

