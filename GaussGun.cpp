/*
 * GaussGun.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "GaussGun.h"
#include "aux.h"

struct Position{
	double X, Y;
};

GaussGun::GaussGun() {
	NextShot = 0;

}

GaussGun::~GaussGun() {
	// TODO Auto-generated destructor stub
}

void GaussGun::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    if (NextShot) { NextShot = NextShot - 1;}
    if (!isFire || NextShot) { return;;}
    if (MyPlayer->getItem(1) < 50 || MyPlayer->getItem(3) < 2) { return;;}
    NextShot = 20;
    MyPlayer->setItem (1, 0);
    MyPlayer->CalcItem(3, -2);
    long i; Position Speed; Position Pos;
    Speed.X = XAim / 10 * Turn;
    Speed.Y = YAim / 10;
    Pos.X = X + XAim / 3 * Turn;
    Pos.Y = Y + YAim / 3;
    for(i = 0; i <= 100; ++i){
        Pos.X = Pos.X + Speed.X;
        Pos.Y = Pos.Y + Speed.Y;
        if (FrmScreen.GetMap((Pos.X), (Pos.Y)) || FrmScreen.isPlayer((Pos.X), (Pos.Y))) {
            FrmScreen.Explosion((Pos.X), (Pos.Y), 0, 5, 20);
            i = i + 10;
            if (i > 100) { break;}
        }
    }
    PlaySound(dsFire5);
}


